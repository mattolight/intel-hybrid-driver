/*
 * Copyright © 2009 Intel Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.
 * IN NO EVENT SHALL PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *     Midhunchandra Kodiyath <midhunchandra.kodiyath@intel.com>
 *
 */

#include "media_drv_kernels.h"
#include "media_drv_hw_g75.h"
#include "media_drv_gpe_utils.h"
#include "media_drv_defines.h"
#include "media_drv_common.h"
#include "media_drv_surface.h"
#include <va/va_enc_vp8.h>

//#define DEBUG
struct hw_codec_info gen75_hw_codec_info = {

  .max_width = 4096,
  .max_height = 4096,

  .mpeg2_dec_support = 0,
  .mpeg2_enc_support = 0,
  .h264_dec_support = 0,
  .h264_enc_support = 0,
  .vc1_dec_support = 0,
  .jpeg_dec_support = 0,
  .vp8_enc_hybrid_support = 1,
  .vpp_support = 0,
  .accelerated_getimage = 1,
  .accelerated_putimage = 1,
  .tiled_surface = 1,
  .di_motion_adptive = 1,
  .di_motion_compensated = 1,
  .blending = 1,
};

const SURFACE_SET_PARAMS surface_set_params_init = {
  0,				//vert_line_stride_offset
  0,				//vert_line_stride
  0,				//pitch
  0,				//tiling
  0,				//format
  0,				//offset
  0,				//size
  FALSE,			//surface_is_2d
  FALSE,			//surface_is_uv_2d
  FALSE,			//surface_is_raw
  FALSE,			//media_block_raw
  FALSE,			//advance_state
  0,				//uv_direction
  0,				//cacheability_control
  0,				// binding_table_offset
  0,				//surface_state_offset
  {NULL, 0, 0, 0, 0, 0, 0, NULL, 0, 0,0,0},	// binding_surface_state
  NULL,				//surface_2d
  {NULL, 0, 0, 0, 0, 0, 0, NULL, 0, 0,0,0} //buf_object             
};

MEDIA_KERNEL media_hybrid_vp8_kernels[] = {
  {
   (BYTE *)"VP8_MBENC_I",
   0,
   MEDIA_VP8_MBENC_I,
   MEDIA_VP8_MBENC_I_SZ,
   NULL,
   0},
  {
   (BYTE *)"VP8_MBENC_ICHROMA",
   0,
   MEDIA_VP8_MBENC_ICHROMA,
   MEDIA_VP8_MBENC_ICHROMA_SZ,
   NULL,
   0},
  {
   (BYTE *)"VP8_MBENC_FRM_P",
   0,
   MEDIA_VP8_MBENC_FRM_P,
   MEDIA_VP8_MBENC_FRM_P_SZ,
   NULL,
   0},
  {
   (BYTE *)"VP8_MBENC_ILuma",
   0,
   MEDIA_VP8_MBENC_ILuma,
   MEDIA_VP8_MBENC_ILuma_SZ,
   NULL,
   0},
  {
   (BYTE *)"VP8_HME_P",
   0,
   MEDIA_VP8_HME_P,
   MEDIA_VP8_HME_P_SZ,
   NULL,
   0},
  {
  (BYTE *)"VP8_HME_DOWNSCALE",
   0,
   MEDIA_VP8_HME_DOWNSCALE,
   MEDIA_VP8_HME_DOWNSCALE_SZ,
   NULL,
   0},

  {
   (BYTE *)"VP8_PAK_PHASE2",
   0,
   MEDIA_VP8_PAK_PHASE2,
   MEDIA_VP8_PAK_PHASE2_SZ,
   NULL,
   0},
  {
   (BYTE *)"VP8_PAK_PHASE1",
   0,
   MEDIA_VP8_PAK_PHASE1,
   MEDIA_VP8_PAK_PHASE1_SZ,
   NULL,
   0},
  {
   (BYTE *)"VP8_INTRA_DIS_BRC",
   0,
   MEDIA_VP8_INTRA_DIS_BRC,
   MEDIA_VP8_INTRA_DIS_BRC_SZ,
   NULL,
   0},

  {
   (BYTE *)"VP8_BRC_INIT",
   0,
   MEDIA_VP8_BRC_INIT,
   MEDIA_VP8_BRC_INIT_SZ,
   NULL,
   0},

  {
   (BYTE *)"VP8_BRC_RESET",
   0,
   MEDIA_VP8_BRC_RESET,
   MEDIA_VP8_BRC_RESET_SZ,
   NULL,
   0},

  {
   (BYTE *)"VP8_BRC_UPDATE",
   0,
   MEDIA_VP8_BRC_UPDATE,
   MEDIA_VP8_BRC_UPDATE_SZ,
   NULL,
   0}

};

const SURFACE_STATE_ADV_G7 SURFACE_STATE_ADV_INIT_G7 = {
  //dw0
   {0},
  {
//dw1
   0,
   0,
   0,
   0},
  {
//dw2
   0,
   FALSE,
   FALSE,
   0,
   0,
   0,
   FALSE,
   0,
   0},
  {
//dw3
   0,
   0,
   0,
   0},
  {
//dw4
   0,
   0,
   0,
   0},
//dw5
   {0},
 //dw6
   {0},
//dw7
   {0}
};

const SURFACE_STATE_G7 SURFACE_STATE_INIT_G7 = {
  //dw0
  {
   FALSE,			// cube_pos_z:1;                                        
   FALSE,			//cube_neg_z:1                                       
   FALSE,			//cube_pos_y:1                                        
   FALSE,			//cube_neg_y:1                                        
   FALSE,			//cube_pos_x:1                                        
   FALSE,			//cube_neg_x:1                                        
   0,				// media_boundry_pix_mode:2                     
   0,				//render_cache_read_write:1
   0,				//reserved0                
   1,				//surface_array_spacing:1         
   0,				//vert_line_stride_ofs:1          
   0,				//vert_line_stride:1          
   0,				//tile_walk:1          
   FALSE,			//tiled_surface:1;      
   0,				//horizontal_alignment:1;     
   0,				//vertical_alignment:2;      
   STATE_SURFACEFORMAT_R8_UNORM,	// surface_format:9;
   0,				//min_mag_state_not_eq:1;                                             
   FALSE,			//surface_array:1;                                         
   1				//MEDIA_SURFACE_2D  // surface_type:3;                  
   },

  //dw1
  {
   0},

  //dw22
  {
   0,
   0},

  //dw3
  {
   0,
   0},

  //dw4
  {
   0,
   0,
   0,
   0,
   0,
   0},

  //dw5
  {
   0,
   0,
   0,
   0,
   0,
   0,
   0},

  //dw6
  {
   0,
   0},

  //dw7
  {
   0,
   0,
   HSW_SCS_ALPHA,
   HSW_SCS_BLUE,
   HSW_SCS_GREEN,
   HSW_SCS_RED,
   0,
   0,
   0,
   0}
};

const UINT16 quant_dc_vp8_g75[MAX_QP_VP8] = {
  4, 5, 6, 7, 8, 9, 10, 10, 11, 12, 13, 14, 15, 16, 17, 17,
  18, 19, 20, 20, 21, 21, 22, 22, 23, 23, 24, 25, 25, 26, 27, 28,
  29, 30, 31, 32, 33, 34, 35, 36, 37, 37, 38, 39, 40, 41, 42, 43,
  44, 45, 46, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58,
  59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74,
  75, 76, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
  91, 93, 95, 96, 98, 100, 101, 102, 104, 106, 108, 110, 112, 114, 116, 118,
  122, 124, 126, 128, 130, 132, 134, 136, 138, 140, 143, 145, 148, 151, 154,
  157
};

const UINT16 quant_ac_vp8_g75[MAX_QP_VP8] = {
  4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
  20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
  36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,
  52, 53, 54, 55, 56, 57, 58, 60, 62, 64, 66, 68, 70, 72, 74, 76,
  78, 80, 82, 84, 86, 88, 90, 92, 94, 96, 98, 100, 102, 104, 106, 108,
  110, 112, 114, 116, 119, 122, 125, 128, 131, 134, 137, 140, 143, 146, 149,
  152,
  155, 158, 161, 164, 167, 170, 173, 177, 181, 185, 189, 193, 197, 201, 205,
  209,
  213, 217, 221, 225, 229, 234, 239, 245, 249, 254, 259, 264, 269, 274, 279,
    284
};

const UINT16 quant_dc2_vp8_g75[MAX_QP_VP8] = {
  8, 10, 12, 14, 16, 18, 20, 20, 22, 24, 26, 28, 30, 32, 34, 34,
  36, 38, 40, 40, 42, 42, 44, 44, 46, 46, 48, 50, 50, 52, 54, 56,
  58, 60, 62, 64, 66, 68, 70, 72, 74, 74, 76, 78, 80, 82, 84, 86,
  88, 90, 92, 92, 94, 96, 98, 100, 102, 104, 106, 108, 110, 112, 114, 116,
  118, 120, 122, 124, 126, 128, 130, 132, 134, 136, 138, 140, 142, 144, 146,
  148,
  150, 152, 152, 154, 156, 158, 160, 162, 164, 166, 168, 170, 172, 174, 176,
  178,
  182, 186, 190, 192, 196, 200, 202, 204, 208, 212, 216, 220, 224, 228, 232,
  236,
  244, 248, 252, 256, 260, 264, 268, 272, 276, 280, 286, 290, 296, 302, 308,
    314
};

const UINT16 quant_ac2_vp8_g75[MAX_QP_VP8] = {
  8, 8, 9, 10, 12, 13, 15, 17, 18, 20, 21, 23, 24, 26, 27, 29,
  31, 32, 34, 35, 37, 38, 40, 41, 43, 44, 46, 48, 49, 51, 52, 54,
  55, 57, 58, 60, 62, 63, 65, 66, 68, 69, 71, 72, 74, 75, 77, 79,
  80, 82, 83, 85, 86, 88, 89, 93, 96, 99, 102, 105, 108, 111, 114, 117,
  120, 124, 127, 130, 133, 136, 139, 142, 145, 148, 151, 155, 158, 161, 164,
  167,
  170, 173, 176, 179, 184, 189, 193, 198, 203, 207, 212, 217, 221, 226, 230,
  235,
  240, 244, 249, 254, 258, 263, 268, 274, 280, 286, 292, 299, 305, 311, 317,
  323,
  330, 336, 342, 348, 354, 362, 370, 379, 385, 393, 401, 409, 416, 424, 432,
    440
};

const UINT16 quant_dc_uv_vp8_g75[MAX_QP_VP8] = {
  4, 5, 6, 7, 8, 9, 10, 10, 11, 12, 13, 14, 15, 16, 17, 17,
  18, 19, 20, 20, 21, 21, 22, 22, 23, 23, 24, 25, 25, 26, 27, 28,
  29, 30, 31, 32, 33, 34, 35, 36, 37, 37, 38, 39, 40, 41, 42, 43,
  44, 45, 46, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58,
  59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74,
  75, 76, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
  91, 93, 95, 96, 98, 100, 101, 102, 104, 106, 108, 110, 112, 114, 116, 118,
  122, 124, 126, 128, 130, 132, 132, 132, 132, 132, 132, 132, 132, 132, 132,
    132
};

const BYTE frame_i_vme_cost_vp8_g75[128][4] = {
  {0x05, 0x1f, 0x02, 0x09},
  {0x05, 0x1f, 0x02, 0x09},
  {0x08, 0x2b, 0x03, 0x0e},
  {0x08, 0x2b, 0x03, 0x0e},
  {0x0a, 0x2f, 0x04, 0x12},
  {0x0a, 0x2f, 0x04, 0x12},
  {0x0d, 0x39, 0x05, 0x17},
  {0x0d, 0x39, 0x05, 0x17},
  {0x0d, 0x39, 0x05, 0x17},
  {0x0f, 0x3b, 0x06, 0x1b},
  {0x0f, 0x3b, 0x06, 0x1b},
  {0x19, 0x3d, 0x07, 0x20},
  {0x19, 0x3d, 0x07, 0x20},
  {0x1a, 0x3f, 0x08, 0x24},
  {0x1a, 0x3f, 0x08, 0x24},
  {0x1a, 0x3f, 0x08, 0x24},
  {0x1b, 0x48, 0x09, 0x29},
  {0x1b, 0x48, 0x09, 0x29},
  {0x1d, 0x49, 0x09, 0x2d},
  {0x1d, 0x49, 0x09, 0x2d},
  {0x1d, 0x49, 0x09, 0x2d},
  {0x1d, 0x49, 0x09, 0x2d},
  {0x1e, 0x4a, 0x0a, 0x32},
  {0x1e, 0x4a, 0x0a, 0x32},
  {0x1e, 0x4a, 0x0a, 0x32},
  {0x1e, 0x4a, 0x0a, 0x32},
  {0x1f, 0x4b, 0x0b, 0x36},
  {0x1f, 0x4b, 0x0b, 0x36},
  {0x1f, 0x4b, 0x0b, 0x36},
  {0x28, 0x4c, 0x0c, 0x3b},
  {0x28, 0x4c, 0x0c, 0x3b},
  {0x29, 0x4d, 0x0d, 0x3f},
  {0x29, 0x4d, 0x0d, 0x3f},
  {0x29, 0x4e, 0x0e, 0x44},
  {0x29, 0x4e, 0x0e, 0x44},
  {0x2a, 0x4f, 0x0f, 0x48},
  {0x2a, 0x4f, 0x0f, 0x48},
  {0x2b, 0x58, 0x10, 0x4d},
  {0x2b, 0x58, 0x10, 0x4d},
  {0x2b, 0x58, 0x11, 0x51},
  {0x2b, 0x58, 0x11, 0x51},
  {0x2b, 0x58, 0x11, 0x51},
  {0x2c, 0x58, 0x12, 0x56},
  {0x2c, 0x58, 0x12, 0x56},
  {0x2c, 0x59, 0x13, 0x5a},
  {0x2c, 0x59, 0x13, 0x5a},
  {0x2d, 0x59, 0x14, 0x5f},
  {0x2d, 0x59, 0x14, 0x5f},
  {0x2e, 0x5a, 0x15, 0x63},
  {0x2e, 0x5a, 0x15, 0x63},
  {0x2e, 0x5a, 0x16, 0x68},
  {0x2e, 0x5a, 0x16, 0x68},
  {0x2e, 0x5a, 0x16, 0x68},
  {0x2f, 0x5b, 0x17, 0x6c},
  {0x2f, 0x5b, 0x17, 0x6c},
  {0x38, 0x5b, 0x18, 0x71},
  {0x38, 0x5b, 0x18, 0x71},
  {0x38, 0x5c, 0x19, 0x76},
  {0x38, 0x5c, 0x19, 0x76},
  {0x38, 0x5c, 0x1a, 0x7a},
  {0x38, 0x5c, 0x1a, 0x7a},
  {0x39, 0x5d, 0x1a, 0x7f},
  {0x39, 0x5d, 0x1a, 0x7f},
  {0x39, 0x5d, 0x1b, 0x83},
  {0x39, 0x5d, 0x1b, 0x83},
  {0x39, 0x5e, 0x1c, 0x88},
  {0x39, 0x5e, 0x1c, 0x88},
  {0x3a, 0x5e, 0x1d, 0x8c},
  {0x3a, 0x5e, 0x1d, 0x8c},
  {0x3a, 0x5f, 0x1e, 0x91},
  {0x3a, 0x5f, 0x1e, 0x91},
  {0x3a, 0x5f, 0x1f, 0x95},
  {0x3a, 0x5f, 0x1f, 0x95},
  {0x3a, 0x68, 0x20, 0x9a},
  {0x3a, 0x68, 0x20, 0x9a},
  {0x3b, 0x68, 0x21, 0x9e},
  {0x3b, 0x68, 0x21, 0x9e},
  {0x3b, 0x68, 0x22, 0xa3},
  {0x3b, 0x68, 0x22, 0xa3},
  {0x3b, 0x68, 0x23, 0xa7},
  {0x3b, 0x68, 0x23, 0xa7},
  {0x3c, 0x68, 0x24, 0xac},
  {0x3c, 0x68, 0x24, 0xac},
  {0x3c, 0x68, 0x24, 0xac},
  {0x3c, 0x69, 0x25, 0xb0},
  {0x3c, 0x69, 0x25, 0xb0},
  {0x3c, 0x69, 0x26, 0xb5},
  {0x3c, 0x69, 0x26, 0xb5},
  {0x3d, 0x69, 0x27, 0xb9},
  {0x3d, 0x69, 0x27, 0xb9},
  {0x3d, 0x69, 0x28, 0xbe},
  {0x3d, 0x69, 0x28, 0xbe},
  {0x3d, 0x6a, 0x29, 0xc2},
  {0x3d, 0x6a, 0x29, 0xc2},
  {0x3e, 0x6a, 0x2a, 0xc7},
  {0x3e, 0x6a, 0x2a, 0xc7},
  {0x3e, 0x6a, 0x2b, 0xcb},
  {0x3e, 0x6a, 0x2b, 0xd0},
  {0x3f, 0x6b, 0x2c, 0xd4},
  {0x3f, 0x6b, 0x2d, 0xd9},
  {0x3f, 0x6b, 0x2e, 0xdd},
  {0x48, 0x6b, 0x2f, 0xe2},
  {0x48, 0x6b, 0x2f, 0xe2},
  {0x48, 0x6c, 0x30, 0xe6},
  {0x48, 0x6c, 0x31, 0xeb},
  {0x48, 0x6c, 0x32, 0xf0},
  {0x48, 0x6c, 0x33, 0xf4},
  {0x48, 0x6c, 0x34, 0xf9},
  {0x49, 0x6d, 0x35, 0xfd},
  {0x49, 0x6d, 0x36, 0xff},
  {0x49, 0x6d, 0x37, 0xff},
  {0x49, 0x6d, 0x38, 0xff},
  {0x49, 0x6e, 0x3a, 0xff},
  {0x49, 0x6e, 0x3b, 0xff},
  {0x4a, 0x6e, 0x3c, 0xff},
  {0x4a, 0x6f, 0x3d, 0xff},
  {0x4a, 0x6f, 0x3d, 0xff},
  {0x4a, 0x6f, 0x3e, 0xff},
  {0x4a, 0x6f, 0x3f, 0xff},
  {0x4a, 0x6f, 0x40, 0xff},
  {0x4b, 0x78, 0x41, 0xff},
  {0x4b, 0x78, 0x42, 0xff},
  {0x4b, 0x78, 0x43, 0xff},
  {0x4b, 0x78, 0x44, 0xff},
  {0x4b, 0x78, 0x46, 0xff},
  {0x4c, 0x78, 0x47, 0xff},
  {0x4c, 0x79, 0x49, 0xff},
  {0x4c, 0x79, 0x4a, 0xff}
};

const UINT cost_table_vp8_g75[128][7] = {
  {0x398f0500, 0x6f6f6f6f, 0x0000006f, 0x06040402, 0x0b0a0907, 0x08, 0x0e},
  {0x3b8f0600, 0x6f6f6f6f, 0x0000006f, 0x06040402, 0x0b0a0907, 0x0a, 0x11},
  {0x3e8f0700, 0x6f6f6f6f, 0x0000006f, 0x06040402, 0x0b0a0907, 0x0c, 0x14},
  {0x488f0800, 0x6f6f6f6f, 0x0000006f, 0x06040402, 0x0b0a0907, 0x0f, 0x18},
  {0x498f0a00, 0x6f6f6f6f, 0x0000006f, 0x0d080805, 0x1b1a190e, 0x11, 0x1b},
  {0x4a8f0b00, 0x6f6f6f6f, 0x0000006f, 0x0d080805, 0x1b1a190e, 0x13, 0x1e},
  {0x4b8f0c00, 0x6f6f6f6f, 0x0000006f, 0x0d080805, 0x1b1a190e, 0x15, 0x22},
  {0x4b8f0c00, 0x6f6f6f6f, 0x0000006f, 0x0d080805, 0x1b1a190e, 0x15, 0x22},
  {0x4d8f0d00, 0x6f6f6f6f, 0x0000006f, 0x0d080805, 0x1b1a190e, 0x17, 0x25},
  {0x4e8f0e00, 0x6f6f6f6f, 0x0000006f, 0x190b0c07, 0x281f1e1a, 0x19, 0x29},
  {0x4f8f0f00, 0x6f6f6f6f, 0x0000006f, 0x190b0c07, 0x281f1e1a, 0x1b, 0x2c},
  {0x588f1800, 0x6f6f6f6f, 0x0000006f, 0x190b0c07, 0x281f1e1a, 0x1d, 0x2f},
  {0x588f1900, 0x6f6f6f6f, 0x0000006f, 0x190b0c07, 0x281f1e1a, 0x1f, 0x33},
  {0x598f1900, 0x6f6f6f6f, 0x0000006f, 0x1c0f0f0a, 0x2b2a291e, 0x21, 0x36},
  {0x5a8f1a00, 0x6f6f6f6f, 0x0000006f, 0x1c0f0f0a, 0x2b2a291e, 0x23, 0x3a},
  {0x5a8f1a00, 0x6f6f6f6f, 0x0000006f, 0x1c0f0f0a, 0x2b2a291e, 0x23, 0x3a},
  {0x5a8f1a00, 0x6f6f6f6f, 0x0000006f, 0x1c0f0f0a, 0x2b2a291e, 0x25, 0x3d},
  {0x5b8f1b00, 0x6f6f6f6f, 0x0000006f, 0x1c0f0f0a, 0x2b2a291e, 0x27, 0x40},
  {0x5b8f1c00, 0x6f6f6f6f, 0x0000006f, 0x2819190c, 0x2d2c2b29, 0x2a, 0x44},
  {0x5b8f1c00, 0x6f6f6f6f, 0x0000006f, 0x2819190c, 0x2d2c2b29, 0x2a, 0x44},
  {0x5c8f1c00, 0x6f6f6f6f, 0x0000006f, 0x2819190c, 0x2d2c2b29, 0x2c, 0x47},
  {0x5c8f1c00, 0x6f6f6f6f, 0x0000006f, 0x2819190c, 0x2d2c2b29, 0x2c, 0x47},
  {0x5d8f1d00, 0x6f6f6f6f, 0x0000006f, 0x2819190c, 0x2d2c2b29, 0x2e, 0x4a},
  {0x5d8f1d00, 0x6f6f6f6f, 0x0000006f, 0x2819190c, 0x2d2c2b29, 0x2e, 0x4a},
  {0x5d8f1d00, 0x6f6f6f6f, 0x0000006f, 0x2819190c, 0x2d2c2b29, 0x30, 0x4e},
  {0x5d8f1d00, 0x6f6f6f6f, 0x0000006f, 0x2819190c, 0x2d2c2b29, 0x30, 0x4e},
  {0x5e8f1e00, 0x6f6f6f6f, 0x0000006f, 0x291b1b0f, 0x382f2e2a, 0x32, 0x51},
  {0x5e8f1f00, 0x6f6f6f6f, 0x0000006f, 0x291b1b0f, 0x382f2e2a, 0x34, 0x55},
  {0x5e8f1f00, 0x6f6f6f6f, 0x0000006f, 0x291b1b0f, 0x382f2e2a, 0x34, 0x55},
  {0x5f8f1f00, 0x6f6f6f6f, 0x0000006f, 0x291b1b0f, 0x382f2e2a, 0x36, 0x58},
  {0x688f2800, 0x6f6f6f6f, 0x0000006f, 0x291b1b0f, 0x382f2e2a, 0x38, 0x5b},
  {0x688f2800, 0x6f6f6f6f, 0x0000006f, 0x2b1d1d18, 0x3938382c, 0x3a, 0x5f},
  {0x688f2800, 0x6f6f6f6f, 0x0000006f, 0x2b1d1d18, 0x3938382c, 0x3c, 0x62},
  {0x688f2900, 0x6f6f6f6f, 0x0000006f, 0x2b1d1d18, 0x3938382c, 0x3e, 0x65},
  {0x698f2900, 0x6f6f6f6f, 0x0000006f, 0x2b1d1d18, 0x3938382c, 0x40, 0x69},
  {0x698f2900, 0x6f6f6f6f, 0x0000006f, 0x2c1f1f19, 0x3b3a392e, 0x43, 0x6c},
  {0x698f2900, 0x6f6f6f6f, 0x0000006f, 0x2c1f1f19, 0x3b3a392e, 0x45, 0x70},
  {0x6a8f2a00, 0x6f6f6f6f, 0x0000006f, 0x2c1f1f19, 0x3b3a392e, 0x47, 0x73},
  {0x6a8f2a00, 0x6f6f6f6f, 0x0000006f, 0x2c1f1f19, 0x3b3a392e, 0x49, 0x76},
  {0x6a8f2a00, 0x6f6f6f6f, 0x0000006f, 0x2e28281b, 0x3c3b3a38, 0x4b, 0x7a},
  {0x6b8f2b00, 0x6f6f6f6f, 0x0000006f, 0x2e28281b, 0x3c3b3a38, 0x4d, 0x7d},
  {0x6b8f2b00, 0x6f6f6f6f, 0x0000006f, 0x2e28281b, 0x3c3b3a38, 0x4d, 0x7d},
  {0x6b8f2b00, 0x6f6f6f6f, 0x0000006f, 0x2e28281b, 0x3c3b3a38, 0x4f, 0x81},
  {0x6b8f2b00, 0x6f6f6f6f, 0x0000006f, 0x2e28281b, 0x3c3b3a38, 0x51, 0x84},
  {0x6b8f2c00, 0x6f6f6f6f, 0x0000006f, 0x2f29291c, 0x3d3c3b38, 0x53, 0x87},
  {0x6c8f2c00, 0x6f6f6f6f, 0x0000006f, 0x2f29291c, 0x3d3c3b38, 0x55, 0x8b},
  {0x6c8f2c00, 0x6f6f6f6f, 0x0000006f, 0x2f29291c, 0x3d3c3b38, 0x57, 0x8e},
  {0x6c8f2c00, 0x6f6f6f6f, 0x0000006f, 0x2f29291c, 0x3d3c3b38, 0x59, 0x91},
  {0x6d8f2d00, 0x6f6f6f6f, 0x0000006f, 0x382a2a1d, 0x3f3e3c39, 0x5b, 0x95},
  {0x6d8f2d00, 0x6f6f6f6f, 0x0000006f, 0x382a2a1d, 0x3f3e3c39, 0x5e, 0x98},
  {0x6d8f2d00, 0x6f6f6f6f, 0x0000006f, 0x382a2a1d, 0x3f3e3c39, 0x60, 0x9c},
  {0x6d8f2d00, 0x6f6f6f6f, 0x0000006f, 0x382a2a1d, 0x3f3e3c39, 0x60, 0x9c},
  {0x6d8f2e00, 0x6f6f6f6f, 0x0000006f, 0x382a2a1d, 0x3f3e3c39, 0x62, 0x9f},
  {0x6e8f2e00, 0x6f6f6f6f, 0x0000006f, 0x392b2b1e, 0x483f3e3a, 0x64, 0xa2},
  {0x6e8f2e00, 0x6f6f6f6f, 0x0000006f, 0x392b2b1e, 0x483f3e3a, 0x66, 0xa6},
  {0x6e8f2e00, 0x6f6f6f6f, 0x0000006f, 0x392b2b1e, 0x483f3e3a, 0x68, 0xa9},
  {0x6f8f2f00, 0x6f6f6f6f, 0x0000006f, 0x392b2b1e, 0x483f3e3a, 0x6a, 0xad},
  {0x6f8f2f00, 0x6f6f6f6f, 0x0000006f, 0x3a2c2c1f, 0x48483f3b, 0x6c, 0xb0},
  {0x6f8f2f00, 0x6f6f6f6f, 0x0000006f, 0x3a2c2c1f, 0x48483f3b, 0x6e, 0xb3},
  {0x788f3800, 0x6f6f6f6f, 0x0000006f, 0x3a2c2c1f, 0x48483f3b, 0x70, 0xb7},
  {0x788f3800, 0x6f6f6f6f, 0x0000006f, 0x3a2c2c1f, 0x48483f3b, 0x72, 0xba},
  {0x788f3800, 0x6f6f6f6f, 0x0000006f, 0x3b2d2d28, 0x4948483c, 0x74, 0xbd},
  {0x788f3800, 0x6f6f6f6f, 0x0000006f, 0x3b2d2d28, 0x4948483c, 0x76, 0xc1},
  {0x788f3800, 0x6f6f6f6f, 0x0000006f, 0x3b2d2d28, 0x4948483c, 0x79, 0xc4},
  {0x788f3800, 0x6f6f6f6f, 0x0000006f, 0x3b2d2d28, 0x4948483c, 0x7b, 0xc8},
  {0x788f3800, 0x6f6f6f6f, 0x0000006f, 0x3b2e2e29, 0x4a49483d, 0x7d, 0xcb},
  {0x798f3900, 0x6f6f6f6f, 0x0000006f, 0x3b2e2e29, 0x4a49483d, 0x7f, 0xce},
  {0x798f3900, 0x6f6f6f6f, 0x0000006f, 0x3b2e2e29, 0x4a49483d, 0x81, 0xd2},
  {0x798f3900, 0x6f6f6f6f, 0x0000006f, 0x3b2e2e29, 0x4a49483d, 0x83, 0xd5},
  {0x798f3900, 0x6f6f6f6f, 0x0000006f, 0x3c2f2f29, 0x4a4a493e, 0x85, 0xd9},
  {0x798f3900, 0x6f6f6f6f, 0x0000006f, 0x3c2f2f29, 0x4a4a493e, 0x87, 0xdc},
  {0x798f3900, 0x6f6f6f6f, 0x0000006f, 0x3c2f2f29, 0x4a4a493e, 0x89, 0xdf},
  {0x798f3a00, 0x6f6f6f6f, 0x0000006f, 0x3c2f2f29, 0x4a4a493e, 0x8b, 0xe3},
  {0x7a8f3a00, 0x6f6f6f6f, 0x0000006f, 0x3d38382a, 0x4b4a493f, 0x8d, 0xe6},
  {0x7a8f3a00, 0x6f6f6f6f, 0x0000006f, 0x3d38382a, 0x4b4a493f, 0x8f, 0xe9},
  {0x7a8f3a00, 0x6f6f6f6f, 0x0000006f, 0x3d38382a, 0x4b4a493f, 0x91, 0xed},
  {0x7a8f3a00, 0x6f6f6f6f, 0x0000006f, 0x3d38382a, 0x4b4a493f, 0x94, 0xf0},
  {0x7a8f3a00, 0x6f6f6f6f, 0x0000006f, 0x3e38382b, 0x4c4b4a48, 0x96, 0xf4},
  {0x7a8f3a00, 0x6f6f6f6f, 0x0000006f, 0x3e38382b, 0x4c4b4a48, 0x98, 0xf7},
  {0x7b8f3b00, 0x6f6f6f6f, 0x0000006f, 0x3e38382b, 0x4c4b4a48, 0x9a, 0xfa},
  {0x7b8f3b00, 0x6f6f6f6f, 0x0000006f, 0x3e38382b, 0x4c4b4a48, 0x9c, 0xfe},
  {0x7b8f3b00, 0x6f6f6f6f, 0x0000006f, 0x3f38392b, 0x4d4c4b48, 0x9e, 0xff},
  {0x7b8f3b00, 0x6f6f6f6f, 0x0000006f, 0x3f38392b, 0x4d4c4b48, 0x9e, 0xff},
  {0x7b8f3b00, 0x6f6f6f6f, 0x0000006f, 0x3f38392b, 0x4d4c4b48, 0xa0, 0xff},
  {0x7b8f3b00, 0x6f6f6f6f, 0x0000006f, 0x3f38392b, 0x4d4c4b48, 0xa2, 0xff},
  {0x7b8f3b00, 0x6f6f6f6f, 0x0000006f, 0x3f38392b, 0x4d4c4b48, 0xa4, 0xff},
  {0x7b8f3b00, 0x6f6f6f6f, 0x0000006f, 0x3f39392c, 0x4d4c4b48, 0xa6, 0xff},
  {0x7c8f3c00, 0x6f6f6f6f, 0x0000006f, 0x3f39392c, 0x4d4c4b48, 0xa8, 0xff},
  {0x7c8f3c00, 0x6f6f6f6f, 0x0000006f, 0x3f39392c, 0x4d4c4b48, 0xaa, 0xff},
  {0x7c8f3c00, 0x6f6f6f6f, 0x0000006f, 0x3f39392c, 0x4d4c4b48, 0xac, 0xff},
  {0x7c8f3c00, 0x6f6f6f6f, 0x0000006f, 0x48393a2c, 0x4e4d4c49, 0xaf, 0xff},
  {0x7c8f3c00, 0x6f6f6f6f, 0x0000006f, 0x48393a2c, 0x4e4d4c49, 0xb1, 0xff},
  {0x7c8f3c00, 0x6f6f6f6f, 0x0000006f, 0x48393a2c, 0x4e4d4c49, 0xb3, 0xff},
  {0x7c8f3c00, 0x6f6f6f6f, 0x0000006f, 0x48393a2c, 0x4e4d4c49, 0xb5, 0xff},
  {0x7d8f3d00, 0x6f6f6f6f, 0x0000006f, 0x483a3a2d, 0x4f4d4c49, 0xb7, 0xff},
  {0x7d8f3d00, 0x6f6f6f6f, 0x0000006f, 0x483a3a2d, 0x4f4d4c49, 0xb9, 0xff},
  {0x7d8f3d00, 0x6f6f6f6f, 0x0000006f, 0x483a3a2d, 0x4f4d4c49, 0xbd, 0xff},
  {0x7d8f3d00, 0x6f6f6f6f, 0x0000006f, 0x493a3b2e, 0x4f4e4d4a, 0xc1, 0xff},
  {0x7e8f3e00, 0x6f6f6f6f, 0x0000006f, 0x493a3b2e, 0x4f4e4d4a, 0xc5, 0xff},
  {0x7e8f3e00, 0x6f6f6f6f, 0x0000006f, 0x493b3b2e, 0x584f4e4a, 0xc8, 0xff},
  {0x7e8f3e00, 0x6f6f6f6f, 0x0000006f, 0x493b3b2e, 0x584f4e4a, 0xcc, 0xff},
  {0x7e8f3e00, 0x6f6f6f6f, 0x0000006f, 0x493b3c2f, 0x584f4e4b, 0xd0, 0xff},
  {0x7f8f3f00, 0x6f6f6f6f, 0x0000006f, 0x493b3c2f, 0x584f4e4b, 0xd2, 0xff},
  {0x7f8f3f00, 0x6f6f6f6f, 0x0000006f, 0x493b3c2f, 0x584f4e4b, 0xd4, 0xff},
  {0x7f8f3f00, 0x6f6f6f6f, 0x0000006f, 0x4a3c3c2f, 0x58584f4b, 0xd8, 0xff},
  {0x7f8f3f00, 0x6f6f6f6f, 0x0000006f, 0x4a3c3c2f, 0x58584f4b, 0xdc, 0xff},
  {0x888f4800, 0x6f6f6f6f, 0x0000006f, 0x4a3c3d38, 0x59584f4c, 0xe0, 0xff},
  {0x888f4800, 0x6f6f6f6f, 0x0000006f, 0x4a3c3d38, 0x59584f4c, 0xe5, 0xff},
  {0x888f4800, 0x6f6f6f6f, 0x0000006f, 0x4b3d3d38, 0x5958584c, 0xe9, 0xff},
  {0x888f4800, 0x6f6f6f6f, 0x0000006f, 0x4b3d3d38, 0x5958584c, 0xed, 0xff},
  {0x888f4800, 0x6f6f6f6f, 0x0000006f, 0x4b3d3e38, 0x5959584c, 0xf1, 0xff},
  {0x888f4800, 0x6f6f6f6f, 0x0000006f, 0x4b3d3e38, 0x5959584c, 0xf5, 0xff},
  {0x898f4900, 0x6f6f6f6f, 0x0000006f, 0x4b3e3e39, 0x5a59584d, 0xfe, 0xff},
  {0x898f4900, 0x6f6f6f6f, 0x0000006f, 0x4c3e3e39, 0x5a59594d, 0xff, 0xff},
  {0x898f4900, 0x6f6f6f6f, 0x0000006f, 0x4c3e3e39, 0x5a59594d, 0xff, 0xff},
  {0x898f4900, 0x6f6f6f6f, 0x0000006f, 0x4c3f3f39, 0x5a5a594e, 0xff, 0xff},
  {0x898f4900, 0x6f6f6f6f, 0x0000006f, 0x4c3f3f39, 0x5a5a594e, 0xff, 0xff},
  {0x898f4900, 0x6f6f6f6f, 0x0000006f, 0x4d3f3f3a, 0x5b5a594e, 0xff, 0xff},
  {0x898f4900, 0x6f6f6f6f, 0x0000006f, 0x4d3f3f3a, 0x5b5a594e, 0xff, 0xff},
  {0x8a8f4a00, 0x6f6f6f6f, 0x0000006f, 0x4d48483a, 0x5b5a594f, 0xff, 0xff},
  {0x8a8f4a00, 0x6f6f6f6f, 0x0000006f, 0x4d48483a, 0x5b5a594f, 0xff, 0xff},
  {0x8a8f4a00, 0x6f6f6f6f, 0x0000006f, 0x4d48483a, 0x5b5b5a4f, 0xff, 0xff},
  {0x8a8f4a00, 0x6f6f6f6f, 0x0000006f, 0x4d48483a, 0x5b5b5a4f, 0xff, 0xff},
  {0x8a8f4a00, 0x6f6f6f6f, 0x0000006f, 0x4e48483a, 0x5c5b5a58, 0xff, 0xff},
  {0x8b8f4b00, 0x6f6f6f6f, 0x0000006f, 0x4e48483b, 0x5c5b5a58, 0xff, 0xff},
  {0x8b8f4b00, 0x6f6f6f6f, 0x0000006f, 0x4e48483b, 0x5c5b5a58, 0xff, 0xff},
  {0x8b8f4b00, 0x6f6f6f6f, 0x0000006f, 0x4f48493b, 0x5d5c5b58, 0xff, 0xff},
  {0x8b8f4b00, 0x6f6f6f6f, 0x0000006f, 0x4f49493b, 0x5d5c5b58, 0xff, 0xff}
};

const UINT new_mv_skip_threshold_VP8_g75[128] = {
  111, 120, 129, 137, 146, 155, 163, 172, 180, 189, 198, 206, 215, 224, 232,
  241,
  249, 258, 267, 275, 284, 293, 301, 310, 318, 327, 336, 344, 353, 362, 370,
  379,
  387, 396, 405, 413, 422, 431, 439, 448, 456, 465, 474, 482, 491, 500, 508,
  517,
  525, 534, 543, 551, 560, 569, 577, 586, 594, 603, 612, 620, 629, 638, 646,
  655,
  663, 672, 681, 689, 698, 707, 715, 724, 733, 741, 750, 758, 767, 776, 784,
  793,
  802, 810, 819, 827, 836, 845, 853, 862, 871, 879, 888, 896, 905, 914, 922,
  931,
  940, 948, 957, 965, 974, 983, 991, 1000, 1009, 1017, 1026, 1034, 1043, 1052,
  1060, 1069,
  1078, 1086, 1095, 1103, 1112, 1121, 1129, 1138, 1147, 1155, 1164, 1172,
  1181, 1190, 1198, 1208
};

const UINT single_su_vp8_g75[14] = {
  0x00000000, 0x00000000, 0x00000000, 0x00000000,
  0x00000000, 0x00000000, 0x00000000, 0x00000000,
  0x00000000, 0x00000000, 0x00000000, 0x00000000,
  0x00000000, 0x00000000
};

const BYTE fullspiral_48x40_vp8_g75[56] = {
  0x0F, 0xF0, 0x01, 0x01,
  0x10, 0x10, 0x0F, 0x0F,
  0x0F, 0xF0, 0xF0, 0xF0,
  0x01, 0x01, 0x01, 0x01,
  0x10, 0x10, 0x10, 0x10,
  0x0F, 0x0F, 0x0F, 0x0F,
  0x0F, 0xF0, 0xF0, 0xF0,
  0xF0, 0x0F, 0x01, 0x01,
  0x01, 0x01, 0x01, 0x01,
  0x10, 0x10, 0x10, 0x10,
  0x10, 0x10, 0x0F, 0x0F,
  0x0F, 0x0F, 0x0F, 0x0F,
  0x0F, 0xF0, 0xF0, 0xF0,
  0xF0, 0xF0, 0xF0, 0xF0
};

const BYTE rasterscan_48x40_vp8_g75[56] = {
  0x11, 0x01, 0x01, 0x01,
  0x11, 0x01, 0x01, 0x01,
  0x11, 0x01, 0x01, 0x01,
  0x11, 0x01, 0x01, 0x01,
  0x11, 0x01, 0x01, 0x01,
  0x01, 0x01, 0x01, 0x01,
  0x00, 0x01, 0x01, 0x01,
  0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00
};

const BYTE diamond_vp8_g75[56] = {
  0x0F, 0xF1, 0x0F, 0x12,	//5
  0x0D, 0xE2, 0x22, 0x1E,	//9
  0x10, 0xFF, 0xE2, 0x20,	//13
  0xFC, 0x06, 0xDD,		//16
  0x2E, 0xF1, 0x3F, 0xD3, 0x11, 0x3D, 0xF3, 0x1F,	//24
  0xEB, 0xF1, 0xF1, 0xF1,	//28
  0x4E, 0x11, 0x12, 0xF2, 0xF1,	//33
  0xE0, 0xFF, 0xFF, 0x0D, 0x1F, 0x1F,	//39
  0x20, 0x11, 0xCF, 0xF1, 0x05, 0x11,	//45
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	//51
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


const UINT16 mv_ref_cost_context_vp8_g75[6][4][2] = {
  {{1328, 10},
   {2047, 1},
   {2047, 1},
   {214, 304},
   },
  {{1072, 21},
   {979, 27},
   {1072, 21},
   {321, 201},
   },
  {{235, 278},
   {511, 107},
   {553, 93},
   {488, 115},
   },
  {{534, 99},
   {560, 92},
   {255, 257},
   {505, 109},
   },
  {{174, 361},
   {238, 275},
   {255, 257},
   {744, 53},
   },
  {{32, 922},
   {113, 494},
   {255, 257},
   {816, 43},
   },
};

static const UINT16 mb_mode_cost_luma_vp8_g75[10] =
  { 657, 869, 915, 917, 208, 0, 0, 0, 0, 0 };

static const UINT16 block_mode_cost_vp8_g75[10][10][10] = {
  {
   {37, 1725, 1868, 1151, 1622, 2096, 2011, 1770, 2218, 2128},
   {139, 759, 1683, 911, 1455, 1846, 1570, 1295, 1792, 1648},
   {560, 1383, 408, 639, 1612, 1174, 1562, 1736, 847, 991},
   {191, 1293, 1299, 466, 1774, 1840, 1784, 1691, 1698, 1505},
   {211, 1624, 1294, 779, 714, 1622, 2222, 1554, 1706, 903},
   {297, 1259, 1098, 1062, 1583, 618, 1053, 1889, 851, 1127},
   {275, 703, 1356, 1111, 1597, 1075, 656, 1529, 1531, 1275},
   {150, 1046, 1760, 1039, 1353, 1981, 2174, 728, 1730, 1379},
   {516, 1414, 741, 1045, 1495, 738, 1288, 1619, 442, 1200},
   {424, 1365, 706, 825, 1197, 1453, 1191, 1462, 1186, 519},

   },
  {
   {393, 515, 1491, 549, 1598, 1524, 964, 1126, 1651, 2172},
   {693, 237, 1954, 641, 1525, 2073, 1183, 971, 1973, 2235},
   {560, 739, 855, 836, 1224, 1115, 966, 839, 1076, 767},
   {657, 368, 1406, 425, 1672, 1853, 1210, 1125, 1969, 1542},
   {321, 1056, 1776, 774, 803, 3311, 1265, 1177, 1366, 636},
   {693, 510, 949, 877, 1049, 658, 882, 1178, 1515, 1111},
   {744, 377, 1278, 958, 1576, 1168, 477, 1146, 1838, 1501},
   {488, 477, 1767, 973, 1107, 1511, 1773, 486, 1527, 1449},
   {744, 1004, 695, 1012, 1326, 834, 1215, 774, 724, 704},
   {522, 567, 1036, 1082, 1039, 1333, 873, 1135, 1189, 677},

   },
  {
   {103, 1441, 1000, 864, 1513, 1928, 1832, 1916, 1663, 1567},
   {304, 872, 1100, 515, 1416, 1417, 3463, 1051, 1305, 1227},
   {684, 2176, 242, 729, 1867, 1496, 2056, 1544, 1038, 930},
   {534, 1198, 669, 300, 1805, 1377, 2165, 1894, 1249, 1153},
   {346, 1602, 1178, 612, 997, 3381, 1335, 1328, 997, 646},
   {393, 1027, 649, 813, 1276, 945, 1545, 1278, 875, 1031},
   {528, 996, 930, 617, 1086, 1190, 621, 2760, 787, 1347},
   {216, 873, 1595, 738, 1339, 3896, 3898, 743, 1343, 1605},
   {675, 1580, 543, 749, 1859, 1245, 1589, 2377, 384, 1075},
   {594, 1163, 415, 684, 1474, 1080, 1491, 1478, 1077, 801},
   },
  {
   {238, 1131, 1483, 398, 1510, 1651, 1495, 1545, 1970, 2090},
   {499, 456, 1499, 449, 1558, 1691, 1272, 969, 2114, 2116},
   {675, 1386, 318, 645, 1449, 1588, 1666, 1925, 979, 859},
   {467, 957, 1223, 238, 1825, 1704, 1608, 1560, 1665, 1376},
   {331, 1460, 1238, 627, 787, 1882, 3928, 1544, 1897, 579},
   {457, 1038, 903, 784, 1158, 725, 955, 1517, 842, 1016},
   {505, 497, 1131, 812, 1508, 1206, 703, 1072, 1254, 1256},
   {397, 741, 1336, 642, 1506, 1852, 1340, 599, 1854, 1000},
   {625, 1212, 597, 750, 1291, 1057, 1401, 1401, 527, 954},
   {499, 1041, 654, 752, 1299, 1217, 1605, 1424, 1377, 505},
   },
  {
   {263, 1094, 1218, 602, 938, 1487, 1231, 1016, 1724, 1448},
   {452, 535, 1728, 562, 1008, 1471, 1473, 873, 3182, 1136},
   {553, 1570, 935, 1093, 826, 1339, 879, 1007, 1006, 476},
   {365, 900, 1050, 582, 866, 1398, 1236, 1123, 1608, 1039},
   {294, 2044, 1790, 1143, 430, 1642, 3688, 1549, 2080, 704},
   {703, 1210, 958, 815, 1211, 960, 623, 2455, 815, 559},
   {675, 574, 862, 1261, 866, 864, 761, 1267, 1014, 936},
   {342, 1254, 1857, 989, 612, 1856, 1858, 553, 1840, 1037},
   {553, 1316, 811, 1072, 1068, 728, 1328, 1317, 1064, 475},
   {288, 1303, 1167, 1167, 823, 1634, 1636, 2497, 1294, 491},
   },
  {
   {227, 1059, 1369, 1066, 1505, 740, 970, 1511, 972, 1775},
   {516, 587, 1033, 646, 1188, 748, 978, 1445, 1294, 1450},
   {684, 1048, 663, 747, 1126, 826, 1386, 1128, 635, 924},
   {494, 814, 933, 510, 1606, 951, 878, 1344, 1031, 1347},
   {553, 1071, 1327, 726, 809, 3376, 1330, 1324, 1062, 407},
   {625, 1120, 988, 1121, 1197, 347, 1064, 1308, 862, 1206},
   {633, 853, 1657, 1073, 1662, 634, 460, 1405, 811, 1155},
   {505, 621, 1394, 876, 1394, 876, 878, 795, 878, 1399},
   {684, 1302, 968, 1704, 1280, 561, 972, 1713, 387, 1104},
   {397, 1447, 1060, 867, 957, 1058, 749, 1475, 1210, 660},
   },
  {
   {331, 933, 1647, 761, 1647, 998, 513, 1402, 1461, 2219},
   {573, 485, 1968, 641, 1570, 1198, 588, 1086, 1382, 1982},
   {790, 942, 570, 790, 1607, 1005, 938, 1193, 714, 751},
   {511, 745, 1152, 492, 1878, 1206, 596, 1867, 1617, 1157},
   {452, 1308, 896, 896, 451, 1308, 3354, 1301, 1306, 794},
   {693, 670, 1072, 1020, 1687, 566, 488, 1432, 1096, 3142},
   {778, 566, 1993, 1283, 3139, 1251, 227, 1378, 1784, 1447},
   {393, 937, 1091, 934, 939, 1348, 1092, 579, 1351, 1095},
   {560, 1013, 1007, 1014, 1011, 644, 1165, 1155, 605, 1016},
   {567, 627, 997, 793, 2562, 998, 849, 1260, 922, 748},
   },
  {
   {338, 762, 1868, 717, 1247, 1757, 1263, 535, 1751, 2162},
   {488, 442, 3235, 756, 1658, 1814, 1264, 528, 1857, 2119},
   {522, 1087, 840, 1103, 843, 1354, 1098, 888, 946, 588},
   {483, 688, 1502, 651, 1213, 1446, 1397, 491, 1908, 1253},
   {452, 1386, 1910, 1175, 298, 1507, 3553, 930, 1904, 905},
   {713, 839, 716, 715, 932, 719, 931, 848, 3088, 1042},
   {516, 495, 1331, 1340, 1331, 1069, 665, 702, 1593, 1337},
   {401, 977, 2167, 1537, 1069, 1764, 3810, 259, 3624, 1578},
   {560, 1104, 601, 1371, 965, 658, 2704, 779, 967, 969},
   {547, 1057, 801, 1141, 1133, 1397, 937, 605, 1252, 631},
   },
  {
   {163, 1240, 925, 983, 1653, 1321, 1353, 1566, 946, 1601},
   {401, 726, 758, 836, 1241, 926, 1656, 795, 1394, 1396},
   {905, 1073, 366, 876, 1436, 1576, 1732, 2432, 459, 1019},
   {594, 922, 835, 417, 1387, 1124, 1098, 2042, 843, 1023},
   {415, 1262, 860, 1274, 758, 1272, 3318, 1010, 1276, 503},
   {641, 1018, 1020, 1095, 1619, 667, 1371, 2348, 397, 849},
   {560, 817, 903, 1014, 1420, 695, 756, 904, 821, 1421},
   {406, 596, 1001, 993, 1257, 1258, 1260, 746, 1002, 1264},
   {979, 1371, 780, 1188, 1693, 1024, 1286, 1699, 183, 1405},
   {733, 1292, 458, 884, 1554, 889, 1151, 1286, 738, 740},
   },
  {
   {109, 1377, 1177, 933, 1140, 1928, 1639, 1705, 1861, 1292},
   {342, 570, 1081, 638, 1154, 1231, 1339, 1342, 1750, 1494},
   {560, 1203, 345, 767, 1325, 1681, 1425, 1905, 1205, 786},
   {406, 1027, 1011, 410, 1306, 1901, 1389, 1636, 1493, 776},
   {206, 1329, 1337, 1037, 802, 1600, 3646, 1451, 1603, 693},
   {472, 1167, 758, 911, 1424, 703, 2749, 1428, 703, 764},
   {342, 780, 1139, 889, 1290, 1139, 781, 1544, 957, 1042},
   {227, 888, 1039, 929, 988, 3753, 1707, 818, 1710, 1306},
   {767, 1055, 627, 725, 1312, 980, 1065, 1324, 599, 811},
   {304, 1372, 888, 1173, 979, 1578, 1580, 1974, 1318, 482},
   }
};

VOID
media_interface_setup_mbpak (MEDIA_ENCODER_CTX * encoder_context)
{
  MBPAK_CONTEXT *mbpak_ctx = &encoder_context->mbpak_context;
  MEDIA_GPE_CTX *mbpak_gpe_ctx = &mbpak_ctx->gpe_context;
  struct gen6_interface_descriptor_data *desc;
  INT i;
  dri_bo *bo;
  BYTE *desc_ptr;
  bo = mbpak_ctx->gpe_context.dynamic_state.res.bo;
  dri_bo_map (bo, 1);
  MEDIA_DRV_ASSERT (bo->virtual);
  desc_ptr = (BYTE *) bo->virtual + mbpak_gpe_ctx->idrt_offset;
  desc = (struct gen6_interface_descriptor_data *) desc_ptr;

  for (i = 0; i < mbpak_gpe_ctx->num_kernels; i++)
    {
      MEDIA_KERNEL *kernel;
      kernel = &mbpak_gpe_ctx->kernels[i];
      MEDIA_DRV_ASSERT (sizeof (*desc) == 32);
      /*Setup the descritor table */
      memset (desc, 0, sizeof (*desc));
      desc->desc0.kernel_start_pointer = kernel->kernel_offset >> 6;
      desc->desc2.sampler_count = 0;	/* FIXME: */
      desc->desc2.sampler_state_pointer = 0;
      desc->desc3.binding_table_entry_count = 0;	//1; /* FIXME: */
      desc->desc3.binding_table_pointer = (BINDING_TABLE_OFFSET (0) >> 5);
      desc->desc4.constant_urb_entry_read_offset = 0;
      desc->desc4.constant_urb_entry_read_length = (mbpak_gpe_ctx->curbe_size + 31) >> 5;	//CURBE_URB_ENTRY_LENGTH;
      desc++;
    }
  dri_bo_unmap (bo);
}

VOID
media_interface_setup_mbenc (MEDIA_ENCODER_CTX * encoder_context)
{
  MBENC_CONTEXT *mbenc_ctx = &encoder_context->mbenc_context;
  MEDIA_GPE_CTX *mbenc_gpe_ctx = &mbenc_ctx->gpe_context;
  struct gen6_interface_descriptor_data *desc;
  INT i;
  dri_bo *bo;
  BYTE *desc_ptr;

  bo = mbenc_ctx->gpe_context.dynamic_state.res.bo;
  dri_bo_map (bo, 1);
  MEDIA_DRV_ASSERT (bo->virtual);
  desc_ptr = (BYTE *) bo->virtual + mbenc_gpe_ctx->idrt_offset;

  desc = (struct gen6_interface_descriptor_data *) desc_ptr;
  for (i = 0; i < mbenc_gpe_ctx->num_kernels; i++)
    {
      MEDIA_KERNEL *kernel;
      kernel = &mbenc_gpe_ctx->kernels[i];
      MEDIA_DRV_ASSERT (sizeof (*desc) == 32);
      /*Setup the descritor table */
      memset (desc, 0, sizeof (*desc));
      desc->desc0.kernel_start_pointer = kernel->kernel_offset >> 6;
      desc->desc2.sampler_count = 0;	/* FIXME: */
      desc->desc2.sampler_state_pointer = 0;
      desc->desc3.binding_table_entry_count = 0;	//1; /* FIXME: */
      desc->desc3.binding_table_pointer = (BINDING_TABLE_OFFSET (0) >> 5);
      desc->desc4.constant_urb_entry_read_offset = 0;
      desc->desc4.constant_urb_entry_read_length = (mbenc_gpe_ctx->curbe_size + 31) >> 5;	//CURBE_URB_ENTRY_LENGTH;
      desc++;
    }
  dri_bo_unmap (bo);
}

VOID
  media_encode_init_mbenc_constant_buffer_vp8_g75
  (MBENC_CONSTANT_BUFFER_PARAMS_VP8 * params)
{
  BYTE *cost_luma_buf, *block_mode_cost;
  BOOL status;
  cost_luma_buf =
    (BYTE *) media_map_buffer_obj (params->mb_mode_cost_luma_buffer->bo);
  MEDIA_DRV_ASSERT (cost_luma_buf);

  media_drv_memset (cost_luma_buf,
		    params->mb_mode_cost_luma_buffer->pitch *
		    params->mb_mode_cost_luma_buffer->height);

  //fill surface with VP8_MB_MODE_COST_LUMA table for I frame
  status = media_drv_memcpy (cost_luma_buf,
			     sizeof (mb_mode_cost_luma_vp8_g75),
			     (VOID *) mb_mode_cost_luma_vp8_g75,
			     sizeof (mb_mode_cost_luma_vp8_g75));
  if (status != TRUE)
    {
      media_unmap_buffer_obj (params->mb_mode_cost_luma_buffer->bo);
      MEDIA_DRV_ASSERT ("media_drv_memcpy failed");
    }
  media_unmap_buffer_obj (params->mb_mode_cost_luma_buffer->bo);
  block_mode_cost = media_map_buffer_obj (params->block_mode_cost_buffer->bo);
  MEDIA_DRV_ASSERT (block_mode_cost);

  media_drv_memset (block_mode_cost,
		    params->block_mode_cost_buffer->pitch *
		    params->block_mode_cost_buffer->height);

  status = media_drv_memcpy (block_mode_cost,
			     sizeof (block_mode_cost_vp8_g75),
			     (VOID *) block_mode_cost_vp8_g75,
			     sizeof (block_mode_cost_vp8_g75));
  if (status != TRUE)
    {
      media_unmap_buffer_obj (params->block_mode_cost_buffer->bo);
      MEDIA_DRV_ASSERT ("media_drv_memcpy failed");
    }
  media_unmap_buffer_obj (params->block_mode_cost_buffer->bo);
}

VOID
media_set_curbe_vp8_mbpak (struct encode_state *encode_state,
			   MEDIA_MBPAK_CURBE_PARAMS_VP8 * params)
{
  VAQMatrixBufferVP8 *quant_params =
    (VAQMatrixBufferVP8 *) encode_state->q_matrix->buffer;
  VAEncSequenceParameterBufferVP8 *seq_params =
    (VAEncSequenceParameterBufferVP8 *) encode_state->seq_param_ext->buffer;
  VAEncPictureParameterBufferVP8 *pic_params =
    (VAEncPictureParameterBufferVP8 *) encode_state->pic_param_ext->buffer;
  UINT shift_factor, mul_factor;
  UINT16 y_quanta_ac_idx, y_quanta_dc_idx, uv_quanta_dc_idx,
    uv_quanta_ac_idx, y2_quanta_ac_idx, y2_quanta_dc_idx;
  // qIndex should be the sum of base and delta qp values.
  y_quanta_ac_idx = quant_params->quantization_index[0];	/* Use entry 0 as for BDW segmentation is disabled */
  y_quanta_dc_idx =
    y_quanta_ac_idx +
    quant_params->quantization_index_delta[QUAND_INDEX_Y1_DC_VP8];
  uv_quanta_dc_idx =
    y_quanta_ac_idx +
    quant_params->quantization_index_delta[QUAND_INDEX_UV_DC_VP8];
  uv_quanta_ac_idx =
    y_quanta_ac_idx +
    quant_params->quantization_index_delta[QUAND_INDEX_UV_AC_VP8];
  y2_quanta_dc_idx =
    y_quanta_ac_idx +
    quant_params->quantization_index_delta[QUAND_INDEX_Y2_DC_VP8];
  y2_quanta_ac_idx =
    y_quanta_ac_idx +
    quant_params->quantization_index_delta[QUAND_INDEX_Y2_AC_VP8];

  shift_factor = 16;
  mul_factor = 1 << shift_factor;

  if (params->pak_phase_type == MBPAK_HYBRID_STATE_P1)
    {
      MEDIA_CURBE_DATA_MBPAK_P1_G75 *cmd =
	(MEDIA_CURBE_DATA_MBPAK_P1_G75 *) params->curbe_cmd_buff;


      if (params->updated == TRUE)
	{
	  cmd->dw40.pak_per_mb_out_data_surf_bti = VP8_MBPAK_PER_MB_OUT_G75;
	  cmd->dw41.mb_enc_curr_y_bti = VP8_MBPAK_CURR_Y_G75;
	  cmd->dw42.pak_recon_y_bti = VP8_MBPAK_CURR_RECON_Y_G75;
	  cmd->dw43.pak_last_ref_pic_y_bti = VP8_MBPAK_LAST_REF_Y_G75;
	  cmd->dw44.pak_golden_ref_pic_y_bti = VP8_MBPAK_GOLDEN_REF_Y_G75;
	  cmd->dw45.pak_alternate_ref_pic_y_bti =
	    VP8_MBPAK_ALTERNATE_REF_Y_G75;
	  cmd->dw46.pak_ind_mv_data_bti = VP8_MBPAK_IND_MV_DATA_G75;
	  cmd->dw47.pak_kernel_debug_bti = VP8_MBPAK_DEBUG_STREAMOUT_G75;

	  return;
	}

      cmd->dw0.frame_width = (seq_params->frame_width + 15) & (~0xF);	/* kernel require MB boundary aligned dimensions */
      cmd->dw0.frame_height = (seq_params->frame_height + 15) & (~0xF);

      cmd->dw1.frame_type = 1;	/* phase1 is always for P frames only */
      cmd->dw1.recon_filter_type =
	(pic_params->pic_flags.bits.version == 0) ? 0 /*6-tap filter */ :
	((pic_params->pic_flags.bits.version == 3) ? 2
	 /*full pixel mvs for chroma,half pixel mvs derived using bilinear filter for luma */
	 : 1 /*bilinear filter */ );
      cmd->dw1.clamping_flag = pic_params->pic_flags.bits.clamping_type;

      cmd->dw2.y_dc_q_mul_factor_segment0 =
	mul_factor / quant_dc_vp8_g75[y_quanta_dc_idx];
      cmd->dw2.y_ac_q_mul_factor_segment0 =
	mul_factor / quant_ac_vp8_g75[y_quanta_ac_idx];

      cmd->dw3.y2_dc_q_mul_factor_segment0 =
	mul_factor / quant_dc2_vp8_g75[y2_quanta_dc_idx];
      cmd->dw3.y2_ac_q_mul_factor_segment0 =
	mul_factor / quant_ac2_vp8_g75[y2_quanta_ac_idx];

      cmd->dw4.uv_dc_q_mul_factor_segment0 =
	mul_factor / quant_dc_uv_vp8_g75[uv_quanta_dc_idx];
      cmd->dw4.uv_ac_q_mul_factor_segment0 =
	mul_factor / quant_ac_vp8_g75[uv_quanta_ac_idx];

      cmd->dw5.y_dc_inv_q_mul_factor_segment0 =
	quant_dc_vp8_g75[y_quanta_dc_idx];
      cmd->dw5.y_ac_inv_q_mul_factor_segment0 =
	quant_ac_vp8_g75[y_quanta_ac_idx];

      cmd->dw6.y2_dc_inv_q_mul_factor_segment0 =
	quant_dc2_vp8_g75[y2_quanta_dc_idx];
      cmd->dw6.y2_ac_inv_q_mul_factor_segment0 =
	quant_ac2_vp8_g75[y2_quanta_ac_idx];

      cmd->dw7.uv_dc_inv_q_mul_factor_segment0 =
	quant_dc_uv_vp8_g75[uv_quanta_dc_idx];
      cmd->dw7.uv_ac_inv_q_mul_factor_segment0 =
	quant_ac_vp8_g75[uv_quanta_ac_idx];

      cmd->dw8.y2_dc_q_shift_factor_segment0 = shift_factor;
      cmd->dw8.y2_ac_q_shift_factor_segment0 = shift_factor;
      cmd->dw8.y_dc_q_shift_factor_segment0 = shift_factor;
      cmd->dw8.y_ac_q_shift_factor_segment0 = shift_factor;

      cmd->dw9.uv_dc_q_shift_factor_segment0 = shift_factor;
      cmd->dw9.uv_ac_q_shift_factor_segment0 = shift_factor;

      if (pic_params->pic_flags.bits.segmentation_enabled)
	{
	  y_quanta_ac_idx = quant_params->quantization_index[1];
	  y_quanta_dc_idx =
	    y_quanta_ac_idx +
	    quant_params->quantization_index_delta[QUAND_INDEX_Y1_DC_VP8];
	  uv_quanta_dc_idx =
	    y_quanta_ac_idx +
	    quant_params->quantization_index_delta[QUAND_INDEX_UV_DC_VP8];
	  uv_quanta_ac_idx =
	    y_quanta_ac_idx +
	    quant_params->quantization_index_delta[QUAND_INDEX_UV_AC_VP8];
	  y2_quanta_dc_idx =
	    y_quanta_ac_idx +
	    quant_params->quantization_index_delta[QUAND_INDEX_Y2_DC_VP8];
	  y2_quanta_ac_idx =
	    y_quanta_ac_idx +
	    quant_params->quantization_index_delta[QUAND_INDEX_Y2_AC_VP8];

	  cmd->dw10.y_dc_q_mul_factor_segment1 =
	    mul_factor / quant_dc_vp8_g75[y_quanta_dc_idx];
	  cmd->dw10.y_ac_q_mul_factor_segment1 =
	    mul_factor / quant_ac_vp8_g75[y_quanta_ac_idx];

	  cmd->dw11.y2_dc_q_mul_factor_segment1 =
	    mul_factor / quant_dc2_vp8_g75[y2_quanta_dc_idx];
	  cmd->dw11.y2_ac_q_mul_factor_segment1 =
	    mul_factor / quant_ac2_vp8_g75[y2_quanta_ac_idx];

	  cmd->dw12.uv_dc_q_mul_factor_segment1 =
	    mul_factor / quant_dc_uv_vp8_g75[uv_quanta_dc_idx];
	  cmd->dw12.uv_ac_q_mul_factor_segment1 =
	    mul_factor / quant_ac_vp8_g75[uv_quanta_ac_idx];

	  cmd->dw13.y_dc_inv_q_mul_factor_segment1 =
	    quant_dc_vp8_g75[y_quanta_dc_idx];
	  cmd->dw13.y_ac_inv_q_mul_factor_segment1 =
	    quant_ac_vp8_g75[y_quanta_ac_idx];

	  cmd->dw14.y2_dc_inv_q_mul_factor_segment1 =
	    quant_dc2_vp8_g75[y2_quanta_dc_idx];
	  cmd->dw14.y2_ac_inv_q_mul_factor_segment1 =
	    quant_ac2_vp8_g75[y2_quanta_ac_idx];

	  cmd->dw15.uv_dc_inv_q_mul_factor_segment1 =
	    quant_dc_uv_vp8_g75[uv_quanta_dc_idx];
	  cmd->dw15.uv_ac_inv_q_mul_factor_segment1 =
	    quant_ac_vp8_g75[uv_quanta_ac_idx];

	  cmd->dw16.y2_dc_q_shift_factor_segment1 = shift_factor;
	  cmd->dw16.y2_ac_q_shift_factor_segment1 = shift_factor;
	  cmd->dw16.y_dc_q_shift_factor_segment1 = shift_factor;
	  cmd->dw16.y_ac_q_shift_factor_segment1 = shift_factor;

	  cmd->dw17.uv_dc_q_shift_factor_segment1 = shift_factor;
	  cmd->dw17.uv_ac_q_shift_factor_segment1 = shift_factor;

	  y_quanta_ac_idx = quant_params->quantization_index[2];
	  y_quanta_dc_idx =
	    y_quanta_ac_idx +
	    quant_params->quantization_index_delta[QUAND_INDEX_Y1_DC_VP8];
	  uv_quanta_dc_idx =
	    y_quanta_ac_idx +
	    quant_params->quantization_index_delta[QUAND_INDEX_UV_DC_VP8];
	  uv_quanta_ac_idx =
	    y_quanta_ac_idx +
	    quant_params->quantization_index_delta[QUAND_INDEX_UV_AC_VP8];
	  y2_quanta_dc_idx =
	    y_quanta_ac_idx +
	    quant_params->quantization_index_delta[QUAND_INDEX_Y2_DC_VP8];
	  y2_quanta_ac_idx =
	    y_quanta_ac_idx +
	    quant_params->quantization_index_delta[QUAND_INDEX_Y2_AC_VP8];

	  cmd->dw18.y_dc_q_mul_factor_segment2 =
	    mul_factor / quant_dc_vp8_g75[y_quanta_dc_idx];
	  cmd->dw18.y_ac_q_mul_factor_segment2 =
	    mul_factor / quant_ac_vp8_g75[y_quanta_ac_idx];

	  cmd->dw19.y2_dc_q_mul_factor_segment2 =
	    mul_factor / quant_dc2_vp8_g75[y2_quanta_dc_idx];
	  cmd->dw19.y2_ac_q_mul_factor_segment2 =
	    mul_factor / quant_ac2_vp8_g75[y2_quanta_ac_idx];

	  cmd->dw20.uv_dc_q_mul_factor_segment2 =
	    mul_factor / quant_dc_uv_vp8_g75[uv_quanta_dc_idx];
	  cmd->dw20.uv_ac_q_mul_factor_segment2 =
	    mul_factor / quant_ac_vp8_g75[uv_quanta_ac_idx];

	  cmd->dw21.y_dc_inv_q_mul_factor_segment2 =
	    quant_dc_vp8_g75[y_quanta_dc_idx];
	  cmd->dw21.y_ac_inv_q_mul_factor_segment2 =
	    quant_ac_vp8_g75[y_quanta_ac_idx];

	  cmd->dw22.y2_dc_inv_q_mul_factor_segment2 =
	    quant_dc2_vp8_g75[y2_quanta_dc_idx];
	  cmd->dw22.y2_ac_inv_q_mul_factor_segment2 =
	    quant_ac2_vp8_g75[y2_quanta_ac_idx];

	  cmd->dw23.uv_dc_inv_q_mul_factor_segment2 =
	    quant_dc_uv_vp8_g75[uv_quanta_dc_idx];
	  cmd->dw23.uv_ac_inv_q_mul_factor_segment2 =
	    quant_ac_vp8_g75[uv_quanta_ac_idx];

	  cmd->dw24.y2_dc_q_shift_factor_segment2 = shift_factor;
	  cmd->dw24.y2_ac_q_shift_factor_segment2 = shift_factor;
	  cmd->dw24.y_dc_q_shift_factor_segment2 = shift_factor;
	  cmd->dw24.y_ac_q_shift_factor_segment2 = shift_factor;

	  cmd->dw25.uv_dc_q_shift_factor_segment2 = shift_factor;
	  cmd->dw25.uv_ac_q_shift_factor_segment2 = shift_factor;

	  y_quanta_ac_idx = quant_params->quantization_index[3];
	  y_quanta_dc_idx =
	    y_quanta_ac_idx +
	    quant_params->quantization_index_delta[QUAND_INDEX_Y1_DC_VP8];
	  uv_quanta_dc_idx =
	    y_quanta_ac_idx +
	    quant_params->quantization_index_delta[QUAND_INDEX_UV_DC_VP8];
	  uv_quanta_ac_idx =
	    y_quanta_ac_idx +
	    quant_params->quantization_index_delta[QUAND_INDEX_UV_AC_VP8];
	  y2_quanta_dc_idx =
	    y_quanta_ac_idx +
	    quant_params->quantization_index_delta[QUAND_INDEX_Y2_DC_VP8];
	  y2_quanta_ac_idx =
	    y_quanta_ac_idx +
	    quant_params->quantization_index_delta[QUAND_INDEX_Y2_AC_VP8];

	  cmd->dw26.y_dc_q_mul_factor_segment3 =
	    mul_factor / quant_dc_vp8_g75[y_quanta_dc_idx];
	  cmd->dw26.y_ac_q_mul_factor_segment3 =
	    mul_factor / quant_ac_vp8_g75[y_quanta_ac_idx];

	  cmd->dw27.y2_dc_q_mul_factor_segment3 =
	    mul_factor / quant_dc2_vp8_g75[y2_quanta_dc_idx];
	  cmd->dw27.y2_ac_q_mul_factor_segment3 =
	    mul_factor / quant_ac2_vp8_g75[y2_quanta_ac_idx];

	  cmd->dw28.uv_dc_q_mul_factor_segment3 =
	    mul_factor / quant_dc_uv_vp8_g75[uv_quanta_dc_idx];
	  cmd->dw28.uv_ac_q_mul_factor_segment3 =
	    mul_factor / quant_ac_vp8_g75[uv_quanta_ac_idx];

	  cmd->dw29.y_dc_inv_q_mul_factor_segment3 =
	    quant_dc_vp8_g75[y_quanta_dc_idx];
	  cmd->dw29.y_ac_inv_q_mul_factor_segment3 =
	    quant_ac_vp8_g75[y_quanta_ac_idx];

	  cmd->dw30.y2_dc_inv_q_mul_factor_segment3 =
	    quant_dc2_vp8_g75[y2_quanta_dc_idx];
	  cmd->dw30.y2_ac_inv_q_mul_factor_segment3 =
	    quant_ac2_vp8_g75[y2_quanta_ac_idx];

	  cmd->dw31.uv_dc_inv_q_mul_factor_segment3 =
	    quant_dc_uv_vp8_g75[uv_quanta_dc_idx];
	  cmd->dw31.uv_ac_inv_q_mul_factor_segment3 =
	    quant_ac_vp8_g75[uv_quanta_ac_idx];

	  cmd->dw32.y2_dc_q_shift_factor_segment3 = shift_factor;
	  cmd->dw32.y2_ac_q_shift_factor_segment3 = shift_factor;
	  cmd->dw32.y_dc_q_shift_factor_segment3 = shift_factor;
	  cmd->dw32.y_ac_q_shift_factor_segment3 = shift_factor;

	  cmd->dw33.uv_dc_q_shift_factor_segment3 = shift_factor;
	  cmd->dw33.uv_ac_q_shift_factor_segment3 = shift_factor;
	}

      cmd->dw34.ref_frame_lf_delta0 = pic_params->ref_lf_delta[0];
      cmd->dw34.ref_frame_lf_delta1 = pic_params->ref_lf_delta[1];
      cmd->dw34.ref_frame_lf_delta2 = pic_params->ref_lf_delta[2];	/*referenceFrame loopfilter delta for last frame */
      cmd->dw34.ref_frame_lf_delta3 = pic_params->ref_lf_delta[3];	/*referenceFrame loopfilter delta for intra frame */

      cmd->dw35.mode_lf_delta0 = pic_params->mode_lf_delta[0];
      cmd->dw35.mode_lf_delta1 = pic_params->mode_lf_delta[1];
      cmd->dw35.mode_lf_delta2 = pic_params->mode_lf_delta[2];
      cmd->dw35.mode_lf_delta3 = pic_params->mode_lf_delta[3];

      cmd->dw36.lf_level0 = pic_params->loop_filter_level[0];
      cmd->dw36.lf_level1 = pic_params->loop_filter_level[1];
      cmd->dw36.lf_level2 = pic_params->loop_filter_level[2];
      cmd->dw36.lf_level3 = pic_params->loop_filter_level[3];

      cmd->dw40.pak_per_mb_out_data_surf_bti = VP8_MBPAK_PER_MB_OUT_G75;
      cmd->dw41.mb_enc_curr_y_bti = VP8_MBPAK_CURR_Y_G75;
      cmd->dw42.pak_recon_y_bti = VP8_MBPAK_CURR_RECON_Y_G75;
      cmd->dw43.pak_last_ref_pic_y_bti = VP8_MBPAK_LAST_REF_Y_G75;
      cmd->dw44.pak_golden_ref_pic_y_bti = VP8_MBPAK_GOLDEN_REF_Y_G75;
      cmd->dw45.pak_alternate_ref_pic_y_bti = VP8_MBPAK_ALTERNATE_REF_Y_G75;
      cmd->dw46.pak_ind_mv_data_bti = VP8_MBPAK_IND_MV_DATA_G75;
      cmd->dw47.pak_kernel_debug_bti = VP8_MBPAK_DEBUG_STREAMOUT_G75;
    }
  else
    {
      MEDIA_CURBE_DATA_MBPAK_P2_G75 *cmd =
	(MEDIA_CURBE_DATA_MBPAK_P2_G75 *) params->curbe_cmd_buff;

      if (params->updated == TRUE)
	{
	  cmd->dw40.pak_per_mb_out_data_surf_bti = VP8_MBPAK_PER_MB_OUT_G75;
	  cmd->dw41.mb_enc_curr_y_bti = VP8_MBPAK_CURR_Y_G75;
	  cmd->dw42.pak_recon_y_bti = VP8_MBPAK_CURR_RECON_Y_G75;
	  cmd->dw43.pak_row_buffer_y_bti = VP8_MBPAK_ROW_BUFF_Y_G75;
	  cmd->dw44.pak_row_buffer_uv_bti = VP8_MBPAK_ROW_BUFF_UV_G75;
	  cmd->dw45.pak_col_buffer_y_bti = VP8_MBPAK_COL_BUFF_Y_G75;
	  cmd->dw46.pak_col_buffer_uv_bti = VP8_MBPAK_COL_BUFF_UV_G75;
	  cmd->dw47.pak_kernel_debug_bti = VP8_MBPAK_DEBUG_STREAMOUT_G75;

	  return;
	}

      cmd->dw0.frame_width = (seq_params->frame_width + 15) & (~0xF);	/* kernel require MB boundary aligned dimensions */
      cmd->dw0.frame_height = (seq_params->frame_height + 15) & (~0xF);

      cmd->dw1.sharpness_level = pic_params->sharpness_level;
      cmd->dw1.loop_filter_type =
	(pic_params->pic_flags.bits.version ==
	 0) ? 0 /*normal loop filter */ : 1 /*simple loop filter */ ;
      cmd->dw1.frame_type = pic_params->pic_flags.bits.frame_type;
      cmd->dw1.clamping_flag = pic_params->pic_flags.bits.clamping_type;

      cmd->dw2.y_dc_q_mul_factor_segment0 =
	mul_factor / quant_dc_vp8_g75[y_quanta_dc_idx];
      cmd->dw2.y_ac_q_mul_factor_segment0 =
	mul_factor / quant_ac_vp8_g75[y_quanta_ac_idx];

      cmd->dw3.y2_dc_q_mul_factor_segment0 =
	mul_factor / quant_dc2_vp8_g75[y2_quanta_dc_idx];
      cmd->dw3.y2_ac_q_mul_factor_segment0 =
	mul_factor / quant_ac2_vp8_g75[y2_quanta_ac_idx];

      cmd->dw4.uv_dc_q_mul_factor_segment0 =
	mul_factor / quant_dc_uv_vp8_g75[uv_quanta_dc_idx];
      cmd->dw4.uv_ac_q_mul_factor_segment0 =
	mul_factor / quant_ac_vp8_g75[uv_quanta_ac_idx];

      cmd->dw5.y_dc_inv_q_mul_factor_segment0 =
	quant_dc_vp8_g75[y_quanta_dc_idx];
      cmd->dw5.y_ac_inv_q_mul_factor_segment0 =
	quant_ac_vp8_g75[y_quanta_ac_idx];

      cmd->dw6.y2_dc_inv_q_mul_factor_segment0 =
	quant_dc2_vp8_g75[y2_quanta_dc_idx];
      cmd->dw6.y2_ac_inv_q_mul_factor_segment0 =
	quant_ac2_vp8_g75[y2_quanta_ac_idx];

      cmd->dw7.uv_dc_inv_q_mul_factor_segment0 =
	quant_dc_uv_vp8_g75[uv_quanta_dc_idx];
      cmd->dw7.uv_ac_inv_q_mul_factor_segment0 =
	quant_ac_vp8_g75[uv_quanta_ac_idx];

      cmd->dw8.y2_dc_q_shift_factor_segment0 = shift_factor;
      cmd->dw8.y2_ac_q_shift_factor_segment0 = shift_factor;
      cmd->dw8.y_dc_q_shift_factor_segment0 = shift_factor;
      cmd->dw8.y_ac_q_shift_factor_segment0 = shift_factor;

      cmd->dw9.uv_dc_q_shift_factor_segment0 = shift_factor;
      cmd->dw9.uv_ac_q_shift_factor_segment0 = shift_factor;

      if (pic_params->pic_flags.bits.segmentation_enabled)
	{
	  y_quanta_ac_idx = quant_params->quantization_index[1];
	  y_quanta_dc_idx =
	    y_quanta_ac_idx +
	    quant_params->quantization_index_delta[QUAND_INDEX_Y1_DC_VP8];
	  uv_quanta_dc_idx =
	    y_quanta_ac_idx +
	    quant_params->quantization_index_delta[QUAND_INDEX_UV_DC_VP8];
	  uv_quanta_ac_idx =
	    y_quanta_ac_idx +
	    quant_params->quantization_index_delta[QUAND_INDEX_UV_AC_VP8];
	  y2_quanta_dc_idx =
	    y_quanta_ac_idx +
	    quant_params->quantization_index_delta[QUAND_INDEX_Y2_DC_VP8];
	  y2_quanta_ac_idx =
	    y_quanta_ac_idx +
	    quant_params->quantization_index_delta[QUAND_INDEX_Y2_AC_VP8];

	  cmd->dw10.y_dc_q_mul_factor_segment1 =
	    mul_factor / quant_dc_vp8_g75[y_quanta_dc_idx];
	  cmd->dw10.y_ac_q_mul_factor_segment1 =
	    mul_factor / quant_ac_vp8_g75[y_quanta_ac_idx];

	  cmd->dw11.y2_dc_q_mul_factor_segment1 =
	    mul_factor / quant_dc2_vp8_g75[y2_quanta_dc_idx];
	  cmd->dw11.y2_ac_q_mul_factor_segment1 =
	    mul_factor / quant_ac2_vp8_g75[y2_quanta_ac_idx];

	  cmd->dw12.uv_dc_q_mul_factor_segment1 =
	    mul_factor / quant_dc_uv_vp8_g75[uv_quanta_dc_idx];
	  cmd->dw12.uv_ac_q_mul_factor_segment1 =
	    mul_factor / quant_ac_vp8_g75[uv_quanta_ac_idx];

	  cmd->dw13.y_dc_inv_q_mul_factor_segment1 =
	    quant_dc_vp8_g75[y_quanta_dc_idx];
	  cmd->dw13.y_ac_inv_q_mul_factor_segment1 =
	    quant_ac_vp8_g75[y_quanta_ac_idx];

	  cmd->dw14.y2_dc_inv_q_mul_factor_segment1 =
	    quant_dc2_vp8_g75[y2_quanta_dc_idx];
	  cmd->dw14.y2_ac_inv_q_mul_factor_segment1 =
	    quant_ac2_vp8_g75[y2_quanta_ac_idx];

	  cmd->dw15.uv_dc_inv_q_mul_factor_segment1 =
	    quant_dc_uv_vp8_g75[uv_quanta_dc_idx];
	  cmd->dw15.uv_ac_inv_q_mul_factor_segment1 =
	    quant_ac_vp8_g75[uv_quanta_ac_idx];

	  cmd->dw16.y2_dc_q_shift_factor_segment1 = shift_factor;
	  cmd->dw16.y2_ac_q_shift_factor_segment1 = shift_factor;
	  cmd->dw16.y_dc_q_shift_factor_segment1 = shift_factor;
	  cmd->dw16.y_ac_q_shift_factor_segment1 = shift_factor;

	  cmd->dw17.uv_dc_q_shift_factor_segment1 = shift_factor;
	  cmd->dw17.uv_ac_q_shift_factor_segment1 = shift_factor;

	  y_quanta_ac_idx = quant_params->quantization_index[2];
	  y_quanta_dc_idx =
	    y_quanta_ac_idx +
	    quant_params->quantization_index_delta[QUAND_INDEX_Y1_DC_VP8];
	  uv_quanta_dc_idx =
	    y_quanta_ac_idx +
	    quant_params->quantization_index_delta[QUAND_INDEX_UV_DC_VP8];
	  uv_quanta_ac_idx =
	    y_quanta_ac_idx +
	    quant_params->quantization_index_delta[QUAND_INDEX_UV_AC_VP8];
	  y2_quanta_dc_idx =
	    y_quanta_ac_idx +
	    quant_params->quantization_index_delta[QUAND_INDEX_Y2_DC_VP8];
	  y2_quanta_ac_idx =
	    y_quanta_ac_idx +
	    quant_params->quantization_index_delta[QUAND_INDEX_Y2_AC_VP8];

	  cmd->dw18.y_dc_q_mul_factor_segment2 =
	    mul_factor / quant_dc_vp8_g75[y_quanta_dc_idx];
	  cmd->dw18.y_ac_q_mul_factor_segment2 =
	    mul_factor / quant_ac_vp8_g75[y_quanta_ac_idx];

	  cmd->dw19.y2_dc_q_mul_factor_segment2 =
	    mul_factor / quant_dc2_vp8_g75[y2_quanta_dc_idx];
	  cmd->dw19.y2_ac_q_mul_factor_segment2 =
	    mul_factor / quant_ac2_vp8_g75[y2_quanta_ac_idx];

	  cmd->dw20.uv_dc_q_mul_factor_segment2 =
	    mul_factor / quant_dc_uv_vp8_g75[uv_quanta_dc_idx];
	  cmd->dw20.uv_ac_q_mul_factor_segment2 =
	    mul_factor / quant_ac_vp8_g75[uv_quanta_ac_idx];

	  cmd->dw21.y_dc_inv_q_mul_factor_segment2 =
	    quant_dc_vp8_g75[y_quanta_dc_idx];
	  cmd->dw21.y_ac_inv_q_mul_factor_segment2 =
	    quant_ac_vp8_g75[y_quanta_ac_idx];

	  cmd->dw22.y2_dc_inv_q_mul_factor_segment2 =
	    quant_dc2_vp8_g75[y2_quanta_dc_idx];
	  cmd->dw22.y2_ac_inv_q_mul_factor_segment2 =
	    quant_ac2_vp8_g75[y2_quanta_ac_idx];

	  cmd->dw23.uv_dc_inv_q_mul_factor_segment2 =
	    quant_dc_uv_vp8_g75[uv_quanta_dc_idx];
	  cmd->dw23.uv_ac_inv_q_mul_factor_segment2 =
	    quant_ac_vp8_g75[uv_quanta_ac_idx];

	  cmd->dw24.y2_dc_q_shift_factor_segment2 = shift_factor;
	  cmd->dw24.y2_ac_q_shift_factor_segment2 = shift_factor;
	  cmd->dw24.y_dc_q_shift_factor_segment2 = shift_factor;
	  cmd->dw24.y_ac_q_shift_factor_segment2 = shift_factor;

	  cmd->dw25.uv_dc_q_shift_factor_segment2 = shift_factor;
	  cmd->dw25.uv_ac_q_shift_factor_segment2 = shift_factor;

	  y_quanta_ac_idx = quant_params->quantization_index[3];
	  y_quanta_dc_idx =
	    y_quanta_ac_idx +
	    quant_params->quantization_index_delta[QUAND_INDEX_Y1_DC_VP8];
	  uv_quanta_dc_idx =
	    y_quanta_ac_idx +
	    quant_params->quantization_index_delta[QUAND_INDEX_UV_DC_VP8];
	  uv_quanta_ac_idx =
	    y_quanta_ac_idx +
	    quant_params->quantization_index_delta[QUAND_INDEX_UV_AC_VP8];
	  y2_quanta_dc_idx =
	    y_quanta_ac_idx +
	    quant_params->quantization_index_delta[QUAND_INDEX_Y2_DC_VP8];
	  y2_quanta_ac_idx =
	    y_quanta_ac_idx +
	    quant_params->quantization_index_delta[QUAND_INDEX_Y2_AC_VP8];

	  cmd->dw26.y_dc_q_mul_factor_segment3 =
	    mul_factor / quant_dc_vp8_g75[y_quanta_dc_idx];
	  cmd->dw26.y_ac_q_mul_factor_segment3 =
	    mul_factor / quant_ac_vp8_g75[y_quanta_ac_idx];

	  cmd->dw27.y2_dc_q_mul_factor_segment3 =
	    mul_factor / quant_dc2_vp8_g75[y2_quanta_dc_idx];
	  cmd->dw27.y2_ac_q_mul_factor_segment3 =
	    mul_factor / quant_ac2_vp8_g75[y2_quanta_ac_idx];

	  cmd->dw28.uv_dc_q_mul_factor_segment3 =
	    mul_factor / quant_dc_uv_vp8_g75[uv_quanta_dc_idx];
	  cmd->dw28.uv_ac_q_mul_factor_segment3 =
	    mul_factor / quant_ac_vp8_g75[uv_quanta_ac_idx];

	  cmd->dw29.y_dc_inv_q_mul_factor_segment3 =
	    quant_dc_vp8_g75[y_quanta_dc_idx];
	  cmd->dw29.y_ac_inv_q_mul_factor_segment3 =
	    quant_ac_vp8_g75[y_quanta_ac_idx];

	  cmd->dw30.y2_dc_inv_q_mul_factor_segment3 =
	    quant_dc2_vp8_g75[y2_quanta_dc_idx];
	  cmd->dw30.y2_ac_inv_q_mul_factor_segment3 =
	    quant_ac2_vp8_g75[y2_quanta_ac_idx];

	  cmd->dw31.uv_dc_inv_q_mul_factor_segment3 =
	    quant_dc_uv_vp8_g75[uv_quanta_dc_idx];
	  cmd->dw31.uv_ac_inv_q_mul_factor_segment3 =
	    quant_ac_vp8_g75[uv_quanta_ac_idx];

	  cmd->dw32.y2_dc_q_shift_factor_segment3 = shift_factor;
	  cmd->dw32.y2_ac_q_shift_factor_segment3 = shift_factor;
	  cmd->dw32.y_dc_q_shift_factor_segment3 = shift_factor;
	  cmd->dw32.y_ac_q_shift_factor_segment3 = shift_factor;

	  cmd->dw33.uv_dc_q_shift_factor_segment3 = shift_factor;
	  cmd->dw33.uv_ac_q_shift_factor_segment3 = shift_factor;
	}

      cmd->dw34.ref_frame_lf_delta0 = pic_params->ref_lf_delta[0];	/*referenceframe loopfilter delta for alt ref frame */
      cmd->dw34.ref_frame_lf_delta1 = pic_params->ref_lf_delta[1];	/*referenceframe loopfilter delta for golden frame */
      cmd->dw34.ref_frame_lf_delta2 = pic_params->ref_lf_delta[2];	/*referenceframe loopfilter delta for last frame */
      cmd->dw34.ref_frame_lf_delta3 = pic_params->ref_lf_delta[3];	/*referenceframe loopfilter delta for intra frame */

      cmd->dw35.mode_lf_delta0 = pic_params->mode_lf_delta[0];
      cmd->dw35.mode_lf_delta1 = pic_params->mode_lf_delta[1];
      cmd->dw35.mode_lf_delta2 = pic_params->mode_lf_delta[2];
      cmd->dw35.mode_lf_delta3 = pic_params->mode_lf_delta[3];

      cmd->dw36.lf_level0 = pic_params->loop_filter_level[0];
      cmd->dw36.lf_level1 = pic_params->loop_filter_level[1];
      cmd->dw36.lf_level2 = pic_params->loop_filter_level[2];
      cmd->dw36.lf_level3 = pic_params->loop_filter_level[3];

      cmd->dw40.pak_per_mb_out_data_surf_bti = VP8_MBPAK_PER_MB_OUT_G75;
      cmd->dw41.mb_enc_curr_y_bti = VP8_MBPAK_CURR_Y_G75;
      cmd->dw42.pak_recon_y_bti = VP8_MBPAK_CURR_RECON_Y_G75;
      cmd->dw43.pak_row_buffer_y_bti = VP8_MBPAK_ROW_BUFF_Y_G75;
      cmd->dw44.pak_row_buffer_uv_bti = VP8_MBPAK_ROW_BUFF_UV_G75;
      cmd->dw45.pak_col_buffer_y_bti = VP8_MBPAK_COL_BUFF_Y_G75;
      cmd->dw46.pak_col_buffer_uv_bti = VP8_MBPAK_COL_BUFF_UV_G75;
      cmd->dw47.pak_kernel_debug_bti = VP8_MBPAK_DEBUG_STREAMOUT_G75;
    }

}

VOID
media_set_curbe_i_vp8_mbenc (struct encode_state *encode_state,
			     MEDIA_MBENC_CURBE_PARAMS_VP8 * params)
{

  VAQMatrixBufferVP8 *quant_params =
    (VAQMatrixBufferVP8 *) encode_state->q_matrix->buffer;
  VAEncSequenceParameterBufferVP8 *seq_params =
    (VAEncSequenceParameterBufferVP8 *) encode_state->seq_param_ext->buffer;
  VAEncPictureParameterBufferVP8 *pic_params =
    (VAEncPictureParameterBufferVP8 *) encode_state->pic_param_ext->buffer;
  UINT segmentation_enabled = pic_params->pic_flags.bits.segmentation_enabled;
  MEDIA_CURBE_DATA_MBENC_I_G75 *cmd =
    (MEDIA_CURBE_DATA_MBENC_I_G75 *) params->curbe_cmd_buff;
  UINT16 y_quanta_dc_idx, uv_quanta_dc_idx, uv_quanta_ac_idx;

  media_drv_memset (cmd, sizeof (*cmd));

  cmd->dw0.frame_width = (seq_params->frame_width + 15) & (~0xF);	/* kernel require MB boundary aligned dimensions */
  cmd->dw0.frame_height = (seq_params->frame_height + 15) & (~0xF);
  cmd->dw1.frame_type = 0;	/*key frame(I-frame) */
  cmd->dw1.enable_segmentation = segmentation_enabled;
  cmd->dw1.enable_hw_intra_prediction =
    (params->kernel_mode == PERFORMANCE_MODE) ? 1 : 0;
  cmd->dw1.enable_debug_dumps = 0;
  cmd->dw1.enable_chroma_ip_enhancement = 1;	/* always enabled and cannot be disabled */
  cmd->dw1.enable_mpu_histogram_update = 1;
  cmd->dw1.vme_enable_tm_check = 0;
  cmd->dw1.vme_distortion_measure = 2;	//defualt value is 2-HAAR transform
  cmd->dw1.reserved_mbz = 1;	//do we need to set this reserved bit to 1?

  y_quanta_dc_idx =
    quant_params->quantization_index[0] +
    quant_params->quantization_index_delta[0];
  y_quanta_dc_idx =
    y_quanta_dc_idx < 0 ? 0 : (y_quanta_dc_idx >
			       MAX_QP_VP8_G75 ? MAX_QP_VP8_G75 :
			       y_quanta_dc_idx);
  cmd->dw2.lambda_seg_0 =
    (UINT16) ((quant_dc_vp8_g75[y_quanta_dc_idx] *
	      quant_dc_vp8_g75[y_quanta_dc_idx]) / 4);

  if (segmentation_enabled)
    {
      y_quanta_dc_idx =
	quant_params->quantization_index[1] +
	quant_params->quantization_index_delta[0];
      y_quanta_dc_idx =
	y_quanta_dc_idx < 0 ? 0 : (y_quanta_dc_idx >
				   MAX_QP_VP8_G75 ? MAX_QP_VP8_G75 :
				   y_quanta_dc_idx);
      cmd->dw2.lambda_seg_1 =
	(UINT16) ((quant_dc_vp8_g75[y_quanta_dc_idx] *
		  quant_dc_vp8_g75[y_quanta_dc_idx]) / 4);

      y_quanta_dc_idx =
	quant_params->quantization_index[2] +
	quant_params->quantization_index_delta[0];
      y_quanta_dc_idx =
	y_quanta_dc_idx < 0 ? 0 : (y_quanta_dc_idx >
				   MAX_QP_VP8_G75 ? MAX_QP_VP8_G75 :
				   y_quanta_dc_idx);
      cmd->dw3.lambda_seg_2 =
	(UINT16) ((quant_dc_vp8_g75[y_quanta_dc_idx] *
		  quant_dc_vp8_g75[y_quanta_dc_idx]) / 4);

      y_quanta_dc_idx =
	quant_params->quantization_index[3] +
	quant_params->quantization_index_delta[0];
      y_quanta_dc_idx =
	y_quanta_dc_idx < 0 ? 0 : (y_quanta_dc_idx >
				   MAX_QP_VP8_G75 ? MAX_QP_VP8_G75 :
				   y_quanta_dc_idx);
      cmd->dw3.lambda_seg_3 =
	(UINT16) ((quant_dc_vp8_g75[y_quanta_dc_idx] *
		  quant_dc_vp8_g75[y_quanta_dc_idx]) / 4);
    }

  cmd->dw4.all_dc_bias_segment_0 = DC_BIAS_SEGMENT_DEFAULT_VAL_VP8;
  if (segmentation_enabled)
    {
      cmd->dw4.all_dc_bias_segment_1 = DC_BIAS_SEGMENT_DEFAULT_VAL_VP8;
      cmd->dw5.all_dc_bias_segment_2 = DC_BIAS_SEGMENT_DEFAULT_VAL_VP8;
      cmd->dw5.all_dc_bias_segment_3 = DC_BIAS_SEGMENT_DEFAULT_VAL_VP8;
    }

  uv_quanta_dc_idx =
    quant_params->quantization_index[0] +
    quant_params->quantization_index_delta[1];
  uv_quanta_dc_idx =
    uv_quanta_dc_idx < 0 ? 0 : (uv_quanta_dc_idx >
				MAX_QP_VP8_G75 ? MAX_QP_VP8_G75 :
				uv_quanta_dc_idx);
  cmd->dw6.chroma_dc_de_quant_segment_0 = quant_dc_vp8_g75[uv_quanta_dc_idx];
  if (segmentation_enabled)
    {
      uv_quanta_dc_idx =
	quant_params->quantization_index[1] +
	quant_params->quantization_index_delta[1];
      uv_quanta_dc_idx =
	uv_quanta_dc_idx < 0 ? 0 : (uv_quanta_dc_idx >
				    MAX_QP_VP8_G75 ? MAX_QP_VP8_G75 :
				    uv_quanta_dc_idx);
      cmd->dw6.chroma_dc_de_quant_segment_1 =
	quant_dc_vp8_g75[uv_quanta_dc_idx];
      uv_quanta_dc_idx =
	quant_params->quantization_index[2] +
	quant_params->quantization_index_delta[1];
      uv_quanta_dc_idx =
	uv_quanta_dc_idx < 0 ? 0 : (uv_quanta_dc_idx >
				    MAX_QP_VP8_G75 ? MAX_QP_VP8_G75 :
				    uv_quanta_dc_idx);
      cmd->dw7.chroma_dc_de_quant_segment_2 =
	quant_dc_vp8_g75[uv_quanta_dc_idx];
      uv_quanta_dc_idx =
	quant_params->quantization_index[3] +
	quant_params->quantization_index_delta[1];
      uv_quanta_dc_idx =
	uv_quanta_dc_idx < 0 ? 0 : (uv_quanta_dc_idx >
				    MAX_QP_VP8_G75 ? MAX_QP_VP8_G75 :
				    uv_quanta_dc_idx);
      cmd->dw7.chroma_dc_de_quant_segment_3 =
	quant_dc_vp8_g75[uv_quanta_dc_idx];
    }

  uv_quanta_ac_idx =
    quant_params->quantization_index[0] +
    quant_params->quantization_index_delta[2];
  uv_quanta_ac_idx =
    uv_quanta_ac_idx < 0 ? 0 : (uv_quanta_ac_idx >
				MAX_QP_VP8_G75 ? MAX_QP_VP8_G75 :
				uv_quanta_ac_idx);
  cmd->dw8.chroma_ac_de_quant_segment0 = quant_ac_vp8_g75[uv_quanta_ac_idx];
  cmd->dw10.chroma_ac0_threshold0_segment0 =
    (UINT16) ((((((1) << 16) -
		1) * 1.0 / ((1 << 16) / quant_ac_vp8_g75[uv_quanta_ac_idx]) -
	       ((48 * quant_ac_vp8_g75[uv_quanta_ac_idx]) >> 7)) * (1 << 13) +
	      3400) / 2217.0);
  cmd->dw10.chroma_ac0_threshold1_segment0 =
    (UINT16) ((((((2) << 16) -
		1) * 1.0 / ((1 << 16) / quant_ac_vp8_g75[uv_quanta_ac_idx]) -
	       ((48 * quant_ac_vp8_g75[uv_quanta_ac_idx]) >> 7)) * (1 << 13) +
	      3400) / 2217.0);
  if (segmentation_enabled)
    {
      uv_quanta_ac_idx =
	quant_params->quantization_index[1] +
	quant_params->quantization_index_delta[2];
      uv_quanta_ac_idx =
	uv_quanta_ac_idx < 0 ? 0 : (uv_quanta_ac_idx >
				    MAX_QP_VP8_G75 ? MAX_QP_VP8_G75 :
				    uv_quanta_ac_idx);
      cmd->dw8.chroma_ac_de_quant_segment1 =
	quant_ac_vp8_g75[uv_quanta_ac_idx];
      cmd->dw10.chroma_ac0_threshold0_segment0 =
	(UINT16) ((((((1) << 16) -
		    1) * 1.0 / ((1 << 16) /
				quant_ac_vp8_g75[uv_quanta_ac_idx]) -
		   ((48 * quant_ac_vp8_g75[uv_quanta_ac_idx]) >> 7)) *
		  (1 << 13) + 3400) / 2217.0);
      cmd->dw10.chroma_ac0_threshold1_segment0 =
	(UINT16) ((((((2) << 16) -
		    1) * 1.0 / ((1 << 16) /
				quant_ac_vp8_g75[uv_quanta_ac_idx]) -
		   ((48 * quant_ac_vp8_g75[uv_quanta_ac_idx]) >> 7)) *
		  (1 << 13) + 3400) / 2217.0);

      uv_quanta_ac_idx =
	quant_params->quantization_index[2] +
	quant_params->quantization_index_delta[2];
      uv_quanta_ac_idx =
	uv_quanta_ac_idx < 0 ? 0 : (uv_quanta_ac_idx >
				    MAX_QP_VP8_G75 ? MAX_QP_VP8_G75 :
				    uv_quanta_ac_idx);
      cmd->dw9.chroma_ac_de_quant_segment2 =
	quant_ac_vp8_g75[uv_quanta_ac_idx];
      cmd->dw12.chroma_ac0_threshold0_segment2 =
	(UINT16) ((((((1) << 16) -
		    1) * 1.0 / ((1 << 16) /
				quant_ac_vp8_g75[uv_quanta_ac_idx]) -
		   ((48 * quant_ac_vp8_g75[uv_quanta_ac_idx]) >> 7)) *
		  (1 << 13) + 3400) / 2217.0);
      cmd->dw12.chroma_ac0_threshold1_segment2 =
	(UINT16) ((((((2) << 16) -
		    1) * 1.0 / ((1 << 16) /
				quant_ac_vp8_g75[uv_quanta_ac_idx]) -
		   ((48 * quant_ac_vp8_g75[uv_quanta_ac_idx]) >> 7)) *
		  (1 << 13) + 3400) / 2217.0);

      uv_quanta_ac_idx =
	quant_params->quantization_index[3] +
	quant_params->quantization_index_delta[2];
      uv_quanta_ac_idx =
	uv_quanta_ac_idx < 0 ? 0 : (uv_quanta_ac_idx >
				    MAX_QP_VP8_G75 ? MAX_QP_VP8_G75 :
				    uv_quanta_ac_idx);
      cmd->dw9.chroma_ac_de_quant_segment3 =
	quant_ac_vp8_g75[uv_quanta_ac_idx];
      cmd->dw13.chroma_ac0_threshold0_segment3 =
	(UINT16) ((((((1) << 16) -
		    1) * 1.0 / ((1 << 16) /
				quant_ac_vp8_g75[uv_quanta_ac_idx]) -
		   ((48 * quant_ac_vp8_g75[uv_quanta_ac_idx]) >> 7)) *
		  (1 << 13) + 3400) / 2217.0);
      cmd->dw13.chroma_ac0_threshold1_segment3 =
	(UINT16) ((((((2) << 16) -
		    1) * 1.0 / ((1 << 16) /
				quant_ac_vp8_g75[uv_quanta_ac_idx]) -
		   ((48 * quant_ac_vp8_g75[uv_quanta_ac_idx]) >> 7)) *
		  (1 << 13) + 3400) / 2217.0);
    }

  uv_quanta_dc_idx =
    quant_params->quantization_index[0] +
    quant_params->quantization_index_delta[1];
  uv_quanta_dc_idx =
    uv_quanta_dc_idx < 0 ? 0 : (uv_quanta_dc_idx >
				MAX_QP_VP8_G75 ? MAX_QP_VP8_G75 :
				uv_quanta_dc_idx);
  cmd->dw14.chroma_dc_threshold0_segment0 =
    (((1) << 16) - 1) / ((1 << 16) / quant_dc_vp8_g75[uv_quanta_dc_idx]) -
    ((48 * quant_dc_vp8_g75[uv_quanta_dc_idx]) >> 7);
  cmd->dw14.chroma_dc_threshold1_segment0 =
    (((2) << 16) - 1) / ((1 << 16) / quant_dc_vp8_g75[uv_quanta_dc_idx]) -
    ((48 * quant_dc_vp8_g75[uv_quanta_dc_idx]) >> 7);
  cmd->dw15.chroma_dc_threshold2_segment0 =
    (((3) << 16) - 1) / ((1 << 16) / quant_dc_vp8_g75[uv_quanta_dc_idx]) -
    ((48 * quant_dc_vp8_g75[uv_quanta_dc_idx]) >> 7);
  cmd->dw15.chroma_dc_threshold3_segment0 =
    (((4) << 16) - 1) / ((1 << 16) / quant_dc_vp8_g75[uv_quanta_dc_idx]) -
    ((48 * quant_dc_vp8_g75[uv_quanta_dc_idx]) >> 7);
  if (segmentation_enabled)
    {
      uv_quanta_dc_idx =
	quant_params->quantization_index[1] +
	quant_params->quantization_index_delta[1];
      uv_quanta_dc_idx =
	uv_quanta_dc_idx < 0 ? 0 : (uv_quanta_dc_idx >
				    MAX_QP_VP8_G75 ? MAX_QP_VP8_G75 :
				    uv_quanta_dc_idx);
      cmd->dw16.chroma_dc_threshold0_segment1 =
	(((1) << 16) - 1) / ((1 << 16) / quant_dc_vp8_g75[uv_quanta_dc_idx]) -
	((48 * quant_dc_vp8_g75[uv_quanta_dc_idx]) >> 7);
      cmd->dw16.chroma_dc_threshold1_segment1 =
	(((2) << 16) - 1) / ((1 << 16) / quant_dc_vp8_g75[uv_quanta_dc_idx]) -
	((48 * quant_dc_vp8_g75[uv_quanta_dc_idx]) >> 7);
      cmd->dw17.chroma_dc_threshold2_segment1 =
	(((3) << 16) - 1) / ((1 << 16) / quant_dc_vp8_g75[uv_quanta_dc_idx]) -
	((48 * quant_dc_vp8_g75[uv_quanta_dc_idx]) >> 7);
      cmd->dw17.chroma_dc_threshold3_segment1 =
	(((4) << 16) - 1) / ((1 << 16) / quant_dc_vp8_g75[uv_quanta_dc_idx]) -
	((48 * quant_dc_vp8_g75[uv_quanta_dc_idx]) >> 7);

      uv_quanta_dc_idx =
	quant_params->quantization_index[2] +
	quant_params->quantization_index_delta[1];
      uv_quanta_dc_idx =
	uv_quanta_dc_idx < 0 ? 0 : (uv_quanta_dc_idx >
				    MAX_QP_VP8_G75 ? MAX_QP_VP8_G75 :
				    uv_quanta_dc_idx);
      cmd->dw18.chroma_dc_threshold0_segment2 =
	(((1) << 16) - 1) / ((1 << 16) / quant_dc_vp8_g75[uv_quanta_dc_idx]) -
	((48 * quant_dc_vp8_g75[uv_quanta_dc_idx]) >> 7);
      cmd->dw18.chroma_dc_threshold1_segment2 =
	(((2) << 16) - 1) / ((1 << 16) / quant_dc_vp8_g75[uv_quanta_dc_idx]) -
	((48 * quant_dc_vp8_g75[uv_quanta_dc_idx]) >> 7);
      cmd->dw19.chroma_dc_threshold2_segment2 =
	(((3) << 16) - 1) / ((1 << 16) / quant_dc_vp8_g75[uv_quanta_dc_idx]) -
	((48 * quant_dc_vp8_g75[uv_quanta_dc_idx]) >> 7);
      cmd->dw19.chroma_dc_threshold3_segment2 =
	(((4) << 16) - 1) / ((1 << 16) / quant_dc_vp8_g75[uv_quanta_dc_idx]) -
	((48 * quant_dc_vp8_g75[uv_quanta_dc_idx]) >> 7);

      uv_quanta_dc_idx =
	quant_params->quantization_index[3] +
	quant_params->quantization_index_delta[1];
      uv_quanta_dc_idx =
	uv_quanta_dc_idx < 0 ? 0 : (uv_quanta_dc_idx >
				    MAX_QP_VP8_G75 ? MAX_QP_VP8_G75 :
				    uv_quanta_dc_idx);
      cmd->dw20.chroma_dc_threshold0_segment3 =
	(((1) << 16) - 1) / ((1 << 16) / quant_dc_vp8_g75[uv_quanta_dc_idx]) -
	((48 * quant_dc_vp8_g75[uv_quanta_dc_idx]) >> 7);
      cmd->dw20.chroma_dc_threshold1_segment3 =
	(((2) << 16) - 1) / ((1 << 16) / quant_dc_vp8_g75[uv_quanta_dc_idx]) -
	((48 * quant_dc_vp8_g75[uv_quanta_dc_idx]) >> 7);
      cmd->dw21.chroma_dc_threshold2_segment3 =
	(((3) << 16) - 1) / ((1 << 16) / quant_dc_vp8_g75[uv_quanta_dc_idx]) -
	((48 * quant_dc_vp8_g75[uv_quanta_dc_idx]) >> 7);
      cmd->dw21.chroma_dc_threshold3_segment3 =
	(((4) << 16) - 1) / ((1 << 16) / quant_dc_vp8_g75[uv_quanta_dc_idx]) -
	((48 * quant_dc_vp8_g75[uv_quanta_dc_idx]) >> 7);
    }

  uv_quanta_ac_idx =
    quant_params->quantization_index[0] +
    quant_params->quantization_index_delta[2];
  uv_quanta_ac_idx =
    uv_quanta_ac_idx < 0 ? 0 : (uv_quanta_ac_idx >
				MAX_QP_VP8_G75 ? MAX_QP_VP8_G75 :
				uv_quanta_ac_idx);
  cmd->dw22.chroma_ac1_threshold_segment0 =
    ((1 << (16)) - 1) / ((1 << 16) / quant_ac_vp8_g75[uv_quanta_ac_idx]) -
    ((48 * quant_ac_vp8_g75[uv_quanta_ac_idx]) >> 7);
  if (segmentation_enabled)
    {
      uv_quanta_ac_idx =
	quant_params->quantization_index[1] +
	quant_params->quantization_index_delta[2];
      uv_quanta_ac_idx =
	uv_quanta_ac_idx < 0 ? 0 : (uv_quanta_ac_idx >
				    MAX_QP_VP8_G75 ? MAX_QP_VP8_G75 :
				    uv_quanta_ac_idx);
      cmd->dw22.chroma_ac1_threshold_segment1 =
	((1 << (16)) - 1) / ((1 << 16) / quant_ac_vp8_g75[uv_quanta_ac_idx]) -
	((48 * quant_ac_vp8_g75[uv_quanta_ac_idx]) >> 7);

      uv_quanta_ac_idx =
	quant_params->quantization_index[2] +
	quant_params->quantization_index_delta[2];
      uv_quanta_ac_idx =
	uv_quanta_ac_idx < 0 ? 0 : (uv_quanta_ac_idx >
				    MAX_QP_VP8_G75 ? MAX_QP_VP8_G75 :
				    uv_quanta_ac_idx);
      cmd->dw23.chroma_ac1_threshold_segment2 =
	((1 << (16)) - 1) / ((1 << 16) / quant_ac_vp8_g75[uv_quanta_ac_idx]) -
	((48 * quant_ac_vp8_g75[uv_quanta_ac_idx]) >> 7);
      uv_quanta_ac_idx =
	quant_params->quantization_index[3] +
	quant_params->quantization_index_delta[2];
      uv_quanta_ac_idx =
	uv_quanta_ac_idx < 0 ? 0 : (uv_quanta_ac_idx >
				    MAX_QP_VP8_G75 ? MAX_QP_VP8_G75 :
				    uv_quanta_ac_idx);
      cmd->dw23.chroma_ac1_threshold_segment3 =
	((1 << (16)) - 1) / ((1 << 16) / quant_ac_vp8_g75[uv_quanta_ac_idx]) -
	((48 * quant_ac_vp8_g75[uv_quanta_ac_idx]) >> 7);
    }

  uv_quanta_dc_idx =
    quant_params->quantization_index[0] +
    quant_params->quantization_index_delta[0];
  uv_quanta_dc_idx =
    uv_quanta_dc_idx < 0 ? 0 : (uv_quanta_dc_idx >
				MAX_QP_VP8_G75 ? MAX_QP_VP8_G75 :
				uv_quanta_dc_idx);
  cmd->dw24.vme_16x16_cost_segment0 =
    frame_i_vme_cost_vp8_g75[uv_quanta_dc_idx & 0x7F][0];
  cmd->dw25.vme_4x4_cost_segment0 =
    frame_i_vme_cost_vp8_g75[uv_quanta_dc_idx & 0x7F][1];
  cmd->dw26.vme_16x16_non_dc_penalty_segment0 =
    frame_i_vme_cost_vp8_g75[uv_quanta_dc_idx & 0x7F][2];
  cmd->dw27.vme_4x4_non_dc_penalty_segment0 =
    frame_i_vme_cost_vp8_g75[uv_quanta_dc_idx & 0x7F][3];
  if (segmentation_enabled)
    {
      uv_quanta_dc_idx =
	quant_params->quantization_index[1] +
	quant_params->quantization_index_delta[0];
      uv_quanta_dc_idx =
	uv_quanta_dc_idx < 0 ? 0 : (uv_quanta_dc_idx >
				    MAX_QP_VP8_G75 ? MAX_QP_VP8_G75 :
				    uv_quanta_dc_idx);
      cmd->dw24.vme_16x16_cost_segment1 =
	frame_i_vme_cost_vp8_g75[uv_quanta_dc_idx & 0x7F][0];
      cmd->dw25.vme_4x4_cost_segment1 =
	frame_i_vme_cost_vp8_g75[uv_quanta_dc_idx & 0x7F][1];
      cmd->dw26.vme_16x16_non_dc_penalty_segment1 =
	frame_i_vme_cost_vp8_g75[uv_quanta_dc_idx & 0x7F][2];
      cmd->dw27.vme_4x4_non_dc_penalty_segment1 =
	frame_i_vme_cost_vp8_g75[uv_quanta_dc_idx & 0x7F][3];

      uv_quanta_dc_idx =
	quant_params->quantization_index[2] +
	quant_params->quantization_index_delta[0];
      uv_quanta_dc_idx =
	uv_quanta_dc_idx < 0 ? 0 : (uv_quanta_dc_idx >
				    MAX_QP_VP8_G75 ? MAX_QP_VP8_G75 :
				    uv_quanta_dc_idx);
      cmd->dw24.vme_16x16_cost_segment2 =
	frame_i_vme_cost_vp8_g75[uv_quanta_dc_idx & 0x7F][0];
      cmd->dw25.vme_4x4_cost_segment2 =
	frame_i_vme_cost_vp8_g75[uv_quanta_dc_idx & 0x7F][1];
      cmd->dw26.vme_16x16_non_dc_penalty_segment2 =
	frame_i_vme_cost_vp8_g75[uv_quanta_dc_idx & 0x7F][2];
      cmd->dw27.vme_4x4_non_dc_penalty_segment2 =
	frame_i_vme_cost_vp8_g75[uv_quanta_dc_idx & 0x7F][3];

      uv_quanta_dc_idx =
	quant_params->quantization_index[3] +
	quant_params->quantization_index_delta[0];
      uv_quanta_dc_idx =
	uv_quanta_dc_idx < 0 ? 0 : (uv_quanta_dc_idx >
				    MAX_QP_VP8_G75 ? MAX_QP_VP8_G75 :
				    uv_quanta_dc_idx);
      cmd->dw24.vme_16x16_cost_segment3 =
	frame_i_vme_cost_vp8_g75[uv_quanta_dc_idx & 0x7F][0];
      cmd->dw25.vme_4x4_cost_segment3 =
	frame_i_vme_cost_vp8_g75[uv_quanta_dc_idx & 0x7F][1];
      cmd->dw26.vme_16x16_non_dc_penalty_segment3 =
	frame_i_vme_cost_vp8_g75[uv_quanta_dc_idx & 0x7F][2];
      cmd->dw27.vme_4x4_non_dc_penalty_segment3 =
	frame_i_vme_cost_vp8_g75[uv_quanta_dc_idx & 0x7F][3];
    }
  //pic_params->segmentation_enabled = 0;

  cmd->dw32.mb_enc_per_mb_out_data_surf_bti = 0;
  cmd->dw33.mb_enc_curr_y_bti = 1;
  cmd->dw34.mb_enc_curr_uv_bti = 1;	//2
  cmd->dw35.mb_mode_cost_luma_bti = 3;
  cmd->dw36.mb_enc_block_mode_cost_bti = 4;
  cmd->dw37.chroma_recon_surf_bti = 5;
  cmd->dw38.segmentation_map_bti = 6;
  cmd->dw39.histogram_bti = 7;
  cmd->dw40.mb_enc_vme_debug_stream_out_bti = 8;
  cmd->dw41.vme_bti = 9;

  if (params->mb_enc_iframe_dist_in_use)
    {
      cmd->dw42.idist_surface = 10;
      cmd->dw43.curr_y_surface4x_downscaled = 11;
      cmd->dw44.vme_coarse_intra_surface = 12;
    }
}

VOID
media_set_curbe_p_vp8_mbenc (struct encode_state *encode_state,
			     MEDIA_MBENC_CURBE_PARAMS_VP8 * params)
{
  VAQMatrixBufferVP8 *quant_params =
    (VAQMatrixBufferVP8 *) encode_state->q_matrix->buffer;
  VAEncSequenceParameterBufferVP8 *seq_params =
    (VAEncSequenceParameterBufferVP8 *) encode_state->seq_param_ext->buffer;
  VAEncPictureParameterBufferVP8 *pic_params =
    (VAEncPictureParameterBufferVP8 *) encode_state->pic_param_ext->buffer;
  UINT segmentation_enabled = pic_params->pic_flags.bits.segmentation_enabled;
  UINT version = pic_params->pic_flags.bits.version;
  MEDIA_CURBE_DATA_MBENC_P_G75 *cmd =
    (MEDIA_CURBE_DATA_MBENC_P_G75 *) params->curbe_cmd_buff;;
  UINT16 luma_dc_seg0, luma_dc_seg1, luma_dc_seg2, luma_dc_seg3;
  UINT16 qp_seg0, qp_seg1, qp_seg2, qp_seg3;

  if (params->updated == TRUE)
    {
      cmd->dw81.per_mb_output_data_surface_bti = 0;
      cmd->dw82.current_picture_y_surface_bti = 1;
      cmd->dw83.current_picture_interleaved_uv_surface_bti = 1;
      cmd->dw84.hme_mv_data_surface_bti = 3;
      cmd->dw85.mv_data_surface_bti = 4;
      cmd->dw86.mb_count_per_reference_frame_bti = 5;
      cmd->dw87.vme_inter_prediction_bti = 8;
      cmd->dw88.last_picture_bti = 9;
      cmd->dw89.gold_picture_bti = 11;
      cmd->dw90.alternate_picture_bti = 13;
      cmd->dw91.per_mb_quant_data_bti = 15;
      cmd->dw92.segment_map_bti = 16;
      cmd->dw93.inter_prediction_distortion_bti = 17;
      cmd->dw94.histogram_bti = 18;
      cmd->dw95.pred_mv_data_bti = 19;
      cmd->dw96.mode_cost_update_bti = 20;
      cmd->dw97.kernel_debug_dump_bti = 21;

      return;
    }

  media_drv_memset (cmd, sizeof (MEDIA_CURBE_DATA_MBENC_P_G75));

  luma_dc_seg0 =
    quant_params->quantization_index[0] +
    quant_params->quantization_index_delta[0];
  luma_dc_seg1 =
    quant_params->quantization_index[1] +
    quant_params->quantization_index_delta[0];
  luma_dc_seg2 =
    quant_params->quantization_index[2] +
    quant_params->quantization_index_delta[0];
  luma_dc_seg3 =
    quant_params->quantization_index[3] +
    quant_params->quantization_index_delta[0];

  qp_seg0 =
    luma_dc_seg0 < 0 ? 0 : (luma_dc_seg0 >
			    MAX_QP_VP8_G75 ? MAX_QP_VP8_G75 : luma_dc_seg0);
  qp_seg1 =
    luma_dc_seg1 < 0 ? 0 : (luma_dc_seg1 >
			    MAX_QP_VP8_G75 ? MAX_QP_VP8_G75 : luma_dc_seg1);
  qp_seg2 =
    luma_dc_seg2 < 0 ? 0 : (luma_dc_seg2 >
			    MAX_QP_VP8_G75 ? MAX_QP_VP8_G75 : luma_dc_seg2);
  qp_seg3 =
    luma_dc_seg3 < 0 ? 0 : (luma_dc_seg3 >
			    MAX_QP_VP8_G75 ? MAX_QP_VP8_G75 : luma_dc_seg3);

  BYTE me_method = (params->kernel_mode == NORMAL_MODE) ? 6 : 4;

  //dw0
  cmd->dw0.frame_width = (seq_params->frame_width + 15) & (~0xF);
  cmd->dw0.frame_height = (seq_params->frame_height + 15) & (~0xF);
  // dw1
  cmd->dw1.frame_type = 1;	// P-frame
  cmd->dw1.motion_compensation_filter_type =
    (version == 0) ? 0 /*6-tap filter */ :
    ((version == 3) ? 2 : 1);

  cmd->dw1.hme_enable = params->hme_enabled;
  cmd->dw1.hme_combine_overlap = (params->kernel_mode == NORMAL_MODE) ? 1 : 2;
  cmd->dw1.multiple_pred_enable = 0;
  cmd->dw1.ref_ctrl = params->ref_frame_ctrl;
  cmd->dw1.enable_segmentation = segmentation_enabled;
  cmd->dw1.enable_segmentation_info_update = 0;
  cmd->dw1.multi_reference_qp_check = 1;
  cmd->dw1.mode_cost_enable_flag = 0;
  cmd->dw1.hme_coarse_shape = 0;
  cmd->dw1.all_fractional = 1;
  //dw2
  cmd->dw2.lambda_intra_segment0 = quant_dc_vp8_g75[qp_seg0];
  cmd->dw2.lambda_inter_segment0 = (quant_dc_vp8_g75[qp_seg0] >> 2);

  if (segmentation_enabled)
    {
      //dw3
      cmd->dw3.lambda_intra_segment1 = (quant_dc_vp8_g75[qp_seg1]);
      cmd->dw3.lambda_inter_segment1 = (quant_dc_vp8_g75[qp_seg1] >> 2);
      //dw4
      cmd->dw4.lambda_intra_segment2 = (quant_dc_vp8_g75[qp_seg2]);
      cmd->dw4.lambda_inter_segment2 = (quant_dc_vp8_g75[qp_seg2] >> 2);
      //dw5
      cmd->dw5.lambda_intra_segment3 = (quant_dc_vp8_g75[qp_seg3]);
      cmd->dw5.lambda_inter_segment3 = (quant_dc_vp8_g75[qp_seg3] >> 2);
    }

  if (params->brc_enabled == TRUE)
    {
      cmd->dw2.lambda_intra_segment0 = cmd->dw3.lambda_intra_segment1 =
	cmd->dw4.lambda_intra_segment2 = cmd->dw5.lambda_intra_segment3 = 0;
    }

  //dw6
  cmd->dw6.reference_frame_sign_bias_3 =
    pic_params->pic_flags.bits.sign_bias_golden;
  cmd->dw6.reference_frame_sign_bias_2 =
    pic_params->pic_flags.bits.sign_bias_alternate;
  cmd->dw6.reference_frame_sign_bias_1 =
    pic_params->pic_flags.bits.sign_bias_golden ^ pic_params->pic_flags.bits.
    sign_bias_alternate;
  cmd->dw6.reference_frame_sign_bias_0 = 0;
  //dw7
  cmd->dw7.raw_dist_threshold = 0;	//kernel is currently setting it to 0
  //dw8
  cmd->dw8.early_ime_successful_stop_threshold = 0;
  cmd->dw8.adaptive_search_enable =
    (params->kernel_mode != PERFORMANCE_MODE) ? 1 : 0;
  cmd->dw8.skip_mode_enable = 1;
  cmd->dw8.bidirectional_mix_disbale = 0;
  cmd->dw8.transform8x8_flag_for_inter_enable = 0;
  cmd->dw8.early_ime_success_enable = 0;
  //dw9
  cmd->dw9.ref_pixel_bias_enable = 0;
  cmd->dw9.unidirection_mix_enable = 0;
  cmd->dw9.bidirectional_weight = 0;
  cmd->dw9.ref_id_polarity_bits = 0;
  cmd->dw9.max_num_of_motion_vectors = 0 /* 32 */ ;	// from Bdw
  //dw10
  cmd->dw10.max_fixed_search_path_length =
    (params->kernel_mode ==
     NORMAL_MODE) ? 16 : ((params->kernel_mode == PERFORMANCE_MODE) ? 9 : 57);
  cmd->dw10.maximum_search_path_length = 57;
  //dw11
  cmd->dw11.submacro_block_subPartition_mask = 0 /* 0x30 */ ;	//from Bdw
  cmd->dw11.intra_sad_measure_adjustment = 2;
  cmd->dw11.inter_sad_measure_adjustment = 2;
  cmd->dw11.block_based_skip_enable = 0;
  cmd->dw11.bme_disable_for_fbr_message = 0 /* 1 */ ;	// from Bdw
  cmd->dw11.forward_trans_form_skip_check_enable = 0;
  cmd->dw11.process_inter_chroma_pixels_mode = 0;
  cmd->dw11.disable_field_cache_allocation = 0;
  cmd->dw11.skip_mode_type = 0;
  cmd->dw11.sub_pel_mode = 3;
  cmd->dw11.dual_search_path_option = 0;
  cmd->dw11.search_control = 0;
  cmd->dw11.reference_access = 0;
  cmd->dw11.source_access = 0;
  cmd->dw11.inter_mb_type_road_map = 0;
  cmd->dw11.source_block_size = 0;
  //dw12
  cmd->dw12.reference_search_windows_height =
    (params->kernel_mode != PERFORMANCE_MODE) ? 40 : 28;
  cmd->dw12.reference_search_windows_width =
    (params->kernel_mode != PERFORMANCE_MODE) ? 48 : 28;
  //dw13
  cmd->dw13.mode_0_3_cost_seg0 = cost_table_vp8_g75[qp_seg0][0];
  cmd->dw14.mode_4_7_cost_seg0 = cost_table_vp8_g75[qp_seg0][1];
  cmd->dw15.val = cost_table_vp8_g75[qp_seg0][2];

  if (params->brc_enabled == TRUE)
    {
      cmd->dw13.mode_0_3_cost_seg0 = cmd->dw14.mode_4_7_cost_seg0 =
	cmd->dw15.val = 0;
    }

  // which table to load is selected by MEMethod parameter determined by the driver based on the usage model (normal/quality/performance)
  switch (me_method)
    {
    case 2:
      media_drv_memcpy (&(cmd->dw16), sizeof (single_su_vp8_g75),
			(VOID *) single_su_vp8_g75,
			sizeof (single_su_vp8_g75));
      break;

    case 3:
      media_drv_memcpy (&(cmd->dw16), sizeof (rasterscan_48x40_vp8_g75),
			(VOID *) rasterscan_48x40_vp8_g75,
			sizeof (rasterscan_48x40_vp8_g75));
      break;

    case 4:
    case 5:
      media_drv_memcpy (&(cmd->dw16), sizeof (fullspiral_48x40_vp8_g75),
			(VOID *) fullspiral_48x40_vp8_g75,
			sizeof (fullspiral_48x40_vp8_g75));
      break;

    case 6:
    default:
      media_drv_memcpy (&(cmd->dw16), sizeof (diamond_vp8_g75),
			(VOID *) diamond_vp8_g75, sizeof (diamond_vp8_g75));
      break;
    }
  //dw30
  cmd->dw30.mv_cost_seg_val = cost_table_vp8_g75[qp_seg0][3];
  //dw31
  cmd->dw31.mv_cost_seg_val = cost_table_vp8_g75[qp_seg0][4];
  //dw32
  cmd->dw32.bilinear_enable = 0;
  cmd->dw32.intra_16x16_no_dc_penalty_segment0 =
    cost_table_vp8_g75[qp_seg0][5];

  if (params->brc_enabled == TRUE)
    {
      cmd->dw30.mv_cost_seg_val = cmd->dw31.mv_cost_seg_val = 0;
      cmd->dw32.intra_16x16_no_dc_penalty_segment0 = 0;
    }

  if (segmentation_enabled)
    {
      cmd->dw32.intra_16x16_no_dc_penalty_segment1 =
	cost_table_vp8_g75[qp_seg1][5];
      cmd->dw33.intra_16x16_no_dc_penalty_segment2 =
	cost_table_vp8_g75[qp_seg2][5];
      cmd->dw33.intra_16x16_no_dc_penalty_segment3 =
	cost_table_vp8_g75[qp_seg3][5];
    }

  cmd->dw33.hme_combine_len = 8;	//based on target usage part of par file param
  //dw34 to dw57
  media_drv_memcpy (&(cmd->dw34), 24 * sizeof (UINT),
		    (VOID *) mv_ref_cost_context_vp8_g75, 24 * sizeof (UINT));
  //dw58
  cmd->dw58.enc_cost_16x16 = 0;
  cmd->dw58.enc_cost_16x8 = 0x73C;
  //dw59
  cmd->dw59.enc_cost_8x8 = 0x365;
  cmd->dw59.enc_cost_4x4 = 0xDC9;
  //dw60
  cmd->dw60.frame_count_probability_ref_frame_cost_0 = 0x0204;
  cmd->dw60.frame_count_probability_ref_frame_cost_1 = 0x006a;
  //dw61
  cmd->dw61.frame_count_probability_ref_frame_cost_2 = 0x0967;
  cmd->dw61.frame_count_probability_ref_frame_cost_3 = 0x0969;
  //dw62
  cmd->dw62.average_qp_of_last_ref_frame = quant_dc_vp8_g75[qp_seg0];	//0x0f; may have to change this later
  cmd->dw62.average_qp_of_gold_ref_frame = quant_dc_vp8_g75[qp_seg0];	//0x0f;
  cmd->dw62.average_qp_of_alt_ref_frame = quant_dc_vp8_g75[qp_seg0];	//0x0f;
  //dw63
  cmd->dw63.intra_4x4_no_dc_penalty_segment0 = cost_table_vp8_g75[qp_seg0][6];

  if (params->brc_enabled == TRUE)
    {
      cmd->dw62.average_qp_of_last_ref_frame = 0x13;
      cmd->dw62.average_qp_of_gold_ref_frame = 0x13;
      cmd->dw62.average_qp_of_alt_ref_frame = 0x13;
      cmd->dw63.intra_4x4_no_dc_penalty_segment0 = 0;
    }

  if (segmentation_enabled)
    {

      cmd->dw63.intra_4x4_no_dc_penalty_segment1 =
	cost_table_vp8_g75[qp_seg1][6];
      cmd->dw63.intra_4x4_no_dc_penalty_segment2 =
	cost_table_vp8_g75[qp_seg2][6];
      cmd->dw63.intra_4x4_no_dc_penalty_segment3 =
	cost_table_vp8_g75[qp_seg3][6];

      //dw64
      cmd->dw64.mode_cost_seg_1_val = cost_table_vp8_g75[qp_seg1][0];
      //dw65
      cmd->dw65.mode_cost_seg_1_val = cost_table_vp8_g75[qp_seg1][1];
      //dw66
      cmd->dw66.mode_cost_seg_1_val = cost_table_vp8_g75[qp_seg1][2];
      //dw67
      cmd->dw67.mv_cost_seg1_val = cost_table_vp8_g75[qp_seg1][3];
      //dw68
      cmd->dw68.mv_cost_seg1_val = cost_table_vp8_g75[qp_seg1][4];
      //dw69
      cmd->dw69.mv_cost_seg2_val = cost_table_vp8_g75[qp_seg2][0];
      //dw70
      cmd->dw70.mv_cost_seg2_val = cost_table_vp8_g75[qp_seg2][1];
      //dw71
      cmd->dw71.mv_cost_seg2_val = cost_table_vp8_g75[qp_seg2][2];
      //dw72
      cmd->dw72.mv_cost_seg2 = cost_table_vp8_g75[qp_seg2][3];
      //dw73
      cmd->dw73.mv_cost_seg2 = cost_table_vp8_g75[qp_seg2][4];
      //dw74
      cmd->dw74.mode_cost_seg3 = cost_table_vp8_g75[qp_seg3][0];
      //dw75
      cmd->dw75.mode_cost_seg3 = cost_table_vp8_g75[qp_seg3][1];
      //dw76
      cmd->dw76.mode_cost_seg3 = cost_table_vp8_g75[qp_seg3][2];
      //dw77
      cmd->dw77.mv_cost_seg3 = cost_table_vp8_g75[qp_seg3][3];
      //dw78
      cmd->dw78.mv_cost_seg3 = cost_table_vp8_g75[qp_seg3][4];
    }

  //dw79
  cmd->dw79.new_mv_skip_threshold_segment0 =
    new_mv_skip_threshold_VP8_g75[qp_seg0];

  if (segmentation_enabled)
    {
      cmd->dw79.new_mv_skip_threshold_segment1 =
	new_mv_skip_threshold_VP8_g75[qp_seg1];
      //dw80
      cmd->dw80.new_mv_skip_threshold_segment2 =
	new_mv_skip_threshold_VP8_g75[qp_seg2];
      cmd->dw80.new_mv_skip_threshold_segment3 =
	new_mv_skip_threshold_VP8_g75[qp_seg3];
    }

  //setup binding table index entries
  cmd->dw81.per_mb_output_data_surface_bti = 0;
  cmd->dw82.current_picture_y_surface_bti = 1;
  cmd->dw83.current_picture_interleaved_uv_surface_bti = 1;
  cmd->dw84.hme_mv_data_surface_bti = 3;
  cmd->dw85.mv_data_surface_bti = 4;
  cmd->dw86.mb_count_per_reference_frame_bti = 5;
  cmd->dw87.vme_inter_prediction_bti = 8;
  cmd->dw88.last_picture_bti = 9;
  cmd->dw89.gold_picture_bti = 11;
  cmd->dw90.alternate_picture_bti = 13;
  cmd->dw91.per_mb_quant_data_bti = 15;
  cmd->dw92.segment_map_bti = 16;
  cmd->dw93.inter_prediction_distortion_bti = 17;
  cmd->dw94.histogram_bti = 18;
  cmd->dw95.pred_mv_data_bti = 19;
  cmd->dw96.mode_cost_update_bti = 20;
  cmd->dw97.kernel_debug_dump_bti = 21;

}

VOID
media_set_curbe_vp8_me (VP8_ME_CURBE_PARAMS * params)
{
  UINT me_mode = 0, scale_factor = 0, me_method = 0;
  MEDIA_CURBE_DATA_ME *cmd = (MEDIA_CURBE_DATA_ME *) params->curbe_cmd_buff;

  media_drv_memcpy (cmd, sizeof (MEDIA_CURBE_DATA_ME), ME_CURBE_INIT_DATA,
		    sizeof (MEDIA_CURBE_DATA_ME));
  me_mode =
    params->me_16x_enabled ? (params->
			      me_16x ? ME16x_BEFORE_ME4x : ME4x_AFTER_ME16x) :
    ME4x_ONLY;
  scale_factor = (me_mode == ME16x_BEFORE_ME4x) ? 16 : 4;
  cmd->dw1.max_num_mvs = 0x10;
  cmd->dw1.bi_weight = 0;
  cmd->dw2.max_num_su = 57;
  cmd->dw2.max_len_sp =
    (params->kernel_mode ==
     NORMAL_MODE) ? 25 : ((params->kernel_mode == PERFORMANCE_MODE) ? 9 : 57);
  cmd->dw3.sub_mb_part_mask = 0x3F /* 0x30 */ ;	// changed from default to match the kernel team's curbe data
  cmd->dw3.inter_sad = 0;
  cmd->dw3.intra_sad = 0;
  cmd->dw3.bme_disable_fbr = 1;
  cmd->dw3.sub_pel_mode = 3;

  cmd->dw4.picture_height_minus1 =
    HEIGHT_IN_MACROBLOCKS (params->frame_field_height / scale_factor) - 1;
  cmd->dw4.picture_width =
    HEIGHT_IN_MACROBLOCKS (params->frame_width / scale_factor);
  cmd->dw5.ref_height = (params->kernel_mode != PERFORMANCE_MODE) ? 40 : 28;
  cmd->dw5.ref_width = (params->kernel_mode != PERFORMANCE_MODE) ? 48 : 28;

  cmd->dw6.me_modes = me_mode;
  cmd->dw6.super_combine_dist =
    (params->kernel_mode ==
     NORMAL_MODE) ? 5 : ((params->kernel_mode == PERFORMANCE_MODE) ? 0 : 1);
  cmd->dw6.max_vmv_range = 0x7fc;

  cmd->dw13.num_ref_idx_l0_minus_one = 0;
  cmd->dw13.num_ref_idx_l1_minus_one = 0;
  me_method = (params->kernel_mode == NORMAL_MODE) ? 6 : 4;
  media_drv_memcpy (&(cmd->dw16), 14 * sizeof (UINT),
		    SEARCH_PATH_TABLE[0][me_method], 14 * sizeof (UINT));

  cmd->dw32.mv_data_surf = VP8_ME_MV_DATA_SURFACE_G75;
  cmd->dw33.mv_data_inp_surf = VP8_16xME_MV_DATA_SURFACE_G75;
  cmd->dw34.dist_surf = VP8_ME_DISTORTION_SURFACE_G75;
  cmd->dw35.min_dist_brc_surf = VP8_ME_BRC_DISTORTION_SURFACE_G75;
  cmd->dw36.mb_enc_vme_interpred = VP8_ME_INTER_PRED_G75;

}

VOID
media_add_binding_table (MEDIA_GPE_CTX * gpe_ctx)
{
  BYTE *binding_surface_state_buf = NULL;
  UINT i;
  binding_surface_state_buf =
    (BYTE *) media_map_buffer_obj (gpe_ctx->surface_state_binding_table.res.
				   bo);
  media_drv_memset (binding_surface_state_buf,
		    gpe_ctx->surface_state_binding_table.res.bo->size);

  for (i = 0; i < LAST_BINDING_TABLE_ENTRIES; i++)
    {
      *((UINT *) ((BYTE *) binding_surface_state_buf +
			  BINDING_TABLE_OFFSET (i))) =
	SURFACE_STATE_OFFSET (i); /*<< BINDING_TABLE_SURFACE_SHIFT */ ;

    }
  media_unmap_buffer_obj (gpe_ctx->surface_state_binding_table.res.bo);

}

static VOID
media_gpe_set_surface_tiling_g7 (SURFACE_STATE_G7 * cmd,UINT tiling)
{
  switch (tiling)
    {
    case I915_TILING_NONE:
      cmd->dw0.tiled_surface = 0;
      cmd->dw0.tile_walk = 0;
      break;
    case I915_TILING_X:
      cmd->dw0.tiled_surface = 1;
      cmd->dw0.tile_walk = MEDIA_TILEWALK_XMAJOR;
      break;
    case I915_TILING_Y:
      cmd->dw0.tiled_surface = 1;
      cmd->dw0.tile_walk = MEDIA_TILEWALK_YMAJOR;
      break;
    }
}

static VOID
media_gpe_set_surface_tiling_adv_g7 (SURFACE_STATE_ADV_G7 * cmd,
				     UINT tiling)
{
  switch (tiling)
    {
    case I915_TILING_NONE:
      cmd->ss2.tiled_surface = 0;
      cmd->ss2.tile_walk = 0;
      break;
    case I915_TILING_X:
      cmd->ss2.tiled_surface = 1;
      cmd->ss2.tile_walk = MEDIA_TILEWALK_XMAJOR;
      break;
    case I915_TILING_Y:
      cmd->ss2.tiled_surface = 1;
      cmd->ss2.tile_walk = MEDIA_TILEWALK_YMAJOR;
      break;
    }
}

VOID
media_set_surface_state_adv (SURFACE_STATE_ADV_G7 * cmd,
			   SURFACE_SET_PARAMS * params, INT format)
{
  cmd->ss0.surface_base_address = params->surface_2d->bo->offset;
  cmd->ss1.cbcr_pixel_offset_v_direction = params->uv_direction;
  cmd->ss1.width = params->surface_2d->width - 1;
  cmd->ss1.height = params->surface_2d->height - 1;
  cmd->ss2.surface_format = format;
  cmd->ss2.interleave_chroma = 1;
  media_gpe_set_surface_tiling_adv_g7 (cmd, params->surface_2d->tiling);
  cmd->ss2.pitch = params->surface_2d->pitch - 1;
  cmd->ss2.surface_object_control_data = params->cacheability_control;
  cmd->ss3.y_offset_for_cb = params->surface_2d->y_cb_offset;	//(params->surface_2d->width * params->surface_2d->height);
}

VOID
media_set_surface_state_buffer_surface (SURFACE_STATE_G7 * cmd,
					SURFACE_SET_PARAMS * params,
					INT format, INT pitch)
{

  // cmd->dw0.vert_line_stride_offset          = params->vert_line_stride_offset;
  //cmd->dw0.vert_line_stride    = params->vert_line_stride;
  cmd->dw0.surface_format = format;
  cmd->dw0.surface_type = MEDIA_SURFACE_BUFFER;
  cmd->dw0.tiled_surface = 0;
  cmd->dw0.surface_array_spacing = 0x1;
  cmd->dw1.base_addr = params->buf_object.bo->offset + params->offset;
  cmd->dw2.width = (params->size - 1) & 0x7F;
  cmd->dw2.height = ((params->size - 1) & 0x1FFF80) >> 7;
  cmd->dw3.depth = ((params->size - 1) & 0xFE00000) >> 21;
  cmd->dw3.surface_pitch = pitch;
  //cmd->dw5.y_offset                     = offset;
  cmd->dw5.obj_ctrl_state = params->cacheability_control;
  cmd->dw7.shader_chanel_select_a = HSW_SCS_ALPHA;
  cmd->dw7.shader_chanel_select_b = HSW_SCS_BLUE;
  cmd->dw7.shader_chanel_select_g = HSW_SCS_GREEN;
  cmd->dw7.shader_chanel_select_r = HSW_SCS_RED;
}

VOID
media_set_surface_state_2d_surface (SURFACE_STATE_G7 * cmd,
				    SURFACE_SET_PARAMS * params, INT format,
				    UINT width,UINT height,
				    UINT offset,
				    UINT cbcr_offset,
				    UINT y_offset)
{
  cmd->dw0.vert_line_stride_offset = params->vert_line_stride_offset;
  cmd->dw0.vert_line_stride = params->vert_line_stride;
  cmd->dw0.surface_format = format;
  cmd->dw0.surface_type = MEDIA_SURFACE_2D;
  media_gpe_set_surface_tiling_g7 (cmd, params->surface_2d->tiling);

  cmd->dw0.surface_array_spacing = params->surface_2d->surface_array_spacing;
  cmd->dw1.base_addr = params->surface_2d->bo->offset + cbcr_offset;
  cmd->dw2.width = width - 1;
  cmd->dw2.height = height - 1;
  cmd->dw3.surface_pitch = params->surface_2d->pitch - 1;
  cmd->dw5.y_offset = y_offset;
  cmd->dw5.obj_ctrl_state = params->cacheability_control;
  cmd->dw7.shader_chanel_select_a = HSW_SCS_ALPHA;
  cmd->dw7.shader_chanel_select_b = HSW_SCS_BLUE;
  cmd->dw7.shader_chanel_select_g = HSW_SCS_GREEN;
  cmd->dw7.shader_chanel_select_r = HSW_SCS_RED;
}

VOID
media_add_surface_state (SURFACE_SET_PARAMS * params)
{
  UINT width, height, format, pitch, tile_alignment, y_offset = 0;
  if (params->surface_is_2d)
    {
      SURFACE_STATE_G7 *cmd =
	(SURFACE_STATE_G7 *) (params->binding_surface_state.buf +
			      params->surface_state_offset);
      *cmd = SURFACE_STATE_INIT_G7;
      width =
	(params->media_block_raw) ? ((params->surface_2d->width +
				      0x3) >> 2) : params->surface_2d->width;
      height = params->surface_2d->height;

      media_set_surface_state_2d_surface (cmd, params, params->format, width,
					  height, 0, 0, 0);

      dri_bo_emit_reloc (params->binding_surface_state.bo,
			 I915_GEM_DOMAIN_RENDER, 0, 0,
			 params->surface_state_offset +
			 offsetof (SURFACE_STATE_G7, dw1),
			 params->surface_2d->bo);

      *((UINT *) ((CHAR *) params->binding_surface_state.buf +
			  params->binding_table_offset)) =
	params->surface_state_offset /*<< BINDING_TABLE_SURFACE_SHIFT */ ;
    }
  else if (params->surface_is_uv_2d)
    {
      UINT cbcr_offset;
      SURFACE_STATE_G7 *cmd =
	(SURFACE_STATE_G7 *) (params->binding_surface_state.buf +
			      params->surface_state_offset);
      *cmd = SURFACE_STATE_INIT_G7;
      if (params->surface_2d->tiling == I915_TILING_Y)
	{
	  tile_alignment = 32;
	}
      else if (params->surface_2d->tiling == I915_TILING_X)
	{
	  tile_alignment = 8;
	}
      else
	tile_alignment = 1;

      width =
	(params->media_block_raw) ? ((params->surface_2d->width +
				      0x3) >> 2) : params->surface_2d->width;
      height = params->surface_2d->height / 2;
      y_offset = (params->surface_2d->y_cb_offset % tile_alignment) >> 1;
      cbcr_offset =
	ALIGN_FLOOR ( /*params->surface_2d->height */ params->surface_2d->
		     y_cb_offset,
		     tile_alignment) * /*params->surface_2d->width */
	params->surface_2d->pitch;
      //cbcr_offset = params->surface_2d->y_cb_offset;    
      media_set_surface_state_2d_surface (cmd, params,
					  STATE_SURFACEFORMAT_R16_UINT, width,
					  height, 0, cbcr_offset, y_offset);

      dri_bo_emit_reloc (params->binding_surface_state.bo,
			 I915_GEM_DOMAIN_RENDER, 0,
			 cbcr_offset,
			 params->surface_state_offset +
			 offsetof (SURFACE_STATE_G7, dw1),
			 params->surface_2d->bo);

      *((UINT *) ((CHAR *) params->binding_surface_state.buf +
			  params->binding_table_offset)) =
	params->surface_state_offset /*<< BINDING_TABLE_SURFACE_SHIFT */ ;
    }
  else if (params->advance_state)
    {

      SURFACE_STATE_ADV_G7 *cmd =
	(SURFACE_STATE_ADV_G7 *) (params->binding_surface_state.buf +
				  params->surface_state_offset);
      *cmd = SURFACE_STATE_ADV_INIT_G7;
      media_set_surface_state_adv (cmd, params, MFX_SURFACE_PLANAR_420_8);

      dri_bo_emit_reloc (params->binding_surface_state.bo,
			 I915_GEM_DOMAIN_RENDER, 0,
			 params->offset,
			 params->surface_state_offset +
			 offsetof (SURFACE_STATE_ADV_G7, ss0),
			 params->surface_2d->bo);

      *((UINT *) ((CHAR *) params->binding_surface_state.buf +
			  params->binding_table_offset)) =
	params->surface_state_offset /*<< BINDING_TABLE_SURFACE_SHIFT */ ;
    }
  else
    {

      SURFACE_STATE_G7 *cmd =
	(SURFACE_STATE_G7 *) (params->binding_surface_state.buf +
			      params->surface_state_offset);
      *cmd = SURFACE_STATE_INIT_G7;
      MEDIA_DRV_ASSERT (params->buf_object.bo);
      if (params->surface_is_raw)
	{
	  format = STATE_SURFACEFORMAT_RAW;
	  pitch = 0;
	}
      else
	{
	  format = STATE_SURFACEFORMAT_R32_UINT;
	  pitch = sizeof (UINT) - 1;
	}

      media_set_surface_state_buffer_surface (cmd, params, format, pitch);

      dri_bo_emit_reloc (params->binding_surface_state.bo,
			 I915_GEM_DOMAIN_RENDER,
			 0 /* I915_GEM_DOMAIN_RENDER */ ,
			 params->offset,
			 params->surface_state_offset +
			 offsetof (SURFACE_STATE_G7, dw1),
			 params->buf_object.bo);

      *((UINT *) ((CHAR *) params->binding_surface_state.buf +
			  params->binding_table_offset)) =
	params->surface_state_offset /*<< BINDING_TABLE_SURFACE_SHIFT */ ;
    }

}

VOID
media_surface_state_vp8_mbpak (MEDIA_ENCODER_CTX * encoder_context,
			       struct encode_state *encode_state,
			       MBPAK_SURFACE_PARAMS_VP8 *
			       mbpak_sutface_params)
{
  MBPAK_CONTEXT *mbpak_ctx = &encoder_context->mbpak_context;
  MEDIA_GPE_CTX *mbpak_gpe_ctx = &mbpak_ctx->gpe_context;
  SURFACE_SET_PARAMS params;
  UINT kernel_dump_offset = 0;
  struct object_surface *obj_surface;
  //struct object_buffer *obj_buffer;
  BYTE *binding_surface_state_buf = NULL;
  MEDIA_RESOURCE surface_2d;	//={0,0,0};
  binding_surface_state_buf =
    (BYTE *) media_map_buffer_obj (mbpak_gpe_ctx->surface_state_binding_table.
				   res.bo);
  //coded data buffer
  params = surface_set_params_init;
  params.binding_surface_state.bo =
    mbpak_gpe_ctx->surface_state_binding_table.res.bo;
  params.binding_surface_state.buf = binding_surface_state_buf;
  params.binding_table_offset = BINDING_TABLE_OFFSET (0);
  params.surface_state_offset = SURFACE_STATE_OFFSET (0);
  obj_surface = encode_state->coded_buf_surface;
  OBJECT_SURFACE_TO_MEDIA_RESOURCE_STRUCT (surface_2d, obj_surface);
  params.buf_object = surface_2d;
  //params.surface_is_raw = 1;
  params.offset = 0;
  params.cacheability_control = mbpak_sutface_params->cacheability_control;
  params.size =
    WIDTH_IN_MACROBLOCKS ((mbpak_sutface_params->orig_frame_width) *
			  HEIGHT_IN_MACROBLOCKS
			  (mbpak_sutface_params->orig_frame_height) *
			  MB_CODE_SIZE_VP8 * sizeof (UINT));
  media_add_surface_state (&params);
  //current pic luma

  params = surface_set_params_init;
  params.binding_surface_state.bo =
    mbpak_gpe_ctx->surface_state_binding_table.res.bo;
  params.binding_surface_state.buf = binding_surface_state_buf;
  params.surface_is_2d = 1;
  params.media_block_raw = 0;
  params.vert_line_stride_offset = 0;
  params.vert_line_stride = 0;
  params.format = STATE_SURFACEFORMAT_R8_UNORM;
  params.binding_table_offset = BINDING_TABLE_OFFSET (1);
  params.surface_state_offset = SURFACE_STATE_OFFSET (1);
  obj_surface = encode_state->input_yuv_object;
  OBJECT_SURFACE_TO_MEDIA_RESOURCE_STRUCT (surface_2d, obj_surface);
  params.surface_2d = &surface_2d;
  params.cacheability_control = mbpak_sutface_params->cacheability_control;
  media_add_surface_state (&params);

//current pic uv
  params = surface_set_params_init;
  params.binding_surface_state.bo =
    mbpak_gpe_ctx->surface_state_binding_table.res.bo;
  params.binding_surface_state.buf = binding_surface_state_buf;
  params.surface_is_uv_2d = 1;
  params.media_block_raw = 0;
  params.vert_line_stride_offset = 0;
  params.vert_line_stride = 0;
  params.format = STATE_SURFACEFORMAT_R8_UNORM;
  params.binding_table_offset = BINDING_TABLE_OFFSET (2);
  params.surface_state_offset = SURFACE_STATE_OFFSET (2);
  obj_surface = encode_state->input_yuv_object;
  OBJECT_SURFACE_TO_MEDIA_RESOURCE_STRUCT (surface_2d, obj_surface);
  params.surface_2d = &surface_2d;
  params.cacheability_control = mbpak_sutface_params->cacheability_control;
  media_add_surface_state (&params);

  //current reconstructed picture luma

  params = surface_set_params_init;
  params.binding_surface_state.bo =
    mbpak_gpe_ctx->surface_state_binding_table.res.bo;
  params.binding_surface_state.buf = binding_surface_state_buf;
  params.surface_is_2d = 1;
  params.media_block_raw = 0;
  params.vert_line_stride_offset = 0;
  params.vert_line_stride = 0;
  params.format = STATE_SURFACEFORMAT_R8_UNORM;
  params.binding_table_offset = BINDING_TABLE_OFFSET (3);
  params.surface_state_offset = SURFACE_STATE_OFFSET (3);
  obj_surface = encode_state->reconstructed_object;
  OBJECT_SURFACE_TO_MEDIA_RESOURCE_STRUCT (surface_2d, obj_surface);
  params.surface_2d = &surface_2d;
  params.cacheability_control = mbpak_sutface_params->cacheability_control;
  media_add_surface_state (&params);

// current reconstructed picture uv
  params = surface_set_params_init;
  params.binding_surface_state.bo =
    mbpak_gpe_ctx->surface_state_binding_table.res.bo;
  params.binding_surface_state.buf = binding_surface_state_buf;
  params.surface_is_uv_2d = 1;
  params.media_block_raw = 0;
  params.vert_line_stride_offset = 0;
  params.vert_line_stride = 0;
  params.format = STATE_SURFACEFORMAT_R8_UNORM;
  params.binding_table_offset = BINDING_TABLE_OFFSET (4);
  params.surface_state_offset = SURFACE_STATE_OFFSET (4);
  obj_surface = encode_state->reconstructed_object;
  OBJECT_SURFACE_TO_MEDIA_RESOURCE_STRUCT (surface_2d, obj_surface);
  params.surface_2d = &surface_2d;
  params.cacheability_control = mbpak_sutface_params->cacheability_control;
  media_add_surface_state (&params);

  if (mbpak_sutface_params->mbpak_phase_type == MBPAK_HYBRID_STATE_P1)
    {
      //MV Data surface 
      params = surface_set_params_init;
      params.binding_surface_state.bo =
	mbpak_gpe_ctx->surface_state_binding_table.res.bo;
      params.binding_surface_state.buf = binding_surface_state_buf;
      params.binding_table_offset = BINDING_TABLE_OFFSET (11);
      params.surface_state_offset = SURFACE_STATE_OFFSET (11);
      obj_surface = encode_state->coded_buf_surface;
      OBJECT_SURFACE_TO_MEDIA_RESOURCE_STRUCT (surface_2d, obj_surface);
      params.buf_object = surface_2d;
      //params.surface_is_raw = 1;
      params.offset = encoder_context->mv_offset;
      params.size =
	WIDTH_IN_MACROBLOCKS (mbpak_sutface_params->orig_frame_width) *
	HEIGHT_IN_MACROBLOCKS (mbpak_sutface_params->orig_frame_height) * 64;
      params.cacheability_control =
	mbpak_sutface_params->cacheability_control;
      media_add_surface_state (&params);

      //last ref
      if (encode_state->ref_last_frame != NULL
	  && encode_state->ref_last_frame->bo != NULL)
	{
	  params = surface_set_params_init;
	  params.binding_surface_state.bo =
	    mbpak_gpe_ctx->surface_state_binding_table.res.bo;
	  params.binding_surface_state.buf = binding_surface_state_buf;
	  params.surface_is_2d = 1;
	  params.media_block_raw = 1;

	  //params.advance_state = 1;
	  params.format = STATE_SURFACEFORMAT_R8_UNORM;
	  params.binding_table_offset = BINDING_TABLE_OFFSET (5);
	  params.surface_state_offset = SURFACE_STATE_OFFSET (5);
	  obj_surface = encode_state->ref_last_frame;
	  OBJECT_SURFACE_TO_MEDIA_RESOURCE_STRUCT (surface_2d, obj_surface);
	  params.surface_2d = &surface_2d;
	  params.cacheability_control =
	    mbpak_sutface_params->cacheability_control;
	  media_add_surface_state (&params);

	  params = surface_set_params_init;
	  params.binding_surface_state.bo =
	    mbpak_gpe_ctx->surface_state_binding_table.res.bo;
	  params.binding_surface_state.buf = binding_surface_state_buf;
	  params.surface_is_uv_2d = 1;
	  params.media_block_raw = 1;
	  //params.advance_state = 1;
	  params.format = STATE_SURFACEFORMAT_R8_UNORM;
	  params.binding_table_offset = BINDING_TABLE_OFFSET (6);
	  params.surface_state_offset = SURFACE_STATE_OFFSET (6);
	  obj_surface = encode_state->ref_last_frame;
	  OBJECT_SURFACE_TO_MEDIA_RESOURCE_STRUCT (surface_2d, obj_surface);
	  params.surface_2d = &surface_2d;
	  params.cacheability_control =
	    mbpak_sutface_params->cacheability_control;
	  media_add_surface_state (&params);
	}
      //goldeb ref
      if (encode_state->ref_gf_frame != NULL
	  && encode_state->ref_gf_frame->bo != NULL)
	{
	  params = surface_set_params_init;
	  params.binding_surface_state.bo =
	    mbpak_gpe_ctx->surface_state_binding_table.res.bo;
	  params.binding_surface_state.buf = binding_surface_state_buf;
	  //params.advance_state = 1;
	  params.surface_is_2d = 1;
	  params.media_block_raw = 1;
	  params.format = STATE_SURFACEFORMAT_R8_UNORM;
	  params.binding_table_offset = BINDING_TABLE_OFFSET (7);
	  params.surface_state_offset = SURFACE_STATE_OFFSET (7);
	  obj_surface = encode_state->ref_gf_frame;
	  OBJECT_SURFACE_TO_MEDIA_RESOURCE_STRUCT (surface_2d, obj_surface);
	  params.surface_2d = &surface_2d;
	  params.cacheability_control =
	    mbpak_sutface_params->cacheability_control;
	  media_add_surface_state (&params);

	  params = surface_set_params_init;
	  params.binding_surface_state.bo =
	    mbpak_gpe_ctx->surface_state_binding_table.res.bo;
	  params.binding_surface_state.buf = binding_surface_state_buf;
	  //params.advance_state = 1;
	  params.surface_is_uv_2d = 1;
	  params.media_block_raw = 1;
	  params.format = STATE_SURFACEFORMAT_R8_UNORM;
	  params.binding_table_offset = BINDING_TABLE_OFFSET (8);
	  params.surface_state_offset = SURFACE_STATE_OFFSET (8);
	  obj_surface = encode_state->ref_gf_frame;
	  OBJECT_SURFACE_TO_MEDIA_RESOURCE_STRUCT (surface_2d, obj_surface);
	  params.surface_2d = &surface_2d;
	  params.cacheability_control =
	    mbpak_sutface_params->cacheability_control;
	  media_add_surface_state (&params);

	}
      //alterbate ref
      if (encode_state->ref_arf_frame != NULL
	  && encode_state->ref_arf_frame->bo != NULL)
	{
	  params = surface_set_params_init;
	  params.binding_surface_state.bo =
	    mbpak_gpe_ctx->surface_state_binding_table.res.bo;
	  params.binding_surface_state.buf = binding_surface_state_buf;
	  //params.advance_state = 1;
	  params.surface_is_2d = 1;
	  params.media_block_raw = 1;
	  params.format = STATE_SURFACEFORMAT_R8_UNORM;
	  params.binding_table_offset = BINDING_TABLE_OFFSET (9);
	  params.surface_state_offset = SURFACE_STATE_OFFSET (9);
	  obj_surface = encode_state->ref_arf_frame;
	  OBJECT_SURFACE_TO_MEDIA_RESOURCE_STRUCT (surface_2d, obj_surface);
	  params.surface_2d = &surface_2d;
	  params.cacheability_control =
	    mbpak_sutface_params->cacheability_control;
	  media_add_surface_state (&params);

	  params = surface_set_params_init;
	  params.binding_surface_state.bo =
	    mbpak_gpe_ctx->surface_state_binding_table.res.bo;
	  params.binding_surface_state.buf = binding_surface_state_buf;
	  //params.advance_state = 1;
	  params.surface_is_uv_2d = 1;
	  params.media_block_raw = 1;
	  params.format = STATE_SURFACEFORMAT_R8_UNORM;
	  params.binding_table_offset = BINDING_TABLE_OFFSET (10);
	  params.surface_state_offset = SURFACE_STATE_OFFSET (10);
	  obj_surface = encode_state->ref_arf_frame;
	  OBJECT_SURFACE_TO_MEDIA_RESOURCE_STRUCT (surface_2d, obj_surface);
	  params.surface_2d = &surface_2d;
	  params.cacheability_control =
	    mbpak_sutface_params->cacheability_control;
	  media_add_surface_state (&params);

	}
      kernel_dump_offset = 12;
    }
  else
    {

      //row buffer y
      params = surface_set_params_init;
      params.binding_surface_state.bo =
	mbpak_gpe_ctx->surface_state_binding_table.res.bo;
      params.binding_surface_state.buf = binding_surface_state_buf;
      params.binding_table_offset = BINDING_TABLE_OFFSET (5);
      params.surface_state_offset = SURFACE_STATE_OFFSET (5);
      params.buf_object = mbpak_ctx->row_buffer_y;
      //params.surface_is_raw = 1;
      params.size = mbpak_ctx->row_buffer_y.bo_size;
      params.cacheability_control =
	mbpak_sutface_params->cacheability_control;
      media_add_surface_state (&params);

      //row buffer uv
      params = surface_set_params_init;
      params.binding_surface_state.bo =
	mbpak_gpe_ctx->surface_state_binding_table.res.bo;
      params.binding_surface_state.buf = binding_surface_state_buf;
      params.binding_table_offset = BINDING_TABLE_OFFSET (6);
      params.surface_state_offset = SURFACE_STATE_OFFSET (6);
      params.buf_object = mbpak_ctx->row_buffer_uv;
      //params.surface_is_raw = 1;
      params.size = mbpak_ctx->row_buffer_uv.bo_size;
      params.cacheability_control =
	mbpak_sutface_params->cacheability_control;
      media_add_surface_state (&params);

      //column buffer .y
      params = surface_set_params_init;
      params.binding_surface_state.bo =
	mbpak_gpe_ctx->surface_state_binding_table.res.bo;
      params.binding_surface_state.buf = binding_surface_state_buf;
      params.binding_table_offset = BINDING_TABLE_OFFSET (7);
      params.surface_state_offset = SURFACE_STATE_OFFSET (7);
      params.buf_object = mbpak_ctx->column_buffer_y;
      //params.surface_is_raw = 1;
      params.cacheability_control =
	mbpak_sutface_params->cacheability_control;
      params.size = mbpak_ctx->column_buffer_y.bo_size;
      media_add_surface_state (&params);

      //column buffer uv
      params = surface_set_params_init;
      params.binding_surface_state.bo =
	mbpak_gpe_ctx->surface_state_binding_table.res.bo;
      params.binding_surface_state.buf = binding_surface_state_buf;
      params.binding_table_offset = BINDING_TABLE_OFFSET (8);
      params.surface_state_offset = SURFACE_STATE_OFFSET (8);
      params.buf_object = mbpak_ctx->column_buffer_uv;
      //params.surface_is_raw = 1;
      params.size = mbpak_ctx->column_buffer_uv.bo_size;
      params.cacheability_control =
	mbpak_sutface_params->cacheability_control;
      media_add_surface_state (&params);
      kernel_dump_offset = 12;

    }

  if (mbpak_sutface_params->kernel_dump)
    {
      params = surface_set_params_init;
      params.binding_surface_state.bo =
	mbpak_gpe_ctx->surface_state_binding_table.res.bo;
      params.binding_surface_state.buf = binding_surface_state_buf;
      params.binding_table_offset = BINDING_TABLE_OFFSET (kernel_dump_offset);
      params.surface_state_offset = SURFACE_STATE_OFFSET (kernel_dump_offset);
      //FIXME:need to pass right buffer here..!
      params.buf_object = mbpak_sutface_params->kernel_dump_buffer;	//mbpak_ctx->kernel_dump_buffer;
      //params.surface_is_raw = 1;
      params.size =
	WIDTH_IN_MACROBLOCKS (mbpak_sutface_params->orig_frame_width) *
	HEIGHT_IN_MACROBLOCKS (mbpak_sutface_params->orig_frame_height) * 32;
      params.cacheability_control =
	mbpak_sutface_params->cacheability_control;
      media_add_surface_state (&params);

    }
  media_unmap_buffer_obj (mbpak_gpe_ctx->surface_state_binding_table.res.bo);
}


VOID
media_surface_state_vp8_mbenc (MEDIA_ENCODER_CTX * encoder_context,
			       struct encode_state *encode_state,
			       MBENC_SURFACE_PARAMS_VP8 *
			       mbenc_sutface_params)
{
  MBENC_CONTEXT *mbenc_ctx = &encoder_context->mbenc_context;
  MEDIA_GPE_CTX *mbenc_gpe_ctx = &mbenc_ctx->gpe_context;
  //ME_CONTEXT *me_ctx = &encoder_context->me_context;
  UINT kernel_dump_offset = 0;
  SURFACE_SET_PARAMS params;
  struct object_surface *obj_surface;
  //struct object_buffer *obj_buffer;
  BYTE *binding_surface_state_buf = NULL;
  MEDIA_RESOURCE surface_2d;
  //MEDIA_RESOURCE *obj_buffer_res;
  binding_surface_state_buf =
    (BYTE *) media_map_buffer_obj (mbenc_gpe_ctx->surface_state_binding_table.
				   res.bo);
  //media_drv_memset(binding_surface_state_buf,mbenc_gpe_ctx->surface_state_binding_table.res.bo->size);
  //coded data buffer
  params = surface_set_params_init;
  params.binding_surface_state.bo =
    mbenc_gpe_ctx->surface_state_binding_table.res.bo;
  params.binding_surface_state.buf = binding_surface_state_buf;
  params.binding_table_offset = BINDING_TABLE_OFFSET (0);
  params.surface_state_offset = SURFACE_STATE_OFFSET (0);
  obj_surface = encode_state->coded_buf_surface;
  OBJECT_SURFACE_TO_MEDIA_RESOURCE_STRUCT (surface_2d, obj_surface);
  params.buf_object = surface_2d;
  params.surface_is_raw = 1;
  params.offset = 0;
  params.size =
    WIDTH_IN_MACROBLOCKS ((mbenc_sutface_params->orig_frame_width) *
			  HEIGHT_IN_MACROBLOCKS
			  (mbenc_sutface_params->orig_frame_height) *
			  MB_CODE_SIZE_VP8 * sizeof (UINT));
  params.cacheability_control = mbenc_sutface_params->cacheability_control;
  media_add_surface_state (&params);
//current pic luma
  params = surface_set_params_init;
  params.binding_surface_state.bo =
    mbenc_gpe_ctx->surface_state_binding_table.res.bo;
  params.binding_surface_state.buf = binding_surface_state_buf;
  params.surface_is_2d = 1;
  params.media_block_raw = 1;
  params.vert_line_stride_offset = 0;
  params.vert_line_stride = 0;
  params.format = STATE_SURFACEFORMAT_R8_UNORM;
  params.binding_table_offset = BINDING_TABLE_OFFSET (1);
  params.surface_state_offset = SURFACE_STATE_OFFSET (1);
  obj_surface = encode_state->input_yuv_object;
  OBJECT_SURFACE_TO_MEDIA_RESOURCE_STRUCT (surface_2d, obj_surface);
  params.surface_2d = &surface_2d;
  params.cacheability_control = mbenc_sutface_params->cacheability_control;
  media_add_surface_state (&params);

//current pic uv
  params = surface_set_params_init;
  params.binding_surface_state.bo =
    mbenc_gpe_ctx->surface_state_binding_table.res.bo;
  params.binding_surface_state.buf = binding_surface_state_buf;
  params.surface_is_uv_2d = 1;
  params.media_block_raw = 1;
  params.vert_line_stride_offset = 0;
  params.vert_line_stride = 0;
  params.format = STATE_SURFACEFORMAT_R8_UNORM;
  params.binding_table_offset = BINDING_TABLE_OFFSET (2);
  params.surface_state_offset = SURFACE_STATE_OFFSET (2);
  obj_surface = encode_state->input_yuv_object;
  OBJECT_SURFACE_TO_MEDIA_RESOURCE_STRUCT (surface_2d, obj_surface);
  params.surface_2d = &surface_2d;
  params.cacheability_control = mbenc_sutface_params->cacheability_control;
  media_add_surface_state (&params);


  if (mbenc_sutface_params->pic_coding == FRAME_TYPE_I)
    {
      params = surface_set_params_init;
      params.binding_surface_state.bo =
	mbenc_gpe_ctx->surface_state_binding_table.res.bo;
      params.binding_surface_state.buf = binding_surface_state_buf;
      params.advance_state = 1;
      params.format = STATE_SURFACEFORMAT_R8_UNORM;
      params.binding_table_offset = BINDING_TABLE_OFFSET (9);
      params.surface_state_offset = SURFACE_STATE_OFFSET (9);
      obj_surface = encode_state->input_yuv_object;
      OBJECT_SURFACE_TO_MEDIA_RESOURCE_STRUCT (surface_2d, obj_surface);
      params.surface_2d = &surface_2d;
      params.uv_direction = VDIRECTION_FULL_FRAME;
      params.cacheability_control =
	mbenc_sutface_params->cacheability_control;
      media_add_surface_state (&params);

      //MBMode Cost Luma surface  
      params = surface_set_params_init;
      params.binding_surface_state.bo =
	mbenc_gpe_ctx->surface_state_binding_table.res.bo;
      params.binding_surface_state.buf = binding_surface_state_buf;
      params.surface_is_2d = 1;
      params.format = STATE_SURFACEFORMAT_R8_UNORM;
      params.binding_table_offset = BINDING_TABLE_OFFSET (3);
      params.surface_state_offset = SURFACE_STATE_OFFSET (3);
      params.surface_2d = &mbenc_ctx->mb_mode_cost_luma_buffer;
      params.cacheability_control =
	mbenc_sutface_params->cacheability_control;
      media_add_surface_state (&params);

      //Block Mode cost surface  
      params = surface_set_params_init;
      params.binding_surface_state.bo =
	mbenc_gpe_ctx->surface_state_binding_table.res.bo;
      params.binding_surface_state.buf = binding_surface_state_buf;
      params.surface_is_2d = 1;
      params.format = STATE_SURFACEFORMAT_R8_UNORM;
      params.binding_table_offset = BINDING_TABLE_OFFSET (4);
      params.surface_state_offset = SURFACE_STATE_OFFSET (4);
      params.surface_2d = &mbenc_ctx->block_mode_cost_buffer;
      params.cacheability_control =
	mbenc_sutface_params->cacheability_control;
      media_add_surface_state (&params);

      //Chroma Reconstruction Surface
      params = surface_set_params_init;
      params.binding_surface_state.bo =
	mbenc_gpe_ctx->surface_state_binding_table.res.bo;
      params.binding_surface_state.buf = binding_surface_state_buf;
      params.surface_is_2d = 1;
      params.media_block_raw = 1;
      params.format = STATE_SURFACEFORMAT_R8_UNORM;
      params.binding_table_offset = BINDING_TABLE_OFFSET (5);
      params.surface_state_offset = SURFACE_STATE_OFFSET (5);
      params.surface_2d = &mbenc_ctx->chroma_reconst_buffer;
      params.cacheability_control =
	mbenc_sutface_params->cacheability_control;
      media_add_surface_state (&params);

      //histogram
      params = surface_set_params_init;
      params.binding_surface_state.bo =
	mbenc_gpe_ctx->surface_state_binding_table.res.bo;
      params.binding_surface_state.buf = binding_surface_state_buf;
      params.binding_table_offset = BINDING_TABLE_OFFSET (7);
      params.surface_state_offset = SURFACE_STATE_OFFSET (7);
      params.buf_object = mbenc_ctx->histogram_buffer;
      params.surface_is_raw = 1;
      params.size = mbenc_ctx->histogram_buffer.bo_size;
      params.cacheability_control =
	mbenc_sutface_params->cacheability_control;
      media_add_surface_state (&params);
      kernel_dump_offset = 8;

    }
  else
    {
      //MV Data surface
      params = surface_set_params_init;
      params.binding_surface_state.bo =
	mbenc_gpe_ctx->surface_state_binding_table.res.bo;
      params.binding_surface_state.buf = binding_surface_state_buf;
      params.binding_table_offset = BINDING_TABLE_OFFSET (4);
      params.surface_state_offset = SURFACE_STATE_OFFSET (4);
      obj_surface = encode_state->coded_buf_surface;
      OBJECT_SURFACE_TO_MEDIA_RESOURCE_STRUCT (surface_2d, obj_surface);
      params.buf_object = surface_2d;
      params.media_block_raw = 1;
      params.surface_is_raw = 1;
      params.offset = encoder_context->mv_offset;
      params.size = WIDTH_IN_MACROBLOCKS (mbenc_sutface_params->orig_frame_width) * HEIGHT_IN_MACROBLOCKS (mbenc_sutface_params->orig_frame_height) * 64;

      params.cacheability_control =
	mbenc_sutface_params->cacheability_control;
      media_add_surface_state (&params);
      if (mbenc_sutface_params->hme_enabled)
	{
	  /*need to add me mv data buffer surface states here later */

	}

      //reference frame mb count 
      params = surface_set_params_init;
      params.binding_surface_state.bo =
	mbenc_gpe_ctx->surface_state_binding_table.res.bo;
      params.binding_surface_state.buf = binding_surface_state_buf;
      params.binding_table_offset = BINDING_TABLE_OFFSET (5);
      params.surface_state_offset = SURFACE_STATE_OFFSET (5);
      params.buf_object = mbenc_ctx->ref_frm_count_surface;
      params.media_block_raw = 1;
      params.size = (sizeof (UINT) * 8);
      media_add_surface_state (&params);

      //current picture VME inter prediction surface..!
      params = surface_set_params_init;
      params.binding_surface_state.bo =
	mbenc_gpe_ctx->surface_state_binding_table.res.bo;
      params.binding_surface_state.buf = binding_surface_state_buf;
      params.advance_state = 1;
      params.format = STATE_SURFACEFORMAT_R8_UNORM;
      params.binding_table_offset = BINDING_TABLE_OFFSET (8);
      params.surface_state_offset = SURFACE_STATE_OFFSET (8);
      obj_surface = encode_state->input_yuv_object;
      OBJECT_SURFACE_TO_MEDIA_RESOURCE_STRUCT (surface_2d, obj_surface);
      params.surface_2d = &surface_2d;
      params.uv_direction = VDIRECTION_FULL_FRAME;
      params.cacheability_control =
	mbenc_sutface_params->cacheability_control;
      media_add_surface_state (&params);

      //last ref
      if (encode_state->ref_last_frame != NULL
	  && encode_state->ref_last_frame->bo != NULL)
	{
	  params = surface_set_params_init;
	  params.binding_surface_state.bo =
	    mbenc_gpe_ctx->surface_state_binding_table.res.bo;
	  params.binding_surface_state.buf = binding_surface_state_buf;
	  params.advance_state = 1;
	  params.format = STATE_SURFACEFORMAT_R8_UNORM;
	  params.binding_table_offset = BINDING_TABLE_OFFSET (9);
	  params.surface_state_offset = SURFACE_STATE_OFFSET (9);
	  obj_surface = encode_state->ref_last_frame;
	  OBJECT_SURFACE_TO_MEDIA_RESOURCE_STRUCT (surface_2d, obj_surface);
	  params.surface_2d = &surface_2d;
	  params.uv_direction = VDIRECTION_FULL_FRAME;
	  params.cacheability_control =
	    mbenc_sutface_params->cacheability_control;
	  media_add_surface_state (&params);
	}

      //goldeb ref
      if (encode_state->ref_gf_frame != NULL
	  && encode_state->ref_gf_frame->bo != NULL)
	{
	  params = surface_set_params_init;
	  params.binding_surface_state.bo =
	    mbenc_gpe_ctx->surface_state_binding_table.res.bo;
	  params.binding_surface_state.buf = binding_surface_state_buf;
	  params.advance_state = 1;
	  params.format = STATE_SURFACEFORMAT_R8_UNORM;
	  params.binding_table_offset = BINDING_TABLE_OFFSET (11);
	  params.surface_state_offset = SURFACE_STATE_OFFSET (11);
	  obj_surface = encode_state->ref_gf_frame;
	  OBJECT_SURFACE_TO_MEDIA_RESOURCE_STRUCT (surface_2d, obj_surface);
	  params.surface_2d = &surface_2d;
	  params.uv_direction = VDIRECTION_FULL_FRAME;
	  params.cacheability_control =
	    mbenc_sutface_params->cacheability_control;
	  media_add_surface_state (&params);
	}

      //alternate ref
      if (encode_state->ref_arf_frame != NULL
	  && encode_state->ref_arf_frame->bo != NULL)
	{
	  params = surface_set_params_init;
	  params.binding_surface_state.bo =
	    mbenc_gpe_ctx->surface_state_binding_table.res.bo;
	  params.binding_surface_state.buf = binding_surface_state_buf;
	  params.advance_state = 1;
	  params.format = STATE_SURFACEFORMAT_R8_UNORM;
	  params.binding_table_offset = BINDING_TABLE_OFFSET (13);
	  params.surface_state_offset = SURFACE_STATE_OFFSET (13);
	  obj_surface = encode_state->ref_arf_frame;
	  OBJECT_SURFACE_TO_MEDIA_RESOURCE_STRUCT (surface_2d, obj_surface);
	  params.surface_2d = &surface_2d;
	  params.uv_direction = VDIRECTION_FULL_FRAME;
	  params.cacheability_control =
	    mbenc_sutface_params->cacheability_control;
	  media_add_surface_state (&params);
	}
      //Per-MB quant data surface
      params = surface_set_params_init;
      params.binding_surface_state.bo =
	mbenc_gpe_ctx->surface_state_binding_table.res.bo;
      params.binding_surface_state.buf = binding_surface_state_buf;
      params.surface_is_2d = 1;
      params.media_block_raw = 1;
      params.vert_line_stride_offset = 0;
      params.vert_line_stride = 0;
      params.format = STATE_SURFACEFORMAT_R8_UNORM;
      params.binding_table_offset = BINDING_TABLE_OFFSET (15);
      params.surface_state_offset = SURFACE_STATE_OFFSET (15);
      params.surface_2d = &mbenc_ctx->pred_mb_quant_data_surface;
      params.cacheability_control =
	mbenc_sutface_params->cacheability_control;
      media_add_surface_state (&params);

      if (mbenc_sutface_params->seg_enabled)
	{

	  //need to add per segmentation map later here
	}

#if 0
      //Inter Prediction Distortion Surface
      params = surface_set_params_init;
      params.binding_surface_state.bo =
	mbenc_gpe_ctx->surface_state_binding_table.res.bo;
      params.binding_surface_state.buf = binding_surface_state_buf;
      params.surface_is_2d = 1;
      params.format = STATE_SURFACEFORMAT_R8_UNORM;
      params.binding_table_offset = BINDING_TABLE_OFFSET (17);
      params.surface_state_offset = SURFACE_STATE_OFFSET (17);
      params.surface_2d = &me_ctx->mv_distortion_surface_4x_me;
      media_add_surface_state (&params);
#endif

      //Histogram Surface
      params = surface_set_params_init;
      params.binding_surface_state.bo =
	mbenc_gpe_ctx->surface_state_binding_table.res.bo;
      params.binding_surface_state.buf = binding_surface_state_buf;
      params.binding_table_offset = BINDING_TABLE_OFFSET (18);
      params.surface_state_offset = SURFACE_STATE_OFFSET (18);
      params.buf_object = mbenc_ctx->histogram_buffer;
      params.surface_is_raw = 1;
      params.size = mbenc_ctx->histogram_buffer.bo_size;
      params.cacheability_control =
	mbenc_sutface_params->cacheability_control;
      media_add_surface_state (&params);

      //Pred MV Data Surface
      params = surface_set_params_init;
      params.binding_surface_state.bo =
	mbenc_gpe_ctx->surface_state_binding_table.res.bo;
      params.binding_surface_state.buf = binding_surface_state_buf;
      params.binding_table_offset = BINDING_TABLE_OFFSET (19);
      params.surface_state_offset = SURFACE_STATE_OFFSET (19);
      params.buf_object = mbenc_ctx->pred_mv_data_surface;
      params.size = mbenc_ctx->pred_mv_data_surface.bo_size;
      params.media_block_raw = 1;
      media_add_surface_state (&params);

      //ModeCost Update Surface
      params = surface_set_params_init;
      params.binding_surface_state.bo =
	mbenc_gpe_ctx->surface_state_binding_table.res.bo;
      params.binding_surface_state.buf = binding_surface_state_buf;
      params.binding_table_offset = BINDING_TABLE_OFFSET (20);
      params.surface_state_offset = SURFACE_STATE_OFFSET (20);
      params.buf_object = mbenc_ctx->mode_cost_update_surface;
      params.size = 64;		//mbenc_ctx->mode_cost_update_surface.bo_size;
      params.surface_is_raw = 1;
      media_add_surface_state (&params);
      kernel_dump_offset = 21;

    }

  if (mbenc_sutface_params->kernel_dump)
    {
      params = surface_set_params_init;
      params.binding_surface_state.bo =
	mbenc_gpe_ctx->surface_state_binding_table.res.bo;
      params.binding_surface_state.buf = binding_surface_state_buf;
      params.binding_table_offset = BINDING_TABLE_OFFSET (kernel_dump_offset);
      params.surface_state_offset = SURFACE_STATE_OFFSET (kernel_dump_offset);
      params.buf_object = mbenc_ctx->kernel_dump_buffer;
      //params.surface_is_raw = 1;
      params.cacheability_control =
	mbenc_sutface_params->cacheability_control;
      params.size =
	WIDTH_IN_MACROBLOCKS ((mbenc_sutface_params->orig_frame_width) *
			      HEIGHT_IN_MACROBLOCKS (mbenc_sutface_params->
						     orig_frame_height) *
			      /*MB_CODE_SIZE_VP8 */ 32);
      params.offset = encoder_context->mv_offset;
      media_add_surface_state (&params);

    }

  media_unmap_buffer_obj (mbenc_gpe_ctx->surface_state_binding_table.res.bo);
}

VOID
media_surface_state_vp8_me (MEDIA_ENCODER_CTX * encoder_context,
			    ME_SURFACE_PARAMS_VP8 * me_sutface_params)
{

#if 0
  ME_CONTEXT *me_ctx = &encoder_context->me_context;
  MEDIA_GPE_CTX *me_gpe_ctx = &me_ctx->gpe_context;
  MEDIA_RESOURCE *mv_data_surface;
  SURFACE_SET_PARAMS params;
  BYTE *binding_surface_state_buf = NULL;
  //if 16xme enabled  
  //params.binding_surface_state.bo =
  //me_sutface_params->me_surface_state_binding_table->res.bo;
  binding_surface_state_buf =
    (CHAR *)
    media_map_buffer_obj (me_sutface_params->me_surface_state_binding_table->
			  res.bo);
  if (me_sutface_params->me_16x_in_use)
    {
      mv_data_surface = &me_ctx->mv_data_surface_16x_me;
    }
  else
    {
      mv_data_surface = &me_ctx->mv_data_surface_4x_me;
    }


  params = surface_set_params_init;
  params.binding_surface_state.bo =
    me_gpe_ctx->surface_state_binding_table.res.bo;
  params.binding_surface_state.buf = binding_surface_state_buf;
  params.surface_is_2d = 1;
  params.vert_line_stride_offset = 0;
  params.vert_line_stride = 0;
  params.format = STATE_SURFACEFORMAT_R8_UNORM;
  params.binding_table_offset = BINDING_TABLE_OFFSET (0);
  params.surface_state_offset = SURFACE_STATE_OFFSET (0);
  params.surface_2d = mv_data_surface;
  media_add_surface_state (&params);

  if (me_sutface_params->me_i6x_enabled)
    {

      //16xme in use
      params = surface_set_params_init;
      params.binding_surface_state.bo =
	me_gpe_ctx->surface_state_binding_table.res.bo;
      params.binding_surface_state.buf = binding_surface_state_buf;
      params.surface_is_2d = 1;
      params.vert_line_stride_offset = 0;
      params.vert_line_stride = 0;
      params.format = STATE_SURFACEFORMAT_R8_UNORM;
      params.binding_table_offset = BINDING_TABLE_OFFSET (1);
      params.surface_state_offset = SURFACE_STATE_OFFSET (1);
      params.surface_2d = &me_ctx->mv_data_surface_16x_me;
      media_add_surface_state (&params);
    }
  if (!me_sutface_params->me_16x_in_use)
    {

      //me distortion
      params = surface_set_params_init;
      params.binding_surface_state.bo =
	me_gpe_ctx->surface_state_binding_table.res.bo;
      params.binding_surface_state.buf = binding_surface_state_buf;
      params.surface_is_2d = 1;
      params.vert_line_stride_offset = 0;
      params.vert_line_stride = 0;
      params.format = STATE_SURFACEFORMAT_R8_UNORM;
      params.binding_table_offset = BINDING_TABLE_OFFSET (2);
      params.surface_state_offset = SURFACE_STATE_OFFSET (2);
      params.surface_2d = &me_ctx->mv_distortion_surface_4x_me;
      media_add_surface_state (&params);


      //me brc distortion
      params = surface_set_params_init;
      params.binding_surface_state.bo =
	me_gpe_ctx->surface_state_binding_table.res.bo;
      params.binding_surface_state.buf = binding_surface_state_buf;
      params.surface_is_2d = 1;
      params.vert_line_stride_offset = 0;
      params.vert_line_stride = 0;
      params.format = STATE_SURFACEFORMAT_R8_UNORM;
      params.binding_table_offset = BINDING_TABLE_OFFSET (3);
      params.surface_state_offset = SURFACE_STATE_OFFSET (3);
      params.surface_2d = &me_ctx->mv_distortion_surface_4x_me;
      media_add_surface_state (&params);
    }


  //current picture
  params = surface_set_params_init;
  params.binding_surface_state.bo =
    me_gpe_ctx->surface_state_binding_table.res.bo;
  params.binding_surface_state.buf = binding_surface_state_buf;
  params.surface_is_2d = 1;
  params.vert_line_stride_offset = 0;
  params.vert_line_stride = 0;
  params.format = STATE_SURFACEFORMAT_R8_UNORM;
  params.binding_table_offset = BINDING_TABLE_OFFSET (4);
  params.surface_state_offset = SURFACE_STATE_OFFSET (4);
  params.surface_2d = &me_ctx->mv_data_surface_16x_me;
  media_add_surface_state (&params);


//forward ref pic-golden/alternate/last
  params = surface_set_params_init;
  params.binding_surface_state.bo =
    me_gpe_ctx->surface_state_binding_table.res.bo;
  params.binding_surface_state.buf = binding_surface_state_buf;
  params.surface_is_2d = 1;
  params.vert_line_stride_offset = 0;
  params.vert_line_stride = 0;
  params.format = STATE_SURFACEFORMAT_R8_UNORM;
  params.binding_table_offset = BINDING_TABLE_OFFSET (5);
  params.surface_state_offset = SURFACE_STATE_OFFSET (5);
  params.surface_2d = &me_ctx->mv_data_surface_16x_me;
  media_add_surface_state (&params);


  media_unmap_buffer_obj (me_sutface_params->
			  me_surface_state_binding_table->res.bo);
#endif
}

VOID
media_surface_state_scaling (MEDIA_ENCODER_CTX * encoder_context,
			     SCALING_SURFACE_PARAMS * scaling_sutface_params)
{
#if 0
  SURFACE_SET_PARAMS params;
  SCALING_CONTEXT *scaling_ctx = &encoder_context->scaling_context;
  MEDIA_GPE_CTX *scaling_gpe_ctx = &scaling_ctx->gpe_context;
  BYTE *binding_surface_state_buf = NULL;
  binding_surface_state_buf =
    (CHAR *)
    media_map_buffer_obj (scaling_gpe_ctx->surface_state_binding_table.res.
			  bo);
  //input buffer
  params = surface_set_params_init;
  params.binding_surface_state.bo =
    scaling_gpe_ctx->surface_state_binding_table.res.bo;
  params.binding_surface_state.buf = binding_surface_state_buf;
  params.surface_is_2d = 1;
  params.media_block_raw = 1;
  params.vert_line_stride_offset = 0;
  params.vert_line_stride = 0;
  params.format = STATE_SURFACEFORMAT_R8_UNORM;
  params.binding_table_offset = BINDING_TABLE_OFFSET (0);
  params.surface_state_offset = SURFACE_STATE_OFFSET (0);
  params.surface_2d = &scaling_sutface_params->scaling_input_surface;
  params.surface_2d->width = ALIGN (scaling_sutface_params->input_width, 16);
  params.surface_2d->height =
    ALIGN (scaling_sutface_params->input_height, 16);
  media_add_surface_state (&params);

  //destination
  params = surface_set_params_init;
  params.binding_surface_state.bo =
    scaling_gpe_ctx->surface_state_binding_table.res.bo;
  params.binding_surface_state.buf = binding_surface_state_buf;
  params.surface_is_2d = 1;
  params.media_block_raw = 1;
  params.vert_line_stride_offset = 0;
  params.vert_line_stride = 0;
  params.format = STATE_SURFACEFORMAT_R8_UNORM;
  params.binding_table_offset = BINDING_TABLE_OFFSET (1);
  params.surface_state_offset = SURFACE_STATE_OFFSET (1);
  params.surface_2d = &scaling_sutface_params->scaling_output_surface;
  params.surface_2d->width = ALIGN (scaling_sutface_params->output_width, 16);
  params.surface_2d->height =
    ALIGN (scaling_sutface_params->output_height, 16);
  media_add_surface_state (&params);

  media_unmap_buffer_obj (scaling_gpe_ctx->surface_state_binding_table.
			  res.bo);
#endif
}