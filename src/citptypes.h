/******************************************************************************
 * libcitp - Controller Interface Transport Protocol (CITP) library
 * citptypes.h - constants, datatypes, and macros
 *
 *
 * Copyright (C) 2013 Jeremy Madea 
 */
#ifndef _CITP_CITPTYPES_H_
#define _CITP_CITPTYPES_H_

#define CITP_MAJOR_VERSION 1
#define CITP_MINOR_VERSION 0

typedef signed char             int8;
typedef short                   int16;
typedef int                     int32;
typedef long long int           int64;
typedef unsigned char           uint8;
typedef unsigned short          uint16;
typedef unsigned int            uint32;
typedef unsigned long long int  uint64;
typedef unsigned char           ucs1;
typedef unsigned short          ucs2;

/* libcitp-specific error codes. These are not defined in spec. */
#define CITP_EBIGMSG -1 
#define CITP_EUNKNOWN -2

/* 
 * Content Type "cookies"
 */

#define CITP_COOKIE_CITP         0x50544943 /* "CITP" */
#define CITP_COOKIE_PINF         0x464e4950 /* "PINF" */
#define CITP_COOKIE_PINF_PNAM    0x6d614e50 /* "PNam" */
#define CITP_COOKIE_PINF_PLOC    0x636f4c50 /* "PLoc" */
#define CITP_COOKIE_SDMX         0x584d4453 /* "SDMX" */
#define CITP_COOKIE_SDMX_ENID    0x456e4964 /* "EnId" */
#define CITP_COOKIE_SDMX_UNAM    0x6d614e55 /* "UNam" */
#define CITP_COOKIE_SDMX_CHBK    0x6b426843 /* "ChBk" */
#define CITP_COOKIE_SDMX_SXSR    0x72535853 /* "SXSr" */
#define CITP_COOKIE_MSEX         0x5845534d /* "MSEX" */
#define CITP_COOKIE_MSEX_CINF    0x666e4943 /* "CInf" */
#define CITP_COOKIE_MSEX_SINF    0x666e4953 /* "SInf" */
#define CITP_COOKIE_MSEX_LSTA    0x6174534c /* "LSta" */
#define CITP_COOKIE_MSEX_NACK    0x6b63614e /* "Nack" */
#define CITP_COOKIE_MSEX_GVSR    0x72535647 /* "GVSr" */
#define CITP_COOKIE_MSEX_GELI    0x494c4547 /* "GELI" */
#define CITP_COOKIE_MSEX_ELIN    0x6e494c45 /* "ELIn" */
#define CITP_COOKIE_MSEX_GEIN    0x6e494547 /* "GEIn" */
#define CITP_COOKIE_MSEX_MEIN    0x6e49454d /* "MEIn" */
#define CITP_COOKIE_MSEX_GELT    0x544c4547 /* "GELT" */
#define CITP_COOKIE_MSEX_ELTH    0x68544c45 /* "ELTh" */
#define CITP_COOKIE_MSEX_GETH    0x68544547 /* "GETh" */
#define CITP_COOKIE_MSEX_ETHN    0x6e685445 /* "EThn" */
#define CITP_COOKIE_MSEX_VSRC    0x63725356 /* "VSrc" */
#define CITP_COOKIE_MSEX_RQST    0x74537152 /* "RqSt" */
#define CITP_COOKIE_MSEX_STFR    0x72467453 /* "StFr" */

/* Partially Implemented */
#define CITP_COOKIE_MSEX_GLEI    0x49454c47 /* "GLEI" */
#define CITP_COOKIE_MSEX_EEIN    0x6e494545 /* "EEIn" */
#define CITP_COOKIE_MSEX_ELUP    0x70554c45 /* "ELUp" */



/* UNIMPLEMENTED content types */

#define CITP_COOKIE_FPTC         0x43545046 /* "FPTC" */
#define CITP_COOKIE_FPTC_PTCH    0x68637450 /* "Ptch" */
#define CITP_COOKIE_FPTC_UPTC    0x63745055 /* "UPtc" */
#define CITP_COOKIE_FPTC_SPTC    0x63745053 /* "SPtc" */
#define CITP_COOKIE_FSEL         0x4c455346 /* "FSEL" */
#define CITP_COOKIE_FSEL_SELE    0x656c6553 /* "Sele" */
#define CITP_COOKIE_FSEL_DESE    0x65536544 /* "DeSe" */
#define CITP_COOKIE_FINF         0x464e4946 /* "FINF" */
#define CITP_COOKIE_FINF_SFRA    0x61724653 /* "SFra" */
#define CITP_COOKIE_FINF_FRAM    0x6d617246 /* "Fram" */
#define CITP_COOKIE_FINF_SPOS    0x736f5053 /* "SPos" */ /* PRELIMINARY in 1.2 spec */
#define CITP_COOKIE_FINF_POSI    0x69736f50 /* "Posi" */ /* PRELIMINARY in 1.2 spec */
#define CITP_COOKIE_FINF_LSTA    0x6174534c /* "LSta" */ /* PRELIMINARY in 1.2 spec */
#define CITP_COOKIE_OMEX         0x58454d4f /* "OMEX" */ /* PRELIMINARY in 1.2 spec */
#define CITP_COOKIE_OMEX_SDDS    0x53444453 /* "SDDS" */ /* PRELIMINARY in 1.2 spec */
#define CITP_COOKIE_OMEX_CDDS    0x53444443 /* "CDDS" */ /* PRELIMINARY in 1.2 spec */

/*
 *  CITP - Base Layer
 */
struct citp_header 
{
    uint32      cookie;                 /* set to "CITP" */
    uint8       version_major;          /* set to 1 */
    uint8       version_minor;          /* set to 0 */
    union 
    {
        uint16  request_index;
        uint16  in_response_to;
    };
    uint32      message_size;           /* size of message including this header */
    uint16      message_part_count;     /* number of message fragments */
    uint16      message_part;           /* index of this message fragment */
    uint32      content_type;           /* cookie identifying 2nd layer content */
};

#define CITP_HEADER_SIZE 20

/*
 *  CITP/PINF - Peer Information Layer
 */

#define CITP_PINF_MULTICAST_IP   "224.0.0.180"
#define CITP_PINF_MULTICAST_PORT 4809

/* ********* PINF Auxillary Structures ********* */ 

/*
 * All PINF messages start with a PINF header. 
 * citp_header.content_type = CITP_COOKIE_PINF 
 */
struct citp_pinf_header 
{ 
    struct citp_header      citp_header;    
    uint32                  content_type;   /* A cookie defining which PINF message it is.  */
};

#define CITP_PINF_HEADER_SIZE 24

/* ********* PINF Messages ********* */ 

/*
 * PINF PNam - "Peer Name" message.
 * pinf.header.content_type = CITP_COOKIE_PINF_PNAM *
 */
struct citp_pinf_pnam 
{ 
  struct citp_pinf_header   pinf_header;  
  ucs1                      *name;        /* null terminated display name */
}; 

/*
 * PINF PLoc - "Peer Location" message. 
 * pinf.header.content_type = CITP_COOKIE_PINF_PLOC 
 */
struct citp_pinf_ploc 
{ 
  struct citp_pinf_header   pinf_header;        
  uint16                    listening_tcp_port; /* Peer's port or 0 if not listening. */ 
  ucs1                      *type;              /* "LightingConsole", "MediaServer", "Visualizer", "OperationHub" */
  ucs1                      *name;              /* The display name of the peer. */
  ucs1                      *state;             /* The display state of the peer. Any descriptive string. */ 
};


/*
 *  CITP, SDMX - Send DMX Layer
 */

/* DMX Connection String Macros */

/* ArtNet "ArtNet/<net>/<universe>/<channel>" */
/* "ArtNet/0/0/1" - The first channel of the first universe on the first network. */
#define CITP_DMX_CONNECTION_ARTNET   tr("ArtNet/%1/%2/%3")

/* Avab IPX "AvabIPX/<net>/<universe>/<channel>" */
/* "AvabIPX/0/0/1" - The first channel of the first universe on the first network. */
#define CITP_DMX_CONNECTION_AVAB     tr("AvabIPX/%1/%2/%3")

/* BSR E1.31 "BSRE1.31/<universe>/<channel>" */
/* "BSRE1.31/0/1" - The first channel of the first universe. */
#define CITP_DMX_CONNECTION_E131     tr("BSRE1.31/%1/%2")

/* ETC Net2 "ETCNet2/<channel>" */
/* "ETCNet2/1" - The first ETCNet2 channel. */
#define CITP_DMX_CONNECTION_ETCNET2  tr("ETCNet2/%1")


/* ********* SDMX Auxillary structures ********* */ 

/*
 * All SDMX messages begin with an SDMX header.
 * citp_header.content_type = CITP_COOKIE_SDMX 
 */
struct citp_sdmx_header 
{ 
    struct citp_header      citp_header;        
    uint32                  content_type;       /* A cookie defining which SDMX message it is.  */
}; 

#define CITP_SDMX_HEADER_SIZE 24


/* ********* SDMX messages ********* */ 

/*
 * SDMX EnId - "Encryption Identifier" message.
 * sdmx_header.content_type = CITP_COOKIE_SDMX_ENID 
 */
struct citp_sdmx_enid 
{ 
    struct citp_sdmx_header sdmx_header;        
    ucs1                    *identifier;        /* Encryption scheme identifier. */
}; 

/*
 * SDMX UNam - "Universe Name" message.
 * sdmx_header.content_type = CITP_COOKIE_SDMX_UNAM 
 */
struct citp_sdmx_unam 
{ 
    struct citp_sdmx_header sdmx_header;        
    uint8                   universe_index;     /* 0-based index of the universe. */
    ucs1                    *universe_name;     /* Name of the universe. */         
}; 

/*
 * SDMX ChBk - "Channel Block" message.
 * sdmx_header.content_type = CITP_COOKIE_SDMX_CHBK 
 */
struct citp_sdmx_chbk 
{ 
    struct citp_sdmx_header sdmx_header;        
    uint8                   blind;              /* 1 for blind preview dmx, 0 otherwise.  */
    uint8                   universe_index;     /* 0-based index of the universe. */
    uint16                  first_channel;      /* 0-based index of first channel in the universe. */
    uint16                  channel_count;      /* Number of channels. */
    uint8                   *channel_levels;    /* Raw channel levels. */
}; 

/*
 * SDMX SXSr - "Set eXternal Source" message. 
 * sdmx_header.content_type = CITP_COOKIE_SDMX_SXSR 
 */
struct citp_sdmx_sxsr
{ 
    struct citp_sdmx_header sdmx_header;            
    ucs1                    *connection_string;     /* DMX connection string. See below. */
};



/* 
 *  CITP/MSEX - Media Server Exchange Layer 
 */

/* MSEX Versions */
#define CITP_MSEX_VERSION_1_0 0x0100
#define CITP_MSEX_VERSION_1_1 0x0101
#define CITP_MSEX_VERSION_1_2 0x0102

/* Library status constants */
#define MSEX_LIBRARY_STATUS_MEDIAPLAYING            0x0001
#define MSEX_LIBRARY_STATUS_MEDIAPLAYBACKREVERSE    0x0002
#define MSEX_LIBRARY_STATUS_MEDIAPLAYBACKLOOPING    0x0004 
#define MSEX_LIBRARY_STATUS_MEDIAPLAYBACKBOUNCING   0x0008 
#define MSEX_LIBRARY_STATUS_MEDIAPLAYBACKRANDOM     0x0010 
#define MSEX_LIBRARY_STATUS_MEDIAPAUSED             0x0020 

/* Image Format constants. */
#define MSEX_IMAGE_FORMAT_RGB8  0x38424752 /* "RGB8"  */ /* Byte order is BGR for MSEX 1.0 */
#define MSEX_IMAGE_FORMAT_PNG   0x00474e50 /* "PNG\0" */
#define MSEX_IMAGE_FORMAT_JPEG  0x4745504a /* "JPEG"  */

/* MSEX Element types */
#define MSEX_ELEMENT_TYPE_MEDIA  1 /* Media (images & video) */ 
#define MSEX_ELEMENT_TYPE_FX     2 /* Effects */
#define MSEX_ELEMENT_TYPE_CUES   3 /* Cues */
#define MSEX_ELEMENT_TYPE_XFADES 4 /* Crossfades */
#define MSEX_ELEMENT_TYPE_MASKS  5 /* Masks */
#define MSEX_ELEMENT_TYPE_BLENDS 6 /* Blend presets */
#define MSEX_ELEMENT_TYPE_FXPRE  7 /* Effect presets */ 
#define MSEX_ELEMENT_TYPE_IMGPRE 8 /* Image presets */
#define MSEX_ELEMENT_TYPE_3DMESH 9 /* 3Dmeshes */

/* MSEX Thumbnail Flags */
#define MSEX_THUMB_KEEP_RATIO 0x01

/* MSEX Update Flags */
#define MSEX_UPDATE_ELTS_UPDATED      0x01
#define MSEX_UPDATE_ELTS_ADDREM       0x02
#define MSEX_UPDATE_LIBS_UPDATED      0x04
#define MSEX_UPDATE_LIBS_ADDREM       0x08
#define MSEX_UPDATE_ALL_ELTS_AFFECTED 0x10
#define MSEX_UPDATE_ALL_LIBS_AFFECTED 0x20


/* ********* MSEX Auxillary structures ********* */ 

/*
 * MSEX library IDs are used in several MSEX 1.1 and 1.2 messages. 
 *
 */
struct msex_library_id 
{
    uint8   level;  /* 0 - 3*/
    uint8   level1; /* sublevel 1 spec when depth >= 1 */
    uint8   level2; /* sublevel 2 spec when depth >= 2 */
    uint8   level3; /* sublevel 3 spec when depth == 3 */
};

/*
 * All MSEX messages begin with an MSEX header. 
 * citp_header.content_type = CITP_COOKIE_MSEX 
 */
struct citp_msex_header
{
    struct citp_header  citp_header;        
    uint8               version_major;
    uint8               version_minor;
    uint32              content_type;
};

#define CITP_MSEX_HEADER_SIZE 26

/* ********* MSEX messages ********* */

/*
 * MSEX CInf - "Client Information" messages.
 * msex_header.content_type = CITP_COOKIE_MSEX_CINF 
 */
struct citp_msex_cinf
{
    struct citp_msex_header msex_header;                    
    uint8                   supported_msex_versions_count;  /* Number of MSEX version pairs. */
    uint16                  *supported_msex_versions;       /* MSB = Major version, LSB = Minor version. */
    uint32                  *future_message_data;           /* A hint that future versions may contain more data. */
};


/*
 * MSEX SInf - "Server Information" messages.
 * msex_header.content_type = CITP_COOKIE_MSEX_SINF 
 */

struct msex_layer_info 
{ 
    ucs1    *dmx_source; 
};

struct citp_msex_1_0_sinf
{
    struct citp_msex_header msex_header;    
    ucs2                    *product_name;
    uint8                   product_version_major; 
    uint8                   product_version_minor; 
    uint8                   layer_count;
    struct msex_layer_info  *layer_information;
};

struct citp_msex_1_2_sinf
{
    struct citp_msex_header msex_header;    
    ucs1                    uuid[36];
    ucs2                    *product_name;
    uint8                   product_version_major; 
    uint8                   product_version_minor; 
    uint8                   product_version_bugfix;
    uint8                   supported_msex_versions_count; 
    uint16                  *supported_msex_versions;
    uint16                  supported_library_types;
    uint8                   thumbnail_formats_count; 
    uint32                  *thumbnail_formats;
    uint8                   stream_formats_count; 
    uint32                  *stream_formats;
    uint8                   layer_count; 
    struct msex_layer_info  *layer_information; 
};


/* 
 * MSEX Nack
 *
 */

struct citp_msex_nack
{
    struct citp_msex_header msex_header;            /* msex_header.content_type = CITP_COOKIE_MSEX_NACK */
    uint32                  received_content_type;  /* MSEX cookie of the message type being NACKed */
};


/* 
 * MSEX LSta "Layer Status" messages.
 * msex_header.content_type = CITP_COOKIE_MSEX_LSTA 
 *   MSEX version 1.0 and 1.1 use MSEX 1.0 layer status messages.
 *   MSEX version 1.2 uses an updated layer status message
 *
 */

struct msex_1_0_layer_status 
{
    uint8   layer_number;               /* 0-based layer number corresponds to layers in SInf message. */
    uint8   physical_output;            /* Current video output index (0-based.) */
    uint8   media_library_number; 
    uint8   media_number;
    ucs2    *media_name;               
    uint32  media_position;             /* media position in frames */
    uint32  media_length;               /* media length in frames */
    uint8   media_fps;                  /* media resolution in frames per second */
    uint32  layer_status_flags;         /* Only MSEX_LIBRARY_STATUS_MEDIAPLAYING */
};

struct citp_msex_1_0_lsta
{
    struct citp_msex_header         msex_header;    
    uint8                           layer_count;    /* number of layer status blocks that follow. */
    struct msex_1_0_layer_status    *layer_status;
};


struct msex_1_2_layer_status 
{
    uint8                   layer_number;       /* 0-based layer number corresponds to layers in SInf message. */
    uint8                   physical_output;    /* Current video output index (0-based.) */
    uint8                   media_library_type; 
    struct msex_library_id  media_library_id;
    uint8                   media_number;
    ucs2                    *media_name;
    uint32                  media_position;     /* media position in frames */
    uint32                  media_length;       /* media length in frames */
    uint8                   media_fps;          /* media resolution in frames per second */
    uint32                  layer_status_flags; /* MSEX_LIBRARY_STATUS_* */
}; 

struct citp_msex_1_2_lsta
{
    struct citp_msex_header         msex_header;    
    uint8                           layer_count;    /* number of layer status blocks that follow. */
    struct msex_1_2_layer_status    *layer_status;
};


/* 
 * MSEX GVSr "Get Video Source" message. 
 * msex_header.content_type = CITP_COOKIE_MSEX_GVSR 
 *
 */

struct citp_msex_gvsr
{
    struct citp_msex_header msex_header;    
};

/*
 * MSEX VSrc "Video Source" message
 * msex_header.content_type = CITP_COOKIE_MSEX_VSRC
 *
 */

/* vsrc source_information auxillary struct. */
struct vsrc_source_information 
{ 
    uint16  source_identifier; 
    ucs2   *source_name; 
    uint8   physical_output; 
    uint8   layer_number; 
    uint16  flags; 
    uint16  width; 
    uint16  height; 
};

struct citp_msex_vsrc
{
    struct  citp_msex_header        msex_header; 
    uint16                          source_count; 
    struct vsrc_source_information  *source_information;
};



/*
 * MSEX GELI - "Get Element Library Information" messages.
 * msex_header.content_type = CITP_COOKIE_MSEX_GELI 
 *
 */

struct citp_msex_1_0_geli
{
    struct citp_msex_header msex_header;    
    uint8                   library_type;
    uint8                   library_count;
    uint8                   *library_numbers;
};

struct citp_msex_1_1_geli
{
    struct citp_msex_header msex_header;    
    uint8                   library_type; 
    struct msex_library_id  library_parent_id; 
    uint8                   library_count;
    uint8                   *library_numbers;
};

struct citp_msex_1_2_geli
{
    struct citp_msex_header msex_header;  
    uint8                   library_type; 
    struct msex_library_id  library_parent_id; 
    uint16                  library_count;
    uint8                   *library_numbers;
};


/*
 * MSEX ElIn - "Element Library Information" messages.
 * msex_header.content_type = CITP_COOKIE_MSEX_ELIN 
 */

struct msex_1_0_element_library_info 
{ 
    uint8   number; 
    uint8   dmx_range_min; 
    uint8   dmx_range_max; 
    ucs2    *name;
    uint8   element_count;
};

struct citp_msex_1_0_elin 
{
    struct citp_msex_header                 msex_header;    
    uint8                                   library_type; 
    uint8                                   library_count;
    struct msex_1_0_element_library_info    *element_library_information; 
}; 



struct msex_1_1_element_library_info 
{ 
    struct msex_library_id  id; 
    uint8                   dmx_range_min; 
    uint8                   dmx_range_max; 
    ucs2                    *name;
    uint8                   library_count;
    uint8                   element_count;
};

struct citp_msex_1_1_elin 
{
    struct citp_msex_header                 msex_header;    
    uint8                                   library_type; 
    uint8                                   library_count;
    struct msex_1_1_element_library_info    *element_library_information; 

}; 


struct msex_1_2_element_library_info 
{ 
    struct msex_library_id  id; 
    uint32                  serial_number;
    uint8                   dmx_range_min; 
    uint8                   dmx_range_max; 
    ucs2                    *name;
    uint16                  library_count;
    uint16                  element_count;
}; 

struct citp_msex_1_2_elin 
{
    struct citp_msex_header                 msex_header;    
    uint8                                   library_type; 
    uint16                                  library_count;
    struct msex_1_2_element_library_info    *element_library_information; 

}; 

/*
 * MSEX GEIn - "Get Element Information" messages. 
 * msex_header.content_type = CITP_COOKIE_MSEX_GEIN 
 */

struct citp_msex_1_0_gein
{
    struct citp_msex_header msex_header;    
    uint8                   library_type; 
    uint8                   library_number; 
    uint8                   element_count;
    uint8                   *element_numbers;
};

struct citp_msex_1_1_gein
{
    struct citp_msex_header msex_header;    
    uint8                   library_type; 
    struct msex_library_id  library_id; 
    uint8                   element_count;
    uint8                   *element_numbers;
};

struct citp_msex_1_2_gein
{
    struct citp_msex_header msex_header;    
    uint8                   library_type; 
    struct msex_library_id  library_id; 
    uint16                  element_count;
    uint8                   *element_numbers;
};


/*
 * MSEX MeIn - "Media Information" messages. 
 * msex_header.content_type = CITP_COOKIE_MSEX_MEIN 
 *
 */

struct msex_1_0_media_info 
{ 
    uint8       number; 
    uint8       dmx_range_min; 
    uint8       dmx_range_max; 
    ucs2        *media_name;
    uint64      media_version_timestamp;
    uint16      media_width; 
    uint16      media_height;
    uint32      media_length;
    uint8       media_fps;
};

struct citp_msex_1_0_mein
{
    struct citp_msex_header msex_header;    
    uint8                       library_number; 
    uint8                       library_count; 
    struct msex_1_0_media_info  *media_information; 
};

struct citp_msex_1_1_mein
{
    struct citp_msex_header     msex_header;    
    struct msex_library_id      library_id; 
    uint8                       library_count; 
    struct msex_1_0_media_info  *media_information; 
};


struct msex_1_2_media_info  
{ 
    uint8       number; 
    uint32      serial_number;
    uint8       dmx_range_min; 
    uint8       dmx_range_max; 
    ucs2        *media_name;
    uint64      media_version_timestamp;
    uint16      media_width; 
    uint16      media_height;
    uint32      media_length;
    uint8       media_fps;
};

struct citp_msex_1_2_mein
{
    struct citp_msex_header msex_header;    
    struct msex_library_id  library_id; 
    uint16                  library_count; 
    struct msex_1_2_media_info  *media_information; 
};


/* MSEX GELT - "Get Element Library Thumbnail" messages. 
 * msex_header.content_type = CITP_COOKIE_MSEX_GELT
 *
 */


struct citp_msex_1_0_gelt
{
    struct citp_msex_header msex_header;    
    uint32                  thumbnail_format;
    uint16                  thumbnail_width; 
    uint16                  thumbnail_height; 
    uint8                   thumbnail_flags;
    uint8                   library_type; 
    uint8                   library_count; 
    uint8                   *library_numbers; 
};

struct citp_msex_1_1_gelt
{
    struct citp_msex_header msex_header;    
    uint32                  thumbnail_format;
    uint16                  thumbnail_width; 
    uint16                  thumbnail_height; 
    uint8                   thumbnail_flags;
    uint8                   library_type; 
    uint8                   library_count; 
    struct msex_library_id  *library_ids; 
};

struct citp_msex_1_2_gelt
{
    struct citp_msex_header msex_header;    
    uint32                  thumbnail_format;
    uint16                  thumbnail_width; 
    uint16                  thumbnail_height; 
    uint8                   thumbnail_flags;
    uint8                   library_type; 
    uint16                  library_count; 
    struct msex_library_id  *library_ids; 
};

/*
 * MSEX ELTh - "Element Library Thumbnail" messages.
 * msex_header.content_type = CITP_COOKIE_MSEX_ELTH 
 */
struct citp_msex_1_0_elth
{
    struct citp_msex_header msex_header;    
    uint8                   library_type; 
    uint8                   library_number; 
    uint32                  thumbnail_format;
    uint16                  thumbnail_width; 
    uint16                  thumbnail_height; 
    uint16                  thumbnail_buffer_size; 
    uint8                   *thumbnail_buffer;
};

struct citp_msex_1_1_elth
{
    struct citp_msex_header msex_header;    
    uint8                   library_type; 
    struct msex_library_id  library_id; 
    uint32                  thumbnail_format;
    uint16                  thumbnail_width; 
    uint16                  thumbnail_height; 
    uint16                  thumbnail_buffer_size; 
    uint8                   *thumbnail_buffer;
};


/*
 * MSEX GETh - "Get Element Thumbnail" messages.
 * msex_header.content_type = CITP_COOKIE_MSEX_GETH 
 */

struct citp_msex_1_0_geth
{
    struct citp_msex_header msex_header;    
    uint32                  thumbnail_format;
    uint16                  thumbnail_width; 
    uint16                  thumbnail_height; 
    uint8                   thumbnail_flags;
    uint8                   library_type; 
    uint8                   library_number; 
    uint8                   element_count;
    uint8                   *element_numbers;
};

struct citp_msex_1_1_geth
{
    struct citp_msex_header msex_header;    
    uint32                  thumbnail_format;
    uint16                  thumbnail_width; 
    uint16                  thumbnail_height; 
    uint8                   thumbnail_flags;
    uint8                   library_type; 
    struct msex_library_id  library_id; 
    uint8                   element_count;
    uint8                   *element_numbers;
};

struct citp_msex_1_2_geth
{
    struct citp_msex_header msex_header;    
    uint32                  thumbnail_format;
    uint16                  thumbnail_width; 
    uint16                  thumbnail_height; 
    uint8                   thumbnail_flags;
    uint8                   library_type; 
    struct msex_library_id  library_id; 
    uint16                  element_count;
    uint8                   *element_numbers;
};


/*
 * MSEX EThn - "Element Thumbnail" messages.
 * msex_header.content_type = CITP_COOKIE_MSEX_ETHN 
 */
struct citp_msex_1_0_ethn
{
    struct citp_msex_header msex_header;    
    uint8                   library_type; 
    uint8                   library_number; 
    uint8                   element_number; 
    uint32                  thumbnail_format;
    uint16                  thumbnail_width; 
    uint16                  thumbnail_height; 
    uint16                  thumbnail_buffer_size; 
    uint8                   *thumbnail_buffer;
};

struct citp_msex_1_1_ethn
{
    struct citp_msex_header msex_header;    
    uint8                   library_type; 
    struct msex_library_id  library_id; 
    uint8                   element_number; 
    uint32                  thumbnail_format;
    uint16                  thumbnail_width; 
    uint16                  thumbnail_height; 
    uint16                  thumbnail_buffer_size; 
    uint8                   *thumbnail_buffer;
};

/* 
 * MSEX RqSt - "Request Stream" messages.
 * msex_header.content_type = CITP_COOKIE_MSEX_RQST
 */
struct citp_msex_rqst
{
    struct citp_msex_header msex_header; 
    uint16                  source_identifier;  
    uint32                  frame_format;       /* RGB8/JPEG (PNG allowed for 1.2) */
    uint16                  frame_width;        /* Preferred minimum  */
    uint16                  frame_height;       /* Preferred minimum  */
    uint8                   fps;                /* Preferred minimum  */
    uint8                   timeout;            /* Timeout in seconds */
};

/*
 * MSEX StFr - "Stream Frame" messages.
 * msex_header.content_type = CITP_COOKIE_MSEX_STFR 
 */
struct citp_msex_1_0_stfr 
{
    struct citp_msex_header msex_header;    
    uint16                  source_identifier; 
    uint32                  frame_format;
    uint16                  frame_width;
    uint16                  frame_height; 
    uint16                  frame_buffer_size; 
    uint8                   *frame_buffer;
};

struct citp_msex_1_2_stfr
{
    struct citp_msex_header msex_header;    
    ucs1                    *media_server_uuid;
    uint16                  source_identifier; 
    uint32                  frame_format;
    uint16                  frame_width;
    uint16                  frame_height; 
    uint16                  frame_buffer_size; 
    uint8                   *frame_buffer;
};

/*
 * MSEX ElUp - "Element Update" messages.
 * msex_header.content_type = CITP_COOKIE_MSEX_EEIN 
 */

struct citp_msex_1_0_elup
{
    struct citp_msex_header     msex_header;
    uint8                       library_type;
    uint8                       library_number;
    uint8                       update_flags;
};
struct citp_msex_1_1_elup
{
    struct citp_msex_header     msex_header;
    uint8                       library_type;
    struct msex_library_id      library_id; 
    uint8                       update_flags;
};

struct elup_affected_items 
{
    uint8   item_set[32]; 
};
/* Would use the following to see if the item at item_index has changed:
 * item_set[item_index / 8] & (1 << (item_index % 8))
 * 
 */ 
struct citp_msex_1_2_elup
{
    struct citp_msex_header     msex_header;
    uint8                       library_type;
    struct msex_library_id      library_id; 
    uint8                       update_flags;
    struct elup_affected_items  affected_elements;
    struct elup_affected_items  affected_libraries;
};

/*
 * MSEX EEIn - "Effect Element Information" messages.
 * msex_header.content_type = CITP_COOKIE_MSEX_EEIN 
 */
struct eein_1_0_effect_info 
{
    uint8   element_number; 
    uint8   dmx_range_min; 
    uint8   dmx_range_max; 
    ucs2    *effect_name;
    uint8   effect_parameter_count; 
    ucs2    **effect_parameter_names;
};
struct citp_msex_1_0_eein
{
    struct citp_msex_header     msex_header;
    uint8                       library_number;
    uint8                       element_count;
    struct eein_1_0_effect_info *effect_information; 
};
struct citp_msex_1_1_eein
{
    struct citp_msex_header     msex_header;
    struct msex_library_id      library_id; 
    uint8                       element_count;
    struct eein_1_0_effect_info *effect_information; 
};

struct eein_1_2_effect_info 
{
    uint8   element_number; 
    uint32  serial_number;
    uint8   dmx_range_min; 
    uint8   dmx_range_max; 
    ucs2    *effect_name;
    uint8   effect_parameter_count; 
    ucs2    **effect_parameter_names;
};
struct citp_msex_1_2_eein
{
    struct citp_msex_header     msex_header;
    struct msex_library_id      library_id; 
    uint16                      element_count;
    struct eein_1_2_effect_info *effect_information; 
};

/*
 * MSEX GLEI - "Generic Element Information" messages.
 * msex_header.content_type = CITP_COOKIE_MSEX_GLEI 
 */

struct glei_1_1_generic_info
{
    uint8   element_number; 
    uint8   dmx_range_min; 
    uint8   dmx_range_max; 
    ucs2    *name;
    uint64  version_timestamp; 
};
struct citp_msex_1_1_glei 
{
    struct citp_msex_header         msex_header;
    struct msex_library_id          library_id; 
    uint8                           element_count;
    struct glei_1_1_generic_info    *generic_information; 
};

struct glei_1_2_generic_info
{
    uint8   element_number; 
    uint32  serial_number;
    uint8   dmx_range_min; 
    uint8   dmx_range_max; 
    ucs2    *name;
    uint64  version_timestamp; 
};
struct citp_msex_1_2_glei 
{
    struct citp_msex_header         msex_header;
    uint8                           library_type;
    struct msex_library_id          library_id; 
    uint16                          element_count;
    struct glei_1_2_generic_info    *generic_information; 
};


#endif /* _CITP_CITPTYPES_H_ */
