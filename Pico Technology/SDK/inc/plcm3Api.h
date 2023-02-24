/**************************************************************************
*
* Filename:    plcm3Api.h
* Author:      MAS
* Description:
*
* This header defines the interface to driver routines for the
* PicoLog CM3 Data Logger.
*
* Copyright © 2011-2018 Pico Technology Ltd. All rights reserved.
*
*************************************************************************/
#ifndef __PLCM3API_H__
#define __PLCM3API_H__

#include <stdint.h>
#include "PicoStatus.h"

#ifdef PREF0
  #undef PREF0
#endif
#ifdef PREF1
  #undef PREF1
#endif
#ifdef PREF2
  #undef PREF2
#endif
#ifdef PREF3
  #undef PREF3
#endif

#ifdef __cplusplus
  #define PREF0 extern "C"
#else
  #define PREF0
#endif

#ifdef WIN32
  //	If you are dynamically linking plcm3.dll into your project #define DYNLINK
  //  somewhere in your project before here.
  #ifdef DYNLINK
    #define PREF1 typedef
    #define PREF2
    #define PREF3(x) (__stdcall *x)
  #else
    #define PREF1
    #ifdef _USRDLL
      #define PREF2 __declspec(dllexport) __stdcall
    #else
      #define PREF2 __declspec(dllimport) __stdcall
    #endif
    #define PREF3(x) x
  #endif
#else
/* Define a 64-bit integer type */
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
#endif

#define PLCM3_MIN_WIRES 2
#define PLCM3_MAX_WIRES 4

typedef enum enPLCM3Channels
{
  PLCM3_CHANNEL_1 = 1,
  PLCM3_CHANNEL_2,
  PLCM3_CHANNEL_3,
  PLCM3_MAX_CHANNELS = PLCM3_CHANNEL_3
} PLCM3_CHANNELS;

typedef enum enPLCM3DataType
{
  PLCM3_OFF,
  PLCM3_1_MILLIVOLT,
  PLCM3_10_MILLIVOLTS,
  PLCM3_100_MILLIVOLTS,
  PLCM3_VOLTAGE,
PLCM3_MAX_DATA_TYPES
} PLCM3_DATA_TYPES;

typedef enum enPLCM3IpDetailsType
{
  PLCM3_IDT_GET,
  PLCM3_IDT_SET,
} PLCM3_IP_DETAILS_TYPE;

typedef enum enPLCM3CommunicationType
{
  PLCM3_CT_USB = 0x00000001,
  PLCM3_CT_ETHERNET = 0x00000002,
  PLCM3_CT_ALL = 0xFFFFFFFF
}PLCM3_COMMUNICATION_TYPE;

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (PLCM3Enumerate)
(
  int8_t   *details,
  uint32_t *length,
  PLCM3_COMMUNICATION_TYPE type
);

PREF0 PREF1 PICO_STATUS PREF2  PREF3 (PLCM3OpenUnit)
(
  int16_t * handle,
  int8_t  * serial
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (PLCM3OpenUnitViaIp)
(
  int16_t * handle,
  int8_t  * serial,
  int8_t  * ipAddress
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (PLCM3CloseUnit)
(
  int16_t handle
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (PLCM3IpDetails)
(
  int16_t   handle,
  int16_t  *enabled,
  int8_t   *ipaddress,
  uint16_t *length,
  uint16_t *listeningPort,
  PLCM3_IP_DETAILS_TYPE type
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (PLCM3GetUnitInfo)
(
  int16_t handle,
  int8_t * string,
  int16_t stringLength,
  int16_t * requiredSize,
  PICO_INFO info
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (PLCM3SetChannel)
(
  int16_t handle,
  PLCM3_CHANNELS channel,
  PLCM3_DATA_TYPES type
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (PLCM3SetMains)
(
  int16_t handle,
  uint16_t sixtyHertz
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (PLCM3GetValue)
(
  int16_t handle,
  PLCM3_CHANNELS channel,
  int32_t * value
);
#endif
