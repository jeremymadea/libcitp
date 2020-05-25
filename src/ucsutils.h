/*
 * ucsutils.h - Interface for utilities used to manipulate ucs1 and ucs2 strings. 
 *
 * Jeremy Madea <jeremymadea@gmail.com>
 *
 */
#ifndef _CITP_UCSUTILS_H_
#define _CITP_UCSUTILS_H_

#include <sys/types.h>

size_t ucs2strlen(const ucs2 *s);
ucs1* ucs1cpy(ucs1 *dst, ucs1 *src);
ucs2* ucs2cpy(ucs2 *dst, ucs2 *src);
ucs2* ucs2pcpy(ucs2 *dst, ucs2 *src);
ucs1 *copy_ucs1_str(void *p); 
void *ucs1str_newcopy(ucs1 **dst, ucs1 *src); 
void *ucs2str_newcopy(ucs2 **dst, ucs2 *src); 

#endif /* _CITP_UCSUTILS_H_ */
