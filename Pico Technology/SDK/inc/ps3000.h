/****************************************************************************
 *
 * Filename:    ps3000.h
 * Author:      MTB & MAS
 * Description:
 *
 * This header defines the interface to driver routines for the
 *  PicoScope 3000 Series PC Oscilloscopes.
 *
 * Copyright � 2002 - 2022 Pico Technology Ltd. All rights reserved.
 *
 ****************************************************************************/
#ifndef PS3000_H
#define PS3000_H

#include <stdint.h>

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
#ifdef PREF4
  #undef PREF4
#endif

#ifdef __cplusplus
  #define PREF0 extern "C"
#else
  #define PREF0
#endif

/*  If you are dynamically linking ps3000.dll into your project #define DYNLINK here
 */
#ifdef WIN32
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

#define PS3000_FIRST_USB  1
#if defined (_DEBUG)
#define PS3000_LAST_USB   64
#else
#define PS3000_LAST_USB 127
#endif

/* Maximum number of PS3000 units that can be opened at once
 */
#define PS3000_MAX_UNITS (PS3000_LAST_USB - PS3000_FIRST_USB + 1)

#define PS3206_MAX_TIMEBASE  21
#define PS3205_MAX_TIMEBASE  20
#define PS3204_MAX_TIMEBASE  19
#define PS3224_MAX_TIMEBASE  19
#define PS3223_MAX_TIMEBASE  19
#define PS3424_MAX_TIMEBASE  19
#define PS3423_MAX_TIMEBASE  19

#define PS3225_MAX_TIMEBASE  18
#define PS3226_MAX_TIMEBASE  19
#define PS3425_MAX_TIMEBASE  19
#define PS3426_MAX_TIMEBASE  19

#define PS3000_MAX_OVERSAMPLE 256

/* Although the PS3000 uses an 8-bit ADC, it is usually possible to
 * oversample (collect multiple readings at each time) by up to 256.
 * the results are therefore ALWAYS scaled up to 16-bits, even if
 * oversampling is not used.
 *
 * The maximum and minimum values returned are therefore as follows:
 */

#define PS3000_MAX_VALUE  32767
#define PS3000_MIN_VALUE -32767
#define PS3000_LOST_DATA -32768

/*
 * Signal generator constants. Note that a signal generator is not
 * available on all variants.
 */
#define PS3000_MIN_SIGGEN_FREQ  0.093
#define PS3000_MAX_SIGGEN_FREQ  1000000L

/*
 * ETS constants
 */
#define PS3206_MAX_ETS_CYCLES      500
#define PS3206_MAX_ETS_INTERLEAVE  100

#define PS3205_MAX_ETS_CYCLES      250
#define PS3205_MAX_ETS_INTERLEAVE   50

#define PS3204_MAX_ETS_CYCLES      125
#define PS3204_MAX_ETS_INTERLEAVE   25

#define PS3000_MAX_ETS_CYCLES_INTERLEAVE_RATIO  10
#define PS3000_MIN_ETS_CYCLES_INTERLEAVE_RATIO   1
#define PS300_MAX_ETS_SAMPLES 100000

#define MAX_PULSE_WIDTH_QUALIFIER_COUNT 16777215L
#define MAX_HOLDOFF_COUNT 8388607L

typedef enum enPS3000Channel
{
  PS3000_CHANNEL_A,
  PS3000_CHANNEL_B,
  PS3000_CHANNEL_C,
  PS3000_CHANNEL_D,
  PS3000_EXTERNAL,
  PS3000_MAX_CHANNELS = PS3000_EXTERNAL,
  PS3000_NONE,
  PS3000_MAX_TRIGGER_SOURCES
}  PS3000_CHANNEL;

typedef enum enPS3000Range
{
  PS3000_10MV,
  PS3000_20MV,
  PS3000_50MV,
  PS3000_100MV,
  PS3000_200MV,
  PS3000_500MV,
  PS3000_1V,
  PS3000_2V,
  PS3000_5V,
  PS3000_10V,
  PS3000_20V,
  PS3000_50V,
  PS3000_100V,
  PS3000_200V,
  PS3000_400V,
  PS3000_MAX_RANGES
}  PS3000_RANGE;

typedef enum enPS3000WaveTypes
  {
  PS3000_SQUARE,
  PS3000_TRIANGLE,
  PS3000_SINE,
  PS3000_MAX_WAVE_TYPES
  }  PS3000_WAVE_TYPES;

typedef enum enPS3000TimeUnits
  {
  PS3000_FS,
  PS3000_PS,
  PS3000_NS,
  PS3000_US,
  PS3000_MS,
  PS3000_S,
  PS3000_MAX_TIME_UNITS,
  }  PS3000_TIME_UNITS;

typedef enum enPS3000Error
  {
  PS3000_OK,
  PS3000_MAX_UNITS_OPENED,  // more than PS3000_MAX_UNITS
  PS3000_MEM_FAIL,      //not enough RAM on host machine
  PS3000_NOT_FOUND,      //cannot find device
  PS3000_FW_FAIL,      //unabled to download firmware
  PS3000_NOT_RESPONDING,
  PS3000_CONFIG_FAIL,    //missing or corrupted configuration settings
  PS3000_OS_NOT_SUPPORTED,  //need to use win98SE (or later) or win2k (or later)
  PS3000_PICOPP_TOO_OLD,
  }  PS3000_ERROR;

typedef enum enPS3000Info
{
  PS3000_DRIVER_VERSION,
  PS3000_USB_VERSION,
  PS3000_HARDWARE_VERSION,
  PS3000_VARIANT_INFO,
  PS3000_BATCH_AND_SERIAL,
  PS3000_CAL_DATE,
  PS3000_ERROR_CODE,
  PS3000_KERNEL_DRIVER_VERSION,
  PS3000_DRIVER_PATH
}  PS3000_INFO;

typedef enum enPS3000TriggerDirection
  {
  PS3000_RISING,
  PS3000_FALLING,
  PS3000_MAX_DIRS
  }  PS3000_TDIR;

typedef enum enPS3000OpenProgress
  {
  PS3000_OPEN_PROGRESS_FAIL     = -1,
  PS3000_OPEN_PROGRESS_PENDING  = 0,
  PS3000_OPEN_PROGRESS_COMPLETE = 1
  } PS3000_OPEN_PROGRESS;

typedef enum enPS3000EtsMode
  {
  PS3000_ETS_OFF,                        // ETS disabled
  PS3000_ETS_FAST,                       // Return ready as soon as requested no of interleaves is available
  PS3000_ETS_SLOW,                        // Return ready every time a new set of no_of_cycles is collected
  PS3000_ETS_MODES_MAX
  }  PS3000_ETS_MODE;

typedef int16_t (PREF4 *PS3000_CALLBACK_FUNC)
(
  int16_t *dataBuffer,
  int16_t  noOfBuffers
);

typedef void (PREF4 *GetOverviewBuffersMaxMin)
(
  int16_t **overviewBuffers,
  int16_t   overflow,
  uint32_t  triggeredAt,
  int16_t   triggered,
  int16_t   auto_stop,
  uint32_t  nValues
);

PREF0 PREF1 int16_t PREF2 PREF3(ps3000_open_unit)
(
  void
);

PREF0 PREF1 int16_t PREF2 PREF3(ps3000_get_unit_info)
(
  int16_t  handle,
  int8_t  *string,
  int16_t  string_length,
  int16_t  line
);

PREF0 PREF1 int16_t PREF2 PREF3(ps3000_flash_led)
(
  int16_t  handle
);

PREF0 PREF1 int16_t PREF2 PREF3(ps3000_close_unit)
(
  int16_t  handle
);

PREF0 PREF1 int16_t PREF2 PREF3(ps3000_set_channel)
(
  int16_t  handle,
  int16_t  channel,
  int16_t  enabled,
  int16_t  dc,
  int16_t  range
);

PREF0 PREF1 int16_t PREF2 PREF3(ps3000_get_timebase)
(
  int16_t  handle,
  int16_t  timebase,
  int32_t  no_of_samples,
  int32_t *time_interval,
  int16_t *time_units,
  int16_t  oversample,
  int32_t *max_samples
);

PREF0 PREF1 int32_t PREF2 PREF3(ps3000_set_siggen)
(
  int16_t  handle,
  int16_t  wave_type,
  int32_t  start_frequency,
  int32_t  stop_frequency,
  float    increment,
  int16_t  dwell_time,
  int16_t  repeat,
  int16_t  dual_slope
);

PREF0 PREF1 int32_t PREF2 PREF3(ps3000_set_ets)
(
  int16_t  handle,
  int16_t  mode,
  int16_t  ets_cycles,
  int16_t  ets_interleave
);

PREF0 PREF1 int16_t PREF2 PREF3(ps3000_set_trigger)
(
  int16_t  handle,
  int16_t  source,
  int16_t  threshold,
  int16_t  direction,
  int16_t  delay,
  int16_t  auto_trigger_ms
);

PREF0 PREF1 int16_t PREF2 PREF3(ps3000_set_trigger2)
(
  int16_t  handle,
  int16_t  source,
  int16_t  threshold,
  int16_t  direction,
  float    delay,
  int16_t  auto_trigger_ms
);

PREF0 PREF1 int16_t PREF2 PREF3(ps3000_run_block)
(
  int16_t handle,
  int32_t  no_of_values,
  int16_t  timebase,
  int16_t  oversample,
  int32_t * time_indisposed_ms
);

PREF0 PREF1 int16_t PREF2 PREF3(ps3000_run_streaming_ns)
(
  int16_t            handle,
  uint32_t           sample_interval,
  PS3000_TIME_UNITS  time_units,
  uint32_t           max_samples,
  int16_t            auto_stop,
  uint32_t           noOfSamplesPerAggregate,
  uint32_t           overview_buffer_size
);

PREF0 PREF1 int16_t PREF2 PREF3(ps3000_run_streaming)
(
  int16_t  handle,
  int16_t  sample_interval_ms,
  int32_t  max_samples,
  int16_t  windowed
);

PREF0 PREF1 int16_t PREF2 PREF3(ps3000_ready)
(
  int16_t  handle
);

PREF0 PREF1 int16_t PREF2 PREF3(ps3000_stop)
(
  int16_t  handle
);

PREF0 PREF1 int32_t PREF2 PREF3(ps3000_get_values)
(
  int16_t  handle,
  int16_t *buffer_a,
  int16_t *buffer_b,
  int16_t *buffer_c,
  int16_t *buffer_d,
  int16_t *overflow,
  int32_t  no_of_values
);

PREF0 PREF1 void PREF2 PREF3 (ps3000_release_stream_buffer)
(
  int16_t  handle
);

PREF0 PREF1 int32_t PREF2 PREF3(ps3000_get_times_and_values)
(
  int16_t  handle,
  int32_t *times,
  int16_t *buffer_a,
  int16_t *buffer_b,
  int16_t *buffer_c,
  int16_t *buffer_d,
  int16_t *overflow,
  int16_t  time_units,
  int32_t  no_of_values
);

PREF0 PREF1 int16_t PREF2 PREF3(ps3000_open_unit_async)
(
  void
);

PREF0 PREF1 int16_t PREF2 PREF3(ps3000_open_unit_progress)
(
  int16_t *handle,
  int16_t * progress_percent
);

PREF0 PREF1 int16_t PREF2 PREF3(ps3000_streaming_ns_get_interval_stateless)
(
  int16_t   handle,
  int16_t   nChannels,
  uint32_t *sample_interval
  );

PREF0 PREF1 int16_t PREF2 PREF3(ps3000_get_streaming_last_values)
(
  int16_t                   handle,
  GetOverviewBuffersMaxMin  lpGetOverviewBuffersMaxMin
);

PREF0 PREF1 int16_t PREF2 PREF3 (ps3000_overview_buffer_status)
(
  int16_t  handle,
  int16_t *previous_buffer_overrun
);

PREF0 PREF1 uint32_t PREF2 PREF3(ps3000_get_streaming_values)
(
  int16_t handle,
  double *start_time,
  int16_t  *pbuffer_a_max,
  int16_t  *pbuffer_a_min,
  int16_t  *pbuffer_b_max,
  int16_t  *pbuffer_b_min,
  int16_t  *pbuffer_c_max,
  int16_t  *pbuffer_c_min,
  int16_t  *pbuffer_d_max,
  int16_t  *pbuffer_d_min,
  int16_t  *overflow,
  uint32_t *triggerAt,
  int16_t  *triggered,
  uint32_t  no_of_values,
  uint32_t  noOfSamplesPerAggregate
);

PREF0 PREF1 uint32_t PREF2 PREF3 (ps3000_get_streaming_values_no_aggregation)
(
  int16_t   handle,
  double   *start_time,
  int16_t  *pbuffer_a,
  int16_t  *pbuffer_b,
  int16_t  *pbuffer_c,
  int16_t  *pbuffer_d,
  int16_t  *overflow,
  uint32_t *triggerAt,
  int16_t  *trigger,
  uint32_t  no_of_values
);

PREF0 PREF1 int16_t PREF2 PREF3 (ps3000_save_streaming_data)
(
  int16_t               handle,
  PS3000_CALLBACK_FUNC  lpCallbackFunc,
  int16_t              *dataBuffers,
  int16_t               dataBufferSize
);

//===========================================================
// Adv Trigger
//===========================================================
typedef enum enThresholdDirection
{
  ABOVE,
  BELOW,
  RISING,
  FALLING,
  RISING_OR_FALLING,
  INSIDE = ABOVE,
  OUTSIDE = BELOW,
  ENTER = RISING,
  EXIT = FALLING,
  ENTER_OR_EXIT = RISING_OR_FALLING,
  NONE = RISING
} THRESHOLD_DIRECTION;

typedef enum enThresholdMode
{
  LEVEL,
  WINDOW
} THRESHOLD_MODE;

typedef enum enTriggerState
{
  CONDITION_DONT_CARE,
  CONDITION_TRUE,
  CONDITION_FALSE,
  CONDITION_MAX
} TRIGGER_STATE;

typedef enum enPulseWidthType
{
  PW_TYPE_NONE,
  PW_TYPE_LESS_THAN,
  PW_TYPE_GREATER_THAN,
  PW_TYPE_IN_RANGE,
  PW_TYPE_OUT_OF_RANGE
} PULSE_WIDTH_TYPE;

#pragma pack(1)
typedef struct tTriggerChannelProperties
{
  int16_t thresholdMajor;
  int16_t thresholdMinor;
  uint16_t hysteresis;
  int16_t channel;
  THRESHOLD_MODE thresholdMode;
} TRIGGER_CHANNEL_PROPERTIES;
#pragma pack()

#pragma pack(1)
typedef struct tTriggerConditions
{
  TRIGGER_STATE channelA;
  TRIGGER_STATE channelB;
  TRIGGER_STATE channelC;
  TRIGGER_STATE channelD;
  TRIGGER_STATE external;
  TRIGGER_STATE pulseWidthQualifier;
} TRIGGER_CONDITIONS;
#pragma pack()

#pragma pack(1)
typedef struct tPwqConditions
{
  TRIGGER_STATE channelA;
  TRIGGER_STATE channelB;
  TRIGGER_STATE channelC;
  TRIGGER_STATE channelD;
  TRIGGER_STATE external;
} PWQ_CONDITIONS;
#pragma pack()

PREF0 PREF1 int16_t PREF2 PREF3 (ps3000SetAdvTriggerChannelProperties)
(
  int16_t                     handle,
  TRIGGER_CHANNEL_PROPERTIES *channelProperties,
  int16_t                     nChannelProperties,
  int32_t                     autoTriggerMilliseconds
);

PREF0 PREF1 int16_t PREF2 PREF3 (ps3000SetAdvTriggerChannelConditions)
(
  int16_t              handle,
  TRIGGER_CONDITIONS  *conditions,
  int16_t              nConditions
);

PREF0 PREF1 int16_t PREF2 PREF3 (ps3000SetAdvTriggerChannelDirections)
(
  int16_t              handle,
  THRESHOLD_DIRECTION  channelA,
  THRESHOLD_DIRECTION  channelB,
  THRESHOLD_DIRECTION  channelC,
  THRESHOLD_DIRECTION  channelD,
  THRESHOLD_DIRECTION  ext
);

PREF0 PREF1 int16_t PREF2 PREF3 (ps3000SetPulseWidthQualifier)
(
  int16_t              handle,
  PWQ_CONDITIONS      *conditions,
  int16_t              nConditions,
  THRESHOLD_DIRECTION  direction,
  uint32_t             lower,
  uint32_t             upper,
  PULSE_WIDTH_TYPE     type
);

PREF0 PREF1 int16_t PREF2 PREF3 (ps3000SetAdvTriggerDelay)
(
  int16_t   handle,
  uint32_t  delay,
  float     preTriggerDelay
);

PREF0 PREF1 int16_t PREF2 PREF3 (ps3000PingUnit)
  (
  int16_t  handle
  );

#endif /* not defined PS3000_H */
