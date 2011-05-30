/*****************************************************************************/
/*! \file    uEye.h
*   \author  (c) 2004-2009 by Imaging Development Systems GmbH
*   \date    $Date: 2009/11/04 $
*   \version $PRODUCTVERSION: 3.50 $
*   \version $Revision: 70 $
*
*   \brief   Library interface for IDS uEye - camera family.
*            definition of exported API functions and constants
*//***************************************************************************/

#ifndef __IDS_HEADER__ 
#define __IDS_HEADER__

#pragma pack(push, 8)

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

// ----------------------------------------------------------------------------
// Version definition
// ----------------------------------------------------------------------------
#ifndef UEYE_VERSION
#   define UEYE_VERSION(major, minor, build)    (((major)<<24) + ((minor)<<16) + (build))
#endif

#ifndef UEYE_VERSION_CODE
#   define UEYE_VERSION_CODE   UEYE_VERSION(3, 50, 0)
#endif

// ----------------------------------------------------------------------------
// Driver name
// ----------------------------------------------------------------------------

#if defined(__linux__) || defined(__LINUX__)
#   define DRIVER_DLL_NAME                  "libueye_api.so"
#elif defined (_WIN64)
#   define DRIVER_DLL_NAME                  "ueye_api_64.dll"
#else
#   define DRIVER_DLL_NAME                  "ueye_api.dll"
#endif


// ----------------------------------------------------------------------------
// Color modes
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
//  Sensor Types
// ----------------------------------------------------------------------------
#define IS_SENSOR_INVALID           0x0000

// CMOS Sensors
#define IS_SENSOR_UI141X_M          0x0001      // VGA rolling shutter, monochrome
#define IS_SENSOR_UI141X_C          0x0002      // VGA rolling shutter, color
#define IS_SENSOR_UI144X_M          0x0003      // SXGA rolling shutter, monochrome
#define IS_SENSOR_UI144X_C          0x0004      // SXGA rolling shutter, SXGA color

#define IS_SENSOR_UI154X_M          0x0030      // SXGA rolling shutter, monochrome
#define IS_SENSOR_UI154X_C          0x0031      // SXGA rolling shutter, color
#define IS_SENSOR_UI145X_C          0x0008      // UXGA rolling shutter, color

#define IS_SENSOR_UI146X_C          0x000a      // QXGA rolling shutter, color
#define IS_SENSOR_UI148X_M          0x000b      // 5MP rolling shutter, mono
#define IS_SENSOR_UI148X_C          0x000c      // 5MP rolling shutter, color

#define IS_SENSOR_UI121X_M          0x0010      // VGA global shutter, monochrome
#define IS_SENSOR_UI121X_C          0x0011      // VGA global shutter, VGA color
#define IS_SENSOR_UI122X_M          0x0012      // WVGA global shutter, monochrome
#define IS_SENSOR_UI122X_C          0x0013      // WVGA global shutter, color

#define IS_SENSOR_UI164X_C          0x0015      // SXGA rolling shutter, color

#define IS_SENSOR_UI155X_C          0x0017      // UXGA rolling shutter, color

#define IS_SENSOR_UI1223_M          0x0018      // WVGA global shutter, monochrome
#define IS_SENSOR_UI1223_C          0x0019      // WVGA global shutter, color

#define IS_SENSOR_UI149X_M          0x003E      // 149x-M
#define IS_SENSOR_UI149X_C          0x003F      // 149x-C

// LE models with xxx5
#define IS_SENSOR_UI1225_M          0x0022      // WVGA global shutter, monochrome, LE model
#define IS_SENSOR_UI1225_C          0x0023      // WVGA global shutter, color, LE model

#define IS_SENSOR_UI1645_C          0x0025      // SXGA rolling shutter, color, LE model
#define IS_SENSOR_UI1555_C          0x0027      // UXGA rolling shutter, color, LE model
#define IS_SENSOR_UI1545_M          0x0028      // SXGA rolling shutter, monochrome, LE model
#define IS_SENSOR_UI1545_C          0x0029      // SXGA rolling shutter, color, LE model
#define IS_SENSOR_UI1455_C          0x002B      // UXGA rolling shutter, color, LE model
#define IS_SENSOR_UI1465_C          0x002D      // QXGA rolling shutter, color, LE model
#define IS_SENSOR_UI1485_M          0x002E      // 5MP rolling shutter, monochrome, LE model
#define IS_SENSOR_UI1485_C          0x002F      // 5MP rolling shutter, color, LE model
#define IS_SENSOR_UI1495_M          0x0040      // 149xLE-M
#define IS_SENSOR_UI1495_C          0x0041      // 149xLE-C

// custom board level designs
#define IS_SENSOR_UI1543_M          0x0032      // SXGA rolling shutter, monochrome, single board
#define IS_SENSOR_UI1543_C          0x0033      // SXGA rolling shutter, color, single board

#define IS_SENSOR_UI1544_M          0x003A      // SXGA rolling shutter, monochrome, single board
#define IS_SENSOR_UI1544_C          0x003B      // SXGA rolling shutter, color, single board
#define IS_SENSOR_UI1543_M_WO       0x003C      // SXGA rolling shutter, color, single board
#define IS_SENSOR_UI1543_C_WO       0x003D      // SXGA rolling shutter, color, single board
#define IS_SENSOR_UI1453_C          0x0035      // UXGA rolling shutter, color, single board
#define IS_SENSOR_UI1463_C          0x0037      // QXGA rolling shutter, color, single board
#define IS_SENSOR_UI1483_C          0x0039      // QSXGA rolling shutter, color, single board

#define IS_SENSOR_UI1463_M_WO       0x0044      // QXGA rolling shutter, monochrome, single board
#define IS_SENSOR_UI1463_C_WO       0x0045      // QXGA rolling shutter, color, single board

#define IS_SENSOR_UI1553_C_WN       0x0047      // UXGA rolling shutter, color, single board
#define IS_SENSOR_UI1483_M_WO       0x0048      // QSXGA rolling shutter, monochrome, single board
#define IS_SENSOR_UI1483_C_WO       0x0049      // QSXGA rolling shutter, color, single board

// CCD Sensors
#define IS_SENSOR_UI223X_M          0x0080      // Sony CCD sensor - XGA monochrome
#define IS_SENSOR_UI223X_C          0x0081      // Sony CCD sensor - XGA color

#define IS_SENSOR_UI241X_M          0x0082      // Sony CCD sensor - VGA monochrome
#define IS_SENSOR_UI241X_C          0x0083      // Sony CCD sensor - VGA color

#define IS_SENSOR_UI234X_M          0x0084      // Sony CCD sensor - SXGA monochrome
#define IS_SENSOR_UI234X_C          0x0085      // Sony CCD sensor - SXGA color

#define IS_SENSOR_UI233X_M          0x0086      // Kodak CCD sensor - 1MP mono
#define IS_SENSOR_UI233X_C          0x0087      // Kodak CCD sensor - 1MP color

#define IS_SENSOR_UI221X_M          0x0088      // Sony CCD sensor - VGA monochrome
#define IS_SENSOR_UI221X_C          0x0089      // Sony CCD sensor - VGA color

#define IS_SENSOR_UI231X_M          0x0090      // Sony CCD sensor - VGA monochrome
#define IS_SENSOR_UI231X_C          0x0091      // Sony CCD sensor - VGA color

#define IS_SENSOR_UI222X_M          0x0092      // Sony CCD sensor - CCIR / PAL monochrome
#define IS_SENSOR_UI222X_C          0x0093      // Sony CCD sensor - CCIR / PAL color

#define IS_SENSOR_UI224X_M          0x0096      // Sony CCD sensor - SXGA monochrome
#define IS_SENSOR_UI224X_C          0x0097      // Sony CCD sensor - SXGA color

#define IS_SENSOR_UI225X_M          0x0098      // Sony CCD sensor - UXGA monochrome
#define IS_SENSOR_UI225X_C          0x0099      // Sony CCD sensor - UXGA color

#define IS_SENSOR_UI214X_M          0x009A      // Sony CCD sensor - SXGA monochrome
#define IS_SENSOR_UI214X_C          0x009B      // Sony CCD sensor - SXGA color

// ----------------------------------------------------------------------------
// error codes
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// common definitions
// ----------------------------------------------------------------------------
#define IS_OFF                              0
#define IS_ON                               1
#define IS_IGNORE_PARAMETER                 -1


// ----------------------------------------------------------------------------
//  device enumeration
// ----------------------------------------------------------------------------
#define IS_USE_DEVICE_ID                    0x8000L
#define IS_ALLOW_STARTER_FW_UPLOAD          0x10000L

// ----------------------------------------------------------------------------
// AutoExit enable/disable
// ----------------------------------------------------------------------------
#define IS_GET_AUTO_EXIT_ENABLED            0x8000
#define IS_DISABLE_AUTO_EXIT                0
#define IS_ENABLE_AUTO_EXIT                 1


// ----------------------------------------------------------------------------
// live/freeze parameters
// ----------------------------------------------------------------------------
#define IS_GET_LIVE                         0x8000

#define IS_WAIT                             0x0001
#define IS_DONT_WAIT                        0x0000
#define IS_FORCE_VIDEO_STOP                 0x4000
#define IS_FORCE_VIDEO_START                0x4000
#define IS_USE_NEXT_MEM                     0x8000


// ----------------------------------------------------------------------------
// video finish constants
// ----------------------------------------------------------------------------
#define IS_VIDEO_NOT_FINISH                 0
#define IS_VIDEO_FINISH                     1


// ----------------------------------------------------------------------------
// bitmap render modes
// ----------------------------------------------------------------------------
#define IS_GET_RENDER_MODE                  0x8000

#define IS_RENDER_DISABLED                  0
#define IS_RENDER_NORMAL                    1
#define IS_RENDER_FIT_TO_WINDOW             2
#define IS_RENDER_DOWNSCALE_1_2             4
#define IS_RENDER_MIRROR_UPDOWN             16
#define IS_RENDER_DOUBLE_HEIGHT             32
#define IS_RENDER_HALF_HEIGHT               64


// ----------------------------------------------------------------------------
// external trigger modes
// ----------------------------------------------------------------------------
#define IS_GET_EXTERNALTRIGGER              0x8000
#define IS_GET_TRIGGER_STATUS               0x8001
#define IS_GET_TRIGGER_MASK                 0x8002
#define IS_GET_TRIGGER_INPUTS               0x8003
#define IS_GET_SUPPORTED_TRIGGER_MODE       0x8004
#define IS_GET_TRIGGER_COUNTER              0x8000

// old defines for compatibility 
#define IS_SET_TRIG_OFF                     0x0000
#define IS_SET_TRIG_HI_LO                   0x0001
#define IS_SET_TRIG_LO_HI                   0x0002
#define IS_SET_TRIG_SOFTWARE                0x0008
#define IS_SET_TRIG_HI_LO_SYNC              0x0010
#define IS_SET_TRIG_LO_HI_SYNC              0x0020

#define IS_SET_TRIG_MASK                    0x0100

// New defines
#define IS_SET_TRIGGER_CONTINUOUS           0x1000
#define IS_SET_TRIGGER_OFF                  IS_SET_TRIG_OFF
#define IS_SET_TRIGGER_HI_LO                (IS_SET_TRIGGER_CONTINUOUS | IS_SET_TRIG_HI_LO) 
#define IS_SET_TRIGGER_LO_HI                (IS_SET_TRIGGER_CONTINUOUS | IS_SET_TRIG_LO_HI) 
#define IS_SET_TRIGGER_SOFTWARE             (IS_SET_TRIGGER_CONTINUOUS | IS_SET_TRIG_SOFTWARE) 
#define IS_SET_TRIGGER_HI_LO_SYNC           IS_SET_TRIG_HI_LO_SYNC
#define IS_SET_TRIGGER_LO_HI_SYNC           IS_SET_TRIG_LO_HI_SYNC


#define IS_GET_TRIGGER_DELAY                0x8000
#define IS_GET_MIN_TRIGGER_DELAY            0x8001
#define IS_GET_MAX_TRIGGER_DELAY            0x8002
#define IS_GET_TRIGGER_DELAY_GRANULARITY    0x8003


// ----------------------------------------------------------------------------
// Timing
// ----------------------------------------------------------------------------
// pixelclock
#define IS_GET_PIXEL_CLOCK                  0x8000
#define IS_GET_DEFAULT_PIXEL_CLK            0x8001
// frame rate
#define IS_GET_FRAMERATE                    0x8000
#define IS_GET_DEFAULT_FRAMERATE            0x8001
// exposure
#define IS_GET_EXPOSURE_TIME                0x8000
#define IS_GET_DEFAULT_EXPOSURE             0x8001

// ----------------------------------------------------------------------------
// Gain definitions
// ----------------------------------------------------------------------------
#define IS_GET_MASTER_GAIN                  0x8000
#define IS_GET_RED_GAIN                     0x8001
#define IS_GET_GREEN_GAIN                   0x8002
#define IS_GET_BLUE_GAIN                    0x8003
#define IS_GET_DEFAULT_MASTER               0x8004
#define IS_GET_DEFAULT_RED                  0x8005
#define IS_GET_DEFAULT_GREEN                0x8006
#define IS_GET_DEFAULT_BLUE                 0x8007
#define IS_GET_GAINBOOST                    0x8008
#define IS_SET_GAINBOOST_ON                 0x0001
#define IS_SET_GAINBOOST_OFF                0x0000
#define IS_GET_SUPPORTED_GAINBOOST          0x0002
#define IS_MIN_GAIN                         0
#define IS_MAX_GAIN                         100


// ----------------------------------------------------------------------------
// Gain factor definitions
// ----------------------------------------------------------------------------
#define IS_GET_MASTER_GAIN_FACTOR           0x8000
#define IS_GET_RED_GAIN_FACTOR              0x8001
#define IS_GET_GREEN_GAIN_FACTOR            0x8002
#define IS_GET_BLUE_GAIN_FACTOR             0x8003
#define IS_SET_MASTER_GAIN_FACTOR           0x8004
#define IS_SET_RED_GAIN_FACTOR              0x8005
#define IS_SET_GREEN_GAIN_FACTOR            0x8006
#define IS_SET_BLUE_GAIN_FACTOR             0x8007
#define IS_GET_DEFAULT_MASTER_GAIN_FACTOR   0x8008
#define IS_GET_DEFAULT_RED_GAIN_FACTOR      0x8009
#define IS_GET_DEFAULT_GREEN_GAIN_FACTOR    0x800a
#define IS_GET_DEFAULT_BLUE_GAIN_FACTOR     0x800b
#define IS_INQUIRE_MASTER_GAIN_FACTOR       0x800c
#define IS_INQUIRE_RED_GAIN_FACTOR          0x800d
#define IS_INQUIRE_GREEN_GAIN_FACTOR        0x800e
#define IS_INQUIRE_BLUE_GAIN_FACTOR         0x800f


// ----------------------------------------------------------------------------
// Global Shutter definitions
// ----------------------------------------------------------------------------
#define IS_SET_GLOBAL_SHUTTER_ON            0x0001
#define IS_SET_GLOBAL_SHUTTER_OFF           0x0000
#define IS_GET_GLOBAL_SHUTTER               0x0010
#define IS_GET_SUPPORTED_GLOBAL_SHUTTER     0x0020


// ----------------------------------------------------------------------------
// Black level definitions
// ----------------------------------------------------------------------------
#define IS_GET_BL_COMPENSATION              0x8000
#define IS_GET_BL_OFFSET                    0x8001
#define IS_GET_BL_DEFAULT_MODE              0x8002
#define IS_GET_BL_DEFAULT_OFFSET            0x8003
#define IS_GET_BL_SUPPORTED_MODE            0x8004

#define IS_BL_COMPENSATION_DISABLE          0
#define IS_BL_COMPENSATION_ENABLE           1
#define IS_BL_COMPENSATION_OFFSET           32

#define IS_MIN_BL_OFFSET                    0
#define IS_MAX_BL_OFFSET                    255

// ----------------------------------------------------------------------------
// hardware gamma definitions
// ----------------------------------------------------------------------------
#define IS_GET_HW_GAMMA                     0x8000
#define IS_GET_HW_SUPPORTED_GAMMA           0x8001

#define IS_SET_HW_GAMMA_OFF                 0x0000
#define IS_SET_HW_GAMMA_ON                  0x0001

// ----------------------------------------------------------------------------
// camera LUT
// ----------------------------------------------------------------------------
#define IS_ENABLE_CAMERA_LUT                0x0001
#define IS_SET_CAMERA_LUT_VALUES            0x0002
#define IS_ENABLE_RGB_GRAYSCALE             0x0004
#define IS_GET_CAMERA_LUT_USER              0x0008
#define IS_GET_CAMERA_LUT_COMPLETE          0x0010

// ----------------------------------------------------------------------------
// camera LUT presets
// ----------------------------------------------------------------------------
#define IS_CAMERA_LUT_IDENTITY              0x00000100
#define IS_CAMERA_LUT_NEGATIV               0x00000200
#define IS_CAMERA_LUT_GLOW1                 0x00000400
#define IS_CAMERA_LUT_GLOW2                 0x00000800
#define IS_CAMERA_LUT_ASTRO1                0x00001000
#define IS_CAMERA_LUT_RAINBOW1              0x00002000
#define IS_CAMERA_LUT_MAP1                  0x00004000
#define IS_CAMERA_LUT_COLD_HOT              0x00008000
#define IS_CAMERA_LUT_SEPIC                 0x00010000
#define IS_CAMERA_LUT_ONLY_RED              0x00020000
#define IS_CAMERA_LUT_ONLY_GREEN            0x00040000
#define IS_CAMERA_LUT_ONLY_BLUE             0x00080000

#define IS_CAMERA_LUT_64                    64
#define IS_CAMERA_LUT_128                   128


// ----------------------------------------------------------------------------
// image parameters
// ----------------------------------------------------------------------------
// brightness
#define IS_GET_BRIGHTNESS                   0x8000
#define IS_MIN_BRIGHTNESS                   0
#define IS_MAX_BRIGHTNESS                   255
#define IS_DEFAULT_BRIGHTNESS               -1
// contrast
#define IS_GET_CONTRAST                     0x8000
#define IS_MIN_CONTRAST                     0
#define IS_MAX_CONTRAST                     511
#define IS_DEFAULT_CONTRAST                 -1
// gamma
#define IS_GET_GAMMA                        0x8000
#define IS_MIN_GAMMA                        1
#define IS_MAX_GAMMA                        1000
#define IS_DEFAULT_GAMMA                    -1
// saturation   (Falcon)
#define IS_GET_SATURATION_U                 0x8000
#define IS_MIN_SATURATION_U                 0
#define IS_MAX_SATURATION_U                 200
#define IS_DEFAULT_SATURATION_U             100
#define IS_GET_SATURATION_V                 0x8001
#define IS_MIN_SATURATION_V                 0
#define IS_MAX_SATURATION_V                 200
#define IS_DEFAULT_SATURATION_V             100
// hue  (Falcon)
#define IS_GET_HUE                          0x8000
#define IS_MIN_HUE                          0
#define IS_MAX_HUE                          255
#define IS_DEFAULT_HUE                      128


// ----------------------------------------------------------------------------
// Image position and size
// ----------------------------------------------------------------------------
#define IS_GET_IMAGE_SIZE_X                 0x8000
#define IS_GET_IMAGE_SIZE_Y                 0x8001
#define IS_GET_IMAGE_SIZE_X_INC             0x8002
#define IS_GET_IMAGE_SIZE_Y_INC             0x8003
#define IS_GET_IMAGE_SIZE_X_MIN             0x8004
#define IS_GET_IMAGE_SIZE_Y_MIN             0x8005
#define IS_GET_IMAGE_SIZE_X_MAX             0x8006
#define IS_GET_IMAGE_SIZE_Y_MAX             0x8007

#define IS_GET_IMAGE_POS_X                  0x8001
#define IS_GET_IMAGE_POS_Y                  0x8002
#define IS_GET_IMAGE_POS_X_ABS              0xC001
#define IS_GET_IMAGE_POS_Y_ABS              0xC002
#define IS_GET_IMAGE_POS_X_INC              0xC003
#define IS_GET_IMAGE_POS_Y_INC              0xC004
#define IS_GET_IMAGE_POS_X_MIN              0xC005
#define IS_GET_IMAGE_POS_Y_MIN              0xC006
#define IS_GET_IMAGE_POS_X_MAX              0xC007
#define IS_GET_IMAGE_POS_Y_MAX              0xC008

#define IS_SET_IMAGE_POS_X_ABS              0x00010000
#define IS_SET_IMAGE_POS_Y_ABS              0x00010000

// Compatibility
#define IS_SET_IMAGEPOS_X_ABS               0x8000
#define IS_SET_IMAGEPOS_Y_ABS               0x8000


// ----------------------------------------------------------------------------
// ROP effect constants
// ----------------------------------------------------------------------------
#define IS_GET_ROP_EFFECT                   0x8000
#define IS_GET_SUPPORTED_ROP_EFFECT         0x8001

#define IS_SET_ROP_NONE                     0
#define IS_SET_ROP_MIRROR_UPDOWN            8
#define IS_SET_ROP_MIRROR_UPDOWN_ODD        16
#define IS_SET_ROP_MIRROR_UPDOWN_EVEN       32
#define IS_SET_ROP_MIRROR_LEFTRIGHT         64


// ----------------------------------------------------------------------------
// Subsampling
// ----------------------------------------------------------------------------
#define IS_GET_SUBSAMPLING                      0x8000
#define IS_GET_SUPPORTED_SUBSAMPLING            0x8001
#define IS_GET_SUBSAMPLING_TYPE                 0x8002
#define IS_GET_SUBSAMPLING_FACTOR_HORIZONTAL    0x8004
#define IS_GET_SUBSAMPLING_FACTOR_VERTICAL      0x8008

#define IS_SUBSAMPLING_DISABLE                  0x00

#define IS_SUBSAMPLING_2X_VERTICAL              0x0001
#define IS_SUBSAMPLING_2X_HORIZONTAL            0x0002
#define IS_SUBSAMPLING_4X_VERTICAL              0x0004
#define IS_SUBSAMPLING_4X_HORIZONTAL            0x0008
#define IS_SUBSAMPLING_3X_VERTICAL              0x0010
#define IS_SUBSAMPLING_3X_HORIZONTAL            0x0020
#define IS_SUBSAMPLING_5X_VERTICAL              0x0040
#define IS_SUBSAMPLING_5X_HORIZONTAL            0x0080
#define IS_SUBSAMPLING_6X_VERTICAL              0x0100
#define IS_SUBSAMPLING_6X_HORIZONTAL            0x0200
#define IS_SUBSAMPLING_8X_VERTICAL              0x0400
#define IS_SUBSAMPLING_8X_HORIZONTAL            0x0800
#define IS_SUBSAMPLING_16X_VERTICAL             0x1000
#define IS_SUBSAMPLING_16X_HORIZONTAL           0x2000

#define IS_SUBSAMPLING_COLOR                    0x01
#define IS_SUBSAMPLING_MONO                     0x02

#define IS_SUBSAMPLING_MASK_VERTICAL            (IS_SUBSAMPLING_2X_VERTICAL | IS_SUBSAMPLING_4X_VERTICAL | IS_SUBSAMPLING_3X_VERTICAL | IS_SUBSAMPLING_5X_VERTICAL | IS_SUBSAMPLING_6X_VERTICAL | IS_SUBSAMPLING_8X_VERTICAL | IS_SUBSAMPLING_16X_VERTICAL)
#define IS_SUBSAMPLING_MASK_HORIZONTAL          (IS_SUBSAMPLING_2X_HORIZONTAL | IS_SUBSAMPLING_4X_HORIZONTAL | IS_SUBSAMPLING_3X_HORIZONTAL | IS_SUBSAMPLING_5X_HORIZONTAL | IS_SUBSAMPLING_6X_HORIZONTAL | IS_SUBSAMPLING_8X_HORIZONTAL | IS_SUBSAMPLING_16X_HORIZONTAL)

// Compatibility
#define IS_SUBSAMPLING_VERT                     IS_SUBSAMPLING_2X_VERTICAL
#define IS_SUBSAMPLING_HOR                      IS_SUBSAMPLING_2X_HORIZONTAL


// ----------------------------------------------------------------------------
// Binning
// ----------------------------------------------------------------------------
#define IS_GET_BINNING                      0x8000
#define IS_GET_SUPPORTED_BINNING            0x8001
#define IS_GET_BINNING_TYPE                 0x8002
#define IS_GET_BINNING_FACTOR_HORIZONTAL    0x8004
#define IS_GET_BINNING_FACTOR_VERTICAL      0x8008

#define IS_BINNING_DISABLE                  0x00

#define IS_BINNING_2X_VERTICAL              0x0001
#define IS_BINNING_2X_HORIZONTAL            0x0002
#define IS_BINNING_4X_VERTICAL              0x0004
#define IS_BINNING_4X_HORIZONTAL            0x0008
#define IS_BINNING_3X_VERTICAL              0x0010
#define IS_BINNING_3X_HORIZONTAL            0x0020
#define IS_BINNING_5X_VERTICAL              0x0040
#define IS_BINNING_5X_HORIZONTAL            0x0080
#define IS_BINNING_6X_VERTICAL              0x0100
#define IS_BINNING_6X_HORIZONTAL            0x0200
#define IS_BINNING_8X_VERTICAL              0x0400
#define IS_BINNING_8X_HORIZONTAL            0x0800
#define IS_BINNING_16X_VERTICAL             0x1000
#define IS_BINNING_16X_HORIZONTAL           0x2000

#define IS_BINNING_COLOR                    0x01
#define IS_BINNING_MONO                     0x02

#define IS_BINNING_MASK_VERTICAL            (IS_BINNING_2X_VERTICAL | IS_BINNING_3X_VERTICAL | IS_BINNING_4X_VERTICAL | IS_BINNING_5X_VERTICAL | IS_BINNING_6X_VERTICAL | IS_BINNING_8X_VERTICAL | IS_BINNING_16X_VERTICAL)
#define IS_BINNING_MASK_HORIZONTAL          (IS_BINNING_2X_HORIZONTAL | IS_BINNING_3X_HORIZONTAL | IS_BINNING_4X_HORIZONTAL | IS_BINNING_5X_HORIZONTAL | IS_BINNING_6X_HORIZONTAL | IS_BINNING_8X_HORIZONTAL | IS_BINNING_16X_HORIZONTAL)

// Compatibility
#define IS_BINNING_VERT                     IS_BINNING_2X_VERTICAL
#define IS_BINNING_HOR                      IS_BINNING_2X_HORIZONTAL

// ----------------------------------------------------------------------------
// Auto Control Parameter
// ----------------------------------------------------------------------------
#define IS_SET_ENABLE_AUTO_GAIN             0x8800
#define IS_GET_ENABLE_AUTO_GAIN             0x8801
#define IS_SET_ENABLE_AUTO_SHUTTER          0x8802
#define IS_GET_ENABLE_AUTO_SHUTTER          0x8803
#define IS_SET_ENABLE_AUTO_WHITEBALANCE     0x8804
#define IS_GET_ENABLE_AUTO_WHITEBALANCE     0x8805
#define IS_SET_ENABLE_AUTO_FRAMERATE        0x8806
#define IS_GET_ENABLE_AUTO_FRAMERATE        0x8807
#define IS_SET_ENABLE_AUTO_SENSOR_GAIN		0x8808
#define IS_GET_ENABLE_AUTO_SENSOR_GAIN		0x8809
#define IS_SET_ENABLE_AUTO_SENSOR_SHUTTER	0x8810
#define IS_GET_ENABLE_AUTO_SENSOR_SHUTTER   0x8811
#define IS_SET_ENABLE_AUTO_SENSOR_GAIN_SHUTTER	0x8812
#define IS_GET_ENABLE_AUTO_SENSOR_GAIN_SHUTTER  0x8813
#define IS_SET_ENABLE_AUTO_SENSOR_FRAMERATE     0x8814
#define IS_GET_ENABLE_AUTO_SENSOR_FRAMERATE     0x8815

#define IS_SET_AUTO_REFERENCE               0x8000
#define IS_GET_AUTO_REFERENCE               0x8001
#define IS_SET_AUTO_GAIN_MAX                0x8002
#define IS_GET_AUTO_GAIN_MAX                0x8003
#define IS_SET_AUTO_SHUTTER_MAX             0x8004
#define IS_GET_AUTO_SHUTTER_MAX             0x8005
#define IS_SET_AUTO_SPEED                   0x8006
#define IS_GET_AUTO_SPEED                   0x8007
#define IS_SET_AUTO_WB_OFFSET               0x8008
#define IS_GET_AUTO_WB_OFFSET               0x8009
#define IS_SET_AUTO_WB_GAIN_RANGE           0x800A
#define IS_GET_AUTO_WB_GAIN_RANGE           0x800B
#define IS_SET_AUTO_WB_SPEED                0x800C
#define IS_GET_AUTO_WB_SPEED                0x800D
#define IS_SET_AUTO_WB_ONCE                 0x800E
#define IS_GET_AUTO_WB_ONCE                 0x800F
#define IS_SET_AUTO_BRIGHTNESS_ONCE         0x8010
#define IS_GET_AUTO_BRIGHTNESS_ONCE         0x8011
#define IS_SET_AUTO_HYSTERESIS				0x8012
#define IS_GET_AUTO_HYSTERESIS				0x8013
#define IS_GET_AUTO_HYSTERESIS_RANGE		0x8014
#define IS_SET_AUTO_WB_HYSTERESIS			0x8015
#define IS_GET_AUTO_WB_HYSTERESIS			0x8016
#define IS_GET_AUTO_WB_HYSTERESIS_RANGE		0x8017
#define IS_SET_AUTO_SKIPFRAMES				0x8018
#define IS_GET_AUTO_SKIPFRAMES				0x8019
#define IS_GET_AUTO_SKIPFRAMES_RANGE		0x801A
#define IS_SET_AUTO_WB_SKIPFRAMES			0x801B
#define IS_GET_AUTO_WB_SKIPFRAMES			0x801C
#define IS_GET_AUTO_WB_SKIPFRAMES_RANGE		0x801D

// ----------------------------------------------------------------------------
// Auto Control definitions
// ----------------------------------------------------------------------------
#define IS_MIN_AUTO_BRIGHT_REFERENCE          0
#define IS_MAX_AUTO_BRIGHT_REFERENCE        255
#define IS_DEFAULT_AUTO_BRIGHT_REFERENCE    128
#define IS_MIN_AUTO_SPEED                     0
#define IS_MAX_AUTO_SPEED                   100
#define IS_DEFAULT_AUTO_SPEED                50

#define IS_DEFAULT_AUTO_WB_OFFSET             0
#define IS_MIN_AUTO_WB_OFFSET               -50
#define IS_MAX_AUTO_WB_OFFSET                50
#define IS_DEFAULT_AUTO_WB_SPEED             50
#define IS_MIN_AUTO_WB_SPEED                  0
#define IS_MAX_AUTO_WB_SPEED                100
#define IS_MIN_AUTO_WB_REFERENCE              0
#define IS_MAX_AUTO_WB_REFERENCE            255


// ----------------------------------------------------------------------------
// AOI types to set/get
// ----------------------------------------------------------------------------
#define IS_SET_AUTO_BRIGHT_AOI              0x8000
#define IS_GET_AUTO_BRIGHT_AOI              0x8001
#define IS_SET_IMAGE_AOI                    0x8002
#define IS_GET_IMAGE_AOI                    0x8003
#define IS_SET_AUTO_WB_AOI                  0x8004
#define IS_GET_AUTO_WB_AOI                  0x8005


// ----------------------------------------------------------------------------
// color modes
// ----------------------------------------------------------------------------
#define IS_GET_COLOR_MODE                   0x8000

#define IS_SET_CM_RGB32                     0
#define IS_SET_CM_RGB24                     1
#define IS_SET_CM_RGB16                     2
#define IS_SET_CM_RGB15                     3
#define IS_SET_CM_Y8                        6
#define IS_SET_CM_RGB8                      7
#define IS_SET_CM_BAYER                     11
#define IS_SET_CM_UYVY                      12
#define IS_SET_CM_UYVY_MONO                 13
#define IS_SET_CM_UYVY_BAYER                14
#define IS_SET_CM_CBYCRY                    23

#define IS_SET_CM_RGBY                      24
#define IS_SET_CM_RGB30                     25
#define IS_SET_CM_Y12                       26
#define IS_SET_CM_BAYER12                   27
#define IS_SET_CM_Y16                       28
#define IS_SET_CM_BAYER16                   29

#define IS_CM_MODE_MASK                     0x007F

// planar vs packed format
#define IS_CM_FORMAT_PACKED                 0x0000
#define IS_CM_FORMAT_PLANAR                 0x2000
#define IS_CM_FORMAT_MASK                   0x2000

// BGR vs. RGB order
#define IS_CM_ORDER_BGR                     0x0000
#define IS_CM_ORDER_RGB                     0x0080
#define IS_CM_ORDER_MASK                    0x0080 


// define compliant color format names
#define IS_CM_MONO8                 IS_SET_CM_Y8                                            // occupies 8 Bit
#define IS_CM_MONO12                IS_SET_CM_Y12                                           // occupies 16 Bit
#define IS_CM_MONO16                IS_SET_CM_Y16                                           // occupies 16 Bit

#define IS_CM_BAYER_RG8             IS_SET_CM_BAYER                                         // occupies 8 Bit
#define IS_CM_BAYER_RG12            IS_SET_CM_BAYER12                                       // occupies 16 Bit
#define IS_CM_BAYER_RG16            IS_SET_CM_BAYER16                                       // occupies 16 Bit

#define IS_CM_BGR555_PACKED         (IS_SET_CM_RGB15 | IS_CM_ORDER_BGR | IS_CM_FORMAT_PACKED) // occupies 16 Bit
#define IS_CM_BGR565_PACKED         (IS_SET_CM_RGB16 | IS_CM_ORDER_BGR | IS_CM_FORMAT_PACKED) // occupies 16 Bit 

#define IS_CM_RGB8_PACKED           (IS_SET_CM_RGB24 | IS_CM_ORDER_RGB | IS_CM_FORMAT_PACKED) // occupies 24 Bit
#define IS_CM_BGR8_PACKED           (IS_SET_CM_RGB24 | IS_CM_ORDER_BGR | IS_CM_FORMAT_PACKED) // occupies 24 Bit  
#define IS_CM_RGBA8_PACKED          (IS_SET_CM_RGB32 | IS_CM_ORDER_RGB | IS_CM_FORMAT_PACKED) // occupies 32 Bit
#define IS_CM_BGRA8_PACKED          (IS_SET_CM_RGB32 | IS_CM_ORDER_BGR | IS_CM_FORMAT_PACKED) // occupies 32 Bit
#define IS_CM_RGBY8_PACKED          (IS_SET_CM_RGBY  | IS_CM_ORDER_RGB | IS_CM_FORMAT_PACKED) // occupies 32 Bit
#define IS_CM_BGRY8_PACKED          (IS_SET_CM_RGBY  | IS_CM_ORDER_BGR | IS_CM_FORMAT_PACKED) // occupies 32 Bit
#define IS_CM_RGB10V2_PACKED        (IS_SET_CM_RGB30 | IS_CM_ORDER_RGB | IS_CM_FORMAT_PACKED) // occupies 32 Bit
#define IS_CM_BGR10V2_PACKED        (IS_SET_CM_RGB30 | IS_CM_ORDER_BGR | IS_CM_FORMAT_PACKED) // occupies 32 Bit

#define IS_CM_YUV422_PACKED         //no compliant version      
#define IS_CM_UYVY_PACKED           (IS_SET_CM_UYVY | IS_CM_FORMAT_PACKED)                    // occupies 16 Bit
#define IS_CM_UYVY_MONO_PACKED      (IS_SET_CM_UYVY_MONO | IS_CM_FORMAT_PACKED)
#define IS_CM_UYVY_BAYER_PACKED     (IS_SET_CM_UYVY_BAYER | IS_CM_FORMAT_PACKED)
#define IS_CM_CBYCRY_PACKED         (IS_SET_CM_CBYCRY | IS_CM_FORMAT_PACKED)                  // occupies 16 Bit

#define IS_CM_RGB8_PLANAR           //no compliant version
#define IS_CM_RGB12_PLANAR          //no compliant version
#define IS_CM_RGB16_PLANAR          //no compliant version


#define IS_CM_ALL_POSSIBLE                  0xFFFF

// ----------------------------------------------------------------------------
// Hotpixel correction
// ----------------------------------------------------------------------------
#define IS_GET_BPC_MODE                      0x8000
#define IS_GET_BPC_THRESHOLD                 0x8001
#define IS_GET_BPC_SUPPORTED_MODE            0x8002

#define IS_BPC_DISABLE                       0
#define IS_BPC_ENABLE_LEVEL_1                1
#define IS_BPC_ENABLE_LEVEL_2                2
#define IS_BPC_ENABLE_USER                   4
#define IS_BPC_ENABLE_SOFTWARE          IS_BPC_ENABLE_LEVEL_2
#define IS_BPC_ENABLE_HARDWARE          IS_BPC_ENABLE_LEVEL_1

#define IS_SET_BADPIXEL_LIST                 0x01
#define IS_GET_BADPIXEL_LIST                 0x02
#define IS_GET_LIST_SIZE                     0x03


// ----------------------------------------------------------------------------
// color correction definitions
// ----------------------------------------------------------------------------
#define IS_GET_CCOR_MODE                    0x8000
#define IS_GET_SUPPORTED_CCOR_MODE          0x8001
#define IS_GET_DEFAULT_CCOR_MODE            0x8002
#define IS_GET_CCOR_FACTOR                  0x8003
#define IS_GET_CCOR_FACTOR_MIN              0x8004
#define IS_GET_CCOR_FACTOR_MAX              0x8005
#define IS_GET_CCOR_FACTOR_DEFAULT          0x8006

#define IS_CCOR_DISABLE                     0x0000
#define IS_CCOR_ENABLE                      0x0001
#define IS_CCOR_ENABLE_NORMAL           IS_CCOR_ENABLE
#define IS_CCOR_ENABLE_BG40_ENHANCED        0x0002
#define IS_CCOR_ENABLE_HQ_ENHANCED          0x0004
#define IS_CCOR_SET_IR_AUTOMATIC            0x0080
#define IS_CCOR_FACTOR                      0x0100

#define IS_CCOR_ENABLE_MASK             (IS_CCOR_ENABLE_NORMAL | IS_CCOR_ENABLE_BG40_ENHANCED | IS_CCOR_ENABLE_HQ_ENHANCED)


// ----------------------------------------------------------------------------
// bayer algorithm modes
// ----------------------------------------------------------------------------
#define IS_GET_BAYER_CV_MODE                0x8000

#define IS_SET_BAYER_CV_NORMAL              0x0000
#define IS_SET_BAYER_CV_BETTER              0x0001
#define IS_SET_BAYER_CV_BEST                0x0002


// ----------------------------------------------------------------------------
// color converter modes
// ----------------------------------------------------------------------------
#define IS_CONV_MODE_NONE                   0x0000
#define IS_CONV_MODE_SOFTWARE               0x0001
#define IS_CONV_MODE_SOFTWARE_3X3           0x0002
#define IS_CONV_MODE_SOFTWARE_5X5           0x0004
#define IS_CONV_MODE_HARDWARE_3X3           0x0008


// ----------------------------------------------------------------------------
// Edge enhancement
// ----------------------------------------------------------------------------
#define IS_GET_EDGE_ENHANCEMENT             0x8000

#define IS_EDGE_EN_DISABLE                  0
#define IS_EDGE_EN_STRONG                   1
#define IS_EDGE_EN_WEAK                     2


// ----------------------------------------------------------------------------
// white balance modes
// ----------------------------------------------------------------------------
#define IS_GET_WB_MODE                      0x8000

#define IS_SET_WB_DISABLE                   0x0000
#define IS_SET_WB_USER                      0x0001
#define IS_SET_WB_AUTO_ENABLE               0x0002
#define IS_SET_WB_AUTO_ENABLE_ONCE          0x0004

#define IS_SET_WB_DAYLIGHT_65               0x0101
#define IS_SET_WB_COOL_WHITE                0x0102
#define IS_SET_WB_U30                       0x0103
#define IS_SET_WB_ILLUMINANT_A              0x0104
#define IS_SET_WB_HORIZON                   0x0105


// ----------------------------------------------------------------------------
// flash strobe constants
// ----------------------------------------------------------------------------
#define IS_GET_FLASHSTROBE_MODE             0x8000
#define IS_GET_FLASHSTROBE_LINE             0x8001
#define IS_GET_SUPPORTED_FLASH_IO_PORTS     0x8002

#define IS_SET_FLASH_OFF                    0
#define IS_SET_FLASH_ON                     1
#define IS_SET_FLASH_LO_ACTIVE          IS_SET_FLASH_ON
#define IS_SET_FLASH_HI_ACTIVE              2
#define IS_SET_FLASH_HIGH                   3
#define IS_SET_FLASH_LOW                    4
#define IS_SET_FLASH_LO_ACTIVE_FREERUN      5
#define IS_SET_FLASH_HI_ACTIVE_FREERUN      6
#define IS_SET_FLASH_IO_1                   0x0010
#define IS_SET_FLASH_IO_2                   0x0020
#define IS_SET_FLASH_IO_3                   0x0040
#define IS_SET_FLASH_IO_4                   0x0080
#define IS_FLASH_IO_PORT_MASK           (IS_SET_FLASH_IO_1 | IS_SET_FLASH_IO_2 | IS_SET_FLASH_IO_3 | IS_SET_FLASH_IO_4)  

#define IS_GET_FLASH_DELAY                  -1
#define IS_GET_FLASH_DURATION               -2
#define IS_GET_MAX_FLASH_DELAY              -3
#define IS_GET_MAX_FLASH_DURATION           -4
#define IS_GET_MIN_FLASH_DELAY              -5
#define IS_GET_MIN_FLASH_DURATION           -6
#define IS_GET_FLASH_DELAY_GRANULARITY      -7
#define IS_GET_FLASH_DURATION_GRANULARITY   -8

// ----------------------------------------------------------------------------
// Digital IO constants
// ----------------------------------------------------------------------------
#define IS_GET_IO                           0x8000
#define IS_GET_IO_MASK                      0x8000
#define IS_GET_INPUT_MASK                   0x8001
#define IS_GET_OUTPUT_MASK                  0x8002
#define IS_GET_SUPPORTED_IO_PORTS           0x8004


// ----------------------------------------------------------------------------
// EEPROM defines
// ----------------------------------------------------------------------------
#define IS_EEPROM_MIN_USER_ADDRESS          0
#define IS_EEPROM_MAX_USER_ADDRESS          63
#define IS_EEPROM_MAX_USER_SPACE            64


// ----------------------------------------------------------------------------
// error report modes
// ----------------------------------------------------------------------------
#define IS_GET_ERR_REP_MODE                 0x8000
#define IS_ENABLE_ERR_REP                   1
#define IS_DISABLE_ERR_REP                  0


// ----------------------------------------------------------------------------
// display mode selectors
// ----------------------------------------------------------------------------
#define IS_GET_DISPLAY_MODE                 0x8000
#define IS_GET_DISPLAY_SIZE_X               0x8000
#define IS_GET_DISPLAY_SIZE_Y               0x8001
#define IS_GET_DISPLAY_POS_X                0x8000
#define IS_GET_DISPLAY_POS_Y                0x8001

#define IS_SET_DM_DIB                       1
#define IS_SET_DM_DIRECTDRAW                2
#define IS_SET_DM_DIRECT3D                  4
#define IS_SET_DM_ALLOW_SYSMEM              0x40
#define IS_SET_DM_ALLOW_PRIMARY             0x80

// -- overlay display mode ---
#define IS_GET_DD_OVERLAY_SCALE             0x8000

#define IS_SET_DM_ALLOW_OVERLAY             0x100
#define IS_SET_DM_ALLOW_SCALING             0x200
#define IS_SET_DM_ALLOW_FIELDSKIP           0x400
#define IS_SET_DM_MONO                      0x800
#define IS_SET_DM_BAYER                     0x1000
#define IS_SET_DM_YCBCR                     0x4000

// -- backbuffer display mode ---
#define IS_SET_DM_BACKBUFFER                0x2000


// ----------------------------------------------------------------------------
// DirectRenderer commands
// ----------------------------------------------------------------------------
#define DR_GET_OVERLAY_DC                       1
#define DR_GET_MAX_OVERLAY_SIZE                 2
#define DR_GET_OVERLAY_KEY_COLOR                3
#define DR_RELEASE_OVERLAY_DC                   4
#define DR_SHOW_OVERLAY                         5         
#define DR_HIDE_OVERLAY                         6               
#define DR_SET_OVERLAY_SIZE                     7                       
#define DR_SET_OVERLAY_POSITION                 8    
#define DR_SET_OVERLAY_KEY_COLOR                9 
#define DR_SET_HWND                             10 
#define DR_ENABLE_SCALING                       11
#define DR_DISABLE_SCALING                      12
#define DR_CLEAR_OVERLAY                        13
#define DR_ENABLE_SEMI_TRANSPARENT_OVERLAY      14
#define DR_DISABLE_SEMI_TRANSPARENT_OVERLAY     15
#define DR_CHECK_COMPATIBILITY                  16
#define DR_SET_VSYNC_OFF                        17
#define DR_SET_VSYNC_AUTO                       18
#define DR_SET_USER_SYNC                        19
#define DR_GET_USER_SYNC_POSITION_RANGE         20
#define DR_LOAD_OVERLAY_FROM_FILE               21
#define DR_STEAL_NEXT_FRAME                     22
#define DR_SET_STEAL_FORMAT                     23
#define DR_GET_STEAL_FORMAT                     24
#define DR_ENABLE_IMAGE_SCALING                 25
#define DR_GET_OVERLAY_SIZE                     26

// ----------------------------------------------------------------------------
// DirectDraw keying color constants
// ----------------------------------------------------------------------------
#define IS_GET_KC_RED                       0x8000
#define IS_GET_KC_GREEN                     0x8001
#define IS_GET_KC_BLUE                      0x8002
#define IS_GET_KC_RGB                       0x8003
#define IS_GET_KC_INDEX                     0x8004
#define IS_GET_KEYOFFSET_X                  0x8000
#define IS_GET_KEYOFFSET_Y                  0x8001

// RGB-triple for default key-color in 15,16,24,32 bit mode
#define IS_SET_KC_DEFAULT                   0xFF00FF   // 0xbbggrr
// color index for default key-color in 8bit palette mode
#define IS_SET_KC_DEFAULT_8                 253


// ----------------------------------------------------------------------------
// Memoryboard
// ----------------------------------------------------------------------------
#define IS_MEMORY_GET_COUNT                 0x8000
#define IS_MEMORY_GET_DELAY                 0x8001
#define IS_MEMORY_MODE_DISABLE              0x0000
#define IS_MEMORY_USE_TRIGGER               0xFFFF


// ----------------------------------------------------------------------------
// Test image modes
// ----------------------------------------------------------------------------
#define IS_GET_TEST_IMAGE                   0x8000

#define IS_SET_TEST_IMAGE_DISABLED          0x0000
#define IS_SET_TEST_IMAGE_MEMORY_1          0x0001
#define IS_SET_TEST_IMAGE_MEMORY_2          0x0002
#define IS_SET_TEST_IMAGE_MEMORY_3          0x0003


// ----------------------------------------------------------------------------
// Led settings
// ----------------------------------------------------------------------------
#define IS_SET_LED_OFF                      0
#define IS_SET_LED_ON                       1
#define IS_SET_LED_TOGGLE                   2
#define IS_GET_LED                          0x8000


// ----------------------------------------------------------------------------
// save options
// ----------------------------------------------------------------------------
#define IS_SAVE_USE_ACTUAL_IMAGE_SIZE       0x00010000

// ----------------------------------------------------------------------------
// renumeration modes
// ----------------------------------------------------------------------------
#define IS_RENUM_BY_CAMERA                  0
#define IS_RENUM_BY_HOST                    1

// ----------------------------------------------------------------------------
// event constants
// ----------------------------------------------------------------------------
#define IS_SET_EVENT_ODD                    0
#define IS_SET_EVENT_EVEN                   1
#define IS_SET_EVENT_FRAME                  2
#define IS_SET_EVENT_EXTTRIG                3
#define IS_SET_EVENT_VSYNC                  4
#define IS_SET_EVENT_SEQ                    5
#define IS_SET_EVENT_STEAL                  6
#define IS_SET_EVENT_VPRES                  7
#define IS_SET_EVENT_TRANSFER_FAILED        8
#define IS_SET_EVENT_DEVICE_RECONNECTED     9
#define IS_SET_EVENT_MEMORY_MODE_FINISH     10
#define IS_SET_EVENT_FRAME_RECEIVED         11
#define IS_SET_EVENT_WB_FINISHED            12
#define IS_SET_EVENT_AUTOBRIGHTNESS_FINISHED 13

#define IS_SET_EVENT_REMOVE                 128
#define IS_SET_EVENT_REMOVAL                129
#define IS_SET_EVENT_NEW_DEVICE             130
#define IS_SET_EVENT_STATUS_CHANGED         131


// ----------------------------------------------------------------------------
// Window message defines
// ----------------------------------------------------------------------------
#define IS_UEYE_MESSAGE                     (WM_USER + 0x0100) 
  #define IS_FRAME                          0x0000
  #define IS_SEQUENCE                       0x0001
  #define IS_TRIGGER                        0x0002
  #define IS_TRANSFER_FAILED                0x0003
  #define IS_DEVICE_RECONNECTED             0x0004
  #define IS_MEMORY_MODE_FINISH             0x0005
  #define IS_FRAME_RECEIVED                 0x0006
  #define IS_GENERIC_ERROR                  0x0007
  #define IS_STEAL_VIDEO                    0x0008
  #define IS_WB_FINISHED                    0x0009
  #define IS_AUTOBRIGHTNESS_FINISHED        0x000A

  #define IS_DEVICE_REMOVED                 0x1000
  #define IS_DEVICE_REMOVAL                 0x1001
  #define IS_NEW_DEVICE                     0x1002
  #define IS_DEVICE_STATUS_CHANGED          0x1003


// ----------------------------------------------------------------------------
// camera id constants
// ----------------------------------------------------------------------------
#define IS_GET_CAMERA_ID                    0x8000


// ----------------------------------------------------------------------------
// camera info constants
// ----------------------------------------------------------------------------
#define IS_GET_STATUS                       0x8000

#define IS_EXT_TRIGGER_EVENT_CNT            0
#define IS_FIFO_OVR_CNT                     1
#define IS_SEQUENCE_CNT                     2
#define IS_LAST_FRAME_FIFO_OVR              3
#define IS_SEQUENCE_SIZE                    4
#define IS_VIDEO_PRESENT                    5
#define IS_STEAL_FINISHED                   6
#define IS_STORE_FILE_PATH                  7
#define IS_LUMA_BANDWIDTH_FILTER            8
#define IS_BOARD_REVISION                   9
#define IS_MIRROR_BITMAP_UPDOWN             10
#define IS_BUS_OVR_CNT                      11
#define IS_STEAL_ERROR_CNT                  12
#define IS_LOW_COLOR_REMOVAL                13
#define IS_CHROMA_COMB_FILTER               14
#define IS_CHROMA_AGC                       15
#define IS_WATCHDOG_ON_BOARD                16
#define IS_PASSTHROUGH_ON_BOARD             17
#define IS_EXTERNAL_VREF_MODE               18
#define IS_WAIT_TIMEOUT                     19
#define IS_TRIGGER_MISSED                   20
#define IS_LAST_CAPTURE_ERROR               21
#define IS_PARAMETER_SET_1                  22
#define IS_PARAMETER_SET_2                  23
#define IS_STANDBY                          24
#define IS_STANDBY_SUPPORTED                25
#define IS_QUEUED_IMAGE_EVENT_CNT           26

// ----------------------------------------------------------------------------
// interface type defines
// ----------------------------------------------------------------------------
#define IS_INTERFACE_TYPE_USB               0x40
#define IS_INTERFACE_TYPE_ETH               0x80

// ----------------------------------------------------------------------------
// board type defines
// ----------------------------------------------------------------------------
#define IS_BOARD_TYPE_FALCON                1
#define IS_BOARD_TYPE_EAGLE                 2
#define IS_BOARD_TYPE_FALCON2               3
#define IS_BOARD_TYPE_FALCON_PLUS           7
#define IS_BOARD_TYPE_FALCON_QUATTRO        9
#define IS_BOARD_TYPE_FALCON_DUO            10
#define IS_BOARD_TYPE_EAGLE_QUATTRO         11
#define IS_BOARD_TYPE_EAGLE_DUO             12
#define IS_BOARD_TYPE_UEYE_USB              (IS_INTERFACE_TYPE_USB + 0)     // 0x40
#define IS_BOARD_TYPE_UEYE_USB_SE           IS_BOARD_TYPE_UEYE_USB          // 0x40
#define IS_BOARD_TYPE_UEYE_USB_RE           IS_BOARD_TYPE_UEYE_USB          // 0x40
#define IS_BOARD_TYPE_UEYE_USB_ME           (IS_INTERFACE_TYPE_USB + 0x01)  // 0x41
#define IS_BOARD_TYPE_UEYE_USB_LE           (IS_INTERFACE_TYPE_USB + 0x02)  // 0x42
#define IS_BOARD_TYPE_UEYE_ETH              IS_INTERFACE_TYPE_ETH           // 0x80
#define IS_BOARD_TYPE_UEYE_ETH_HE           IS_BOARD_TYPE_UEYE_ETH          // 0x80
#define IS_BOARD_TYPE_UEYE_ETH_SE           (IS_INTERFACE_TYPE_ETH + 0x01)  // 0x81
#define IS_BOARD_TYPE_UEYE_ETH_RE           IS_BOARD_TYPE_UEYE_ETH_SE       // 0x81

// ----------------------------------------------------------------------------
// camera type defines
// ----------------------------------------------------------------------------
#define IS_CAMERA_TYPE_UEYE_USB         IS_BOARD_TYPE_UEYE_USB_SE
#define IS_CAMERA_TYPE_UEYE_USB_SE      IS_BOARD_TYPE_UEYE_USB_SE
#define IS_CAMERA_TYPE_UEYE_USB_RE      IS_BOARD_TYPE_UEYE_USB_RE
#define IS_CAMERA_TYPE_UEYE_USB_ME      IS_BOARD_TYPE_UEYE_USB_ME
#define IS_CAMERA_TYPE_UEYE_USB_LE      IS_BOARD_TYPE_UEYE_USB_LE
#define IS_CAMERA_TYPE_UEYE_ETH         IS_BOARD_TYPE_UEYE_ETH_HE
#define IS_CAMERA_TYPE_UEYE_ETH_HE      IS_BOARD_TYPE_UEYE_ETH_HE
#define IS_CAMERA_TYPE_UEYE_ETH_SE      IS_BOARD_TYPE_UEYE_ETH_SE
#define IS_CAMERA_TYPE_UEYE_ETH_RE      IS_BOARD_TYPE_UEYE_ETH_RE

// ----------------------------------------------------------------------------
// readable operation system defines
// ----------------------------------------------------------------------------
#define IS_OS_UNDETERMINED                  0
#define IS_OS_WIN95                         1
#define IS_OS_WINNT40                       2
#define IS_OS_WIN98                         3
#define IS_OS_WIN2000                       4
#define IS_OS_WINXP                         5
#define IS_OS_WINME                         6
#define IS_OS_WINNET                        7
#define IS_OS_WINSERVER2003                 8
#define IS_OS_WINVISTA                      9
#define IS_OS_LINUX24                       10
#define IS_OS_LINUX26                       11
#define IS_OS_WIN7                          12


// ----------------------------------------------------------------------------
// Bus speed
// ----------------------------------------------------------------------------
#define IS_USB_10                           0x0001 //  1,5 Mb/s
#define IS_USB_11                           0x0002 //   12 Mb/s
#define IS_USB_20                           0x0004 //  480 Mb/s
#define IS_USB_30                           0x0008 // 5000 Mb/s
#define IS_ETHERNET_10                      0x0080 //   10 Mb/s
#define IS_ETHERNET_100                     0x0100 //  100 Mb/s
#define IS_ETHERNET_1000                    0x0200 // 1000 Mb/s
#define IS_ETHERNET_10000                   0x0400 //10000 Mb/s

#define IS_USB_LOW_SPEED                    1
#define IS_USB_FULL_SPEED                   12
#define IS_USB_HIGH_SPEED                   480
#define IS_USB_SUPER_SPEED                  5000
#define IS_ETHERNET_10Base                  10
#define IS_ETHERNET_100Base                 100
#define IS_ETHERNET_1000Base                1000
#define IS_ETHERNET_10GBase                 10000

// ----------------------------------------------------------------------------
// HDR
// ----------------------------------------------------------------------------
#define IS_HDR_NOT_SUPPORTED                0
#define IS_HDR_KNEEPOINTS                   1
#define IS_DISABLE_HDR                      0
#define IS_ENABLE_HDR                       1


// ----------------------------------------------------------------------------
// Test images
// ----------------------------------------------------------------------------
#define IS_TEST_IMAGE_NONE                          0x00000000
#define IS_TEST_IMAGE_WHITE                         0x00000001
#define IS_TEST_IMAGE_BLACK                         0x00000002
#define IS_TEST_IMAGE_HORIZONTAL_GREYSCALE          0x00000004
#define IS_TEST_IMAGE_VERTICAL_GREYSCALE            0x00000008
#define IS_TEST_IMAGE_DIAGONAL_GREYSCALE            0x00000010
#define IS_TEST_IMAGE_WEDGE_GRAY                    0x00000020
#define IS_TEST_IMAGE_WEDGE_COLOR                   0x00000040
#define IS_TEST_IMAGE_ANIMATED_WEDGE_GRAY           0x00000080

#define IS_TEST_IMAGE_ANIMATED_WEDGE_COLOR          0x00000100
#define IS_TEST_IMAGE_MONO_BARS                     0x00000200
#define IS_TEST_IMAGE_COLOR_BARS1                   0x00000400
#define IS_TEST_IMAGE_COLOR_BARS2                   0x00000800
#define IS_TEST_IMAGE_GREYSCALE1                    0x00001000
#define IS_TEST_IMAGE_GREY_AND_COLOR_BARS           0x00002000
#define IS_TEST_IMAGE_MOVING_GREY_AND_COLOR_BARS    0x00004000
#define IS_TEST_IMAGE_ANIMATED_LINE                 0x00008000

#define IS_TEST_IMAGE_ALTERNATE_PATTERN             0x00010000
#define IS_TEST_IMAGE_VARIABLE_GREY                 0x00020000
#define IS_TEST_IMAGE_MONOCHROME_HORIZONTAL_BARS    0x00040000
#define IS_TEST_IMAGE_MONOCHROME_VERTICAL_BARS      0x00080000
#define IS_TEST_IMAGE_CURSOR_H                      0x00100000
#define IS_TEST_IMAGE_CURSOR_V                      0x00200000
#define IS_TEST_IMAGE_COLDPIXEL_GRID                0x00400000
#define IS_TEST_IMAGE_HOTPIXEL_GRID                 0x00800000

#define IS_TEST_IMAGE_VARIABLE_RED_PART             0x01000000
#define IS_TEST_IMAGE_VARIABLE_GREEN_PART           0x02000000
#define IS_TEST_IMAGE_VARIABLE_BLUE_PART            0x04000000
#define IS_TEST_IMAGE_SHADING_IMAGE                 0x08000000
//                                                  0x10000000
//                                                  0x20000000
//                                                  0x40000000
//                                                  0x80000000


// ----------------------------------------------------------------------------
// Sensor scaler
// ----------------------------------------------------------------------------
#define IS_ENABLE_SENSOR_SCALER             1
#define IS_ENABLE_ANTI_ALIASING             2


// ----------------------------------------------------------------------------
// Timeouts
// ----------------------------------------------------------------------------
#define IS_TRIGGER_TIMEOUT                  0


// ----------------------------------------------------------------------------
// Auto pixel clock modes
// ----------------------------------------------------------------------------
#define IS_BEST_PCLK_RUN_ONCE               0

// ----------------------------------------------------------------------------
// sequence flags
// ----------------------------------------------------------------------------
#define IS_LOCK_LAST_BUFFER                 0x8002

// ----------------------------------------------------------------------------
// Image files types
// ----------------------------------------------------------------------------
#define IS_IMG_BMP                          0
#define IS_IMG_JPG                          1
#define IS_IMG_PNG                          2
#define IS_IMG_RAW                          4
#define IS_IMG_TIF                          8

// ----------------------------------------------------------------------------
// I2C defines
// nRegisterAddr | IS_I2C_16_BIT_REGISTER
// ----------------------------------------------------------------------------
#define IS_I2C_16_BIT_REGISTER              0x10000000

// ----------------------------------------------------------------------------
// DirectDraw steal video constants   (Falcon)
// ----------------------------------------------------------------------------
#define IS_INIT_STEAL_VIDEO                 1
#define IS_EXIT_STEAL_VIDEO                 2
#define IS_INIT_STEAL_VIDEO_MANUAL          3
#define IS_INIT_STEAL_VIDEO_AUTO            4
#define IS_SET_STEAL_RATIO                  64
#define IS_USE_MEM_IMAGE_SIZE               128
#define IS_STEAL_MODES_MASK                 7
#define IS_SET_STEAL_COPY                   0x1000
#define IS_SET_STEAL_NORMAL                 0x2000

// ----------------------------------------------------------------------------
// AGC modes   (Falcon)
// ----------------------------------------------------------------------------
#define IS_GET_AGC_MODE                     0x8000
#define IS_SET_AGC_OFF                      0
#define IS_SET_AGC_ON                       1


// ----------------------------------------------------------------------------
// Gamma modes   (Falcon)
// ----------------------------------------------------------------------------
#define IS_GET_GAMMA_MODE                   0x8000
#define IS_SET_GAMMA_OFF                    0
#define IS_SET_GAMMA_ON                     1


// ----------------------------------------------------------------------------
// sync levels   (Falcon)
// ----------------------------------------------------------------------------
#define IS_GET_SYNC_LEVEL                   0x8000
#define IS_SET_SYNC_75                      0
#define IS_SET_SYNC_125                     1


// ----------------------------------------------------------------------------
// color bar modes   (Falcon)
// ----------------------------------------------------------------------------
#define IS_GET_CBARS_MODE                   0x8000
#define IS_SET_CBARS_OFF                    0
#define IS_SET_CBARS_ON                     1


// ----------------------------------------------------------------------------
// horizontal filter defines   (Falcon)
// ----------------------------------------------------------------------------
#define IS_GET_HOR_FILTER_MODE              0x8000
#define IS_GET_HOR_FILTER_STEP              0x8001

#define IS_DISABLE_HOR_FILTER               0
#define IS_ENABLE_HOR_FILTER                1
#define IS_HOR_FILTER_STEP(_s_)         ((_s_ + 1) << 1)
#define IS_HOR_FILTER_STEP1                 2
#define IS_HOR_FILTER_STEP2                 4
#define IS_HOR_FILTER_STEP3                 6


// ----------------------------------------------------------------------------
// vertical filter defines   (Falcon)
// ----------------------------------------------------------------------------
#define IS_GET_VERT_FILTER_MODE             0x8000
#define IS_GET_VERT_FILTER_STEP             0x8001

#define IS_DISABLE_VERT_FILTER              0
#define IS_ENABLE_VERT_FILTER               1
#define IS_VERT_FILTER_STEP(_s_)        ((_s_ + 1) << 1)
#define IS_VERT_FILTER_STEP1                2
#define IS_VERT_FILTER_STEP2                4
#define IS_VERT_FILTER_STEP3                6


// ----------------------------------------------------------------------------
// scaler modes   (Falcon)
// ----------------------------------------------------------------------------
#define IS_GET_SCALER_MODE          (float) 1000
#define IS_SET_SCALER_OFF           (float) 0
#define IS_SET_SCALER_ON            (float) 1

#define IS_MIN_SCALE_X              (float)   6.25
#define IS_MAX_SCALE_X              (float) 100.00
#define IS_MIN_SCALE_Y              (float)   6.25
#define IS_MAX_SCALE_Y              (float) 100.00


// ----------------------------------------------------------------------------
// video source selectors   (Falcon)
// ----------------------------------------------------------------------------
#define IS_GET_VIDEO_IN                     0x8000
#define IS_GET_VIDEO_PASSTHROUGH            0x8000
#define IS_GET_VIDEO_IN_TOGGLE              0x8001
#define IS_GET_TOGGLE_INPUT_1               0x8000
#define IS_GET_TOGGLE_INPUT_2               0x8001
#define IS_GET_TOGGLE_INPUT_3               0x8002
#define IS_GET_TOGGLE_INPUT_4               0x8003

#define IS_SET_VIDEO_IN_1                   0x00
#define IS_SET_VIDEO_IN_2                   0x01
#define IS_SET_VIDEO_IN_S                   0x02
#define IS_SET_VIDEO_IN_3                   0x03
#define IS_SET_VIDEO_IN_4                   0x04
#define IS_SET_VIDEO_IN_1S                  0x10
#define IS_SET_VIDEO_IN_2S                  0x11
#define IS_SET_VIDEO_IN_3S                  0x13
#define IS_SET_VIDEO_IN_4S                  0x14
#define IS_SET_VIDEO_IN_EXT                 0x40
#define IS_SET_TOGGLE_OFF                   0xFF
#define IS_SET_VIDEO_IN_SYNC                0x4000


// ----------------------------------------------------------------------------
// video crossbar selectors   (Falcon)
// ----------------------------------------------------------------------------
#define IS_GET_CROSSBAR                     0x8000

#define IS_CROSSBAR_1                       0
#define IS_CROSSBAR_2                       1
#define IS_CROSSBAR_3                       2
#define IS_CROSSBAR_4                       3
#define IS_CROSSBAR_5                       4
#define IS_CROSSBAR_6                       5
#define IS_CROSSBAR_7                       6
#define IS_CROSSBAR_8                       7
#define IS_CROSSBAR_9                       8
#define IS_CROSSBAR_10                      9
#define IS_CROSSBAR_11                      10
#define IS_CROSSBAR_12                      11
#define IS_CROSSBAR_13                      12
#define IS_CROSSBAR_14                      13
#define IS_CROSSBAR_15                      14
#define IS_CROSSBAR_16                      15
#define IS_SELECT_AS_INPUT                  128


// ----------------------------------------------------------------------------
// video format selectors   (Falcon)
// ----------------------------------------------------------------------------
#define IS_GET_VIDEO_MODE                   0x8000

#define IS_SET_VM_PAL                       0
#define IS_SET_VM_NTSC                      1
#define IS_SET_VM_SECAM                     2
#define IS_SET_VM_AUTO                      3


// ----------------------------------------------------------------------------
// capture modes   (Falcon)
// ----------------------------------------------------------------------------
#define IS_GET_CAPTURE_MODE                 0x8000

#define IS_SET_CM_ODD                       0x0001
#define IS_SET_CM_EVEN                      0x0002
#define IS_SET_CM_FRAME                     0x0004
#define IS_SET_CM_NONINTERLACED             0x0008
#define IS_SET_CM_NEXT_FRAME                0x0010
#define IS_SET_CM_NEXT_FIELD                0x0020
#define IS_SET_CM_BOTHFIELDS            (IS_SET_CM_ODD | IS_SET_CM_EVEN | IS_SET_CM_NONINTERLACED)
#define IS_SET_CM_FRAME_STEREO              0x2004


// ----------------------------------------------------------------------------
// display update mode constants   (Falcon)
// ----------------------------------------------------------------------------
#define IS_GET_UPDATE_MODE                  0x8000
#define IS_SET_UPDATE_TIMER                 1
#define IS_SET_UPDATE_EVENT                 2


// ----------------------------------------------------------------------------
// sync generator mode constants   (Falcon)
// ----------------------------------------------------------------------------
#define IS_GET_SYNC_GEN                     0x8000
#define IS_SET_SYNC_GEN_OFF                 0
#define IS_SET_SYNC_GEN_ON                  1


// ----------------------------------------------------------------------------
// decimation modes   (Falcon)
// ----------------------------------------------------------------------------
#define IS_GET_DECIMATION_MODE              0x8000
#define IS_GET_DECIMATION_NUMBER            0x8001

#define IS_DECIMATION_OFF                   0
#define IS_DECIMATION_CONSECUTIVE           1
#define IS_DECIMATION_DISTRIBUTED           2


// ----------------------------------------------------------------------------
// hardware watchdog defines   (Falcon)
// ----------------------------------------------------------------------------
#define IS_GET_WATCHDOG_TIME                0x2000
#define IS_GET_WATCHDOG_RESOLUTION          0x4000
#define IS_GET_WATCHDOG_ENABLE              0x8000

#define IS_WATCHDOG_MINUTES                 0
#define IS_WATCHDOG_SECONDS                 0x8000
#define IS_DISABLE_WATCHDOG                 0
#define IS_ENABLE_WATCHDOG                  1
#define IS_RETRIGGER_WATCHDOG               2
#define IS_ENABLE_AUTO_DEACTIVATION         4
#define IS_DISABLE_AUTO_DEACTIVATION        8
#define IS_WATCHDOG_RESERVED                0x1000


// ----------------------------------------------------------------------------
// typedefs
// ----------------------------------------------------------------------------
#ifdef __LINUX__
        #define FORCEINLINE         inline
        #define USHORT              IS_U16

		#include <unistd.h>

		#define Sleep(n)       usleep(n)

		#include <stdint.h>

        // aliases for common Win32 types
        typedef int32_t           BOOLEAN;
        typedef int32_t           BOOL;
        typedef int32_t           INT;
        typedef uint32_t          UINT;
        typedef int32_t           LONG;
        typedef void              VOID;
        typedef void*             LPVOID;
        typedef uint32_t          ULONG;

        typedef uint64_t          UINT64;
        typedef int64_t           __int64;
        typedef int64_t           LONGLONG;
        typedef uint32_t          DWORD;
        typedef uint16_t          WORD;

        typedef unsigned char     BYTE;
        typedef char              CHAR;
        typedef char              TCHAR;
        typedef unsigned char     UCHAR;

        typedef int8_t*           LPTSTR;
        typedef const int8_t*     LPCTSTR;
        typedef const int8_t*     LPCSTR;
        typedef uint32_t          WPARAM;
        typedef uint32_t          LPARAM;
        typedef uint32_t          LRESULT;
        typedef uint32_t          HRESULT;

        typedef void*             HWND;
        typedef void*             HGLOBAL;
        typedef void*             HINSTANCE;
        typedef void*             HDC;
        typedef void*             HMODULE;
        typedef void*             HKEY;
        typedef void*             HANDLE;

        typedef BYTE*             LPBYTE;
        typedef DWORD*            PDWORD;
        typedef VOID*             PVOID;
        typedef CHAR*             PCHAR;

				

    #ifndef FALSE
        #define FALSE 0
    #endif
    #ifndef TRUE
        #define TRUE 1
    #endif

    #ifndef HIBYTE
        #define HIBYTE(_x_)    ( (_x_)>>8 )
    #endif

    #ifndef LOBYTE
        #define LOBYTE(_x_)    ( (_x_)&0x00ff )
    #endif

    #ifndef HIWORD
        #define HIWORD(_x_)    ( (_x_)>>16 )
    #endif

    #ifndef LOWORD
        #define LOWORD(_x_)    ( (_x_)&0x0000ffff )
    #endif

    #ifndef _min_
        #define _min_( _x_, _y_ ) ( (_x_)<(_y_) ? (_x_) : (_y_) )
    #endif

    #ifndef _max_
        #define _max_( _x_, _y_ ) ( (_x_)>(_y_) ? (_x_) : (_y_) )
    #endif

    #ifndef WM_USER
        #define WM_USER        0x400
    #endif

        // unknown stuff for Linux
        #define WINAPI
        #define CALLBACK
        #undef  UNICODE
        #define __stdcall

    //#define IDSEXP    EXTERNC __attribute__((cdecl)) INT
    //#define IDSEXPUL  EXTERNC __attribute__((cdecl)) ULONG
        #define IDSEXP    __attribute__((cdecl)) INT
        #define IDSEXPUL  __attribute__((cdecl)) ULONG

        typedef long (*WNDPROC) (HWND, UINT, WPARAM, LPARAM);
#if 0
        typedef union _LARGE_INTEGER
        {
            struct
            {
                DWORD LowPart;
                LONG HighPart;
            };
            struct
            {
                DWORD LowPart;
                LONG HighPart;
            } u;
            LONGLONG QuadPart;
        } LARGE_INTEGER, *PLARGE_INTEGER;

        //useful structs that were in windows.h
        typedef struct tagRECT
        {
            long    left;
            long    top;
            long    right;
            long    bottom;
        } RECT, *PRECT, *LPRECT;

        typedef struct tagRGNDATAHEADER
        {
            DWORD   dwSize;
            DWORD   iType;
            DWORD   nCount;
            DWORD   nRgnSize;
            RECT    rcBound;
        } RGNDATAHEADER, *PRGNDATAHEADER;

        typedef struct tagRGNDATA
        {
            RGNDATAHEADER   rdh;
            char            Buffer[1];
        } RGNDATA, *PRGNDATA, *LPRGNDATA;


        typedef struct tagBITMAPINFOHEADER
        {
                DWORD      biSize;
                long       biWidth;
                long       biHeight;
                WORD       biPlanes;
                WORD       biBitCount;
                DWORD      biCompression;
                DWORD      biSizeImage;
                long       biXPelsPerMeter;
                long       biYPelsPerMeter;
                DWORD      biClrUsed;
                DWORD      biClrImportant;
        } BITMAPINFOHEADER, *PBITMAPINFOHEADER, *LPBITMAPINFOHEADER;

        typedef struct tagRGBQUAD
        {
                BYTE    rgbBlue;
                BYTE    rgbGreen;
                BYTE    rgbRed;
                BYTE    rgbReserved;
        } RGBQUAD;

        typedef struct tagBITMAPINFO
        {
            BITMAPINFOHEADER    bmiHeader;
            RGBQUAD             bmiColors[1];
        } BITMAPINFO, *PBITMAPINFO, *LPBITMAPINFO;
#endif /* 0 */

    #define ZeroMemory(a,b)      memset((a), 0, (b))
    #define OutputDebugString(s) fprintf(stderr, s)


    #define INFINITE    -1
#else

#include <windows.h>

#if defined (_MSC_VER) || defined (__BORLANDC__) || defined (_WIN32_WCE)
  #if defined (_PURE_C) && !defined (_IDS_EXPORT) && !defined (_FALC_EXPORT)
    #define IDSEXP     extern  __declspec(dllimport) INT __cdecl
    #define IDSEXPUL   extern  __declspec(dllimport) ULONG __cdecl
  #elif defined (__STDC__) && !defined (_IDS_EXPORT) && !defined (_FALC_EXPORT)
    #define IDSEXP   extern  __declspec(dllimport) INT __cdecl
    #define IDSEXPUL extern  __declspec(dllimport) ULONG __cdecl
  #elif !defined (_IDS_EXPORT) && !defined (_FALC_EXPORT)   // using the DLL, not creating one
    #define IDSEXP   extern "C" __declspec(dllimport) INT __cdecl
    #define IDSEXPUL extern "C" __declspec(dllimport) ULONG __cdecl
  #elif defined (_IDS_VBSTD) || defined (_FALC_VBSTD)     // for creating stdcall dll
    #define IDSEXP    extern __declspec(dllexport) INT __stdcall
    #define IDSEXPUL  extern __declspec(dllexport) ULONG __stdcall
  #else            // for creating cdecl dll
    #define IDSEXP    extern  __declspec(dllexport) INT __cdecl
    #define IDSEXPUL  extern  __declspec(dllexport) ULONG __cdecl
  #endif
#elif !defined (_IDS_EXPORT) && !defined (_FALC_EXPORT)  // using the DLL, not creating one
  #define IDSEXP    extern  __declspec(dllimport) INT __cdecl
  #define IDSEXPUL  extern  __declspec(dllimport) ULONG __cdecl
#endif

typedef int     INT;

#endif    // Linux

#ifdef _WIN32_WCE
  typedef TCHAR IS_CHAR;
#else
  typedef char IS_CHAR;
#endif


// ----------------------------------------------------------------------------
// typedefs
// ----------------------------------------------------------------------------
typedef DWORD   HIDS;
typedef DWORD   HCAM;
typedef DWORD   HFALC;

// ----------------------------------------------------------------------------
// invalid values for device handles
// ----------------------------------------------------------------------------
#define IS_INVALID_HIDS (HIDS)0
#define IS_INVALID_HCAM (HIDS)0
#define IS_INVALID_HFALC (HIDS)0


// ----------------------------------------------------------------------------
// info struct
// ----------------------------------------------------------------------------
#define FALCINFO   BOARDINFO
#define PFALCINFO  PBOARDINFO
#define CAMINFO    BOARDINFO
#define PCAMINFO   PBOARDINFO

typedef struct
{
  char          SerNo[12];          // e.g. "1234512345"  (11 char)
  char          ID[20];             // e.g. "IDS GmbH"
  char          Version[10];        // e.g. "V2.10"  (9 char)
  char          Date[12];           // e.g. "24.01.2006" (11 char)
  unsigned char Select;             // contains board select number for multi board support
  unsigned char Type;               // e.g. IS_BOARD_TYPE_UEYE_USB
  char          Reserved[8];        // (7 char)
} BOARDINFO, *PBOARDINFO;


typedef struct _SENSORINFO
{
  WORD          SensorID;           // e.g. IS_SENSOR_UI224X_C
  IS_CHAR       strSensorName[32];  // e.g. "UI-224X-C"
  char          nColorMode;         // e.g. IS_COLORMODE_BAYER
  DWORD         nMaxWidth;          // e.g. 1280
  DWORD         nMaxHeight;         // e.g. 1024
  BOOL          bMasterGain;        // e.g. TRUE
  BOOL          bRGain;             // e.g. TRUE
  BOOL          bGGain;             // e.g. TRUE
  BOOL          bBGain;             // e.g. TRUE
  BOOL          bGlobShutter;       // e.g. TRUE
  char          Reserved[16];       // not used
} SENSORINFO, *PSENSORINFO;


typedef struct _REVISIONINFO
{
    WORD  size;                     // 2
    WORD  Sensor;                   // 2
    WORD  Cypress;                  // 2
    DWORD Blackfin;                 // 4
    WORD  DspFirmware;              // 2
                                    // --12
    WORD  USB_Board;                // 2
    WORD  Sensor_Board;             // 2
    WORD  Processing_Board;         // 2
    WORD  Memory_Board;             // 2
    WORD  Housing;                  // 2
    WORD  Filter;                   // 2
    WORD  Timing_Board;             // 2
    WORD  Product;                  // 2
    WORD  Power_Board;              // 2
    WORD  Logic_Board;              // 2
                                    // --28
    BYTE reserved[96];              // --128
} REVISIONINFO, *PREVISIONINFO;



// ----------------------------------------------------------------------------
// Capture errors
// ----------------------------------------------------------------------------
typedef enum _UEYE_CAPTURE_ERROR
{
    IS_CAPERR_API_NO_DEST_MEM=              0xa2,
    IS_CAPERR_API_CONVERSION_FAILED=        0xa3,
    IS_CAPERR_API_IMAGE_LOCKED=             0xa5,

    IS_CAPERR_DRV_OUT_OF_BUFFERS=           0xb2,
    IS_CAPERR_DRV_DEVICE_NOT_READY=         0xb4,

    IS_CAPERR_USB_TRANSFER_FAILED=          0xc7,

    IS_CAPERR_DEV_TIMEOUT=                  0xd6,

    IS_CAPERR_ETH_BUFFER_OVERRUN=           0xe4,
    IS_CAPERR_ETH_MISSED_IMAGES=            0xe5

} UEYE_CAPTURE_ERROR;

typedef struct _UEYE_CAPTURE_ERROR_INFO
{
    DWORD dwCapErrCnt_Total;

    BYTE  reserved[60];

    DWORD adwCapErrCnt_Detail[256]; // access via UEYE_CAPTURE_ERROR

} UEYE_CAPTURE_ERROR_INFO;



#ifndef UEYE_CAMERA_INFO_STRUCT
#define UEYE_CAMERA_INFO_STRUCT
typedef struct _UEYE_CAMERA_INFO
{
  DWORD     dwCameraID;   // this is the user definable camera ID
  DWORD     dwDeviceID;   // this is the systems enumeration ID
  DWORD     dwSensorID;   // this is the sensor ID e.g. IS_SENSOR_UI141X_M
  DWORD     dwInUse;      // flag, whether the camera is in use or not
  IS_CHAR   SerNo[16];    // serial number of the camera
  IS_CHAR   Model[16];    // model name of the camera
  DWORD     dwStatus;     // various flags with camera status
  DWORD     dwReserved[15];
}UEYE_CAMERA_INFO, *PUEYE_CAMERA_INFO;
#endif //UEYE_CAMERA_INFO_STRUCT

// usage of the list:
// 1. call the DLL with .dwCount = 0
// 2. DLL returns .dwCount = N  (N = number of available cameras)
// 3. call DLL with .dwCount = N and a pointer to UEYE_CAMERA_LIST with
//    and array of UEYE_CAMERA_INFO[N]
// 4. DLL will fill in the array with the camera infos and
//    will update the .dwCount member with the actual number of cameras
//    because there may be a change in number of cameras between step 2 and 3
// 5. check if there's a difference in actual .dwCount and formerly
//    reported value of N and call DLL again with an updated array size
#ifndef UEYE_CAMERA_LIST_STRUCT
#define UEYE_CAMERA_LIST_STRUCT
typedef struct _UEYE_CAMERA_LIST
{
  ULONG     dwCount;
  UEYE_CAMERA_INFO uci[1];
}UEYE_CAMERA_LIST, *PUEYE_CAMERA_LIST;
#endif //UEYE_CAMERA_LIST_STRUCT

// ----------------------------------------------------------------------------
// the  following defines are the status bits of the dwStatus member of
// the UEYE_CAMERA_INFO structure
#define FIRMWARE_DOWNLOAD_NOT_SUPPORTED                 0x00000001
#define INTERFACE_SPEED_NOT_SUPPORTED                   0x00000002
#define INVALID_SENSOR_DETECTED                         0x00000004
#define AUTHORIZATION_FAILED                            0x00000008
#define DEVSTS_INCLUDED_STARTER_FIRMWARE_INCOMPATIBLE   0x00000010

// the following macro determines the availability of the camera based
// on the status flags
#define IS_CAMERA_AVAILABLE(_s_)     ( (((_s_) & FIRMWARE_DOWNLOAD_NOT_SUPPORTED) == 0) && \
                                       (((_s_) & INTERFACE_SPEED_NOT_SUPPORTED)   == 0) && \
                                       (((_s_) & INVALID_SENSOR_DETECTED)         == 0) && \
                                       (((_s_) & AUTHORIZATION_FAILED)            == 0) )

// ----------------------------------------------------------------------------
// auto feature structs and definitions
// ----------------------------------------------------------------------------
#define AC_SHUTTER				0x00000001
#define AC_GAIN					0x00000002
#define AC_WHITEBAL				0x00000004
#define AC_WB_RED_CHANNEL		0x00000008
#define AC_WB_GREEN_CHANNEL		0x00000010
#define AC_WB_BLUE_CHANNEL		0x00000020
#define AC_FRAMERATE			0x00000040
#define AC_SENSOR_SHUTTER		0x00000080
#define AC_SENSOR_GAIN			0x00000100
#define AC_SENSOR_GAIN_SHUTTER	0x00000200
#define AC_SENSOR_FRAMERATE     0x00000400

#define ACS_ADJUSTING 0x00000001
#define ACS_FINISHED  0x00000002
#define ACS_DISABLED  0x00000004

typedef struct _AUTO_BRIGHT_STATUS
{
    DWORD curValue;             // current average greylevel
    long curError;              // current auto brightness error
    DWORD curController;        // current active brightness controller -> AC_x
    DWORD curCtrlStatus;        // current control status -> ACS_x
} AUTO_BRIGHT_STATUS, *PAUTO_BRIGHT_STATUS;



typedef struct _AUTO_WB_CHANNNEL_STATUS
{
    DWORD curValue;             // current average greylevel
    long curError;              // current auto wb error
    DWORD curCtrlStatus;        // current control status -> ACS_x
} AUTO_WB_CHANNNEL_STATUS, *PAUTO_WB_CHANNNEL_STATUS;

typedef struct _AUTO_WB_STATUS
{
    AUTO_WB_CHANNNEL_STATUS RedChannel;
    AUTO_WB_CHANNNEL_STATUS GreenChannel;
    AUTO_WB_CHANNNEL_STATUS BlueChannel;
    DWORD curController;        // current active wb controller -> AC_x
} AUTO_WB_STATUS, *PAUTO_WB_STATUS;

typedef struct _UEYE_AUTO_INFO
{
    DWORD               AutoAbility;        // auto control ability
    AUTO_BRIGHT_STATUS  sBrightCtrlStatus;  // brightness auto control status
    AUTO_WB_STATUS      sWBCtrlStatus;      // white balance auto control status
    DWORD               reserved[12];
} UEYE_AUTO_INFO, *PUEYE_AUTO_INFO;


// ----------------------------------------------------------------------------
// function exports
// ----------------------------------------------------------------------------
#ifdef __LINUX__
    IDSEXP is_WaitEvent             (HIDS hf, INT which, INT nTimeout);
#endif

// ----------------------------------------------------------------------------
// functions only effective on Falcon boards
// ----------------------------------------------------------------------------
  IDSEXP   is_SetVideoInput          (HIDS hf, INT Source);
  IDSEXP   is_SetSaturation          (HIDS hf, INT ChromU, INT ChromV);
  IDSEXP   is_SetHue                 (HIDS hf, INT Hue);
  IDSEXP   is_SetVideoMode           (HIDS hf, INT Mode);
  IDSEXP   is_SetAGC                 (HIDS hf, INT Mode);
  IDSEXP   is_SetSyncLevel           (HIDS hf, INT Level);
  IDSEXP   is_ShowColorBars          (HIDS hf, INT Mode);
  IDSEXP   is_SetScaler              (HIDS hf, float Scalex, float Scaley);
  IDSEXP   is_SetCaptureMode         (HIDS hf, INT Mode);
  IDSEXP   is_SetHorFilter           (HIDS hf, INT Mode);
  IDSEXP   is_SetVertFilter          (HIDS hf, INT Mode);
  IDSEXP   is_ScaleDDOverlay         (HIDS hf, BOOL boScale);
  IDSEXP   is_GetCurrentField        (HIDS hf, int* pField);
  IDSEXP   is_SetVideoSize           (HIDS hf, INT xpos, INT ypos, INT xsize, INT ysize);
  IDSEXP   is_SetKeyOffset           (HIDS hf, INT nOffsetX, INT nOffsetY);
  IDSEXP   is_PrepareStealVideo      (HIDS hf, int Mode, ULONG StealColorMode);
  IDSEXP   is_SetParentHwnd          (HIDS hf, HWND hwnd);
  IDSEXP   is_SetUpdateMode          (HIDS hf, INT mode);
  IDSEXP   is_OvlSurfaceOffWhileMove (HIDS hf, BOOL boMode);
  IDSEXP   is_GetPciSlot             (HIDS hf, INT* pnSlot);
  IDSEXP   is_GetIRQ                 (HIDS hf, INT* pnIRQ);
  IDSEXP   is_SetToggleMode          (HIDS hf, int nInput1, int nInput2, int nInput3, int nInput4);
  IDSEXP   is_SetDecimationMode      (HIDS hf, INT nMode, INT nDecimate);
  IDSEXP   is_SetSync                (HIDS hf, INT nSync);
  // only FALCON duo/quattro
  IDSEXP   is_SetVideoCrossbar       (HIDS hf, INT In, INT Out);
  // watchdog functions
  IDSEXP   is_WatchdogTime           (HIDS hf, long lTime);
  IDSEXP   is_Watchdog               (HIDS hf, long lMode);
  // video out functions
  IDSEXP   is_SetPassthrough         (HIDS hf, INT Source);

// ----------------------------------------------------------------------------
// alias functions for compatibility
// ----------------------------------------------------------------------------
  IDSEXP   is_InitBoard              (HIDS* phf, HWND hWnd);
  IDSEXP   is_ExitBoard              (HIDS hf);
  IDSEXP   is_InitFalcon             (HIDS* phf, HWND hWnd);
  IDSEXP   is_ExitFalcon             (HIDS hf);

  IDSEXP   is_GetBoardType           (HIDS hf);
  IDSEXP   is_GetBoardInfo           (HIDS hf, PBOARDINFO pInfo);
  IDSEXPUL is_BoardStatus            (HIDS hf, INT nInfo, ULONG ulValue);
  IDSEXP   is_GetNumberOfDevices     (void);
  IDSEXP   is_GetNumberOfBoards      (INT* pnNumBoards);

// ----------------------------------------------------------------------------
// common function
// ----------------------------------------------------------------------------
  IDSEXP   is_StopLiveVideo          (HIDS hf, INT Wait);
  IDSEXP   is_FreezeVideo            (HIDS hf, INT Wait);
  IDSEXP   is_CaptureVideo           (HIDS hf, INT Wait);
  IDSEXP   is_IsVideoFinish          (HIDS hf, BOOL* pbo);
  IDSEXP   is_HasVideoStarted        (HIDS hf, BOOL* pbo);

  IDSEXP   is_SetBrightness          (HIDS hf, INT Bright);
  IDSEXP   is_SetContrast            (HIDS hf, INT Cont);
  IDSEXP   is_SetGamma               (HIDS hf, INT nGamma);

  IDSEXP   is_AllocImageMem          (HIDS hf, INT width, INT height, INT bitspixel, char** ppcImgMem, int* pid);
  IDSEXP   is_SetImageMem            (HIDS hf, char* pcMem, int id);
  IDSEXP   is_FreeImageMem           (HIDS hf, char* pcMem, int id);
  IDSEXP   is_GetImageMem            (HIDS hf, VOID** pMem);
  IDSEXP   is_GetActiveImageMem      (HIDS hf, char** ppcMem, int* pnID);
  IDSEXP   is_InquireImageMem        (HIDS hf, char* pcMem, int nID, int* pnX, int* pnY, int* pnBits, int* pnPitch);
  IDSEXP   is_GetImageMemPitch       (HIDS hf, INT* pPitch);

  IDSEXP   is_SetAllocatedImageMem   (HIDS hf, INT width, INT height, INT bitspixel, char* pcImgMem, int* pid);
  IDSEXP   is_SaveImageMem           (HIDS hf, const IS_CHAR* File, char* pcMem, int nID);
  IDSEXP   is_CopyImageMem           (HIDS hf, char* pcSource, int nID, char* pcDest);
  IDSEXP   is_CopyImageMemLines      (HIDS hf, char* pcSource, int nID, int nLines, char* pcDest);

  IDSEXP   is_AddToSequence          (HIDS hf, char* pcMem, INT nID);
  IDSEXP   is_ClearSequence          (HIDS hf);
  IDSEXP   is_GetActSeqBuf           (HIDS hf, INT* pnNum, char** ppcMem, char** ppcMemLast);
  IDSEXP   is_LockSeqBuf             (HIDS hf, INT nNum, char* pcMem);
  IDSEXP   is_UnlockSeqBuf           (HIDS hf, INT nNum, char* pcMem);

  IDSEXP   is_SetImageSize           (HIDS hf, INT x, INT y);
  IDSEXP   is_SetImagePos            (HIDS hf, INT x, INT y);

  IDSEXP   is_GetError               (HIDS hf, INT* pErr, IS_CHAR** ppcErr);
  IDSEXP   is_SetErrorReport         (HIDS hf, INT Mode);

  IDSEXP   is_ReadEEPROM             (HIDS hf, INT Adr, char* pcString, INT Count);
  IDSEXP   is_WriteEEPROM            (HIDS hf, INT Adr, char* pcString, INT Count);
  IDSEXP   is_SaveImage              (HIDS hf, const IS_CHAR* File);

  IDSEXP   is_SetColorMode           (HIDS hf, INT Mode);
  IDSEXP   is_GetColorDepth          (HIDS hf, INT* pnCol, INT* pnColMode);
  // bitmap display function
  IDSEXP   is_RenderBitmap           (HIDS hf, INT nMemID, HWND hwnd, INT nMode);

  IDSEXP   is_SetDisplayMode         (HIDS hf, INT Mode);
  IDSEXP   is_GetDC                  (HIDS hf, HDC* phDC);
  IDSEXP   is_ReleaseDC              (HIDS hf, HDC hDC);
  IDSEXP   is_UpdateDisplay          (HIDS hf);
  IDSEXP   is_SetDisplaySize         (HIDS hf, INT x, INT y);
  IDSEXP   is_SetDisplayPos          (HIDS hf, INT x, INT y);

  IDSEXP   is_LockDDOverlayMem       (HIDS hf, VOID** ppMem, INT* pPitch);
  IDSEXP   is_UnlockDDOverlayMem     (HIDS hf);
  IDSEXP   is_LockDDMem              (HIDS hf, VOID** ppMem, INT* pPitch);
  IDSEXP   is_UnlockDDMem            (HIDS hf);
  IDSEXP   is_GetDDOvlSurface        (HIDS hf, void** ppDDSurf);
  IDSEXP   is_SetKeyColor            (HIDS hf, INT r, INT g, INT b);
  IDSEXP   is_StealVideo             (HIDS hf, int Wait);
  IDSEXP   is_SetHwnd                (HIDS hf, HWND hwnd);


  IDSEXP   is_SetDDUpdateTime        (HIDS hf, INT ms);
  IDSEXP   is_EnableDDOverlay        (HIDS hf);
  IDSEXP   is_DisableDDOverlay       (HIDS hf);
  IDSEXP   is_ShowDDOverlay          (HIDS hf);
  IDSEXP   is_HideDDOverlay          (HIDS hf);


  IDSEXP   is_GetVsyncCount          (HIDS hf, long* pIntr, long* pActIntr);
  IDSEXP   is_GetOsVersion           (void);
  // version information
  IDSEXP   is_GetDLLVersion          (void);

  IDSEXP   is_InitEvent              (HIDS hf, HANDLE hEv, INT which);
  IDSEXP   is_ExitEvent              (HIDS hf, INT which);
  IDSEXP   is_EnableEvent            (HIDS hf, INT which);
  IDSEXP   is_DisableEvent           (HIDS hf, INT which);

  IDSEXP   is_SetIO                  (HIDS hf, INT nIO);
  IDSEXP   is_SetFlashStrobe         (HIDS hf, INT nMode, INT nLine);
  IDSEXP   is_SetExternalTrigger     (HIDS hf, INT nTriggerMode);
  IDSEXP   is_SetTriggerCounter      (HIDS hf, INT nValue);
  IDSEXP   is_SetRopEffect           (HIDS hf, INT effect, INT param, INT reserved);

// ----------------------------------------------------------------------------
// new functions only valid for uEye camera family
// ----------------------------------------------------------------------------
  // Camera functions
  IDSEXP is_InitCamera                  (HIDS* phf, HWND hWnd);
  IDSEXP is_ExitCamera                  (HIDS hf);
  IDSEXP is_GetCameraInfo               (HIDS hf, PCAMINFO pInfo);
  IDSEXPUL is_CameraStatus              (HIDS hf, INT nInfo, ULONG ulValue);
  IDSEXP is_GetCameraType               (HIDS hf);
  IDSEXP is_GetNumberOfCameras          (INT* pnNumCams);

  // PixelClock
  IDSEXP is_GetPixelClockRange          (HIDS hf, INT *pnMin, INT *pnMax);
  IDSEXP is_SetPixelClock               (HIDS hf, INT Clock);
  IDSEXP is_GetUsedBandwidth            (HIDS hf);
  // Set/Get Frame rate
  IDSEXP is_GetFrameTimeRange           (HIDS hf, double *min, double *max, double *intervall);
  IDSEXP is_SetFrameRate                (HIDS hf, double FPS, double* newFPS);
  // Set/Get Exposure
  IDSEXP is_GetExposureRange            (HIDS hf, double *min, double *max, double *intervall);
  IDSEXP is_SetExposureTime             (HIDS hf, double EXP, double* newEXP);
  // get frames per second
  IDSEXP is_GetFramesPerSecond          (HIDS hf, double *dblFPS);

  // is_SetIOMask ( only uEye USB )
  IDSEXP is_SetIOMask                   (HIDS hf, INT nMask);

  // Get Sensor info
  IDSEXP is_GetSensorInfo               (HIDS hf, PSENSORINFO pInfo);
  // Get RevisionInfo
  IDSEXP is_GetRevisionInfo             (HIDS hf, PREVISIONINFO prevInfo);

  // enable/disable AutoExit after device remove
  IDSEXP is_EnableAutoExit              (HIDS hf, INT nMode);
  // Message
  IDSEXP is_EnableMessage               (HIDS hf, INT which, HWND hWnd);

  // hardware gain settings
  IDSEXP is_SetHardwareGain             (HIDS hf, INT nMaster, INT nRed, INT nGreen, INT nBlue);

  // set render mode
  IDSEXP is_SetRenderMode               (HIDS hf, INT Mode);

  // enable/disable WhiteBalance
  IDSEXP is_SetWhiteBalance             (HIDS hf, INT nMode);
  IDSEXP is_SetWhiteBalanceMultipliers  (HIDS hf, double dblRed, double dblGreen, double dblBlue);
  IDSEXP is_GetWhiteBalanceMultipliers  (HIDS hf, double *pdblRed, double *pdblGreen, double *pdblBlue);

  // Edge enhancement
  IDSEXP is_SetEdgeEnhancement          (HIDS hf, INT nEnable);

  // Sensor features
  IDSEXP is_SetColorCorrection          (HIDS hf, INT nEnable, double *factors);
  IDSEXP is_SetBlCompensation           (HIDS hf, INT nEnable, INT offset, INT reserved);

  // Hotpixel
  IDSEXP is_SetBadPixelCorrection       (HIDS hf, INT nEnable, INT threshold);
  IDSEXP is_LoadBadPixelCorrectionTable (HIDS hf, const IS_CHAR *File);
  IDSEXP is_SaveBadPixelCorrectionTable (HIDS hf, const IS_CHAR *File);
  IDSEXP is_SetBadPixelCorrectionTable  (HIDS hf, INT nMode, WORD *pList);

  // Memoryboard
  IDSEXP is_SetMemoryMode               (HIDS hf, INT nCount, INT nDelay);
  IDSEXP is_TransferImage               (HIDS hf, INT nMemID, INT seqID, INT imageNr, INT reserved);
  IDSEXP is_TransferMemorySequence      (HIDS hf, INT seqID, INT StartNr, INT nCount, INT nSeqPos);
  IDSEXP is_MemoryFreezeVideo           (HIDS hf, INT nMemID, INT Wait);
  IDSEXP is_GetLastMemorySequence       (HIDS hf, INT *pID);
  IDSEXP is_GetNumberOfMemoryImages     (HIDS hf, INT nID, INT *pnCount);
  IDSEXP is_GetMemorySequenceWindow     (HIDS hf, INT nID, INT *left, INT *top, INT *right, INT *bottom);
  IDSEXP is_IsMemoryBoardConnected      (HIDS hf, BOOL *pConnected);
  IDSEXP is_ResetMemory                 (HIDS hf, INT nReserved);

  IDSEXP is_SetSubSampling              (HIDS hf, INT mode);
  IDSEXP is_ForceTrigger                (HIDS hf);

  // new with driver version 1.12.0006
  IDSEXP is_GetBusSpeed                 (HIDS hf);

  // new with driver version 1.12.0015
  IDSEXP is_SetBinning                  (HIDS hf, INT mode);

  // new with driver version 1.12.0017
  IDSEXP is_ResetToDefault              (HIDS hf);
  IDSEXP is_LoadParameters              (HIDS hf, const IS_CHAR* pFilename);
  IDSEXP is_SaveParameters              (HIDS hf, const IS_CHAR* pFilename);

  // new with driver version 1.14.0001
  IDSEXP is_GetGlobalFlashDelays        (HIDS hf, ULONG *pulDelay, ULONG *pulDuration);
  IDSEXP is_SetFlashDelay               (HIDS hf, ULONG ulDelay, ULONG ulDuration);
  // new with driver version 1.14.0002
  IDSEXP is_LoadImage                   (HIDS hf, const IS_CHAR* File);

  // new with driver version 1.14.0008
  IDSEXP is_SetImageAOI                 (HIDS hf, INT xPos, INT yPos, INT width, INT height);
  IDSEXP is_SetCameraID                 (HIDS hf, INT nID);
  IDSEXP is_SetBayerConversion          (HIDS hf, INT nMode);
  IDSEXP is_SetTestImage                (HIDS hf, INT nMode);
  // new with driver version 1.14.0009
  IDSEXP is_SetHardwareGamma            (HIDS hf, INT nMode);

  // new with driver version 2.00.0001
  IDSEXP is_GetCameraList               (PUEYE_CAMERA_LIST pucl);

  // new with driver version 2.00.0011
  IDSEXP is_SetAOI                      (HIDS hf, INT type, INT *pXPos, INT *pYPos, INT *pWidth, INT *pHeight);
  IDSEXP is_SetAutoParameter            (HIDS hf, INT param, double *pval1, double *pval2);
  IDSEXP is_GetAutoInfo                 (HIDS hf, UEYE_AUTO_INFO *pInfo);
  
  // new with driver version 2.20.0001
  IDSEXP is_ConvertImage                (HIDS hf, char* pcSource, int nIDSource, char** pcDest, INT *nIDDest, INT *reserved);
  IDSEXP is_SetConvertParam             (HIDS hf, BOOL ColorCorrection, INT BayerConversionMode, INT ColorMode, INT Gamma, double* WhiteBalanceMultipliers);
  
  IDSEXP is_SaveImageEx                 (HIDS hf, const IS_CHAR* File, INT fileFormat, INT Param);
  IDSEXP is_SaveImageMemEx              (HIDS hf, const IS_CHAR* File, char* pcMem, INT nID, INT FileFormat, INT Param);
  IDSEXP is_LoadImageMem                (HIDS hf, const IS_CHAR* File, char** ppcImgMem, INT* pid);
  
  IDSEXP is_GetImageHistogram           (HIDS hf, int nID, INT ColorMode, DWORD* pHistoMem);
  IDSEXP is_SetTriggerDelay             (HIDS hf, INT nTriggerDelay);

  // new with driver version 2.21.0000
  IDSEXP is_SetGainBoost                (HIDS hf, INT mode);
  IDSEXP is_SetLED                      (HIDS hf, INT nValue);

  IDSEXP is_SetGlobalShutter            (HIDS hf, INT mode);
  IDSEXP is_SetExtendedRegister         (HIDS hf, INT index,WORD value);
  IDSEXP is_GetExtendedRegister         (HIDS hf, INT index, WORD *pwValue);

  // new with driver version 2.22.0002
  IDSEXP is_SetHWGainFactor             (HIDS hf, INT nMode, INT nFactor);

  // camera renumeration
  IDSEXP is_Renumerate                  (HIDS hf, INT nMode);

  // Read / Write I2C
  IDSEXP is_WriteI2C                    (HIDS hf, INT nDeviceAddr, INT nRegisterAddr, BYTE* pbData, INT nLen);
  IDSEXP is_ReadI2C                     (HIDS hf, INT nDeviceAddr, INT nRegisterAddr, BYTE* pbData, INT nLen);


  // new with driver version 3.10.0000
  typedef struct _KNEEPOINT
  {
      double x;
      double y;
  } KNEEPOINT, *PKNEEPOINT;


  typedef struct _KNEEPOINTARRAY
  {
      INT NumberOfUsedKneepoints;
      KNEEPOINT Kneepoint[10];
  } KNEEPOINTARRAY, *PKNEEPOINTARRAY;


  typedef struct _KNEEPOINTINFO
  {
      INT NumberOfSupportedKneepoints;
      INT NumberOfUsedKneepoints;
      double MinValueX;
      double MaxValueX;
      double MinValueY;
      double MaxValueY;
      KNEEPOINT DefaultKneepoint[10];
      INT Reserved[10];
  } KNEEPOINTINFO, *PKNEEPOINTINFO;


  // HDR functions
  IDSEXP is_GetHdrMode                  (HIDS hf, INT *Mode);
  IDSEXP is_EnableHdr                   (HIDS hf, INT Enable);
  IDSEXP is_SetHdrKneepoints            (HIDS hf, KNEEPOINTARRAY *KneepointArray, INT KneepointArraySize);
  IDSEXP is_GetHdrKneepoints            (HIDS hf, KNEEPOINTARRAY *KneepointArray, INT KneepointArraySize);
  IDSEXP is_GetHdrKneepointInfo         (HIDS hf, KNEEPOINTINFO *KneepointInfo, INT KneepointInfoSize);

  IDSEXP is_SetOptimalCameraTiming      (HIDS hf, INT Mode, INT Timeout, INT *pMaxPxlClk, double *pMaxFrameRate);

  IDSEXP is_GetSupportedTestImages      (HIDS hf, INT *SupportedTestImages);
  IDSEXP is_GetTestImageValueRange      (HIDS hf, INT TestImage, INT *TestImageValueMin, INT *TestImageValueMax);
  IDSEXP is_SetSensorTestImage          (HIDS hf, INT Param1, INT Param2);

  IDSEXP is_SetCameraLUT                (HIDS hf, UINT Mode, UINT NumberOfEntries, double *pRed_Grey, double *pGreen, double *pBlue);
  IDSEXP is_GetCameraLUT                (HIDS hf, UINT Mode, UINT NumberOfEntries, double *pRed_Grey, double *pGreen, double *pBlue);

  IDSEXP is_GetColorConverter           (HIDS hf, INT ColorMode, INT *pCurrentConvertMode, INT *pDefaultConvertMode, INT *pSupportedConvertModes);
  IDSEXP is_SetColorConverter           (HIDS hf, INT ColorMode, INT ConvertMode);

  IDSEXP is_GetCaptureErrorInfo         (HIDS hf, UEYE_CAPTURE_ERROR_INFO *pCaptureErrorInfo, UINT SizeCaptureErrorInfo);
  IDSEXP is_ResetCaptureErrorInfo       (HIDS hf );

  IDSEXP is_WaitForNextImage            (HIDS hf, UINT timeout, char **ppcMem, INT *imageID);
  IDSEXP is_InitImageQueue              (HIDS hf, INT nMode);
  IDSEXP is_ExitImageQueue              (HIDS hf);

  IDSEXP is_SetTimeout                  (HIDS hf, UINT nMode, UINT Timeout);
  IDSEXP is_GetTimeout                  (HIDS hf, UINT nMode, UINT *pTimeout);


  typedef enum  eUEYE_GET_ESTIMATED_TIME_MODE
  {
      IS_SE_STARTER_FW_UPLOAD =   0x00000001, /*!< get estimated duration of GigE SE starter firmware upload in milliseconds */

  } UEYE_GET_ESTIMATED_TIME_MODE;    
  
  
  IDSEXP is_GetDuration                 (HIDS hf, UINT nMode, INT* pnTime);


  // new with driver version 3.40.0000
  typedef struct _SENSORSCALERINFO
  {
      INT       nCurrMode;
      INT       nNumberOfSteps;
      double    dblFactorIncrement;
      double    dblMinFactor;
      double    dblMaxFactor;
      double    dblCurrFactor;
      BYTE      bReserved[88];
  } SENSORSCALERINFO;


  IDSEXP is_GetSensorScalerInfo (HIDS hf, SENSORSCALERINFO *pSensorScalerInfo, INT nSensorScalerInfoSize);
  IDSEXP is_SetSensorScaler      (HIDS hf, UINT nMode, double dblFactor); 

  typedef struct _UEYETIME
  {
      WORD      wYear;
      WORD      wMonth;
      WORD      wDay;
      WORD      wHour;
      WORD      wMinute;
      WORD      wSecond;
      WORD      wMilliseconds;
      BYTE      byReserved[10];
  } UEYETIME;


  typedef struct _UEYEIMAGEINFO
  {
      DWORD                 dwFlags;
      BYTE                  byReserved1[4];
      UINT64                u64TimestampDevice;
      UEYETIME              TimestampSystem;
      DWORD                 dwIoStatus;
      BYTE                  byReserved2[4];
      UINT64                u64FrameNumber;
      DWORD                 dwImageBuffers;
      DWORD                 dwImageBuffersInUse;
      DWORD                 dwReserved3;
      DWORD                 dwImageHeight;
      DWORD                 dwImageWidth;
  } UEYEIMAGEINFO;


  IDSEXP is_GetImageInfo (HIDS hf, INT nImageBufferID, UEYEIMAGEINFO *pImageInfo, INT nImageInfoSize);

// ----------------------------------------------------------------------------
// new functions and datatypes only valid for uEye ETH
// ----------------------------------------------------------------------------

#pragma pack( push, 1)

  // IP V4 address
  typedef union _UEYE_ETH_ADDR_IPV4
  {
      struct
      {
          BYTE  by1;
          BYTE  by2;
          BYTE  by3;
          BYTE  by4;
      } by;

      DWORD dwAddr;

  } UEYE_ETH_ADDR_IPV4, *PUEYE_ETH_ADDR_IPV4;

  // Ethernet address
  typedef struct _UEYE_ETH_ADDR_MAC
  {
      BYTE abyOctet[6];

  } UEYE_ETH_ADDR_MAC, *PUEYE_ETH_ADDR_MAC;

  // IP configuration
  typedef struct _UEYE_ETH_IP_CONFIGURATION
  {
      UEYE_ETH_ADDR_IPV4    ipAddress;      /*!< IP address */
      UEYE_ETH_ADDR_IPV4    ipSubnetmask;   /*!< IP subnetmask */

      BYTE                  reserved[4];    /*!< reserved */

  } UEYE_ETH_IP_CONFIGURATION, *PUEYE_ETH_IP_CONFIGURATION;

  // values for UEYE_ETH_DEVICE_INFO_HEARTBEAT::dwDeviceStatusFlags
  typedef enum _UEYE_ETH_DEVICESTATUS
  {
      IS_ETH_DEVSTATUS_READY_TO_OPERATE=            0x00000001, /*!< device is ready to operate */
      IS_ETH_DEVSTATUS_TESTING_IP_CURRENT=          0x00000002, /*!< device is (arp-)probing its current ip */
      IS_ETH_DEVSTATUS_TESTING_IP_PERSISTENT=       0x00000004, /*!< device is (arp-)probing its persistent ip */
      IS_ETH_DEVSTATUS_TESTING_IP_RANGE=            0x00000008, /*!< device is (arp-)probing the autocfg ip range */

      IS_ETH_DEVSTATUS_INAPPLICABLE_IP_CURRENT=     0x00000010, /*!< current ip is inapplicable */
      IS_ETH_DEVSTATUS_INAPPLICABLE_IP_PERSISTENT=  0x00000020, /*!< persistent ip is inapplicable */
      IS_ETH_DEVSTATUS_INAPPLICABLE_IP_RANGE=       0x00000040, /*!< autocfg ip range is inapplicable */

      IS_ETH_DEVSTATUS_UNPAIRED=                    0x00000100, /*!< device is unpaired */
      IS_ETH_DEVSTATUS_PAIRING_IN_PROGRESS=         0x00000200, /*!< device is being paired */
      IS_ETH_DEVSTATUS_PAIRED=                      0x00000400, /*!< device is paired */

      IS_ETH_DEVSTATUS_FORCE_100MBPS=               0x00001000, /*!< device phy is configured to 100 Mbps */
      IS_ETH_DEVSTATUS_NO_COMPORT=                  0x00002000, /*!< device does not support ueye eth comport */

      IS_ETH_DEVSTATUS_RECEIVING_FW_STARTER=        0x00010000, /*!< device is receiving the starter firmware */
      IS_ETH_DEVSTATUS_RECEIVING_FW_RUNTIME=        0x00020000, /*!< device is receiving the runtime firmware */
      IS_ETH_DEVSTATUS_INAPPLICABLE_FW_RUNTIME=     0x00040000, /*!< runtime firmware is inapplicable */
      IS_ETH_DEVSTATUS_INAPPLICABLE_FW_STARTER=     0x00080000, /*!< starter firmware is inapplicable */

      IS_ETH_DEVSTATUS_REBOOTING_FW_RUNTIME=        0x00100000, /*!< device is rebooting to runtime firmware */
      IS_ETH_DEVSTATUS_REBOOTING_FW_STARTER=        0x00200000, /*!< device is rebooting to starter firmware */
      IS_ETH_DEVSTATUS_REBOOTING_FW_FAILSAFE=       0x00400000, /*!< device is rebooting to failsafe firmware */

      IS_ETH_DEVSTATUS_RUNTIME_FW_ERR0=             0x80000000, /*!< checksum error runtime firmware */

  } UEYE_ETH_DEVICESTATUS;

  // heartbeat info transmitted periodically by a device
  // contained in UEYE_ETH_DEVICE_INFO
  typedef struct _UEYE_ETH_DEVICE_INFO_HEARTBEAT
  {
      BYTE                  abySerialNumber[12];        /*!< camera's serial number (string) */

      BYTE                  byDeviceType;               /*!< device type / board type, 0x80 for ETH */
      
      BYTE                  byCameraID;                 /*!< camera id */

      WORD                  wSensorID;                  /*!< camera's sensor's id */

      WORD                  wSizeImgMem_MB;             /*!< size of camera's image memory in MB */

      BYTE                  reserved_1[2];              /*!< reserved */

      DWORD                 dwVerStarterFirmware;       /*!< starter firmware version */

      DWORD                 dwVerRuntimeFirmware;       /*!< runtime firmware version */

      DWORD                 dwStatus;                   /*!< camera status flags */

      BYTE                  reserved_2[4];              /*!< reserved */
      
      WORD                  wTemperature;               /*!< camera temperature */
      
      WORD                  wLinkSpeed_Mb;              /*!< link speed in Mb */

      UEYE_ETH_ADDR_MAC     macDevice;                  /*!< camera's MAC address */
      
      WORD                  wComportOffset;             /*!< comport offset from 100, valid range -99 to +156 */

      UEYE_ETH_IP_CONFIGURATION ipcfgPersistentIpCfg;   /*!< persistent IP configuration */

      UEYE_ETH_IP_CONFIGURATION ipcfgCurrentIpCfg;      /*!< current IP configuration */

      UEYE_ETH_ADDR_MAC     macPairedHost;              /*!< paired host's MAC address */

      BYTE                  reserved_4[2];              /*!< reserved */

      UEYE_ETH_ADDR_IPV4    ipPairedHostIp;             /*!< paired host's IP address */

      UEYE_ETH_ADDR_IPV4    ipAutoCfgIpRangeBegin;      /*!< begin of IP address range */

      UEYE_ETH_ADDR_IPV4    ipAutoCfgIpRangeEnd;        /*!< end of IP address range */

      BYTE                  abyUserSpace[8];            /*!< user space data (first 8 bytes) */

      BYTE                  reserved_5[84];             /*!< reserved */

      BYTE                  reserved_6[64];             /*!< reserved */

  } UEYE_ETH_DEVICE_INFO_HEARTBEAT, *PUEYE_ETH_DEVICE_INFO_HEARTBEAT;

  // values for UEYE_ETH_DEVICE_INFO_CONTROL::dwControlStatus
  typedef enum _UEYE_ETH_CONTROLSTATUS
  {
      IS_ETH_CTRLSTATUS_AVAILABLE=              0x00000001, /*!< device is available TO US */
      IS_ETH_CTRLSTATUS_ACCESSIBLE1=            0x00000002, /*!< device is accessible BY US, i.e. directly 'unicastable' */
      IS_ETH_CTRLSTATUS_ACCESSIBLE2=            0x00000004, /*!< device is accessible BY US, i.e. not on persistent ip and adapters ip autocfg range is valid */

      IS_ETH_CTRLSTATUS_PERSISTENT_IP_USED=     0x00000010, /*!< device is running on persistent ip configuration */
      IS_ETH_CTRLSTATUS_COMPATIBLE=             0x00000020, /*!< device is compatible TO US */
      IS_ETH_CTRLSTATUS_ADAPTER_ON_DHCP=        0x00000040, /*!< adapter is configured to use dhcp */

      IS_ETH_CTRLSTATUS_UNPAIRING_IN_PROGRESS=  0x00000100, /*!< device is being unpaired FROM US */
      IS_ETH_CTRLSTATUS_PAIRING_IN_PROGRESS=    0x00000200, /*!< device is being paired TO US */

      IS_ETH_CTRLSTATUS_PAIRED=                 0x00001000, /*!< device is paired TO US */

      IS_ETH_CTRLSTATUS_FW_UPLOAD_STARTER=      0x00010000, /*!< device is receiving the starter firmware */
      IS_ETH_CTRLSTATUS_FW_UPLOAD_RUNTIME=      0x00020000, /*!< device is receiving the runtime firmware */

      IS_ETH_CTRLSTATUS_REBOOTING=              0x00100000, /*!< device is rebooting */

      IS_ETH_CTRLSTATUS_INITIALIZED=            0x08000000, /*!< device object is initialized */

      IS_ETH_CTRLSTATUS_TO_BE_DELETED=          0x40000000, /*!< device object is being deleted */
      IS_ETH_CTRLSTATUS_TO_BE_REMOVED=          0x80000000, /*!< device object is being removed */

  } UEYE_ETH_CONTROLSTATUS;

  // control info for a listed device
  // contained in UEYE_ETH_DEVICE_INFO
  typedef struct _UEYE_ETH_DEVICE_INFO_CONTROL
  {
      DWORD     dwDeviceID;         /*!< device's unique id */

      DWORD     dwControlStatus;    /*!< device control status */

      BYTE      reserved_1[80];     /*!< reserved */

      BYTE      reserved_2[64];     /*!< reserved */

  } UEYE_ETH_DEVICE_INFO_CONTROL, *PUEYE_ETH_DEVICE_INFO_CONTROL;

  // Ethernet configuration
  typedef struct _UEYE_ETH_ETHERNET_CONFIGURATION
  {
      UEYE_ETH_IP_CONFIGURATION ipcfg;
      UEYE_ETH_ADDR_MAC         mac;

  } UEYE_ETH_ETHERNET_CONFIGURATION, *PUEYE_ETH_ETHERNET_CONFIGURATION;

  // autocfg ip setup
  typedef struct _UEYE_ETH_AUTOCFG_IP_SETUP
  {
      UEYE_ETH_ADDR_IPV4    ipAutoCfgIpRangeBegin;      /*!< begin of ip address range for devices */
      UEYE_ETH_ADDR_IPV4    ipAutoCfgIpRangeEnd;        /*!< end of ip address range for devices */

      BYTE                  reserved[4];    /*!< reserved */

  } UEYE_ETH_AUTOCFG_IP_SETUP, *PUEYE_ETH_AUTOCFG_IP_SETUP;

  // values for incoming packets filter setup
  typedef enum _UEYE_ETH_PACKETFILTER_SETUP
  {
      // notice: arp and icmp (ping) packets are always passed!

      IS_ETH_PCKTFLT_PASSALL=       0,  /*!< pass all packets to OS */
      IS_ETH_PCKTFLT_BLOCKUEGET=    1,  /*!< block UEGET packets to the OS */
      IS_ETH_PCKTFLT_BLOCKALL=      2   /*!< block all packets to the OS */

  } UEYE_ETH_PACKETFILTER_SETUP;

  // values for link speed setup
  typedef enum _UEYE_ETH_LINKSPEED_SETUP
  {
      IS_ETH_LINKSPEED_100MB=		100,    /*!< 100 MBits */
      IS_ETH_LINKSPEED_1000MB=	    1000    /*!< 1000 MBits */

  } UEYE_ETH_LINKSPEED_SETUP;


  // control info for a device's network adapter
  // contained in UEYE_ETH_DEVICE_INFO
  typedef struct _UEYE_ETH_ADAPTER_INFO
  {
      DWORD                             dwAdapterID;        /*!< adapter's unique id */

      DWORD                             dwDeviceLinkspeed;  /*!< device's linked to this adapter are forced to use this link speed */

      UEYE_ETH_ETHERNET_CONFIGURATION   ethcfg;         /*!< adapter's eth configuration */
      BYTE                              reserved_2[2];  /*!< reserved */
      BOOL                              bIsEnabledDHCP; /*!< adapter's dhcp enabled flag */

      UEYE_ETH_AUTOCFG_IP_SETUP         autoCfgIp;                  /*!< the setup for the ip auto configuration */
      BOOL                              bIsValidAutoCfgIpRange;     /*!<    the given range is valid when: 
                                                                            - begin and end are valid ip addresses
                                                                            - begin and end are in the subnet of the adapter
                                                                            - */

      DWORD                             dwCntDevicesKnown;      /*!< count of listed Known devices */
      DWORD                             dwCntDevicesPaired;     /*!< count of listed Paired devices */

      WORD                              wPacketFilter;          /*!< Setting for the Incoming Packets Filter. see UEYE_ETH_PACKETFILTER_SETUP enum above. */

      BYTE                              reserved_3[38];         /*!< reserved */
      BYTE                              reserved_4[64];         /*!< reserved */

  } UEYE_ETH_ADAPTER_INFO, *PUEYE_ETH_ADAPTER_INFO;

  // driver info
  // contained in UEYE_ETH_DEVICE_INFO
  typedef struct _UEYE_ETH_DRIVER_INFO
  {
      DWORD     dwMinVerStarterFirmware;    /*!< minimum version compatible starter firmware */
      DWORD     dwMaxVerStarterFirmware;    /*!< maximum version compatible starter firmware */

      BYTE      reserved_1[8];              /*!< reserved */
      BYTE      reserved_2[64];             /*!< reserved */

  } UEYE_ETH_DRIVER_INFO, *PUEYE_ETH_DRIVER_INFO;



  // use is_GetEthDeviceInfo() to obtain this data.
  typedef struct _UEYE_ETH_DEVICE_INFO
  {
      UEYE_ETH_DEVICE_INFO_HEARTBEAT    infoDevHeartbeat;

      UEYE_ETH_DEVICE_INFO_CONTROL      infoDevControl;

      UEYE_ETH_ADAPTER_INFO             infoAdapter;

      UEYE_ETH_DRIVER_INFO              infoDriver;

  } UEYE_ETH_DEVICE_INFO, *PUEYE_ETH_DEVICE_INFO;


  typedef struct _UEYE_COMPORT_CONFIGURATION
  {
      WORD wComportNumber;

  } UEYE_COMPORT_CONFIGURATION, *PUEYE_COMPORT_CONFIGURATION;


#pragma pack(pop)

  IDSEXP is_GetEthDeviceInfo    (HIDS hf, UEYE_ETH_DEVICE_INFO* pDeviceInfo, UINT uStructSize);
  IDSEXP is_SetPersistentIpCfg  (HIDS hf, UEYE_ETH_IP_CONFIGURATION* pIpCfg, UINT uStructSize);
  IDSEXP is_SetStarterFirmware  (HIDS hf, const CHAR* pcFilepath, UINT uFilepathLen);

  IDSEXP is_SetAutoCfgIpSetup   (INT iAdapterID, const UEYE_ETH_AUTOCFG_IP_SETUP* pSetup, UINT uStructSize);
  IDSEXP is_SetPacketFilter     (INT iAdapterID, UINT uFilterSetting);
  
  IDSEXP is_GetComportNumber    (HIDS hf, UINT *pComportNumber);

  IDSEXP is_DirectRenderer      (HIDS hf, UINT nMode, void *pParam, UINT SizeOfParam);

#ifdef __cplusplus
};
#endif  /* __cplusplus */

#pragma pack(pop)

#endif  // #ifndef __IDS_HEADER__
