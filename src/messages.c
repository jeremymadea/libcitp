/*
 * messages.c - functions for constructing raw CITP messages from structures. 
 *
 * Jeremy Madea <jeremymadea@gmail.com>
 *
 */


#include <string.h>
#include "citptypes.h"
#include "ucsutils.h"

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


void citp_build_pinf_pnam_msg(void *msg, const struct citp_pinf_pnam *p)
{
    *(uint32 *)msg = p->pinf_header.citp_header.cookie;             msg += 4; 
    *(uint8  *)msg = p->pinf_header.citp_header.version_major;      msg += 1; 
    *(uint8  *)msg = p->pinf_header.citp_header.version_minor;      msg += 1; 
    *(uint16 *)msg = p->pinf_header.citp_header.request_index;      msg += 2; 
    *(uint32 *)msg = p->pinf_header.citp_header.message_size;       msg += 4; 
    *(uint16 *)msg = p->pinf_header.citp_header.message_part_count; msg += 2; 
    *(uint16 *)msg = p->pinf_header.citp_header.message_part;       msg += 2; 
    *(uint32 *)msg = p->pinf_header.citp_header.content_type;       msg += 4; 
    *(uint32 *)msg = p->pinf_header.content_type;                   msg += 4; 
    msg = stpcpy((char *)msg, (char *)(p->name));                     msg += 1; 
}
    
void citp_build_pinf_ploc_msg(void *msg, const struct citp_pinf_ploc *p)
{
    *(uint32 *)msg = p->pinf_header.citp_header.cookie;             msg += 4; 
    *(uint8  *)msg = p->pinf_header.citp_header.version_major;      msg += 1; 
    *(uint8  *)msg = p->pinf_header.citp_header.version_minor;      msg += 1; 
    *(uint16 *)msg = p->pinf_header.citp_header.request_index;      msg += 2; 
    *(uint32 *)msg = p->pinf_header.citp_header.message_size;       msg += 4; 
    *(uint16 *)msg = p->pinf_header.citp_header.message_part_count; msg += 2; 
    *(uint16 *)msg = p->pinf_header.citp_header.message_part;       msg += 2; 
    *(uint32 *)msg = p->pinf_header.citp_header.content_type;       msg += 4; 
    *(uint32 *)msg = p->pinf_header.content_type;                   msg += 4; 
    *(uint16 *)msg = p->listening_tcp_port;                         msg += 2; 
    msg = stpcpy((char *)msg, (char *)p->type);                     msg += 1; 
    msg = stpcpy((char *)msg, (char *)p->name);                     msg += 1; 
    msg = stpcpy((char *)msg, (char *)p->state);                    msg += 1; 
}

void citp_build_sdmx_enid_msg(void *msg, const struct citp_sdmx_enid *p)
{
    *(uint32 *)msg = p->sdmx_header.citp_header.cookie;             msg += 4; 
    *(uint8  *)msg = p->sdmx_header.citp_header.version_major;      msg += 1; 
    *(uint8  *)msg = p->sdmx_header.citp_header.version_minor;      msg += 1; 
    *(uint16 *)msg = p->sdmx_header.citp_header.request_index;      msg += 2; 
    *(uint32 *)msg = p->sdmx_header.citp_header.message_size;       msg += 4; 
    *(uint16 *)msg = p->sdmx_header.citp_header.message_part_count; msg += 2; 
    *(uint16 *)msg = p->sdmx_header.citp_header.message_part;       msg += 2; 
    *(uint32 *)msg = p->sdmx_header.citp_header.content_type;       msg += 4; 
    *(uint32 *)msg = p->sdmx_header.content_type;                   msg += 4; 
    msg = stpcpy((char *)msg, (char *)p->identifier);               msg += 1; 
}

void citp_build_sdmx_unam_msg(void *msg, const struct citp_sdmx_unam *p)
{
    *(uint32 *)msg = p->sdmx_header.citp_header.cookie;             msg += 4; 
    *(uint8  *)msg = p->sdmx_header.citp_header.version_major;      msg += 1; 
    *(uint8  *)msg = p->sdmx_header.citp_header.version_minor;      msg += 1; 
    *(uint16 *)msg = p->sdmx_header.citp_header.request_index;      msg += 2; 
    *(uint32 *)msg = p->sdmx_header.citp_header.message_size;       msg += 4; 
    *(uint16 *)msg = p->sdmx_header.citp_header.message_part_count; msg += 2; 
    *(uint16 *)msg = p->sdmx_header.citp_header.message_part;       msg += 2; 
    *(uint32 *)msg = p->sdmx_header.citp_header.content_type;       msg += 4; 
    *(uint32 *)msg = p->sdmx_header.content_type;                   msg += 4; 
    *(uint8  *)msg = p->universe_index;                             msg += 1;
    msg = stpcpy((char *)msg, (char *)p->universe_name);            msg += 1; 
}

void citp_build_sdmx_chbk_msg(void *msg, const struct citp_sdmx_chbk *p)
{
    *(uint32 *)msg = p->sdmx_header.citp_header.cookie;             msg += 4; 
    *(uint8  *)msg = p->sdmx_header.citp_header.version_major;      msg += 1; 
    *(uint8  *)msg = p->sdmx_header.citp_header.version_minor;      msg += 1; 
    *(uint16 *)msg = p->sdmx_header.citp_header.request_index;      msg += 2; 
    *(uint32 *)msg = p->sdmx_header.citp_header.message_size;       msg += 4; 
    *(uint16 *)msg = p->sdmx_header.citp_header.message_part_count; msg += 2; 
    *(uint16 *)msg = p->sdmx_header.citp_header.message_part;       msg += 2; 
    *(uint32 *)msg = p->sdmx_header.citp_header.content_type;       msg += 4; 
    *(uint32 *)msg = p->sdmx_header.content_type;                   msg += 4; 
    *(uint8  *)msg = p->blind;                                      msg += 1;
    *(uint8  *)msg = p->universe_index;                             msg += 1;
    *(uint16 *)msg = p->first_channel;                              msg += 2;
    *(uint16 *)msg = p->channel_count;                              msg += 2;
    (void)memcpy(msg, p->channel_levels, p->channel_count);  

}

void citp_build_sdmx_sxsr_msg(void *msg, const struct citp_sdmx_sxsr *p)
{
    *(uint32 *)msg = p->sdmx_header.citp_header.cookie;             msg += 4; 
    *(uint8  *)msg = p->sdmx_header.citp_header.version_major;      msg += 1; 
    *(uint8  *)msg = p->sdmx_header.citp_header.version_minor;      msg += 1; 
    *(uint16 *)msg = p->sdmx_header.citp_header.request_index;      msg += 2; 
    *(uint32 *)msg = p->sdmx_header.citp_header.message_size;       msg += 4; 
    *(uint16 *)msg = p->sdmx_header.citp_header.message_part_count; msg += 2; 
    *(uint16 *)msg = p->sdmx_header.citp_header.message_part;       msg += 2; 
    *(uint32 *)msg = p->sdmx_header.citp_header.content_type;       msg += 4; 
    *(uint32 *)msg = p->sdmx_header.content_type;                   msg += 4; 
    msg = stpcpy((char *)msg, (char *)p->connection_string);        msg += 1; 
}

void citp_build_msex_cinf_msg(void *msg, const struct citp_msex_cinf *p)
{
    size_t size; 
    *(uint32 *)msg = p->msex_header.citp_header.cookie;             msg += 4; 
    *(uint8  *)msg = p->msex_header.citp_header.version_major;      msg += 1; 
    *(uint8  *)msg = p->msex_header.citp_header.version_minor;      msg += 1; 
    *(uint16 *)msg = p->msex_header.citp_header.request_index;      msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.message_size;       msg += 4; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part_count; msg += 2; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part;       msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.content_type;       msg += 4; 
    *(uint8  *)msg = p->msex_header.version_major;                  msg += 1; 
    *(uint8  *)msg = p->msex_header.version_minor;                  msg += 1; 
    *(uint32 *)msg = p->msex_header.content_type;                   msg += 4; 
    *(uint8  *)msg = p->supported_msex_versions_count;              msg += 1;

    size = sizeof(uint16) * p->supported_msex_versions_count;
    (void)memcpy(msg, p->supported_msex_versions, size);
    msg += size; 

    *(uint32 *)msg = (uint32)0; /* instead of p->future_message_data; */
}

void citp_build_msex_1_0_sinf_msg(void *msg, const struct citp_msex_1_0_sinf *p) 
{
    int i; 
    struct msex_layer_info *info;
    *(uint32 *)msg = p->msex_header.citp_header.cookie;             msg += 4; 
    *(uint8  *)msg = p->msex_header.citp_header.version_major;      msg += 1; 
    *(uint8  *)msg = p->msex_header.citp_header.version_minor;      msg += 1; 
    *(uint16 *)msg = p->msex_header.citp_header.request_index;      msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.message_size;       msg += 4; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part_count; msg += 2; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part;       msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.content_type;       msg += 4; 
    *(uint8  *)msg = p->msex_header.version_major;                  msg += 1; 
    *(uint8  *)msg = p->msex_header.version_minor;                  msg += 1; 
    *(uint32 *)msg = p->msex_header.content_type;                   msg += 4; 
    msg = ucs2pcpy((ucs2 *)msg, p->product_name);                   msg += 2; 
    *(uint8  *)msg = p->product_version_major;                      msg += 1; 
    *(uint8  *)msg = p->product_version_minor;                      msg += 1; 
    *(uint8  *)msg = p->layer_count;                                msg += 1; 

    for (i=0; i < p->layer_count; i++) { 
        info = p->layer_information + i;
        msg = stpcpy((char *)msg, (char *)info->dmx_source);        msg += 1; 
    }

}

void citp_build_msex_1_2_sinf_msg(void *msg, const struct citp_msex_1_2_sinf *p)
{
    int i; 
    struct msex_layer_info *info;
    size_t size; 

    *(uint32 *)msg = p->msex_header.citp_header.cookie;             msg += 4; 
    *(uint8  *)msg = p->msex_header.citp_header.version_major;      msg += 1; 
    *(uint8  *)msg = p->msex_header.citp_header.version_minor;      msg += 1; 
    *(uint16 *)msg = p->msex_header.citp_header.request_index;      msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.message_size;       msg += 4; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part_count; msg += 2; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part;       msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.content_type;       msg += 4; 
    *(uint8  *)msg = p->msex_header.version_major;                  msg += 1; 
    *(uint8  *)msg = p->msex_header.version_minor;                  msg += 1; 
    *(uint32 *)msg = p->msex_header.content_type;                   msg += 4; 

    (void)memcpy(msg, p->uuid, 36);                                 msg += 36;
    
    msg = ucs2pcpy((ucs2 *)msg, p->product_name);                   msg += 2; 
    *(uint8  *)msg = p->product_version_major;                      msg += 1; 
    *(uint8  *)msg = p->product_version_minor;                      msg += 1; 
    *(uint8  *)msg = p->product_version_bugfix;                     msg += 1; 

    *(uint8  *)msg = p->supported_msex_versions_count;              msg += 1; 
    size = sizeof(uint16) * p->supported_msex_versions_count;
    (void)memcpy(msg, p->supported_msex_versions, size);
    msg += size; 

    *(uint16 *)msg = p->supported_library_types;                    msg += 2; 

    *(uint8  *)msg = p->thumbnail_formats_count;                    msg += 1; 
    size = sizeof(uint32) * p->thumbnail_formats_count;
    (void)memcpy(msg, p->thumbnail_formats, size);
    msg += size; 

    *(uint8  *)msg = p->stream_formats_count;                       msg += 1; 
    size = sizeof(uint32) * p->stream_formats_count;
    (void)memcpy(msg, p->stream_formats, size);
    msg += size; 

    *(uint8  *)msg = p->layer_count;                                msg += 1; 

    for (i=0; i < p->layer_count; i++) { 
        info = p->layer_information + i;
        msg = stpcpy((char *)msg, (char *)info->dmx_source);        msg += 1; 
    }
}

void citp_build_msex_1_0_lsta_msg(void *msg, const struct citp_msex_1_0_lsta *p) 
{
    int i; 
    struct msex_1_0_layer_status *status;

    *(uint32 *)msg = p->msex_header.citp_header.cookie;             msg += 4; 
    *(uint8  *)msg = p->msex_header.citp_header.version_major;      msg += 1; 
    *(uint8  *)msg = p->msex_header.citp_header.version_minor;      msg += 1; 
    *(uint16 *)msg = p->msex_header.citp_header.request_index;      msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.message_size;       msg += 4; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part_count; msg += 2; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part;       msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.content_type;       msg += 4; 
    *(uint8  *)msg = p->msex_header.version_major;                  msg += 1; 
    *(uint8  *)msg = p->msex_header.version_minor;                  msg += 1; 
    *(uint32 *)msg = p->msex_header.content_type;                   msg += 4; 
    *(uint8  *)msg = p->layer_count;                                msg += 1; 

    for (i=0; i < p->layer_count; i++) { 
        status = p->layer_status + i; 
        *(uint8  *)msg = status->layer_number;                       msg += 1; 
        *(uint8  *)msg = status->physical_output;                    msg += 1; 
        *(uint8  *)msg = status->media_library_number;               msg += 1; 
        *(uint8  *)msg = status->media_number;                       msg += 1; 
        msg = ucs2pcpy((ucs2 *)msg, status->media_name);             msg += 2;               
        *(uint32 *)msg = status->media_position;                     msg += 4; 
        *(uint32 *)msg = status->media_length;                       msg += 4; 
        *(uint8  *)msg = status->media_fps;                          msg += 1; 
        *(uint32 *)msg = status->layer_status_flags;                 msg += 4; 
    }
}

void citp_build_msex_1_2_lsta_msg(void *msg, const struct citp_msex_1_2_lsta *p) 
{
    int i; 
    struct msex_1_2_layer_status *status;

    *(uint32 *)msg = p->msex_header.citp_header.cookie;             msg += 4; 
    *(uint8  *)msg = p->msex_header.citp_header.version_major;      msg += 1; 
    *(uint8  *)msg = p->msex_header.citp_header.version_minor;      msg += 1; 
    *(uint16 *)msg = p->msex_header.citp_header.request_index;      msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.message_size;       msg += 4; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part_count; msg += 2; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part;       msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.content_type;       msg += 4; 
    *(uint8  *)msg = p->msex_header.version_major;                  msg += 1; 
    *(uint8  *)msg = p->msex_header.version_minor;                  msg += 1; 
    *(uint32 *)msg = p->msex_header.content_type;                   msg += 4; 
    *(uint8  *)msg = p->layer_count;                                msg += 1; 

    for (i=0; i < p->layer_count; i++) { 
        status = p->layer_status + i; 
        *(uint8  *)msg = status->layer_number;                       msg += 1; 
        *(uint8  *)msg = status->physical_output;                    msg += 1; 
        *(uint8  *)msg = status->media_library_type;                 msg += 1; 
        *(uint8  *)msg = status->media_library_id.level;             msg += 1; 
        *(uint8  *)msg = status->media_library_id.level1;            msg += 1; 
        *(uint8  *)msg = status->media_library_id.level2;            msg += 1; 
        *(uint8  *)msg = status->media_library_id.level3;            msg += 1; 
        *(uint8  *)msg = status->media_number;                       msg += 1; 
        msg = ucs2pcpy((ucs2 *)msg, status->media_name);             msg += 2;               
        *(uint32 *)msg = status->media_position;                     msg += 4; 
        *(uint32 *)msg = status->media_length;                       msg += 4; 
        *(uint8  *)msg = status->media_fps;                          msg += 1; 
        *(uint32 *)msg = status->layer_status_flags;                 msg += 4; 
    }
}

void citp_build_msex_nack_msg(void *msg, const struct citp_msex_nack *p) 
{
    *(uint32 *)msg = p->msex_header.citp_header.cookie;             msg += 4; 
    *(uint8  *)msg = p->msex_header.citp_header.version_major;      msg += 1; 
    *(uint8  *)msg = p->msex_header.citp_header.version_minor;      msg += 1; 
    *(uint16 *)msg = p->msex_header.citp_header.request_index;      msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.message_size;       msg += 4; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part_count; msg += 2; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part;       msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.content_type;       msg += 4; 
    *(uint8  *)msg = p->msex_header.version_major;                  msg += 1; 
    *(uint8  *)msg = p->msex_header.version_minor;                  msg += 1; 
    *(uint32 *)msg = p->msex_header.content_type;                   msg += 4; 
    *(uint32 *)msg = p->received_content_type;                      msg += 4;
}

void citp_build_msex_gvsr_msg(void *msg, const struct citp_msex_gvsr *p)
{
    *(uint32 *)msg = p->msex_header.citp_header.cookie;             msg += 4; 
    *(uint8  *)msg = p->msex_header.citp_header.version_major;      msg += 1; 
    *(uint8  *)msg = p->msex_header.citp_header.version_minor;      msg += 1; 
    *(uint16 *)msg = p->msex_header.citp_header.request_index;      msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.message_size;       msg += 4; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part_count; msg += 2; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part;       msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.content_type;       msg += 4; 
    *(uint8  *)msg = p->msex_header.version_major;                  msg += 1; 
    *(uint8  *)msg = p->msex_header.version_minor;                  msg += 1; 
    *(uint32 *)msg = p->msex_header.content_type;                   msg += 4; 
}

void citp_build_msex_vsrc_msg(void *msg, const struct citp_msex_vsrc *p)
{
    int i; 
    struct vsrc_source_information *info; 

    *(uint32 *)msg = p->msex_header.citp_header.cookie;             msg += 4; 
    *(uint8  *)msg = p->msex_header.citp_header.version_major;      msg += 1; 
    *(uint8  *)msg = p->msex_header.citp_header.version_minor;      msg += 1; 
    *(uint16 *)msg = p->msex_header.citp_header.request_index;      msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.message_size;       msg += 4; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part_count; msg += 2; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part;       msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.content_type;       msg += 4; 
    *(uint8  *)msg = p->msex_header.version_major;                  msg += 1; 
    *(uint8  *)msg = p->msex_header.version_minor;                  msg += 1; 
    *(uint32 *)msg = p->msex_header.content_type;                   msg += 4; 
    *(uint16 *)msg = p->source_count;                               msg += 2; 

    for (i=0; i < p->source_count; i++) { 
        info = p->source_information + i; 
        *(uint16 *)msg = info->source_identifier;                   msg += 2; 
        msg = ucs2pcpy((ucs2 *)msg, info->source_name);             msg += 2;
        *(uint8  *)msg = info->physical_output;                     msg += 1;  
        *(uint8  *)msg = info->layer_number;                        msg += 1; 
        *(uint16 *)msg = info->flags;                               msg += 2; 
        *(uint16 *)msg = info->width;                               msg += 2; 
        *(uint16 *)msg = info->height;                              msg += 2; 
    }
}

void citp_build_msex_1_0_geli_msg(void *msg, const struct citp_msex_1_0_geli *p) 
{
    *(uint32 *)msg = p->msex_header.citp_header.cookie;             msg += 4; 
    *(uint8  *)msg = p->msex_header.citp_header.version_major;      msg += 1; 
    *(uint8  *)msg = p->msex_header.citp_header.version_minor;      msg += 1; 
    *(uint16 *)msg = p->msex_header.citp_header.request_index;      msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.message_size;       msg += 4; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part_count; msg += 2; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part;       msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.content_type;       msg += 4; 
    *(uint8  *)msg = p->msex_header.version_major;                  msg += 1; 
    *(uint8  *)msg = p->msex_header.version_minor;                  msg += 1; 
    *(uint32 *)msg = p->msex_header.content_type;                   msg += 4; 
    *(uint8  *)msg = p->library_type;                               msg += 1; 
    *(uint8  *)msg = p->library_count;                              msg += 1; 
    (void)memcpy(msg, p->library_numbers, p->library_count);  

}

void citp_build_msex_1_1_geli_msg(void *msg, const struct citp_msex_1_1_geli *p)
{
    *(uint32 *)msg = p->msex_header.citp_header.cookie;             msg += 4; 
    *(uint8  *)msg = p->msex_header.citp_header.version_major;      msg += 1; 
    *(uint8  *)msg = p->msex_header.citp_header.version_minor;      msg += 1; 
    *(uint16 *)msg = p->msex_header.citp_header.request_index;      msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.message_size;       msg += 4; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part_count; msg += 2; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part;       msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.content_type;       msg += 4; 
    *(uint8  *)msg = p->msex_header.version_major;                  msg += 1; 
    *(uint8  *)msg = p->msex_header.version_minor;                  msg += 1; 
    *(uint32 *)msg = p->msex_header.content_type;                   msg += 4; 
    *(uint8  *)msg = p->library_type;                               msg += 1; 
    *(uint8  *)msg = p->library_parent_id.level;                    msg += 1; 
    *(uint8  *)msg = p->library_parent_id.level1;                   msg += 1; 
    *(uint8  *)msg = p->library_parent_id.level2;                   msg += 1; 
    *(uint8  *)msg = p->library_parent_id.level3;                   msg += 1; 
    *(uint8  *)msg = p->library_count;                              msg += 1; 
    (void)memcpy(msg, p->library_numbers, p->library_count);  
}

void citp_build_msex_1_2_geli_msg(void *msg, const struct citp_msex_1_2_geli *p)
{
    *(uint32 *)msg = p->msex_header.citp_header.cookie;             msg += 4; 
    *(uint8  *)msg = p->msex_header.citp_header.version_major;      msg += 1; 
    *(uint8  *)msg = p->msex_header.citp_header.version_minor;      msg += 1; 
    *(uint16 *)msg = p->msex_header.citp_header.request_index;      msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.message_size;       msg += 4; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part_count; msg += 2; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part;       msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.content_type;       msg += 4; 
    *(uint8  *)msg = p->msex_header.version_major;                  msg += 1; 
    *(uint8  *)msg = p->msex_header.version_minor;                  msg += 1; 
    *(uint32 *)msg = p->msex_header.content_type;                   msg += 4; 
    *(uint8  *)msg = p->library_type;                               msg += 1; 
    *(uint8  *)msg = p->library_parent_id.level;                    msg += 1; 
    *(uint8  *)msg = p->library_parent_id.level1;                   msg += 1; 
    *(uint8  *)msg = p->library_parent_id.level2;                   msg += 1; 
    *(uint8  *)msg = p->library_parent_id.level3;                   msg += 1; 
    *(uint16 *)msg = p->library_count;                              msg += 2; 
    (void)memcpy(msg, p->library_numbers, p->library_count);  
}

void citp_build_msex_1_0_elin_msg(void *msg, const struct citp_msex_1_0_elin *p)
{
    int i; 
    struct msex_1_0_element_library_info *info; 

    *(uint32 *)msg = p->msex_header.citp_header.cookie;             msg += 4; 
    *(uint8  *)msg = p->msex_header.citp_header.version_major;      msg += 1; 
    *(uint8  *)msg = p->msex_header.citp_header.version_minor;      msg += 1; 
    *(uint16 *)msg = p->msex_header.citp_header.request_index;      msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.message_size;       msg += 4; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part_count; msg += 2; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part;       msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.content_type;       msg += 4; 
    *(uint8  *)msg = p->msex_header.version_major;                  msg += 1; 
    *(uint8  *)msg = p->msex_header.version_minor;                  msg += 1; 
    *(uint32 *)msg = p->msex_header.content_type;                   msg += 4; 
    *(uint8  *)msg = p->library_type;                               msg += 1; 
    *(uint8  *)msg = p->library_count;                              msg += 1; 
    for (i=0; i < p->library_count; i++) { 
        info = p->element_library_information + i; 
        *(uint8  *)msg = info->number;                              msg += 1; 
        *(uint8  *)msg = info->dmx_range_min;                       msg += 1; 
        *(uint8  *)msg = info->dmx_range_max;                       msg += 1; 
        msg = ucs2pcpy((ucs2 *)msg, info->name);                    msg += 2;               
        *(uint8  *)msg = info->element_count;                       msg += 1; 
    }
}

void citp_build_msex_1_1_elin_msg(void *msg, const struct citp_msex_1_1_elin *p)
{
    int i; 
    struct msex_1_1_element_library_info *info; 

    *(uint32 *)msg = p->msex_header.citp_header.cookie;             msg += 4; 
    *(uint8  *)msg = p->msex_header.citp_header.version_major;      msg += 1; 
    *(uint8  *)msg = p->msex_header.citp_header.version_minor;      msg += 1; 
    *(uint16 *)msg = p->msex_header.citp_header.request_index;      msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.message_size;       msg += 4; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part_count; msg += 2; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part;       msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.content_type;       msg += 4; 
    *(uint8  *)msg = p->msex_header.version_major;                  msg += 1; 
    *(uint8  *)msg = p->msex_header.version_minor;                  msg += 1; 
    *(uint32 *)msg = p->msex_header.content_type;                   msg += 4; 
    *(uint8  *)msg = p->library_type;                               msg += 1; 
    *(uint8  *)msg = p->library_count;                              msg += 1; 
    for (i=0; i < p->library_count; i++) { 
        info = p->element_library_information + i; 
        *(uint8  *)msg = info->id.level;                            msg += 1; 
        *(uint8  *)msg = info->id.level1;                           msg += 1; 
        *(uint8  *)msg = info->id.level2;                           msg += 1; 
        *(uint8  *)msg = info->id.level3;                           msg += 1; 
        *(uint8  *)msg = info->dmx_range_min;                       msg += 1; 
        *(uint8  *)msg = info->dmx_range_max;                       msg += 1; 
        msg = ucs2pcpy((ucs2 *)msg, info->name);                    msg += 2;               
        *(uint8  *)msg = info->library_count;                       msg += 1; 
        *(uint8  *)msg = info->element_count;                       msg += 1; 
    }
}

void citp_build_msex_1_2_elin_msg(void *msg, const struct citp_msex_1_2_elin *p)
{
    int i; 
    struct msex_1_2_element_library_info *info; 

    *(uint32 *)msg = p->msex_header.citp_header.cookie;             msg += 4; 
    *(uint8  *)msg = p->msex_header.citp_header.version_major;      msg += 1; 
    *(uint8  *)msg = p->msex_header.citp_header.version_minor;      msg += 1; 
    *(uint16 *)msg = p->msex_header.citp_header.request_index;      msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.message_size;       msg += 4; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part_count; msg += 2; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part;       msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.content_type;       msg += 4; 
    *(uint8  *)msg = p->msex_header.version_major;                  msg += 1; 
    *(uint8  *)msg = p->msex_header.version_minor;                  msg += 1; 
    *(uint32 *)msg = p->msex_header.content_type;                   msg += 4; 
    *(uint8  *)msg = p->library_type;                               msg += 1; 
    *(uint16 *)msg = p->library_count;                              msg += 2; 
    for (i=0; i < p->library_count; i++) { 
        info = p->element_library_information + i; 
        *(uint8  *)msg = info->id.level;                            msg += 1; 
        *(uint8  *)msg = info->id.level1;                           msg += 1; 
        *(uint8  *)msg = info->id.level2;                           msg += 1; 
        *(uint8  *)msg = info->id.level3;                           msg += 1; 
        *(uint32 *)msg = info->serial_number;                       msg += 4; 
        *(uint8  *)msg = info->dmx_range_min;                       msg += 1; 
        *(uint8  *)msg = info->dmx_range_max;                       msg += 1; 
        msg = ucs2pcpy((ucs2 *)msg, info->name);                    msg += 2;               
        *(uint16 *)msg = info->library_count;                       msg += 2; 
        *(uint16 *)msg = info->element_count;                       msg += 2; 
    }
}

void citp_build_msex_1_0_gein_msg(void *msg, const struct citp_msex_1_0_gein *p)
{
    *(uint32 *)msg = p->msex_header.citp_header.cookie;             msg += 4; 
    *(uint8  *)msg = p->msex_header.citp_header.version_major;      msg += 1; 
    *(uint8  *)msg = p->msex_header.citp_header.version_minor;      msg += 1; 
    *(uint16 *)msg = p->msex_header.citp_header.request_index;      msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.message_size;       msg += 4; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part_count; msg += 2; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part;       msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.content_type;       msg += 4; 
    *(uint8  *)msg = p->msex_header.version_major;                  msg += 1; 
    *(uint8  *)msg = p->msex_header.version_minor;                  msg += 1; 
    *(uint32 *)msg = p->msex_header.content_type;                   msg += 4; 
    *(uint8  *)msg = p->library_type;                               msg += 1; 
    *(uint8  *)msg = p->library_number;                             msg += 1; 
    *(uint8  *)msg = p->element_count;                              msg += 1; 
    (void)memcpy(msg, p->element_numbers, p->element_count);  
}

void citp_build_msex_1_1_gein_msg(void *msg, const struct citp_msex_1_1_gein *p)
{
    *(uint32 *)msg = p->msex_header.citp_header.cookie;             msg += 4; 
    *(uint8  *)msg = p->msex_header.citp_header.version_major;      msg += 1; 
    *(uint8  *)msg = p->msex_header.citp_header.version_minor;      msg += 1; 
    *(uint16 *)msg = p->msex_header.citp_header.request_index;      msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.message_size;       msg += 4; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part_count; msg += 2; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part;       msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.content_type;       msg += 4; 
    *(uint8  *)msg = p->msex_header.version_major;                  msg += 1; 
    *(uint8  *)msg = p->msex_header.version_minor;                  msg += 1; 
    *(uint32 *)msg = p->msex_header.content_type;                   msg += 4; 
    *(uint8  *)msg = p->library_type;                               msg += 1; 
    *(uint8  *)msg = p->library_id.level;                           msg += 1; 
    *(uint8  *)msg = p->library_id.level1;                          msg += 1; 
    *(uint8  *)msg = p->library_id.level2;                          msg += 1; 
    *(uint8  *)msg = p->library_id.level3;                          msg += 1; 
    *(uint8  *)msg = p->element_count;                              msg += 1; 
    (void)memcpy(msg, p->element_numbers, p->element_count);  
}

void citp_build_msex_1_2_gein_msg(void *msg, const struct citp_msex_1_2_gein *p)
{
    *(uint32 *)msg = p->msex_header.citp_header.cookie;             msg += 4; 
    *(uint8  *)msg = p->msex_header.citp_header.version_major;      msg += 1; 
    *(uint8  *)msg = p->msex_header.citp_header.version_minor;      msg += 1; 
    *(uint16 *)msg = p->msex_header.citp_header.request_index;      msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.message_size;       msg += 4; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part_count; msg += 2; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part;       msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.content_type;       msg += 4; 
    *(uint8  *)msg = p->msex_header.version_major;                  msg += 1; 
    *(uint8  *)msg = p->msex_header.version_minor;                  msg += 1; 
    *(uint32 *)msg = p->msex_header.content_type;                   msg += 4; 
    *(uint8  *)msg = p->library_type;                               msg += 1; 
    *(uint8  *)msg = p->library_id.level;                           msg += 1; 
    *(uint8  *)msg = p->library_id.level1;                          msg += 1; 
    *(uint8  *)msg = p->library_id.level2;                          msg += 1; 
    *(uint8  *)msg = p->library_id.level3;                          msg += 1; 
    *(uint16 *)msg = p->element_count;                              msg += 2; 
    (void)memcpy(msg, p->element_numbers, p->element_count);  

}

void citp_build_msex_1_0_mein_msg(void *msg, const struct citp_msex_1_0_mein *p)
{
    int i; 
    struct msex_1_0_media_info *info;

    *(uint32 *)msg = p->msex_header.citp_header.cookie;             msg += 4; 
    *(uint8  *)msg = p->msex_header.citp_header.version_major;      msg += 1; 
    *(uint8  *)msg = p->msex_header.citp_header.version_minor;      msg += 1; 
    *(uint16 *)msg = p->msex_header.citp_header.request_index;      msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.message_size;       msg += 4; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part_count; msg += 2; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part;       msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.content_type;       msg += 4; 
    *(uint8  *)msg = p->msex_header.version_major;                  msg += 1; 
    *(uint8  *)msg = p->msex_header.version_minor;                  msg += 1; 
    *(uint32 *)msg = p->msex_header.content_type;                   msg += 4; 
    *(uint8  *)msg = p->library_number;                             msg += 1; 
    *(uint8  *)msg = p->library_count;                              msg += 1; 
    for (i=0; i < p->library_count; i++) { 
        info = p->media_information + i; 
        *(uint8  *)msg = info->number;                              msg += 1; 
        *(uint8  *)msg = info->dmx_range_min;                       msg += 1; 
        *(uint8  *)msg = info->dmx_range_max;                       msg += 1; 
        msg = ucs2pcpy((ucs2 *)msg, info->media_name);              msg += 2;               
        *(uint64 *)msg = info->media_version_timestamp;             msg += 8;
        *(uint16 *)msg = info->media_width;                         msg += 2; 
        *(uint16 *)msg = info->media_height;                        msg += 2; 
        *(uint32 *)msg = info->media_length;                        msg += 4; 
        *(uint8  *)msg = info->media_fps;                           msg += 1; 
    }
}

void citp_build_msex_1_1_mein_msg(void *msg, const struct citp_msex_1_1_mein *p)
{
    int i; 
    struct msex_1_0_media_info *info;

    *(uint32 *)msg = p->msex_header.citp_header.cookie;             msg += 4; 
    *(uint8  *)msg = p->msex_header.citp_header.version_major;      msg += 1; 
    *(uint8  *)msg = p->msex_header.citp_header.version_minor;      msg += 1; 
    *(uint16 *)msg = p->msex_header.citp_header.request_index;      msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.message_size;       msg += 4; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part_count; msg += 2; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part;       msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.content_type;       msg += 4; 
    *(uint8  *)msg = p->msex_header.version_major;                  msg += 1; 
    *(uint8  *)msg = p->msex_header.version_minor;                  msg += 1; 
    *(uint32 *)msg = p->msex_header.content_type;                   msg += 4; 
    *(uint8  *)msg = p->library_id.level;                           msg += 1; 
    *(uint8  *)msg = p->library_id.level1;                          msg += 1; 
    *(uint8  *)msg = p->library_id.level2;                          msg += 1; 
    *(uint8  *)msg = p->library_id.level3;                          msg += 1; 
    *(uint8  *)msg = p->library_count;                              msg += 1; 
    for (i=0; i < p->library_count; i++) { 
        info = p->media_information + i; 
        *(uint8  *)msg = info->number;                              msg += 1; 
        *(uint8  *)msg = info->dmx_range_min;                       msg += 1; 
        *(uint8  *)msg = info->dmx_range_max;                       msg += 1; 
        msg = ucs2pcpy((ucs2 *)msg, info->media_name);              msg += 2;               
        *(uint64 *)msg = info->media_version_timestamp;             msg += 8;
        *(uint16 *)msg = info->media_width;                         msg += 2; 
        *(uint16 *)msg = info->media_height;                        msg += 2; 
        *(uint32 *)msg = info->media_length;                        msg += 4; 
        *(uint8  *)msg = info->media_fps;                           msg += 1; 
    }
}

void citp_build_msex_1_2_mein_msg(void *msg, const struct citp_msex_1_2_mein *p)
{
    int i; 
    struct msex_1_2_media_info *info;

    *(uint32 *)msg = p->msex_header.citp_header.cookie;             msg += 4; 
    *(uint8  *)msg = p->msex_header.citp_header.version_major;      msg += 1; 
    *(uint8  *)msg = p->msex_header.citp_header.version_minor;      msg += 1; 
    *(uint16 *)msg = p->msex_header.citp_header.request_index;      msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.message_size;       msg += 4; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part_count; msg += 2; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part;       msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.content_type;       msg += 4; 
    *(uint8  *)msg = p->msex_header.version_major;                  msg += 1; 
    *(uint8  *)msg = p->msex_header.version_minor;                  msg += 1; 
    *(uint32 *)msg = p->msex_header.content_type;                   msg += 4; 
    *(uint8  *)msg = p->library_id.level;                           msg += 1; 
    *(uint8  *)msg = p->library_id.level1;                          msg += 1; 
    *(uint8  *)msg = p->library_id.level2;                          msg += 1; 
    *(uint8  *)msg = p->library_id.level3;                          msg += 1; 
    *(uint16 *)msg = p->library_count;                              msg += 2; 
    for (i=0; i < p->library_count; i++) { 
        info = p->media_information + i; 
        *(uint8  *)msg = info->number;                              msg += 1; 
        *(uint32 *)msg = info->serial_number;                       msg += 1; 
        *(uint8  *)msg = info->dmx_range_min;                       msg += 1; 
        *(uint8  *)msg = info->dmx_range_max;                       msg += 1; 
        msg = ucs2pcpy((ucs2 *)msg, info->media_name);              msg += 2;               
        *(uint64 *)msg = info->media_version_timestamp;             msg += 8;
        *(uint16 *)msg = info->media_width;                         msg += 2; 
        *(uint16 *)msg = info->media_height;                        msg += 2; 
        *(uint32 *)msg = info->media_length;                        msg += 4; 
        *(uint8  *)msg = info->media_fps;                           msg += 1; 
    }
}

void citp_build_msex_1_0_gelt_msg(void *msg, const struct citp_msex_1_0_gelt *p)
{
    *(uint32 *)msg = p->msex_header.citp_header.cookie;             msg += 4; 
    *(uint8  *)msg = p->msex_header.citp_header.version_major;      msg += 1; 
    *(uint8  *)msg = p->msex_header.citp_header.version_minor;      msg += 1; 
    *(uint16 *)msg = p->msex_header.citp_header.request_index;      msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.message_size;       msg += 4; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part_count; msg += 2; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part;       msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.content_type;       msg += 4; 
    *(uint8  *)msg = p->msex_header.version_major;                  msg += 1; 
    *(uint8  *)msg = p->msex_header.version_minor;                  msg += 1; 
    *(uint32 *)msg = p->msex_header.content_type;                   msg += 4; 
    *(uint32 *)msg = p->thumbnail_format;                           msg += 4;
    *(uint16 *)msg = p->thumbnail_width;                            msg += 2;
    *(uint16 *)msg = p->thumbnail_height;                           msg += 2; 
    *(uint8  *)msg = p->thumbnail_flags;                            msg += 1;
    *(uint8  *)msg = p->library_type;                               msg += 1; 
    *(uint8  *)msg = p->library_count;                              msg += 1; 
    (void)memcpy(msg, p->library_numbers, p->library_count);  
}

void citp_build_msex_1_1_gelt_msg(void *msg, const struct citp_msex_1_1_gelt *p)
{
    struct msex_library_id *id; 
    int i; 
    
    *(uint32 *)msg = p->msex_header.citp_header.cookie;             msg += 4; 
    *(uint8  *)msg = p->msex_header.citp_header.version_major;      msg += 1; 
    *(uint8  *)msg = p->msex_header.citp_header.version_minor;      msg += 1; 
    *(uint16 *)msg = p->msex_header.citp_header.request_index;      msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.message_size;       msg += 4; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part_count; msg += 2; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part;       msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.content_type;       msg += 4; 
    *(uint8  *)msg = p->msex_header.version_major;                  msg += 1; 
    *(uint8  *)msg = p->msex_header.version_minor;                  msg += 1; 
    *(uint32 *)msg = p->msex_header.content_type;                   msg += 4; 
    *(uint32 *)msg = p->thumbnail_format;                           msg += 4;
    *(uint16 *)msg = p->thumbnail_width;                            msg += 2;
    *(uint16 *)msg = p->thumbnail_height;                           msg += 2; 
    *(uint8  *)msg = p->thumbnail_flags;                            msg += 1;
    *(uint8  *)msg = p->library_type;                               msg += 1; 
    *(uint8  *)msg = p->library_count;                              msg += 1; 
    for (i=0; i< p->library_count; i++) {
        id = p->library_ids + i; 
        *(uint8 *)msg = id->level;      msg += 1; 
        *(uint8 *)msg = id->level1;     msg += 1; 
        *(uint8 *)msg = id->level2;     msg += 1; 
        *(uint8 *)msg = id->level3;     msg += 1; 
    }
    
}

void citp_build_msex_1_2_gelt_msg(void *msg, const struct citp_msex_1_2_gelt *p)
{
    struct msex_library_id *id; 
    int i; 

    *(uint32 *)msg = p->msex_header.citp_header.cookie;             msg += 4; 
    *(uint8  *)msg = p->msex_header.citp_header.version_major;      msg += 1; 
    *(uint8  *)msg = p->msex_header.citp_header.version_minor;      msg += 1; 
    *(uint16 *)msg = p->msex_header.citp_header.request_index;      msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.message_size;       msg += 4; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part_count; msg += 2; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part;       msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.content_type;       msg += 4; 
    *(uint8  *)msg = p->msex_header.version_major;                  msg += 1; 
    *(uint8  *)msg = p->msex_header.version_minor;                  msg += 1; 
    *(uint32 *)msg = p->msex_header.content_type;                   msg += 4; 
    *(uint32 *)msg = p->thumbnail_format;                           msg += 4;
    *(uint16 *)msg = p->thumbnail_width;                            msg += 2;
    *(uint16 *)msg = p->thumbnail_height;                           msg += 2; 
    *(uint8  *)msg = p->thumbnail_flags;                            msg += 1;
    *(uint8  *)msg = p->library_type;                               msg += 1; 
    *(uint16 *)msg = p->library_count;                              msg += 2; 
    for (i=0; i< p->library_count; i++) {
        id = p->library_ids + i; 
        *(uint8 *)msg = id->level;      msg += 1; 
        *(uint8 *)msg = id->level1;     msg += 1; 
        *(uint8 *)msg = id->level2;     msg += 1; 
        *(uint8 *)msg = id->level3;     msg += 1; 
    }
    
}

void citp_build_msex_1_0_elth_msg(void *msg, const struct citp_msex_1_0_elth *p)
{
    *(uint32 *)msg = p->msex_header.citp_header.cookie;             msg += 4; 
    *(uint8  *)msg = p->msex_header.citp_header.version_major;      msg += 1; 
    *(uint8  *)msg = p->msex_header.citp_header.version_minor;      msg += 1; 
    *(uint16 *)msg = p->msex_header.citp_header.request_index;      msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.message_size;       msg += 4; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part_count; msg += 2; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part;       msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.content_type;       msg += 4; 
    *(uint8  *)msg = p->msex_header.version_major;                  msg += 1; 
    *(uint8  *)msg = p->msex_header.version_minor;                  msg += 1; 
    *(uint32 *)msg = p->msex_header.content_type;                   msg += 4; 
    *(uint8  *)msg = p->library_type;                               msg += 1; 
    *(uint8  *)msg = p->library_number;                             msg += 1; 
    *(uint32 *)msg = p->thumbnail_format;                           msg += 4;
    *(uint16 *)msg = p->thumbnail_width;                            msg += 2;
    *(uint16 *)msg = p->thumbnail_height;                           msg += 2; 
    *(uint16 *)msg = p->thumbnail_buffer_size;                      msg += 2; 
    (void)memcpy(msg, p->thumbnail_buffer, p->thumbnail_buffer_size);  
}

void citp_build_msex_1_1_elth_msg(void *msg, const struct citp_msex_1_1_elth *p)
{
    *(uint32 *)msg = p->msex_header.citp_header.cookie;             msg += 4; 
    *(uint8  *)msg = p->msex_header.citp_header.version_major;      msg += 1; 
    *(uint8  *)msg = p->msex_header.citp_header.version_minor;      msg += 1; 
    *(uint16 *)msg = p->msex_header.citp_header.request_index;      msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.message_size;       msg += 4; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part_count; msg += 2; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part;       msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.content_type;       msg += 4; 
    *(uint8  *)msg = p->msex_header.version_major;                  msg += 1; 
    *(uint8  *)msg = p->msex_header.version_minor;                  msg += 1; 
    *(uint32 *)msg = p->msex_header.content_type;                   msg += 4; 
    *(uint8  *)msg = p->library_type;                               msg += 1; 
    *(uint8  *)msg = p->library_id.level;                           msg += 1; 
    *(uint8  *)msg = p->library_id.level1;                          msg += 1; 
    *(uint8  *)msg = p->library_id.level2;                          msg += 1; 
    *(uint8  *)msg = p->library_id.level3;                          msg += 1; 
    *(uint32 *)msg = p->thumbnail_format;                           msg += 4;
    *(uint16 *)msg = p->thumbnail_width;                            msg += 2;
    *(uint16 *)msg = p->thumbnail_height;                           msg += 2; 
    *(uint16 *)msg = p->thumbnail_buffer_size;                      msg += 2; 
    (void)memcpy(msg, p->thumbnail_buffer, p->thumbnail_buffer_size);  
}

void citp_build_msex_1_0_geth_msg(void *msg, const struct citp_msex_1_0_geth *p)
{
    *(uint32 *)msg = p->msex_header.citp_header.cookie;             msg += 4; 
    *(uint8  *)msg = p->msex_header.citp_header.version_major;      msg += 1; 
    *(uint8  *)msg = p->msex_header.citp_header.version_minor;      msg += 1; 
    *(uint16 *)msg = p->msex_header.citp_header.request_index;      msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.message_size;       msg += 4; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part_count; msg += 2; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part;       msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.content_type;       msg += 4; 
    *(uint8  *)msg = p->msex_header.version_major;                  msg += 1; 
    *(uint8  *)msg = p->msex_header.version_minor;                  msg += 1; 
    *(uint32 *)msg = p->msex_header.content_type;                   msg += 4; 
    *(uint32 *)msg = p->thumbnail_format;                           msg += 4;
    *(uint16 *)msg = p->thumbnail_width;                            msg += 2;
    *(uint16 *)msg = p->thumbnail_height;                           msg += 2; 
    *(uint8  *)msg = p->thumbnail_flags;                            msg += 1;
    *(uint8  *)msg = p->library_type;                               msg += 1; 
    *(uint8  *)msg = p->library_number;                             msg += 1; 
    *(uint8  *)msg = p->element_count;                              msg += 1; 
    (void)memcpy(msg, p->element_numbers, p->element_count);  
}

void citp_build_msex_1_1_geth_msg(void *msg, const struct citp_msex_1_1_geth *p)
{
    *(uint32 *)msg = p->msex_header.citp_header.cookie;             msg += 4; 
    *(uint8  *)msg = p->msex_header.citp_header.version_major;      msg += 1; 
    *(uint8  *)msg = p->msex_header.citp_header.version_minor;      msg += 1; 
    *(uint16 *)msg = p->msex_header.citp_header.request_index;      msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.message_size;       msg += 4; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part_count; msg += 2; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part;       msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.content_type;       msg += 4; 
    *(uint8  *)msg = p->msex_header.version_major;                  msg += 1; 
    *(uint8  *)msg = p->msex_header.version_minor;                  msg += 1; 
    *(uint32 *)msg = p->msex_header.content_type;                   msg += 4; 
    *(uint32 *)msg = p->thumbnail_format;                           msg += 4;
    *(uint16 *)msg = p->thumbnail_width;                            msg += 2;
    *(uint16 *)msg = p->thumbnail_height;                           msg += 2; 
    *(uint8  *)msg = p->thumbnail_flags;                            msg += 1;
    *(uint8  *)msg = p->library_type;                               msg += 1; 
    *(uint8  *)msg = p->library_id.level;                           msg += 1; 
    *(uint8  *)msg = p->library_id.level1;                          msg += 1; 
    *(uint8  *)msg = p->library_id.level2;                          msg += 1; 
    *(uint8  *)msg = p->library_id.level3;                          msg += 1; 
    *(uint8  *)msg = p->element_count;                              msg += 1; 
    (void)memcpy(msg, p->element_numbers, p->element_count);  
}

void citp_build_msex_1_2_geth_msg(void *msg, const struct citp_msex_1_2_geth *p)
{
    *(uint32 *)msg = p->msex_header.citp_header.cookie;             msg += 4; 
    *(uint8  *)msg = p->msex_header.citp_header.version_major;      msg += 1; 
    *(uint8  *)msg = p->msex_header.citp_header.version_minor;      msg += 1; 
    *(uint16 *)msg = p->msex_header.citp_header.request_index;      msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.message_size;       msg += 4; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part_count; msg += 2; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part;       msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.content_type;       msg += 4; 
    *(uint8  *)msg = p->msex_header.version_major;                  msg += 1; 
    *(uint8  *)msg = p->msex_header.version_minor;                  msg += 1; 
    *(uint32 *)msg = p->msex_header.content_type;                   msg += 4; 
    *(uint32 *)msg = p->thumbnail_format;                           msg += 4;
    *(uint16 *)msg = p->thumbnail_width;                            msg += 2;
    *(uint16 *)msg = p->thumbnail_height;                           msg += 2; 
    *(uint8  *)msg = p->thumbnail_flags;                            msg += 1;
    *(uint8  *)msg = p->library_type;                               msg += 1; 
    *(uint8  *)msg = p->library_id.level;                           msg += 1; 
    *(uint8  *)msg = p->library_id.level1;                          msg += 1; 
    *(uint8  *)msg = p->library_id.level2;                          msg += 1; 
    *(uint8  *)msg = p->library_id.level3;                          msg += 1; 
    *(uint16 *)msg = p->element_count;                              msg += 2; 
    (void)memcpy(msg, p->element_numbers, p->element_count);  
}

void citp_build_msex_1_0_ethn_msg(void *msg, const struct citp_msex_1_0_ethn *p)
{
    *(uint32 *)msg = p->msex_header.citp_header.cookie;             msg += 4; 
    *(uint8  *)msg = p->msex_header.citp_header.version_major;      msg += 1; 
    *(uint8  *)msg = p->msex_header.citp_header.version_minor;      msg += 1; 
    *(uint16 *)msg = p->msex_header.citp_header.request_index;      msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.message_size;       msg += 4; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part_count; msg += 2; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part;       msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.content_type;       msg += 4; 
    *(uint8  *)msg = p->msex_header.version_major;                  msg += 1; 
    *(uint8  *)msg = p->msex_header.version_minor;                  msg += 1; 
    *(uint32 *)msg = p->msex_header.content_type;                   msg += 4; 
    *(uint8  *)msg = p->library_type;                               msg += 1; 
    *(uint8  *)msg = p->library_number;                             msg += 1; 
    *(uint8  *)msg = p->element_number;                             msg += 1; 
    *(uint32 *)msg = p->thumbnail_format;                           msg += 4;
    *(uint16 *)msg = p->thumbnail_width;                            msg += 2;
    *(uint16 *)msg = p->thumbnail_height;                           msg += 2; 
    *(uint16 *)msg = p->thumbnail_buffer_size;                      msg += 2; 
    (void)memcpy(msg, p->thumbnail_buffer, p->thumbnail_buffer_size);  
}

void citp_build_msex_1_1_ethn_msg(void *msg, const struct citp_msex_1_1_ethn *p)
{
    *(uint32 *)msg = p->msex_header.citp_header.cookie;             msg += 4; 
    *(uint8  *)msg = p->msex_header.citp_header.version_major;      msg += 1; 
    *(uint8  *)msg = p->msex_header.citp_header.version_minor;      msg += 1; 
    *(uint16 *)msg = p->msex_header.citp_header.request_index;      msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.message_size;       msg += 4; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part_count; msg += 2; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part;       msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.content_type;       msg += 4; 
    *(uint8  *)msg = p->msex_header.version_major;                  msg += 1; 
    *(uint8  *)msg = p->msex_header.version_minor;                  msg += 1; 
    *(uint32 *)msg = p->msex_header.content_type;                   msg += 4; 
    *(uint8  *)msg = p->library_type;                               msg += 1; 
    *(uint8  *)msg = p->library_id.level;                           msg += 1; 
    *(uint8  *)msg = p->library_id.level1;                          msg += 1; 
    *(uint8  *)msg = p->library_id.level2;                          msg += 1; 
    *(uint8  *)msg = p->library_id.level3;                          msg += 1; 
    *(uint8  *)msg = p->element_number;                             msg += 1; 
    *(uint32 *)msg = p->thumbnail_format;                           msg += 4;
    *(uint16 *)msg = p->thumbnail_width;                            msg += 2;
    *(uint16 *)msg = p->thumbnail_height;                           msg += 2; 
    *(uint16 *)msg = p->thumbnail_buffer_size;                      msg += 2; 
    (void)memcpy(msg, p->thumbnail_buffer, p->thumbnail_buffer_size);  
}


void citp_build_msex_rqst_msg(void *msg, const struct citp_msex_rqst *p)
{
    *(uint32 *)msg = p->msex_header.citp_header.cookie;             msg += 4; 
    *(uint8  *)msg = p->msex_header.citp_header.version_major;      msg += 1; 
    *(uint8  *)msg = p->msex_header.citp_header.version_minor;      msg += 1; 
    *(uint16 *)msg = p->msex_header.citp_header.request_index;      msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.message_size;       msg += 4; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part_count; msg += 2; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part;       msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.content_type;       msg += 4; 
    *(uint8  *)msg = p->msex_header.version_major;                  msg += 1; 
    *(uint8  *)msg = p->msex_header.version_minor;                  msg += 1; 
    *(uint32 *)msg = p->msex_header.content_type;                   msg += 4; 
    *(uint16 *)msg = p->source_identifier;                          msg += 2; 
    *(uint32 *)msg = p->frame_format;                               msg += 4; 
    *(uint16 *)msg = p->frame_width;                                msg += 2; 
    *(uint16 *)msg = p->frame_height;                               msg += 2; 
    *(uint8  *)msg = p->fps;                                        msg += 1; 
    *(uint8  *)msg = p->timeout;                                    msg += 1; 

};

void citp_build_msex_1_0_stfr_msg(void *msg, const struct citp_msex_1_0_stfr *p)
{
    *(uint32 *)msg = p->msex_header.citp_header.cookie;             msg += 4; 
    *(uint8  *)msg = p->msex_header.citp_header.version_major;      msg += 1; 
    *(uint8  *)msg = p->msex_header.citp_header.version_minor;      msg += 1; 
    *(uint16 *)msg = p->msex_header.citp_header.request_index;      msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.message_size;       msg += 4; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part_count; msg += 2; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part;       msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.content_type;       msg += 4; 
    *(uint8  *)msg = p->msex_header.version_major;                  msg += 1; 
    *(uint8  *)msg = p->msex_header.version_minor;                  msg += 1; 
    *(uint32 *)msg = p->msex_header.content_type;                   msg += 4; 
    *(uint16 *)msg = p->source_identifier;                          msg += 2; 
    *(uint32 *)msg = p->frame_format;                               msg += 4; 
    *(uint16 *)msg = p->frame_width;                                msg += 2; 
    *(uint16 *)msg = p->frame_height;                               msg += 2; 
    *(uint16 *)msg = p->frame_buffer_size;                          msg += 2; 
    (void)memcpy(msg, p->frame_buffer, p->frame_buffer_size);  
};

void citp_build_msex_1_2_stfr_msg(void *msg, const struct citp_msex_1_2_stfr *p)
{
    *(uint32 *)msg = p->msex_header.citp_header.cookie;             msg += 4; 
    *(uint8  *)msg = p->msex_header.citp_header.version_major;      msg += 1; 
    *(uint8  *)msg = p->msex_header.citp_header.version_minor;      msg += 1; 
    *(uint16 *)msg = p->msex_header.citp_header.request_index;      msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.message_size;       msg += 4; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part_count; msg += 2; 
    *(uint16 *)msg = p->msex_header.citp_header.message_part;       msg += 2; 
    *(uint32 *)msg = p->msex_header.citp_header.content_type;       msg += 4; 
    *(uint8  *)msg = p->msex_header.version_major;                  msg += 1; 
    *(uint8  *)msg = p->msex_header.version_minor;                  msg += 1; 
    *(uint32 *)msg = p->msex_header.content_type;                   msg += 4; 
    (void)memcpy(msg, p->media_server_uuid, 36);                    msg += 36;
    *(uint16 *)msg = p->source_identifier;                          msg += 2; 
    *(uint32 *)msg = p->frame_format;                               msg += 4; 
    *(uint16 *)msg = p->frame_width;                                msg += 2; 
    *(uint16 *)msg = p->frame_height;                               msg += 2; 
    *(uint16 *)msg = p->frame_buffer_size;                          msg += 2; 
    (void)memcpy(msg, p->frame_buffer, p->frame_buffer_size);  
};
