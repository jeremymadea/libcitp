/*
 * citp.h - The libcitp interface.
 *
 * Jeremy Madea <jeremymadea@gmail.com>
 *
 */
#ifndef _CITP_H_
#define _CITP_H_

#include "citptypes.h"

/* Safe raw message building function (see build.c) */
int citp_build_message(void *msg, size_t max_message_size, const void *p);

/* Message parsing function (see parse.c) */
void *citp_parse_message(void *buf);

/* Message creation functions (see create.c) */
struct citp_pinf_pnam *citp_create_pinf_pnam(ucs1 *name);
struct citp_pinf_ploc *citp_create_pinf_ploc(uint16 port, ucs1 *type, ucs1* name, ucs1 *state);
struct citp_msex_cinf *citp_create_msex_cinf(uint8 count, const uint16 *versions);
struct citp_msex_gvsr *citp_create_msex_gvsr();
struct citp_msex_1_1_geli *citp_create_msex_1_1_geli(uint8 type, const struct msex_library_id *id, uint8 count, const uint8 *numbers);
struct citp_msex_1_2_geli *citp_create_msex_1_2_geli(uint8 type, const struct msex_library_id *id, uint16 count, const uint8 *numbers);
/* Message deletion - for freeing memory allocated for messages. (see delete.c) */
void citp_delete_message(void *msg);


/* old pinf ploc maker. */
uint32 citp_make_pinf_ploc(void *buf, uint16 port, ucs1 *type, ucs1 *name, ucs1 *state); 
/*
uint32 citp_make_pinf_pname(); 
uint32 citp_make_sdmx_enid(); 
uint32 citp_make_sdmx_unam(); 
uint32 citp_make_sdmx_chbk();
uint32 citp_make_sdmx_sxsr(); 
uint32 citp_make_msex_cinf(); 
uint32 citp_make_msex_sinf(); 
uint32 citp_make_msex_lsta(); 
uint32 citp_make_msex_nack();
uint32 citp_make_msex_gvsr(); 
uint32 citp_make_msex_geli(); 
uint32 citp_make_msex_elin(); 
uint32 citp_make_msex_gein(); 
uint32 citp_make_msex_mein(); 
uint32 citp_make_msex_geth(); 
uint32 citp_make_msex_ethn(); 
*/

#endif /* _CITP_H_ */
