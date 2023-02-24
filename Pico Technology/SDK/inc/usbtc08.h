/*********************************************************************
 *
 * Filename:    usbtc08.h
 * Author:      SDI & MAS
 * Description:
 *
 * This header defines the interface to driver routines for the
 * USB TC-08 Thermocouple Data Loggers.
 *
 * History:	12May03 SDI Created
 *
 * Copyright � 2002 - 2022 Pico Technology Ltd. All rights reserved.
 *
 *********************************************************************/
#ifndef __USBTC08_H__
#define __USBTC08_H__


#include <stdint.h>

#ifdef __cplusplus
  #define PREF0 extern "C"
#else
  #define PREF0
#endif

#ifdef WIN32
  #ifdef PREF1
    #undef PREF1
  #endif
  #ifdef PREF2
    #undef PREF2
  #endif
  #ifdef PREF3
    #undef PREF3
  #endif
  /*	If you are dynamically linking usbtc08.dll into your project #define DYNLINK here
  */
  #ifdef DYNLINK
    #define PREF1 typedef
    #define PREF2
    #define PREF3(x) (__stdcall *x)
  #else
    #define PREF1
    #ifdef _USRDLL
      #define PREF2 __declspec (dllexport) __stdcall
    #else
      #define PREF2 __declspec (dllimport) __stdcall
    #endif
    #define PREF3(x) x
  #endif
#else
  #ifdef DYNLINK
    #define PREF1 typedef
    #define PREF2
    #define PREF3(x) (*x)
  #else
    #ifdef _USRDLL
      #define PREF1 __attribute__((visibility("default")))
    #else
      #define PREF1
    #endif
    #define PREF2
    #define PREF3(x) x
  #endif
  #define __stdcall
#endif


/* General Defines **************************************************/
#define USBTC08_MAX_FILTER_SIZE   255
#define USBTC08_MAX_SAMPLE_BUFFER 600 /* Max readings that usb_tc08_get_temp will ever return */
#define USBTC08_MAX_INFO_CHARS    256
#define USBTC08_MAX_DATE_CHARS    9
#define USBTC08_MAX_SERIAL_CHARS  11
#define USBTC08_MAX_VERSION_CHARS 12


/* Enumerations *****************************************************/

/* There are 8 channels from 1 to 8
 *  to enumerate them, use:
 *
 *  for (i = 1; i <= USBTC08_MAX_CHANNELS; i++)
 *
 *  the Cold Junction Compensation is channel 0
 */
typedef enum enUSBTC08Channels
{
  USBTC08_CHANNEL_CJC,
  USBTC08_CHANNEL_1,
  USBTC08_CHANNEL_2,
  USBTC08_CHANNEL_3,
  USBTC08_CHANNEL_4,
  USBTC08_CHANNEL_5,
  USBTC08_CHANNEL_6,
  USBTC08_CHANNEL_7,
  USBTC08_CHANNEL_8,
  USBTC08_MAX_CHANNELS = USBTC08_CHANNEL_8
} USBTC08_CHANNELS;

typedef enum enUSBTC08Progress
{
  USBTC08_PROGRESS_FAIL     = -1,
  USBTC08_PROGRESS_PENDING  = 0,
  USBTC08_PROGRESS_COMPLETE = 1
} USBTC08_PROGRESS;

typedef enum enUSBTC08Error
{
  /*========================
  User/Developer error codes
  =========================*/
  USBTC08_ERROR_OK,
  USBTC08_ERROR_OS_NOT_SUPPORTED,	      /* need to use win98 (or later) or win2k (or later) */
  USBTC08_ERROR_NO_CHANNELS_SET,
  USBTC08_ERROR_INVALID_PARAMETER,      /* one or more of the function arguments was invalid */
  USBTC08_ERROR_VARIANT_NOT_SUPPORTED,  /* the hardware version is not supported (download the latest driver) */
  USBTC08_ERROR_INCORRECT_MODE,         /* an incompatible mix of legacy and non-legacy functions was called
                                           ... or usb_tc08_get_single was called while streaming was active */
  USBTC08_ERROR_ENUMERATION_INCOMPLETE, /* a second call to usb_tc08_open_unit_async() was made before
                                           asynchronous enumeration had completed */

  /*=======================
  Reserved Pico error codes
  ========================*/
  USBTC08_ERROR_NOT_RESPONDING,         /* unit is not responding to the driver */
  USBTC08_ERROR_FW_FAIL,                /* unabled to download firmware */
  USBTC08_ERROR_CONFIG_FAIL,		        /* missing or corrupted eeprom */
  USBTC08_ERROR_NOT_FOUND,			        /* cannot find enumerated device */
  USBTC08_ERROR_THREAD_FAIL,            /* a threading function failed */
  USBTC08_ERROR_PIPE_INFO_FAIL,         /* could not get pipes from the device */
  USBTC08_ERROR_NOT_CALIBRATED,          /* no calibration date was found */
  USBTC08_EROOR_PICOPP_TOO_OLD,
	USBTC08_ERROR_PICOPP_TOO_OLD = USBTC08_EROOR_PICOPP_TOO_OLD,
	USBTC08_ERROR_PICO_DRIVER_FUNCTION,

  /*===========================
  New User/Developererror codes
  ============================*/
  USBTC08_ERROR_COMMUNICATION           /*the PC has lost communication with unit*/
}	USBTC08_ERROR;

typedef enum enUSBTC08Units
{
  USBTC08_UNITS_CENTIGRADE,
  USBTC08_UNITS_FAHRENHEIT,
  USBTC08_UNITS_KELVIN,
  USBTC08_UNITS_RANKINE,
  USBTC08_MAX_UNITS = USBTC08_UNITS_RANKINE
} USBTC08_UNITS;

typedef enum enUSBTC08InfoLine
{
  USBTC08LINE_DRIVER_VERSION,
  USBTC08LINE_KERNEL_DRIVER_VERSION,
  USBTC08LINE_HARDWARE_VERSION,
  USBTC08LINE_VARIANT_INFO,
  USBTC08LINE_BATCH_AND_SERIAL,
  USBTC08LINE_CAL_DATE,
  USBTC08LINE_DRIVER_PATH
} USBTC08_INFO_LINE;

/* Structures *****************************************************/

typedef struct tUSBTC08Info
{
  int16_t size;
  int8_t  DriverVersion[USBTC08_MAX_VERSION_CHARS];
  int16_t PicoppVersion;
  int16_t HardwareVersion;
  int16_t Variant;
  int8_t  szSerial[USBTC08_MAX_SERIAL_CHARS];
  int8_t  szCalDate[USBTC08_MAX_DATE_CHARS];
} USBTC08_INFO, *LPUSBTC08_INFO;


/*====================================================================
    New USB TC08 API Calls

    This set of functions should be used in preference to the
    Legacy API calls at the bottom of this header file
    (see also 'Shared API Calls' which are designed to be used
    with the new API calls, but can also be used with legacy calls)
=====================================================================*/

PREF0 PREF1 int16_t PREF2 PREF3(usb_tc08_set_channel)
(
  int16_t handle,
  int16_t channel,
  int8_t  tc_type
);

PREF0 PREF1 int32_t PREF2 PREF3(usb_tc08_run)
(
  int16_t handle,
  int32_t interval_ms
);

/* must be called at least once per minute to ensure no data is lost */
PREF0 PREF1 int32_t PREF2 PREF3(usb_tc08_get_temp)
(
  int16_t  handle,
  float   *temp_buffer,
  int32_t *times_ms_buffer, /* wraps back to zero after 24 days */
  int32_t  buffer_length,
  int16_t *overflow,
  int16_t  channel,
  int16_t  units,
  int16_t  fill_missing
);

PREF0 PREF1 int32_t PREF2 PREF3(usb_tc08_get_temp_deskew)
(
  int16_t  handle,
  float   *temp_buffer,
  int32_t *times_ms_buffer, /* wraps back to zero after 24 days */
  int32_t  buffer_length,
  int16_t *overflow,
  int16_t  channel,
  int16_t  units,
  int16_t  fill_missing
);

PREF0 PREF1 int16_t PREF2 PREF3(usb_tc08_get_single)
(
  int16_t  handle,
  float   *temp,
  int16_t *overflow_flags,
  int16_t  units
);

/*==========================================================================
    Shared API Calls

    These functions are designed for use with the USB TC08,
    however, they can (and should) still be used with the legacy API calls
===========================================================================*/

PREF0 PREF1 int16_t PREF2 PREF3(usb_tc08_open_unit)
(
  void
);

/* These two functions are used instead of usb_tc08_open_unit()
 * if the calling application needs to perform operations while
 * waiting for a unit to open
 */
PREF0 PREF1 int16_t PREF2 PREF3(usb_tc08_open_unit_async)
(
  void
);

PREF0 PREF1 int16_t PREF2 PREF3(usb_tc08_open_unit_progress)
(
  int16_t *handle,
  int16_t *percent_progress
);

PREF0 PREF1 int16_t PREF2 PREF3(usb_tc08_close_unit)
(
  int16_t handle
);

PREF0 PREF1 int16_t PREF2 PREF3(usb_tc08_stop)
(
  int16_t handle
);

PREF0 PREF1 int16_t PREF2 PREF3(usb_tc08_set_mains)
(
  int16_t handle,
  int16_t sixty_hertz
);

/* set-up all channels before calling this
 * in legacy mode, this will be the fixed sampling rate
 */
PREF0 PREF1 int32_t PREF2 PREF3(usb_tc08_get_minimum_interval_ms)
(
  int16_t handle
);

PREF0 PREF1 int16_t PREF2 PREF3(usb_tc08_get_unit_info)
(
  int16_t handle, USBTC08_INFO * info
);

PREF0 PREF1 int16_t PREF2 PREF3(usb_tc08_get_unit_info2)
(
  int16_t  handle,
  int8_t  *string,
  int16_t  string_length,
  int16_t  line
);

PREF0 PREF1 int16_t PREF2 PREF3(usb_tc08_get_formatted_info)
(
  int16_t  handle,
  int8_t  *unit_info,
  int16_t  string_length);

/* pass 0 as the unit handle to get the last reason
 * that usb_tc08_open_unit() failed
 */
PREF0 PREF1 int16_t PREF2 PREF3(usb_tc08_get_last_error)
(
  int16_t handle
);

/*====================================================================
    Legacy API Calls

    Provided to aid backwards compatibility with code written
    for old TC08 Units (differences exist).

    These functions should not be used in new code and are
    deprecated for removal in a future version of the driver.
=====================================================================*/

/* Legacy defines
 */
#define CHANNELS_PER_TC08 8
#define MAX_TC08_UNITS    64

PREF0 PREF1 int16_t PREF2 PREF3(usb_tc08_legacy_run)
(
  int16_t handle
);

PREF0 PREF1 int16_t PREF2 PREF3(usb_tc08_legacy_set_channel)
(
  int16_t handle,
  int16_t channel,
  int8_t  tc_type,
  int16_t filter_factor,
  int16_t offset,
  int16_t slope
);

PREF0 PREF1 int16_t PREF2 PREF3(usb_tc08_legacy_get_temp)
(
  int32_t  *temp,
  int16_t   handle,
  uint16_t  channel,
  uint16_t  filtered
);

PREF0 PREF1 int16_t PREF2 PREF3(usb_tc08_legacy_get_cold_junction)
(
  int32_t * temp,
  int16_t handle
);

PREF0 PREF1 int16_t PREF2 PREF3(usb_tc08_legacy_get_driver_version)
(
  void
);

PREF0 PREF1 int16_t PREF2 PREF3(usb_tc08_legacy_get_version)
(
  int16_t *version,
  int16_t handle
);

PREF0 PREF1 int16_t PREF2 PREF3(usb_tc08_legacy_get_cycle)
(
  int32_t *cycle,
  int16_t handle
);

#endif
