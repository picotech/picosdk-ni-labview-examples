/****************************************************************************
 *
 * Filename:    ps2000.h
 * Author:      MTB & MAS
 * Description:
 *
 * This header defines the interface to driver routines for the
 *  PicoScope 2000 Series PC Oscilloscopes.
 *
 * Copyright � 2005 - 2022 Pico Technology Ltd. All rights reserved.
 *
 ****************************************************************************/
#ifndef PS2000_H
#define PS2000_H

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

/*  If you are dynamically linking ps2000.dll into your project #define DYNLINK here
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

#define PS2000_FIRST_USB  1
#define PS2000_LAST_USB   127

/* Maximum number of PS2000 units that can be opened at once
 */
#define PS2000_MAX_UNITS (PS2000_LAST_USB - PS2000_FIRST_USB + 1)

#define PS2000_MAX_TIMEBASE  19

#define PS2105_MAX_TIMEBASE 20
#define PS2104_MAX_TIMEBASE 19

#define PS2200_MAX_TIMEBASE 23

#define PS2000_MAX_OVERSAMPLE 256

#define PS2105_MAX_ETS_CYCLES  250
#define PS2105_MAX_ETS_INTERLEAVE  50

#define PS2104_MAX_ETS_CYCLES  125
#define PS2104_MAX_ETS_INTERLEAVE  25

#define PS2203_MAX_ETS_CYCLES  250
#define PS2203_MAX_ETS_INTERLEAVE 50

#define PS2204_MAX_ETS_CYCLES  250
#define PS2204_MAX_ETS_INTERLEAVE 40

#define PS2205_MAX_ETS_CYCLES  250
#define PS2205_MAX_ETS_INTERLEAVE 40

#define PS2000_MIN_ETS_CYCLES_INTERLEAVE_RATIO 1
#define PS2000_MAX_ETS_CYCLES_INTERLEAVE_RATIO  10

#define PS2000_MIN_SIGGEN_FREQ 0.0f
#define PS2000_MAX_SIGGEN_FREQ 100000.0f


/* Although the PS2000 uses an 8-bit ADC, it is usually possible to
 * oversample (collect multiple readings at each time) by up to 256.
 * the results are therefore ALWAYS scaled up to 16-bits, even if
 * oversampling is not used.
 *
 * The maximum and minimum values returned are therefore as follows:
 */

#define PS2000_MAX_VALUE 32767
#define PS2000_MIN_VALUE -32767
#define PS2000_LOST_DATA -32768

typedef enum enPS2000Channel
{
  PS2000_CHANNEL_A,
  PS2000_CHANNEL_B,
  PS2000_CHANNEL_C,
  PS2000_CHANNEL_D,
  PS2000_EXTERNAL,
  PS2000_MAX_CHANNELS = PS2000_EXTERNAL,
  PS2000_NONE,
}  PS2000_CHANNEL;

typedef enum enPS2000Range
{
  PS2000_10MV,
  PS2000_20MV,
  PS2000_50MV,
  PS2000_100MV,
  PS2000_200MV,
  PS2000_500MV,
  PS2000_1V,
  PS2000_2V,
  PS2000_5V,
  PS2000_10V,
  PS2000_20V,
  PS2000_50V,
  PS2000_MAX_RANGES
}  PS2000_RANGE;

typedef enum enPS2000TimeUnits
  {
  PS2000_FS,
  PS2000_PS,
  PS2000_NS,
  PS2000_US,
  PS2000_MS,
  PS2000_S,
  PS2000_MAX_TIME_UNITS,
  }  PS2000_TIME_UNITS;

typedef enum enPS2000Error
  {
  PS2000_OK,
  PS2000_MAX_UNITS_OPENED,  // more than PS2000_MAX_UNITS
  PS2000_MEM_FAIL,          //not enough RAM on host machine
  PS2000_NOT_FOUND,         //cannot find device
  PS2000_FW_FAIL,           //unabled to download firmware
  PS2000_NOT_RESPONDING,
  PS2000_CONFIG_FAIL,       //missing or corrupted configuration settings
  PS2000_OS_NOT_SUPPORTED,  //need to use win98SE (or later) or win2k (or later)
  PS2000_PICOPP_TOO_OLD,
  }  PS2000_ERROR;

typedef enum enPS2000Info
{
  PS2000_DRIVER_VERSION,
  PS2000_USB_VERSION,
  PS2000_HARDWARE_VERSION,
  PS2000_VARIANT_INFO,
  PS2000_BATCH_AND_SERIAL,
  PS2000_CAL_DATE,
  PS2000_ERROR_CODE,
  PS2000_KERNEL_DRIVER_VERSION,
  PS2000_DRIVER_PATH
}  PS2000_INFO;

typedef enum enPS2000TriggerDirection
  {
  PS2000_RISING,
  PS2000_FALLING,
  PS2000_MAX_DIRS
  }  PS2000_TDIR;

typedef enum enPS2000OpenProgress
  {
  PS2000_OPEN_PROGRESS_FAIL     = -1,
  PS2000_OPEN_PROGRESS_PENDING  =  0,
  PS2000_OPEN_PROGRESS_COMPLETE =  1
  } PS2000_OPEN_PROGRESS;

typedef enum enPS2000EtsMode
  {
  PS2000_ETS_OFF,   // ETS disabled
  PS2000_ETS_FAST,  // Return ready as soon as requested no of interleaves is available
  PS2000_ETS_SLOW,  // Return ready every time a new set of no_of_cycles is collected
  PS2000_ETS_MODES_MAX
  }  PS2000_ETS_MODE;

typedef enum enPS2000ButtonState
  {
  PS2000_NO_PRESS,
  PS2000_SHORT_PRESS,
  PS2000_LONG_PRESS
  } PS2000_BUTTON_STATE;

typedef enum enPS2000SweepType
{
  PS2000_UP,
  PS2000_DOWN,
  PS2000_UPDOWN,
  PS2000_DOWNUP,
  MAX_SWEEP_TYPES
} PS2000_SWEEP_TYPE;

typedef enum enPS2000WaveType
{
  PS2000_SINE,
  PS2000_SQUARE,
  PS2000_TRIANGLE,
  PS2000_RAMPUP,
  PS2000_RAMPDOWN,
  PS2000_DC_VOLTAGE,
  PS2000_GAUSSIAN,
  PS2000_SINC,
  PS2000_HALF_SINE,
} PS2000_WAVE_TYPE;

typedef void (PREF4 *GetOverviewBuffersMaxMin)
(
  int16_t **overviewBuffers,
  int16_t   overflow,
  uint32_t  triggeredAt,
  int16_t   triggered,
  int16_t   auto_stop,
  uint32_t  nValues
);

PREF0 PREF1 int16_t PREF2 PREF3(ps2000_open_unit)
(
  void
);

PREF0 PREF1 int16_t PREF2 PREF3(ps2000_get_unit_info)
(
  int16_t  handle,
  int8_t  *string,
  int16_t  string_length,
  int16_t  line
);

PREF0 PREF1 int16_t PREF2 PREF3(ps2000_flash_led)
(
  int16_t handle
);

PREF0 PREF1 int16_t PREF2 PREF3(ps2000_close_unit)
(
  int16_t handle
);

PREF0 PREF1 int16_t PREF2 PREF3(ps2000_set_channel)
(
  int16_t  handle,
  int16_t  channel,
  int16_t  enabled,
  int16_t  dc,
  int16_t  range
);

PREF0 PREF1 int16_t PREF2 PREF3(ps2000_get_timebase)
(
  int16_t  handle,
  int16_t  timebase,
  int32_t  no_of_samples,
  int32_t *time_interval,
  int16_t *time_units,
  int16_t  oversample,
  int32_t *max_samples
);

PREF0 PREF1 int16_t PREF2 PREF3(ps2000_set_trigger)
(
  int16_t  handle,
  int16_t  source,
  int16_t  threshold,
  int16_t  direction,
  int16_t  delay,
  int16_t  auto_trigger_ms
);

PREF0 PREF1 int16_t PREF2 PREF3(ps2000_set_trigger2)
(
  int16_t  handle,
  int16_t  source,
  int16_t  threshold,
  int16_t  direction,
  float    delay,
  int16_t  auto_trigger_ms
);

PREF0 PREF1 int16_t PREF2 PREF3(ps2000_run_block)
(
  int16_t handle,
  int32_t  no_of_values,
  int16_t  timebase,
  int16_t  oversample,
  int32_t * time_indisposed_ms
);

PREF0 PREF1 int16_t PREF2 PREF3(ps2000_run_streaming)
(
  int16_t  handle,
  int16_t  sample_interval_ms,
  int32_t  max_samples,
  int16_t  windowed
);

PREF0 PREF1 int16_t PREF2 PREF3(ps2000_run_streaming_ns)
(
  int16_t            handle,
  uint32_t           sample_interval,
  PS2000_TIME_UNITS  time_units,
  uint32_t           max_samples,
  int16_t            auto_stop,
  uint32_t           noOfSamplesPerAggregate,
  uint32_t           overview_buffer_size);

PREF0 PREF1 int16_t PREF2 PREF3(ps2000_ready)
(
  int16_t  handle
);

PREF0 PREF1 int16_t PREF2 PREF3(ps2000_stop)
(
  int16_t  handle
);

PREF0 PREF1 int32_t PREF2 PREF3(ps2000_get_values)
(
  int16_t  handle,
  int16_t *buffer_a,
  int16_t *buffer_b,
  int16_t *buffer_c,
  int16_t *buffer_d,
  int16_t *overflow,
  int32_t  no_of_values
);

PREF0 PREF1 int32_t PREF2 PREF3(ps2000_get_times_and_values)
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

PREF0 PREF1 int16_t PREF2 PREF3(ps2000_last_button_press)
(
  int16_t  handle
);

PREF0 PREF1 int32_t PREF2 PREF3(ps2000_set_ets)
(
  int16_t  handle,
  int16_t  mode,
  int16_t  ets_cycles,
  int16_t  ets_interleave
);

PREF0 PREF1 int16_t PREF2 PREF3(ps2000_set_led)
(
  int16_t  handle,
  int16_t  state
);

PREF0 PREF1 int16_t PREF2 PREF3(ps2000_open_unit_async)
(
  void
);

PREF0 PREF1 int16_t PREF2 PREF3(ps2000_open_unit_progress)
(
  int16_t *handle,
  int16_t *progress_percent
);

PREF0 PREF1 int16_t PREF2 PREF3 (ps2000_get_streaming_last_values)
(
  int16_t  handle,
  GetOverviewBuffersMaxMin
);

PREF0 PREF1 int16_t PREF2 PREF3 (ps2000_overview_buffer_status)
(
  int16_t  handle,
  int16_t *previous_buffer_overrun
);

PREF0 PREF1 uint32_t PREF2 PREF3 (ps2000_get_streaming_values)
(
  int16_t  handle,
  double   *start_time,
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

PREF0 PREF1 uint32_t PREF2 PREF3 (ps2000_get_streaming_values_no_aggregation)
(
  int16_t handle,
  double *start_time,
  int16_t * pbuffer_a,
  int16_t * pbuffer_b,
  int16_t * pbuffer_c,
  int16_t * pbuffer_d,
  int16_t * overflow,
  uint32_t * triggerAt,
  int16_t * trigger,
  uint32_t no_of_values
);

PREF0 PREF1 int16_t PREF2 PREF3(ps2000_set_light)
(
  int16_t  handle,
  int16_t  state
);

PREF0 PREF1 int16_t PREF2 PREF3(ps2000_set_sig_gen_arbitrary)
 (
  int16_t            handle,
  int32_t            offsetVoltage,
  uint32_t           pkToPk,
  uint32_t           startDeltaPhase,
  uint32_t           stopDeltaPhase,
  uint32_t           deltaPhaseIncrement,
  uint32_t           dwellCount,
  uint8_t           *arbitraryWaveform,
  int32_t            arbitraryWaveformSize,
  PS2000_SWEEP_TYPE  sweepType,
  uint32_t           sweeps
);

PREF0 PREF1 int16_t PREF2 PREF3(ps2000_set_sig_gen_built_in)
(
  int16_t            handle,
  int32_t            offsetVoltage,
  uint32_t           pkToPk,
  PS2000_WAVE_TYPE   waveType,
  float              startFrequency,
  float              stopFrequency,
  float              increment,
  float              dwellTime,
  PS2000_SWEEP_TYPE  sweepType,
  uint32_t           sweeps
);

//===========================================================
// Adv Trigger
//===========================================================
typedef enum enPS2000ThresholdDirection
{
  PS2000_ABOVE,
  PS2000_BELOW,
  PS2000_ADV_RISING,
  PS2000_ADV_FALLING,
  PS2000_RISING_OR_FALLING,
  PS2000_INSIDE = PS2000_ABOVE,
  PS2000_OUTSIDE = PS2000_BELOW,
  PS2000_ENTER = PS2000_ADV_RISING,
  PS2000_EXIT = PS2000_ADV_FALLING,
  PS2000_ENTER_OR_EXIT = PS2000_RISING_OR_FALLING,
  PS2000_ADV_NONE = PS2000_ADV_RISING
} PS2000_THRESHOLD_DIRECTION;

typedef enum enPS2000ThresholdMode
{
  PS2000_LEVEL,
  PS2000_WINDOW
} PS2000_THRESHOLD_MODE;

typedef enum enPS2000TriggerState
{
  PS2000_CONDITION_DONT_CARE,
  PS2000_CONDITION_TRUE,
  PS2000_CONDITION_FALSE,
  PS2000_CONDITION_MAX
} PS2000_TRIGGER_STATE;

typedef enum enPS2000PulseWidthType
{
  PS2000_PW_TYPE_NONE,
  PS2000_PW_TYPE_LESS_THAN,
  PS2000_PW_TYPE_GREATER_THAN,
  PS2000_PW_TYPE_IN_RANGE,
  PS2000_PW_TYPE_OUT_OF_RANGE
} PS2000_PULSE_WIDTH_TYPE;

#pragma pack(1)
typedef struct tPS2000TriggerChannelProperties
{
  int16_t thresholdMajor;
  int16_t thresholdMinor;
  uint16_t hysteresis;
  int16_t channel;
  PS2000_THRESHOLD_MODE thresholdMode;
} PS2000_TRIGGER_CHANNEL_PROPERTIES;
#pragma pack()

#pragma pack(1)
typedef struct tPS2000TriggerConditions
{
  PS2000_TRIGGER_STATE channelA;
  PS2000_TRIGGER_STATE channelB;
  PS2000_TRIGGER_STATE channelC;
  PS2000_TRIGGER_STATE channelD;
  PS2000_TRIGGER_STATE external;
  PS2000_TRIGGER_STATE pulseWidthQualifier;
} PS2000_TRIGGER_CONDITIONS;
#pragma pack()

#pragma pack(1)
typedef struct tPS2000PwqConditions
{
  PS2000_TRIGGER_STATE channelA;
  PS2000_TRIGGER_STATE channelB;
  PS2000_TRIGGER_STATE channelC;
  PS2000_TRIGGER_STATE channelD;
  PS2000_TRIGGER_STATE external;
} PS2000_PWQ_CONDITIONS;
#pragma pack()

PREF0 PREF1 int16_t PREF2 PREF3 (ps2000SetAdvTriggerChannelProperties)
(
  int16_t                            handle,
  PS2000_TRIGGER_CHANNEL_PROPERTIES *channelProperties,
  int16_t                            nChannelProperties,
  int32_t                            autoTriggerMilliseconds
);

PREF0 PREF1 int16_t PREF2 PREF3 (ps2000SetAdvTriggerChannelConditions)
(
  int16_t                    handle,
  PS2000_TRIGGER_CONDITIONS *conditions,
  int16_t                    nConditions
);

PREF0 PREF1 int16_t PREF2 PREF3 (ps2000SetAdvTriggerChannelDirections)
(
  int16_t                     handle,
  PS2000_THRESHOLD_DIRECTION  channelA,
  PS2000_THRESHOLD_DIRECTION  channelB,
  PS2000_THRESHOLD_DIRECTION  channelC,
  PS2000_THRESHOLD_DIRECTION  channelD,
  PS2000_THRESHOLD_DIRECTION  ext
);

PREF0 PREF1 int16_t PREF2 PREF3 (ps2000SetPulseWidthQualifier)
(
  int16_t                     handle,
  PS2000_PWQ_CONDITIONS      *conditions,
  int16_t                     nConditions,
  PS2000_THRESHOLD_DIRECTION  direction,
  uint32_t                    lower,
  uint32_t                    upper,
  PS2000_PULSE_WIDTH_TYPE     type
);

PREF0 PREF1 int16_t PREF2 PREF3 (ps2000SetAdvTriggerDelay)
(
  int16_t   handle,
  uint32_t  delay,
  float     preTriggerDelay
);

PREF0 PREF1 int16_t PREF2 PREF3 (ps2000PingUnit)
(
  int16_t  handle
);

#endif /* not defined PS2000_H */
