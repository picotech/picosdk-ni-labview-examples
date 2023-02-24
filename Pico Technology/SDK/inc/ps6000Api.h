/****************************************************************************
 *
 * Filename:    ps6000Api.h
 * Author:      MAS
 * Description:
 *
 * This header defines the interface to driver routines for the
 *  PicoScope 6000 Series PC Oscilloscopes.
 *
 * Copyright � 2009 - 2022 Pico Technology Ltd. All rights reserved.
 *
 ****************************************************************************/
#ifndef __PS6000API_H__
#define __PS6000API_H__

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
// If you are dynamically linking ps6000.dll into your project #define DYNLINK here
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

#define PS6000_MAX_OVERSAMPLE_8BIT 256

/* Although the PS6000 uses an 8-bit ADC, it is usually possible to
 * oversample (collect multiple readings at each time) by up to 256.
 * the results are therefore ALWAYS scaled up to 16-bits, even if
 * oversampling is not used.
 *
 * The maximum and minimum values returned are therefore as follows:
 */
#define PS6000_MAX_VALUE 32512
#define PS6000_MIN_VALUE -32512

#define MAX_PULSE_WIDTH_QUALIFIER_COUNT 16777215L

#define MAX_SIG_GEN_BUFFER_SIZE  16384
#define PS640X_C_D_MAX_SIG_GEN_BUFFER_SIZE 65536

#define MIN_SIG_GEN_BUFFER_SIZE        1
#define MIN_DWELL_COUNT                3
#define MAX_SWEEPS_SHOTS ((1 << 30) - 1)

#define MAX_WAVEFORMS_PER_SECOND  1000000

// supported by the PS6402 and PS6403
// for other devices use GetAnalogueOffset also
// PS6402 and PS6403 supports this function
#define MAX_ANALOGUE_OFFSET_50MV_200MV  0.500f
#define MIN_ANALOGUE_OFFSET_50MV_200MV -0.500f
#define MAX_ANALOGUE_OFFSET_500MV_2V    2.500f
#define MIN_ANALOGUE_OFFSET_500MV_2V   -2.500f
#define MAX_ANALOGUE_OFFSET_5V_20V        20.f
#define MIN_ANALOGUE_OFFSET_5V_20V       -20.f

#define PS6000_MAX_ETS_CYCLES 250
#define PS6000_MAX_INTERLEAVE  50

typedef enum enPS6000ExternalFrequency
{
  PS6000_FREQUENCY_OFF,
  PS6000_FREQUENCY_5MHZ,
  PS6000_FREQUENCY_10MHZ,
  PS6000_FREQUENCY_20MHZ,
  PS6000_FREQUENCY_25MHZ,
  PS6000_MAX_FREQUENCIES
} PS6000_EXTERNAL_FREQUENCY;

typedef enum  enPS6000BandwidthLimiter
{
  PS6000_BW_FULL,
  PS6000_BW_20MHZ,
  PS6000_BW_25MHZ,
} PS6000_BANDWIDTH_LIMITER;

typedef enum enPS6000Channel
{
  PS6000_CHANNEL_A,
  PS6000_CHANNEL_B,
  PS6000_CHANNEL_C,
  PS6000_CHANNEL_D,
  PS6000_EXTERNAL,
  PS6000_MAX_CHANNELS = PS6000_EXTERNAL,
  PS6000_TRIGGER_AUX,
  PS6000_MAX_TRIGGER_SOURCES
}  PS6000_CHANNEL;

typedef enum enPS6000ChannelBufferIndex
{
  PS6000_CHANNEL_A_MAX,
  PS6000_CHANNEL_A_MIN,
  PS6000_CHANNEL_B_MAX,
  PS6000_CHANNEL_B_MIN,
  PS6000_CHANNEL_C_MAX,
  PS6000_CHANNEL_C_MIN,
  PS6000_CHANNEL_D_MAX,
  PS6000_CHANNEL_D_MIN,
  PS6000_MAX_CHANNEL_BUFFERS
} PS6000_CHANNEL_BUFFER_INDEX;

typedef enum enPS6000Range
{
  PS6000_10MV,
  PS6000_20MV,
  PS6000_50MV,
  PS6000_100MV,
  PS6000_200MV,
  PS6000_500MV,
  PS6000_1V,
  PS6000_2V,
  PS6000_5V,
  PS6000_10V,
  PS6000_20V,
  PS6000_50V,
  PS6000_MAX_RANGES
}  PS6000_RANGE;


typedef enum enPS6000Coupling
{
  PS6000_AC,
  PS6000_DC_1M,
  PS6000_DC_50R
} PS6000_COUPLING;

typedef enum enPS6000EtsMode
{
  PS6000_ETS_OFF,             // ETS disabled
  PS6000_ETS_FAST,            // Return ready as soon as requested no of interleaves is available
  PS6000_ETS_SLOW,            // Return ready every time a new set of no_of_cycles is collected
  PS6000_ETS_MODES_MAX
}  PS6000_ETS_MODE;

typedef enum enPS6000TimeUnits
{
  PS6000_FS,
  PS6000_PS,
  PS6000_NS,
  PS6000_US,
  PS6000_MS,
  PS6000_S,
  PS6000_MAX_TIME_UNITS,
}  PS6000_TIME_UNITS;

typedef enum enPS6000SweepType
{
  PS6000_UP,
  PS6000_DOWN,
  PS6000_UPDOWN,
  PS6000_DOWNUP,
  PS6000_MAX_SWEEP_TYPES
} PS6000_SWEEP_TYPE;

typedef enum enPS6000WaveType
{
  PS6000_SINE,
  PS6000_SQUARE,
  PS6000_TRIANGLE,
  PS6000_RAMP_UP,
  PS6000_RAMP_DOWN,
  PS6000_SINC,
  PS6000_GAUSSIAN,
  PS6000_HALF_SINE,
  PS6000_DC_VOLTAGE,
  PS6000_MAX_WAVE_TYPES
} PS6000_WAVE_TYPE;

typedef enum enPS6000ExtraOperations
{
  PS6000_ES_OFF,
  PS6000_WHITENOISE,
  PS6000_PRBS // Pseudo-Random Bit Stream
} PS6000_EXTRA_OPERATIONS;

#define PS6000_PRBS_MAX_FREQUENCY       20000000.f
#define PS6000_SINE_MAX_FREQUENCY       20000000.f
#define PS6000_SQUARE_MAX_FREQUENCY     20000000.f
#define PS6000_TRIANGLE_MAX_FREQUENCY   20000000.f
#define PS6000_SINC_MAX_FREQUENCY       20000000.f
#define PS6000_RAMP_MAX_FREQUENCY       20000000.f
#define PS6000_HALF_SINE_MAX_FREQUENCY  20000000.f
#define PS6000_GAUSSIAN_MAX_FREQUENCY   20000000.f
#define PS6000_MIN_FREQUENCY                 0.03f

typedef enum enPS6000SigGenTrigType
{
  PS6000_SIGGEN_RISING,
  PS6000_SIGGEN_FALLING,
  PS6000_SIGGEN_GATE_HIGH,
  PS6000_SIGGEN_GATE_LOW
} PS6000_SIGGEN_TRIG_TYPE;

typedef enum enPS6000SigGenTrigSource
{
  PS6000_SIGGEN_NONE,
  PS6000_SIGGEN_SCOPE_TRIG,
  PS6000_SIGGEN_AUX_IN,
  PS6000_SIGGEN_EXT_IN,
  PS6000_SIGGEN_SOFT_TRIG,
  PS6000_SIGGEN_TRIGGER_RAW
} PS6000_SIGGEN_TRIG_SOURCE;

typedef enum enPS6000IndexMode
{
  PS6000_SINGLE,
  PS6000_DUAL,
  PS6000_QUAD,
  PS6000_MAX_INDEX_MODES
} PS6000_INDEX_MODE;

typedef enum enPS6000ThresholdMode
{
  PS6000_LEVEL,
  PS6000_WINDOW
} PS6000_THRESHOLD_MODE;

typedef enum enPS6000ThresholdDirection
{
  PS6000_ABOVE,             //using upper threshold
  PS6000_BELOW,							// using upper threshold
  PS6000_RISING,            // using upper threshold
  PS6000_FALLING,           // using upper threshold
  PS6000_RISING_OR_FALLING, // using upper threshold
  PS6000_ABOVE_LOWER,       // using lower threshold
  PS6000_BELOW_LOWER,       // using lower threshold
  PS6000_RISING_LOWER,      // using lower threshold
  PS6000_FALLING_LOWER,     // using lower threshold
  // Windowing using both thresholds
  PS6000_INSIDE        = PS6000_ABOVE,
  PS6000_OUTSIDE       = PS6000_BELOW,
  PS6000_ENTER         = PS6000_RISING,
  PS6000_EXIT          = PS6000_FALLING,
  PS6000_ENTER_OR_EXIT = PS6000_RISING_OR_FALLING,
  PS6000_POSITIVE_RUNT = 9,
  PS6000_NEGATIVE_RUNT,
  // no trigger set
  PS6000_NONE = PS6000_RISING
} PS6000_THRESHOLD_DIRECTION;

typedef enum enPS6000TriggerState
{
  PS6000_CONDITION_DONT_CARE,
  PS6000_CONDITION_TRUE,
  PS6000_CONDITION_FALSE,
  PS6000_CONDITION_MAX
} PS6000_TRIGGER_STATE;

#pragma pack(push,1)
typedef struct tPS6000TriggerInfo
{
	PICO_STATUS	status;
	uint32_t	segmentIndex;
	uint32_t	triggerIndex;
	int64_t		triggerTime;
	int16_t		timeUnits;
	int16_t		reserved0;
	uint64_t	timeStampCounter;
} PS6000_TRIGGER_INFO;

typedef struct tPS6000TriggerConditions
{
  PS6000_TRIGGER_STATE channelA;
  PS6000_TRIGGER_STATE channelB;
  PS6000_TRIGGER_STATE channelC;
  PS6000_TRIGGER_STATE channelD;
  PS6000_TRIGGER_STATE external;
  PS6000_TRIGGER_STATE aux;
  PS6000_TRIGGER_STATE pulseWidthQualifier;
} PS6000_TRIGGER_CONDITIONS;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct tPS6000PwqConditions
{
  PS6000_TRIGGER_STATE channelA;
  PS6000_TRIGGER_STATE channelB;
  PS6000_TRIGGER_STATE channelC;
  PS6000_TRIGGER_STATE channelD;
  PS6000_TRIGGER_STATE external;
  PS6000_TRIGGER_STATE aux;
} PS6000_PWQ_CONDITIONS;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct tPS6000TriggerChannelProperties
{
  int16_t            thresholdUpper;
  uint16_t  hysteresisUpper;
  int16_t            thresholdLower;
  uint16_t  hysteresisLower;
  PS6000_CHANNEL  channel;
  PS6000_THRESHOLD_MODE  thresholdMode;
} PS6000_TRIGGER_CHANNEL_PROPERTIES;
#pragma pack(pop)

typedef enum enPS6000RatioMode
{
  PS6000_RATIO_MODE_NONE,
  PS6000_RATIO_MODE_AGGREGATE    = 1,
  PS6000_RATIO_MODE_AVERAGE      = 2,
  PS6000_RATIO_MODE_DECIMATE     = 4,
  PS6000_RATIO_MODE_DISTRIBUTION = 8
} PS6000_RATIO_MODE;

typedef enum enPS6000PulseWidthType
{
  PS6000_PW_TYPE_NONE,
  PS6000_PW_TYPE_LESS_THAN,
  PS6000_PW_TYPE_GREATER_THAN,
  PS6000_PW_TYPE_IN_RANGE,
  PS6000_PW_TYPE_OUT_OF_RANGE
} PS6000_PULSE_WIDTH_TYPE;

typedef enum enPS6000Temperatures
{
	PS6000_WHAT_ARE_AVAILABLE = 0,
	PS6000_INTERNAL_TEMPERATURE = 1
} PS6000_TEMPERATURES;

typedef void (PREF4 *ps6000BlockReady)
(
  int16_t        handle,
  PICO_STATUS  status,
  void        *pParameter
);

typedef void (PREF4 *ps6000StreamingReady)
(
  int16_t          handle,
  uint32_t  noOfSamples,
  uint32_t  startIndex,
  int16_t          overflow,
  uint32_t  triggerAt,
  int16_t          triggered,
  int16_t          autoStop,
  void          *pParameter
);

typedef void (PREF4 *ps6000DataReady)
(
  int16_t          handle,
  PICO_STATUS    status,
  uint32_t  noOfSamples,
  int16_t          overflow,
  void          *pParameter
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000OpenUnit)
(
  int16_t *handle,
  int8_t  *serial
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000OpenUnitAsync)
(
  int16_t *status,
  int8_t  *serial
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000OpenUnitProgress)
(
  int16_t *handle,
  int16_t *progressPercent,
  int16_t *complete
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000GetUnitInfo)
(
  int16_t      handle,
  int8_t      *string,
  int16_t      stringLength,
  int16_t     *requiredSize,
  PICO_INFO  info
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000FlashLed)
(
  int16_t  handle,
  int16_t  start
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000CloseUnit)
(
  int16_t  handle
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000MemorySegments)
(
  int16_t          handle,
  uint32_t  nSegments,
  uint32_t *nMaxSamples
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000SetChannel)
(
  int16_t                     handle,
  PS6000_CHANNEL            channel,
  int16_t                     enabled,
  PS6000_COUPLING           type,
  PS6000_RANGE              range,
  float                     analogueOffset,
  PS6000_BANDWIDTH_LIMITER  bandwidth
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000GetTimebase)
(
  int16_t          handle,
  uint32_t  timebase,
  uint32_t  noSamples,
  int32_t          *timeIntervalNanoseconds,
  int16_t          oversample,
  uint32_t *maxSamples,
  uint32_t  segmentIndex
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000GetTimebase2)
(
  int16_t          handle,
  uint32_t  timebase,
  uint32_t  noSamples,
  float         *timeIntervalNanoseconds,
  int16_t          oversample,
  uint32_t *maxSamples,
  uint32_t  segmentIndex
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000SetSigGenArbitrary)
(
  int16_t                      handle,
  int32_t                       offsetVoltage,
  uint32_t              pkToPk,
  uint32_t              startDeltaPhase,
  uint32_t              stopDeltaPhase,
  uint32_t              deltaPhaseIncrement,
  uint32_t              dwellCount,
  int16_t                     *arbitraryWaveform,
  int32_t                       arbitraryWaveformSize,
  PS6000_SWEEP_TYPE          sweepType,
  PS6000_EXTRA_OPERATIONS    operation,
  PS6000_INDEX_MODE          indexMode,
  uint32_t              shots,
  uint32_t              sweeps,
  PS6000_SIGGEN_TRIG_TYPE    triggerType,
  PS6000_SIGGEN_TRIG_SOURCE  triggerSource,
  int16_t                      extInThreshold
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000SetSigGenBuiltIn)
(
  int16_t                      handle,
  int32_t                       offsetVoltage,
  uint32_t              pkToPk,
  int16_t                      waveType,
  float                      startFrequency,
  float                      stopFrequency,
  float                      increment,
  float                      dwellTime,
  PS6000_SWEEP_TYPE          sweepType,
  PS6000_EXTRA_OPERATIONS    operation,
  uint32_t              shots,
  uint32_t              sweeps,
  PS6000_SIGGEN_TRIG_TYPE    triggerType,
  PS6000_SIGGEN_TRIG_SOURCE  triggerSource,
  int16_t                      extInThreshold
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000SetSigGenBuiltInV2)
(
	int16_t										handle,
	int32_t										offsetVoltage,
	uint32_t									pkToPk,
	int16_t 									waveType,
	double 										startFrequency,
	double										stopFrequency,
	double 										increment,
	double 										dwellTime,
	PS6000_SWEEP_TYPE					sweepType,
	PS6000_EXTRA_OPERATIONS		operation,
	uint32_t									shots,
	uint32_t									sweeps,
	PS6000_SIGGEN_TRIG_TYPE		triggerType,
	PS6000_SIGGEN_TRIG_SOURCE triggerSource,
	int16_t										extInThreshold
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000SetSigGenPropertiesArbitrary)
(
  int16_t                      handle,
  int32_t                       offsetVoltage,
  uint32_t              pkToPk,
  uint32_t              startDeltaPhase,
  uint32_t              stopDeltaPhase,
  uint32_t              deltaPhaseIncrement,
  uint32_t              dwellCount,
  PS6000_SWEEP_TYPE          sweepType,
  uint32_t              shots,
  uint32_t              sweeps,
  PS6000_SIGGEN_TRIG_TYPE    triggerType,
  PS6000_SIGGEN_TRIG_SOURCE  triggerSource,
  int16_t                      extInThreshold
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000SetSigGenPropertiesBuiltIn)
(
  int16_t                      handle,
  int32_t                       offsetVoltage,
  uint32_t              pkToPk,
  double                      startFrequency,
  double                      stopFrequency,
  double                      increment,
  double                      dwellTime,
  PS6000_SWEEP_TYPE          sweepType,
  uint32_t              shots,
  uint32_t              sweeps,
  PS6000_SIGGEN_TRIG_TYPE    triggerType,
  PS6000_SIGGEN_TRIG_SOURCE  triggerSource,
  int16_t                      extInThreshold
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000SigGenFrequencyToPhase)
	(
	int16_t												handle,
	double												frequency,
	PS6000_INDEX_MODE							indexMode,
	uint32_t											bufferLength,
	uint32_t										* phase
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000SigGenArbitraryMinMaxValues)
	(
	int16_t			handle,
	int16_t		*	minArbitraryWaveformValue,
	int16_t		*	maxArbitraryWaveformValue,
	uint32_t  * minArbitraryWaveformSize,
	uint32_t	*	maxArbitraryWaveformSize
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000SigGenSoftwareControl)
(
  int16_t  handle,
  int16_t  state
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000SetSimpleTrigger)
(
  int16_t                       handle,
  int16_t                       enable,
  PS6000_CHANNEL              source,
  int16_t                       threshold,
  PS6000_THRESHOLD_DIRECTION  direction,
  uint32_t               delay,
  int16_t                       autoTrigger_ms
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000SetEts)
(
  int16_t            handle,
  PS6000_ETS_MODE  mode,
  int16_t            etsCycles,
  int16_t            etsInterleave,
  int32_t            *sampleTimePicoseconds
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000SetTriggerChannelProperties)
(
  int16_t                              handle,
  PS6000_TRIGGER_CHANNEL_PROPERTIES *channelProperties,
  int16_t                              nChannelProperties,
  int16_t                              auxOutputEnable,
  int32_t                               autoTriggerMilliseconds
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000SetTriggerChannelConditions)
(
  int16_t                      handle,
  PS6000_TRIGGER_CONDITIONS *conditions,
  int16_t                      nConditions
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000SetTriggerChannelDirections)
(
  int16_t                       handle,
  PS6000_THRESHOLD_DIRECTION  channelA,
  PS6000_THRESHOLD_DIRECTION  channelB,
  PS6000_THRESHOLD_DIRECTION  channelC,
  PS6000_THRESHOLD_DIRECTION  channelD,
  PS6000_THRESHOLD_DIRECTION  ext,
  PS6000_THRESHOLD_DIRECTION  aux
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000SetTriggerDelay)
(
  int16_t          handle,
  uint32_t  delay
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000SetPulseWidthQualifier)
(
  int16_t                       handle,
  PS6000_PWQ_CONDITIONS      *conditions,
  int16_t                       nConditions,
  PS6000_THRESHOLD_DIRECTION  direction,
  uint32_t               lower,
  uint32_t               upper,
  PS6000_PULSE_WIDTH_TYPE     type
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000IsTriggerOrPulseWidthQualifierEnabled)
(
  int16_t  handle,
  int16_t *triggerEnabled,
  int16_t *pulseWidthQualifierEnabled
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000GetTriggerTimeOffset)
(
  int16_t              handle,
  uint32_t     *timeUpper,
  uint32_t     *timeLower,
  PS6000_TIME_UNITS *timeUnits,
  uint32_t      segmentIndex
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000GetTriggerTimeOffset64)
(
  int16_t              handle,
  int64_t           *time,
  PS6000_TIME_UNITS *timeUnits,
  uint32_t      segmentIndex
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000GetValuesTriggerTimeOffsetBulk)
(
  int16_t              handle,
  uint32_t     *timesUpper,
  uint32_t     *timesLower,
  PS6000_TIME_UNITS *timeUnits,
  uint32_t      fromSegmentIndex,
  uint32_t      toSegmentIndex
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000GetValuesTriggerTimeOffsetBulk64)
(
  int16_t              handle,
  int64_t           *times,
  PS6000_TIME_UNITS *timeUnits,
  uint32_t      fromSegmentIndex,
  uint32_t      toSegmentIndex
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000SetDataBuffers)
(
  int16_t             handle,
  PS6000_CHANNEL    channel,
  int16_t            *bufferMax,
  int16_t            *bufferMin,
  uint32_t     bufferLth,
  PS6000_RATIO_MODE downSampleRatioMode
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000SetDataBuffer)
(
  int16_t              handle,
  PS6000_CHANNEL     channel,
  int16_t             *buffer,
  uint32_t      bufferLth,
  PS6000_RATIO_MODE  downSampleRatioMode
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000SetDataBufferBulk)
(
  int16_t              handle,
  PS6000_CHANNEL     channel,
  int16_t             *buffer,
  uint32_t      bufferLth,
  uint32_t      waveform,
  PS6000_RATIO_MODE  downSampleRatioMode
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000SetDataBuffersBulk)
(
  int16_t              handle,
  PS6000_CHANNEL     channel,
  int16_t             *bufferMax,
  int16_t             *bufferMin,
  uint32_t      bufferLth,
  uint32_t      waveform,
  PS6000_RATIO_MODE  downSampleRatioMode
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000SetEtsTimeBuffer)
(
  int16_t          handle,
  int64_t       *buffer,
  uint32_t  bufferLth
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000SetEtsTimeBuffers)
(
  int16_t          handle,
  uint32_t *timeUpper,
  uint32_t *timeLower,
  uint32_t  bufferLth
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000RunBlock)
(
  int16_t             handle,
  uint32_t     noOfPreTriggerSamples,
  uint32_t     noOfPostTriggerSamples,
  uint32_t     timebase,
  int16_t             oversample,
  int32_t             *timeIndisposedMs,
  uint32_t     segmentIndex,
  ps6000BlockReady  lpReady,
  void             *pParameter
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000IsReady)
(
  int16_t  handle,
  int16_t *ready
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000RunStreaming)
(
  int16_t              handle,
  uint32_t     *sampleInterval,
  PS6000_TIME_UNITS  sampleIntervalTimeUnits,
  uint32_t      maxPreTriggerSamples,
  uint32_t      maxPostPreTriggerSamples,
  int16_t              autoStop,
  uint32_t      downSampleRatio,
  PS6000_RATIO_MODE  downSampleRatioMode,
  uint32_t      overviewBufferSize
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000GetStreamingLatestValues)
(
  int16_t                 handle,
  ps6000StreamingReady  lpPs6000Ready,
  void                 *pParameter
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000NoOfStreamingValues)
(
  int16_t          handle,
  uint32_t *noOfValues
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000GetMaxDownSampleRatio)
(
  int16_t              handle,
  uint32_t      noOfUnaggreatedSamples,
  uint32_t     *maxDownSampleRatio,
  PS6000_RATIO_MODE  downSampleRatioMode,
  uint32_t      segmentIndex
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000GetValues)
(
  int16_t              handle,
  uint32_t      startIndex,
  uint32_t     *noOfSamples,
  uint32_t      downSampleRatio,
  PS6000_RATIO_MODE  downSampleRatioMode,
  uint32_t      segmentIndex,
  int16_t             *overflow
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000GetValuesBulk)
(
  int16_t              handle,
  uint32_t     *noOfSamples,
  uint32_t      fromSegmentIndex,
  uint32_t      toSegmentIndex,
  uint32_t      downSampleRatio,
  PS6000_RATIO_MODE  downSampleRatioMode,
  int16_t             *overflow
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000GetValuesAsync)
(
  int16_t              handle,
  uint32_t      startIndex,
  uint32_t      noOfSamples,
  uint32_t      downSampleRatio,
  PS6000_RATIO_MODE  downSampleRatioMode,
  uint32_t      segmentIndex,
  void              *lpDataReady,
  void              *pParameter
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000GetValuesOverlapped)
(
  int16_t              handle,
  uint32_t      startIndex,
  uint32_t     *noOfSamples,
  uint32_t      downSampleRatio,
  PS6000_RATIO_MODE  downSampleRatioMode,
  uint32_t      segmentIndex,
  int16_t             *overflow
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000GetValuesOverlappedBulk)
(
  int16_t              handle,
  uint32_t      startIndex,
  uint32_t     *noOfSamples,
  uint32_t      downSampleRatio,
  PS6000_RATIO_MODE  downSampleRatioMode,
  uint32_t      fromSegmentIndex,
  uint32_t      toSegmentIndex,
  int16_t             *overflow
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000GetValuesBulkAsyc)
(
  int16_t              handle,
  uint32_t      startIndex,
  uint32_t     *noOfSamples,
  uint32_t      downSampleRatio,
  PS6000_RATIO_MODE  downSampleRatioMode,
  uint32_t      fromSegmentIndex,
  uint32_t      toSegmentIndex,
  int16_t             *overflow
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000GetNoOfCaptures)
(
  int16_t          handle,
  uint32_t *nCaptures
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000GetNoOfProcessedCaptures)
(
  int16_t          handle,
  uint32_t *nProcessedCaptures
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000Stop)
(
  int16_t  handle
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000SetNoOfCaptures)
(
  int16_t          handle,
  uint32_t  nCaptures
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000SetWaveformLimiter)
(
  int16_t          handle,
  uint32_t  nWaveformsPerSecond
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000GetTriggerInfoBulk)
(
	int16_t										handle,
	PS6000_TRIGGER_INFO			*	triggerInfo,
	uint32_t									fromSegmentIndex,
	uint32_t									toSegmentIndex
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000EnumerateUnits)
(
  int16_t *count,
  int8_t  *serials,
  int16_t *serialLth
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000SetExternalClock)
(
  int16_t                      handle,
  PS6000_EXTERNAL_FREQUENCY  frequency,
  int16_t                      threshold
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000PingUnit)
(
  int16_t  handle
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000GetAnalogueOffset)
(
  int16_t            handle,
  PS6000_RANGE     range,
  PS6000_COUPLING  coupling,
  float           *maximumVoltage,
  float           *minimumVoltage
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000QueryTemperatures)
(
	int16_t					handle,
	PS6000_TEMPERATURES * types,
	float * temperatures
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000QueryOutputEdgeDetect)
(
	int16_t		handle,
	int16_t * state
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000SetOutputEdgeDetect)
(
	int16_t	handle,
	int16_t state
);
#endif
