/*
 * build.c - Implementation of safe raw message building function.
 *
 * Jeremy Madea <jeremymadea@gmail.com>
 *
 */
#include "citptypes.h"
#include "messages.h" 

int citp_build_message(void *msg, uint32 max_message_size, const void *p)
{
    uint16 mver; 

    if (((struct citp_header *)p)->message_size > max_message_size)
        return CITP_EBIGMSG; 

    switch (((struct citp_header *)p)->content_type) { 
        case CITP_COOKIE_PINF:
            switch(((struct citp_pinf_header *)p)->content_type) { 
                case CITP_COOKIE_PINF_PNAM:
                    citp_build_pinf_pnam_msg(msg, (struct citp_pinf_pnam *)p); 
                    break;
                case CITP_COOKIE_PINF_PLOC:
                    citp_build_pinf_ploc_msg(msg, (struct citp_pinf_ploc *)p); 
                    break;
                default: /* UNKNOWN */
                    return CITP_EUNKNOWN; 
            } 
        break; 
        case CITP_COOKIE_SDMX:
            switch(((struct citp_sdmx_header *)p)->content_type) { 
                case CITP_COOKIE_SDMX_ENID:
                    citp_build_sdmx_enid_msg(msg, (struct citp_sdmx_enid *)p); 
                    break;
                case CITP_COOKIE_SDMX_UNAM:
                    citp_build_sdmx_unam_msg(msg, (struct citp_sdmx_unam *)p); 
                    break;
                case CITP_COOKIE_SDMX_CHBK:
                    citp_build_sdmx_chbk_msg(msg, (struct citp_sdmx_chbk *)p); 
                    break;
                case CITP_COOKIE_SDMX_SXSR:
                    citp_build_sdmx_sxsr_msg(msg, (struct citp_sdmx_sxsr *)p); 
                    break;
                default: /* UNKNOWN */
                    return CITP_EUNKNOWN; 
            } 
        break; 
        case CITP_COOKIE_MSEX: 
            mver = ((struct citp_msex_header *)p)->version_minor; 
            switch(((struct citp_msex_header *)p)->content_type) { 
                case CITP_COOKIE_MSEX_CINF:
                    citp_build_msex_cinf_msg(msg, (struct citp_msex_cinf *)p); 
                    break;
                case CITP_COOKIE_MSEX_SINF:
                    switch(mver) { 
                        case 0: 
                        case 1: citp_build_msex_1_0_sinf_msg(msg, (struct citp_msex_1_0_sinf *)p); break;
                        case 2: citp_build_msex_1_2_sinf_msg(msg, (struct citp_msex_1_2_sinf *)p); break;
                        default:
                            return CITP_EUNKNOWN; 
                    };
                    break;
                case CITP_COOKIE_MSEX_LSTA:
                    switch(mver) { 
                        case 0: 
                        case 1: citp_build_msex_1_0_lsta_msg(msg, (struct citp_msex_1_0_lsta *)p); break;
                        case 2: citp_build_msex_1_2_lsta_msg(msg, (struct citp_msex_1_2_lsta *)p); break;
                        default:
                            return CITP_EUNKNOWN; 
                    };
                    break;
                case CITP_COOKIE_MSEX_NACK:
                    citp_build_msex_nack_msg(msg, (struct citp_msex_nack *)p); 
                    break;
                case CITP_COOKIE_MSEX_GVSR:
                    citp_build_msex_gvsr_msg(msg, (struct citp_msex_gvsr *)p); 
                    break;
                case CITP_COOKIE_MSEX_VSRC:
                    citp_build_msex_vsrc_msg(msg, (struct citp_msex_vsrc *)p); 
                    break;
                case CITP_COOKIE_MSEX_GELI:
                    switch(mver) { 
                        case 0: citp_build_msex_1_0_geli_msg(msg, (struct citp_msex_1_0_geli *)p); break;
                        case 1: citp_build_msex_1_1_geli_msg(msg, (struct citp_msex_1_1_geli *)p); break;
                        case 2: citp_build_msex_1_2_geli_msg(msg, (struct citp_msex_1_2_geli *)p); break;
                        default:
                            return CITP_EUNKNOWN; 
                    };
                    break;
                case CITP_COOKIE_MSEX_ELIN:
                    switch(mver) { 
                        case 0: citp_build_msex_1_0_elin_msg(msg, (struct citp_msex_1_0_elin *)p); break;
                        case 1: citp_build_msex_1_1_elin_msg(msg, (struct citp_msex_1_1_elin *)p); break;
                        case 2: citp_build_msex_1_2_elin_msg(msg, (struct citp_msex_1_2_elin *)p); break;
                        default:
                            return CITP_EUNKNOWN; 
                    };
                    break;
                case CITP_COOKIE_MSEX_GEIN:
                    switch(mver) { 
                        case 0: citp_build_msex_1_0_gein_msg(msg, (struct citp_msex_1_0_gein *)p); break;
                        case 1: citp_build_msex_1_1_gein_msg(msg, (struct citp_msex_1_1_gein *)p); break;
                        case 2: citp_build_msex_1_2_gein_msg(msg, (struct citp_msex_1_2_gein *)p); break;
                        default:
                            return CITP_EUNKNOWN; 
                    };
                    break;
                case CITP_COOKIE_MSEX_MEIN:
                    switch(mver) { 
                        case 0: citp_build_msex_1_0_mein_msg(msg, (struct citp_msex_1_0_mein *)p); break;
                        case 1: citp_build_msex_1_1_mein_msg(msg, (struct citp_msex_1_1_mein *)p); break;
                        case 2: citp_build_msex_1_2_mein_msg(msg, (struct citp_msex_1_2_mein *)p); break;
                        default:
                            return CITP_EUNKNOWN; 
                    };
                    break;

                case CITP_COOKIE_MSEX_GELT:
                    switch(mver) { 
                        case 0: citp_build_msex_1_0_gelt_msg(msg, (struct citp_msex_1_0_gelt *)p); break;
                        case 1: citp_build_msex_1_1_gelt_msg(msg, (struct citp_msex_1_1_gelt *)p); break;
                        case 2: citp_build_msex_1_2_gelt_msg(msg, (struct citp_msex_1_2_gelt *)p); break;
                        default:
                            return CITP_EUNKNOWN; 
                    };
                    break;
                case CITP_COOKIE_MSEX_ELTH:
                    switch(mver) { 
                        case 0: citp_build_msex_1_0_elth_msg(msg, (struct citp_msex_1_0_elth *)p); break;
                        case 1:
                        case 2: citp_build_msex_1_1_elth_msg(msg, (struct citp_msex_1_1_elth *)p); break;
                        default:
                            return CITP_EUNKNOWN; 
                    };
                    break;

                case CITP_COOKIE_MSEX_GETH:
                    switch(mver) { 
                        case 0: citp_build_msex_1_0_geth_msg(msg, (struct citp_msex_1_0_geth *)p); break;
                        case 1: citp_build_msex_1_1_geth_msg(msg, (struct citp_msex_1_1_geth *)p); break;
                        case 2: citp_build_msex_1_2_geth_msg(msg, (struct citp_msex_1_2_geth *)p); break;
                        default:
                            return CITP_EUNKNOWN; 
                    };
                    break;
                case CITP_COOKIE_MSEX_ETHN:
                    switch(mver) { 
                        case 0: citp_build_msex_1_0_ethn_msg(msg, (struct citp_msex_1_0_ethn *)p); break;
                        case 1:
                        case 2: citp_build_msex_1_1_ethn_msg(msg, (struct citp_msex_1_1_ethn *)p); break;
                        default:
                            return CITP_EUNKNOWN; 
                    };
                    break;
                case CITP_COOKIE_MSEX_RQST:
                    citp_build_msex_rqst_msg(msg, (struct citp_msex_rqst *)p); 
                    break;
                case CITP_COOKIE_MSEX_STFR:
                    switch(mver) { 
                        case 0: 
                        case 1: citp_build_msex_1_0_stfr_msg(msg, (struct citp_msex_1_0_stfr *)p); break;
                        case 2: citp_build_msex_1_2_stfr_msg(msg, (struct citp_msex_1_2_stfr *)p); break;
                        default:
                            return CITP_EUNKNOWN; 
                    };
                    break;
                default: /* UNKNOWN */
                    return CITP_EUNKNOWN; 
            }
        break; 
        default: /* UNKNOWN */
            return CITP_EUNKNOWN; 
    }
    return 0; 
}

