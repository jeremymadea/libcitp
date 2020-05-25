/* 
 * delete.c - Functions for deleting CITP message structures. 
 * Jeremy Madea <jeremymadea@gmail.com>
 *
 */
#ifndef _CITP_DELETE_H_
#define _CITP_DELETE_H_

#include "citptypes.h"

/* Forward declarations of deletion routines for message structures. */
void citp_delete_message(void *msg);
/*
void citp_delete_pinf(void *msg); 
void citp_delete_sdmx(void *msg); 
void citp_delete_msex(void *msg);
*/
/* Forwards declarations of deletion routines for auxillary structures. */
/*
void citp_delete_msex_layer_information(uint8 cnt, struct msex_layer_info *info);
void citp_delete_msex_1_0_layer_status(uint8 cnt, struct msex_1_0_layer_status *status); 
void citp_delete_msex_1_2_layer_status(uint8 cnt, struct msex_1_2_layer_status *status); 
void citp_delete_msex_1_0_element_library_info(uint16 cnt, struct msex_1_0_element_library_info *info); 
void citp_delete_msex_1_1_element_library_info(uint16 cnt, struct msex_1_1_element_library_info *info); 
void citp_delete_msex_1_2_element_library_info(uint16 cnt, struct msex_1_2_element_library_info *info); 
void citp_delete_msex_1_0_media_info(uint8 cnt, struct msex_1_0_media_info *info); 
void citp_delete_msex_1_2_media_info(uint16 cnt, struct msex_1_2_media_info *info); 
*/

#endif /* _CITP_DELETE_H_ */
