/* 
 * parse.h - Interface for parsing raw CITP messages. 
 * Jeremy Madea <jeremymadea@gmail.com>
 *
 */
#ifndef _CITP_PARSE_H_
#define _CITP_PARSE_H_

/* Forward declarations of parsing routines. */
void *citp_parse_message(void *buf);
/*
void *citp_parse_pinf(void *buf); 
void *citp_parse_sdmx(void *buf); 
void *citp_parse_msex(void *buf);
struct citp_pinf_pnam *parse_pinf_pnam(void *buf);
struct citp_pinf_ploc *parse_pinf_ploc(void *buf);
struct citp_sdmx_enid *parse_sdmx_enid(void *buf);
struct citp_sdmx_unam *parse_sdmx_unam(void *buf);
struct citp_sdmx_chbk *parse_sdmx_chbk(void *buf);
struct citp_sdmx_sxsr *parse_sdmx_sxsr(void *buf);
struct citp_msex_cinf *parse_msex_cinf(void *buf);
struct citp_msex_1_0_sinf *parse_msex_1_0_sinf(void *buf); 
struct citp_msex_1_2_sinf *parse_msex_1_2_sinf(void *buf); 
struct citp_msex_1_0_lsta *parse_msex_1_0_lsta(void *buf); 
struct citp_msex_1_2_lsta *parse_msex_1_2_lsta(void *buf); 
struct citp_msex_lsta *parse_msex_lsta(void *buf);
struct citp_msex_nack *parse_msex_nack(void *buf);
struct citp_msex_gvsr *parse_msex_gvsr(void *buf);
struct citp_msex_1_0_geli *parse_msex_1_0_geli(void *buf); 
struct citp_msex_1_1_geli *parse_msex_1_1_geli(void *buf); 
struct citp_msex_1_2_geli *parse_msex_1_2_geli(void *buf); 
struct citp_msex_1_0_elin *parse_msex_1_0_elin(void *buf); 
struct citp_msex_1_1_elin *parse_msex_1_1_elin(void *buf); 
struct citp_msex_1_2_elin *parse_msex_1_2_elin(void *buf); 
struct citp_msex_1_0_gein *parse_msex_1_0_gein(void *buf); 
struct citp_msex_1_1_gein *parse_msex_1_1_gein(void *buf); 
struct citp_msex_1_2_gein *parse_msex_1_2_gein(void *buf); 
struct citp_msex_1_0_mein *parse_msex_1_0_mein(void *buf); 
struct citp_msex_1_1_mein *parse_msex_1_1_mein(void *buf); 
struct citp_msex_1_2_mein *parse_msex_1_2_mein(void *buf); 
struct citp_msex_1_0_geth *parse_msex_1_0_geth(void *buf); 
struct citp_msex_1_1_geth *parse_msex_1_1_geth(void *buf); 
struct citp_msex_1_2_geth *parse_msex_1_2_geth(void *buf); 
struct citp_msex_1_0_ethn *parse_msex_1_0_ethn(void *buf); 
struct citp_msex_1_1_ethn *parse_msex_1_1_ethn(void *buf); 
*/
#endif /* _CITP_PARSE_H_ */
