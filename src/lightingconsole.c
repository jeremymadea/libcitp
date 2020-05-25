/*
 * lightingconsole.c
 *
 * Jeremy Madea <jeremymadea@gmail.com>
 *
 * Behavior regarding CITP as specified in CITP Specification: 
 * Datagram (UDP) socket, port 4809, joined to multicast address 224.0.0.180:
 * - Regularly send a CITP/PINF/PLoc message with no listening port.
 *   - Receive CITP/PINF/PLoc messages to be aware of available visualizers and media servers.
 *   - Connect either automatically or on user demand to an available visualizer and/or media server. 
 *   - Receive CITP/MSEX/StFr Stream Frame video content from media server video subscriptions.
 * For all TCP connections to a media server: 
 * - Send CITP/PINF/PNam message immediately after connecting.
 * - Send CITP/MSEX/CInf Client Information message immediately after connecting.
 * - Receive CITP/MSEX/SInf Server Information and CITP/MSEX/LSta layer status messages.
 * - Send CITP/MSEX/GELI Get Element Library Information message(s) and initiate element 
 *   library update. Request all libraries of relevant type to the media server in question 
 *   (as identified by the CITP/PINF/PLoc Name field).
 * - Send CITP/MSEX/GVsr Get Video Sources message to retrieve information about available 
 *   video feeds.
 */

#include <stdio.h>      /* printf() and fprintf() */
#include <sys/select.h> /* select() */
#include <sys/socket.h> /* socket(), connect(), send(), and recv() */
#include <arpa/inet.h>  /* sockaddr_in and inet_addr() */
#include <stdlib.h>     /* atoi() and exit() */
#include <string.h>     /* memset() */
#include <unistd.h>     /* close() */
#include <signal.h>     /* signal() */
#include <fcntl.h>
#include <errno.h>
#include "citp.h"
#include "ucsutils.h"

#define RCVBUFSIZE 65536 /* Size of receive buffer */
#define SNDBUFSIZE 65536 /* Size of send buffer */
#define UDPBUFSIZE 65536 /* Size of UDP buffer */
#define BEACON_INTERVAL_USEC 1500000

/* UDP CONNECTION VARIABLES */ 
int                 g_udpsock;
char                g_udpbuf[UDPBUFSIZE];
struct sockaddr_in  g_saddr;
struct in_addr      g_iaddr;
struct ip_mreq      g_imreq;

struct citp_pinf_ploc *g_ploc; 
char *g_lib_type[] = { 
    "", /* 0 - unused */
    "Media (images & video)", 
    "Effects",
    "Cues",
    "Crossfades",
    "Masks", 
    "Blend presets",
    "Effect presets",  
    "Image presets",
    "3D Meshes" 
}; 

void die (char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

/* 
 * ucs2conv_braindead - returns a newly allocated string and copies
 *                      the ucs2 string pointed to by src into it, 
 *                      ignoring the ucs2 high bytes.
 */
char *ucs2conv_braindead(const ucs2 *src)
{
    char *new;
    char *ret; 
    new = malloc(ucs2strlen(src) + 1); 
    ret = new; 
    if (!new) { 
        die("Could not allocate memory for string"); 
    }
    while (*src != 0) {
       *new++ = *(ucs1 *)src++;
    }
    *new = '\0';
    
    return ret;
}

int udp_send_message(void *msg)
{ 
    uint32 msgsz; 
    int status;

    msgsz = ((struct citp_header *)msg)->message_size; 
    if (msgsz > UDPBUFSIZE) { 
       fprintf(stderr, "UDP buffer too small for message. (%d < %d)\n", 
               UDPBUFSIZE, msgsz);
       exit(EXIT_FAILURE);
    }

    status = citp_build_message((void *)g_udpbuf, UDPBUFSIZE, msg); 
    if (status == CITP_EUNKNOWN) { 
        fprintf(stderr, "Message type unknown.\n"); 
        exit(EXIT_FAILURE); 
    }
    if (status == CITP_EBIGMSG) { 
        fprintf(stderr, "Message too large for buffer.\n"); 
        exit(EXIT_FAILURE); 
    }
    
    status = sendto(g_udpsock, g_udpbuf, msgsz, 0,
                   (struct sockaddr *)&g_saddr, sizeof(struct sockaddr_in));
    if (status < 0) { 
        die("Error writing to socket");
    }
    if (status != msgsz) { 
        fprintf(stderr, "sendto() sent different number of bytes than expected.");
        exit(EXIT_FAILURE);
    }
    return 0; 
}

void *udp_recv_message()
{
    unsigned int bytes_read, addrlen; 
    struct sockaddr_in from; 

    addrlen = sizeof(struct sockaddr_in);
    bytes_read = recvfrom(g_udpsock, g_udpbuf, UDPBUFSIZE, 0, (struct sockaddr *)&from, &addrlen);

    if (from.sin_family != AF_INET) { 
        die("UDP message with unimplemented address family.");
    }

#ifdef DEBUG
printf("DEBUG: %d byte UDP message from %s:%d\n", bytes_read, inet_ntoa(from.sin_addr), ntohs(from.sin_port)); 
#endif 
    
    return citp_parse_message((void *)g_udpbuf); 
}


int tcp_send_message(int sock, char *buf, void *msg) 
{
    uint32 msgsz; 
    int status;

    msgsz = ((struct citp_header *)msg)->message_size; 

    if (msgsz > SNDBUFSIZE) {
       fprintf(stderr, "Send buffer too small for message. (%d < %d)\n", 
               SNDBUFSIZE, msgsz);
       exit(EXIT_FAILURE);
    }

    status = citp_build_message((void *)buf, SNDBUFSIZE, msg); /* construct the raw message. */ 
    if (status == CITP_EUNKNOWN) { 
        fprintf(stderr, "Message type unknown.\n"); 
        exit(EXIT_FAILURE); 
    }
    if (status == CITP_EBIGMSG) { 
        fprintf(stderr, "Message too large for buffer.\n"); 
        exit(EXIT_FAILURE); 
    }

    if (send(sock, buf, (size_t)msgsz, 0) != msgsz)
        die("send() sent a different number of bytes than expected");

    /* TODO Add more robust error checking. */

    return 0; 
}

int tcp_recv_nbytes(int sock, int n, char *buf) 
{
    int cur_bytes; 
    int tot_bytes = 0;

#ifdef DEBUG
printf("DEBUG: Attempting to recv %d bytes.\n", n); 
#endif
    while (tot_bytes < n) { 
        cur_bytes = recv(sock, buf + tot_bytes, n - tot_bytes, MSG_WAITALL); 
        if (cur_bytes < 0) { 
            //die("receive from socket failed"); 
        } else {
            tot_bytes += cur_bytes; 
#ifdef DEBUG
printf("DEBUG: Current bytes: %d Total bytes: %d\n", cur_bytes, tot_bytes);
#endif
        }
    }
    return tot_bytes; 
}

void *tcp_recv_message(int sock, char *buf) 
{
    uint32 msgsz; 
    int cur_bytes;
    int tot_bytes = 0; 
 
    /* Read in the CITP header to determine total message size. */
    tot_bytes = tcp_recv_nbytes(sock, CITP_HEADER_SIZE, buf); 
    if (tot_bytes != CITP_HEADER_SIZE) { 
       fprintf(stderr, "Did not receive full CITP header.");
       exit(EXIT_FAILURE);
        
    }

    msgsz = *(uint32 *)(buf + 8);

    if (msgsz > RCVBUFSIZE) { 
       /* TODO Read and discard chunks until done then bail. */
       /* Keeping it simple for now. */
       fprintf(stderr, "Message too big to receive");
       exit(EXIT_FAILURE);
    }
    
    cur_bytes = tcp_recv_nbytes(sock, msgsz - CITP_HEADER_SIZE, buf + CITP_HEADER_SIZE); 

    tot_bytes += cur_bytes;

    if (tot_bytes != msgsz) {
       fprintf(stderr, "WARNING: total_bytes different from msgsz.");
    } 
 
    return citp_parse_message((void *)buf); 
}

void handle_pinf(void *message) { 
    printf("Received CITP/PINF/"); 
    switch(((struct citp_pinf_header *)message)->content_type) {
        case CITP_COOKIE_PINF_PNAM: 
            printf("PNAM\n");
            printf("Name: %s\n", (char *)((struct citp_pinf_pnam *)message)->name); 
            break;
        case CITP_COOKIE_PINF_PLOC: 
            printf("PLOC\n"); 
            printf("Port: %d\n", ((struct citp_pinf_ploc *)message)->listening_tcp_port); 
            printf("Type: %s\n", (char *)((struct citp_pinf_ploc *)message)->type); 
            printf("Name: %s\n", (char *)((struct citp_pinf_ploc *)message)->name); 
            printf("State: %s\n", (char *)((struct citp_pinf_ploc *)message)->state); 
            break;
        default: 
            printf("UNKNOWN\n"); 
            break;
    }
    citp_delete_message(message);
}

void handle_msex(void *message) { 
    /* Convenience pointer for handling CITP/MSEX/SInf */
    struct citp_msex_1_0_sinf *sinf; 

    /* Convenience pointers for handling CITP/MSEX/LSta */
    struct citp_msex_1_0_lsta *lsta; 
    struct msex_1_0_layer_status *layer_status; 

    /* Convenience pointers for handling CITP/MSEX/ELIn */
    struct citp_msex_1_1_elin *elin;
    struct msex_1_1_element_library_info *libinfo; 

    uint32 msex_type;   
    uint8 mver, Mver;
    int i;
    char *name; 

    mver = ((struct citp_msex_header *)message)->version_minor; 
    Mver = ((struct citp_msex_header *)message)->version_major; 
    msex_type = ((struct citp_msex_header *)message)->content_type; 

#ifdef DEBUG
printf("DEBUG: MSEX Header ---\n");
fwrite(message, 1, sizeof(struct citp_msex_header), stdout);
printf("\nDEBUG: END of Header ---\n");
/*
printf("DEBUG: MSEX Message ---\n");
fwrite(message, 1, ((struct citp_header *)message)->message_size, stdout);
printf("\nDEBUG: END of Message ---\n");
*/
#endif

    switch(msex_type) { 
        case CITP_COOKIE_MSEX_SINF: 
            sinf = (struct citp_msex_1_0_sinf *)message; 
            name = ucs2conv_braindead(sinf->product_name); 
            printf("Server Information\n"); 
            printf("Connection made to '%s'\n", name); 
            printf("\tLayer count: %d\n", sinf->layer_count); 
            for (i=0; i<sinf->layer_count; i++) {
                printf("\tLayer %03d DMX source: %s\n", i, (char *)((sinf->layer_information + i)->dmx_source));
            }
            free(name);
            citp_delete_message(message);
            break;
        case CITP_COOKIE_MSEX_LSTA: 
            if (mver >=2) { 
                fprintf(stderr, "Unsupported MSEX LSta version: v%d.%d\n", Mver, mver);
                exit(EXIT_FAILURE); 
            }
            lsta = (struct citp_msex_1_0_lsta *)message; 
            printf("Layer Status Information\n"); 
            for (i=0; i<lsta->layer_count; i++) { 
                layer_status = (lsta->layer_status + i); 
                name = ucs2conv_braindead(layer_status->media_name);
                printf("%03d(%d) %s, ID:%d/%d Position %d/%d (%d fps)%s\n", 
                       layer_status->layer_number, layer_status->physical_output, name, 
                       layer_status->media_library_number, layer_status->media_number, 
                       layer_status->media_position, layer_status->media_length, layer_status->media_fps,
                       (layer_status->layer_status_flags & MSEX_LIBRARY_STATUS_MEDIAPLAYING) ? " Playing" : ""
                ); 
                free(name);
            }
            citp_delete_message(message);
            break; 
        case CITP_COOKIE_MSEX_ELIN: 
            switch(mver) { 
                case 0: printf("unimplemented CITP/MSEX/ELIn v1.0\n"); break;
                case 1: 
                    elin = (struct citp_msex_1_1_elin *)message; 
                    printf("Element Library Information\n");
                    printf("Library type: %s\n", g_lib_type[elin->library_type]); 
                    printf("Library count: %d\n", elin->library_count);
                    for (i=0; i<elin->library_count; i++) { 
                        libinfo = (elin->element_library_information + i); 
                        printf("ID: %d/%d/%d/%d\n", libinfo->id.level, libinfo->id.level1, libinfo->id.level2, libinfo->id.level3);
                        printf("DMX Range Min: %d\n", libinfo->dmx_range_min);
                        printf("DMX Range Max: %d\n", libinfo->dmx_range_max);
                        name = ucs2conv_braindead(libinfo->name); 
                        printf("Name: %s\n", name); 
                        printf("Library Count: %d\n", libinfo->library_count);
                        printf("Element Count: %d\n", libinfo->element_count);
                        free(name);
                    }
                    break;
                case 2: printf("unimplemented CITP/MSEX/ELIn v1.2\n"); break;
                default: printf("Unrecognized CITP/MSEX version v%d.%d\n", Mver, mver); break;
            }
            citp_delete_message(message);
            break;
        default: 
            printf("Got unimplemented MSEX message type: %x Version %d.%d\n", msex_type, Mver, mver); 
            citp_delete_message(message);
            break;
    }
    return;
}

void handle_unknown() { 
    printf("Unknown message type received. Ignoring.\n"); 
    return;
}

void beacon()
{
#ifdef DEBUG
printf("DEBUG: beacon (sending PLOC)\n");
#endif
    udp_send_message(g_ploc);
}

void setup_udp()
{   
    int status; 

    /* Initialize for safety. */
    memset(&g_saddr, 0, sizeof(struct sockaddr_in));
    memset(&g_iaddr, 0, sizeof(struct in_addr));
    memset(&g_imreq, 0, sizeof(struct ip_mreq));

    g_udpsock = socket(AF_INET, SOCK_DGRAM, 0);
    if (g_udpsock < 0) {
        die("Error creating UDP socket");
    }
    
    g_saddr.sin_family      = AF_INET;
    g_saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    g_saddr.sin_port        = htons(CITP_PINF_MULTICAST_PORT);

    status = bind(g_udpsock, (struct sockaddr *)&g_saddr, sizeof(struct sockaddr_in));
    if (status < 0) {
        die("Error binding to UDP socket");
    }

    g_iaddr.s_addr = INADDR_ANY;
    status = setsockopt(g_udpsock, IPPROTO_IP, IP_MULTICAST_IF, &g_iaddr, sizeof(struct in_addr));
    if (status < 0) { 
        die("Error setting socket option on UDP socket"); 
    }

    g_imreq.imr_multiaddr.s_addr = inet_addr(CITP_PINF_MULTICAST_IP);
    g_imreq.imr_interface.s_addr = INADDR_ANY; // use DEFAULT interface
    status = setsockopt(g_udpsock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (const void *)&g_imreq, sizeof(struct ip_mreq));

    if (status < 0) { 
        die("Error setting socket option on UDP socket"); 
    }

    /* Other defaults should be fine. 
     * IP_MULTICAST_LOOP default is 1 (enabled)
     * IP_MULTICAST_TTL  default is 1 (local subnet) 
     *
     * TTL should be configurable in a real tool. 
     */

    g_saddr.sin_family      = PF_INET;
    g_saddr.sin_addr.s_addr = inet_addr(CITP_PINF_MULTICAST_IP);
    g_saddr.sin_port        = htons(CITP_PINF_MULTICAST_PORT);
}

int main(int argc, char *argv[])
{

    /* TCP CONNECTION VARIABLES */
    int tcpsock;                     /* Socket descriptor */
    struct sockaddr_in mserver_addr; /* server address */
    unsigned short mserver_port;     /* server port */
    char *mserver_ip_quad;           /* Server IP address (dotted quad) */
    char sendbuf[SNDBUFSIZE];
    char recvbuf[RCVBUFSIZE];
    fd_set rfds;
    int maxfd; 
    struct timeval timeout; 
    int status;

    uint16 supported_msex_versions[] = {CITP_MSEX_VERSION_1_0, CITP_MSEX_VERSION_1_1, CITP_MSEX_VERSION_1_2};
    uint8 libnums[] = { 0 };
    struct msex_library_id libid = { 0, 0, 0, 0 }; 
    void *message; 

    struct citp_pinf_pnam *pnam; 
    struct citp_msex_cinf *cinf; 
    struct citp_msex_1_1_geli *geli; 
    struct citp_msex_gvsr *gvsr; 
    //struct citp_msex_1_0_sinf *sinf; 

    /* PARSE COMMAND LINE ARGUMENTS */
    if ((argc < 3) || (argc > 3)) 
    {
       fprintf(stderr, "Usage: %s <IP> <Port>\n", argv[0]);
       exit(EXIT_FAILURE);
    }
    mserver_ip_quad = argv[1];
    mserver_port    = atoi(argv[2]);  

    /* === SETUP UDP CONNECTION === */
    setup_udp(); 

    /* === SETUP BEACON BEHAVIOR === */
    g_ploc = citp_create_pinf_ploc(0, (ucs1 *)"LightingConsole", (ucs1 *)"LIBCITP test lightingconsole" , (ucs1 *)"Alive");


    /* === SETUP THE TCP CONNECTION === */
        /* create socket */
    if ((tcpsock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        die("socket() failed");

        /* prepare the server address info */
    memset(&mserver_addr, 0, sizeof(mserver_addr));
    mserver_addr.sin_family      = AF_INET;
    mserver_addr.sin_addr.s_addr = inet_addr(mserver_ip_quad);
    mserver_addr.sin_port        = htons(mserver_port);

        /* connect to server */
    if (connect(tcpsock, (struct sockaddr *) &mserver_addr, sizeof(mserver_addr)) < 0)
        die("connect() failed");

    if (fcntl(tcpsock, F_SETFL, O_NONBLOCK) < 0)
        die("fcntl on tcpsock failed");

    /* === SEND PINF/PNAM MESSAGE TO SERVER === */
    pnam = citp_create_pinf_pnam((ucs1 *)"LIBCITP test lightingconsole");
    tcp_send_message(tcpsock, sendbuf, pnam);

    /* === SEND MSEX/CINF MESSAGE === */
    cinf = citp_create_msex_cinf(3, supported_msex_versions);
    tcp_send_message(tcpsock, sendbuf, cinf);

    /* === SEND MSEX/GELI MESSAGE(s) (initiate element library update) === */
    geli = citp_create_msex_1_1_geli(MSEX_ELEMENT_TYPE_MEDIA, &libid, 0, libnums);
printf("geli = %p\n", geli); 
    tcp_send_message(tcpsock, sendbuf, geli);

    /* === SEND MSEX/GVSR MESSAGE === */
    gvsr = citp_create_msex_gvsr();
printf("gvsr = %p (after return)\n", gvsr);
    tcp_send_message(tcpsock, sendbuf, gvsr);
printf("Sent gvsr\n");

    maxfd = (g_udpsock > tcpsock ? g_udpsock : tcpsock) + 1;

    while (1) {
#ifdef DEBUG
printf("DEBUG: Resetting fd set.\n");
#endif
        FD_ZERO(&rfds); 
        FD_SET(g_udpsock, &rfds);
        FD_SET(tcpsock, &rfds); 

        /* resetting timeout not strictly necessary, but prescribed. */        
        timeout.tv_sec = 0; 
        timeout.tv_usec = 500000; 

        status = select(maxfd, &rfds, (fd_set *)NULL, (fd_set *)NULL, &timeout); 
        if (0 == status) { 
            /* Timeout */
            beacon(); 
        } else if (status < 0) {
            if (errno == EINTR) 
                continue; 
            else
                die("select");
        } else {
            /* Handle input on sockets */
            if (FD_ISSET(tcpsock, &rfds)) { 
                message = tcp_recv_message(tcpsock, recvbuf); 
                if (message) {
                    switch(((struct citp_header *)message)->content_type) {
                        case CITP_COOKIE_PINF: 
                            handle_pinf(message); 
                            break; 
                        case CITP_COOKIE_MSEX: 
                            handle_msex(message);
                            break;
                    }
                } else { 
                    handle_unknown(); 
                }
            }
            if (FD_ISSET(g_udpsock, &rfds)) { 
                message = udp_recv_message(); 
                if (message) {
                    switch(((struct citp_header *)message)->content_type) {
                        case CITP_COOKIE_PINF: 
                            handle_pinf(message); 
                            break; 
                        case CITP_COOKIE_MSEX: 
                            handle_msex(message);
                            break;
                    }
                } else { 
                    handle_unknown(); 
                }
            }
        }

    }

    /* === FINISH UP === */
    citp_delete_message(pnam);  
    citp_delete_message(cinf);  
    citp_delete_message(geli);  
    citp_delete_message(gvsr);  
    citp_delete_message(g_ploc); 

    close(tcpsock);
    shutdown(g_udpsock, SHUT_RDWR);
    close(g_udpsock);

    exit(0);
}
