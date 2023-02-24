/**************************************************************************
*
* Filename:    usbPT104Api.h
* Author:      MAS
* Description:
*
* This header defines the interface to driver routines for the
* USB PT-104 Platinum Resistance Temperature Data Logger.
*
* Copyright � 2009 - 2022 Pico Technology Ltd. All rights reserved.
*
*************************************************************************/
#ifndef __USBPT104API_H__
#define __USBPT104API_H__

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
  //	If you are dynamically linking usbpt104.DLL into your project #define DYNLINK
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

#define USBPT104_MIN_WIRES 2
#define USBPT104_MAX_WIRES 4

typedef enum enUsbPt104Channels
{
  USBPT104_CHANNEL_1 = 1,
  USBPT104_CHANNEL_2,
  USBPT104_CHANNEL_3,
  USBPT104_CHANNEL_4,
  USBPT104_CHANNEL_5,
  USBPT104_CHANNEL_6,
  USBPT104_CHANNEL_7,
  USBPT104_CHANNEL_8,
	USBPT104_MAX_CHANNELS = USBPT104_CHANNEL_8
} USBPT104_CHANNELS;


typedef enum enUsbPt104DataType
{
  USBPT104_OFF,
  USBPT104_PT100,
  USBPT104_PT1000,
  USBPT104_RESISTANCE_TO_375R,
  USBPT104_RESISTANCE_TO_10K,
  USBPT104_DIFFERENTIAL_TO_115MV,
  USBPT104_DIFFERENTIAL_TO_2500MV,
  USBPT104_SINGLE_ENDED_TO_115MV,
  USBPT104_SINGLE_ENDED_TO_2500MV,
  USBPT104_MAX_DATA_TYPES
} USBPT104_DATA_TYPES;

typedef enum enIpDetailsType
{
  IDT_GET,
  IDT_SET,
} IP_DETAILS_TYPE;

typedef enum enCommunicationType
{
  CT_USB = 0x00000001,
  CT_ETHERNET = 0x00000002,
  CT_ALL = 0xFFFFFFFF
}COMMUNICATION_TYPE;

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (UsbPt104Enumerate)
(
  int8_t   *details,
  uint32_t *length,
  COMMUNICATION_TYPE type
);

PREF0 PREF1 PICO_STATUS PREF2  PREF3 (UsbPt104OpenUnit)
(
  int16_t *handle,
  int8_t  *serial
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (UsbPt104OpenUnitViaIp)
(
  int16_t *handle,
  int8_t  *serial,
  int8_t  *ipAddress
);

PREF0 PREF1 PICO_STATUS PREF2  PREF3 (UsbPt104CloseUnit)
(
  int16_t handle
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (UsbPt104IpDetails)
(
  int16_t   handle,
  int16_t  *enabled,
  int8_t   *ipaddress,
  uint16_t *length,
  uint16_t *listeningPort,
  IP_DETAILS_TYPE type
);

PREF0 PREF1 PICO_STATUS PREF2  PREF3 (UsbPt104GetUnitInfo)
(
  int16_t    handle,
  int8_t    *string,
  int16_t    stringLength,
  int16_t   *requiredSize,
  PICO_INFO  info
);

PREF0 PREF1 PICO_STATUS PREF2  PREF3 (UsbPt104SetChannel)
(
  int16_t              handle,
  USBPT104_CHANNELS    channel,
  USBPT104_DATA_TYPES  type,
  int16_t              noOfWires
);

PREF0 PREF1 PICO_STATUS PREF2  PREF3 (UsbPt104SetMains)
(
  int16_t  handle,
  uint16_t sixtyHertz
);

PREF0 PREF1 PICO_STATUS PREF2  PREF3 (UsbPt104GetValue)
(
  int16_t            handle,
  USBPT104_CHANNELS  channel,
  int32_t           *value,
  int16_t            filtered
);

#endif
