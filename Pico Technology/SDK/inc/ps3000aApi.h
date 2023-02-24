/****************************************************************************
 *
 * Filename:    ps3000aApi.h
 * Author:      MAS
 * Description:
 *
 * This header defines the interface to driver routines for the
 *	PicoScope 3000A, B and D Series PC Oscilloscopes.
 *
 * Copyright � 2010 - 2022 Pico Technology Ltd. All rights reserved.
 *
 ****************************************************************************/
#ifndef __PS3000AAPI_H__
#define __PS3000AAPI_H__

#include <stdint.h>

#include "PicoCallback.h"
#include "PicoStatus.h"
#include "PicoVersion.h"

#ifdef __cplusplus
  #define PREF0 extern "C"
  #define TYPE_ENUM
#else
  #define PREF0
  #define TYPE_ENUM enum
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
  //If you are dynamically linking ps3000a.dll into your project #define DYNLINK here
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

#define PS3000A_MAX_OVERSAMPLE  256

/* Depending on the adc;oversample (collect multiple readings at each time) by up to 256.
 * the results are therefore ALWAYS scaled up to 16-bits, even if
 * oversampling is not used.
 *
 * The maximum and minimum values returned are therefore as follows:
 */

#define PS3207A_MAX_ETS_CYCLES  500
#define PS3207A_MAX_INTERLEAVE   40

#define PS3206A_MAX_ETS_CYCLES  500
#define PS3206A_MAX_INTERLEAVE   40
#define PS3206MSO_MAX_INTERLEAVE 80

#define PS3205A_MAX_ETS_CYCLES  250
#define PS3205A_MAX_INTERLEAVE   20
#define PS3205MSO_MAX_INTERLEAVE 40

#define PS3204A_MAX_ETS_CYCLES  125
#define PS3204A_MAX_INTERLEAVE   10
#define PS3204MSO_MAX_INTERLEAVE 20

#define PS3000A_EXT_MAX_VALUE  32767
#define PS3000A_EXT_MIN_VALUE -32767

#define PS3000A_MAX_LOGIC_LEVEL  32767
#define PS3000A_MIN_LOGIC_LEVEL -32767

#define MIN_SIG_GEN_FREQ 0.0f
#define MAX_SIG_GEN_FREQ 20000000.0f

#define PS3207B_MAX_SIG_GEN_BUFFER_SIZE 32768
#define PS3206B_MAX_SIG_GEN_BUFFER_SIZE 16384
#define MAX_SIG_GEN_BUFFER_SIZE         8192
#define MIN_SIG_GEN_BUFFER_SIZE         1
#define MIN_DWELL_COUNT                 3
#define MAX_SWEEPS_SHOTS       ((1 << 30) - 1)

#define MAX_ANALOGUE_OFFSET_50MV_200MV  0.250f
#define MIN_ANALOGUE_OFFSET_50MV_200MV -0.250f
#define MAX_ANALOGUE_OFFSET_500MV_2V    2.500f
#define MIN_ANALOGUE_OFFSET_500MV_2V   -2.500f
#define MAX_ANALOGUE_OFFSET_5V_20V        20.f
#define MIN_ANALOGUE_OFFSET_5V_20V       -20.f

#define PS3000A_SHOT_SWEEP_TRIGGER_CONTINUOUS_RUN 0xFFFFFFFF

typedef enum enPS3000ABandwidthLimiter
{
  PS3000A_BW_FULL,
  PS3000A_BW_20MHZ,
} PS3000A_BANDWIDTH_LIMITER;

typedef enum enPS3000AChannelBufferIndex
{
  PS3000A_CHANNEL_A_MAX,
  PS3000A_CHANNEL_A_MIN,
  PS3000A_CHANNEL_B_MAX,
  PS3000A_CHANNEL_B_MIN,
  PS3000A_CHANNEL_C_MAX,
  PS3000A_CHANNEL_C_MIN,
  PS3000A_CHANNEL_D_MAX,
  PS3000A_CHANNEL_D_MIN,
  PS3000A_MAX_CHANNEL_BUFFERS
} PS3000A_CHANNEL_BUFFER_INDEX;

typedef enum enPS3000AChannel
{
  PS3000A_CHANNEL_A,
  PS3000A_CHANNEL_B,
  PS3000A_CHANNEL_C,
  PS3000A_CHANNEL_D,
  PS3000A_EXTERNAL,
  PS3000A_MAX_CHANNELS = PS3000A_EXTERNAL,
  PS3000A_TRIGGER_AUX,
  PS3000A_MAX_TRIGGER_SOURCES
} PS3000A_CHANNEL;

typedef enum enPS3000ADigitalPort
{
  PS3000A_DIGITAL_PORT0 = 0x80, // digital channel 0 - 7
  PS3000A_DIGITAL_PORT1,             // digital channel 8 - 15
  PS3000A_DIGITAL_PORT2,             // digital channel 16 - 23
  PS3000A_DIGITAL_PORT3,             // digital channel 24 - 31
  PS3000A_MAX_DIGITAL_PORTS = (PS3000A_DIGITAL_PORT3 - PS3000A_DIGITAL_PORT0) + 1
} PS3000A_DIGITAL_PORT;

typedef enum enPS3000ADigitalChannel
{
  PS3000A_DIGITAL_CHANNEL_0,
  PS3000A_DIGITAL_CHANNEL_1,
  PS3000A_DIGITAL_CHANNEL_2,
  PS3000A_DIGITAL_CHANNEL_3,
  PS3000A_DIGITAL_CHANNEL_4,
  PS3000A_DIGITAL_CHANNEL_5,
  PS3000A_DIGITAL_CHANNEL_6,
  PS3000A_DIGITAL_CHANNEL_7,
  PS3000A_DIGITAL_CHANNEL_8,
  PS3000A_DIGITAL_CHANNEL_9,
  PS3000A_DIGITAL_CHANNEL_10,
  PS3000A_DIGITAL_CHANNEL_11,
  PS3000A_DIGITAL_CHANNEL_12,
  PS3000A_DIGITAL_CHANNEL_13,
  PS3000A_DIGITAL_CHANNEL_14,
  PS3000A_DIGITAL_CHANNEL_15,
  PS3000A_DIGITAL_CHANNEL_16,
  PS3000A_DIGITAL_CHANNEL_17,
  PS3000A_DIGITAL_CHANNEL_18,
  PS3000A_DIGITAL_CHANNEL_19,
  PS3000A_DIGITAL_CHANNEL_20,
  PS3000A_DIGITAL_CHANNEL_21,
  PS3000A_DIGITAL_CHANNEL_22,
  PS3000A_DIGITAL_CHANNEL_23,
  PS3000A_DIGITAL_CHANNEL_24,
  PS3000A_DIGITAL_CHANNEL_25,
  PS3000A_DIGITAL_CHANNEL_26,
  PS3000A_DIGITAL_CHANNEL_27,
  PS3000A_DIGITAL_CHANNEL_28,
  PS3000A_DIGITAL_CHANNEL_29,
  PS3000A_DIGITAL_CHANNEL_30,
  PS3000A_DIGITAL_CHANNEL_31,
  PS3000A_MAX_DIGITAL_CHANNELS
} PS3000A_DIGITAL_CHANNEL;

typedef enum enPS3000ARange
{
  PS3000A_10MV,
  PS3000A_20MV,
  PS3000A_50MV,
  PS3000A_100MV,
  PS3000A_200MV,
  PS3000A_500MV,
  PS3000A_1V,
  PS3000A_2V,
  PS3000A_5V,
  PS3000A_10V,
  PS3000A_20V,
  PS3000A_50V,
  PS3000A_MAX_RANGES,
} PS3000A_RANGE;

typedef enum enPS3000ACoupling
{
  PS3000A_AC,
  PS3000A_DC
} PS3000A_COUPLING;

typedef enum enPS3000AChannelInfo
{
  PS3000A_CI_RANGES,
} PS3000A_CHANNEL_INFO;

typedef enum enPS3000AEtsMode
{
  PS3000A_ETS_OFF, // ETS disabled
  PS3000A_ETS_FAST,
  PS3000A_ETS_SLOW,
  PS3000A_ETS_MODES_MAX
} PS3000A_ETS_MODE;

typedef enum enPS3000ATimeUnits
{
  PS3000A_FS,
  PS3000A_PS,
  PS3000A_NS,
  PS3000A_US,
  PS3000A_MS,
  PS3000A_S,
  PS3000A_MAX_TIME_UNITS,
} PS3000A_TIME_UNITS;

typedef enum enPS3000ASweepType
{
  PS3000A_UP,
  PS3000A_DOWN,
  PS3000A_UPDOWN,
  PS3000A_DOWNUP,
  PS3000A_MAX_SWEEP_TYPES
} PS3000A_SWEEP_TYPE;

typedef enum enPS3000AWaveType
{
  PS3000A_SINE,
  PS3000A_SQUARE,
  PS3000A_TRIANGLE,
  PS3000A_RAMP_UP,
  PS3000A_RAMP_DOWN,
  PS3000A_SINC,
  PS3000A_GAUSSIAN,
  PS3000A_HALF_SINE,
  PS3000A_DC_VOLTAGE,
  PS3000A_MAX_WAVE_TYPES
} PS3000A_WAVE_TYPE;

typedef enum enPS3000AExtraOperations
{
  PS3000A_ES_OFF,
  PS3000A_WHITENOISE,
  PS3000A_PRBS // Pseudo-Random Bit Stream
} PS3000A_EXTRA_OPERATIONS;

#define PS3000A_SINE_MAX_FREQUENCY       1000000.f
#define PS3000A_SQUARE_MAX_FREQUENCY     1000000.f
#define PS3000A_TRIANGLE_MAX_FREQUENCY   1000000.f
#define PS3000A_SINC_MAX_FREQUENCY       1000000.f
#define PS3000A_RAMP_MAX_FREQUENCY       1000000.f
#define PS3000A_HALF_SINE_MAX_FREQUENCY  1000000.f
#define PS3000A_GAUSSIAN_MAX_FREQUENCY   1000000.f
#define PS3000A_PRBS_MAX_FREQUENCY       1000000.f
#define PS3000A_PRBS_MIN_FREQUENCY           0.03f
#define PS3000A_MIN_FREQUENCY                0.03f

typedef enum enPS3000ASigGenTrigType
{
  PS3000A_SIGGEN_RISING,
  PS3000A_SIGGEN_FALLING,
  PS3000A_SIGGEN_GATE_HIGH,
  PS3000A_SIGGEN_GATE_LOW
} PS3000A_SIGGEN_TRIG_TYPE;

typedef enum enPS3000ASigGenTrigSource
{
  PS3000A_SIGGEN_NONE,
  PS3000A_SIGGEN_SCOPE_TRIG,
  PS3000A_SIGGEN_AUX_IN,
  PS3000A_SIGGEN_EXT_IN,
  PS3000A_SIGGEN_SOFT_TRIG
} PS3000A_SIGGEN_TRIG_SOURCE;

typedef enum enPS3000AIndexMode
{
  PS3000A_SINGLE,
  PS3000A_DUAL,
  PS3000A_QUAD,
  PS3000A_MAX_INDEX_MODES
} PS3000A_INDEX_MODE;

typedef enum enPS3000A_ThresholdMode
{
  PS3000A_LEVEL,
  PS3000A_WINDOW
} PS3000A_THRESHOLD_MODE;

typedef enum enPS3000AThresholdDirection
{
  PS3000A_ABOVE,             //using upper threshold
  PS3000A_BELOW,						 //using upper threshold
  PS3000A_RISING,            // using upper threshold
  PS3000A_FALLING,           // using upper threshold
  PS3000A_RISING_OR_FALLING, // using both threshold
  PS3000A_ABOVE_LOWER,       // using lower threshold
  PS3000A_BELOW_LOWER,       // using lower threshold
  PS3000A_RISING_LOWER,      // using lower threshold
  PS3000A_FALLING_LOWER,     // using lower threshold
  // Windowing using both thresholds
  PS3000A_INSIDE        = PS3000A_ABOVE,
  PS3000A_OUTSIDE       = PS3000A_BELOW,
  PS3000A_ENTER         = PS3000A_RISING,
  PS3000A_EXIT          = PS3000A_FALLING,
  PS3000A_ENTER_OR_EXIT = PS3000A_RISING_OR_FALLING,
  PS3000A_POSITIVE_RUNT = 9,
  PS3000A_NEGATIVE_RUNT,
  // no trigger set
  PS3000A_NONE = PS3000A_RISING
} PS3000A_THRESHOLD_DIRECTION;

typedef enum enPS3000ADigitalDirection
{
  PS3000A_DIGITAL_DONT_CARE,
  PS3000A_DIGITAL_DIRECTION_LOW,
  PS3000A_DIGITAL_DIRECTION_HIGH,
  PS3000A_DIGITAL_DIRECTION_RISING,
  PS3000A_DIGITAL_DIRECTION_FALLING,
  PS3000A_DIGITAL_DIRECTION_RISING_OR_FALLING,
  PS3000A_DIGITAL_MAX_DIRECTION
} PS3000A_DIGITAL_DIRECTION;

typedef enum enPS3000ATriggerState
{
  PS3000A_CONDITION_DONT_CARE,
  PS3000A_CONDITION_TRUE,
  PS3000A_CONDITION_FALSE,
  PS3000A_CONDITION_MAX
} PS3000A_TRIGGER_STATE;

#pragma pack(push,1)
typedef struct tPS3000ATriggerConditions
{
  PS3000A_TRIGGER_STATE channelA;
  PS3000A_TRIGGER_STATE channelB;
  PS3000A_TRIGGER_STATE channelC;
  PS3000A_TRIGGER_STATE channelD;
  PS3000A_TRIGGER_STATE external;
  PS3000A_TRIGGER_STATE aux;
  PS3000A_TRIGGER_STATE pulseWidthQualifier;
} PS3000A_TRIGGER_CONDITIONS;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct tPS3000ATriggerConditionsV2
{
  PS3000A_TRIGGER_STATE channelA;
  PS3000A_TRIGGER_STATE channelB;
  PS3000A_TRIGGER_STATE channelC;
  PS3000A_TRIGGER_STATE channelD;
  PS3000A_TRIGGER_STATE external;
  PS3000A_TRIGGER_STATE aux;
  PS3000A_TRIGGER_STATE pulseWidthQualifier;
  PS3000A_TRIGGER_STATE digital;
} PS3000A_TRIGGER_CONDITIONS_V2;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct tPS3000APwqConditions
{
  PS3000A_TRIGGER_STATE channelA;
  PS3000A_TRIGGER_STATE channelB;
  PS3000A_TRIGGER_STATE channelC;
  PS3000A_TRIGGER_STATE channelD;
  PS3000A_TRIGGER_STATE external;
  PS3000A_TRIGGER_STATE aux;
} PS3000A_PWQ_CONDITIONS;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct tPS3000APwqConditionsV2
{
  PS3000A_TRIGGER_STATE channelA;
  PS3000A_TRIGGER_STATE channelB;
  PS3000A_TRIGGER_STATE channelC;
  PS3000A_TRIGGER_STATE channelD;
  PS3000A_TRIGGER_STATE external;
  PS3000A_TRIGGER_STATE aux;
  PS3000A_TRIGGER_STATE digital;
} PS3000A_PWQ_CONDITIONS_V2;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct tPS3000ADigitalChannelDirections
{
  PS3000A_DIGITAL_CHANNEL   channel;
  PS3000A_DIGITAL_DIRECTION direction;
} PS3000A_DIGITAL_CHANNEL_DIRECTIONS;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct tPS3000ATriggerChannelProperties
{
  int16_t                   thresholdUpper;
  uint16_t          thresholdUpperHysteresis;
  int16_t                   thresholdLower;
  uint16_t          thresholdLowerHysteresis;
  PS3000A_CHANNEL         channel;
  PS3000A_THRESHOLD_MODE  thresholdMode;
} PS3000A_TRIGGER_CHANNEL_PROPERTIES;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct tPS3000ATriggerInfo
{
	PICO_STATUS		status;
	uint32_t		segmentIndex;
	uint32_t		reserved0;
	int64_t			triggerTime;
	int16_t			timeUnits;
	int16_t			reserved1;
	uint64_t		timeStampCounter;
} PS3000A_TRIGGER_INFO;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct tPS3000AScalingFactors
{
	PS3000A_CHANNEL channelOrPort;
	PS3000A_RANGE   range;
	int16_t         offset;
	double          scalingFactor;
}PS3000A_SCALING_FACTORS_VALUES;
#pragma pack(pop)

typedef enum enPS3000ARatioMode
{
  PS3000A_RATIO_MODE_NONE,
  PS3000A_RATIO_MODE_AGGREGATE = 1,
  PS3000A_RATIO_MODE_DECIMATE  = 2,
  PS3000A_RATIO_MODE_AVERAGE   = 4,
} PS3000A_RATIO_MODE;

typedef enum enPS3000APulseWidthType
{
  PS3000A_PW_TYPE_NONE,
  PS3000A_PW_TYPE_LESS_THAN,
  PS3000A_PW_TYPE_GREATER_THAN,
  PS3000A_PW_TYPE_IN_RANGE,
  PS3000A_PW_TYPE_OUT_OF_RANGE
} PS3000A_PULSE_WIDTH_TYPE;

typedef enum enPS3000AHoldOffType
{
  PS3000A_TIME,
  PS3000A_EVENT,
  PS3000A_MAX_HOLDOFF_TYPE
} PS3000A_HOLDOFF_TYPE;

typedef void (__stdcall *ps3000aBlockReady)
(
  int16_t       handle,
  PICO_STATUS status,
  void       *pParameter
);

typedef void (__stdcall *ps3000aStreamingReady)
(
  int16_t          handle,
  int32_t           noOfSamples,
  uint32_t  startIndex,
  int16_t          overflow,
  uint32_t  triggerAt,
  int16_t          triggered,
  int16_t          autoStop,
  void          *pParameter
);

typedef void (__stdcall *ps3000aDataReady)
(
  int16_t          handle,
  PICO_STATUS    status,
  uint32_t  noOfSamples,
  int16_t          overflow,
  void          *pParameter
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aOpenUnit)
(
  int16_t *handle,
  int8_t  *serial
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aOpenUnitAsync)
(
  int16_t *status,
  int8_t  *serial
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aOpenUnitProgress)
(
  int16_t *handle,
  int16_t *progressPercent,
  int16_t *complete
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aGetUnitInfo)
 (
  int16_t      handle,
  int8_t      *string,
  int16_t      stringLength,
  int16_t     *requiredSize,
  PICO_INFO  info
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aFlashLed)
(
  int16_t  handle,
  int16_t  start
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aCloseUnit)
(
  int16_t  handle
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aMemorySegments)
(
  int16_t           handle,
  uint32_t  nSegments,
  int32_t           *nMaxSamples
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aSetChannel)
(
  int16_t             handle,
  PS3000A_CHANNEL   channel,
  int16_t             enabled,
  PS3000A_COUPLING  type,
  PS3000A_RANGE     range,
  float             analogOffset
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aSetDigitalPort)
(
  int16_t                 handle,
  PS3000A_DIGITAL_PORT  port,
  int16_t                 enabled,
  int16_t                 logicLevel
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aSetBandwidthFilter)
(
  int16_t                      handle,
  PS3000A_CHANNEL            channel,
  PS3000A_BANDWIDTH_LIMITER  bandwidth
);


PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aSetNoOfCaptures)
(
  int16_t           handle,
  uint32_t  nCaptures
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aGetTimebase)
(
  int16_t           handle,
  uint32_t   timebase,
  int32_t            noSamples,
  int32_t           *timeIntervalNanoseconds,
  int16_t           oversample,
  int32_t           *maxSamples,
  uint32_t  segmentIndex
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aGetTimebase2)
(
  int16_t           handle,
  uint32_t   timebase,
  int32_t            noSamples,
  float          *timeIntervalNanoseconds,
  int16_t           oversample,
  int32_t           *maxSamples,
  uint32_t  segmentIndex
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aSetSigGenArbitrary)
(
  int16_t                       handle,
  int32_t                        offsetVoltage,
  uint32_t               pkToPk,
  uint32_t               startDeltaPhase,
  uint32_t               stopDeltaPhase,
  uint32_t               deltaPhaseIncrement,
  uint32_t               dwellCount,
  int16_t                      *arbitraryWaveform,
  int32_t                        arbitraryWaveformSize,
  PS3000A_SWEEP_TYPE          sweepType,
  PS3000A_EXTRA_OPERATIONS    operation,
  PS3000A_INDEX_MODE          indexMode,
  uint32_t               shots,
  uint32_t               sweeps,
  PS3000A_SIGGEN_TRIG_TYPE    triggerType,
  PS3000A_SIGGEN_TRIG_SOURCE  triggerSource,
  int16_t                       extInThreshold
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps3000aSetSigGenBuiltIn)
(
  int16_t                       handle,
  int32_t                        offsetVoltage,
  uint32_t               pkToPk,
  int16_t                       waveType,
  float                       startFrequency,
  float                       stopFrequency,
  float                       increment,
  float                       dwellTime,
  PS3000A_SWEEP_TYPE          sweepType,
  PS3000A_EXTRA_OPERATIONS    operation,
  uint32_t               shots,
  uint32_t               sweeps,
  PS3000A_SIGGEN_TRIG_TYPE    triggerType,
  PS3000A_SIGGEN_TRIG_SOURCE  triggerSource,
  int16_t                       extInThreshold
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps3000aSetSigGenBuiltInV2)
(
  int16_t                       handle,
  int32_t                        offsetVoltage,
  uint32_t               pkToPk,
  int16_t                       waveType,
  double                       startFrequency,
  double                       stopFrequency,
	double											 increment,
  double                       dwellTime,
  PS3000A_SWEEP_TYPE          sweepType,
  PS3000A_EXTRA_OPERATIONS    operation,
  uint32_t               shots,
  uint32_t               sweeps,
  PS3000A_SIGGEN_TRIG_TYPE    triggerType,
  PS3000A_SIGGEN_TRIG_SOURCE  triggerSource,
  int16_t                       extInThreshold
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aSetSigGenPropertiesArbitrary)
(
  int16_t                       handle,
  uint32_t               startDeltaPhase,
  uint32_t               stopDeltaPhase,
  uint32_t               deltaPhaseIncrement,
  uint32_t               dwellCount,
  PS3000A_SWEEP_TYPE          sweepType,
  uint32_t               shots,
  uint32_t               sweeps,
  PS3000A_SIGGEN_TRIG_TYPE    triggerType,
  PS3000A_SIGGEN_TRIG_SOURCE  triggerSource,
  int16_t                       extInThreshold
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps3000aSetSigGenPropertiesBuiltIn)
(
  int16_t                       handle,
  double                       startFrequency,
  double                       stopFrequency,
  double                       increment,
  double                       dwellTime,
  PS3000A_SWEEP_TYPE          sweepType,
  uint32_t               shots,
  uint32_t               sweeps,
  PS3000A_SIGGEN_TRIG_TYPE    triggerType,
  PS3000A_SIGGEN_TRIG_SOURCE  triggerSource,
  int16_t                       extInThreshold
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps3000aSigGenFrequencyToPhase)
	(
	int16_t												handle,
	double												frequency,
	PS3000A_INDEX_MODE						indexMode,
	uint32_t											bufferLength,
	uint32_t										* phase
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps3000aSigGenArbitraryMinMaxValues)
	(
	int16_t			handle,
	int16_t		*	minArbitraryWaveformValue,
	int16_t		*	maxArbitraryWaveformValue,
	uint32_t	* minArbitraryWaveformSize,
	uint32_t	*	maxArbitraryWaveformSize
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps3000aGetMaxEtsValues)
	(
	int16_t			 handle,
	int16_t    * etsCycles,
	int16_t    * etsInterleave
	);


PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aSigGenSoftwareControl)
(
  int16_t  handle,
  int16_t  state
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aSetEts)
(
  int16_t             handle,
  PS3000A_ETS_MODE  mode,
  int16_t             etsCycles,
  int16_t             etsInterleave,
  int32_t             *sampleTimePicoseconds
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aSetSimpleTrigger)
(
  int16_t                        handle,
  int16_t                        enable,
  PS3000A_CHANNEL              source,
  int16_t                        threshold,
  PS3000A_THRESHOLD_DIRECTION  direction,
  uint32_t                delay,
  int16_t                        autoTrigger_ms
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aSetTriggerDigitalPortProperties)
(
  int16_t                               handle,
  PS3000A_DIGITAL_CHANNEL_DIRECTIONS *directions,
  int16_t                               nDirections
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aSetPulseWidthDigitalPortProperties)
	(
	int16_t                               handle,
	PS3000A_DIGITAL_CHANNEL_DIRECTIONS *directions,
	int16_t                               nDirections
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aSetTriggerChannelProperties)
(
  int16_t                               handle,
  PS3000A_TRIGGER_CHANNEL_PROPERTIES *channelProperties,
  int16_t                               nChannelProperties,
  int16_t                               auxOutputEnable,
  int32_t                                autoTriggerMilliseconds
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aSetTriggerChannelConditions)
(
  int16_t                       handle,
  PS3000A_TRIGGER_CONDITIONS *conditions,
  int16_t                       nConditions
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aSetTriggerChannelConditionsV2)
(
  int16_t                          handle,
  PS3000A_TRIGGER_CONDITIONS_V2 *conditions,
  int16_t                          nConditions
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aSetTriggerChannelDirections)
(
  int16_t                        handle,
  PS3000A_THRESHOLD_DIRECTION  channelA,
  PS3000A_THRESHOLD_DIRECTION  channelB,
  PS3000A_THRESHOLD_DIRECTION  channelC,
  PS3000A_THRESHOLD_DIRECTION  channelD,
  PS3000A_THRESHOLD_DIRECTION  ext,
  PS3000A_THRESHOLD_DIRECTION  aux
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aSetTriggerDelay)
(
  int16_t          handle,
  uint32_t  delay
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aSetPulseWidthQualifier)
(
  int16_t                        handle,
  PS3000A_PWQ_CONDITIONS      *conditions,
  int16_t                        nConditions,
  PS3000A_THRESHOLD_DIRECTION  direction,
  uint32_t                lower,
  uint32_t                upper,
  PS3000A_PULSE_WIDTH_TYPE     type
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aSetPulseWidthQualifierV2)
(
  int16_t                        handle,
  PS3000A_PWQ_CONDITIONS_V2   *conditions,
  int16_t                        nConditions,
  PS3000A_THRESHOLD_DIRECTION  direction,
  uint32_t                lower,
  uint32_t                upper,
  PS3000A_PULSE_WIDTH_TYPE     type
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aIsTriggerOrPulseWidthQualifierEnabled)
(
  int16_t  handle,
  int16_t *triggerEnabled,
  int16_t *pulseWidthQualifierEnabled
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aGetTriggerTimeOffset)
(
  int16_t               handle,
  uint32_t      *timeUpper,
  uint32_t      *timeLower,
  PS3000A_TIME_UNITS *timeUnits,
  uint32_t      segmentIndex
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aGetTriggerTimeOffset64)
(
  int16_t               handle,
  int64_t            *time,
  PS3000A_TIME_UNITS *timeUnits,
  uint32_t      segmentIndex
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aGetValuesTriggerTimeOffsetBulk)
(
  int16_t               handle,
  uint32_t      *timesUpper,
  uint32_t      *timesLower,
  PS3000A_TIME_UNITS *timeUnits,
  uint32_t      fromSegmentIndex,
  uint32_t      toSegmentIndex
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aGetValuesTriggerTimeOffsetBulk64)
(
  int16_t               handle,
  int64_t            *times,
  PS3000A_TIME_UNITS *timeUnits,
  uint32_t      fromSegmentIndex,
  uint32_t      toSegmentIndex
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aGetNoOfCaptures)
(
  int16_t          handle,
  uint32_t *nCaptures
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aGetNoOfProcessedCaptures)
(
  int16_t          handle,
  uint32_t *nProcessedCaptures
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aSetDataBuffer)
(
  int16_t               handle,
  PS3000A_CHANNEL     channelOrPort,
  int16_t              *buffer,
  int32_t                bufferLth,
  uint32_t      segmentIndex,
  PS3000A_RATIO_MODE  mode
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aSetDataBuffers)
(
  int16_t               handle,
  PS3000A_CHANNEL     channelOrPort,
  int16_t              *bufferMax,
  int16_t              *bufferMin,
  int32_t                bufferLth,
  uint32_t      segmentIndex,
  PS3000A_RATIO_MODE  mode
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps3000aSetUnscaledDataBuffers)
(
	int16_t               handle,
	PS3000A_CHANNEL     channelOrPort,
	int8_t              *bufferMax,
	int8_t              *bufferMin,
	int32_t                bufferLth,
	uint32_t      segmentIndex,
	PS3000A_RATIO_MODE  mode
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aSetEtsTimeBuffer)
(
  int16_t    handle,
  int64_t *buffer,
  int32_t     bufferLth
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aSetEtsTimeBuffers)
(
  int16_t          handle,
  uint32_t *timeUpper,
  uint32_t *timeLower,
  int32_t           bufferLth
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aIsReady)
(
  int16_t  handle,
  int16_t *ready
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aRunBlock)
(
  int16_t              handle,
  int32_t               noOfPreTriggerSamples,
  int32_t               noOfPostTriggerSamples,
  uint32_t      timebase,
  int16_t              oversample,
  int32_t              *timeIndisposedMs,
  uint32_t     segmentIndex,
  ps3000aBlockReady  lpReady,
  void              *pParameter
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aRunStreaming)
(
  int16_t               handle,
  uint32_t      *sampleInterval,
  PS3000A_TIME_UNITS  sampleIntervalTimeUnits,
  uint32_t       maxPreTriggerSamples,
  uint32_t       maxPostPreTriggerSamples,
  int16_t               autoStop,
  uint32_t       downSampleRatio,
  PS3000A_RATIO_MODE  downSampleRatioMode,
  uint32_t       overviewBufferSize
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aGetStreamingLatestValues)
(
int16_t                  handle,
ps3000aStreamingReady  lpPs3000aReady,
void                  *pParameter
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aNoOfStreamingValues)
(
  int16_t          handle,
  uint32_t *noOfValues
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aGetMaxDownSampleRatio)
(
  int16_t               handle,
  uint32_t       noOfUnaggreatedSamples,
  uint32_t      *maxDownSampleRatio,
  PS3000A_RATIO_MODE  downSampleRatioMode,
  uint32_t      segmentIndex
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aGetValues)
(
  int16_t               handle,
  uint32_t       startIndex,
  uint32_t      *noOfSamples,
  uint32_t       downSampleRatio,
  PS3000A_RATIO_MODE  downSampleRatioMode,
  uint32_t      segmentIndex,
  int16_t              *overflow
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aGetValuesBulk)
(
 int16_t                handle,
  uint32_t      *noOfSamples,
  uint32_t      fromSegmentIndex,
  uint32_t      toSegmentIndex,
  uint32_t       downSampleRatio,
  PS3000A_RATIO_MODE  downSampleRatioMode,
  int16_t              *overflow
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aGetValuesAsync)
(
  int16_t           handle,
  uint32_t   startIndex,
  uint32_t   noOfSamples,
  uint32_t   downSampleRatio,
  PS3000A_RATIO_MODE   downSampleRatioMode,
  uint32_t  segmentIndex,
  void           *lpDataReady,
  void           *pParameter
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aGetValuesOverlapped)
(
  int16_t               handle,
  uint32_t       startIndex,
  uint32_t      *noOfSamples,
  uint32_t       downSampleRatio,
  PS3000A_RATIO_MODE  downSampleRatioMode,
  uint32_t      segmentIndex,
  int16_t              *overflow
);


PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aGetValuesOverlappedBulk)
(
  int16_t               handle,
  uint32_t       startIndex,
  uint32_t      *noOfSamples,
  uint32_t       downSampleRatio,
  PS3000A_RATIO_MODE  downSampleRatioMode,
  uint32_t      fromSegmentIndex,
  uint32_t      toSegmentIndex,
  int16_t              *overflow
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aGetTriggerInfoBulk)
(
	int16_t									handle,
  PS3000A_TRIGGER_INFO	*	triggerInfo,
  uint32_t								fromSegmentIndex,
  uint32_t								toSegmentIndex
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aStop)
(
  int16_t  handle
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aHoldOff)
(
  int16_t                 handle,
  uint64_t             holdoff,
  PS3000A_HOLDOFF_TYPE  type
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aGetChannelInformation)
(
  int16_t                 handle,
  PS3000A_CHANNEL_INFO  info,
  int32_t                   probe,
  int32_t                  *ranges,
  int32_t                  *length,
  int32_t                   channels
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aEnumerateUnits)
(
  int16_t *count,
  int8_t  *serials,
  int16_t *serialLth
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aPingUnit)
(
  int16_t  handle
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aMaximumValue)
(
  int16_t  handle,
  int16_t *value
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aMinimumValue)
(
  int16_t  handle,
  int16_t *value
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aGetAnalogueOffset)
(
  int16_t             handle,
  PS3000A_RANGE     range,
  PS3000A_COUPLING  coupling,
  float            *maximumVoltage,
  float            *minimumVoltage
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aGetMaxSegments)
(
  int16_t           handle,
  uint32_t *maxSegments
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aChangePowerSource)
(
  int16_t        handle,
  PICO_STATUS  powerState
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps3000aCurrentPowerSource)
(
  int16_t  handle
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps3000aQueryOutputEdgeDetect)
(
	int16_t		handle,
	int16_t * state
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps3000aSetOutputEdgeDetect)
(
	int16_t	handle,
	int16_t state
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps3000aGetScalingValues)
(
	int16_t	handle,
	PS3000A_SCALING_FACTORS_VALUES *scalingValues,
	int16_t nChannels
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps3000aCheckForUpdate)(int16_t handle,
                                                           PICO_FIRMWARE_INFO* firmwareInfos,
                                                           int16_t* nFirmwareInfos,
                                                           uint16_t* updatesRequired);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps3000aStartFirmwareUpdate)(int16_t handle, PicoUpdateFirmwareProgress progress);

#endif
