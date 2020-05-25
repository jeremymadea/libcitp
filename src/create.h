/* 
 * create.h - Interface for creating new CITP messages. 
 * Jeremy Madea <jeremymadea@gmail.com>
 *
 */
#ifndef _CITP_CREATE_H_
#define _CITP_CREATE_H_

struct citp_pinf_pnam *citp_create_pinf_pnam(ucs1 *name);
struct citp_pinf_ploc *citp_create_pinf_ploc(uint16 port, ucs1 *type, ucs1* name, ucs1 *state);
struct citp_msex_cinf *citp_create_msex_cinf(uint8 count, const uint16 *versions);
/*
struct citp_sdmx_enid *create_sdmx_enid(void *buf);
struct citp_sdmx_unam *create_sdmx_unam(void *buf);
struct citp_sdmx_chbk *create_sdmx_chbk(void *buf);
struct citp_sdmx_sxsr *create_sdmx_sxsr(void *buf);
struct citp_msex_cinf *create_msex_cinf(void *buf);
struct citp_msex_1_0_sinf *create_msex_1_0_sinf(void *buf); 
struct citp_msex_1_2_sinf *create_msex_1_2_sinf(void *buf); 
struct citp_msex_1_0_lsta *create_msex_1_0_lsta(void *buf); 
struct citp_msex_1_2_lsta *create_msex_1_2_lsta(void *buf); 
struct citp_msex_lsta *create_msex_lsta(void *buf);
struct citp_msex_nack *create_msex_nack(void *buf);
struct citp_msex_gvsr *create_msex_gvsr(void *buf);
struct citp_msex_1_0_geli *create_msex_1_0_geli(void *buf); 
struct citp_msex_1_1_geli *create_msex_1_1_geli(void *buf); 
struct citp_msex_1_2_geli *create_msex_1_2_geli(void *buf); 
struct citp_msex_1_0_elin *create_msex_1_0_elin(void *buf); 
struct citp_msex_1_1_elin *create_msex_1_1_elin(void *buf); 
struct citp_msex_1_2_elin *create_msex_1_2_elin(void *buf); 
struct citp_msex_1_0_gein *create_msex_1_0_gein(void *buf); 
struct citp_msex_1_1_gein *create_msex_1_1_gein(void *buf); 
struct citp_msex_1_2_gein *create_msex_1_2_gein(void *buf); 
struct citp_msex_1_0_mein *create_msex_1_0_mein(void *buf); 
struct citp_msex_1_1_mein *create_msex_1_1_mein(void *buf); 
struct citp_msex_1_2_mein *create_msex_1_2_mein(void *buf); 
struct citp_msex_1_0_geth *create_msex_1_0_geth(void *buf); 
struct citp_msex_1_1_geth *create_msex_1_1_geth(void *buf); 
struct citp_msex_1_2_geth *create_msex_1_2_geth(void *buf); 
struct citp_msex_1_0_ethn *create_msex_1_0_ethn(void *buf); 
struct citp_msex_1_1_ethn *create_msex_1_1_ethn(void *buf); 
*/

#endif /* _CITP_CREATE_H_ */
