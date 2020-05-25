/*
 * messages.h - functions for constructing raw CITP messages from structures. 
 *
 * Jeremy Madea <jeremymadea@gmail.com>
 *
 */
#ifndef _CITP_MESSAGES_H_
#define _CITP_MESSAGES_H_

#include "citptypes.h"

/***************************************************************************
 *************************************************************************** 
 *****                                                                 *****
 *****               WARNING WARNING WARNGING WARNING                  ***** 
 *****                                                                 *****
 *****      The following citp_build_* functions are DANGEROUS!        *****
 *****  Their 'msg' argument is assumed to point to sufficient space   *****
 *****  and data is written to that space without any sanity checks.   *****
 *****                                                                 *****
 *************************************************************************** 
 ***************************************************************************/

void citp_build_pinf_pnam_msg(void *msg, const struct citp_pinf_pnam *p);
void citp_build_pinf_ploc_msg(void *msg, const struct citp_pinf_ploc *p);
void citp_build_sdmx_enid_msg(void *msg, const struct citp_sdmx_enid *p);
void citp_build_sdmx_unam_msg(void *msg, const struct citp_sdmx_unam *p);
void citp_build_sdmx_chbk_msg(void *msg, const struct citp_sdmx_chbk *p);
void citp_build_sdmx_sxsr_msg(void *msg, const struct citp_sdmx_sxsr *p);
void citp_build_msex_cinf_msg(void *msg, const struct citp_msex_cinf *p);
void citp_build_msex_1_0_sinf_msg(void *msg, const struct citp_msex_1_0_sinf *p);
void citp_build_msex_1_2_sinf_msg(void *msg, const struct citp_msex_1_2_sinf *p);
void citp_build_msex_1_0_lsta_msg(void *msg, const struct citp_msex_1_0_lsta *p);
void citp_build_msex_1_2_lsta_msg(void *msg, const struct citp_msex_1_2_lsta *p);
void citp_build_msex_nack_msg(void *msg, const struct citp_msex_nack *p);
void citp_build_msex_gvsr_msg(void *msg, const struct citp_msex_gvsr *p);
void citp_build_msex_vsrc_msg(void *msg, const struct citp_msex_vsrc *p);
void citp_build_msex_1_0_geli_msg(void *msg, const struct citp_msex_1_0_geli *p);
void citp_build_msex_1_1_geli_msg(void *msg, const struct citp_msex_1_1_geli *p);
void citp_build_msex_1_2_geli_msg(void *msg, const struct citp_msex_1_2_geli *p);
void citp_build_msex_1_0_elin_msg(void *msg, const struct citp_msex_1_0_elin *p);
void citp_build_msex_1_1_elin_msg(void *msg, const struct citp_msex_1_1_elin *p);
void citp_build_msex_1_2_elin_msg(void *msg, const struct citp_msex_1_2_elin *p);
void citp_build_msex_1_0_gein_msg(void *msg, const struct citp_msex_1_0_gein *p);
void citp_build_msex_1_1_gein_msg(void *msg, const struct citp_msex_1_1_gein *p);
void citp_build_msex_1_2_gein_msg(void *msg, const struct citp_msex_1_2_gein *p);
void citp_build_msex_1_0_mein_msg(void *msg, const struct citp_msex_1_0_mein *p);
void citp_build_msex_1_1_mein_msg(void *msg, const struct citp_msex_1_1_mein *p);
void citp_build_msex_1_2_mein_msg(void *msg, const struct citp_msex_1_2_mein *p);
void citp_build_msex_1_0_gelt_msg(void *msg, const struct citp_msex_1_0_gelt *p);
void citp_build_msex_1_1_gelt_msg(void *msg, const struct citp_msex_1_1_gelt *p);
void citp_build_msex_1_2_gelt_msg(void *msg, const struct citp_msex_1_2_gelt *p);
void citp_build_msex_1_0_elth_msg(void *msg, const struct citp_msex_1_0_elth *p);
void citp_build_msex_1_1_elth_msg(void *msg, const struct citp_msex_1_1_elth *p);
void citp_build_msex_1_0_geth_msg(void *msg, const struct citp_msex_1_0_geth *p);
void citp_build_msex_1_1_geth_msg(void *msg, const struct citp_msex_1_1_geth *p);
void citp_build_msex_1_2_geth_msg(void *msg, const struct citp_msex_1_2_geth *p);
void citp_build_msex_1_0_ethn_msg(void *msg, const struct citp_msex_1_0_ethn *p);
void citp_build_msex_1_1_ethn_msg(void *msg, const struct citp_msex_1_1_ethn *p);
void citp_build_msex_rqst_msg(void *msg, const struct citp_msex_rqst *p);
void citp_build_msex_1_0_stfr_msg(void *msg, const struct citp_msex_1_0_stfr *p);
void citp_build_msex_1_2_stfr_msg(void *msg, const struct citp_msex_1_2_stfr *p);

#endif /* _CITP_MESSAGES_H_ */
