/****************************************************************************
 *
 * Filename:    ps4000aApi.h
 * Author:      MAS
 * Description:
 *
 * This header defines the interface to driver routines for the
 *	PicoScope 4444 and 4824 PC Oscilloscopes.
 *
 * Copyright � 2013 - 2022 Pico Technology Ltd. All rights reserved.
 *
 ****************************************************************************/
#ifndef __PS4000AAPI_H__
#define __PS4000AAPI_H__

#include <stdint.h>

#include "PicoStatus.h"
#include "PicoCallback.h"
#include "PicoConnectProbes.h"
#include "PicoVersion.h"

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
/*	If you are dynamically linking ps4000a.dll into your project #define DYNLINK here
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

#define PS4000A_EXT_MAX_VALUE  32767
#define PS4000A_EXT_MIN_VALUE -32767

#define MAX_PULSE_WIDTH_QUALIFIER_COUNT 16777215L
#define MAX_DELAY_COUNT 8388607L

#define PS4000A_MAX_SIG_GEN_BUFFER_SIZE 16384

#define PS4000A_MIN_SIG_GEN_BUFFER_SIZE 10
#define PS4000A_MIN_DWELL_COUNT				10
#define PS4000A_MAX_SWEEPS_SHOTS				((1 << 30) - 1)
#define	PS4000A_AWG_DAC_FREQUENCY							80e6
#define	PS4000A_AWG_PHASE_ACCUMULATOR  4294967296.0

#define PS4000A_MAX_ANALOGUE_OFFSET_50MV_200MV	 0.250f
#define PS4000A_MIN_ANALOGUE_OFFSET_50MV_200MV	-0.250f
#define PS4000A_MAX_ANALOGUE_OFFSET_500MV_2V		 2.500f
#define PS4000A_MIN_ANALOGUE_OFFSET_500MV_2V		-2.500f
#define PS4000A_MAX_ANALOGUE_OFFSET_5V_20V			 20.f
#define PS4000A_MIN_ANALOGUE_OFFSET_5V_20V			-20.f
#define PS4000A_MAX_ANALOGUE_OFFSET_10V_50V      25.f
#define PS4000A_MIN_ANALOGUE_OFFSET_10V_50V     -25.f


typedef enum enPS4000ADeviceResolution
{
	PS4000A_DR_8BIT,
	PS4000A_DR_12BIT,
	PS4000A_DR_14BIT,
	PS4000A_DR_15BIT,
	PS4000A_DR_16BIT,
} PS4000A_DEVICE_RESOLUTION;

typedef enum enPS4000AExtraOperations
{
	PS4000A_ES_OFF,
	PS4000A_WHITENOISE,
	PS4000A_PRBS // Pseudo-Random Bit Stream
} PS4000A_EXTRA_OPERATIONS;

typedef enum	enPS4000ABandwidthLimiterFlags
{
	PS4000A_BW_FULL_FLAG = (1 << 0),
	PS4000A_BW_20KHZ_FLAG = (1 << 1),
	PS4000A_BW_100KHZ_FLAG = (1 << 2), //( default when current clamp detected: can be changed)
	PS4000A_BW_1MHZ_FLAG  = (1 << 3)  //( default for 14 bits: can be changed)
} PS4000A_BANDWIDTH_LIMITER_FLAGS;

typedef enum	enPS4000ABandwidthLimiter
{
	PS4000A_BW_FULL,
	PS4000A_BW_20KHZ,
	PS4000A_BW_100KHZ, //( default when current clamp detected: can be changed)
	PS4000A_BW_1MHZ
} PS4000A_BANDWIDTH_LIMITER;

typedef enum enPS4000ACoupling
{
	PS4000A_AC,
	PS4000A_DC
} PS4000A_COUPLING;

typedef enum enPS4000AChannel
{
	PS4000A_CHANNEL_A,
	PS4000A_CHANNEL_B,
	PS4000A_CHANNEL_C,
	PS4000A_CHANNEL_D,
	PS4000A_MAX_4_CHANNELS,
	PS4000A_CHANNEL_E = PS4000A_MAX_4_CHANNELS,
	PS4000A_CHANNEL_F,
	PS4000A_CHANNEL_G,
	PS4000A_CHANNEL_H,
	PS4000A_EXTERNAL,
	PS4000A_MAX_CHANNELS = PS4000A_EXTERNAL,
	PS4000A_TRIGGER_AUX,
	PS4000A_MAX_TRIGGER_SOURCES,
	PS4000A_PULSE_WIDTH_SOURCE = 0x10000000
}	PS4000A_CHANNEL;



typedef enum enPS4000AChannelBufferIndex
{
	PS4000A_CHANNEL_A_MAX,
	PS4000A_CHANNEL_A_MIN,
	PS4000A_CHANNEL_B_MAX,
	PS4000A_CHANNEL_B_MIN,
	PS4000A_CHANNEL_C_MAX,
	PS4000A_CHANNEL_C_MIN,
	PS4000A_CHANNEL_D_MAX,
	PS4000A_CHANNEL_D_MIN,
	PS4000A_CHANNEL_E_MAX,
	PS4000A_CHANNEL_E_MIN,
	PS4000A_CHANNEL_F_MAX,
	PS4000A_CHANNEL_F_MIN,
	PS4000A_CHANNEL_G_MAX,
	PS4000A_CHANNEL_G_MIN,
	PS4000A_CHANNEL_H_MAX,
	PS4000A_CHANNEL_H_MIN,
	PS4000A_MAX_CHANNEL_BUFFERS
} PS4000A_CHANNEL_BUFFER_INDEX;

typedef enum enPS4000ARange
{
	PS4000A_10MV,
	PS4000A_20MV,
	PS4000A_50MV,
	PS4000A_100MV,
	PS4000A_200MV,
	PS4000A_500MV,
	PS4000A_1V,
	PS4000A_2V,
	PS4000A_5V,
	PS4000A_10V,
	PS4000A_20V,
	PS4000A_50V,
	PS4000A_100V,
	PS4000A_200V,
	PS4000A_MAX_RANGES
}	PS4000A_RANGE;

typedef enum enPS4000AResistanceRange
{
	PS4000A_RESISTANCE_315K = 0x00000200,
	PS4000A_RESISTANCE_1100K,
	PS4000A_RESISTANCE_10M,
	PS4000A_MAX_RESISTANCE_RANGES = (PS4000A_RESISTANCE_10M + 1) - PS4000A_RESISTANCE_315K,
	PS4000A_RESISTANCE_ADCV = 0x10000000
}	PS4000A_RESISTANCE_RANGE;

typedef enum enPS4000AEtsMode
  {
  PS4000A_ETS_OFF,             // ETS disabled
  PS4000A_ETS_FAST,            // Return ready as soon as requested no of interleaves is available
  PS4000A_ETS_SLOW,            // Return ready every time a new set of no_of_cycles is collected
  PS4000A_ETS_MODES_MAX
  }	PS4000A_ETS_MODE;

typedef enum enPS4000ATimeUnits
  {
  PS4000A_FS,
  PS4000A_PS,
  PS4000A_NS,
  PS4000A_US,
  PS4000A_MS,
  PS4000A_S,
  PS4000A_MAX_TIME_UNITS,
  }	PS4000A_TIME_UNITS;

typedef enum enPS4000ASweepType
{
	PS4000A_UP,
	PS4000A_DOWN,
	PS4000A_UPDOWN,
	PS4000A_DOWNUP,
	PS4000A_MAX_SWEEP_TYPES
} PS4000A_SWEEP_TYPE;

typedef enum enPS4000AWaveType
{
	PS4000A_SINE,
	PS4000A_SQUARE,
	PS4000A_TRIANGLE,
	PS4000A_RAMP_UP,
	PS4000A_RAMP_DOWN,
	PS4000A_SINC,
	PS4000A_GAUSSIAN,
	PS4000A_HALF_SINE,
	PS4000A_DC_VOLTAGE,
	PS4000A_WHITE_NOISE,
	PS4000A_MAX_WAVE_TYPES
} PS4000A_WAVE_TYPE;

typedef enum enPS4000APinStates
{
	PS4000A_CAL_PINS_OFF,
	PS4000A_GND_SIGNAL,
	PS4000A_SIGNAL_SIGNAL
} PS4000A_PIN_STATES;

#define PS4000A_SINE_MAX_FREQUENCY				1000000.f
#define PS4000A_SQUARE_MAX_FREQUENCY			1000000.f
#define PS4000A_TRIANGLE_MAX_FREQUENCY		1000000.f
#define PS4000A_SINC_MAX_FREQUENCY				1000000.f
#define PS4000A_RAMP_MAX_FREQUENCY				1000000.f
#define PS4000A_HALF_SINE_MAX_FREQUENCY	1000000.f
#define PS4000A_GAUSSIAN_MAX_FREQUENCY		1000000.f
#define PS4000A_MIN_FREQUENCY									 0.03f

typedef enum enPS4000AChannelLed
{
	PS4000A_CHANNEL_LED_OFF,
	PS4000A_CHANNEL_LED_RED,
	PS4000A_CHANNEL_LED_GREEN
} PS4000A_CHANNEL_LED;

typedef enum enPS4000AProbeLedPosition
{
	PS4000A_UPPER_LEFT_LED = 1,
	PS4000A_LOWER_LEFT_LED = 2,
	PS4000A_UPPER_RIGHT_LED = 4,
	PS4000A_LOWER_RIGHT_LED = 8,

	PS4000A_RIGHT_LEDS = PS4000A_UPPER_RIGHT_LED | PS4000A_LOWER_RIGHT_LED,
	PS4000A_LEFT_LEDS = PS4000A_UPPER_LEFT_LED | PS4000A_LOWER_LEFT_LED,

	PS4000A_UPPER_LEDS = PS4000A_UPPER_RIGHT_LED | PS4000A_UPPER_LEFT_LED,
	PS4000A_LOWER_LEDS = PS4000A_LOWER_RIGHT_LED | PS4000A_LOWER_LEFT_LED,

	PS4000A_ALL_LEDS = PS4000A_UPPER_LEFT_LED | PS4000A_LOWER_LEFT_LED | PS4000A_UPPER_RIGHT_LED | PS4000A_LOWER_RIGHT_LED
} PS4000A_PROBE_LED_POSITION;

typedef enum enPS4000AMetaType
{
	PS4000A_MT_UNIT_INFO,
	PS4000A_MT_DEVICE_CAPABILITY,
	PS4000A_MT_DEVICE_SETTINGS,
	PS4000A_MT_SIGNAL_GENERATOR_SETTINGS
} PS4000A_META_TYPE;

typedef enum enPS4000AMetaOperation
{
	PS4000A_MO_READ,
	PS4000A_MO_WRITE
} PS4000A_META_OPERATION;

typedef enum enPS4000AMetaFormat
{
	PS4000A_MF_COMMA_SEPARATED,
	PS4000A_MF_XML
} PS4000A_META_FORMAT;

typedef enum enPS4000ASigGenTrigType
{
	PS4000A_SIGGEN_RISING,
	PS4000A_SIGGEN_FALLING,
	PS4000A_SIGGEN_GATE_HIGH,
	PS4000A_SIGGEN_GATE_LOW
} PS4000A_SIGGEN_TRIG_TYPE;

typedef enum enPS4000ASigGenTrigSource
{
	PS4000A_SIGGEN_NONE,
	PS4000A_SIGGEN_SCOPE_TRIG,
	PS4000A_SIGGEN_AUX_IN,
	PS4000A_SIGGEN_EXT_IN,
	PS4000A_SIGGEN_SOFT_TRIG
} PS4000A_SIGGEN_TRIG_SOURCE;

typedef enum enPS4000AIndexMode
{
	PS4000A_SINGLE,
	PS4000A_DUAL,
	PS4000A_QUAD,
	PS4000A_MAX_INDEX_MODES
} PS4000A_INDEX_MODE;

typedef enum enPS4000AThresholdMode
{
	PS4000A_LEVEL,
	PS4000A_WINDOW
} PS4000A_THRESHOLD_MODE;

typedef enum enPS4000AThresholdDirection
{
	PS4000A_ABOVE, //using upper threshold
	PS4000A_BELOW, //using upper threshold
	PS4000A_RISING, // using upper threshold
	PS4000A_FALLING, // using upper threshold
	PS4000A_RISING_OR_FALLING, // using both threshold
	PS4000A_ABOVE_LOWER, // using lower threshold
	PS4000A_BELOW_LOWER, // using lower threshold
	PS4000A_RISING_LOWER,			 // using lower threshold
	PS4000A_FALLING_LOWER,		 // using lower threshold

	// Windowing using both thresholds
	PS4000A_INSIDE = PS4000A_ABOVE,
	PS4000A_OUTSIDE = PS4000A_BELOW,
	PS4000A_ENTER = PS4000A_RISING,
	PS4000A_EXIT = PS4000A_FALLING,
	PS4000A_ENTER_OR_EXIT = PS4000A_RISING_OR_FALLING,
	PS4000A_POSITIVE_RUNT = 9,
  PS4000A_NEGATIVE_RUNT,

	// no trigger set
  PS4000A_NONE = PS4000A_RISING
} PS4000A_THRESHOLD_DIRECTION;


typedef enum enPS4000ATriggerState
{
  PS4000A_CONDITION_DONT_CARE,
  PS4000A_CONDITION_TRUE,
  PS4000A_CONDITION_FALSE,
	PS4000A_CONDITION_MAX
} PS4000A_TRIGGER_STATE;

typedef enum enPS4000ASensorState
{
	PS4000A_CONNECT_STATE_FLOATING,
	PS4000A_SENSOR_STATE_CONNECTED
} PS4000A_SENSOR_STATE;

typedef enum enPS4000AFrequencyCounterRange
{
  PS4000A_FC_2K,
  PS4000A_FC_20K,
  PS4000A_FC_20,
  PS4000A_FC_200,
  PS4000A_FC_MAX
}PS4000A_FREQUENCY_COUNTER_RANGE;

typedef enum enPS4000AChannelFlags
{
	PS4000A_CHANNEL_A_FLAGS = 1,
	PS4000A_CHANNEL_B_FLAGS = 2,
	PS4000A_CHANNEL_C_FLAGS = 4,
	PS4000A_CHANNEL_D_FLAGS = 8,
	PS4000A_CHANNEL_E_FLAGS = 16,
	PS4000A_CHANNEL_F_FLAGS = 32,
	PS4000A_CHANNEL_G_FLAGS = 64,
	PS4000A_CHANNEL_H_FLAGS = 128,
}	PS4000A_CHANNEL_FLAGS;

#pragma pack(push,1)
typedef struct tPS4000AChannelLedSetting
{
	PS4000A_CHANNEL channel;
	PS4000A_CHANNEL_LED state;
} PS4000A_CHANNEL_LED_SETTING;

typedef struct ps4000aProbeLedColour
{
	uint8_t red;
	uint8_t green;
	uint8_t blue;
} PS4000A_PROBE_LED_COLOUR;

typedef struct tPS4000AProbeChannelLedSetting
{
	PS4000A_CHANNEL channel;
	PS4000A_PROBE_LED_POSITION position;
	PS4000A_PROBE_LED_COLOUR rgb;
} PS4000A_PROBE_CHANNEL_LED_SETTING;

typedef struct tPS4000ADirection
{
	PS4000A_CHANNEL							channel;
	PS4000A_THRESHOLD_DIRECTION direction;
} PS4000A_DIRECTION;


typedef struct tPS4000ACondition
{
	PS4000A_CHANNEL   		source;
  PS4000A_TRIGGER_STATE condition;
} PS4000A_CONDITION;

typedef enum enPS4000AConditionsInfo
{
	PS4000A_CLEAR = 0x00000001,
  PS4000A_ADD = 0x00000002
} PS4000A_CONDITIONS_INFO;

typedef struct tPS4000ATriggerChannelProperties
{
  int16_t										thresholdUpper;
	uint16_t					thresholdUpperHysteresis;
  int16_t										thresholdLower;
	uint16_t					thresholdLowerHysteresis;
	PS4000A_CHANNEL					channel;
  PS4000A_THRESHOLD_MODE	thresholdMode;
} PS4000A_TRIGGER_CHANNEL_PROPERTIES;

typedef struct tPS4000AConnectDetect
{
	PS4000A_CHANNEL channel;
	PS4000A_SENSOR_STATE state;
} PS4000A_CONNECT_DETECT;

typedef struct tPS4000AUserProbeInteractions
{
	uint16_t connected;

	PS4000A_CHANNEL channel;
	uint16_t enabled;

	PicoConnectProbe probeName;

	uint8_t requiresPower_;
	uint8_t isPowered_;

	PICO_STATUS status_;

	PICO_CONNECT_PROBE_RANGE probeOff;

	PICO_CONNECT_PROBE_RANGE rangeFirst_;
	PICO_CONNECT_PROBE_RANGE rangeLast_;
	PICO_CONNECT_PROBE_RANGE rangeCurrent_;

	PS4000A_COUPLING couplingFirst_;
	PS4000A_COUPLING couplingLast_;
	PS4000A_COUPLING couplingCurrent_;

	PS4000A_BANDWIDTH_LIMITER_FLAGS filterFlags_;
	PS4000A_BANDWIDTH_LIMITER_FLAGS filterCurrent_;

	PS4000A_BANDWIDTH_LIMITER defaultFilter_;
} PS4000A_USER_PROBE_INTERACTIONS;
#pragma pack(pop)


typedef enum enPS4000ARatioMode
{
	PS4000A_RATIO_MODE_NONE = 0,
	PS4000A_RATIO_MODE_AGGREGATE = 1,
	PS4000A_RATIO_MODE_DECIMATE = 2,
	PS4000A_RATIO_MODE_AVERAGE = 4,
	PS4000A_RATIO_MODE_DISTRIBUTION = 8
} PS4000A_RATIO_MODE;

typedef enum enPS4000APulseWidthType
{
	PS4000A_PW_TYPE_NONE,
  PS4000A_PW_TYPE_LESS_THAN,
	PS4000A_PW_TYPE_GREATER_THAN,
	PS4000A_PW_TYPE_IN_RANGE,
	PS4000A_PW_TYPE_OUT_OF_RANGE
} PS4000A_PULSE_WIDTH_TYPE;

typedef enum enPS4000AChannelInfo
{
	PS4000A_CI_RANGES,
	PS4000A_CI_RESISTANCES,
} PS4000A_CHANNEL_INFO;

typedef void (PREF4 *ps4000aBlockReady)
	(
		int16_t											handle,
		PICO_STATUS								status,
		void										*	pParameter
	);

typedef void (PREF4 *ps4000aStreamingReady)
	(
		int16_t    									handle,
		int32_t     									noOfSamples,
		uint32_t							startIndex,
		int16_t    									overflow,
		uint32_t							triggerAt,
		int16_t    									triggered,
		int16_t    									autoStop,
		void										*	pParameter
	);


typedef void (PREF4 *ps4000aDataReady)
	(
		int16_t    									handle,
		PICO_STATUS								status,
		uint32_t     				noOfSamples,
		int16_t    									overflow,
		void										*	pParameter
	);


typedef void (PREF4 *ps4000aProbeInteractions)
	(
		int16_t    												handle,
		PICO_STATUS												status,
		PS4000A_USER_PROBE_INTERACTIONS * probes,
		uint32_t													nProbes
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps4000aOpenUnitWithResolution)
(
	int16_t											* handle,
	int8_t											* serial,
	PS4000A_DEVICE_RESOLUTION			resolution
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aOpenUnit)
  (
	  int16_t											* handle,
		int8_t											* serial
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps4000aOpenUnitAsyncWithResolution)
(
	int16_t											* status,
	int8_t											* serial,
	PS4000A_DEVICE_RESOLUTION			resolution
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aOpenUnitAsync)
  (
	  int16_t											* status,
		int8_t											* serial
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aOpenUnitProgress)
	(
	  int16_t 										* handle,
	  int16_t 										* progressPercent,
	  int16_t 										* complete
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aGetUnitInfo)
 	(
	  int16_t     								  handle,
	  int8_t      								* string,
	  int16_t     								  stringLength,
	  int16_t     								* requiredSize,
	  PICO_INFO 								  info
	);

// This function retrieves information about the accessory (e.g. probe) attached to the specified channel.
// Note: you must set a probe interaction callback to be able to retrieve probe information.
//
// parameters:
// handle: identifies the device to which the accessory is attached.
// channel: identifies the channel to which the accessory is attached. If no accessory is connected to this channel, an error will result.
// string: on exit, the accessory information string selected specified by the info argument. If string is NULL, only requiredSize is returned.
// stringLength: the maximum number of 8-bit integers (int8_t) that may be written to string.
// requiredSize: on exit, the required length of the string array.
// info: a number specifying what information is required. Note that unlike ps6000aGetUnitInfo, only PICO_BATCH_AND_SERIAL and PICO_CAL_DATE are valid for accessories.
//
// return:
// PICO_OK
// PICO_INVALID_HANDLE (handle isn't that of an open PicoScope device.)
// PICO_PROBE_COLLECTION_NOT_STARTED (handle hasn't got a probe interaction callback set).
// PICO_INVALID_CHANNEL (channel doesn't map to a channel on the device with handle.)
// PICO_NULL_PARAMETER (requiredSize is NULL.)
// PICO_INVALID_INFO (info is an invalid value for the attached accessory.)
// PICO_INFO_UNAVAILABLE (no accessory is connected, or the connected accessory does not support any info.)
// PICO_DRIVER_FUNCTION (another thread is already calling a driver function.)
PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps4000aGetAccessoryInfo)
  (
	  int16_t     								  handle,
	  PS4000A_CHANNEL							  channel,
	  int8_t											* string,
	  int16_t     								  stringLength,
	  int16_t											* requiredSize,
	  PICO_INFO 								  info
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aFlashLed)
	(
	  int16_t 											handle,
		int16_t 											start
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aSetChannelLed)
	(
	int16_t 												handle,
	PS4000A_CHANNEL_LED_SETTING		*	ledStates,
	uint16_t												nLedStates
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aIsLedFlashing)
	(
	  int16_t 										  handle,
		int16_t 										* status
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aCloseUnit)
	(
	  int16_t												handle
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aMemorySegments)
	(
	  int16_t												handle,
		uint32_t								nSegments,
		int32_t											* nMaxSamples
	);


PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aSetChannel)
 	(
	  int16_t											handle,
		PS4000A_CHANNEL						channel,
	  int16_t											enabled,
	  PS4000A_COUPLING					type,
		PICO_CONNECT_PROBE_RANGE				range,
		float											analogOffset
	);


PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aSetBandwidthFilter)
 	(
	  int16_t												handle,
	  PS4000A_CHANNEL							channel,
	  PS4000A_BANDWIDTH_LIMITER		bandwidth
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aApplyResistanceScaling)
	(
	int16_t											handle,
	PS4000A_CHANNEL							channel,
	PICO_CONNECT_PROBE_RANGE					range,
	int16_t										* bufferMax,
	int16_t										* bufferMin,
	uint32_t										buffertLth,
	int16_t										* overflow
	);



PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aGetTimebase)
	(
	   int16_t											handle,
	   uint32_t							timebase,
	   int32_t												noSamples,
	   int32_t											* timeIntervalNanoseconds,
		 int32_t											* maxSamples,
		 uint32_t							segmentIndex
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aGetTimebase2)
	(
	   int16_t											handle,
	   uint32_t							timebase,
	   int32_t												noSamples,
	   float										* timeIntervalNanoseconds,
		 int32_t											* maxSamples,
		 uint32_t							segmentIndex
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aSetSigGenArbitrary)
	(
	 	int16_t												handle,
	 	int32_t												offsetVoltage,
	 	uint32_t								pkToPk,
	 	uint32_t								startDeltaPhase,
	 	uint32_t								stopDeltaPhase,
	 	uint32_t								deltaPhaseIncrement,
	 	uint32_t								dwellCount,
	 	int16_t											*	arbitraryWaveform,
	 	int32_t												arbitraryWaveformSize,
		PS4000A_SWEEP_TYPE					sweepType,
		PS4000A_EXTRA_OPERATIONS		operation,
		PS4000A_INDEX_MODE					indexMode,
		uint32_t								shots,
		uint32_t								sweeps,
		PS4000A_SIGGEN_TRIG_TYPE		triggerType,
		PS4000A_SIGGEN_TRIG_SOURCE	triggerSource,
		int16_t												extInThreshold
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps4000aSetSigGenBuiltIn)
	(
		int16_t												handle,
		int32_t												offsetVoltage,
		uint32_t								pkToPk,
		PS4000A_WAVE_TYPE						waveType,
		double											startFrequency,
		double											stopFrequency,
		double											increment,
		double											dwellTime,
		PS4000A_SWEEP_TYPE					sweepType,
		PS4000A_EXTRA_OPERATIONS		operation,
		uint32_t								shots,
		uint32_t								sweeps,
		PS4000A_SIGGEN_TRIG_TYPE		triggerType,
		PS4000A_SIGGEN_TRIG_SOURCE	triggerSource,
		int16_t												extInThreshold
		);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aSetSigGenPropertiesArbitrary)
	(
	 	int16_t												handle,
	 	uint32_t								startDeltaPhase,
	 	uint32_t								stopDeltaPhase,
	 	uint32_t								deltaPhaseIncrement,
	 	uint32_t								dwellCount,
		PS4000A_SWEEP_TYPE					sweepType,
		uint32_t								shots,
		uint32_t								sweeps,
		PS4000A_SIGGEN_TRIG_TYPE		triggerType,
		PS4000A_SIGGEN_TRIG_SOURCE	triggerSource,
		int16_t												extInThreshold
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps4000aSetSigGenPropertiesBuiltIn)
	(
		int16_t												handle,
		double											startFrequency,
		double											stopFrequency,
		double											increment,
		double											dwellTime,
		PS4000A_SWEEP_TYPE					sweepType,
		uint32_t								shots,
		uint32_t								sweeps,
		PS4000A_SIGGEN_TRIG_TYPE		triggerType,
		PS4000A_SIGGEN_TRIG_SOURCE	triggerSource,
		int16_t												extInThreshold
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps4000aSigGenFrequencyToPhase)
	(
		int16_t												handle,
		double												frequency,
		PS4000A_INDEX_MODE						indexMode,
		uint32_t											bufferLength,
		uint32_t										* phase
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps4000aSigGenArbitraryMinMaxValues)
	(
	int16_t			handle,
	int16_t		*	minArbitraryWaveformValue,
	int16_t		*	maxArbitraryWaveformValue,
	uint32_t	* minArbitraryWaveformSize,
	uint32_t	*	maxArbitraryWaveformSize
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aSigGenSoftwareControl)
	(
		int16_t												handle,
		int16_t												state
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aSetEts)
  (
		int16_t												handle,
		PS4000A_ETS_MODE						mode,
		int16_t												etsCycles,
		int16_t												etsInterleave,
		int32_t											* sampleTimePicoseconds
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aSetTriggerChannelProperties)
	(
		int16_t																				handle,
		PS4000A_TRIGGER_CHANNEL_PROPERTIES			 *	channelProperties,
		int16_t																				nChannelProperties,
		int16_t																				auxOutputEnable,
		int32_t																				autoTriggerMilliseconds
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aSetTriggerChannelConditions)
	(
		int16_t													handle,
		PS4000A_CONDITION					*		conditions,
		int16_t													nConditions,
		PS4000A_CONDITIONS_INFO				info
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aSetTriggerChannelDirections)
	(
		int16_t													handle,
		PS4000A_DIRECTION					*		directions,
		int16_t													nDirections
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aSetSimpleTrigger)
	(
		int16_t												handle,
		int16_t												enable,
		PS4000A_CHANNEL							source,
		int16_t												threshold,
		PS4000A_THRESHOLD_DIRECTION direction,
		uint32_t								delay,
		int16_t												autoTrigger_ms
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aSetTriggerDelay)
	(
		int16_t									handle,
		uint32_t					delay
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aSetPulseWidthQualifierProperties)
	(
		int16_t														handle,
		PS4000A_THRESHOLD_DIRECTION			direction,
		uint32_t										lower,
		uint32_t										upper,
		PS4000A_PULSE_WIDTH_TYPE				type
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aSetPulseWidthQualifierConditions)
	(
		int16_t												handle,
		PS4000A_CONDITION					*	conditions,
		int16_t												nConditions,
		PS4000A_CONDITIONS_INFO			info
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aIsTriggerOrPulseWidthQualifierEnabled)
	(
		int16_t 								handle,
		int16_t 							* triggerEnabled,
		int16_t 							* pulseWidthQualifierEnabled
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aGetTriggerTimeOffset)
	(
		int16_t									handle,
		uint32_t 			* timeUpper,
		uint32_t 			* timeLower,
		PS4000A_TIME_UNITS	*	timeUnits,
		uint32_t					segmentIndex
	);


PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aGetTriggerTimeOffset64)
	(
		int16_t									handle,
		int64_t							* time,
		PS4000A_TIME_UNITS	*	timeUnits,
		uint32_t				segmentIndex
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aGetValuesTriggerTimeOffsetBulk)
	(
	  int16_t									handle,
		uint32_t				*	timesUpper,
		uint32_t				* timesLower,
		PS4000A_TIME_UNITS	*	timeUnits,
		uint32_t					fromSegmentIndex,
		uint32_t					toSegmentIndex
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aGetValuesTriggerTimeOffsetBulk64)
	(
	  int16_t									handle,
		int64_t							*	times,
		PS4000A_TIME_UNITS	*	timeUnits,
		uint32_t					fromSegmentIndex,
		uint32_t					toSegmentIndex
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aSetDataBuffers)
(
   int16_t									handle,
	 PS4000A_CHANNEL 				channel,
	 int16_t								*	bufferMax,
	 int16_t								*	bufferMin,
   int32_t										bufferLth,
	 uint32_t					segmentIndex,
	 PS4000A_RATIO_MODE			mode
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aSetDataBuffer)
(
   int16_t								 handle,
	 PS4000A_CHANNEL 			 channel,
	 int16_t							*  buffer,
   int32_t									 bufferLth,
	 uint32_t				 segmentIndex,
	 PS4000A_RATIO_MODE		 mode
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aSetEtsTimeBuffer)
(
   int16_t									handle,
	 int64_t *							buffer,
	 int32_t										bufferLth
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aSetEtsTimeBuffers)
(
   int16_t									handle,
	 uint32_t				* timeUpper,
	 uint32_t				* timeLower,
	 int32_t										bufferLth
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aIsReady)
	(
		int16_t handle,
		int16_t * ready
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aRunBlock)
	(
		int16_t									handle,
		int32_t									noOfPreTriggerSamples,
		int32_t									noOfPostTriggerSamples,
		uint32_t					timebase,
		int32_t								* timeIndisposedMs,
		uint32_t					segmentIndex,
		ps4000aBlockReady			lpReady,
		void								* pParameter
	);


PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aRunStreaming)
  (
	  int16_t									handle,
		uint32_t				* sampleInterval,
		PS4000A_TIME_UNITS		sampleIntervalTimeUnits,
	  uint32_t					maxPreTriggerSamples,
	  uint32_t					maxPostTriggerSamples,
		int16_t									autoStop,
		uint32_t					downSampleRatio,
		PS4000A_RATIO_MODE		downSampleRatioMode,
    uint32_t					overviewBufferSize
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aGetStreamingLatestValues)
  (
    int16_t									handle,
    ps4000aStreamingReady	lpPs4000aReady,
		void								* pParameter
  );

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aNoOfStreamingValues)
	(
	  int16_t								handle,
		uint32_t			*	noOfValues
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aGetMaxDownSampleRatio)
	(
	  int16_t								handle,
		uint32_t 			noOfUnaggregatedSamples,
		uint32_t 		* maxDownSampleRatio,
		PS4000A_RATIO_MODE	downSampleRatioMode,
		uint32_t				segmentIndex
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aGetValues)
	(
	  int16_t								handle,
		uint32_t 			startIndex,
	  uint32_t			*	noOfSamples,
	  uint32_t				downSampleRatio,
		PS4000A_RATIO_MODE	downSampleRatioMode,
		uint32_t				segmentIndex,
		int16_t							* overflow
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aGetValuesAsync)
	(
	  int16_t								handle,
		uint32_t				startIndex,
	  uint32_t				noOfSamples,
	  uint32_t				downSampleRatio,
		PS4000A_RATIO_MODE	downSampleRatioMode,
		uint32_t				segmentIndex,
	  void							*	lpDataReady,
		void							*	pParameter
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aGetValuesBulk)
	(
	  int16_t								handle,
		uint32_t			*	noOfSamples,
		uint32_t				fromSegmentIndex,
		uint32_t				toSegmentIndex,
	  uint32_t				downSampleRatio,
		PS4000A_RATIO_MODE 	downSampleRatioMode,
		int16_t							* overflow
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aGetValuesOverlapped)
	(
	  int16_t										handle,
	  uint32_t			 			startIndex,
	  uint32_t					*	noOfSamples,
	  uint32_t						downSampleRatio,
	  PS4000A_RATIO_MODE			downSampleRatioMode,
		uint32_t						segmentIndex,
	  int16_t									* overflow
	);


PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aGetValuesOverlappedBulk)
	(
	  int16_t									handle,
		uint32_t					startIndex,
  	uint32_t 	 		*	noOfSamples,
	  uint32_t					downSampleRatio,
	  PS4000A_RATIO_MODE		downSampleRatioMode,
	  uint32_t					fromSegmentIndex,
	  uint32_t					toSegmentIndex,
	  int16_t								*	overflow
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aEnumerateUnits)
	(
	int16_t * count,
	int8_t * serials,
	int16_t * serialLth
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aGetChannelInformation)
	(
	int16_t										handle,
	PS4000A_CHANNEL_INFO		info,
	int32_t											probe,
	int32_t										* ranges,
	int32_t										* length,
	int32_t											channels);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aConnectDetect)
	(
	int16_t		handle,
	PS4000A_CONNECT_DETECT * sensor,
	int16_t  nSensors
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps4000aSetProbeInteractionCallback)
 (
	int16_t		handle,
	ps4000aProbeInteractions callback
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps4000aCalibrateProbe)
(
	int16_t	handle,
	PS4000A_CHANNEL channel,
	int16_t * checkCalibrationRequired
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps4000aSetProbeLedColour)
(
	int16_t		handle,
	PS4000A_PROBE_CHANNEL_LED_SETTING * settings,
	uint16_t nSettings
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps4000aRegisterProbeLedColour)
(
	int16_t		handle,
	PICO_CONNECT_PROBE probe,
	PS4000A_PROBE_CHANNEL_LED_SETTING * settings,
	uint16_t nSettings
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps4000aSetProbeLedDefaults)
  (
    int16_t handle,
    int16_t enabled
  );

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aMaximumValue)
	(
	int16_t		handle,
	int16_t * value
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aMinimumValue)
	(
	int16_t		handle,
	int16_t * value
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aGetAnalogueOffset)
	(
	int16_t							handle,
	PICO_CONNECT_PROBE_RANGE	range,
	PS4000A_COUPLING		coupling,
	float							* maximumOffset,
	float							* minimumOffset
	);


PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aGetMaxSegments)
	(
	int16_t						handle,
	uint32_t * maxSegments
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aChangePowerSource)
	(
	int16_t				handle,
  PICO_STATUS powerState
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aCurrentPowerSource)
	(
	int16_t		handle
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aStop)
	(
	  int16_t handle
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aPingUnit)
	(
	  int16_t handle
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aSetNoOfCaptures)
	(
	int16_t					handle,
	uint32_t nCaptures
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aGetNoOfCaptures)
  (
    int16_t                handle,
    uint32_t               * nCaptures
  );

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aGetNoOfProcessedCaptures)
  (
    int16_t                handle,
    uint32_t               * nProcessedCaptures
  );

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aDeviceMetaData)
	(
	int16_t										handle,
	int8_t									*	settings,
	int32_t									*	nSettingsLength,
	PS4000A_META_TYPE					type,
	PS4000A_META_OPERATION		operation,
	PS4000A_META_FORMAT				format
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aGetString)
	(
	int16_t										handle,
	PICO_STRING_VALUE					stringValue,
	int8_t									*	string,
	int32_t									*	stringLength
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aGetCommonModeOverflow)
	(
	int16_t			handle,
	uint16_t	*	overflow
	);
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps4000aSetFrequencyCounter)
(
    int16_t                                handle,
    PS4000A_CHANNEL                        channel,
    int16_t                                enabled,
    PS4000A_FREQUENCY_COUNTER_RANGE        range,
    int16_t                                thresholdMajor,
    int16_t                                thresholdMinor
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps4000aQueryOutputEdgeDetect)
(
	int16_t		handle,
	int16_t * state
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps4000aSetOutputEdgeDetect)
(
	int16_t	handle,
	int16_t state
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps4000aSetDeviceResolution)
(
  int16_t                          handle,
  PS4000A_DEVICE_RESOLUTION        resolution
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps4000aGetDeviceResolution)
(
	int16_t                      handle,
	PS4000A_DEVICE_RESOLUTION    * resolution
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps4000aSetCalibrationPins)
(
	int16_t               handle,
	PS4000A_PIN_STATES		pinStates,
	PS4000A_WAVE_TYPE			waveType,
	double								frequency,
	uint32_t							amplitude,
	uint32_t							offset
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps4000aNearestSampleIntervalStateless)
(
	int16_t                        handle,
	PS4000A_CHANNEL_FLAGS          enabledChannelOrPortFlags,
	double                         timeIntervalRequested,
	PS4000A_DEVICE_RESOLUTION      resolution,
	uint16_t                       useEts,
	uint32_t                       * timebase,
	double                         * timeIntervalAvailable
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps4000aGetMinimumTimebaseStateless)
(
	int16_t                        handle,
	PS4000A_CHANNEL_FLAGS          enabledChannelOrPortFlags,
	uint32_t                       * timebase,
	double                         * timeInterval,
	PS4000A_DEVICE_RESOLUTION      resolution
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps4000aCheckForUpdate)
(
	int16_t handle,
	PICO_FIRMWARE_INFO* firmwareInfos,
    int16_t* nFirmwareInfos,
    uint16_t* updatesRequired
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps4000aStartFirmwareUpdate)
(
	int16_t handle,
	PicoUpdateFirmwareProgress progress
	);

#endif
