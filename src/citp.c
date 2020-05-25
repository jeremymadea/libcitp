/*
 * citp.c
 *
 * Jeremy Madea <jeremymadea@gmail.com>
 *
 */

#include <string.h>
#include <strings.h>
#include "citptypes.h"
#include "citp.h"

#define CITP_PLOC_HDR_SZ 6

uint32 citp_add_header(void *buf, uint16 reqnum, uint16 part_count, uint16 part, uint32 cookie) {
    *(uint32 *)buf        = (uint32)CITP_COOKIE_CITP;
    *(uint8 *)(buf + 4)   = (uint8)CITP_MAJOR_VERSION;
    *(uint8 *)(buf + 5)   = (uint8)CITP_MINOR_VERSION;
    *(uint16 *)(buf + 6)  = reqnum; 
    *(uint32 *)(buf + 8)  = (uint32)CITP_HEADER_SIZE; 
    *(uint16 *)(buf + 12) = (uint16)part_count; 
    *(uint16 *)(buf + 14) = (uint16)part; 
    *(uint32 *)(buf + 16) = cookie;
    return (uint32)CITP_HEADER_SIZE;
}

uint32 citp_set_size(void *buf, uint32 size) { 
    *(uint32 *)(buf + 8) = size; 
    return size; 
}

uint32 citp_add_size(void *buf, uint32 size) { 
    *(uint32 *)(buf + 8) += size; 
    return *(uint32 *)(buf + 8); 
}

uint32 citp_make_pinf_ploc(void *buf, uint16 port, ucs1 *type, ucs1*name, ucs1 *state) {
    int size; 
    char *s; 

    (void)citp_add_header(buf, 0, 1, 0, CITP_COOKIE_PINF);

    size  = CITP_PLOC_HDR_SZ 
          + strlen((const char *)type) + 1 
          + strlen((const char *)name) + 1 
          + strlen((const char *)state) + 1;

    *(uint32 *)(buf + 20) = (uint32)CITP_COOKIE_PINF_PLOC;
    *(uint16 *)(buf + 24) = (uint16)port; 

    s = stpcpy((char *)(buf + 26), (char *)type); 
    s = stpcpy((char *)(s + 1), (char *)name); 
    s = stpcpy((char *)(s + 1), (char *)state); 

    return citp_add_size(buf, (uint32)size); 
}


