/*
 * ucsutils.h - Implementation of utilities used to manipulate ucs1 and ucs2 strings. 
 *
 * Jeremy Madea <jeremymadea@gmail.com>
 *
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include "citptypes.h"

size_t ucs2strlen(const ucs2 *s) 
{
    register size_t len = 0; 
    while (*s != 0) len++, s++; 
    return len;
} 

/* copies src to dst including the trailing ucs1 null ('\0') and returns a pointer 
 * to src's trailing null. This is designed to be used for copying multiple null-terminated 
 * strings from a byte array. Compare and contrast with strpcpy() which is designed for 
 * writing multiple null-terminated strings to a byte array.
 */
ucs1 *ucs1cpy(ucs1 *dst, ucs1 *src)
{
    while ((*dst = *src) != 0) dst++, src++;
    return src;
}

/* copies src to dst including the trailing ucs2 null ("\0\0") and returns a pointer 
 * to src's trailing null. This is designed to be used for copying multiple null-terminated 
 * strings from a byte array. Compare and contrast with strpcpy() which is designed for 
 * writing multiple null-terminated strings to a byte array.
 */
ucs2 *ucs2cpy(ucs2 *dst, ucs2 *src)
{
    while ((*dst = *src) != 0) dst++, src++;
    return src;
}

/* copies src to dst including the trailing ucs2 null ("\0\0") and returns a pointer 
 * to dst's trailing null. This is a ucs2 version of stpcpy. 
 */
ucs2 *ucs2pcpy(ucs2 *dst, ucs2 *src) 
{
    while ((*dst = *src) != 0) dst++, src++;
    return dst;
}


/* Utilities for allocating strings and copying contents from byte arrays. */

ucs1 *copy_ucs1_str(void *p) 
{
    size_t z; 
    ucs1 *s;
    z = strlen(p) + 1; 
    s = malloc(z); 
    if (!s) {
        perror("Could not allocate string");
        exit(EXIT_FAILURE); /* XXX  Should avoid exiting but simple for now. */
    }
    strcpy((char *)s, (char *)p); 
    return s;
}

/*
 * Allocates storage for a new copy of the source string. Destination is 
 * assigned a pointer to this space. The string is copied from src to the
 * newly allocated space. A pointer to src's trailing null '\0' is returned. 
 * 
 */
void *ucs1str_newcopy(ucs1 **dst, ucs1 *src) 
{
    size_t z; 
    z = strlen((char *)src) + 1;
    *dst = malloc(z); 
    if (!*dst) { 
        perror("Could not allocate memory for ucs2 string");
        exit(EXIT_FAILURE); /* XXX  Should avoid exiting but simple for now. */
    }
    return ucs1cpy(*dst, src); 
}

/*
 * Allocates storage for a new copy of the source string. Destination is 
 * assigned a pointer to this space. The string is copied from src to the
 * newly allocated space. A pointer to src's trailing ucs2 null "\0\0" 
 * is returned. 
 * 
 */
void *ucs2str_newcopy(ucs2 **dst, ucs2 *src) 
{
    size_t z; 
    z = (ucs2strlen(src) + 1) * sizeof(ucs2); 
    *dst = malloc(z); 
    if (!*dst) { 
        perror("Could not allocate memory for ucs2 string");
        exit(EXIT_FAILURE); /* XXX  Should avoid exiting but simple for now. */
    }
    return ucs2cpy(*dst, src); 
}

