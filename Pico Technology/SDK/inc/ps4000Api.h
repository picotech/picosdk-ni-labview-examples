/****************************************************************************
 *
 * Filename:    ps4000Api.h
 * Author:      MAS
 * Description:
 *
 * This header defines the interface to driver routines for the
 *  PicoScope 4000 Series PC Oscilloscopes.
 *
 * Copyright � 2008 - 2022 Pico Technology Ltd. All rights reserved.
 *
 ****************************************************************************/
#ifndef __PS4000API_H__
#define __PS4000API_H__

#include <stdint.h>

#include "PicoStatus.h"

#ifdef __cplusplus
  #define PREF0 extern "C"
  #define TYPE_ENUM
#else
  #define PREF0
  #define TYPE_ENUM enum
#endif

#ifdef WIN32
  typedef uint64_t uint64_t;
  #ifdef PREF1
    #undef PREF1
  #endif
  #ifdef PREF2
    #undef PREF2
  #endif
  #ifdef PREF3
    #undef PREF3
  #endif
  /*  If you are dynamically linking ps4000.dll into your project #define DYNLINK here
   */
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

#define PS4000_MAX_OVERSAMPLE_12BIT  16
#define PS4000_MAX_OVERSAMPLE_8BIT  256

/* Depending on the adc; oversample (collect multiple readings at each time) by up to 256.
 * the results are therefore ALWAYS scaled up to 16-bits, even if
 * oversampling is not used.
 *
 * The maximum and minimum values returned are therefore as follows:
 */

#define PS4XXX_MAX_ETS_CYCLES 400
#define PS4XXX_MAX_INTERLEAVE  80

#define PS4262_MAX_VALUE  32767
#define PS4262_MIN_VALUE -32767

#define PS4000_MAX_VALUE  32764
#define PS4000_MIN_VALUE -32764
#define PS4000_LOST_DATA -32768

#define PS4000_EXT_MAX_VALUE  32767
#define PS4000_EXT_MIN_VALUE -32767

#define MAX_PULSE_WIDTH_QUALIFIER_COUNT 16777215L
#define MAX_DELAY_COUNT 8388607L

#define MIN_SIG_GEN_FREQ          0.0f
#define MAX_SIG_GEN_FREQ     100000.0f
#define MAX_SIG_GEN_FREQ_4262 20000.0f

// applicable to all variants with a signal generator
#define MIN_SIG_GEN_BUFFER_SIZE    1

// values relate to the PS4227 and PS4226
#define MAX_SIG_GEN_BUFFER_SIZE 8192
#define MIN_DWELL_COUNT           10

#define PS4262_MAX_WAVEFORM_BUFFER_SIZE 4096
#define PS4262_MIN_DWELL_COUNT             3

#define MAX_SWEEPS_SHOTS     ((1 << 30) - 1)

typedef enum enChannelBufferIndex
{
  PS4000_CHANNEL_A_MAX,
  PS4000_CHANNEL_A_MIN,
  PS4000_CHANNEL_B_MAX,
  PS4000_CHANNEL_B_MIN,
  PS4000_CHANNEL_C_MAX,
  PS4000_CHANNEL_C_MIN,
  PS4000_CHANNEL_D_MAX,
  PS4000_CHANNEL_D_MIN,
  PS4000_MAX_CHANNEL_BUFFERS
} PS4000_CHANNEL_BUFFER_INDEX;

typedef enum enPS4000Channel
{
  PS4000_CHANNEL_A,
  PS4000_CHANNEL_B,
  PS4000_CHANNEL_C,
  PS4000_CHANNEL_D,
  PS4000_EXTERNAL,
  PS4000_MAX_CHANNELS = PS4000_EXTERNAL,
  PS4000_TRIGGER_AUX,
  PS4000_MAX_TRIGGER_SOURCES
}  PS4000_CHANNEL;

typedef enum enPS4000Range
{
  PS4000_10MV,
  PS4000_20MV,
  PS4000_50MV,
  PS4000_100MV,
  PS4000_200MV,
  PS4000_500MV,
  PS4000_1V,
  PS4000_2V,
  PS4000_5V,
  PS4000_10V,
  PS4000_20V,
  PS4000_50V,
  PS4000_100V,
  PS4000_MAX_RANGES,

  PS4000_RESISTANCE_100R = PS4000_MAX_RANGES,
  PS4000_RESISTANCE_1K,
  PS4000_RESISTANCE_10K,
  PS4000_RESISTANCE_100K,
  PS4000_RESISTANCE_1M,
  PS4000_MAX_RESISTANCES,

  PS4000_ACCELEROMETER_10MV = PS4000_MAX_RESISTANCES,
  PS4000_ACCELEROMETER_20MV,
  PS4000_ACCELEROMETER_50MV,
  PS4000_ACCELEROMETER_100MV,
  PS4000_ACCELEROMETER_200MV,
  PS4000_ACCELEROMETER_500MV,
  PS4000_ACCELEROMETER_1V,
  PS4000_ACCELEROMETER_2V,
  PS4000_ACCELEROMETER_5V,
  PS4000_ACCELEROMETER_10V,
  PS4000_ACCELEROMETER_20V,
  PS4000_ACCELEROMETER_50V,
  PS4000_ACCELEROMETER_100V,
  PS4000_MAX_ACCELEROMETER,

  PS4000_TEMPERATURE_UPTO_40 = PS4000_MAX_ACCELEROMETER,
  PS4000_TEMPERATURE_UPTO_70,
  PS4000_TEMPERATURE_UPTO_100,
  PS4000_TEMPERATURE_UPTO_130,
  PS4000_MAX_TEMPERATURES,

  PS4000_RESISTANCE_5K = PS4000_MAX_TEMPERATURES,
  PS4000_RESISTANCE_25K,
  PS4000_RESISTANCE_50K,
  PS4000_MAX_EXTRA_RESISTANCES
} PS4000_RANGE;

typedef enum enPS4000Probe
{
  P_NONE,
  P_CURRENT_CLAMP_10A,
  P_CURRENT_CLAMP_1000A,
  P_TEMPERATURE_SENSOR,
  P_CURRENT_MEASURING_DEVICE,
  P_PRESSURE_SENSOR_50BAR,
  P_PRESSURE_SENSOR_5BAR,
  P_OPTICAL_SWITCH,
  P_UNKNOWN,
  P_MAX_PROBES = P_UNKNOWN
} PS4000_PROBE;

typedef enum enPS4000ChannelInfo
{
  CI_RANGES,
  CI_RESISTANCES,
  CI_ACCELEROMETER,
  CI_PROBES,
  CI_TEMPERATURES
} PS4000_CHANNEL_INFO;

typedef enum enPS4000EtsMode
  {
  PS4000_ETS_OFF,             // ETS disabled
  PS4000_ETS_FAST,
  PS4000_ETS_SLOW,
  PS4000_ETS_MODES_MAX
  }  PS4000_ETS_MODE;

typedef enum enPS4000TimeUnits
  {
  PS4000_FS,
  PS4000_PS,
  PS4000_NS,
  PS4000_US,
  PS4000_MS,
  PS4000_S,
  PS4000_MAX_TIME_UNITS,
  }  PS4000_TIME_UNITS;

typedef enum enSweepType
{
  UP,
  DOWN,
  UPDOWN,
  DOWNUP,
  MAX_SWEEP_TYPES
} SWEEP_TYPE;

typedef enum enPS4000OperationTypes
{
  PS4000_OP_NONE,
  PS4000_WHITENOISE,
  PS4000_PRBS
} PS4000_OPERATION_TYPES;

typedef enum enWaveType
{
  PS4000_SINE,
  PS4000_SQUARE,
  PS4000_TRIANGLE,
  PS4000_RAMP_UP,
  PS4000_RAMP_DOWN,
  PS4000_SINC,
  PS4000_GAUSSIAN,
  PS4000_HALF_SINE,
  PS4000_DC_VOLTAGE,
  PS4000_WHITE_NOISE,
  MAX_WAVE_TYPES
} WAVE_TYPE;

typedef enum enSigGenTrigType
{
  SIGGEN_RISING,
  SIGGEN_FALLING,
  SIGGEN_GATE_HIGH,
  SIGGEN_GATE_LOW
} SIGGEN_TRIG_TYPE;

typedef enum enSigGenTrigSource
{
  SIGGEN_NONE,
  SIGGEN_SCOPE_TRIG,
  SIGGEN_AUX_IN,
  SIGGEN_EXT_IN,
  SIGGEN_SOFT_TRIG
} SIGGEN_TRIG_SOURCE;

typedef enum enIndexMode
{
  SINGLE,
  DUAL,
  QUAD,
  MAX_INDEX_MODES
} INDEX_MODE;

typedef enum enThresholdMode
{
  LEVEL,
  WINDOW
} THRESHOLD_MODE;

typedef enum enThresholdDirection
{
  ABOVE, //using upper threshold
  BELOW,
  RISING, // using upper threshold
  FALLING, // using upper threshold
  RISING_OR_FALLING, // using both threshold
  ABOVE_LOWER, // using lower threshold
  BELOW_LOWER, // using lower threshold
  RISING_LOWER,       // using lower threshold
  FALLING_LOWER,     // using lower threshold

  // Windowing using both thresholds
  INSIDE = ABOVE,
  OUTSIDE = BELOW,
  ENTER = RISING,
  EXIT = FALLING,
  ENTER_OR_EXIT = RISING_OR_FALLING,
  POSITIVE_RUNT = 9,
  NEGATIVE_RUNT,

  // no trigger set
  NONE = RISING
} THRESHOLD_DIRECTION;

typedef enum enTriggerState
{
  CONDITION_DONT_CARE,
  CONDITION_TRUE,
  CONDITION_FALSE,
  CONDITION_MAX
} TRIGGER_STATE;

#pragma pack(1)
typedef struct tTriggerConditions
{
  TRIGGER_STATE channelA;
  TRIGGER_STATE channelB;
  TRIGGER_STATE channelC;
  TRIGGER_STATE channelD;
  TRIGGER_STATE external;
  TRIGGER_STATE aux;
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
  TRIGGER_STATE aux;
} PWQ_CONDITIONS;
#pragma pack()

#pragma pack(1)
typedef struct tTriggerChannelProperties
{
  int16_t thresholdUpper;
  uint16_t thresholdUpperHysteresis;
  int16_t thresholdLower;
  uint16_t thresholdLowerHysteresis;
  PS4000_CHANNEL channel;
  THRESHOLD_MODE thresholdMode;
} TRIGGER_CHANNEL_PROPERTIES;
#pragma pack()

typedef enum enRatioMode
{
  RATIO_MODE_NONE,
  RATIO_MODE_AGGREGATE = 1,
  RATIO_MODE_AVERAGE = 2
} RATIO_MODE;

typedef enum enPulseWidthType
{
  PW_TYPE_NONE,
  PW_TYPE_LESS_THAN,
  PW_TYPE_GREATER_THAN,
  PW_TYPE_IN_RANGE,
  PW_TYPE_OUT_OF_RANGE
} PULSE_WIDTH_TYPE;

typedef enum enPs4000HoldOffType
{
  PS4000_TIME,
  PS4000_MAX_HOLDOFF_TYPE
} PS4000_HOLDOFF_TYPE;

typedef enum enPS4000FrequencyCounterRange
{
  FC_2K,
  FC_20K,
  FC_20,
  FC_200,
  FC_MAX
}PS4000_FREQUENCY_COUNTER_RANGE;

typedef void (__stdcall *ps4000BlockReady)
(
  int16_t      handle,
  PICO_STATUS  status,
  void        *pParameter
);

typedef void (__stdcall *ps4000StreamingReady)
(
  int16_t   handle,
  int32_t   noOfSamples,
  uint32_t  startIndex,
  int16_t   overflow,
  uint32_t  triggerAt,
  int16_t   triggered,
  int16_t   autoStop,
  void     *pParameter
);

typedef void (__stdcall *ps4000DataReady)
(
  int16_t   handle,
  int32_t   noOfSamples,
  int16_t   overflow,
  uint32_t  triggerAt,
  int16_t   triggered,
  void     *pParameter
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000OpenUnit)
(
  int16_t *handle
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000OpenUnitAsync)
(
  int16_t *status
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000OpenUnitEx)
(
  int16_t *handle,
  int8_t  *serial
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000OpenUnitAsyncEx)
(
  int16_t *status,
  int8_t  *serial
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000OpenUnitProgress)
(
  int16_t *handle,
  int16_t *progressPercent,
  int16_t *complete
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000GetUnitInfo)
(
  int16_t    handle,
  int8_t    *string,
  int16_t    stringLength,
  int16_t   *requiredSize,
  PICO_INFO  info
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000FlashLed)
(
  int16_t  handle,
  int16_t  start
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000IsLedFlashing)
(
  int16_t  handle,
  int16_t *status
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000CloseUnit)
(
  int16_t  handle
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000MemorySegments)
(
  int16_t   handle,
  uint16_t  nSegments,
  int32_t  *nMaxSamples
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000SetChannel)
(
  int16_t         handle,
  PS4000_CHANNEL  channel,
  int16_t         enabled,
  int16_t         dc,
  PS4000_RANGE    range
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000SetNoOfCaptures)
(
  int16_t   handle,
  uint16_t  nCaptures
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000GetTimebase)
(
  int16_t   handle,
  uint32_t  timebase,
  int32_t   noSamples,
  int32_t  *timeIntervalNanoseconds,
  int16_t   oversample,
  int32_t  *maxSamples,
  uint16_t  segmentIndex
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000GetTimebase2)
(
  int16_t   handle,
  uint32_t  timebase,
  int32_t   noSamples,
  float    *timeIntervalNanoseconds,
  int16_t   oversample,
  int32_t  *maxSamples,
  uint16_t  segmentIndex
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000SigGenOff)
(
	int16_t handle
);


PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000SetSigGenArbitrary)
(
  int16_t             handle,
  int32_t             offsetVoltage,
  uint32_t            pkToPk,
  uint32_t            startDeltaPhase,
  uint32_t            stopDeltaPhase,
  uint32_t            deltaPhaseIncrement,
  uint32_t            dwellCount,
  int16_t            *arbitraryWaveform,
  int32_t             arbitraryWaveformSize,
  SWEEP_TYPE          sweepType,
  int16_t             operationType,
  INDEX_MODE          indexMode,
  uint32_t            shots,
  uint32_t            sweeps,
  SIGGEN_TRIG_TYPE    triggerType,
  SIGGEN_TRIG_SOURCE  triggerSource,
  int16_t             extInThreshold
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps4000SetSigGenBuiltIn)
(
  int16_t             handle,
  int32_t             offsetVoltage,
  uint32_t            pkToPk,
  int16_t             waveType,
  float               startFrequency,
  float               stopFrequency,
  float               increment,
  float               dwellTime,
  SWEEP_TYPE          sweepType,
  int16_t             operationType,
  uint32_t            shots,
  uint32_t            sweeps,
  SIGGEN_TRIG_TYPE    triggerType,
  SIGGEN_TRIG_SOURCE  triggerSource,
  int16_t             extInThreshold
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps4000SigGenFrequencyToPhase)
	(
	int16_t												handle,
	double												frequency,
	INDEX_MODE										indexMode,
	uint32_t											bufferLength,
	uint32_t										* phase
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps4000SigGenArbitraryMinMaxValues)
	(
	int16_t			handle,
	int16_t		*	minArbitraryWaveformValue,
	int16_t		*	maxArbitraryWaveformValue,
	uint32_t	* minArbitraryWaveformSize,
	uint32_t	*	maxArbitraryWaveformSize
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000SigGenSoftwareControl)
(
  int16_t  handle,
  int16_t  state
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000SetEts)
(
  int16_t          handle,
  PS4000_ETS_MODE  mode,
  int16_t          etsCycles,
  int16_t          etsInterleave,
  int32_t         *sampleTimePicoseconds
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000SetSimpleTrigger)
(
  int16_t handle,
  int16_t enable,
  PS4000_CHANNEL source,
  int16_t threshold,
  THRESHOLD_DIRECTION direction,
  uint32_t delay,
  int16_t autoTrigger_ms
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000SetTriggerChannelProperties)
(
  int16_t                     handle,
  TRIGGER_CHANNEL_PROPERTIES *channelProperties,
  int16_t                     nChannelProperties,
  int16_t                     auxOutputEnable,
  int32_t                     autoTriggerMilliseconds
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000SetExtTriggerRange)
(
  int16_t       handle,
  PS4000_RANGE  extRange
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000SetTriggerChannelConditions)
(
  int16_t             handle,
  TRIGGER_CONDITIONS *conditions,
  int16_t             nConditions
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000SetTriggerChannelDirections)
(
  int16_t              handle,
  THRESHOLD_DIRECTION  channelA,
  THRESHOLD_DIRECTION  channelB,
  THRESHOLD_DIRECTION  channelC,
  THRESHOLD_DIRECTION  channelD,
  THRESHOLD_DIRECTION  ext,
  THRESHOLD_DIRECTION  aux
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000SetTriggerDelay)
(
  int16_t   handle,
  uint32_t  delay
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000SetPulseWidthQualifier)
(
  int16_t              handle,
  PWQ_CONDITIONS      *conditions,
  int16_t              nConditions,
  THRESHOLD_DIRECTION  direction,
  uint32_t             lower,
  uint32_t             upper,
  PULSE_WIDTH_TYPE     type
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000IsTriggerOrPulseWidthQualifierEnabled)
(
  int16_t  handle,
  int16_t *triggerEnabled,
  int16_t *pulseWidthQualifierEnabled
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000GetTriggerTimeOffset)
(
  int16_t            handle,
  uint32_t          *timeUpper,
  uint32_t          *timeLower,
  PS4000_TIME_UNITS *timeUnits,
  uint16_t           segmentIndex
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000GetTriggerChannelTimeOffset)
(
  int16_t            handle,
  uint32_t          *timeUpper,
  uint32_t          *timeLower,
  PS4000_TIME_UNITS *timeUnits,
  uint16_t           segmentIndex,
  PS4000_CHANNEL     channel
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000GetTriggerTimeOffset64)
(
  int16_t            handle,
  int64_t           *time,
  PS4000_TIME_UNITS *timeUnits,
  uint16_t           segmentIndex
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000GetTriggerChannelTimeOffset64)
(
  int16_t            handle,
  int64_t           *time,
  PS4000_TIME_UNITS *timeUnits,
  uint16_t           segmentIndex,
  PS4000_CHANNEL     channel
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000GetValuesTriggerTimeOffsetBulk)
(
  int16_t            handle,
  uint32_t          *timesUpper,
  uint32_t          *timesLower,
  PS4000_TIME_UNITS *timeUnits,
  uint16_t           fromSegmentIndex,
  uint16_t           toSegmentIndex
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000GetValuesTriggerChannelTimeOffsetBulk)
(
  int16_t            handle,
  uint32_t          *timesUpper,
  uint32_t          *timesLower,
  PS4000_TIME_UNITS *timeUnits,
  uint16_t           fromSegmentIndex,
  uint16_t           toSegmentIndex,
  PS4000_CHANNEL     channel
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000GetValuesTriggerTimeOffsetBulk64)
(
  int16_t            handle,
  int64_t           *times,
  PS4000_TIME_UNITS *timeUnits,
  uint16_t           fromSegmentIndex,
  uint16_t           toSegmentIndex
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000GetValuesTriggerChannelTimeOffsetBulk64)
(
  int16_t            handle,
  int64_t           *times,
  PS4000_TIME_UNITS *timeUnits,
  uint16_t           fromSegmentIndex,
  uint16_t           toSegmentIndex,
  PS4000_CHANNEL     channel
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000SetDataBufferBulk)
(
  int16_t         handle,
  PS4000_CHANNEL  channel,
  int16_t        *buffer,
  int32_t         bufferLth,
  uint16_t        waveform
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000SetDataBuffers)
(
  int16_t         handle,
  PS4000_CHANNEL  channel,
  int16_t        *bufferMax,
  int16_t        *bufferMin,
  int32_t         bufferLth
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000SetDataBufferWithMode)
(
  int16_t         handle,
  PS4000_CHANNEL  channel,
  int16_t        *buffer,
  int32_t         bufferLth,
  RATIO_MODE      mode
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000SetDataBuffersWithMode)
(
  int16_t         handle,
  PS4000_CHANNEL  channel,
  int16_t        *bufferMax,
  int16_t        *bufferMin,
  int32_t         bufferLth,
  RATIO_MODE      mode
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000SetDataBuffer)
(
  int16_t         handle,
  PS4000_CHANNEL  channel,
  int16_t        *buffer,
  int32_t         bufferLth
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000SetEtsTimeBuffer)
(
  int16_t  handle,
  int64_t *buffer,
  int32_t  bufferLth
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000SetEtsTimeBuffers)
(
  int16_t   handle,
  uint32_t *timeUpper,
  uint32_t *timeLower,
  int32_t   bufferLth
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000RunBlock)
(
  int16_t           handle,
  int32_t           noOfPreTriggerSamples,
  int32_t           noOfPostTriggerSamples,
  uint32_t          timebase,
  int16_t           oversample,
  int32_t          *timeIndisposedMs,
  uint16_t          segmentIndex,
  ps4000BlockReady  lpReady,
  void             *pParameter
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000RunStreaming)
(
  int16_t            handle,
  uint32_t          *sampleInterval,
  PS4000_TIME_UNITS  sampleIntervalTimeUnits,
  uint32_t           maxPreTriggerSamples,
  uint32_t           maxPostPreTriggerSamples,
  int16_t            autoStop,
  uint32_t           downSampleRatio,
  uint32_t           overviewBufferSize
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000RunStreamingEx)
(
  int16_t            handle,
  uint32_t          *sampleInterval,
  PS4000_TIME_UNITS  sampleIntervalTimeUnits,
  uint32_t           maxPreTriggerSamples,
  uint32_t           maxPostPreTriggerSamples,
  int16_t            autoStop,
  uint32_t           downSampleRatio,
  int16_t            downSampleRatioMode,
  uint32_t           overviewBufferSize
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000IsReady)
(
  int16_t handle,
  int16_t * ready
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000GetStreamingLatestValues)
(
  int16_t               handle,
  ps4000StreamingReady  lpPs4000Ready,
  void                 *pParameter
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000NoOfStreamingValues)
(
  int16_t   handle,
  uint32_t *noOfValues
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000GetMaxDownSampleRatio)
(
  int16_t   handle,
  uint32_t  noOfUnaggreatedSamples,
  uint32_t *maxDownSampleRatio,
  int16_t   downSampleRatioMode,
  uint16_t  segmentIndex
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000GetValues)
(
  int16_t   handle,
  uint32_t  startIndex,
  uint32_t *noOfSamples,
  uint32_t  downSampleRatio,
  int16_t   downSampleRatioMode,
  uint16_t  segmentIndex,
  int16_t  *overflow
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000GetValuesBulk)
(
  int16_t   handle,
  uint32_t *noOfSamples,
  uint16_t  fromSegmentIndex,
  uint16_t  toSegmentIndex,
  int16_t  *overflow
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000GetValuesAsync)
(
  int16_t   handle,
  uint32_t  startIndex,
  uint32_t  noOfSamples,
  uint32_t  downSampleRatio,
  int16_t   downSampleRatioMode,
  uint16_t  segmentIndex,
  void     *lpDataReady,
  void     *pParameter
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000Stop)
(
  int16_t  handle
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000SetProbe)
(
  int16_t       handle,
  PS4000_PROBE  probe,
  PS4000_RANGE  range
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000HoldOff)
(
  int16_t              handle,
  uint64_t             holdoff,
  PS4000_HOLDOFF_TYPE  type
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000GetProbe)
(
  int16_t       handle,
  PS4000_PROBE *probe
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000GetChannelInformation)
(
  int16_t              handle,
  PS4000_CHANNEL_INFO  info,
  int32_t              probe,
  int32_t             *ranges,
  int32_t             *length,
  int32_t              channels
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000SetFrequencyCounter)
(
  int16_t                         handle,
  PS4000_CHANNEL                  channel,
  int16_t                         enabled,
  PS4000_FREQUENCY_COUNTER_RANGE  range,
  int16_t                         thresholdMajor,
  int16_t                         thresholdMinor
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000EnumerateUnits)
(
  int16_t *count,
  int8_t  *serials,
  int16_t *serialLth
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000PingUnit)
(
  int16_t  handle
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000SetBwFilter)
(
  int16_t         handle,
  PS4000_CHANNEL  channel,
  int16_t         enable
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000TriggerWithinPreTriggerSamples)
(
  int16_t  handle,
  int16_t  state
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000GetNoOfCaptures)
(
  int16_t   handle,
  uint16_t *nCaptures
);

#endif
