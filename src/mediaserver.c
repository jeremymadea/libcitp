/*
 * mediaserver.c
 *
 * Jeremy Madea <jeremymadea@gmail.com>
 *
 * Behavior regarding CITP as specified in CITP Specification: 
 *
 * TCP listening socket on any (known) port:
 * - Accept incoming connections from any lighting console or visualizer. If the media server can only handle a
 *   limited number of simultaneous connections then it should actively refuse any further connection attempts.
 * Datagram (UDP) socket, port 4809, joined to multicast address 224.0.0.180:
 *   - Regularly send a CITP/PINF/PLoc message containing the port on which the listening socket is listening.
 * For all accepted incoming TCP connections from a lighting console or visualizer:
 *   - Send CITP/PINF/PNam message immediately after connecting.
 *   - Send a CITP/MSEX/SInf Server Information message (MSEX 1.0 or MSEX 1.1).
 *   - Receive CITP/MSEX/CInf Client Information message from lighting console and respond with a
 *   CITP/MSEX/SInf Server Information message (MSEX 1.2 or later).
 *   - Regularly send a CITP/MSEX/LSta Layer Status message.
 *   - Receive and respond to CITP/MSEX element library browsing messages.
 *   - Send CITP/MSEX element library information messages on library changes.
 *   - Receive and respond to CITP/MSEX video stream browsing and subscription messages.
 *
 *  PC based applications must choose listening ports and set socket address reusability 
 *  flags as necessary to avoid blocking eachother when run on the same network interface. 
 *  Achieve this by calling listen() for port 0 and retrieving the port chosen by the 
 *  operating system with getsockname(), and by setting the SO_REUSEADDR (and possibly 
 *  also SO_REUSEPORT) option on the multicast socket before joining the multicast address.
 *  To join a multicast address, use setsockopt() with IPPROTO_IP and IP_ADD_MEMBERSHIP.
 *
 */
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include "citptypes.h"
#include "citp.h" 

#define MAXBUFSZ 65536

int main(int argc, char **argv) 
{
    int i;
    int sockfd; 
    int status; 
    int bufsz; 
    char buffer[MAXBUFSZ]; 
    struct sockaddr_in  saddr; 
    struct in_addr      iaddr;

    /* Initialize for safety. */
    memset(&saddr, 0, sizeof(struct sockaddr_in));
    memset(&iaddr, 0, sizeof(struct in_addr));

    sockfd = socket(AF_INET, SOCK_DGRAM, 0); 
    if (sockfd < 0) {
        perror("Error creating socket"); 
        exit(EXIT_FAILURE);
    }

    saddr.sin_family      = AF_INET; 
    saddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    saddr.sin_port        = htons(CITP_PINF_MULTICAST_PORT);

    status = bind(sockfd, (struct sockaddr *)&saddr, sizeof(struct sockaddr_in));
    if (status < 0) { 
        perror("Error binding to socket"); 
        exit(EXIT_FAILURE);
    }

    iaddr.s_addr = INADDR_ANY; 
    status = setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_IF, &iaddr, sizeof(struct in_addr));
    if (status < 0) { 
        perror("Error setting sockopt"); 
        exit(EXIT_FAILURE);
    }

    /* Other defaults should be fine. 
     * IP_MULTICAST_LOOP default is 1 (enabled)
     * IP_MULTICAST_TTL  default is 1 (local subnet) 
     *
     * TTL should be configurable in a real tool. 
     */

    saddr.sin_family      = PF_INET;
    saddr.sin_addr.s_addr = inet_addr(CITP_PINF_MULTICAST_IP);
    saddr.sin_port        = htons(CITP_PINF_MULTICAST_PORT);



    bufsz = citp_make_pinf_ploc((void *)buffer, 1234, (ucs1 *)"MediaServer", (ucs1 *)"ControlFreakMediaServer", (ucs1 *)"Idle"); 

    // strcpy(buffer, "This is a test."); 

    for (i=0; i<60; i++) {
        status = sendto(sockfd, buffer, bufsz, 0,
                       (struct sockaddr *)&saddr, sizeof(struct sockaddr_in));
        if (status < 0) { 
            perror("Error writing to socket");
            exit(EXIT_FAILURE);
        }
        sleep(1);
    }

    shutdown(sockfd, SHUT_RDWR); 
    close(sockfd);

    exit(EXIT_SUCCESS); 
}
