/* 
 * create.c - Functions for creating new CITP messages. 
 * Jeremy Madea <jeremymadea@gmail.com>
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "citptypes.h"
#include "ucsutils.h"
#include "create.h"

/* INTERFACE (see create.h) 
struct citp_pinf_pnam *create_pinf_pnam(ucs1 *name);
struct citp_pinf_ploc *create_pinf_ploc(uint16 port, ucs1 *type, ucs1* name, ucs1 *state);
*/

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


void citp_set_header(struct citp_header *p, uint16 request, uint16 count, uint16 part, uint32 type)
{
    p->cookie             = CITP_COOKIE_CITP; 
    p->version_major      = CITP_MAJOR_VERSION;
    p->version_minor      = CITP_MINOR_VERSION;
    p->request_index      = request;
    p->message_part_count = count;
    p->message_part       = part;
    p->content_type       = type; 
    return;
}

void citp_set_size(struct citp_header *p, uint32 size) 
{
    p->message_size = size; 
}


struct citp_pinf_pnam *citp_create_pinf_pnam(ucs1 *name)
{
    struct citp_pinf_pnam *p;
    size_t size = CITP_PINF_HEADER_SIZE; 

    p = malloc(sizeof(struct citp_pinf_pnam));
    if (!p) {
        perror("Could not allocate memory for citp_pinf_pnam");
        return NULL;
    }

    citp_set_header(&(p->pinf_header.citp_header), 0, 1, 0, CITP_COOKIE_PINF); 
    p->pinf_header.content_type = CITP_COOKIE_PINF_PNAM; 

    size += strlen((char *)name) + 1; 
    (void)ucs1str_newcopy(&(p->name), name); 

    citp_set_size(&p->pinf_header.citp_header, (uint32)size);
    return p;
}

struct citp_pinf_ploc *citp_create_pinf_ploc(uint16 port, ucs1 *type, ucs1* name, ucs1 *state)
{
    struct citp_pinf_ploc *p;
    size_t size = CITP_PINF_HEADER_SIZE; 

    p = malloc(sizeof(struct citp_pinf_ploc));
    if (!p) {
        perror("Could not allocate memory for citp_pinf_ploc");
        return NULL;
    }  
    citp_set_header(&p->pinf_header.citp_header, 0, 1, 0, CITP_COOKIE_PINF); 
    p->pinf_header.content_type = CITP_COOKIE_PINF_PLOC; 

    size += 2; /* for port */
    size += strlen((char *)type) + 1; 
    size += strlen((char *)name) + 1; 
    size += strlen((char *)state) + 1; 

    p->listening_tcp_port = port; 

    (void)ucs1str_newcopy(&p->type, type); 
    (void)ucs1str_newcopy(&p->name, name); 
    (void)ucs1str_newcopy(&p->state, state); 

    citp_set_size(&p->pinf_header.citp_header, (uint32)size);
    return p;
}
/*
 * struct citp_msex_cinf
 * {
 *     struct citp_msex_header msex_header;
 *     uint8                   supported_msex_versions_count;  // Number of MSEX version pairs. 
 *     uint16                  *supported_msex_versions;       // MSB = Major version, LSB = Minor version. 
 *     uint32                  *future_message_data;           // A hint that future versions may contain more data. 
 * };
*/
struct citp_msex_cinf *citp_create_msex_cinf(uint8 count, const uint16 *versions) 
{
    struct citp_msex_cinf *p; 
    size_t size = CITP_MSEX_HEADER_SIZE;
    int i; 

    p = malloc(sizeof(struct citp_msex_cinf)); 
    if (!p) { 
        perror("Could not allocate memory for citp_msex_cinf");
        return NULL;
    }
  
    citp_set_header(&p->msex_header.citp_header, 0, 1, 0, CITP_COOKIE_MSEX); 
    p->msex_header.content_type = CITP_COOKIE_MSEX_CINF; 
    p->msex_header.version_major = 1; 
    p->msex_header.version_minor = 2; 
    p->supported_msex_versions_count = count; 
    p->future_message_data = NULL; 
    size += 5; 
    size += count * 2; 
    
    if (!(p->supported_msex_versions = malloc(count * 2))) {  
        perror("Could not allocate memory for versions in citp_msex_cinf");
        return NULL;
    }
   
    for (i=0; i<count; i++) { 
        *(p->supported_msex_versions + i) = *(versions + i);
    } 

    citp_set_size(&p->msex_header.citp_header, (uint32)size);
    return p;
    
}

/* 
 * struct citp_msex_1_1_geli
 * {
 *     struct citp_msex_header msex_header;    
 *     uint8                   library_type; 
 *     struct msex_library_id  library_parent_id; 
 *     uint8                   library_count;
 *     uint8                   *library_numbers;
 * };
 */
struct citp_msex_1_1_geli *citp_create_msex_1_1_geli(uint8 type, const struct msex_library_id *id, uint8 count, const uint8 *numbers)
{
    struct citp_msex_1_1_geli *p; 
    size_t size = CITP_MSEX_HEADER_SIZE;
    int i; 

    p = malloc(sizeof(struct citp_msex_1_1_geli)); 
    if (!p) { 
        perror("Could not allocate memory for citp_msex_1_1_geli");
        return NULL;
    }
  
    citp_set_header(&p->msex_header.citp_header, 0, 1, 0, CITP_COOKIE_MSEX); 
    p->msex_header.content_type = CITP_COOKIE_MSEX_GELI; 
    p->msex_header.version_major = 1; 
    p->msex_header.version_minor = 1; 

    p->library_type = type; 
    p->library_parent_id.level = id->level; 
    p->library_parent_id.level1 = id->level1; 
    p->library_parent_id.level2 = id->level2; 
    p->library_parent_id.level3 = id->level3; 
    p->library_count = count; 
    size += 7; 
    size += count; 
   
    if (count == 0) { 
        p->library_numbers = NULL; 
    } else {  
        if (!(p->library_numbers = malloc(count))) {  
            perror("Could not allocate memory for library_numbers in citp_msex_1_1_geli");
            return NULL;
        }
        for (i=0; i<count; i++) { 
            *(p->library_numbers + i) = *(numbers + i);
        }
    } 

printf("geli = %p\n", p);
    citp_set_size(&p->msex_header.citp_header, (uint32)size);
    return p;
}

/*
 * struct citp_msex_1_2_geli
 * {
 *     struct citp_msex_header msex_header;  
 *     uint8                   library_type; 
 *     struct msex_library_id  library_parent_id; 
 *     uint16                  library_count;
 *     uint8                   *library_numbers;
 * };
 */
struct citp_msex_1_2_geli *citp_create_msex_1_2_geli(uint8 type, const struct msex_library_id *id, uint16 count, const uint8 *numbers)
{
    struct citp_msex_1_2_geli *p; 
    size_t size = CITP_MSEX_HEADER_SIZE;
    int i; 

    p = malloc(sizeof(struct citp_msex_1_2_geli)); 
    if (!p) { 
        perror("Could not allocate memory for citp_msex_1_2_geli");
        return NULL;
    }
  
    citp_set_header(&p->msex_header.citp_header, 0, 1, 0, CITP_COOKIE_MSEX); 
    p->msex_header.content_type = CITP_COOKIE_MSEX_GELI; 
    p->msex_header.version_major = 1; 
    p->msex_header.version_minor = 2; 

    p->library_type = type; 
    p->library_parent_id.level = id->level; 
    p->library_parent_id.level1 = id->level1; 
    p->library_parent_id.level2 = id->level2; 
    p->library_parent_id.level3 = id->level3; 
    p->library_count = count; 
    size += 7; 
    size += count; 
    
    if (count == 0) { 
        p->library_numbers = NULL; 
    } else {  
        if (!(p->library_numbers = malloc(count))) {  
            perror("Could not allocate memory for library_numbers in citp_msex_1_2_geli");
            return NULL;
        }
       
        for (i=0; i<count; i++) { 
            *(p->library_numbers + i) = *(numbers + i);
        }
    }
 
    citp_set_size(&p->msex_header.citp_header, (uint32)size);
    return p;
}

struct citp_msex_gvsr *citp_create_msex_gvsr()
{
    struct citp_msex_gvsr *p; 
    size_t size = CITP_MSEX_HEADER_SIZE;

    p = malloc(sizeof(struct citp_msex_gvsr)); 
    if (!p) { 
        perror("Could not allocate memory for citp_msex_gvsr");
        return NULL;
    }
  
    citp_set_header(&p->msex_header.citp_header, 0, 1, 0, CITP_COOKIE_MSEX); 
    p->msex_header.content_type = CITP_COOKIE_MSEX_GVSR; 
    p->msex_header.version_major = 1; 
    p->msex_header.version_minor = 2; 

    citp_set_size(&p->msex_header.citp_header, (uint32)size);
printf("gvsr = %p (before return)\n", p);
    return p;
}
