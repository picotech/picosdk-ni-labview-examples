/****************************************************************************
 *
 * Filename:    ps5000Api.h
 * Author:      MAS
 * Description:
 *
 * This header defines the interface to driver routines for the
 *  PicoScope 5203 and 5204 PC Oscilloscopes.
 *
 * Copyright � 2002 - 2022 Pico Technology Ltd. All rights reserved.
 *
 ****************************************************************************/
#ifndef __PS5000API_H__
#define __PS5000API_H__

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
/*  If you are dynamically linking ps5000.dll into your project #define DYNLINK here
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
  #define PREF4 __stdcall
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
  #define PREF4
#endif

#define PS5000_MAX_OVERSAMPLE_8BIT 256

/* Although the PS5000 uses an 8-bit ADC, it is usually possible to
 * oversample (collect multiple readings at each time) by up to 256.
 * the results are therefore ALWAYS scaled up to 16-bits, even if
 * oversampling is not used.
 *
 * The maximum and minimum values returned are therefore as follows:
 */
#define PS5000_MAX_VALUE  32512
#define PS5000_MIN_VALUE -32512
#define PS5000_LOST_DATA -32768

#define PS5000_EXT_MAX_VALUE  32767
#define PS5000_EXT_MIN_VALUE -32767

#define MAX_PULSE_WIDTH_QUALIFIER_COUNT 16777215L
#define MAX_DELAY_COUNT 8388607L

#define MAX_SIG_GEN_BUFFER_SIZE 8192
#define MIN_SIG_GEN_BUFFER_SIZE 10
#define MIN_DWELL_COUNT         10
#define MAX_SWEEPS_SHOTS ((1 << 30) - 1)

typedef enum enPS5000Channel
{
  PS5000_CHANNEL_A,
  PS5000_CHANNEL_B,
  PS5000_CHANNEL_C,
  PS5000_CHANNEL_D,
  PS5000_EXTERNAL,
  PS5000_MAX_CHANNELS = PS5000_EXTERNAL,
  PS5000_TRIGGER_AUX,
  PS5000_MAX_TRIGGER_SOURCES
}  PS5000_CHANNEL;

typedef enum enChannelBufferIndex
{
  PS5000_CHANNEL_A_MAX,
  PS5000_CHANNEL_A_MIN,
  PS5000_CHANNEL_B_MAX,
  PS5000_CHANNEL_B_MIN,
  PS5000_CHANNEL_C_MAX,
  PS5000_CHANNEL_C_MIN,
  PS5000_CHANNEL_D_MAX,
  PS5000_CHANNEL_D_MIN,
  PS5000_MAX_CHANNEL_BUFFERS
} PS5000_CHANNEL_BUFFER_INDEX;

typedef enum enPS5000Range
{
  PS5000_10MV,
  PS5000_20MV,
  PS5000_50MV,
  PS5000_100MV,
  PS5000_200MV,
  PS5000_500MV,
  PS5000_1V,
  PS5000_2V,
  PS5000_5V,
  PS5000_10V,
  PS5000_20V,
  PS5000_50V,
  PS5000_MAX_RANGES
}  PS5000_RANGE;


typedef enum enPS5000EtsMode
  {
  PS5000_ETS_OFF,      // ETS disabled
  PS5000_ETS_FAST,     // Return ready as soon as requested no of interleaves is available
  PS5000_ETS_SLOW,     // Return ready every time a new set of no_of_cycles is collected
  PS5000_ETS_MODES_MAX
  }  PS5000_ETS_MODE;

typedef enum enPS5000TimeUnits
  {
  PS5000_FS,
  PS5000_PS,
  PS5000_NS,
  PS5000_US,
  PS5000_MS,
  PS5000_S,
  PS5000_MAX_TIME_UNITS,
  }  PS5000_TIME_UNITS;

typedef enum enSweepType
{
  UP,
  DOWN,
  UPDOWN,
  DOWNUP,
  MAX_SWEEP_TYPES
} SWEEP_TYPE;

typedef enum enWaveType
{
  PS5000_SINE,
  PS5000_SQUARE,
  PS5000_TRIANGLE,
  PS5000_RAMP_UP,
  PS5000_RAMP_DOWN,
  PS5000_SINC,
  PS5000_GAUSSIAN,
  PS5000_HALF_SINE,
  PS5000_DC_VOLTAGE,
  PS5000_WHITE_NOISE,
  MAX_WAVE_TYPES
} WAVE_TYPE;

#define PS5000_SINE_MAX_FREQUENCY        20000000.f
#define PS5000_SQUARE_MAX_FREQUENCY      20000000.f
#define PS5000_TRIANGLE_MAX_FREQUENCY    20000000.f
#define PS5000_SINC_MAX_FREQUENCY        20000000.f
#define PS5000_RAMP_MAX_FREQUENCY        20000000.f
#define PS5000_HALF_SINE_MAX_FREQUENCY   20000000.f
#define PS5000_GAUSSIAN_MAX_FREQUENCY    20000000.f
#define PS5000_MIN_FREQUENCY                  0.03f

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

typedef enum enTriggerState
{
  CONDITION_DONT_CARE,
  CONDITION_TRUE,
  CONDITION_FALSE,
  CONDITION_MAX
} TRIGGER_STATE;

#pragma pack(push,1)
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
#pragma pack(pop)

#pragma pack(push,1)
typedef struct tPwqConditions
{
  TRIGGER_STATE channelA;
  TRIGGER_STATE channelB;
  TRIGGER_STATE channelC;
  TRIGGER_STATE channelD;
  TRIGGER_STATE external;
  TRIGGER_STATE aux;
} PWQ_CONDITIONS;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct tTriggerChannelProperties
{
  int16_t thresholdMajor;
  int16_t thresholdMinor;
  uint16_t hysteresis;
  PS5000_CHANNEL channel;
  THRESHOLD_MODE thresholdMode;
} TRIGGER_CHANNEL_PROPERTIES;
#pragma pack(pop)

typedef enum enRatioMode
{
  RATIO_MODE_NONE = 0,
  RATIO_MODE_AGGREGATE = 1,
  RATIO_MODE_DECIMATE = 2,
  RATIO_MODE_AVERAGE = 4,
  RATIO_MODE_DISTRIBUTION = 8
} RATIO_MODE;

typedef enum enPulseWidthType
{
  PW_TYPE_NONE,
  PW_TYPE_LESS_THAN,
  PW_TYPE_GREATER_THAN,
  PW_TYPE_IN_RANGE,
  PW_TYPE_OUT_OF_RANGE
} PULSE_WIDTH_TYPE;

typedef enum enPS5000ChannelInfo
{
  CI_RANGES,
} PS5000_CHANNEL_INFO;

typedef void (PREF4 *ps5000BlockReady)
(
  int16_t      handle,
  PICO_STATUS  status,
  void        *pParameter
);

typedef void (PREF4 *ps5000StreamingReady)
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

typedef void (PREF4 *ps5000DataReady)
(
  int16_t   handle,
  int32_t   noOfSamples,
  int16_t   overflow,
  uint32_t  triggerAt,
  int16_t   triggered,
  void     *pParameter
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps5000OpenUnit)
(
  int16_t *handle
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps5000OpenUnitAsync)
(
  int16_t *status
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps5000OpenUnitProgress)
(
  int16_t *handle,
  int16_t *progressPercent,
  int16_t *complete
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps5000GetUnitInfo)
(
  int16_t    handle,
  int8_t    *string,
  int16_t    stringLength,
  int16_t   *requiredSize,
  PICO_INFO  info
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps5000FlashLed)
(
  int16_t  handle,
  int16_t  start
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps5000IsLedFlashing)
(
  int16_t  handle,
  int16_t *status
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps5000CloseUnit)
(
  int16_t  handle
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps5000MemorySegments)
(
  int16_t   handle,
  uint16_t  nSegments,
  int32_t  *nMaxSamples
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps5000SetChannel)
(
  int16_t         handle,
  PS5000_CHANNEL  channel,
  int16_t         enabled,
  int16_t         dc,
  PS5000_RANGE    range
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps5000GetTimebase)
(
  int16_t   handle,
  uint32_t  timebase,
  int32_t   noSamples,
  int32_t  *timeIntervalNanoseconds,
  int16_t   oversample,
  int32_t  *maxSamples,
  uint16_t  segmentIndex
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps5000GetTimebase2)
(
  int16_t   handle,
  uint32_t  timebase,
  int32_t   noSamples,
  float    *timeIntervalNanoseconds,
  int16_t   oversample,
  int32_t  *maxSamples,
  uint16_t  segmentIndex
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps5000SetSigGenArbitrary)
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
  int16_t             whiteNoise,
  INDEX_MODE          indexMode,
  uint32_t            shots,
  uint32_t            sweeps,
  SIGGEN_TRIG_TYPE    triggerType,
  SIGGEN_TRIG_SOURCE  triggerSource,
  int16_t             extInThreshold
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps5000SetSigGenBuiltIn)
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
  int16_t             whiteNoise,
  uint32_t            shots,
  uint32_t            sweeps,
  SIGGEN_TRIG_TYPE    triggerType,
  SIGGEN_TRIG_SOURCE  triggerSource,
  int16_t             extInThreshold
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps5000SetSigGenBuiltInV2)
(
  int16_t             handle,
  int32_t             offsetVoltage,
  uint32_t            pkToPk,
  int16_t             waveType,
  double              startFrequency,
  double              stopFrequency,
  double              increment,
  double              dwellTime,
  SWEEP_TYPE          sweepType,
  int16_t             whiteNoise,
  uint32_t            shots,
  uint32_t            sweeps,
  SIGGEN_TRIG_TYPE    triggerType,
  SIGGEN_TRIG_SOURCE  triggerSource,
  int16_t             extInThreshold
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps5000SigGenFrequencyToPhase)
	(
	int16_t												handle,
	double												frequency,
	INDEX_MODE										indexMode,
	uint32_t											bufferLength,
	uint32_t										* phase
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps5000SigGenArbitraryMinMaxValues)
	(
	int16_t			handle,
	int16_t		*	minArbitraryWaveformValue,
	int16_t		*	maxArbitraryWaveformValue,
	uint32_t	* minArbitraryWaveformSize,
	uint32_t	*	maxArbitraryWaveformSize
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps5000SigGenSoftwareControl)
(
  int16_t  handle,
  int16_t  state
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps5000SetEts)
(
  int16_t          handle,
  PS5000_ETS_MODE  mode,
  int16_t          etsCycles,
  int16_t          etsInterleave,
  int32_t         *sampleTimePicoseconds
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps5000SetTriggerChannelProperties)
(
  int16_t                     handle,
  TRIGGER_CHANNEL_PROPERTIES *channelProperties,
  int16_t                     nChannelProperties,
  int16_t                     auxOutputEnable,
  int32_t                     autoTriggerMilliseconds
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps5000SetTriggerChannelConditions)
(
  int16_t             handle,
  TRIGGER_CONDITIONS *conditions,
  int16_t             nConditions
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps5000SetTriggerChannelDirections)
(
  int16_t              handle,
  THRESHOLD_DIRECTION  channelA,
  THRESHOLD_DIRECTION  channelB,
  THRESHOLD_DIRECTION  channelC,
  THRESHOLD_DIRECTION  channelD,
  THRESHOLD_DIRECTION  ext,
  THRESHOLD_DIRECTION  aux
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps5000SetSimpleTrigger)
(
  int16_t              handle,
  int16_t              enable,
  PS5000_CHANNEL       source,
  int16_t              threshold,
  THRESHOLD_DIRECTION  direction,
  uint32_t             delay,
  int16_t              autoTrigger_ms
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps5000SetTriggerDelay)
(
  int16_t   handle,
  uint32_t  delay
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps5000SetPulseWidthQualifier)
(
  int16_t              handle,
  PWQ_CONDITIONS      *conditions,
  int16_t              nConditions,
  THRESHOLD_DIRECTION  direction,
  uint32_t             lower,
  uint32_t             upper,
  PULSE_WIDTH_TYPE     type
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps5000IsTriggerOrPulseWidthQualifierEnabled)
(
  int16_t  handle,
  int16_t *triggerEnabled,
  int16_t *pulseWidthQualifierEnabled
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps5000GetTriggerTimeOffset)
(
  int16_t            handle,
  uint32_t          *timeUpper,
  uint32_t          *timeLower,
  PS5000_TIME_UNITS *timeUnits,
  uint16_t           segmentIndex
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps5000GetTriggerTimeOffset64)
(
  int16_t            handle,
  int64_t           *time,
  PS5000_TIME_UNITS *timeUnits,
  uint16_t           segmentIndex
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps5000GetValuesTriggerTimeOffsetBulk)
(
  int16_t            handle,
  uint32_t          *timesUpper,
  uint32_t          *timesLower,
  PS5000_TIME_UNITS *timeUnits,
  uint16_t           fromSegmentIndex,
  uint16_t           toSegmentIndex
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps5000GetValuesTriggerTimeOffsetBulk64)
(
  int16_t            handle,
  int64_t           *times,
  PS5000_TIME_UNITS *timeUnits,
  uint16_t           fromSegmentIndex,
  uint16_t           toSegmentIndex
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps5000SetDataBuffers)
(
  int16_t         handle,
  PS5000_CHANNEL  channel,
  int16_t        *bufferMax,
  int16_t        *bufferMin,
  int32_t         bufferLth
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps5000SetDataBuffer)
(
   int16_t         handle,
   PS5000_CHANNEL  channel,
   int16_t        *buffer,
   int32_t         bufferLth
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps5000SetDataBufferBulk)
(
  int16_t         handle,
  PS5000_CHANNEL  channel,
  int16_t        *buffer,
  int32_t         bufferLth,
  uint16_t        waveform
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps5000SetEtsTimeBuffer)
(
  int16_t  handle,
  int64_t *buffer,
  int32_t  bufferLth
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps5000SetEtsTimeBuffers)
(
  int16_t   handle,
  uint32_t *timeUpper,
  uint32_t *timeLower,
  int32_t   bufferLth
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps5000IsReady)
(
  int16_t  handle,
  int16_t *ready
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps5000RunBlock)
(
  int16_t           handle,
  int32_t           noOfPreTriggerSamples,
  int32_t           noOfPostTriggerSamples,
  uint32_t          timebase,
  int16_t           oversample,
  int32_t          *timeIndisposedMs,
  uint16_t          segmentIndex,
  ps5000BlockReady  lpReady,
  void             *pParameter
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps5000RunStreaming)
(
  int16_t            handle,
  uint32_t          *sampleInterval,
  PS5000_TIME_UNITS  sampleIntervalTimeUnits,
  uint32_t           maxPreTriggerSamples,
  uint32_t           maxPostPreTriggerSamples,
  int16_t            autoStop,
  uint32_t           downSampleRatio,
  uint32_t           overviewBufferSize
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps5000GetStreamingLatestValues)
(
  int16_t               handle,
  ps5000StreamingReady  lpPs5000Ready,
  void                 *pParameter
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps5000NoOfStreamingValues)
(
  int16_t   handle,
  uint32_t *noOfValues
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps5000GetMaxDownSampleRatio)
(
  int16_t   handle,
  uint32_t  noOfUnaggreatedSamples,
  uint32_t *maxDownSampleRatio,
  int16_t   downSampleRatioMode,
  uint16_t  segmentIndex
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps5000GetValues)
(
  int16_t   handle,
  uint32_t  startIndex,
  uint32_t *noOfSamples,
  uint32_t  downSampleRatio,
  int16_t   downSampleRatioMode,
  uint16_t  segmentIndex,
  int16_t  *overflow
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps5000GetValuesBulk)
(
  int16_t   handle,
  uint32_t *noOfSamples,
  uint16_t  fromSegmentIndex,
  uint16_t  toSegmentIndex,
  int16_t  *overflow
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps5000GetValuesAsync)
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

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps5000Stop)
(
  int16_t  handle
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps5000PingUnit)
(
  int16_t  handle
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps5000SetNoOfCaptures)
(
  int16_t  handle,
  uint16_t nCaptures
);

#endif
