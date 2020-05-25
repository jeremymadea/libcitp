/* 
 * parse.c - Functions for parsing raw CITP messages. 
 * Jeremy Madea <jeremymadea@gmail.com>
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "citptypes.h"
#include "ucsutils.h"
#include "parse.h"

/* INTERFACE (see parse.h) */
/* void *citp_parse_message(void *buf); */ 

/* Forward declarations of private parsing routines. */
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
struct citp_msex_vsrc *parse_msex_vsrc(void *buf);
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
struct citp_msex_1_0_gelt *parse_msex_1_0_gelt(void *buf); 
struct citp_msex_1_1_gelt *parse_msex_1_1_gelt(void *buf); 
struct citp_msex_1_2_gelt *parse_msex_1_2_gelt(void *buf); 
struct citp_msex_1_0_elth *parse_msex_1_0_elth(void *buf); 
struct citp_msex_1_1_elth *parse_msex_1_1_elth(void *buf); 
struct citp_msex_1_0_geth *parse_msex_1_0_geth(void *buf); 
struct citp_msex_1_1_geth *parse_msex_1_1_geth(void *buf); 
struct citp_msex_1_2_geth *parse_msex_1_2_geth(void *buf); 
struct citp_msex_1_0_ethn *parse_msex_1_0_ethn(void *buf); 
struct citp_msex_1_1_ethn *parse_msex_1_1_ethn(void *buf); 

struct citp_msex_rqst *parse_msex_rqst(void *buf); 
struct citp_msex_1_0_stfr *parse_msex_1_0_stfr(void *buf); 
struct citp_msex_1_2_stfr *parse_msex_1_2_stfr(void *buf); 


/* Utilities for extracting data from raw messages. */

uint8 citp_raw_version_major(void *buf)
{ 
    return *(uint8 *)(buf + 4);
}

uint8 citp_raw_version_minor(void *buf)
{ 
    return *(uint8 *)(buf + 5);
}

uint16 citp_raw_request_number(void *buf)
{
    return *(uint8 *)(buf + 6);
}

uint32 citp_raw_size(void *buf) 
{ 
    return *(uint32 *)(buf + 8); 
}

uint16 citp_raw_part_count(void *buf) 
{ 
    return *(uint16 *)(buf + 12);
}

uint16 citp_raw_part_number(void *buf) 
{
    return *(uint16 *)(buf + 14);
}

uint32 citp_raw_layer_cookie(void *buf) 
{ 
    return *(uint32 *)(buf + 16);
}

uint32 citp_raw_message_cookie(void *buf) 
{ 
    return *(uint32 *)(buf + 20);
}

uint32 msex_raw_message_cookie(void *buf) 
{ 
    return *(uint32 *)(buf + 22);
}

uint8 msex_raw_version_major(void *buf)
{
    return *(uint8 *)(buf + 20);
}

uint8 msex_raw_version_minor(void *buf)
{
    return *(uint8 *)(buf + 21);
}


void *citp_parse_message(void *buf) 
{
    uint32 layer; 

    layer = citp_raw_layer_cookie(buf); 
    switch (layer) {
        case CITP_COOKIE_PINF: 
            return citp_parse_pinf(buf); 
            break;
        case CITP_COOKIE_SDMX: 
            return citp_parse_sdmx(buf); 
            break;
        case CITP_COOKIE_MSEX:
            return citp_parse_msex(buf); 
            break;
        case CITP_COOKIE_FPTC:  /* UNIMPLEMENTED */
        case CITP_COOKIE_FSEL:  /* UNIMPLEMENTED */
        case CITP_COOKIE_FINF:  /* UNIMPLEMENTED */
        default:                /* UNKNOWN */
            return NULL; 
    }
}

void *citp_parse_pinf(void *buf) 
{ 
    uint32 type; 
    type = citp_raw_message_cookie(buf);
    switch(type) {
        case CITP_COOKIE_PINF_PNAM:
            return (void *)parse_pinf_pnam(buf);
        case CITP_COOKIE_PINF_PLOC:
            return (void *)parse_pinf_ploc(buf);
        default:                    /* UNKNOWN */
            return NULL;
    }
}

void *citp_parse_sdmx(void *buf) 
{ 
    uint32 type; 
    type = citp_raw_message_cookie(buf);
    switch(type) {
        case CITP_COOKIE_SDMX_ENID:
            return (void *)parse_sdmx_enid(buf);
        case CITP_COOKIE_SDMX_UNAM:
            return (void *)parse_sdmx_unam(buf);
        case CITP_COOKIE_SDMX_CHBK:
            return (void *)parse_sdmx_chbk(buf);
        case CITP_COOKIE_SDMX_SXSR:
            return (void *)parse_sdmx_sxsr(buf);
        default:                    /* UNKNOWN */
            return NULL;
    }
}

void *citp_parse_msex(void *buf) 
{ 
    uint32 type; 
    uint8 mver; 

    type = msex_raw_message_cookie(buf); /* different offset than other citp messages. */
    mver = msex_raw_version_minor(buf);
#ifdef DEBUG
printf("DEBUG: Parsing MSEX %x Minor version %d\n", type, mver); 
#endif
    switch(type) {
        case CITP_COOKIE_MSEX_CINF:
            return (void *)parse_msex_cinf(buf);
        case CITP_COOKIE_MSEX_SINF:
            switch(mver) { 
                case 0: 
                case 1: return (void *)parse_msex_1_0_sinf(buf);
                case 2: 
                default: return (void *)parse_msex_1_2_sinf(buf);
            };
        case CITP_COOKIE_MSEX_LSTA:
            switch(mver) { 
                case 0: 
                case 1: return (void *)parse_msex_1_0_lsta(buf);
                case 2: 
                default: return (void *)parse_msex_1_2_lsta(buf);
            };
        case CITP_COOKIE_MSEX_NACK:
            return (void *)parse_msex_nack(buf);
        case CITP_COOKIE_MSEX_GVSR:
            return (void *)parse_msex_gvsr(buf);
        case CITP_COOKIE_MSEX_VSRC:
            return (void *)parse_msex_vsrc(buf);
        case CITP_COOKIE_MSEX_GELI:
            switch(mver) { 
                case 0: return (void *)parse_msex_1_0_geli(buf);
                case 1: return (void *)parse_msex_1_1_geli(buf);
                case 2: 
                default: return (void *)parse_msex_1_2_geli(buf);
            };
        case CITP_COOKIE_MSEX_ELIN:
            switch(mver) { 
                case 0: return (void *)parse_msex_1_0_elin(buf);
                case 1: return (void *)parse_msex_1_1_elin(buf);
                case 2: 
                default: return (void *)parse_msex_1_2_elin(buf);
            };
        case CITP_COOKIE_MSEX_GEIN:
            switch(mver) { 
                case 0: return (void *)parse_msex_1_0_gein(buf);
                case 1: return (void *)parse_msex_1_1_gein(buf);
                case 2: 
                default: return (void *)parse_msex_1_2_gein(buf);
            };
        case CITP_COOKIE_MSEX_MEIN:
            switch(mver) { 
                case 0: return (void *)parse_msex_1_0_mein(buf);
                case 1: return (void *)parse_msex_1_1_mein(buf);
                case 2: 
                default: return (void *)parse_msex_1_2_mein(buf);
            };
        case CITP_COOKIE_MSEX_GELT:
            switch(mver) { 
                case 0: return (void *)parse_msex_1_0_gelt(buf);
                case 1: return (void *)parse_msex_1_1_gelt(buf);
                case 2: 
                default: return (void *)parse_msex_1_2_gelt(buf);
            };
        case CITP_COOKIE_MSEX_ELTH: 
            switch(mver) { 
                case 0: return (void *)parse_msex_1_0_elth(buf);
                case 1:
                case 2: 
                default: return (void *)parse_msex_1_1_elth(buf);
            };
        case CITP_COOKIE_MSEX_GETH:
            switch(mver) { 
                case 0: return (void *)parse_msex_1_0_geth(buf);
                case 1: return (void *)parse_msex_1_1_geth(buf);
                case 2: 
                default: return (void *)parse_msex_1_2_geth(buf);
            };
        case CITP_COOKIE_MSEX_ETHN: 
            switch(mver) { 
                case 0: return (void *)parse_msex_1_0_ethn(buf);
                case 1:
                case 2: 
                default: return (void *)parse_msex_1_1_ethn(buf);
            };
        case CITP_COOKIE_MSEX_RQST:
            return (void *)parse_msex_rqst(buf);
        case CITP_COOKIE_MSEX_STFR: 
            switch(mver) { 
                case 0:
                case 1: return (void *)parse_msex_1_0_stfr(buf);
                case 2: 
                default: return (void *)parse_msex_1_2_stfr(buf);
            };
        default:                    /* UNKNOWN */
            return NULL;
    }
}

void fill_citp_header(struct citp_header *p, void *buf)
{
    p->cookie = CITP_COOKIE_CITP; 
    p->version_major = citp_raw_version_major(buf);
    p->version_minor = citp_raw_version_minor(buf);
    p->request_index = citp_raw_request_number(buf); 
    p->message_size = citp_raw_size(buf);
    p->message_part_count = citp_raw_part_count(buf);
    p->message_part = citp_raw_part_number(buf);
    p->content_type = citp_raw_layer_cookie(buf); 
    return;
}

void fill_pinf_header(struct citp_pinf_header *p, void *buf)
{
    fill_citp_header(&(p->citp_header), buf); 
    p->content_type = citp_raw_message_cookie(buf); 
    return;
}

void fill_sdmx_header(struct citp_sdmx_header *p, void *buf)
{
    fill_citp_header(&(p->citp_header), buf); 
    p->content_type = citp_raw_message_cookie(buf); 
    return; 
}

void fill_msex_header(struct citp_msex_header *p, void *buf)
{
    fill_citp_header(&(p->citp_header), buf); 
    p->version_minor = msex_raw_version_minor(buf); 
    p->version_major = msex_raw_version_major(buf);
    p->content_type = msex_raw_message_cookie(buf);
    return;
}

struct citp_pinf_pnam *parse_pinf_pnam(void *buf)
{
    struct citp_pinf_pnam *p;

    p = malloc(sizeof(struct citp_pinf_pnam));
    if (!p) {
        perror("Could not allocate memory for citp_pinf_pnam");
        return NULL;
    }

    fill_pinf_header(&p->pinf_header, buf); 
    p->name = copy_ucs1_str(buf + CITP_PINF_HEADER_SIZE);

    return p;
}

struct citp_pinf_ploc *parse_pinf_ploc(void *buf)
{
    struct citp_pinf_ploc *p;
    void *cur; 

    p = malloc(sizeof(struct citp_pinf_ploc));
    if (!p) {
        perror("Could not allocate memory for citp_pinf_ploc");
        return NULL;
    }  

    fill_pinf_header(&p->pinf_header, buf); 
    cur = buf + CITP_PINF_HEADER_SIZE; 
    p->listening_tcp_port = *(uint16 *)cur; 
    cur += 2; 
    p->type = copy_ucs1_str(cur); 
    cur += strlen((char *)p->type) + 1; 
    p->name = copy_ucs1_str(cur);
    cur += strlen((char *)p->name) + 1; 
    p->state = copy_ucs1_str(cur);

    return p;
}

struct citp_sdmx_enid *parse_sdmx_enid(void *buf)
{
    struct citp_sdmx_enid *p;

    p = malloc(sizeof(struct citp_sdmx_enid));
    if (!p) {
        perror("Could not allocate memory for citp_sdmx_enid");
        return NULL;
    }  

    fill_sdmx_header(&p->sdmx_header, buf);
    p->identifier = copy_ucs1_str(buf + CITP_SDMX_HEADER_SIZE);

    return p;
}

struct citp_sdmx_unam *parse_sdmx_unam(void *buf)
{
    struct citp_sdmx_unam *p;
    void *cur; 

    p = malloc(sizeof(struct citp_sdmx_unam));
    if (!p) {
        perror("Could not allocate memory for citp_sdmx_unam");
        return NULL;
    }  

    fill_sdmx_header(&p->sdmx_header, buf);
    cur = buf + CITP_SDMX_HEADER_SIZE; 
    p->universe_index = *(uint8 *)cur; 
    cur += 1; 
    p->universe_name = copy_ucs1_str(cur); 

    return p;
}

struct citp_sdmx_chbk *parse_sdmx_chbk(void *buf)
{
    struct citp_sdmx_chbk *p;
    void *cur; 

    p = malloc(sizeof(struct citp_sdmx_chbk));
    if (!p) {
        perror("Could not allocate memory for citp_sdmx_chbk");
        return NULL;
    }  

    fill_sdmx_header(&p->sdmx_header, buf);
    cur = buf + CITP_SDMX_HEADER_SIZE; 
    p->blind          = *(uint8 *)cur;  cur += 1;
    p->universe_index = *(uint8* )cur;  cur += 1; 
    p->first_channel  = *(uint16 *)cur; cur += 2; 
    p->channel_count  = *(uint16 *)cur; cur += 2; 

    p->channel_levels = malloc(p->channel_count); 
    if (!p->channel_levels) { 
        perror("Could not allocate memory for SDMX channel levels"); 
        exit(EXIT_FAILURE); /* XXX simple for now. */
    }

    memcpy(p->channel_levels, cur, p->channel_count); 

    return p;
}


struct citp_sdmx_sxsr *parse_sdmx_sxsr(void *buf)
{
    struct citp_sdmx_sxsr *p;

    p = malloc(sizeof(struct citp_sdmx_sxsr));
    if (!p) {
        perror("Could not allocate memory for citp_sdmx_sxsr");
        return NULL;
    }  

    fill_sdmx_header(&p->sdmx_header, buf);
    p->connection_string = copy_ucs1_str(buf + CITP_SDMX_HEADER_SIZE);

    return p;
}


struct citp_msex_cinf *parse_msex_cinf(void *buf)
{
    struct citp_msex_cinf *p;
    void *cur; 

    p = malloc(sizeof(struct citp_msex_cinf));
    if (!p) {
        perror("Could not allocate memory for citp_msex_cinf");
        return NULL;
    }  

    fill_msex_header(&p->msex_header, buf);
    cur = buf + CITP_MSEX_HEADER_SIZE; 
    p->supported_msex_versions_count = *(uint8 *)cur; 

    p->supported_msex_versions = calloc(p->supported_msex_versions_count, sizeof(uint16));
    if (!p->supported_msex_versions) { 
        perror("Could not allocate memory for MSEX supported version list"); 
        exit(EXIT_FAILURE); /* XXX simple for now. */
    }

    memcpy(p->supported_msex_versions, cur, p->supported_msex_versions_count * sizeof(uint16)); 

    return p;
}

struct citp_msex_1_0_sinf *parse_msex_1_0_sinf(void *buf) 
{
    struct citp_msex_1_0_sinf *p;
    void *cur;
    int i;
    struct msex_layer_info *info; 
#ifdef DEBUG
printf("DEBUG: Parsing MSEX 1.0 SInf message.\n");
#endif
    p = malloc(sizeof(struct citp_msex_1_0_sinf));
    if (!p) {
        perror("Could not allocate memory for citp_msex_1_0_sinf");
        return NULL;
    }  

    fill_msex_header(&p->msex_header, buf);
    cur = buf + CITP_MSEX_HEADER_SIZE; 
    cur = ucs2str_newcopy(&(p->product_name), cur); 
    cur += sizeof(ucs2); 
    p->product_version_major = *(uint8 *)cur; cur += 1; 
    p->product_version_minor = *(uint8 *)cur; cur += 1; 
    p->layer_count = *(uint8 *)cur;           cur += 1; 
    p->layer_information = calloc((size_t)p->layer_count, sizeof(struct msex_layer_info)); 
    if (!p->layer_information) {
        perror("Could not allocate memory for layer information");
        exit(EXIT_FAILURE); /* XXX simple for now. */
    }  
    info = p->layer_information; 
    for (i=0; i < p->layer_count; i++) {
        cur = ucs1str_newcopy(&(info->dmx_source), cur); 
        cur += sizeof(ucs1); 
        info++;  
    }

    return p;
}

struct citp_msex_1_2_sinf *parse_msex_1_2_sinf(void *buf) 
{
    struct citp_msex_1_2_sinf *p;
    void *cur; 
    int i;
    struct msex_layer_info *info; 
    size_t size; 

    p = malloc(sizeof(struct citp_msex_1_2_sinf));
    if (!p) {
        perror("Could not allocate memory for citp_msex_1_2_sinf");
        return NULL;
    }  

    fill_msex_header(&p->msex_header, buf);
    cur = buf + CITP_MSEX_HEADER_SIZE; 

    memcpy((void *)&(p->uuid), cur, 36); 
    cur += 36;  
    cur = ucs2str_newcopy(&(p->product_name), cur); 
    cur += sizeof(ucs2); 
    p->product_version_major = *(uint8 *)cur; cur += 1; 
    p->product_version_major = *(uint8 *)cur; cur += 1; 
    p->product_version_bugfix = *(uint8 *)cur; cur += 1; 

    p->supported_msex_versions_count = *(uint8 *)cur; cur += 1; 
    size = p->supported_msex_versions_count * sizeof(uint16);
    p->supported_msex_versions = malloc(size); 
    if (!p->supported_msex_versions) {
        perror("Could not allocate memory for supported MSEX versions");
        exit(EXIT_FAILURE); /* XXX simple for now. */
    } 
    memcpy((void *)&(p->supported_msex_versions), cur, size); 
    cur += size;

    p->supported_library_types = *(uint16 *)cur; cur += 2;
 
    p->thumbnail_formats_count = *(uint8 *)cur; cur += 1; 
    size = p->thumbnail_formats_count * sizeof(uint32); 
    p->thumbnail_formats = malloc(size); 
    if (!p->thumbnail_formats) {
        perror("Could not allocate memory for thumbnail formats");
        exit(EXIT_FAILURE); /* XXX simple for now. */
    } 
    memcpy((void *)&(p->thumbnail_formats), cur, size); 
    cur += size;

    p->stream_formats_count = *(uint8 *)cur; cur += 1; 
    size = p->stream_formats_count * sizeof(uint32); 
    p->stream_formats = malloc(size); 
    if (!p->stream_formats) {
        perror("Could not allocate memory for stream formats");
        exit(EXIT_FAILURE); /* XXX simple for now. */
    } 
    memcpy((void *)&(p->stream_formats), cur, size); 
    cur += size;

    p->layer_count = *(uint8 *)cur; cur += 1; 
    p->layer_information = calloc((size_t)p->layer_count, sizeof(struct msex_layer_info)); 
    if (!p->layer_information) {
        perror("Could not allocate memory for layer information");
        exit(EXIT_FAILURE); /* XXX simple for now. */
    }  
    info = p->layer_information; 
    for (i=0; i < p->layer_count; i++) {
        cur = ucs1str_newcopy(&(info->dmx_source), cur); 
        cur += sizeof(ucs1); 
        info++;  
    }

    return p;
}

struct citp_msex_1_0_lsta *parse_msex_1_0_lsta(void *buf) 
{
    struct citp_msex_1_0_lsta *p;
    void *cur;
    int i;
    struct msex_1_0_layer_status *status;

    p = malloc(sizeof(struct citp_msex_1_0_lsta));
    if (!p) {
        perror("Could not allocate memory for MSEX 1.0 LSta message");
        return NULL;
    }  

    fill_msex_header(&p->msex_header, buf);
    cur = buf + CITP_MSEX_HEADER_SIZE; 

    p->layer_count = *(uint8 *)cur; cur += 1; 
    p->layer_status = calloc((size_t)p->layer_count, sizeof(struct msex_1_0_layer_status)); 
    if (!p->layer_status) {
        perror("Could not allocate memory for layer status");
        exit(EXIT_FAILURE); /* XXX simple for now. */
    }  
    status = p->layer_status; 
    for (i=0; i < p->layer_count; i++) {
        status->layer_number = *(uint8 *)cur; cur += 1; 
        status->physical_output = *(uint8 *)cur; cur += 1; 
        status->media_library_number = *(uint8 *)cur; cur += 1; 
        status->media_number = *(uint8 *)cur; cur += 1; 
        cur = ucs2str_newcopy(&(status->media_name), cur); 
        cur += sizeof(ucs2); 
        status->media_position = *(uint32 *)cur; cur += 4; 
        status->media_length = *(uint32 *)cur; cur += 4; 
        status->media_fps = *(uint8 *)cur; cur += 1; 
        status->layer_status_flags = *(uint32 *)cur; cur += 4; 
        status++;  
    }

    return p;
}

struct citp_msex_1_2_lsta *parse_msex_1_2_lsta(void *buf) 
{
    struct citp_msex_1_2_lsta *p;
    void *cur;
    int i;
    struct msex_1_2_layer_status *status;

    p = malloc(sizeof(struct citp_msex_1_2_lsta));
    if (!p) {
        perror("Could not allocate memory for MSEX 1.2 LSta message");
        return NULL;
    }  

    fill_msex_header(&p->msex_header, buf);
    cur = buf + CITP_MSEX_HEADER_SIZE; 

    p->layer_count = *(uint8 *)cur; cur += 1; 
    p->layer_status = calloc((size_t)p->layer_count, sizeof(struct msex_1_2_layer_status)); 
    if (!p->layer_status) {
        perror("Could not allocate memory for layer status");
        exit(EXIT_FAILURE); /* XXX simple for now. */
    }  
    status = p->layer_status; 
    for (i=0; i < p->layer_count; i++) {
        status->layer_number = *(uint8 *)cur; cur += 1; 
        status->physical_output = *(uint8 *)cur; cur += 1; 
        status->media_library_type = *(uint8 *)cur; cur += 1; 
        status->media_library_id.level  = *(uint8 *)cur; cur += 1; 
        status->media_library_id.level1 = *(uint8 *)cur; cur += 1; 
        status->media_library_id.level2 = *(uint8 *)cur; cur += 1; 
        status->media_library_id.level3 = *(uint8 *)cur; cur += 1; 
        status->media_number = *(uint8 *)cur; cur += 1; 
        cur = ucs2str_newcopy(&(status->media_name), cur); 
        cur += sizeof(ucs2); 
        status->media_position = *(uint32 *)cur; cur += 4; 
        status->media_length = *(uint32 *)cur; cur += 4; 
        status->media_fps = *(uint8 *)cur; cur += 1; 
        status->layer_status_flags = *(uint32 *)cur; cur += 4; 
        status++;  
    }

    return p;
}

struct citp_msex_nack *parse_msex_nack(void *buf)
{
    struct citp_msex_nack *p;
    p = malloc(sizeof(struct citp_msex_nack));
    if (!p) {
        perror("Could not allocate memory for citp_msex_nack");
        return NULL;
    }  

    fill_msex_header(&p->msex_header, buf);
    p->received_content_type = *(uint32 *)(buf + CITP_MSEX_HEADER_SIZE); 

    return p;
}

struct citp_msex_gvsr *parse_msex_gvsr(void *buf) 
{
    struct citp_msex_gvsr *p;
    p = malloc(sizeof(struct citp_msex_gvsr));
    if (!p) {
        perror("Could not allocate memory for citp_msex_gvsr");
        return NULL;
    }  

    fill_msex_header(&p->msex_header, buf);

    return p;
}

struct citp_msex_vsrc *parse_msex_vsrc(void *buf) 
{
    struct citp_msex_vsrc *p;
    void *cur; 
    struct vsrc_source_information *info; 
    int i;

    p = malloc(sizeof(struct citp_msex_vsrc));
    if (!p) {
        perror("Could not allocate memory for citp_msex_vsrc");
        return NULL;
    }  

    fill_msex_header(&p->msex_header, buf);
    cur = buf + CITP_MSEX_HEADER_SIZE; 

    p->source_count                         = *(uint16 *)cur; cur += 2; 

    p->source_information = calloc((size_t)p->source_count, sizeof(struct vsrc_source_information)); 
    if (!p->source_information) {
        perror("Could not allocate memory for video source information");
        exit(EXIT_FAILURE); /* XXX simple for now. */
    }  

    info = p->source_information; 
    for (i=0; i < p->source_count; i++) {
        info->source_identifier = *(uint16 *)cur; cur += 2;
        cur = ucs2str_newcopy(&(info->source_name), cur); 
        cur += sizeof(ucs2);
        info->physical_output = *(uint8  *)cur; cur += 1;
        info->layer_number    = *(uint8  *)cur; cur += 1;
        info->flags           = *(uint16 *)cur; cur += 2; 
        info->width           = *(uint16 *)cur; cur += 2; 
        info->height          = *(uint16 *)cur; cur += 2; 
        info++;  
    }

    return p;
}

struct citp_msex_1_0_geli *parse_msex_1_0_geli(void *buf) 
{
    struct citp_msex_1_0_geli *p;
    void *cur; 

    p = malloc(sizeof(struct citp_msex_1_0_geli));
    if (!p) {
        perror("Could not allocate memory for MSEX 1.0 GELI message");
        return NULL;
    }  

    fill_msex_header(&p->msex_header, buf);
    cur = buf + CITP_MSEX_HEADER_SIZE; 

    p->library_type   = *(uint8 *)cur;  cur += 1;
    p->library_count  = *(uint8* )cur;  cur += 1; 

    p->library_numbers = malloc(p->library_count); 
    if (!p->library_numbers) { 
        perror("Could not allocate memory for MSEX/GELI 1.0 library numbers"); 
        exit(EXIT_FAILURE); /* XXX simple for now. */
    }

    memcpy(p->library_numbers, cur, p->library_count); 

    return p;
}

struct citp_msex_1_1_geli *parse_msex_1_1_geli(void *buf) 
{
    struct citp_msex_1_1_geli *p;
    void *cur; 

    p = malloc(sizeof(struct citp_msex_1_1_geli));
    if (!p) {
        perror("Could not allocate memory for MSEX 1.1 GELI message");
        return NULL;
    }  

    fill_msex_header(&p->msex_header, buf);
    cur = buf + CITP_MSEX_HEADER_SIZE; 

    p->library_type             = *(uint8 *)cur;  cur += 1;
    p->library_parent_id.level  = *(uint8 *)cur;  cur += 1;
    p->library_parent_id.level1 = *(uint8 *)cur;  cur += 1;
    p->library_parent_id.level2 = *(uint8 *)cur;  cur += 1;
    p->library_parent_id.level3 = *(uint8 *)cur;  cur += 1;
    p->library_count  = *(uint8* )cur;  cur += 1; 

    p->library_numbers = malloc(p->library_count); 
    if (!p->library_numbers) { 
        perror("Could not allocate memory for MSEX/GELI 1.1 library numbers"); 
        exit(EXIT_FAILURE); /* XXX simple for now. */
    }

    memcpy(p->library_numbers, cur, p->library_count); 

    return p;
}

struct citp_msex_1_2_geli *parse_msex_1_2_geli(void *buf)
{
    struct citp_msex_1_2_geli *p;
    void *cur;

    p = malloc(sizeof(struct citp_msex_1_2_geli));
    if (!p) {
        perror("Could not allocate memory for MSEX 1.2 GELI message");
        return NULL;
    }  

    fill_msex_header(&p->msex_header, buf);
    cur = buf + CITP_MSEX_HEADER_SIZE; 

    p->library_type   = *(uint8 *)cur;  cur += 1;
    p->library_parent_id.level  = *(uint8 *)cur;  cur += 1;
    p->library_parent_id.level1 = *(uint8 *)cur;  cur += 1;
    p->library_parent_id.level2 = *(uint8 *)cur;  cur += 1;
    p->library_parent_id.level3 = *(uint8 *)cur;  cur += 1;
    p->library_count  = *(uint16* )cur;  cur += 2; 

    p->library_numbers = malloc(p->library_count); 
    if (!p->library_numbers) { 
        perror("Could not allocate memory for MSEX/GELI 1.2 library numbers"); 
        exit(EXIT_FAILURE); /* XXX simple for now. */
    }

    memcpy(p->library_numbers, cur, p->library_count); 

    return p;
}

struct citp_msex_1_0_elin *parse_msex_1_0_elin(void *buf)
{
    struct citp_msex_1_0_elin *p;
    void *cur;
    int i;
    struct msex_1_0_element_library_info *info;

    p = malloc(sizeof(struct citp_msex_1_0_elin));
    if (!p) {
        perror("Could not allocate memory for MSEX 1.0 ELIn message");
        return NULL;
    }  

    fill_msex_header(&p->msex_header, buf);
    cur = buf + CITP_MSEX_HEADER_SIZE; 

    p->library_type = *(uint8 *)cur; cur += 1; 

    p->library_count = *(uint8 *)cur; cur += 1; 
    p->element_library_information = calloc((size_t)p->library_count, sizeof(struct msex_1_0_element_library_info)); 
    if (!p->element_library_information) {
        perror("Could not allocate memory for MSEX 1.0 element library information");
        exit(EXIT_FAILURE); /* XXX simple for now. */
    }  
    info = p->element_library_information; 
    for (i=0; i < p->library_count; i++) {
        info->number = *(uint8 *)cur; cur += 1; 
        info->dmx_range_min = *(uint8 *)cur; cur += 1; 
        info->dmx_range_max = *(uint8 *)cur; cur += 1; 
        cur = ucs2str_newcopy(&(info->name), cur); 
        cur += sizeof(ucs2); 
        info->element_count = *(uint8 *)cur; cur += 1; 
        info++;  
    }

    return p;
}

struct citp_msex_1_1_elin *parse_msex_1_1_elin(void *buf)
{
    struct citp_msex_1_1_elin *p;
    void *cur;
    int i;
    struct msex_1_1_element_library_info *info;

    p = malloc(sizeof(struct citp_msex_1_1_elin));
    if (!p) {
        perror("Could not allocate memory for MSEX 1.1 ELIn message");
        return NULL;
    }  

    fill_msex_header(&p->msex_header, buf);
    cur = buf + CITP_MSEX_HEADER_SIZE; 

    p->library_type = *(uint8 *)cur; cur += 1; 

    p->library_count = *(uint8 *)cur; cur += 1; 
    p->element_library_information = calloc((size_t)p->library_count, sizeof(struct msex_1_1_element_library_info)); 
    if (!p->element_library_information) {
        perror("Could not allocate memory for MSEX 1.1 element library information");
        exit(EXIT_FAILURE); /* XXX simple for now. */
    }  
    info = p->element_library_information; 
    for (i=0; i < p->library_count; i++) {
        info->id.level = *(uint8 *)cur; cur += 1; 
        info->id.level1 = *(uint8 *)cur; cur += 1; 
        info->id.level2 = *(uint8 *)cur; cur += 1; 
        info->id.level3 = *(uint8 *)cur; cur += 1; 
        info->dmx_range_min = *(uint8 *)cur; cur += 1; 
        info->dmx_range_max = *(uint8 *)cur; cur += 1; 
        cur = ucs2str_newcopy(&(info->name), cur); 
        cur += sizeof(ucs2); 
        info->library_count = *(uint8 *)cur; cur += 1; 
        info->element_count = *(uint8 *)cur; cur += 1; 
        info++;  
    }

    return p;
}
struct citp_msex_1_2_elin *parse_msex_1_2_elin(void *buf)
{
    struct citp_msex_1_2_elin *p;
    void *cur;
    int i;
    struct msex_1_2_element_library_info *info;

    p = malloc(sizeof(struct citp_msex_1_2_elin));
    if (!p) {
        perror("Could not allocate memory for MSEX 1.2 ELIn message");
        return NULL;
    }  

    fill_msex_header(&p->msex_header, buf);
    cur = buf + CITP_MSEX_HEADER_SIZE; 

    p->library_type = *(uint8 *)cur; cur += 1; 

    p->library_count = *(uint16 *)cur; cur += 2; 
    p->element_library_information = calloc((size_t)p->library_count, sizeof(struct msex_1_2_element_library_info)); 
    if (!p->element_library_information) {
        perror("Could not allocate memory for MSEX 1.2 element library information");
        exit(EXIT_FAILURE); /* XXX simple for now. */
    }  
    info = p->element_library_information; 
    for (i=0; i < p->library_count; i++) {
        info->id.level = *(uint8 *)cur; cur += 1; 
        info->id.level1 = *(uint8 *)cur; cur += 1; 
        info->id.level2 = *(uint8 *)cur; cur += 1; 
        info->id.level3 = *(uint8 *)cur; cur += 1; 
        info->serial_number = *(uint32 *)cur; cur += 4; 
        info->dmx_range_min = *(uint8 *)cur; cur += 1; 
        info->dmx_range_max = *(uint8 *)cur; cur += 1; 
        cur = ucs2str_newcopy(&(info->name), cur); 
        cur += sizeof(ucs2); 
        info->element_count = *(uint8 *)cur; cur += 1; 
        info++;  
    }

    return p;
}

struct citp_msex_1_0_gein *parse_msex_1_0_gein(void *buf) 
{
    struct citp_msex_1_0_gein *p;
    void *cur;
    p = malloc(sizeof(struct citp_msex_1_0_gein));
    if (!p) {
        perror("Could not allocate memory for citp_msex_1_0_gein");
        return NULL;
    }  

    fill_msex_header(&p->msex_header, buf);
    cur = buf + CITP_MSEX_HEADER_SIZE; 

    p->library_type    = *(uint8 *)cur;  cur += 1; 
    p->library_number  = *(uint8 *)cur;  cur += 1; 
    p->element_count   = *(uint8 *)cur;  cur += 1; 

    p->element_numbers = malloc(p->element_count);
    if (!p->element_numbers) {
        perror("Could not allocate memory for element numbers"); 
        exit(EXIT_FAILURE); /* XXX simple for now. */
    }
    memcpy(p->element_numbers, cur, p->element_count); 

    return p;
}

struct citp_msex_1_1_gein *parse_msex_1_1_gein(void *buf)
{
    struct citp_msex_1_1_gein *p;
    void *cur;

    p = malloc(sizeof(struct citp_msex_1_1_gein));
    if (!p) {
        perror("Could not allocate memory for citp_msex_1_1_gein");
        return NULL;
    }  

    fill_msex_header(&p->msex_header, buf);
    cur = buf + CITP_MSEX_HEADER_SIZE; 

    p->library_type      = *(uint8 *)cur;  cur += 1; 
    p->library_id.level  = *(uint8 *)cur;  cur += 1; 
    p->library_id.level1 = *(uint8 *)cur;  cur += 1; 
    p->library_id.level2 = *(uint8 *)cur;  cur += 1; 
    p->library_id.level3 = *(uint8 *)cur;  cur += 1; 
    p->element_count     = *(uint8 *)cur;  cur += 1; 

    p->element_numbers = malloc(p->element_count);
    if (!p->element_numbers) {
        perror("Could not allocate memory for element numbers"); 
        exit(EXIT_FAILURE); /* XXX simple for now. */
    }
    memcpy(p->element_numbers, cur, p->element_count); 

    return p;
}

struct citp_msex_1_2_gein *parse_msex_1_2_gein(void *buf)
{
    struct citp_msex_1_2_gein *p;
    void *cur; 

    p = malloc(sizeof(struct citp_msex_1_2_gein));
    if (!p) {
        perror("Could not allocate memory for citp_msex_1_2_gein");
        return NULL;
    }  

    fill_msex_header(&p->msex_header, buf);
    cur = buf + CITP_MSEX_HEADER_SIZE; 

    p->library_type      = *(uint8 *)cur;  cur += 1; 
    p->library_id.level  = *(uint8 *)cur;  cur += 1; 
    p->library_id.level1 = *(uint8 *)cur;  cur += 1; 
    p->library_id.level2 = *(uint8 *)cur;  cur += 1; 
    p->library_id.level3 = *(uint8 *)cur;  cur += 1; 
    p->element_count     = *(uint16 *)cur; cur += 1; 

    p->element_numbers = malloc(p->element_count);
    if (!p->element_numbers) {
        perror("Could not allocate memory for element numbers"); 
        exit(EXIT_FAILURE); /* XXX simple for now. */
    }
    memcpy(p->element_numbers, cur, p->element_count); 

    return p;
}

struct citp_msex_1_0_mein *parse_msex_1_0_mein(void *buf)
{
    struct citp_msex_1_0_mein *p;
    void *cur;
    int i;
    struct msex_1_0_media_info *info;

    p = malloc(sizeof(struct citp_msex_1_0_mein));
    if (!p) {
        perror("Could not allocate memory for MSEX 1.0 MEIn message");
        return NULL;
    }  

    fill_msex_header(&p->msex_header, buf);
    cur = buf + CITP_MSEX_HEADER_SIZE; 

    p->library_number = *(uint8 *)cur; cur += 1; 

    p->library_count = *(uint8 *)cur; cur += 1; 
    p->media_information = calloc((size_t)p->library_count, sizeof(struct msex_1_0_media_info)); 
    if (!p->media_information) {
        perror("Could not allocate memory for MSEX 1.0 media information");
        exit(EXIT_FAILURE); /* XXX simple for now. */
    }  
    info = p->media_information; 
    for (i=0; i < p->library_count; i++) {
        info->number = *(uint8 *)cur; cur += 1; 
        info->dmx_range_min = *(uint8 *)cur; cur += 1; 
        info->dmx_range_max = *(uint8 *)cur; cur += 1; 
        cur = ucs2str_newcopy(&(info->media_name), cur); 
        cur += sizeof(ucs2); 
        info->media_version_timestamp = *(uint64 *)cur; cur += 8; 
        info->media_width = *(uint16 *)cur; cur += 2; 
        info->media_height = *(uint16 *)cur; cur += 2; 
        info->media_length = *(uint32 *)cur; cur += 4; 
        info->media_fps = *(uint8 *)cur; cur += 1; 
        info++;  
    }

    return p;
}
struct citp_msex_1_1_mein *parse_msex_1_1_mein(void *buf)
{
    struct citp_msex_1_1_mein *p;
    void *cur;
    int i;
    struct msex_1_0_media_info *info;

    p = malloc(sizeof(struct citp_msex_1_1_mein));
    if (!p) {
        perror("Could not allocate memory for MSEX MEIn message");
        return NULL;
    }  

    fill_msex_header(&p->msex_header, buf);
    cur = buf + CITP_MSEX_HEADER_SIZE; 

    p->library_id.level  = *(uint8 *)cur; cur += 1; 
    p->library_id.level1 = *(uint8 *)cur; cur += 1; 
    p->library_id.level2 = *(uint8 *)cur; cur += 1; 
    p->library_id.level3 = *(uint8 *)cur; cur += 1; 

    p->library_count = *(uint8 *)cur; cur += 1; 
    p->media_information = calloc((size_t)p->library_count, sizeof(struct msex_1_0_media_info)); 
    if (!p->media_information) {
        perror("Could not allocate memory for MSEX 1.1 media information");
        exit(EXIT_FAILURE); /* XXX simple for now. */
    }  
    info = p->media_information; 
    for (i=0; i < p->library_count; i++) {
        info->number = *(uint8 *)cur; cur += 1; 
        info->dmx_range_min = *(uint8 *)cur; cur += 1; 
        info->dmx_range_max = *(uint8 *)cur; cur += 1; 
        cur = ucs2str_newcopy(&(info->media_name), cur); 
        cur += sizeof(ucs2); 
        info->media_version_timestamp = *(uint64 *)cur; cur += 8; 
        info->media_width = *(uint16 *)cur; cur += 2; 
        info->media_height = *(uint16 *)cur; cur += 2; 
        info->media_length = *(uint32 *)cur; cur += 4; 
        info->media_fps = *(uint8 *)cur; cur += 1; 
        info++;  
    }

    return p;
}
struct citp_msex_1_2_mein *parse_msex_1_2_mein(void *buf)
{
    struct citp_msex_1_2_mein *p;
    void *cur;
    int i;
    struct msex_1_2_media_info *info;

    p = malloc(sizeof(struct citp_msex_1_2_mein));
    if (!p) {
        perror("Could not allocate memory for MSEX 1.2 MEIn message");
        return NULL;
    }  

    fill_msex_header(&p->msex_header, buf);
    cur = buf + CITP_MSEX_HEADER_SIZE; 

    p->library_id.level  = *(uint8 *)cur; cur += 1; 
    p->library_id.level1 = *(uint8 *)cur; cur += 1; 
    p->library_id.level2 = *(uint8 *)cur; cur += 1; 
    p->library_id.level3 = *(uint8 *)cur; cur += 1; 

    p->library_count = *(uint16 *)cur; cur += 2; 
    p->media_information = calloc((size_t)p->library_count, sizeof(struct msex_1_2_media_info)); 
    if (!p->media_information) {
        perror("Could not allocate memory for MSEX 1.2 media information");
        exit(EXIT_FAILURE); /* XXX simple for now. */
    }  
    info = p->media_information; 
    for (i=0; i < p->library_count; i++) {
        info->number = *(uint8 *)cur; cur += 1; 
        info->serial_number = *(uint32 *)cur; cur += 4; 
        info->dmx_range_min = *(uint8 *)cur; cur += 1; 
        info->dmx_range_max = *(uint8 *)cur; cur += 1; 
        cur = ucs2str_newcopy(&(info->media_name), cur); 
        cur += sizeof(ucs2); 
        info->media_version_timestamp = *(uint64 *)cur; cur += 8; 
        info->media_width = *(uint16 *)cur; cur += 2; 
        info->media_height = *(uint16 *)cur; cur += 2; 
        info->media_length = *(uint32 *)cur; cur += 4; 
        info->media_fps = *(uint8 *)cur; cur += 1; 
        info++;  
    }

    return p;
}

/* new code */

struct citp_msex_1_0_gelt *parse_msex_1_0_gelt(void *buf)
{
    struct citp_msex_1_0_gelt *p;
    void *cur; 

    p = malloc(sizeof(struct citp_msex_1_0_gelt));
    if (!p) {
        perror("Could not allocate memory for citp_msex_1_0_gelt");
        return NULL;
    }  

    fill_msex_header(&p->msex_header, buf);
    cur = buf + CITP_MSEX_HEADER_SIZE; 

    p->thumbnail_format      = *(uint32 *)cur; cur += 4; 
    p->thumbnail_width       = *(uint16 *)cur; cur += 2; 
    p->thumbnail_height      = *(uint16 *)cur; cur += 2; 
    p->thumbnail_flags       = *(uint8 *)cur;  cur += 1; 
    p->library_type          = *(uint8 *)cur;  cur += 1; 
    p->library_count         = *(uint8 *)cur;  cur += 1; 

    p->library_numbers = malloc(p->library_count);
    if (!p->library_numbers) {
        perror("Could not allocate memory for element numbers"); 
        exit(EXIT_FAILURE); /* XXX simple for now. */
    }
    memcpy(p->library_numbers, cur, p->library_count); 

    return p;
}

struct citp_msex_1_1_gelt *parse_msex_1_1_gelt(void *buf)
{
    struct citp_msex_1_1_gelt *p;
    struct msex_library_id *id;
    void *cur;
    int i; 

    p = malloc(sizeof(struct citp_msex_1_1_gelt));
    if (!p) {
        perror("Could not allocate memory for citp_msex_1_1_gelt");
        return NULL;
    }  

    fill_msex_header(&p->msex_header, buf);
    cur = buf + CITP_MSEX_HEADER_SIZE; 

    p->thumbnail_format      = *(uint32 *)cur; cur += 4; 
    p->thumbnail_width       = *(uint16 *)cur; cur += 2; 
    p->thumbnail_height      = *(uint16 *)cur; cur += 2; 
    p->thumbnail_flags       = *(uint8 *)cur;  cur += 1; 
    p->library_type          = *(uint8 *)cur;  cur += 1; 
    p->library_count         = *(uint8 *)cur;  cur += 1; 

    p->library_ids = malloc(p->library_count * sizeof(struct msex_library_id));
    if (!p->library_ids) {
        perror("Could not allocate memory for library ids"); 
        exit(EXIT_FAILURE); /* XXX simple for now. */
    }

    for (i=0; i< p->library_count; i++) {
        id = p->library_ids + i; 
        id->level  = *(uint8 *)cur; cur += 1; 
        id->level1 = *(uint8 *)cur; cur += 1; 
        id->level2 = *(uint8 *)cur; cur += 1; 
        id->level3 = *(uint8 *)cur; cur += 1; 
    }

    return p;
}

struct citp_msex_1_2_gelt *parse_msex_1_2_gelt(void *buf)
{
    struct citp_msex_1_2_gelt *p;
    struct msex_library_id *id;
    void *cur;
    int i; 

    p = malloc(sizeof(struct citp_msex_1_2_gelt));
    if (!p) {
        perror("Could not allocate memory for citp_msex_1_2_gelt");
        return NULL;
    }  

    fill_msex_header(&p->msex_header, buf);
    cur = buf + CITP_MSEX_HEADER_SIZE; 

    p->thumbnail_format      = *(uint32 *)cur; cur += 4; 
    p->thumbnail_width       = *(uint16 *)cur; cur += 2; 
    p->thumbnail_height      = *(uint16 *)cur; cur += 2; 
    p->thumbnail_flags       = *(uint8 *)cur;  cur += 1; 
    p->library_type          = *(uint8 *)cur;  cur += 1; 
    p->library_count         = *(uint16 *)cur; cur += 2; 

    p->library_ids = malloc(p->library_count * sizeof(struct msex_library_id));
    if (!p->library_ids) {
        perror("Could not allocate memory for library ids"); 
        exit(EXIT_FAILURE); /* XXX simple for now. */
    }

    for (i=0; i< p->library_count; i++) {
        id = p->library_ids + i; 
        id->level  = *(uint8 *)cur; cur += 1; 
        id->level1 = *(uint8 *)cur; cur += 1; 
        id->level2 = *(uint8 *)cur; cur += 1; 
        id->level3 = *(uint8 *)cur; cur += 1; 
    }

    return p;
}

struct citp_msex_1_0_elth *parse_msex_1_0_elth(void *buf)
{
    struct citp_msex_1_0_elth *p;
    void *cur; 

    p = malloc(sizeof(struct citp_msex_1_0_elth));
    if (!p) {
        perror("Could not allocate memory for citp_msex_1_0_elth");
        return NULL;
    }  

    fill_msex_header(&p->msex_header, buf);
    cur = buf + CITP_MSEX_HEADER_SIZE; 
    p->library_type          = *(uint8 *)cur;  cur += 1; 
    p->library_number        = *(uint8 *)cur;  cur += 1; 
    p->thumbnail_format      = *(uint32 *)cur; cur += 4; 
    p->thumbnail_width       = *(uint16 *)cur; cur += 2; 
    p->thumbnail_height      = *(uint16 *)cur; cur += 2; 
    p->thumbnail_buffer_size = *(uint16 *)cur; cur += 2; 

    p->thumbnail_buffer = malloc(p->thumbnail_buffer_size);
    if (!p->thumbnail_buffer) {
        perror("Could not allocate memory for thumbnail buffer"); 
        exit(EXIT_FAILURE); /* XXX simple for now. */
    }
    memcpy(p->thumbnail_buffer, cur, p->thumbnail_buffer_size); 

    return p;
}

struct citp_msex_1_1_elth *parse_msex_1_1_elth(void *buf)
{
    struct citp_msex_1_1_elth *p;
    void *cur; 

    p = malloc(sizeof(struct citp_msex_1_1_elth));
    if (!p) {
        perror("Could not allocate memory for citp_msex_1_1_elth");
        return NULL;
    }  

    fill_msex_header(&p->msex_header, buf);

    cur = buf + CITP_MSEX_HEADER_SIZE; 
    p->library_type          = *(uint8 *)cur;  cur += 1;
    p->library_id.level      = *(uint8 *)cur;  cur += 1;
    p->library_id.level1     = *(uint8 *)cur;  cur += 1;
    p->library_id.level2     = *(uint8 *)cur;  cur += 1;
    p->library_id.level3     = *(uint8 *)cur;  cur += 1;
    p->thumbnail_format      = *(uint32 *)cur; cur += 4;
    p->thumbnail_width       = *(uint16 *)cur; cur += 2;
    p->thumbnail_height      = *(uint16 *)cur; cur += 2;
    p->thumbnail_buffer_size = *(uint16 *)cur; cur += 2;

    p->thumbnail_buffer = malloc(p->thumbnail_buffer_size);
    if (!p->thumbnail_buffer) {
        perror("Could not allocate memory for thumbnail buffer");
        exit(EXIT_FAILURE); /* XXX simple for now. */
    }   
    memcpy(p->thumbnail_buffer, cur, p->thumbnail_buffer_size);

    return p;
}

/* end new code */

struct citp_msex_1_0_geth *parse_msex_1_0_geth(void *buf)
{
    struct citp_msex_1_0_geth *p;
    void *cur; 

    p = malloc(sizeof(struct citp_msex_1_0_geth));
    if (!p) {
        perror("Could not allocate memory for citp_msex_1_0_geth");
        return NULL;
    }  

    fill_msex_header(&p->msex_header, buf);
    cur = buf + CITP_MSEX_HEADER_SIZE; 

    p->thumbnail_format      = *(uint32 *)cur; cur += 4; 
    p->thumbnail_width       = *(uint16 *)cur; cur += 2; 
    p->thumbnail_height      = *(uint16 *)cur; cur += 2; 
    p->thumbnail_flags       = *(uint8 *)cur;  cur += 1; 
    p->library_type          = *(uint8 *)cur;  cur += 1; 
    p->library_number        = *(uint8 *)cur;  cur += 1; 
    p->element_count         = *(uint8 *)cur;  cur += 1; 

    p->element_numbers = malloc(p->element_count);
    if (!p->element_numbers) {
        perror("Could not allocate memory for element numbers"); 
        exit(EXIT_FAILURE); /* XXX simple for now. */
    }
    memcpy(p->element_numbers, cur, p->element_count); 

    return p;
}

struct citp_msex_1_1_geth *parse_msex_1_1_geth(void *buf)
{
    struct citp_msex_1_1_geth *p;
    void *cur; 
    p = malloc(sizeof(struct citp_msex_1_1_geth));
    if (!p) {
        perror("Could not allocate memory for citp_msex_1_1_geth");
        return NULL;
    }  

    fill_msex_header(&p->msex_header, buf);
    cur = buf + CITP_MSEX_HEADER_SIZE; 

    p->thumbnail_format      = *(uint32 *)cur; cur += 4; 
    p->thumbnail_width       = *(uint16 *)cur; cur += 2; 
    p->thumbnail_height      = *(uint16 *)cur; cur += 2; 
    p->thumbnail_flags       = *(uint8 *)cur;  cur += 1; 
    p->library_type          = *(uint8 *)cur;  cur += 1; 
    p->library_id.level      = *(uint8 *)cur;  cur += 1; 
    p->library_id.level1     = *(uint8 *)cur;  cur += 1; 
    p->library_id.level2     = *(uint8 *)cur;  cur += 1; 
    p->library_id.level3     = *(uint8 *)cur;  cur += 1; 
    p->element_count         = *(uint8 *)cur;  cur += 1; 

    p->element_numbers = malloc(p->element_count);
    if (!p->element_numbers) {
        perror("Could not allocate memory for element numbers"); 
        exit(EXIT_FAILURE); /* XXX simple for now. */
    }
    memcpy(p->element_numbers, cur, p->element_count); 


    return p;
}
struct citp_msex_1_2_geth *parse_msex_1_2_geth(void *buf)
{
    struct citp_msex_1_2_geth *p;
    void *cur;

    p = malloc(sizeof(struct citp_msex_1_2_geth));
    if (!p) {
        perror("Could not allocate memory for citp_msex_1_2_geth");
        return NULL;
    }  

    fill_msex_header(&p->msex_header, buf);
    cur = buf + CITP_MSEX_HEADER_SIZE; 

    p->thumbnail_format      = *(uint32 *)cur; cur += 4; 
    p->thumbnail_width       = *(uint16 *)cur; cur += 2; 
    p->thumbnail_height      = *(uint16 *)cur; cur += 2; 
    p->thumbnail_flags       = *(uint8 *)cur;  cur += 1; 
    p->library_type          = *(uint8 *)cur;  cur += 1; 
    p->library_id.level      = *(uint8 *)cur;  cur += 1; 
    p->library_id.level1     = *(uint8 *)cur;  cur += 1; 
    p->library_id.level2     = *(uint8 *)cur;  cur += 1; 
    p->library_id.level3     = *(uint8 *)cur;  cur += 1; 
    p->element_count         = *(uint16 *)cur; cur += 2; 

    p->element_numbers = malloc(p->element_count);
    if (!p->element_numbers) {
        perror("Could not allocate memory for element numbers"); 
        exit(EXIT_FAILURE); /* XXX simple for now. */
    }
    memcpy(p->element_numbers, cur, p->element_count); 


    return p;
}

struct citp_msex_1_0_ethn *parse_msex_1_0_ethn(void *buf)
{
    struct citp_msex_1_0_ethn *p;
    void *cur; 

    p = malloc(sizeof(struct citp_msex_1_0_ethn));
    if (!p) {
        perror("Could not allocate memory for citp_msex_1_0_ethn");
        return NULL;
    }  

    fill_msex_header(&p->msex_header, buf);
    cur = buf + CITP_MSEX_HEADER_SIZE; 
    p->library_type          = *(uint8 *)cur;  cur += 1; 
    p->library_number        = *(uint8 *)cur;  cur += 1; 
    p->element_number        = *(uint8 *)cur;  cur += 1; 
    p->thumbnail_format      = *(uint32 *)cur; cur += 4; 
    p->thumbnail_width       = *(uint16 *)cur; cur += 2; 
    p->thumbnail_height      = *(uint16 *)cur; cur += 2; 
    p->thumbnail_buffer_size = *(uint16 *)cur; cur += 2; 

    p->thumbnail_buffer = malloc(p->thumbnail_buffer_size);
    if (!p->thumbnail_buffer) {
        perror("Could not allocate memory for thumbnail buffer"); 
        exit(EXIT_FAILURE); /* XXX simple for now. */
    }
    memcpy(p->thumbnail_buffer, cur, p->thumbnail_buffer_size); 

    return p;
}

struct citp_msex_1_1_ethn *parse_msex_1_1_ethn(void *buf)
{
    struct citp_msex_1_1_ethn *p;
    void *cur; 

    p = malloc(sizeof(struct citp_msex_1_1_ethn));
    if (!p) {
        perror("Could not allocate memory for citp_msex_1_1_ethn");
        return NULL;
    }  

    fill_msex_header(&p->msex_header, buf);

    cur = buf + CITP_MSEX_HEADER_SIZE; 
    p->library_type          = *(uint8 *)cur;  cur += 1;
    p->library_id.level      = *(uint8 *)cur;  cur += 1;
    p->library_id.level1     = *(uint8 *)cur;  cur += 1;
    p->library_id.level2     = *(uint8 *)cur;  cur += 1;
    p->library_id.level3     = *(uint8 *)cur;  cur += 1;
    p->element_number        = *(uint8 *)cur;  cur += 1;
    p->thumbnail_format      = *(uint32 *)cur; cur += 4;
    p->thumbnail_width       = *(uint16 *)cur; cur += 2;
    p->thumbnail_height      = *(uint16 *)cur; cur += 2;
    p->thumbnail_buffer_size = *(uint16 *)cur; cur += 2;

    p->thumbnail_buffer = malloc(p->thumbnail_buffer_size);
    if (!p->thumbnail_buffer) {
        perror("Could not allocate memory for thumbnail buffer");
        exit(EXIT_FAILURE); /* XXX simple for now. */
    }   
    memcpy(p->thumbnail_buffer, cur, p->thumbnail_buffer_size);

    return p;
}

struct citp_msex_rqst *parse_msex_rqst(void *buf)
{
    struct citp_msex_rqst *p;
    void *cur; 

    p = malloc(sizeof(struct citp_msex_rqst));
    if (!p) {
        perror("Could not allocate memory for citp_msex_rqst");
        return NULL;
    }  

    fill_msex_header(&p->msex_header, buf);
    cur = buf + CITP_MSEX_HEADER_SIZE; 

    p->source_identifier = *(uint16 *)cur; cur += 2;
    p->frame_format      = *(uint32 *)cur; cur += 4;
    p->frame_width       = *(uint16 *)cur; cur += 2;
    p->frame_height      = *(uint16 *)cur; cur += 2;
    p->fps               = *(uint8  *)cur; cur += 1;
    p->timeout           = *(uint8  *)cur; cur += 1;

    return p;
}

struct citp_msex_1_0_stfr *parse_msex_1_0_stfr(void *buf)
{
    struct citp_msex_1_0_stfr *p;
    void *cur; 

    p = malloc(sizeof(struct citp_msex_1_0_stfr));
    if (!p) {
        perror("Could not allocate memory for citp_msex_1_0_stfr");
        return NULL;
    }  

    fill_msex_header(&p->msex_header, buf);
    cur = buf + CITP_MSEX_HEADER_SIZE; 

    p->source_identifier = *(uint16 *)cur; cur += 2;
    p->frame_format      = *(uint32 *)cur; cur += 4;
    p->frame_width       = *(uint16 *)cur; cur += 2;
    p->frame_height      = *(uint16 *)cur; cur += 2;
    p->frame_buffer_size = *(uint16 *)cur; cur += 2;

    p->frame_buffer = malloc(p->frame_buffer_size);
    if (!p->frame_buffer) {
        perror("Could not allocate memory for frame buffer");
        exit(EXIT_FAILURE); /* XXX simple for now. */
    }   
    memcpy(p->frame_buffer, cur, p->frame_buffer_size);

    return p;
}

struct citp_msex_1_2_stfr *parse_msex_1_2_stfr(void *buf)
{
    struct citp_msex_1_2_stfr *p;
    void *cur; 

    p = malloc(sizeof(struct citp_msex_1_2_stfr));
    if (!p) {
        perror("Could not allocate memory for citp_msex_1_2_stfr");
        return NULL;
    }  

    fill_msex_header(&p->msex_header, buf);
    cur = buf + CITP_MSEX_HEADER_SIZE; 

    memcpy((void *)&(p->media_server_uuid), cur, 36); 
    cur += 36;  

    p->source_identifier = *(uint16 *)cur; cur += 2;
    p->frame_format      = *(uint32 *)cur; cur += 4;
    p->frame_width       = *(uint16 *)cur; cur += 2;
    p->frame_height      = *(uint16 *)cur; cur += 2;
    p->frame_buffer_size = *(uint16 *)cur; cur += 2;

    p->frame_buffer = malloc(p->frame_buffer_size);
    if (!p->frame_buffer) {
        perror("Could not allocate memory for frame buffer");
        exit(EXIT_FAILURE); /* XXX simple for now. */
    }   
    memcpy(p->frame_buffer, cur, p->frame_buffer_size);

    return p;
}

