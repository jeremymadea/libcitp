/* 
 * delete.c - Functions for deleting CITP message structures. 
 * Jeremy Madea <jeremymadea@gmail.com>
 *
 */
#include <stdlib.h>
#include "citptypes.h"

/* Forward declarations of deletion routines for message structures. */
void citp_delete_message(void *msg);
void citp_delete_pinf(void *msg); 
void citp_delete_sdmx(void *msg); 
void citp_delete_msex(void *msg);

/* Forwards declarations of deletion routines for auxillary structures. */
void citp_delete_msex_layer_information(uint8 cnt, struct msex_layer_info *info);
void citp_delete_msex_1_0_layer_status(uint8 cnt, struct msex_1_0_layer_status *status); 
void citp_delete_msex_1_2_layer_status(uint8 cnt, struct msex_1_2_layer_status *status); 
void citp_delete_msex_1_0_element_library_info(uint8 cnt, struct msex_1_0_element_library_info *info); 
void citp_delete_msex_1_1_element_library_info(uint8 cnt, struct msex_1_1_element_library_info *info); 
void citp_delete_msex_1_2_element_library_info(uint16 cnt, struct msex_1_2_element_library_info *info); 
void citp_delete_msex_1_0_media_info(uint8 cnt, struct msex_1_0_media_info *info); 
void citp_delete_msex_1_2_media_info(uint16 cnt, struct msex_1_2_media_info *info); 
void citp_delete_vsrc_source_information(uint16 cnt, struct vsrc_source_information *info); 

void citp_delete_message(void *msg) 
{
    uint32 layer; 

    layer = ((struct citp_header *)msg)->content_type; 
    switch (layer) {
        case CITP_COOKIE_PINF: 
            citp_delete_pinf(msg); 
            break;
        case CITP_COOKIE_SDMX: 
            citp_delete_sdmx(msg); 
            break;
        case CITP_COOKIE_MSEX:
            citp_delete_msex(msg); 
            break;
        case CITP_COOKIE_FPTC:  /* UNIMPLEMENTED */
        case CITP_COOKIE_FSEL:  /* UNIMPLEMENTED */
        case CITP_COOKIE_FINF:  /* UNIMPLEMENTED */
        default:                /* UNKNOWN */
        break;
    }
    return;
}

void citp_delete_pinf(void *msg) 
{ 
    uint32 type; 
    type = ((struct citp_pinf_header *)msg)->content_type;
    switch(type) {
        case CITP_COOKIE_PINF_PNAM:
            free(((struct citp_pinf_pnam *)msg)->name); 
            break;
        case CITP_COOKIE_PINF_PLOC:
            free(((struct citp_pinf_ploc *)msg)->type);
            free(((struct citp_pinf_ploc *)msg)->name);
            free(((struct citp_pinf_ploc *)msg)->state);
            break;
        default:                    /* UNKNOWN */
        break;
    }
    free(msg);
    return;
}

void citp_delete_sdmx(void *msg) 
{ 
    uint32 type; 
    type = ((struct citp_sdmx_header *)msg)->content_type;
    switch(type) {
        case CITP_COOKIE_SDMX_ENID:
            free(((struct citp_sdmx_enid *)msg)->identifier); 
            break;
        case CITP_COOKIE_SDMX_UNAM:
            free(((struct citp_sdmx_unam *)msg)->universe_name); 
            break;
        case CITP_COOKIE_SDMX_CHBK:
            free(((struct citp_sdmx_chbk *)msg)->channel_levels); 
            break;
        case CITP_COOKIE_SDMX_SXSR:
            free(((struct citp_sdmx_sxsr *)msg)->connection_string); 
            break;
        default:                    /* UNKNOWN */
        break;
    }
    free(msg);
    return;
}

void citp_delete_msex(void *msg) 
{ 
    uint32 type; 
    uint8 mver; 

    type = ((struct citp_msex_header *)msg)->content_type;
    mver = ((struct citp_msex_header *)msg)->version_minor;
        
    switch(type) {
        case CITP_COOKIE_MSEX_CINF:
            free(((struct citp_msex_cinf *)msg)->supported_msex_versions); 
            free(((struct citp_msex_cinf *)msg)->future_message_data);   /* Should be NULL */
            break;
        case CITP_COOKIE_MSEX_SINF:
            switch(mver) { 
                case 0: 
                case 1: 
                    free(((struct citp_msex_1_0_sinf *)msg)->product_name);
                    citp_delete_msex_layer_information( 
                        ((struct citp_msex_1_0_sinf *)msg)->layer_count, 
                        ((struct citp_msex_1_0_sinf *)msg)->layer_information); 
                    break;
                case 2: 
                    free(((struct citp_msex_1_2_sinf *)msg)->product_name);
                    free(((struct citp_msex_1_2_sinf *)msg)->supported_msex_versions);
                    free(((struct citp_msex_1_2_sinf *)msg)->thumbnail_formats);
                    free(((struct citp_msex_1_2_sinf *)msg)->stream_formats);
                    citp_delete_msex_layer_information( 
                        ((struct citp_msex_1_2_sinf *)msg)->layer_count, 
                        ((struct citp_msex_1_2_sinf *)msg)->layer_information); 
                    break;
                default:
                    break;
            };
            break;
        case CITP_COOKIE_MSEX_LSTA:
            switch(mver) { 
                case 0: 
                case 1: citp_delete_msex_1_0_layer_status(
                        ((struct citp_msex_1_0_lsta *)msg)->layer_count, 
                        ((struct citp_msex_1_0_lsta *)msg)->layer_status); 
                    break;
                case 2: citp_delete_msex_1_2_layer_status(
                        ((struct citp_msex_1_2_lsta *)msg)->layer_count, 
                        ((struct citp_msex_1_2_lsta *)msg)->layer_status); 
                    break;
                default:
                    break;
            };
            break;
        case CITP_COOKIE_MSEX_NACK: /* nothing to do */
            break;
        case CITP_COOKIE_MSEX_GVSR: /* nothing to do */
            break;
        case CITP_COOKIE_MSEX_VSRC: 
            citp_delete_vsrc_source_information(
                ((struct citp_msex_vsrc *)msg)->source_count, 
                ((struct citp_msex_vsrc *)msg)->source_information);
            break; 
        case CITP_COOKIE_MSEX_GELI:
            switch(mver) { 
                case 0:
                    free(((struct citp_msex_1_0_geli *)msg)->library_numbers);  
                    break; 
                case 1:
                    free(((struct citp_msex_1_1_geli *)msg)->library_numbers);  
                    break; 
                case 2: 
                    free(((struct citp_msex_1_2_geli *)msg)->library_numbers);  
                    break; 
                default:
                    break;
            };
            break;
        case CITP_COOKIE_MSEX_ELIN: 
            switch(mver) { 
                case 0: citp_delete_msex_1_0_element_library_info(
                        ((struct citp_msex_1_0_elin *)msg)->library_count, 
                        ((struct citp_msex_1_0_elin *)msg)->element_library_information); 
                    break;
                case 1: citp_delete_msex_1_1_element_library_info(
                        ((struct citp_msex_1_1_elin *)msg)->library_count, 
                        ((struct citp_msex_1_1_elin *)msg)->element_library_information); 
                    break;
                case 2: citp_delete_msex_1_2_element_library_info(
                        ((struct citp_msex_1_2_elin *)msg)->library_count, 
                        ((struct citp_msex_1_2_elin *)msg)->element_library_information); 
                    break;
                default:
                    break;
            };
            break;
        case CITP_COOKIE_MSEX_GEIN:
            switch(mver) { 
                case 0:
                    free(((struct citp_msex_1_2_gein *)msg)->element_numbers);  
                    break; 
                case 1:
                    free(((struct citp_msex_1_2_gein *)msg)->element_numbers);  
                    break; 
                case 2: 
                    free(((struct citp_msex_1_2_gein *)msg)->element_numbers);  
                    break; 
                default:
                    break;
            };
            break;
        case CITP_COOKIE_MSEX_MEIN: 
            switch(mver) { 
                case 0:
                case 1: citp_delete_msex_1_0_media_info(
                        ((struct citp_msex_1_0_mein *)msg)->library_count, 
                        ((struct citp_msex_1_0_mein *)msg)->media_information); 
                    break;
                case 2: citp_delete_msex_1_2_media_info(
                        ((struct citp_msex_1_2_mein *)msg)->library_count, 
                        ((struct citp_msex_1_2_mein *)msg)->media_information); 
                    break;
                default:
                    break;
            };
            break;
        case CITP_COOKIE_MSEX_GELT:
            switch(mver) { 
                case 0:
                    free(((struct citp_msex_1_0_gelt *)msg)->library_numbers);  
                    break; 
                case 1:
                    free(((struct citp_msex_1_1_gelt *)msg)->library_ids);  
                    break; 
                case 2: 
                    free(((struct citp_msex_1_2_gelt *)msg)->library_ids);  
                    break; 
                default:
                    break;
            };
            break;
        case CITP_COOKIE_MSEX_ELTH: 
            switch(mver) { 
                case 0:
                    free(((struct citp_msex_1_0_elth *)msg)->thumbnail_buffer);  
                    break; 
                case 1:
                    free(((struct citp_msex_1_1_elth *)msg)->thumbnail_buffer);  
                    break; 
                case 2: 
                default:
                    break;
            };
            break;
        case CITP_COOKIE_MSEX_GETH:
            switch(mver) { 
                case 0:
                    free(((struct citp_msex_1_0_geth *)msg)->element_numbers);  
                    break; 
                case 1:
                    free(((struct citp_msex_1_1_geth *)msg)->element_numbers);  
                    break; 
                case 2: 
                    free(((struct citp_msex_1_2_geth *)msg)->element_numbers);  
                    break; 
                default:
                    break;
            };
            break;
        case CITP_COOKIE_MSEX_ETHN: 
            switch(mver) { 
                case 0:
                    free(((struct citp_msex_1_0_ethn *)msg)->thumbnail_buffer);  
                    break; 
                case 1:
                    free(((struct citp_msex_1_1_ethn *)msg)->thumbnail_buffer);  
                    break; 
                case 2: 
                default:
                    break;
            };
            break;
        case CITP_COOKIE_MSEX_RQST: /* nothing to do */
            break; 
        case CITP_COOKIE_MSEX_STFR: 
            switch(mver) { 
                case 0:
                case 1:
                    free(((struct citp_msex_1_0_stfr *)msg)->frame_buffer);  
                    break; 
                case 2: 
                    free(((struct citp_msex_1_2_stfr *)msg)->frame_buffer);  
                    break; 
                default:
                    break;
            };
            break;
        default:                    /* UNKNOWN */
        break;
    }
    free(msg);
}

void citp_delete_msex_layer_information(uint8 cnt, struct msex_layer_info *info)
{   
    int i; 
    for (i=0; i<cnt; i++) {
        free((info+i)->dmx_source); 
    } 
    free(info); 
    return;
}

void citp_delete_msex_1_0_layer_status(uint8 cnt, struct msex_1_0_layer_status *status)
{
    int i; 
    for (i=0; i<cnt; i++) {
        free((status+i)->media_name); 
    } 
    free(status); 
    return;
}

void citp_delete_msex_1_2_layer_status(uint8 cnt, struct msex_1_2_layer_status *status) 
{
    int i; 
    for (i=0; i<cnt; i++) {
        free((status+i)->media_name); 
    } 
    free(status); 
    return;
}
void citp_delete_msex_1_0_element_library_info(uint8 cnt, struct msex_1_0_element_library_info *info)
{
    int i; 
    for (i=0; i<cnt; i++) {
        free((info+i)->name); 
    } 
    free(info); 
    return;
}

void citp_delete_msex_1_1_element_library_info(uint8 cnt, struct msex_1_1_element_library_info *info) 
{
    int i; 
    for (i=0; i<cnt; i++) {
        free((info+i)->name); 
    } 
    free(info); 
    return;
}

void citp_delete_msex_1_2_element_library_info(uint16 cnt, struct msex_1_2_element_library_info *info) 
{
    int i; 
    for (i=0; i<cnt; i++) {
        free((info+i)->name); 
    } 
    free(info); 
    return;
}

void citp_delete_msex_1_0_media_info(uint8 cnt, struct msex_1_0_media_info *info)
{
    int i; 
    for (i=0; i<cnt; i++) {
        free((info+i)->media_name); 
    } 
    free(info); 
    return;
}

void citp_delete_msex_1_2_media_info(uint16 cnt, struct msex_1_2_media_info *info)
{
    int i; 
    for (i=0; i<cnt; i++) {
        free((info+i)->media_name); 
    } 
    free(info); 
    return;
}

void citp_delete_vsrc_source_information(uint16 cnt, struct vsrc_source_information *info)
{
    int i; 
    for (i=0; i<cnt; i++) { 
        free((info +i)->source_name);
    }
    free(info);
    return;
}
