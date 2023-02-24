/**************************************************************************
*
* Filename:    pl1000Api.h
* Author:      MB & MAS
* Description:
*
* This header defines the interface to driver routines for the
* PicoLog 1000 Series Data Loggers.
*
* Copyright © 2009-2018 Pico Technology Ltd. All rights reserved.
*
*************************************************************************/
#ifndef __PL1000API_H__
#define  __PL1000API_H__

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
	//	If you are dynamically linking pl1000.dll into your project #define DYNLINK
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
  #define PREF4 __stdcall
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
  #define PREF4
#endif


typedef enum enPL1000Inputs
{
  PL1000_CHANNEL_1 = 1,
  PL1000_CHANNEL_2,
  PL1000_CHANNEL_3,
  PL1000_CHANNEL_4,
  PL1000_CHANNEL_5,
  PL1000_CHANNEL_6,
  PL1000_CHANNEL_7,
  PL1000_CHANNEL_8,
  PL1000_CHANNEL_9,
  PL1000_CHANNEL_10,
  PL1000_CHANNEL_11,
	PL1000_CHANNEL_12,
	PL1000_CHANNEL_13,
	PL1000_CHANNEL_14,
	PL1000_CHANNEL_15,
	PL1000_CHANNEL_16,
	PL1000_MAX_CHANNELS = PL1000_CHANNEL_16
} PL1000_INPUTS;

typedef enum enPL1000DO_Channel
{
	PL1000_DO_CHANNEL_0,
	PL1000_DO_CHANNEL_1,
	PL1000_DO_CHANNEL_2,
	PL1000_DO_CHANNEL_3,
	PL1000_DO_CHANNEL_MAX
} PL1000_DO_CH;

typedef enum enPL1000OpenProgress
{
  PL1000_OPEN_PROGRESS_FAIL     = -1,
  PL1000_OPEN_PROGRESS_PENDING  = 0,
  PL1000_OPEN_PROGRESS_COMPLETE = 1
} PL1000_OPEN_PROGRESS;

#define PL1000_MIN_PERIOD 100
#define PL1000_MAX_PERIOD 1800


#ifndef BM_DEFINED
#define BM_DEFINED
typedef enum _BLOCK_METHOD{BM_SINGLE, BM_WINDOW, BM_STREAM} BLOCK_METHOD;
#endif

PREF0 PREF1 PICO_STATUS PREF2  PREF3 (pl1000OpenUnit) (int16_t * handle);

PREF0 PREF1 PICO_STATUS PREF2  PREF3 (pl1000CloseUnit) (int16_t handle);

PREF0 PREF1 PICO_STATUS PREF2  PREF3 (pl1000GetUnitInfo)
	(int16_t handle, int8_t * string, int16_t stringLength, int16_t * requiredSize, PICO_INFO info);

PREF0 PREF1 PICO_STATUS PREF2  PREF3 (pl1000SetDo) (int16_t handle, int16_t do_value, int16_t doNo);

PREF0 PREF1 PICO_STATUS PREF2  PREF3 (pl1000SetPulseWidth) (int16_t handle, uint16_t period, uint8_t cycle);

PREF0 PREF1 PICO_STATUS PREF2  PREF3 (pl1000Run) (int16_t handle, uint32_t no_of_values, BLOCK_METHOD method);

PREF0 PREF1 PICO_STATUS PREF2  PREF3 (pl1000Ready) (int16_t handle, int16_t * ready);

PREF0 PREF1 PICO_STATUS PREF2  PREF3 (pl1000Stop) (int16_t handle);

PREF0 PREF1 PICO_STATUS PREF2  PREF3 (pl1000MaxValue) (int16_t handle, uint16_t *maxValue);

PREF0 PREF1 PICO_STATUS PREF2  PREF3 (pl1000SetInterval)
	(int16_t handle, uint32_t * us_for_block, uint32_t ideal_no_of_samples, int16_t * channels,int16_t no_of_channels);

PREF0 PREF1 PICO_STATUS PREF2  PREF3 (pl1000SetTrigger)
	(int16_t handle, uint16_t enabled, uint16_t auto_trigger, uint16_t auto_ms, uint16_t channel, uint16_t dir, uint16_t threshold, uint16_t hysterisis, float delay);

PREF0 PREF1 PICO_STATUS PREF2  PREF3 (pl1000GetValues)
	(int16_t handle, uint16_t * values, uint32_t * noOfValues, uint16_t * overflow, uint32_t * triggerIndex);

PREF0 PREF1 PICO_STATUS PREF2  PREF3 (pl1000GetTriggerTimeOffsetNs)	(int16_t handle, int64_t * time);

PREF0 PREF1 PICO_STATUS PREF2  PREF3 (pl1000GetSingle) (int16_t handle, PL1000_INPUTS channel, uint16_t *value);

PREF0 PREF1 PICO_STATUS PREF2  PREF3 (pl1000OpenUnitAsync) (int16_t * status);

PREF0 PREF1 PICO_STATUS PREF2  PREF3 (pl1000OpenUnitProgress) (int16_t * handle, int16_t * progress, int16_t * complete);

PREF0 PREF1 PICO_STATUS PREF2  PREF3 (pl1000PingUnit) (int16_t handle);

#endif
