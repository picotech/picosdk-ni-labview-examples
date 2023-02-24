/****************************************************************************
 *
 * Filename:    ps2000aApi.h
 * Author:      MAS
 * Description:
 *
 * This header defines the interface to driver routines for the
 *	PicoScope 2000A and 2000B Series, and 2205 MSO PC Oscilloscopes.
 *
 * Copyright � 2010 - 2022 Pico Technology Ltd. All rights reserved.
 *
 ****************************************************************************/
#ifndef __PS2000AAPI_H__
#define __PS2000AAPI_H__

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
	#ifdef PREF1
	  #undef PREF1
	#endif
	#ifdef PREF2
	  #undef PREF2
	#endif
	#ifdef PREF3
	  #undef PREF3
	#endif
	/*	If you are dynamically linking ps2000a.dll into your project #define DYNLINK here
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
	#define __stdcall
#endif

/* Depending on the adc; oversample (collect multiple readings at each time) by up to 256.
 * the results are therefore ALWAYS scaled up to 16-bits, even if
 * oversampling is not used.
 *
 * The maximum and minimum values returned are therefore as follows:
 */

// covers the PS2208 and PS2208A
#define PS2208_MAX_ETS_CYCLES	500
#define PS2208_MAX_INTERLEAVE	 20

// covers the PS2207 and PS2207A
#define PS2207_MAX_ETS_CYCLES	500
#define PS2207_MAX_INTERLEAVE	 20

// covers the PS2206 and PS2206A
#define PS2206_MAX_ETS_CYCLES	250
#define PS2206_MAX_INTERLEAVE	 10

#define PS2000A_EXT_MAX_VALUE  32767
#define PS2000A_EXT_MIN_VALUE -32767

#define PS2000A_MAX_LOGIC_LEVEL	 32767
#define PS2000A_MIN_LOGIC_LEVEL -32767

#define MIN_SIG_GEN_FREQ 0.0f
#define MAX_SIG_GEN_FREQ 20000000.0f

#define PS2000A_MAX_SIG_GEN_BUFFER_SIZE 8192
#define PS2000A_MIN_SIG_GEN_BUFFER_SIZE 1
#define PS2000A_MIN_DWELL_COUNT				3
#define PS2000A_MAX_SWEEPS_SHOTS				((1 << 30) - 1)

#define PS2000A_MAX_ANALOGUE_OFFSET_50MV_200MV	 0.250f
#define PS2000A_MIN_ANALOGUE_OFFSET_50MV_200MV	-0.250f
#define PS2000A_MAX_ANALOGUE_OFFSET_500MV_2V		 2.500f
#define PS2000A_MIN_ANALOGUE_OFFSET_500MV_2V		-2.500f
#define PS2000A_MAX_ANALOGUE_OFFSET_5V_20V			 20.f
#define PS2000A_MIN_ANALOGUE_OFFSET_5V_20V			-20.f

// supported by the PS2206/PS2206A, PS2207/PS2207A, PS2208/PS2208A only
#define PS2000A_SHOT_SWEEP_TRIGGER_CONTINUOUS_RUN 0xFFFFFFFF

/// <summary>
/// The analogue channels index
/// </summary>
typedef enum enPS2000AChannelBufferIndex
{
	PS2000A_CHANNEL_A_MAX,
	PS2000A_CHANNEL_A_MIN,
	PS2000A_CHANNEL_B_MAX,
	PS2000A_CHANNEL_B_MIN,
	PS2000A_CHANNEL_C_MAX,
	PS2000A_CHANNEL_C_MIN,
	PS2000A_CHANNEL_D_MAX,
	PS2000A_CHANNEL_D_MIN,
	PS2000A_MAX_CHANNEL_BUFFERS
} PS2000A_CHANNEL_BUFFER_INDEX;

/// <summary>
/// The analogue channels and trigger channels supported by the devices
/// </summary>
typedef enum enPS2000AChannel
{
	PS2000A_CHANNEL_A,
	PS2000A_CHANNEL_B,
	PS2000A_CHANNEL_C,
	PS2000A_CHANNEL_D,
	PS2000A_EXTERNAL,
	PS2000A_MAX_CHANNELS = PS2000A_EXTERNAL,
	PS2000A_TRIGGER_AUX,
	PS2000A_MAX_TRIGGER_SOURCES

}	PS2000A_CHANNEL;

/// <summary>
/// MSO models only.
/// Defines how the analgoue and digital triggers are combined.
/// </summary>

typedef enum enPS2000ATriggerOperand
{
	/// <summary>
	/// Ignore the trigger settings
	/// </summary>
	PS2000A_OPERAND_NONE,
	/// <summary>
	/// Fire when either trigger is activated.
	/// </summary>
	PS2000A_OPERAND_OR,
	/// <summary>
	/// Fire when both triggers are activated
	/// </summary>
	PS2000A_OPERAND_AND,
	/// <summary>
	/// Fire when one trigger is activated.
	/// </summary>
	PS2000A_OPERAND_THEN
} PS2000A_TRIGGER_OPERAND;

/// <summary>
/// MSO ports
/// </summary>
typedef enum enPS2000DigitalPort
{
	PS2000A_DIGITAL_PORT0 = 0x80, // digital channel 0 - 7
	PS2000A_DIGITAL_PORT1,			 // digital channel 8 - 15
	PS2000A_DIGITAL_PORT2,			 // digital channel 16 - 23
	PS2000A_DIGITAL_PORT3,			 // digital channel 24 - 31
	PS2000A_MAX_DIGITAL_PORTS = (PS2000A_DIGITAL_PORT3 - PS2000A_DIGITAL_PORT0) + 1
}	PS2000A_DIGITAL_PORT;


/// <summary>
/// MSO digital channels
/// </summary>
typedef enum enPS2000ADigitalChannel
{
	PS2000A_DIGITAL_CHANNEL_0,
	PS2000A_DIGITAL_CHANNEL_1,
	PS2000A_DIGITAL_CHANNEL_2,
	PS2000A_DIGITAL_CHANNEL_3,
	PS2000A_DIGITAL_CHANNEL_4,
	PS2000A_DIGITAL_CHANNEL_5,
	PS2000A_DIGITAL_CHANNEL_6,
	PS2000A_DIGITAL_CHANNEL_7,
	PS2000A_DIGITAL_CHANNEL_8,
	PS2000A_DIGITAL_CHANNEL_9,
	PS2000A_DIGITAL_CHANNEL_10,
	PS2000A_DIGITAL_CHANNEL_11,
	PS2000A_DIGITAL_CHANNEL_12,
	PS2000A_DIGITAL_CHANNEL_13,
	PS2000A_DIGITAL_CHANNEL_14,
	PS2000A_DIGITAL_CHANNEL_15,
	PS2000A_DIGITAL_CHANNEL_16,
	PS2000A_DIGITAL_CHANNEL_17,
	PS2000A_DIGITAL_CHANNEL_18,
	PS2000A_DIGITAL_CHANNEL_19,
	PS2000A_DIGITAL_CHANNEL_20,
	PS2000A_DIGITAL_CHANNEL_21,
	PS2000A_DIGITAL_CHANNEL_22,
	PS2000A_DIGITAL_CHANNEL_23,
	PS2000A_DIGITAL_CHANNEL_24,
	PS2000A_DIGITAL_CHANNEL_25,
	PS2000A_DIGITAL_CHANNEL_26,
	PS2000A_DIGITAL_CHANNEL_27,
	PS2000A_DIGITAL_CHANNEL_28,
	PS2000A_DIGITAL_CHANNEL_29,
	PS2000A_DIGITAL_CHANNEL_30,
	PS2000A_DIGITAL_CHANNEL_31,
	PS2000A_MAX_DIGITAL_CHANNELS
} PS2000A_DIGITAL_CHANNEL;

/// <summary>
/// Ranges that the channels are set to:
/// Not all ranges are supported by every variant
/// </summary>
typedef enum enPS2000ARange
{
	PS2000A_10MV,
	PS2000A_20MV,
	PS2000A_50MV,
	PS2000A_100MV,
	PS2000A_200MV,
	PS2000A_500MV,
	PS2000A_1V,
	PS2000A_2V,
	PS2000A_5V,
	PS2000A_10V,
	PS2000A_20V,
	PS2000A_50V,
	PS2000A_MAX_RANGES,
} PS2000A_RANGE;

/// <summary>
/// Available coupling modes.
/// </summary>
typedef enum enPS2000ACoupling
{
	PS2000A_AC,
	PS2000A_DC
} PS2000A_COUPLING;

typedef enum enPS2000AChannelInfo
{
	PS2000A_CI_RANGES,
} PS2000A_CHANNEL_INFO;

/// <summary>
/// Ets modes avialable
/// </summary>
typedef enum enPS2000AEtsMode
{
	/// <summary>
	/// disables
	/// </summary>
  PS2000A_ETS_OFF,
	/// <summary>
	/// enables ETS and provides etsCycles of data, which may contain data from previously returned cycles.
	/// </summary>
  PS2000A_ETS_FAST,
	/// <summary>
	/// enables ETS and provides fresh data every etsCycles. This
	/// mode takes longer to provide each data set, but the data sets are more stable and
	/// are guaranteed to contain only new data.
	/// </summary>
	PS2000A_ETS_SLOW,

  PS2000A_ETS_MODES_MAX
  }	PS2000A_ETS_MODE;

/// <summary>
/// Time units that the time paramaters are using.
/// </summary>
typedef enum enPS2000ATimeUnits
  {
  PS2000A_FS,
  PS2000A_PS,
  PS2000A_NS,
  PS2000A_US,
  PS2000A_MS,
  PS2000A_S,
  PS2000A_MAX_TIME_UNITS,
  }	PS2000A_TIME_UNITS;

/// <summary>
/// whether the frequency will sweep from startFrequency to
/// stopFrequency, or in the opposite direction, or repeatedly reverse direction
/// </summary>
typedef enum enPS2000ASweepType
{
	PS2000A_UP,
	PS2000A_DOWN,
	PS2000A_UPDOWN,
	PS2000A_DOWNUP,
	PS2000A_MAX_SWEEP_TYPES
} PS2000A_SWEEP_TYPE;

/// <summary>
/// Built in waveform types
/// </summary>
typedef enum enPS2000AWaveType
{
	PS2000A_SINE,
	PS2000A_SQUARE,
	PS2000A_TRIANGLE,
	PS2000A_RAMP_UP,
	PS2000A_RAMP_DOWN,
	PS2000A_SINC,
	PS2000A_GAUSSIAN,
	PS2000A_HALF_SINE,
	PS2000A_DC_VOLTAGE,
	PS2000A_MAX_WAVE_TYPES
} PS2000A_WAVE_TYPE;

/// <summary>
/// The type of waveform to be produced, specified by one of the following
/// </summary>
typedef enum enPS2000AExtraOperations
{
	/// <summary>
	/// Normal signal generator operation specified by wavetype.
	/// </summary>
	PS2000A_ES_OFF,
	/// <summary>
	/// The signal generator produces white noise and ignores all settings except pkToPk and offsetVoltage.
	/// </summary>
	PS2000A_WHITENOISE,
	/// <summary>
	/// produces a pseudorandom random binary sequence with a bit rate
	/// specified by the start and stop frequency.
	/// </summary>
	PS2000A_PRBS // Pseudo-Random Bit Stream
} PS2000A_EXTRA_OPERATIONS;


#define PS2000A_SINE_MAX_FREQUENCY				1000000.f
#define PS2000A_SQUARE_MAX_FREQUENCY			1000000.f
#define PS2000A_TRIANGLE_MAX_FREQUENCY		1000000.f
#define PS2000A_SINC_MAX_FREQUENCY				1000000.f
#define PS2000A_RAMP_MAX_FREQUENCY				1000000.f
#define PS2000A_HALF_SINE_MAX_FREQUENCY		1000000.f
#define PS2000A_GAUSSIAN_MAX_FREQUENCY		1000000.f
#define PS2000A_PRBS_MAX_FREQUENCY				1000000.f
#define PS2000A_PRBS_MIN_FREQUENCY					 0.03f
#define PS2000A_MIN_FREQUENCY			  				 0.03f

/// <summary>
/// The type of trigger that will be applied to the signal generator
/// </summary>
typedef enum enPS2000ASigGenTrigType
{
	/// <summary>
	/// Trigger on rising edge
	/// </summary>
	PS2000A_SIGGEN_RISING,
	/// <summary>
	/// Trigger on falling edge
	/// </summary>
	PS2000A_SIGGEN_FALLING,
	/// <summary>
	/// Run while trigger is high
	/// </summary>
	PS2000A_SIGGEN_GATE_HIGH,
	/// <summary>
	/// Run while trigger is low
	/// </summary>
	PS2000A_SIGGEN_GATE_LOW
} PS2000A_SIGGEN_TRIG_TYPE;

/// <summary>
/// The source that will trigger the signal generator
/// </summary>
typedef enum enPS2000ASigGenTrigSource
{
	/// <summary>
	/// Run without waiting for trigger
	/// </summary>
	PS2000A_SIGGEN_NONE,
	/// <summary>
	/// Use scope trigger
	/// </summary
	PS2000A_SIGGEN_SCOPE_TRIG,
	/// <summary>
	/// Use AUXIO input
	/// </summary>
	PS2000A_SIGGEN_AUX_IN,
	/// <summary>
	/// Use external input
	/// </summary>
	PS2000A_SIGGEN_EXT_IN,
	/// <summary>
	/// Wait for software trigger
	/// </summary>
	PS2000A_SIGGEN_SOFT_TRIG
} PS2000A_SIGGEN_TRIG_SOURCE;

/// <summary>
/// AWG index modes
/// </summary>
typedef enum enPS2000AIndexMode
{
	/// <summary>
	/// The generator outputs the raw contents of the buffer repeatedly .
	/// </summary>
	PS2000A_SINGLE,
	/// <summary>
	/// The generator outputs the contents of the buffer from beginning to end, and then does a second pass in the reverse
	/// direction through the buffer
	/// </summary>
	PS2000A_DUAL,
	/// <summary>
	/// This is similiar to the Dual but passes through the buffer four time inverting, and inverting reversed
	/// </summary>
	PS2000A_QUAD,

	PS2000A_MAX_INDEX_MODES
} PS2000A_INDEX_MODE;

/// <summary>
/// The number of thershold that will be used for triggering.
/// </summary>
typedef enum enPS2000A_ThresholdMode
{
	PS2000A_LEVEL,
	PS2000A_WINDOW
} PS2000A_THRESHOLD_MODE;

/// <summary>
/// The direction that the signal will pass through the trigger.
/// </summary>
typedef enum enPS2000AThresholdDirection
{
	/// <summary>
	/// For gated triggers: above the upper threshold.
	/// </summary>
	PS2000A_ABOVE,
	/// <summary>
	/// For gated triggers: below the upper threshold.
	/// </summary
	PS2000A_BELOW,
	/// <summary>
	/// For threshold triggers: rising edge, using upper threshold.
	/// </summary>
	PS2000A_RISING,
	/// <summary>
	/// For threshold triggers: falling edge, using upper threshold.
	/// </summary>
	PS2000A_FALLING,
	/// <summary>
	/// For threshold triggers: either edge.
	/// </summary>
	PS2000A_RISING_OR_FALLING,
	/// <summary>
	/// For gated triggers: above the lower threshold.
	/// </summary>
	PS2000A_ABOVE_LOWER,
	/// <summary>
	/// For gated triggers: below the lower threshold.
	/// </summary>
	PS2000A_BELOW_LOWER,
	/// <summary>
	/// For threshold triggers: rising edge, using lower threshold.
	/// </summary>
	PS2000A_RISING_LOWER,
	/// <summary>
	/// For threshold triggers: falling edge, using lower threshold.
	/// </summary>
	PS2000A_FALLING_LOWER,

	/// <summary>
	/// For window-qualified triggers: inside window.
	/// </summary>
	PS2000A_INSIDE = PS2000A_ABOVE,
	/// <summary>
	/// For window-qualified triggers: outside window.
	/// </summary>
	PS2000A_OUTSIDE = PS2000A_BELOW,
	/// <summary>
	/// For window triggers: entering the window.
	/// </summary>
	PS2000A_ENTER = PS2000A_RISING,
	/// <summary>
  /// For window triggers: leaving the window.
  /// </summary>
	PS2000A_EXIT = PS2000A_FALLING,
	/// <summary>
	/// For window triggers: either entering or leaving the window.
	/// </summary>
	PS2000A_ENTER_OR_EXIT = PS2000A_RISING_OR_FALLING,
	/// <summary>
	/// For window-qualified triggers.
	/// </summary>
	PS2000A_POSITIVE_RUNT = 9,
	/// <summary>
	/// For window-qualified triggers.
	/// </summary>
  PS2000A_NEGATIVE_RUNT,

	/// <summary>
	/// No trigger.
	/// </summary>
  PS2000A_NONE = PS2000A_RISING
} PS2000A_THRESHOLD_DIRECTION;


/// <summary>
/// Digital channel trigger dirction
/// </summary>
typedef enum enPS2000ADigitalDirection
{
	PS2000A_DIGITAL_DONT_CARE,
	PS2000A_DIGITAL_DIRECTION_LOW,
	PS2000A_DIGITAL_DIRECTION_HIGH,
	PS2000A_DIGITAL_DIRECTION_RISING,
	PS2000A_DIGITAL_DIRECTION_FALLING,
	PS2000A_DIGITAL_DIRECTION_RISING_OR_FALLING,
	PS2000A_DIGITAL_MAX_DIRECTION
} PS2000A_DIGITAL_DIRECTION;

/// <summary>
/// The type of condition that should be applied to each channel.
/// The channels that are set to True or False must all meet their conditions
/// simultaneously to produce a trigger. Channels set to DontCare are ignored.
/// </summary>
typedef enum enPS2000ATriggerState
{
  PS2000A_CONDITION_DONT_CARE,
  PS2000A_CONDITION_TRUE,
  PS2000A_CONDITION_FALSE,
	PS2000A_CONDITION_MAX
} PS2000A_TRIGGER_STATE;

/// <summary>
/// A structure of this type is passed to ps2000aSetTriggerChannelConditions in the
/// conditions argument to specify the trigger conditions.
/// </summary>
#pragma pack(push,1)
typedef struct tPS2000ATriggerConditions
{
  PS2000A_TRIGGER_STATE channelA;
  PS2000A_TRIGGER_STATE channelB;
  PS2000A_TRIGGER_STATE channelC;
  PS2000A_TRIGGER_STATE channelD;
  PS2000A_TRIGGER_STATE external;
  PS2000A_TRIGGER_STATE aux;
	PS2000A_TRIGGER_STATE pulseWidthQualifier;
	PS2000A_TRIGGER_STATE digital;
} PS2000A_TRIGGER_CONDITIONS;
#pragma pack(pop)


/// <summary>
/// A structure of this type is passed to ps2000aSetPulseWidthQualifier in the
/// conditions argument to specify the trigger conditions.
/// Analog-input models only ( for MSOs use PwqConditionsV2)
/// </summary>
#pragma pack(push,1)
typedef struct tPS2000APwqConditions
{
  PS2000A_TRIGGER_STATE channelA;
  PS2000A_TRIGGER_STATE channelB;
  PS2000A_TRIGGER_STATE channelC;
  PS2000A_TRIGGER_STATE channelD;
  PS2000A_TRIGGER_STATE external;
  PS2000A_TRIGGER_STATE aux;
	PS2000A_TRIGGER_STATE digital;
} PS2000A_PWQ_CONDITIONS;
#pragma pack(pop)

/// <summary>
/// A structure of this type is passed to ps2000aSetTriggerChannelDirections in
/// the directions argument to specify the trigger direction for a specified source.
/// Not all driver series support this method.
/// </summary>
#pragma pack(push,1)
typedef struct tPS2000ADigitalChannelDirections
{
	/// <summary>
	/// The channel being configured. Channels supported by series SetChannel for allowable values.
	/// </summary>
	PS2000A_DIGITAL_CHANNEL channel;
	/// <summary>
	/// The trigger direction that should be applied to each channel.
	/// </summary>
	PS2000A_DIGITAL_DIRECTION direction;
} PS2000A_DIGITAL_CHANNEL_DIRECTIONS;
#pragma pack(pop)

/// <summary>
/// A structure of this type is passed to ps2000aSetTriggerChannelProperties in the
/// channelProperties argument to specify the trigger mechanism.
/// All values are scaled in 16-bit ADC counts at the currently selected range for that channel.
/// </summary>
#pragma pack(push,1)
typedef struct tPS2000ATriggerChannelProperties
{
	/// <summary>
	/// The upper threshold at which the trigger must fire
	/// </summary>
  int16_t										thresholdUpper;
	/// <summary>
	/// The hysteresis by which the trigger must exceed the upper threshold before it will fire.
	/// </summary>
	uint16_t					thresholdUpperHysteresis;
	/// <summary>
	/// The lower threshold at which the trigger must fire.
	/// </summary>
  int16_t										thresholdLower;
	/// <summary>
	/// The hysteresis by which the trigger must exceed the lower threshold before it will fire.
	/// </summary>
	uint16_t					thresholdLowerHysteresis;
	/// <summary>
	/// The channel to which the properties apply
	/// </summary>
	PS2000A_CHANNEL					channel;
	/// <summary>
	/// Either a level or window trigger
	/// </summary>
  PS2000A_THRESHOLD_MODE	thresholdMode;
} PS2000A_TRIGGER_CHANNEL_PROPERTIES;
#pragma pack(pop)

/// <summary>
/// Various methods of data reduction.
/// Note that a single call to setting the buffers (ie. ps2000aSetDataBuffer) can only
/// associate one buffer with one downsampling mode. If you intend to retrieve more than one
/// downsampling mode from the get values functions, you must call set data buffer several
///	times to associate a separate buffer with each channel and downsampling mode.
/// </summary>
typedef enum enPS2000ARatioMode
{
	/// <summary>
	/// No downsampling. Returns the raw data values.
	/// </summary>
	PS2000A_RATIO_MODE_NONE,
	/// <summary>
	/// Reduces every block of n values to just two values: a minimum and a maximum.
	/// The minimum and maximum values are returned in two separate buffers.
	/// </summary>
	PS2000A_RATIO_MODE_AGGREGATE = 1,
	/// <summary>
	/// Reduces every block of n values to a single value representing the
	/// average (arithmetic mean) of all the values.
	/// </summary>
	PS2000A_RATIO_MODE_DECIMATE = 2,
	/// <summary>
	/// Reduces every block of n values to just the first value in the block,
	/// discarding all the other values.
	/// </summary>
	PS2000A_RATIO_MODE_AVERAGE = 4,
} PS2000A_RATIO_MODE;


/// <summary>
/// The pulse-width type.
/// </summary>
typedef enum enPS2000APulseWidthType
{
	/// <summary>
	/// Do not use the pulse width qualifier
	/// </summary>
	PS2000A_PW_TYPE_NONE,
	/// <summary>
	/// Pulse width less than lower pulse width counter
	/// </summary>
  PS2000A_PW_TYPE_LESS_THAN,
	/// <summary>
	/// Pulse width greater than lower pulse width counter
	/// </summary>
	PS2000A_PW_TYPE_GREATER_THAN,
	/// <summary>
	/// Pulse width between lower and upper pulsee width counter
	/// </summary>
	PS2000A_PW_TYPE_IN_RANGE,
	/// <summary>
	/// Pulse width not between lower and upper pulse width counter
	/// </summary>
	PS2000A_PW_TYPE_OUT_OF_RANGE
} PS2000A_PULSE_WIDTH_TYPE;

typedef enum enPS2000AHoldOffType
{
	PS2000A_TIME,
	PS2000A_MAX_HOLDOFF_TYPE
} PS2000A_HOLDOFF_TYPE;

#pragma pack(push,1)
typedef struct tPS2000AScalingFactors
{
	PS2000A_CHANNEL channelOrPort;
	PS2000A_RANGE   range;
	int16_t         offset;
	double          scalingFactor;
}PS2000A_SCALING_FACTORS_VALUES;
#pragma pack(pop)

  /// <summary>
  /// This callback function is part of your application. You register it with the ps3000a
  /// driver using series RunBlock, and the driver calls it back when block-mode data is
  /// ready. You can then download the data using series GetValues.
  /// </summary>
  /// <param name="handle">Device identifier returned by OpenUnit.</param>
  /// <param name="status">Indicates whether an error occurred during collection of the data.</param>
  /// <param name="pParameter">A void pointer passed from series RunBlock. Your callback function can write to this
  ///  location to send any data, such as a status flag, back to your application.</param>
typedef void (__stdcall *ps2000aBlockReady)
	(
		int16_t											handle,
		PICO_STATUS								status,
		void										*	pParameter
	);

/// <summary>
/// This callback function is part of your application. You register it with the driver using
/// series GetStreamingLatestValues, and the driver calls it back when streaming- mode data is
/// ready. You can then download the data using the series GetValuesAsync function.
/// </summary>
/// <param name="handle">Device identifier returned by OpenUnit.</param>
/// <param name="noOfSamples">The number of samples available.</param>
/// <param name="startIndex">An index to the first valid sample in the buffer. This is
///  the buffer that was previously passed to series SetDataBuffer.</param>
/// <param name="overflow">Returns a set of flags that indicate whether an overvoltage has occurred
///  on any of the channels.It is a bit pattern with bit 0 denoting Channel.</param>
/// <param name="triggerAt">An index to the buffer indicating the location of the trigger point relative
///  to startIndex.This parameter is valid only when triggered is non-zero.</param>
/// <param name="triggered">A flag indicating whether a trigger occurred. If non-zero,
///  a trigger occurred at the location indicated by triggerAt.</param>
/// <param name="autoStop">The flag that was set in the call to series RunStreaming.</param>
/// <param name="pParameter">a void pointer passed from series GetStreamingLatestValues.
/// The callback function can write to this locatio.</param>
typedef void (__stdcall *ps2000aStreamingReady)
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

/// <summary>
/// This is a callback function that you write to collect data from the driver. You supply a
/// pointer to the function when you call ps3000aGetValuesAsync, and the driver calls
/// your function back when the data is ready.
/// </summary>
/// <param name="handle">Device identifier returned by OpenUnit.</param>
/// <param name="status">Indicates whether an error occurred during collection of the data.</param>
/// <param name="noOfSamples">the number of samples collected.</param>
/// <param name="overflow">A set of flags that indicates whether an overvoltage has
/// occurred and on which channels.It is a bit field with bit 0 representing Channel A.</param>
/// <param name="pParameter">A void pointer passed from ps3000aGetValuesAsync. The callback function can
/// write to this location to send any data, such as a status flag, back to the application.
/// The data type is defined by the application programmer.</param>
typedef void (__stdcall *ps2000aDataReady)
	(
		int16_t    									handle,
		PICO_STATUS								status,
		uint32_t     				noOfSamples,
		int16_t    									overflow,
		void										*	pParameter
	);

/// <summary>
/// This function opens a PicoScope 2000 Series (A API) scope attached to the computer.
/// The maximum number of units that can be opened depends on the operating system, the kernel driver and the computer.
/// </summary>
/// <param name="handle"> on exit, the result of the attempt to open a scope:
///                       -1 : if the scope fails to open
///                       0 : if no scope is found
///                       > 0 : a number that uniquely identifies the scope
///                       If a valid handle is returned, it must be used in all subsequent calls
///												to API functions to identify this scope.</param>
/// <param name="serial">on entry, a null-terminated string containing the serial
///                      number of the scope to be opened.If serial is NULL then the
///                      function opens the first scope found; otherwise, it tries to open the
///                      scope that matches the string.</param>
/// <returns>
/// PICO_OK
/// PICO_OS_NOT_SUPPORTED
/// PICO_OPEN_OPERATION_IN_PROGRESS
/// PICO_EEPROM_CORRUPT
/// PICO_KERNEL_DRIVER_TOO_OLD
/// PICO_FPGA_FAIL
/// PICO_MEMORY_CLOCK_FREQUENCY
/// PICO_FW_FAIL
/// PICO_MAX_UNITS_OPENED
/// PICO_NOT_FOUND(if the specified unit was not found)
/// PICO_NOT_RESPONDING
/// PICO_MEMORY_FAIL
/// PICO_ANALOG_BOARD
/// PICO_CONFIG_FAIL_AWG
/// PICO_INITIALISE_FPGA
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aOpenUnit)
  (
	  int16_t											* handle,
		int8_t											* serial
	);

/// <summary>
/// This function opens a scope without blocking the calling thread. You can find out when
/// it has finished by periodically calling ps2000aOpenUnitProgress until that function
/// returns a non - zero value.
/// </summary>
/// <param name="status">a status code:
///                      0 if the open operation was disallowed because another open
///                      operation is in progress. 1 if the open operation was successfully.</param>
/// <param name="serial">see ps2000aOpenUnit.</param>
/// <returns>
/// PICO_OK
/// PICO_OPEN_OPERATION_IN_PROGRESS
/// PICO_OPERATION_FAILED
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aOpenUnitAsync)
  (
	  int16_t											* status,
		int8_t											* serial
	);

/// <summary>
/// This function checks on the progress of a request made to ps2000aOpenUnitAsync to
/// open a scope.
/// </summary>
/// <param name="handle">This handle is valid only if the function returns PICO_OK.</param>
/// <param name="progressPercent">On exit, the percentage progress towards
///  opening the scope. 100% implies that the open operation is complete.</param>
/// <param name="complete">Set to 1 when the open operation has finished.</param>
/// <returns>
/// PICO_OK
/// PICO_NULL_PARAMETER
/// PICO_OPERATION_FAILED
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aOpenUnitProgress)
	(
	  int16_t 										* handle,
	  int16_t 										* progressPercent,
	  int16_t 										* complete
	);

/// <summary>
/// This function retrieves information about the specified oscilloscope. If the device fails
/// to open, or no device is opened only the driver version is available.
/// </summary>
/// <param name="handle">device identifier returned by ps2000aOpenUnit. If an invalid
///  handle is passed, only the driver versions can be read.</param>
/// <param name="string">On exit, the unit information string selected specified by
/// the info argument.If string is NULL, only requiredSize is returned.</param>
/// <param name="stringLength">The maximum number of chars that may be written to string.</param>
/// <param name="requiredSize">On exit, the required length of the string array.</param>
/// <param name="info">a number specifying what information is required.
/// The possible values are listed in the table below.</param>
/// <returns>
/// PICO_OK
/// PICO_INVALID_HANDLE
/// PICO_NULL_PARAMETER
/// PICO_INVALID_INFO
/// PICO_INFO_UNAVAILABLE
/// PICO_DRIVER_FUNCTION
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aGetUnitInfo)
 	(
	  int16_t     								  handle,
	  int8_t      								* string,
	  int16_t     								  stringLength,
	  int16_t     								* requiredSize,
	  PICO_INFO 								  info
	);

/// <summary>
/// This function flashes the LED on the front of the scope without blocking the calling
/// thread.Calls to ps2000aRunStreaming and ps2000aRunBlock cancel any flashing
/// started by this function.It is not possible to set the LED to be constantly illuminated,
///  as this state is used to indicate that the scope has not been initialized.
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="start">the action required:
///            < 0 : flash the LED indefinitely
///            0 : stop the LED flashing
///            > 0 : flash the LED start times.If the LED is already flashing
///                  on entry to this function, the flash count will be reset to start.</param>
/// <returns>
/// PICO_OK
///	PICO_HANDLE_INVALID
///	PICO_BUSY
///	PICO_DRIVER_FUNCTION
///	PICO_NOT_RESPONDING
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aFlashLed)
	(
	  int16_t 											handle,
		int16_t 											start
	);

/// <summary>
/// This function shuts down an oscilloscope.
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <returns>
/// PICO_OK
///	PICO_HANDLE_INVALID
///	PICO_USER_CALLBACK
///	PICO_DRIVER_FUNCTION
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aCloseUnit)
	(
	  int16_t												handle
	);

/// <summary>
/// This function sets the number of memory segments that the scope will use. When the scope is opened,
/// the number of segments defaults to 1, meaning that each capture fills the scope's available memory.
/// This function allows you to divide the memory into a number of segments so that the scope can
/// store several waveforms sequentially.
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="nSegments">The number of segments required, from 1 to ps2000aGetMaxSegments.</param>
/// <param name="nMaxSamples">on exit, the number of samples available in each segment.This is
///  the total number over all channels, so if more than one channel is in use then the number
///  of samples available to each channel is nMaxSamples divided by the number of channels.</param>
/// <returns>
///	PICO_OK
///	PICO_USER_CALLBACK
///	PICO_INVALID_HANDLE
///	PICO_TOO_MANY_SEGMENTS
///	PICO_MEMORY
///	PICO_DRIVER_FUNCTION
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aMemorySegments)
	(
	  int16_t												handle,
		uint32_t							nSegments,
		int32_t											* nMaxSamples
	);

/// <summary>
/// This function specifies whether an input channel is to be enabled, its input coupling
///	type, voltage range, analog offset.
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="channel">, the channel to be configured. The values are:
///		PS2000A_CHANNEL_A: Channel A input
///		PS2000A_CHANNEL_B : Channel B input
///		PS2000A_CHANNEL_C : Channel C input
///		PS2000A_CHANNEL_D : Channel D input</param>
/// <param name="enabled">Whether or not to enable the channel. The values are:
///		TRUE: enable
///		FALSE : do not enable</param>
/// <param name="type">the impedance and coupling type. The values are:
///		PS2000A_AC: 1 megohm impedance, AC coupling.The channel accepts input frequencies
///               from about 1 hertz up to its maximum analog bandwidth.
///		PS2000A_DC: 1 megohm impedance, DC coupling.The channel accepts all input frequencies
///               from zero(DC) up to its maximum analog bandwidth.</param>
/// <param name="range">The input voltage range.</param>
/// <param name="analogOffset">a voltage to add to the input channel before digitization.
/// The allowable range of offsets can be obtained from ps2000aGetAnalogueOffset and depends
/// on the input range selected for the channel.This argument is ignored if the device is a
/// PicoScope 2205 MSO.</param>
/// <returns>
/// PICO_OK
///	PICO_USER_CALLBACK
///	PICO_INVALID_HANDLE
///	PICO_INVALID_CHANNEL
///	PICO_INVALID_VOLTAGE_RANGE
///	PICO_INVALID_COUPLING
///	PICO_INVALID_ANALOGUE_OFFSET
///	PICO_DRIVER_FUNCTION
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aSetChannel)
 	(
	  int16_t												handle,
		PS2000A_CHANNEL							channel,
	  int16_t												enabled,
	  PS2000A_COUPLING						type,
		PS2000A_RANGE								range,
		float												analogOffset
	);

/// <summary>
/// This function is used to enable the digital ports of an MSO and set the logic level (the
///	voltage point at which the state transitions from 0 to 1).
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="port">the digital port to be configured:
///		PS2000A_DIGITAL_PORT0 = 0x80 (D0 to D7)
///		PS2000A_DIGITAL_PORT1 = 0x81 (D8 to D15)</param>
/// <param name="enabled">Whether or not to enable the channel. The values are:
///		TRUE: enable
///		FALSE : do not enable</param>
/// <param name="logicLevel">The logic threshold voltage. Range: �32767 (�5 V) to 32767 (5 V).</param>
/// <returns>
/// PICO_OK
///	PICO_INVALID_HANDLE
///	PICO_INVALID_CHANNEL
///	PICO_RATIO_MODE_NOT_SUPPORTED
///	PICO_SEGMENT_OUT_OF_RANGE
///	PICO_DRIVER_FUNCTION
///	PICO_INVALID_PARAMETER
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aSetDigitalPort)
 	(
	  int16_t												handle,
		PS2000A_DIGITAL_PORT				port,
	  int16_t												enabled,
		int16_t									      logicLevel
	);


/// <summary>
/// This function sets the number of captures to be collected in one run of rapid block
///	mode.If you do not call this function before a run, the driver will capture only one
///	waveform.Once a value has been set, the value remains constant unless changed.
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="nCaptures">The number of waveforms to capture in one run.</param>
/// <returns>
/// PICO_OK
///	PICO_INVALID_HANDLE
///	PICO_INVALID_PARAMETER
///	PICO_DRIVER_FUNCTION
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aSetNoOfCaptures)
	(
	int16_t handle,
	uint32_t nCaptures
	);

/// <summary>
/// This function calculates the sampling rate and maximum number of samples for a
/// given timebase under the specified conditions.The result will depend on the number of
/// channels enabled by the last call to ps2000aSetChannel.
///
/// This function is provided for use with programming languages that do not support the
/// float data type.The value returned in the timeIntervalNanoseconds argument is
/// restricted to integers.If your programming language supports the float type, we
/// recommend that you use ps2000aGetTimebase2 instead.
///
/// To use ps2000aGetTimebase or ps2000aGetTimebase2, first estimate the timebase
/// number that you require using the information in the timebase guide.Next, call one of
/// these functions with the timebase that you have just chosen and verify that the
/// timeIntervalNanoseconds argument that the function returns is the value that you
/// require.You may need to iterate this process until you obtain the time interval that you need.
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="timebase">The timebase guide.</param>
/// <param name="noSamples">The number of samples required.</param>
/// <param name="timeIntervalNanoseconds">On exit, the time interval between readings at the
///  selected timebase.Use NULL if not required.In ETS mode this argument is not valid;
///  use the sample time returned by ps2000aSetEts.</param>
/// <param name="oversample">Not used.</param>
/// <param name="maxSamples">On exit, the maximum number of samples available. The scope allocates
/// a certain amount of memory for internal overheads and this may vary depending on the number of
///  segments, number of channels enabled, and the timebase chosen.Use NULL if not required.</param>
/// <param name="segmentIndex">The index of the memory segment to use.</param>
/// <returns>
/// /// PICO_OK
///	PICO_INVALID_HANDLE
///	PICO_TOO_MANY_SAMPLES
///	PICO_INVALID_CHANNEL
///	PICO_INVALID_TIMEBASE
///	PICO_INVALID_PARAMETER
///	PICO_SEGMENT_OUT_OF_RANGE
///	PICO_DRIVER_FUNCTION
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aGetTimebase)
	(
	   int16_t											handle,
	   uint32_t							timebase,
	   int32_t												noSamples,
	   int32_t											* timeIntervalNanoseconds,
	   int16_t											oversample,
		 int32_t											* maxSamples,
		 uint32_t							segmentIndex
	);

/// <summary>
/// This function is an upgraded version of ps2000aGetTimebase, and returns the time
///	interval as a float rather than a long.This allows it to return sub - nanosecond time
///	intervals.See ps2000aGetTimebase for a full description.
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="timebase">The timebase guide.</param>
/// <param name="noSamples">The number of samples required.</param>
/// <param name="timeIntervalNanoseconds">A pointer to the time interval between readings at
///  the selected timebase.If a null pointer is passed, the parameter will be ignored.</param>
/// <param name="oversample">Not used.</param>
/// <param name="maxSamples">On exit, the maximum number of samples available. The scope allocates
/// a certain amount of memory for internal overheads and this may vary depending on the number of
///  segments, number of channels enabled, and the timebase chosen.Use NULL if not required.</param>
/// <param name="segmentIndex">The index of the memory segment to use.</param>
/// <returns>
/// PICO_OK
///	PICO_INVALID_HANDLE
///	PICO_TOO_MANY_SAMPLES
///	PICO_INVALID_CHANNEL
///	PICO_INVALID_TIMEBASE
///	PICO_INVALID_PARAMETER
///	PICO_SEGMENT_OUT_OF_RANGE
///	PICO_DRIVER_FUNCTION
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aGetTimebase2)
	(
	   int16_t											handle,
	   uint32_t							timebase,
	   int32_t												noSamples,
	   float										* timeIntervalNanoseconds,
	   int16_t											oversample,
		 int32_t											* maxSamples,
		 uint32_t							segmentIndex
	);

/// <summary>
/// This function programs the signal generator to produce an arbitrary waveform. The arbitrary waveform
/// generator uses direct digital synthesis (DDS). It maintains a 32 - bit phase accumulator that
/// indicates the present location in the waveform.The top bits of the phase accumulator are used as
/// an index into a buffer containing the arbitrary waveform.The remaining bits act as the fractional
/// part of the index, enabling high - resolution control of output frequency and allowing the
/// generation of lower frequencies.
///
/// The phase accumulator initially increments by startDeltaPhase.If the AWG is set to sweep mode, the
/// phase increment is increased at specified intervals until it reaches stopDeltaPhase. The easiest way
/// to obtain the values of startDeltaPhase and stopDeltaPhase necessary to generate the desired frequency
/// is to call ps2000aSigGenFrequencyToPhase.
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="offsetVoltage">The voltage offset, in microvolts, to be applied to the waveform.</param>
/// <param name="pkToPk">The peak-to-peak voltage, in microvolts, of the waveform signal.</param>
/// <param name="startDeltaPhase">The initial value added to the phase accumulator as the generator
///	begins to step through the waveform buffer.Calculate this value from the information above, or use
/// ps2000aSigGenFrequencyToPhase.</param>
/// <param name="stopDeltaPhase">The final value added to the phase accumulator before the generator
/// restarts or reverses the sweep.When frequency sweeping is not required, set equal to startDeltaPhase.</param>
/// <param name="deltaPhaseIncrement">the amount added to the delta phase value every time the dwellCount
/// period expires.This determines the amount by which the generator sweeps the output frequency in each
/// dwell period.When frequency sweeping is not required, set to zero.</param>
/// <param name="dwellCount">the time, in multiples of ddsPeriod, between successive additions of
///	deltaPhaseIncrement to the delta phase accumulator.This determines the rate at which the generator
/// sweeps the output frequency.Minimum value : PS2000A_MIN_DWELL_COUNT.</param>
/// <param name="arbitaryWaveform">A buffer that holds the waveform pattern as a set of samples equally
/// spaced in time.Each sample is scaled to an output voltage as follows:
///
///    vOUT = 1 �V *(pkToPk / 2) *(sample_value / 32767) + offsetVoltage
///
/// and clipped to the overall �2 V range of the AWG.</param>
/// <param name="arbitaryWaveformSize">the size of the arbitrary waveform buffer, in samples, in the range:
/// [minArbitraryWaveformSize, maxArbitraryWaveformSize] where minArbitraryWaveformSize and
/// maxArbitraryWaveformSize are the values returned by ps2000aSigGenArbitraryMinMaxValues.</param>
/// <param name="sweepType">, determines whether the startDeltaPhase is swept up to the stopDeltaPhase,
/// or down to it, or repeatedly swept up and down.</param>
/// <param name="operation">The type of waveform to be produced.</param>
/// <param name="indexMode">Specifies how the signal will be formed from the arbitrary waveform data.
/// Single and dual index modes are possible.</param>
/// <param name="shots">0: sweep the frequency as specified by sweeps
///	1...PS2000A_MAX_SWEEPS_SHOTS: the number of cycles of the waveform to be
/// produced after a trigger event.sweeps must be zero.
/// PS2000A_SHOT_SWEEP_TRIGGER_CONTINUOUS_RUN : start and run continuously after trigger
/// occurs(not PicoScope 2205 MSO).</param>
/// <param name="sweeps">0: produce number of cycles specified by shots
/// 1..PS2000A_MAX_SWEEPS_SHOTS: the number of times to sweep the frequency after a trigger event,
/// according to sweepType.shots must be zero.
/// PS2000A_SHOT_SWEEP_TRIGGER_CONTINUOUS_RUN: start a sweep and continue after trigger
/// occurs(not PicoScope 2205 MSO).</param>
/// <param name="triggerType">The type of trigger that will be applied to the signal generator.</param>
/// <param name="triggerSource">The source that will trigger the signal generator.
/// If a trigger source other than P2000A_SIGGEN_NONE is specified, then either shots or sweeps,
/// but not both, must be non - zero.</param>
/// <param name="extInThreshold">Trigger level, in ADC counts, for external trigger.</param>
/// <returns>
/// PICO_OK
///	PICO_AWG_NOT_SUPPORTED
///	PICO_BUSY
///	PICO_INVALID_HANDLE
///	PICO_SIG_GEN_PARAM
///	PICO_SHOTS_SWEEPS_WARNING
///	PICO_NOT_RESPONDING
///	PICO_WARNING_EXT_THRESHOLD_CONFLICT
///	PICO_NO_SIGNAL_GENERATOR
///	PICO_SIGGEN_OFFSET_VOLTAGE
///	PICO_SIGGEN_PK_TO_PK
///	PICO_SIGGEN_OUTPUT_OVER_VOLTAGE
///	PICO_DRIVER_FUNCTION
///	PICO_SIGGEN_WAVEFORM_SETUP_FAILED
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aSetSigGenArbitrary)
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
		PS2000A_SWEEP_TYPE					sweepType,
		PS2000A_EXTRA_OPERATIONS		operation,
		PS2000A_INDEX_MODE					indexMode,
		uint32_t								shots,
		uint32_t								sweeps,
		PS2000A_SIGGEN_TRIG_TYPE		triggerType,
		PS2000A_SIGGEN_TRIG_SOURCE	triggerSource,
		int16_t												extInThreshold
	);

/// <summary>
/// This function sets up the signal generator to produce a signal from a list of built-in
/// waveforms.If different start and stop frequencies are specified, the device will sweep
/// either up, down, or up and down.
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="offsetVoltage">The voltage offset, in microvolts, to be applied to the waveform</param>
/// <param name="pkToPk">The peak-to-peak voltage, in microvolts, of the waveform signal.
///
///  Note: if the signal voltages described by the combination of offsetVoltage and pkToPk
///  extend outside the voltage range of the signal generator, the output waveform will be clipped.</param>
/// <param name="waveType">The type of waveform to be generated.</param>
/// <param name="startFrequency">The frequency that the signal generator will initially produce. See
/// #defines above.</param>
/// <param name="stopFrequency">The frequency at which the sweep reverses direction or returns to
///	the initial frequency.</param>
/// <param name="increment">The amount of frequency increase or decrease in sweep mode.</param>
/// <param name="dwellTime">The time for which the sweep stays at each frequency, in seconds.</param>
/// <param name="sweepType">whether the frequency will sweep from startFrequency to stopFrequency,
///  or in the opposite direction, or repeatedly reverse direction.</param>
/// <param name="operation">the type of waveform to be produced, specified by one of the following
///	enumerated types :
///		PS2000A_ES_OFF, normal signal generator operation specified by waveType.PS2000A_WHITENOISE,
///	  the signal generator produces white noise and ignores all settings except pkToPk and offsetVoltage.
///		PS2000A_PRBS, produces a random bitstream with a bit rate specified by the start and stop
///		frequency(not available on PicoScope 2205 MSO).</param>
/// <param name="shots">0: sweep the frequency as specified by sweeps
///	1...PS2000A_MAX_SWEEPS_SHOTS: the number of cycles of the waveform to be
/// produced after a trigger event.sweeps must be zero.
/// PS2000A_SHOT_SWEEP_TRIGGER_CONTINUOUS_RUN : start and run continuously after trigger
/// occurs(not PicoScope 2205 MSO)./param>
/// <param name="sweeps">0: produce number of cycles specified by shots
/// 1..PS2000A_MAX_SWEEPS_SHOTS: the number of times to sweep the frequency after a trigger event,
/// according to sweepType.shots must be zero.
/// PS2000A_SHOT_SWEEP_TRIGGER_CONTINUOUS_RUN: start a sweep and continue after trigger
/// occurs(not PicoScope 2205 MSO).</param>
/// <param name="triggerType">The type of trigger that will be applied to the signal generator.</param>
/// <param name="triggerSource">The source that will trigger the signal generator.
/// If a trigger source other than P2000A_SIGGEN_NONE is specified, then either shots or sweeps,
/// but not both, must be non - zero.</param>
/// <param name="extInThreshold">Trigger level, in ADC counts, for external trigger.</param>
/// <returns>
/// PICO_OK
///	PICO_BUSY
///	PICO_INVALID_HANDLE
///	PICO_SIG_GEN_PARAM
///	PICO_SHOTS_SWEEPS_WARNING
///	PICO_NOT_RESPONDING
///	PICO_WARNING_AUX_OUTPUT_CONFLICT
///	PICO_WARNING_EXT_THRESHOLD_CONFLICT
///	PICO_NO_SIGNAL_GENERATOR
///	PICO_SIGGEN_OFFSET_VOLTAGE
///	PICO_SIGGEN_PK_TO_PK
///	PICO_SIGGEN_OUTPUT_OVER_VOLTAGE
///	PICO_DRIVER_FUNCTION
///	PICO_SIGGEN_WAVEFORM_SETUP_FAILED
///	PICO_NOT_RESPONDING
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps2000aSetSigGenBuiltIn)
	(
		int16_t												handle,
		int32_t												offsetVoltage,
		uint32_t								pkToPk,
		int16_t												waveType,
		float												startFrequency,
		float												stopFrequency,
		float												increment,
		float												dwellTime,
		PS2000A_SWEEP_TYPE					sweepType,
		PS2000A_EXTRA_OPERATIONS		operation,
		uint32_t								shots,
		uint32_t								sweeps,
		PS2000A_SIGGEN_TRIG_TYPE		triggerType,
		PS2000A_SIGGEN_TRIG_SOURCE	triggerSource,
		int16_t												extInThreshold
		);

/// <summary>
/// This function sets up the signal generator. It differs from ps2000SetSigGenBuiltIn in
/// having double - precision arguments instead of floats, giving greater resolution when
/// setting the output frequency.
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="offsetVoltage">The voltage offset, in microvolts, to be applied to the waveform.</param>
/// <param name="pkToPk">The peak-to-peak voltage, in microvolts, of the waveform signal.
///
///  Note: if the signal voltages described by the combination of offsetVoltage and pkToPk
///  extend outside the voltage range of the signal generator, the output waveform will be clipped.</param>
/// <param name="waveType">The type of waveform to be generated.</param>
/// <param name="startFrequency">The frequency that the signal generator will initially produce. See
/// #defines above.</param>
/// <param name="stopFrequency">The frequency at which the sweep reverses direction or returns to
///	the initial frequency.</param>
/// <param name="increment">The amount of frequency increase or decrease in sweep mode.</param>
/// <param name="dwellTime">The time for which the sweep stays at each frequency, in seconds.</param>
/// <param name="sweepType">whether the frequency will sweep from startFrequency to stopFrequency,
///  or in the opposite direction, or repeatedly reverse direction.</param>
/// <param name="operation">the type of waveform to be produced, specified by one of the following
///	enumerated types :
///		PS2000A_ES_OFF, normal signal generator operation specified by waveType.PS2000A_WHITENOISE,
///	  the signal generator produces white noise and ignores all settings except pkToPk and offsetVoltage.
///		PS2000A_PRBS, produces a random bitstream with a bit rate specified by the start and stop
///		frequency(not available on PicoScope 2205 MSO).</param>
/// <param name="shots">0: sweep the frequency as specified by sweeps
///	1...PS2000A_MAX_SWEEPS_SHOTS: the number of cycles of the waveform to be
/// produced after a trigger event.sweeps must be zero.
/// PS2000A_SHOT_SWEEP_TRIGGER_CONTINUOUS_RUN : start and run continuously after trigger
/// occurs(not PicoScope 2205 MSO).</param>
/// <param name="sweeps">0: produce number of cycles specified by shots
/// 1..PS2000A_MAX_SWEEPS_SHOTS: the number of times to sweep the frequency after a trigger event,
/// according to sweepType.shots must be zero.
/// PS2000A_SHOT_SWEEP_TRIGGER_CONTINUOUS_RUN: start a sweep and continue after trigger
/// occurs(not PicoScope 2205 MSO).</param>
/// <param name="triggerType">The type of trigger that will be applied to the signal generator.</param>
/// <param name="triggerSource">The source that will trigger the signal generator.
/// If a trigger source other than P2000A_SIGGEN_NONE is specified, then either shots or sweeps,
/// but not both, must be non - zero.</param>
/// <param name="extInThreshold">Trigger level, in ADC counts, for external trigger.</param>
/// <returns>
/// PICO_OK
///	PICO_BUSY
///	PICO_INVALID_HANDLE
///	PICO_SIG_GEN_PARAM
///	PICO_SHOTS_SWEEPS_WARNING
///	PICO_NOT_RESPONDING
///	PICO_WARNING_AUX_OUTPUT_CONFLICT
///	PICO_WARNING_EXT_THRESHOLD_CONFLICT
///	PICO_NO_SIGNAL_GENERATOR
///	PICO_SIGGEN_OFFSET_VOLTAGE
///	PICO_SIGGEN_PK_TO_PK
///	PICO_SIGGEN_OUTPUT_OVER_VOLTAGE
///	PICO_DRIVER_FUNCTION
///	PICO_SIGGEN_WAVEFORM_SETUP_FAILED
///	PICO_NOT_RESPONDING
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps2000aSetSigGenBuiltInV2)
	(
		int16_t												handle,
		int32_t												offsetVoltage,
		uint32_t								pkToPk,
		int16_t												waveType,
		double												startFrequency,
		double												stopFrequency,
		double												increment,
		double												dwellTime,
		PS2000A_SWEEP_TYPE					sweepType,
		PS2000A_EXTRA_OPERATIONS		operation,
		uint32_t								shots,
		uint32_t								sweeps,
		PS2000A_SIGGEN_TRIG_TYPE		triggerType,
		PS2000A_SIGGEN_TRIG_SOURCE	triggerSource,
		int16_t												extInThreshold
		);

/// <summary>
/// This function reprograms the arbitrary waveform generator. All values can be reprogrammed while
/// the signal generator is waiting for a trigger.
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="startDeltaPhase">The initial value added to the phase accumulator as the generator
///	begins to step through the waveform buffer.Calculate this value from the information above, or use
/// ps2000aSigGenFrequencyToPhase.</param>
/// <param name="stopDeltaPhase">The final value added to the phase accumulator before the generator
/// restarts or reverses the sweep.When frequency sweeping is not required, set equal to startDeltaPhase.</param>
/// <param name="deltaPhaseIncrement">the amount added to the delta phase value every time the dwellCount
/// period expires.This determines the amount by which the generator sweeps the output frequency in each
/// dwell period.When frequency sweeping is not required, set to zero.</param>
/// <param name="dwellCount">the time, in multiples of ddsPeriod, between successive additions of
///	deltaPhaseIncrement to the delta phase accumulator.This determines the rate at which the generator
/// sweeps the output frequency.Minimum value : PS2000A_MIN_DWELL_COUNT.</param>
/// <param name="arbitaryWaveform">A buffer that holds the waveform pattern as a set of samples equally
/// spaced in time.Each sample is scaled to an output voltage as follows:
///
///    vOUT = 1 �V *(pkToPk / 2) *(sample_value / 32767) + offsetVoltage
///
/// and clipped to the overall �2 V range of the AWG.</param>
/// <param name="arbitaryWaveformSize">the size of the arbitrary waveform buffer, in samples, in the range:
/// [minArbitraryWaveformSize, maxArbitraryWaveformSize] where minArbitraryWaveformSize and
/// maxArbitraryWaveformSize are the values returned by ps2000aSigGenArbitraryMinMaxValues.</param>
/// <param name="sweepType">, determines whether the startDeltaPhase is swept up to the stopDeltaPhase,
/// or down to it, or repeatedly swept up and down.</param>
/// <param name="operation">The type of waveform to be produced.</param>
/// <param name="indexMode">Specifies how the signal will be formed from the arbitrary waveform data.
/// Single and dual index modes are possible.</param>
/// <param name="shots">0: sweep the frequency as specified by sweeps
///	1...PS2000A_MAX_SWEEPS_SHOTS: the number of cycles of the waveform to be
/// produced after a trigger event.sweeps must be zero.
/// PS2000A_SHOT_SWEEP_TRIGGER_CONTINUOUS_RUN : start and run continuously after trigger
/// occurs(not PicoScope 2205 MSO).</param>
/// <param name="sweeps">0: produce number of cycles specified by shots
/// 1..PS2000A_MAX_SWEEPS_SHOTS: the number of times to sweep the frequency after a trigger event,
/// according to sweepType.shots must be zero.
/// PS2000A_SHOT_SWEEP_TRIGGER_CONTINUOUS_RUN: start a sweep and continue after trigger
/// occurs(not PicoScope 2205 MSO).</param>
/// <param name="triggerType">The type of trigger that will be applied to the signal generator.</param>
/// <param name="triggerSource">The source that will trigger the signal generator.
/// If a trigger source other than P2000A_SIGGEN_NONE is specified, then either shots or sweeps,
/// but not both, must be non - zero.</param>
/// <param name="extInThreshold">Trigger level, in ADC counts, for external trigger.</param>
/// <returns>
/// PICO_OK if successful
///	PICO_INVALID_HANDLE
///	PICO_NO_SIGNAL_GENERATOR
///	PICO_DRIVER_FUNCTION
///	PICO_AWG_NOT_SUPPORTED
///	PICO_SIGGEN_OFFSET_VOLTAGE
///	PICO_SIGGEN_PK_TO_PK
///	PICO_SIGGEN_OUTPUT_OVER_VOLTAGE
///	PICO_SIG_GEN_PARAM
///	PICO_SHOTS_SWEEPS_WARNING
///	PICO_WARNING_EXT_THRESHOLD_CONFLICT
///	PICO_BUSY
///	PICO_SIGGEN_WAVEFORM_SETUP_FAILED
///	PICO_NOT_RESPONDING
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aSetSigGenPropertiesArbitrary)
	(
	 	int16_t												handle,
	 	uint32_t								startDeltaPhase,
	 	uint32_t								stopDeltaPhase,
	 	uint32_t								deltaPhaseIncrement,
	 	uint32_t								dwellCount,
		PS2000A_SWEEP_TYPE					sweepType,
		uint32_t								shots,
		uint32_t								sweeps,
		PS2000A_SIGGEN_TRIG_TYPE		triggerType,
		PS2000A_SIGGEN_TRIG_SOURCE	triggerSource,
		int16_t												extInThreshold
	);

/// <summary>
/// This function reprograms the signal generator. Values can be changed while the signal
///	generator is waiting for a trigger.
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="startFrequency">The frequency that the signal generator will initially produce. See
/// #defines above.</param>
/// <param name="stopFrequency">The frequency at which the sweep reverses direction or returns to
///	the initial frequency.</param>
/// <param name="increment">The amount of frequency increase or decrease in sweep mode.</param>
/// <param name="dwellTime">The time for which the sweep stays at each frequency, in seconds.</param>
/// <param name="sweepType">whether the frequency will sweep from startFrequency to stopFrequency,
///  or in the opposite direction, or repeatedly reverse direction.</param>
/// <param name="operation">the type of waveform to be produced, specified by one of the following
///	enumerated types :
///		PS2000A_ES_OFF, normal signal generator operation specified by waveType.PS2000A_WHITENOISE,
///	  the signal generator produces white noise and ignores all settings except pkToPk and offsetVoltage.
///		PS2000A_PRBS, produces a random bitstream with a bit rate specified by the start and stop
///		frequency(not available on PicoScope 2205 MSO).</param>
/// <param name="shots">0: sweep the frequency as specified by sweeps
///	1...PS2000A_MAX_SWEEPS_SHOTS: the number of cycles of the waveform to be
/// produced after a trigger event.sweeps must be zero.
/// PS2000A_SHOT_SWEEP_TRIGGER_CONTINUOUS_RUN : start and run continuously after trigger
/// occurs(not PicoScope 2205 MSO).</param>
/// <param name="sweeps">0: produce number of cycles specified by shots
/// 1..PS2000A_MAX_SWEEPS_SHOTS: the number of times to sweep the frequency after a trigger event,
/// according to sweepType.shots must be zero.
/// PS2000A_SHOT_SWEEP_TRIGGER_CONTINUOUS_RUN: start a sweep and continue after trigger
/// occurs(not PicoScope 2205 MSO).</param>
/// <param name="triggerType">The type of trigger that will be applied to the signal generator.</param>
/// <param name="triggerSource">The source that will trigger the signal generator.
/// If a trigger source other than P2000A_SIGGEN_NONE is specified, then either shots or sweeps,
/// but not both, must be non - zero.</param>
/// <param name="extInThreshold">Trigger level, in ADC counts, for external trigger.</param>
/// <returns>
/// PICO_OK if successful
/// PICO_INVALID_HANDLE
/// PICO_NO_SIGNAL_GENERATOR
/// PICO_DRIVER_FUNCTION
/// PICO_WARNING_EXT_THRESHOLD_CONFLICT
/// PICO_SIGGEN_OFFSET_VOLTAGE
/// PICO_SIGGEN_PK_TO_PK
/// PICO_SIGGEN_OUTPUT_OVER_VOLTAGE
/// PICO_SIG_GEN_PARAM
/// PICO_SHOTS_SWEEPS_WARNING
/// PICO_WARNING_EXT_THRESHOLD_CONFLICT
/// PICO_BUSY
/// PICO_SIGGEN_WAVEFORM_SETUP_FAILED
/// PICO_NOT_RESPONDING
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps2000aSetSigGenPropertiesBuiltIn)
	(
		int16_t												handle,
		double												startFrequency,
		double												stopFrequency,
		double												increment,
		double												dwellTime,
		PS2000A_SWEEP_TYPE					sweepType,
		uint32_t								shots,
		uint32_t								sweeps,
		PS2000A_SIGGEN_TRIG_TYPE		triggerType,
		PS2000A_SIGGEN_TRIG_SOURCE	triggerSource,
		int16_t												extInThreshold
	);

/// <summary>
/// This function converts a frequency to a phase count for use with the arbitrary waveform
///  generator setup functions ps2000aSetSigGenArbitrary and ps2000aSetSigGenPropertiesArbitrary.
/// The value returned depends on the length of the buffer, the index mode passed and the device model.
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="frequency">The required AWG output frequency.</param>
/// <param name="indexMode">See AWG index modes.</param>
/// <param name="bufferLength">The number of samples in the AWG buffer.</param>
/// <param name="phase">On exit, the deltaPhase argument to be sent to the AWG setup function.</param>
/// <returns>
/// PICO_OK
///	PICO_NOT_SUPPORTED_BY_THIS_DEVICE, if the device does not have an AWG.
///	PICO_SIGGEN_FREQUENCY_OUT_OF_RANGE, if the frequency is out of range.
///	PICO_NULL_PARAMETER, if phase is a NULL pointer.
///	PICO_SIG_GEN_PARAM, if indexMode or bufferLength is out of range.
///	PICO_INVALID_HANDLE
///	PICO_DRIVER_FUNCTION
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps2000aSigGenFrequencyToPhase)
	(
	int16_t												handle,
	double												frequency,
	PS2000A_INDEX_MODE						indexMode,
	uint32_t											bufferLength,
	uint32_t										* phase
	);

/// <summary>
/// This function returns the range of possible sample values and waveform buffer sizes
/// that can be supplied to ps2000aSetSigGenArbitrary for setting up the arbitrary
/// waveform generator(AWG).These values may vary between models.
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="minArbitraryWaveformValue">On exit, the lowest sample value allowed in the
/// arbitraryWaveform buffer supplied to ps2000aSetChannelInfoSigGenArbitrary.</param>
/// <param name="maxArbitraryWaveformValue">On exit, the highest sample value allowed in the
///  arbitraryWaveform buffer supplied to ps2000aSetSigGenArbitrary.</param>
/// <param name="minArbitraryWaveformSize">On exit, the minimum value allowed for the
/// arbitraryWaveformSize argument supplied to ps2000aSetSigGenArbitrary.</param>
/// <param name="maxArbitraryWaveformSize">On exit, the maximum value allowed for the
/// arbitraryWaveformSize argument supplied to ps2000aSetSigGenArbitrary.</param>
/// <returns>
/// PICO_OK
/// PICO_NOT_SUPPORTED_BY_THIS_DEVICE, if the device does not have an arbitrary waveform generator.
/// PICO_NULL_PARAMETER, if all the parameter pointers are NULL.
/// PICO_INVALID_HANDLE
/// PICO_DRIVER_FUNCTION
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps2000aSigGenArbitraryMinMaxValues)
	(
	int16_t			handle,
	int16_t		*	minArbitraryWaveformValue,
	int16_t		*	maxArbitraryWaveformValue,
	uint32_t	* minArbitraryWaveformSize,
	uint32_t	*	maxArbitraryWaveformSize
	);

/// <summary>
/// This function causes a trigger event, or starts and stops gating. Use it as follows:
/// 1. Call ps2000aSetSigGenBuiltIn or ps2000aSetSigGenArbitrary to set up the signal generator,
/// setting the triggerSource argument to SIGGEN_SOFT_TRIG.
/// 2. (a)If you set the signal generator triggerType to edge triggering (PS2000A_SIGGEN_RISING or
/// PS2000A_SIGGEN_FALLING), call ps2000aSigGenSoftwareControl once to trigger a capture.
/// (b)If you set the signal generator triggerType to gated triggering (PS2000A_SIGGEN_GATE_HIGH
/// or PS2000A_SIGGEN_GATE_LOW), call ps2000aSigGenSoftwareControl with state set to 0 to start
/// capture, and then again with state set to 1 to stop capture.
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="state">specifies whether to start or stop capture. Effective only when the signal
/// generator triggerType is set to SIGGEN_GATE_HIGH or SIGGEN_GATE_LOW.Ignored for other trigger types.
///			0: to start capture
///			<> 0 : to stop </param>
/// <returns>
/// PICO_OK
///	PICO_INVALID_HANDLE
///	PICO_NO_SIGNAL_GENERATOR
///	PICO_SIGGEN_TRIGGER_SOURCE
///	PICO_DRIVER_FUNCTION
///	PICO_NOT_RESPONDING
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aSigGenSoftwareControl)
	(
		int16_t												handle,
		int16_t												state
	);

/// <summary>
/// This function is used to enable or disable ETS (equivalent-time sampling) and to set
///	the ETS parameters.See ETS overview for an explanation of ETS mode.
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="mode">The ETS mode.</param>
/// <param name="etsCycles">the number of cycles to store: the computer can then select etsInterleave
///  cycles to give the most uniform spread of samples.Range: between two and five times the value of
///  etsInterleave, and not more than the appropriate MAX_ETS_CYCLES constant:
///	 see #defines above.</param>
/// <param name="etsInterleave">the number of waveforms to combine into a single ETS capture.
///	see #defines above for Maximum value.</param>
/// <param name="sampleTimePicoseconds">on exit, the effective sampling interval of the ETS data.
/// For example, if the captured sample time is 4 ns and etsInterleave is 10, then the effective
/// sample time in ETS mode is 400 ps.</param>
/// <returns>
/// PICO_OK
///	PICO_USER_CALLBACK
///	PICO_INVALID_HANDLE
///	PICO_INVALID_PARAMETER
///	PICO_DRIVER_FUNCTION
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aSetEts)
  (
		int16_t												handle,
		PS2000A_ETS_MODE						mode,
		int16_t												etsCycles,
		int16_t												etsInterleave,
		int32_t											* sampleTimePicoseconds
	);

/// <summary>
/// This function simplifies arming the trigger. It supports only the LEVEL trigger types
/// and does not allow more than one channel to have a trigger applied to it.Any previous
/// pulse width qualifier is canceled.
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="enable">Zero to disable the trigger, any non-zero value to set the trigger.</param>
/// <param name="source">The channel on which to trigger.</param>
/// <param name="threshold">The ADC count at which the trigger will fire.</param>
/// <param name="direction">The direction in which the signal must move to cause a trigger.</param>
/// <param name="delay">The time between the trigger occurring and the first sample being taken.
/// For example, if delay = 100 then the scope would wait 100 sample periods before sampling.</param>
/// <param name="autoTrigger_ms">the number of milliseconds the device will wait if no trigger occurs.
/// If this is set to zero, the scope device will wait indefinitely for a trigger.</param>
/// <returns>
/// PICO_OK
///	PICO_INVALID_CHANNEL
///	PICO_INVALID_PARAMETER
///	PICO_MEMORY
///	PICO_CONDITIONS
///	PICO_INVALID_HANDLE
///	PICO_USER_CALLBACK
///	PICO_DRIVER_FUNCTION
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aSetSimpleTrigger)
	(
		int16_t handle,
		int16_t enable,
		PS2000A_CHANNEL source,
		int16_t threshold,
		PS2000A_THRESHOLD_DIRECTION direction,
		uint32_t delay,
		int16_t autoTrigger_ms
	);

/// <summary>
/// This function will set the individual Digital channels trigger directions. Each trigger
/// direction consists of a channel name and a direction.If the channel is not included in
/// the array of PS2000A_DIGITAL_CHANNEL_DIRECTIONS the driver assumes the digital
/// channel's trigger direction is PS2000A_DIGITAL_DONT_CARE.
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="directions">a pointer to an array of PS2000A_DIGITAL_CHANNEL_DIRECTIONS
/// structures describing the requested properties.The array can contain a single element
/// describing the properties of one channel, or a number of elements describing several
/// digital channels.If directions is NULL, digital triggering is switched off.A digital
/// channel that is not included in the array will be set to PS2000A_DIGITAL_DONT_CARE.</param>
/// <param name="nDirections">The number of digital channel directions being passed to the driver.</param>
/// <returns>
/// PICO_OK
/// PICO_INVALID_HANDLE
/// PICO_DRIVER_FUNCTION
/// PICO_INVALID_DIGITAL_CHANNEL
/// PICO_INVALID_DIGITAL_TRIGGER_DIRECTION
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aSetTriggerDigitalPortProperties)
(
	int16_t handle,
	PS2000A_DIGITAL_CHANNEL_DIRECTIONS * directions,
	int16_t															   nDirections
);

/// <summary>
/// Mixed-signal (MSO) models in this series have two independent triggers, one for the
/// analog input channels and another for the digital inputs.This function defines how the
/// two triggers are combined.
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="operand">How the analogue and digital triggers will interact with each other.</param>
/// <returns>
/// PICO_OK
///	PICO_INVALID_HANDLE
///	PICO_DRIVER_FUNCTION
///	PICO_NOT_USED
///	PICO_INVALID_PARAMETER
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aSetDigitalAnalogTriggerOperand)
(
	int16_t handle,
	PS2000A_TRIGGER_OPERAND operand
);

/// <summary>
/// This function will set the individual digital channels' pulse-width trigger directions.
///  Each trigger direction consists of a channel name and a direction. If the channel is not
/// included in the array of PS2000A_DIGITAL_CHANNEL_DIRECTIONS the driver assumes the digital
/// channel's pulse-width trigger direction is PS2000A_DIGITAL_DONT_CARE.
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="directions">A pointer to an array of PS2000A_DIGITAL_CHANNEL_DIRECTIONS structures
/// describing the requested properties.The array can contain a single element describing the
/// properties of one channel, or a number of elements describing several digital channels.
/// If directions is NULL, digital pulse - width triggering is switched off. A digital channel that
/// is not included in the array will be set to PS2000A_DIGITAL_DONT_CARE.</param>
/// <param name="nDirections">the number of digital channel directions being passed to the driver.</param>
/// <returns>
/// PICO_OK
///	PICO_INVALID_HANDLE
///	PICO_DRIVER_FUNCTION
///	PICO_INVALID_DIGITAL_CHANNEL
///	PICO_INVALID_DIGITAL_TRIGGER_DIRECTION
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aSetPulseWidthDigitalPortProperties)
	(
	int16_t                               handle,
	PS2000A_DIGITAL_CHANNEL_DIRECTIONS *directions,
	int16_t                               nDirections
	);


/// <summary>
/// This function is used to enable or disable triggering and set its parameters.
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="channelProperties">A pointer to an array of PS2000A_TRIGGER_CHANNEL_PROPERTIES
/// structures describing the requested properties.The array can contain a single element
///	describing the properties of one channel, or a number of elements describing several channels.
/// If NULL is passed, triggering is switched off.</param>
/// <param name="nChannelProperties">The size of the channelProperties array. If zero, triggering
/// is switched off.</param>
/// <param name="auxOutputEnable">Not used.</param>
/// <param name="autoTriggerMilliseconds">The time in milliseconds for which the scope device will
///  wait before collecting data if no trigger event occurs.If this is set to zero, the scope
///  device will wait indefinitely for a trigger.</param>
/// <returns>
/// PICO_OK
///	PICO_INVALID_HANDLE
///	PICO_USER_CALLBACK
///	PICO_TRIGGER_ERROR
///	PICO_MEMORY
///	PICO_INVALID_TRIGGER_PROPERTY
///	PICO_DRIVER_FUNCTION
///	PICO_INVALID_PARAMETER
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aSetTriggerChannelProperties)
	(
		int16_t																	handle,
		PS2000A_TRIGGER_CHANNEL_PROPERTIES	*	channelProperties,
		int16_t																	nChannelProperties,
		int16_t																	auxOutputEnable,
		int32_t																	autoTriggerMilliseconds
	);


/// <summary>
/// This function sets up trigger conditions on the scope's inputs. The trigger is defined by
/// one or more PS2000A_TRIGGER_CONDITIONS structures that are then ORed together. Each structure
///  is itself the AND of the states of one or more of the inputs.This AND - OR logic allows
/// you to create any possible Boolean function of the scope's inputs.
///
///  If complex triggering is not required, use ps2000aSetSimpleTrigger.
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="conditions">An array of PS2000A_TRIGGER_CONDITIONS structures specifying the
/// conditions that should be applied to each channel. In the simplest case, the array consists
/// of a single element.When there is more than one element, the overall trigger condition is
/// the logical OR of all the elements.</param>
/// <param name="nConditions">The number of elements in the conditions array. If nConditions is zero
/// then triggering is switched.</param>
/// <returns>
/// PICO_OK
///	PICO_INVALID_HANDLE
///	PICO_USER_CALLBACK
///	PICO_CONDITIONS
///	PICO_MEMORY
///	PICO_DRIVER_FUNCTION
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aSetTriggerChannelConditions)
	(
		int16_t													handle,
		PS2000A_TRIGGER_CONDITIONS	*	conditions,
		int16_t													nConditions
	);

/// <summary>
/// This function sets the direction of the trigger for each channel.
///
/// If using a level trigger in conjunction with a pulse - width trigger, see the
/// description of the direction argument to ps2000aSetPulseWidthQualifier for more information.
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="channelA">The direction in which the signal must pass through the threshold
/// to activate the trigger.</param>
/// <param name="channelB">The direction in which the signal must pass through the threshold
/// to activate the trigger.</param>
/// <param name="channelC">The direction in which the signal must pass through the threshold
/// to activate the trigger. Four channel variants only.</param>
/// <param name="channelD">The direction in which the signal must pass through the threshold
/// to activate the trigger. Four channel variants only.</param>
/// <param name="ext">The direction in which the signal must pass through the threshold
/// to activate the trigger.</param></param>
/// <param name="aux">Not used.</param></param>
/// <returns>
/// PICO_OK
///	PICO_INVALID_HANDLE
///	PICO_USER_CALLBACK
///	PICO_INVALID_PARAMETER
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aSetTriggerChannelDirections)
	(
		int16_t													handle,
		PS2000A_THRESHOLD_DIRECTION		channelA,
		PS2000A_THRESHOLD_DIRECTION		channelB,
		PS2000A_THRESHOLD_DIRECTION		channelC,
		PS2000A_THRESHOLD_DIRECTION		channelD,
		PS2000A_THRESHOLD_DIRECTION		ext,
		PS2000A_THRESHOLD_DIRECTION		aux
	);

/// <summary>
/// This function sets the post-trigger delay, which causes capture to start a defined time
/// after the trigger event.
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="delay">The time between the trigger occurring and the first sample. For example,
///  if delay=100 then the scope would wait 100 sample periods before sampling.At a timebase of
///  1GS/s, or 1ns per sample, the total delay would then be 100 x 1 ns = 100 ns.Range:
///			0 to MAX_DELAY_COUNT.</param>
/// <returns>
/// PICO_OK
///	PICO_INVALID_HANDLE
///	PICO_USER_CALLBACK
///	PICO_DRIVER_FUNCTION
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aSetTriggerDelay)
	(
		int16_t									handle,
		uint32_t					delay
	);

/// <summary>
/// This function sets up the conditions for pulse width qualification, which is used with
///	either threshold triggering, level triggering or window triggering to produce
/// time - qualified triggers.
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="conditions">This function sets up the conditions for pulse width qualification,
/// which is used with either threshold triggering, level triggering or window triggering to
/// produce time - qualified triggers.</param>
/// <param name="nConditions">The number of elements in the conditions array. If nConditions is
/// zero then the pulse-width qualifier is not used. Range:
///			0 to PS2000A_MAX_PULSE_WIDTH_QUALIFIER_COUNT.</param>
/// <param name="directions">the direction of the signal required for the pulse width trigger to
/// fire.See PS2000A_THRESHOLD_DIRECTION constants for the list of possible values.Each channel
/// of the oscilloscope(except the EXT input) has two thresholds for each direction�for example,
/// PS2000A_RISING and PS2000A_RISING_LOWER � so that one can be 	used for the pulse - width
/// qualifier and the other for the level trigger.The driver will not let you use the same
/// threshold for both triggers; so, for example, you cannot use PS2000A_RISING as the direction
/// argument for both ps2000aSetTriggerConditions and ps2000aSetPulseWidthQualifier at the same
/// time. There is no such restriction when using window triggers.</param>
/// <param name="lower">The lower limit of the pulse-width counter, measured in sample periods.</param>
/// <param name="upper">The upper limit of the pulse-width counter, measured in sample periods.
/// This parameter is used only when the type is set to PS2000A_PW_TYPE_IN_RANGE or
/// PS2000A_PW_TYPE_OUT_OF_RANGE.</param>
/// <param name="type">The pulse-width type.</param>
/// <returns>
///	PICO_OK
///	PICO_INVALID_HANDLE
///	PICO_USER_CALLBACK
///	PICO_DRIVER_FUNCTION
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aSetPulseWidthQualifier)
	(
		int16_t													handle,
		PS2000A_PWQ_CONDITIONS			*	conditions,
		int16_t													nConditions,
		PS2000A_THRESHOLD_DIRECTION		direction,
		uint32_t									lower,
		uint32_t									upper,
		PS2000A_PULSE_WIDTH_TYPE			type
	);

/// <summary>
/// This function discovers whether a trigger, or pulse width triggering, is enabled.
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="triggerEnabled">on exit, indicates whether the trigger will successfully
/// be set when ps2000aRunBlock or ps2000aRunStreaming is called.A non - zero value indicates
/// that the trigger is set, zero that the trigger is not set.</param>
/// <param name="pulseWidthQualifierEnabled">on exit, indicates whether the pulse width
/// qualifier will successfully be set when ps2000aRunBlock or ps2000aRunStreaming is
/// called.A non - zero value indicates that the pulse width qualifier is set, zero that
/// the pulse width qualifier is not set.</param>
/// <returns>
/// PICO_OK
///	PICO_INVALID_HANDLE
///	PICO_NULL_PARAMETER
///	PICO_DRIVER_FUNCTION
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aIsTriggerOrPulseWidthQualifierEnabled)
	(
		int16_t 								handle,
		int16_t 							* triggerEnabled,
		int16_t 							* pulseWidthQualifierEnabled
	);

/// <summary>
/// This function gets the time, as two 4-byte values, at which the trigger occurred. Call it
/// after block - mode data has been captured or when data has been retrieved from a
/// previous block - mode capture.A 64 - bit version of this function,
/// ps2000aGetTriggerTimeOffset64, is also available.
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="timeUpper">on exit, the upper 32 bits of the time at which the trigger point occurred.</param>
/// <param name="timeLower">on exit, the lower 32 bits of the time at which the trigger point occurred.</param>
/// <param name="timeUnits">returns the time units in which timeUpper and timeLower are measured.</param>
/// <param name="segmentIndex">the number of the memory segment for which the information is required.</param>
/// <returns>
/// PICO_OK
///	PICO_INVALID_HANDLE
///	PICO_DEVICE_SAMPLING
///	PICO_SEGMENT_OUT_OF_RANGE
///	PICO_NOT_USED_IN_THIS_CAPTURE_MODE
///	PICO_NOT_RESPONDING
///	PICO_NULL_PARAMETER
///	PICO_NO_SAMPLES_AVAILABLE
///	PICO_DRIVER_FUNCTION
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aGetTriggerTimeOffset)
	(
		int16_t									handle,
		uint32_t 			* timeUpper,
		uint32_t 			* timeLower,
		PS2000A_TIME_UNITS	*	timeUnits,
		uint32_t				segmentIndex
	);

/// <summary>
/// This function gets the time, as a single 64-bit value, at which the trigger occurred. Call
/// it after block - mode data has been captured or when data has been retrieved from a
/// previous block - mode capture.A 32 - bit version of this function, ps2000aGetTriggerTimeOffset,
/// is also available.
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="time">On exit, the time at which the trigger point occurred.</param>
/// <param name="timeUnits">On exit, the time units in which time is measured.</param>
/// <param name="segmentIndex">Yhe number of the memory segment for which the information is required.</param>
/// <returns>
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aGetTriggerTimeOffset64)
	(
		int16_t									handle,
		int64_t							* time,
		PS2000A_TIME_UNITS	*	timeUnits,
		uint32_t				segmentIndex
	);

/// <summary>
/// This function retrieves the time offsets, as lower and upper 32-bit values, for
/// waveforms obtained in rapid block mode.The time offset of a waveform is the delay
/// from the trigger sampling instant to the time at which the driver estimates the
///	waveform to have crossed the trigger threshold.You can add this offset to the time of
/// each sample in the waveform to reduce trigger jitter.Without using the time offset,
/// trigger jitter can be up to 1 sample period; adding the time offset reduces jitter to a
/// small fraction of a sample period.This function is provided for use in programming
/// environments that do not support 64 - bit integers.If your programming environment
/// supports this data type, it is easier to use ps2000aGetValuesTriggerTimeOffsetBulk64.
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="timeUpper">An array of integers. On exit, the most significant 32
///	bits of the time offset for each requested segment index.times[0] will hold the
/// fromSegmentIndex time offset and the last times index will hold the toSegmentIndex
/// time offset.The array must be long enough to hold the number of requested times.</param>
/// <param name="timeLower">An array of integers. On exit, the least significant 32 bits
/// of the time offset for each requested segment index.times[0] will hold the
/// fromSegmentIndex time offset and the last times index will hold the toSegmentIndex
/// time offset.The array size must be long enough to hold the number of requested times.</param>
/// <param name="timeUnits">An array of integers. The array must be long enough to hold
/// the number of requested times.On exit, timeUnits[0] will contain the time unit for
/// fromSegmentIndex and the last element will contain the time unit for toSegmentIndex.
/// Refer to ps2000aGetTriggerTimeOffset for allowable values.</param>
/// <param name="fromSegmentIndex">The first segment for which the time offset is required</param>
/// <param name="toSegmentIndex">The last segment for which the time offset is required.
/// If toSegmentIndex is less than fromSegmentIndex then the driver will wrap around
/// from the last segment to the first.</param>
/// <returns>
/// PICO_OK
///	PICO_INVALID_HANDLE
///	PICO_NOT_USED_IN_THIS_CAPTURE_MODE
///	PICO_NOT_RESPONDING
///	PICO_NULL_PARAMETER
///	PICO_DEVICE_SAMPLING
///	PICO_SEGMENT_OUT_OF_RANGE
///	PICO_NO_SAMPLES_AVAILABLE
///	PICO_DRIVER_FUNCTION
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aGetValuesTriggerTimeOffsetBulk)
	(
	  int16_t									handle,
		uint32_t				*	timesUpper,
		uint32_t				* timesLower,
		PS2000A_TIME_UNITS	*	timeUnits,
		uint32_t				fromSegmentIndex,
		uint32_t				toSegmentIndex
	);

/// <summary>
/// This function retrieves the 64-bit time offsets for waveforms captured in rapid block mode.
/// A 32 - bit version of this function, ps2000aGetValuesTriggerTimeOffsetBulk, is available
/// for use with programming languages that do not support 64 - bit integers.
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="times">an array of integers. On exit, this will hold the time offset
///	for each requested segment index.times[0] will hold the time offset for fromSegmentIndex,
/// and the last times index will hold the time offset for toSegmentIndex.The array must be
/// long enough to hold the number of times requested.</param>
/// <param name="timeUnits">an array of integers long enough to hold the number of requested
/// times.timeUnits[0] will contain the time unit for fromSegmentIndex, and the last element
/// will contain the toSegmentIndex. Refer to ps2000aGetTriggerTimeOffset64 for specific
/// figures.</param>
/// <param name="fromSegmentIndex">the first segment for which the time offset is required.
/// The results for this segment will be placed in times[0] and timeUnits[0].</param>
/// <param name="toSegmentIndex">the last segment for which the time offset is required.
/// The results for this segment will be placed in the last elements of the times and
/// timeUnits arrays.If toSegmentIndex is less than fromSegmentIndex then the driver
/// will wrap around from the last segment to the first.</param>
/// <returns>
/// PICO_OK
///	PICO_INVALID_HANDLE
///	PICO_NOT_USED_IN_THIS_CAPTURE_MODE
///	PICO_NOT_RESPONDING
///	PICO_NULL_PARAMETER
///	PICO_DEVICE_SAMPLING
///	PICO_SEGMENT_OUT_OF_RANGE
///	PICO_NO_SAMPLES_AVAILABLE
///	PICO_DRIVER_FUNCTION
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aGetValuesTriggerTimeOffsetBulk64)
	(
	  int16_t									handle,
		int64_t							*	times,
		PS2000A_TIME_UNITS	*	timeUnits,
		uint32_t				fromSegmentIndex,
		uint32_t				toSegmentIndex
	);

/// <summary>
/// This function sets the number of captures to be collected in one run of rapid block
/// mode. If you do not call this function before a run, the driver will capture only one
/// waveform. Once a value has been set, the value remains constant unless changed.
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="">the number of waveforms to capture in one run.</param>
/// <returns>
/// PICO_OK
///	PICO_INVALID_HANDLE
///	PICO_INVALID_PARAMETER
///	PICO_DRIVER_FUNCTION
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aGetNoOfCaptures)
	(
	  int16_t								handle,
		uint32_t			*	nCaptures
	);

/// <summary>
/// This function finds out how many captures in rapid block mode have been processed
///	after ps2000aRunBlock has been called when either the collection completed or the
///	collection of waveforms was interrupted by calling ps2000aStop.The returned value
///	(nCaptures) can then be used to iterate through the number of segments using
///	ps2000aGetValues, or in a single call to ps2000aGetValuesBulk where it is used to
///	calculate the toSegmentIndex parameter.
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="nProcessedCaptures">Output: the number of available captures that has
///	been collected from calling ps2000aRunBlock.</param>
/// <returns>
/// PICO_OK
///	PICO_DRIVER_FUNCTION
///	PICO_INVALID_HANDLE
///	PICO_NO_SAMPLES_AVAILABLE
///	PICO_NULL_PARAMETER
///	PICO_INVALID_PARAMETER
///	PICO_SEGMENT_OUT_OF_RANGE
///	PICO_TOO_MANY_SAMPLES
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aGetNoOfProcessedCaptures)
	(
	  int16_t								handle,
		uint32_t			*	nProcessedCaptures
	);

/// <summary>
/// This function tells the driver where to store the data, either unprocessed or
///	downsampled, that will be returned after the next call to one of the GetValues
///	functions.The function allows you to specify only a single buffer, so for aggregation
///	mode, which requires two buffers, you need to call ps2000aSetDataBuffers instead.
///
/// You must allocate memory for the buffer before calling this function.
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="channelOrPort">The analogue channel you want to use with the buffer.
/// To set the buffer for a digital port (MSO models only), use one of these values :
///			PS2000A_DIGITAL_PORT0 = 0x80
///			PS2000A_DIGITAL_PORT1 = 0x81</param>
/// <param name="buffer">The location of the buffer.</param>
/// <param name="bufferLth">The size of the buffer array.</param>
/// <param name="segmentIndex">The number of the memory segment to be used.</param>
/// <param name="mode">The downsampling mode. See PS2000A_RATIO_MODE for the available modes.</param>
/// <returns>
/// PICO_OK
///	PICO_INVALID_HANDLE
///	PICO_INVALID_CHANNEL
///	PICO_RATIO_MODE_NOT_SUPPORTED
///	PICO_SEGMENT_OUT_OF_RANGE
///	PICO_DRIVER_FUNCTION
///	PICO_INVALID_PARAMETER
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aSetDataBuffer)
(
   int16_t								 handle,
	 int32_t						 			 channelOrPort,
	 int16_t							*  buffer,
   int32_t									 bufferLth,
	 uint32_t				 segmentIndex,
	 PS2000A_RATIO_MODE		 mode
);

/// <summary>
/// This function tells the driver the location of one or two buffers for receiving data. You
///	need to allocate memory for the buffers before calling this function.If you do not need
///	two buffers, because you are not using aggregate mode, you can optionally use
///	ps2000aSetDataBuffer instead.
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="channelOrPort">The analogue channel you want to use with the buffer.
/// To set the buffer for a digital port (MSO models only), use one of these values :
///			PS2000A_DIGITAL_PORT0 = 0x80
///			PS2000A_DIGITAL_PORT1 = 0x81</param>
/// <param name="bufferMax">A buffer to receive the maximum data values in aggregation mode,
/// or the non - aggregated values otherwise.</param>
/// <param name="bufferMin">A buffer to receive the minimum aggregated data values. Not used
/// in other downsampling modes.</param>
/// <param name="bufferLth">The size of the buffer array.</param>
/// <param name="segmentIndex">The number of the memory segment to be used.</param>
/// <param name="mode">The downsampling mode. See PS2000A_RATIO_MODE for the available modes.</param>
/// <returns>
/// PICO_OK
///	PICO_INVALID_HANDLE
///	PICO_INVALID_CHANNEL
///	PICO_RATIO_MODE_NOT_SUPPORTED
///	PICO_SEGMENT_OUT_OF_RANGE
///	PICO_DRIVER_FUNCTION
///	PICO_INVALID_PARAMETER
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aSetDataBuffers)
(
   int16_t								 handle,
	 int32_t						 			 channelOrPort,
	 int16_t							 * bufferMax,
	 int16_t							 * bufferMin,
   int32_t									 bufferLth,
	 uint32_t				 segmentIndex,
	 PS2000A_RATIO_MODE		 mode
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps2000aSetUnscaledDataBuffers)
(
	int16_t               handle,
	PS2000A_CHANNEL     channelOrPort,
	int8_t              *bufferMax,
	int8_t              *bufferMin,
	int32_t                bufferLth,
	uint32_t      segmentIndex,
	PS2000A_RATIO_MODE  mode
);
/// <summary>
/// This function tells the driver where to find your application's ETS time buffers. These
///	buffers contain the 64 - bit timing information for each ETS sample after you run a
///	block - mode ETS capture.
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="buffer">An array of 64-bit words, each representing the time in
/// femtoseconds(10^-15s) at which the sample was captured.</param>
/// <param name="bufferLth">The size of the buffer array.</param>
/// <returns>
/// PICO_OK
/// PICO_INVALID_HANDLE
/// PICO_NULL_PARAMETER
/// PICO_DRIVER_FUNCTION
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aSetEtsTimeBuffer)
(
   int16_t									handle,
	 int64_t *							buffer,
	 int32_t										bufferLth
);

/// <summary>
/// This function tells the driver where to find your application's ETS time buffers. These
/// buffers contain the timing information for each ETS sample after you run a block - mode
///	ETS capture.There are two buffers containing the upper and lower 32 - bit parts of the
///	timing information, to allow programming languages that do not support 64 - bit data to
///	retrieve the timings.

/// If your programming language supports 64 - bit data then you can use ps2000aSetEtsTimeBuffer
/// instead.
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="timeUpper">An array of 32-bit words, each representing the upper
/// 32 bits of the time in femtoseconds(10^�15s) at which the sample was captured.</param>
/// <param name="timeLower">An array of 32-bit words, each representing the lower
///	32 bits of the time in femtoseconds(10^�15s) at which the sample was captured.</param>
/// <param name="bufferLth">The size of the timeUpper and timeLower arrays.</param>
/// <returns>
/// PICO_OK
///	PICO_INVALID_HANDLE
///	PICO_NULL_PARAMETER
///	PICO_DRIVER_FUNCTION
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aSetEtsTimeBuffers)
(
   int16_t									handle,
	 uint32_t				* timeUpper,
	 uint32_t				* timeLower,
	 int32_t										bufferLth
);

/// <summary>
/// This function may be used instead of a callback function to receive data from
///	ps2000aRunBlock.To use this method, pass a NULL pointer as the lpReady argument
///	to ps2000aRunBlock.You must then poll the driver to see if it has finished collecting
///	the requested samples.
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="ready">Output: indicates the state of the collection. If zero, the
///	device is still collecting.If non - zero, the device has finished collecting and
/// ps2000aGetValues can be used to retrieve the data.</param>
/// <returns>
/// PICO_OK
///	PICO_INVALID_HANDLE
///	PICO_DRIVER_FUNCTION
///	PICO_NULL_PARAMETER
///	PICO_NO_SAMPLES_AVAILABLE
///	PICO_CANCELLED
///	PICO_NOT_RESPONDING
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aIsReady)
	(
		int16_t handle,
		int16_t * ready
	);

/// <summary>
/// This function starts collecting data in block mode. For a step-by-step guide to this
///	process, see Using block mode.The number of samples is determined by noOfPreTriggerSamples
///	and noOfPostTriggerSamples(see below for details).The total number of samples must
///	not be more than the size of the segment referred to by segmentIndex.
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="noOfPreTriggerSamples">The number of samples to store before the trigger event.</param>
/// <param name="noOfPostTriggerSamples">The number of samples to store after the trigger event.
///			Note: the maximum number of samples returned is always noOfPreTriggerSamples +
///			noOfPostTriggerSamples. This is true even if no trigger event has been set.</param>
/// <param name="timebase">A number in the range 0 to 2 32�1.See the guide to calculating timebase
/// values.This argument is ignore.</param>
/// <param name="oversample">Not used.</param>
/// <param name="timeIndisposedMs">On exit, the time, in milliseconds, that the scope will spend
/// collecting samples.This does not include any auto trigger timeout. It is not valid in ETS
/// capture mode.The pointer can be set to null if a value is not required.</param>
/// <param name="segmentIndex">Zero-based, which memory segment to use.</param>
/// <param name="lpReady">A pointer to the ps2000aBlockReady callback function that the driver
/// will call when the data has been collected.To use the ps2000aIsReady polling method instead
/// of a callback function, set this pointer to NULL.</param>
/// <param name="pParameter">a void pointer that is passed to the ps2000aBlockReady callback
/// function.The callback can use this pointer to return arbitrary data to the application.</param>
/// <returns>
/// PICO_OK
///	PICO_BUFFERS_NOT_SET(in Overlapped mode)
///	PICO_INVALID_HANDLE
///	PICO_USER_CALLBACK
///	PICO_SEGMENT_OUT_OF_RANGE
///	PICO_INVALID_CHANNEL
///	PICO_INVALID_TRIGGER_CHANNEL
///	PICO_INVALID_CONDITION_CHANNEL
///	PICO_TOO_MANY_SAMPLES
///	PICO_INVALID_TIMEBASE
///	PICO_NOT_RESPONDING
///	PICO_CONFIG_FAIL
///	PICO_INVALID_PARAMETER
///	PICO_NOT_RESPONDING
///	PICO_TRIGGER_ERROR
///	PICO_DRIVER_FUNCTION
///	PICO_FW_FAIL
///	PICO_NOT_ENOUGH_SEGMENTS(in Bulk mode)
///	PICO_PULSE_WIDTH_QUALIFIER
///	PICO_SEGMENT_OUT_OF_RANGE(in Overlapped mode)
///	PICO_STARTINDEX_INVALID(in Overlapped mode)
///	PICO_INVALID_SAMPLERATIO(in Overlapped mode)
///	PICO_CONFIG_FAIL
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aRunBlock)
	(
		int16_t									handle,
		int32_t									noOfPreTriggerSamples,
		int32_t									noOfPostTriggerSamples,
		uint32_t					timebase,
		int16_t									oversample,
		int32_t								* timeIndisposedMs,
		uint32_t				segmentIndex,
		ps2000aBlockReady			lpReady,
		void								* pParameter
	);

/// <summary>
/// This function tells the oscilloscope to start collecting data in streaming mode. When
///	data has been collected from the device it is downsampled if necessary and then
///	delivered to the application.Call ps2000aGetStreamingLatestValues to retrieve the
///	data. See Using streaming mode for a step - by - step guide to this process.When a
/// trigger is set, the total number of samples stored in the driver is the sum of
/// maxPreTriggerSamples and maxPostTriggerSamples.If autoStop is false, this will
///	become the maximum number of samples without downsampling.
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="sampleInterval">On entry, the requested time interval between samples; on exit, the actual
/// time interval used.</param>
/// <param name="sampleIntervalTimeUnits">The maximum number of raw samples before a trigger event for each enabled
/// channel.If no trigger condition is set this argument is ignored.</param>
/// <param name="maxPreTriggerSamples">The maximum number of raw samples after a trigger event for each enabled channel.
/// If no trigger condition is set, this argument states the maximum number of samples to be stored.</param>
/// <param name="maxPostPreTriggerSamples">A flag that specifies if the streaming should stop when all of maxSamples
/// have been captured.</param>
/// <param name="autoStop">A flag that specifies if the streaming should stop when all of maxSamples have
/// been captured.</param>
/// <param name="downSampleRatio">The downsampling factor that will be applied to the raw data.</param>
/// <param name="downSampleRatioMode">See PS2000A_RATIO_MODE for available modes.</param>
/// <param name="overviewBufferSize">The size of the overview buffers. These are temporary buffers used for storing
/// the data before returning it to the application.The size is the same as the bufferLth value passed
/// to ps2000aSetDataBuffer.</param>
/// <returns>
/// PICO_OK
///	PICO_INVALID_HANDLE
///	PICO_ETS_MODE_SET
///	PICO_USER_CALLBACK
///	PICO_NULL_PARAMETER
///	PICO_INVALID_PARAMETER
///	PICO_STREAMING_FAILED
///	PICO_NOT_RESPONDING
///	PICO_TRIGGER_ERROR
///	PICO_INVALID_SAMPLE_INTERVAL
///	PICO_INVALID_BUFFER
///	PICO_DRIVER_FUNCTION
///	PICO_FW_FAIL
///	PICO_MEMORY
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aRunStreaming)
  (
	  int16_t									handle,
		uint32_t				* sampleInterval,
		PS2000A_TIME_UNITS		sampleIntervalTimeUnits,
	  uint32_t					maxPreTriggerSamples,
	  uint32_t					maxPostPreTriggerSamples,
		int16_t									autoStop,
		uint32_t					downSampleRatio,
		PS2000A_RATIO_MODE		downSampleRatioMode,
    uint32_t					overviewBufferSize
	);

/// <summary>
/// This function instructs the driver to return the next block of values to your
///	ps2000aStreamingReady callback function.You must have previously called
///	ps2000aRunStreaming beforehand to set up streaming.
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="lpPs2000aReady">a pointer to your ps2000aStreamingReady callback function.</param>
/// <param name="pParameter">a void pointer that will be passed to the ps2000aStreamingReady
/// callback function.The callback function may optionally use this pointer to return
/// information to the application.</param>
/// <returns>
/// PICO_OK
///	PICO_INVALID_HANDLE
///	PICO_NO_SAMPLES_AVAILABLE
///	PICO_INVALID_CALL
///	PICO_BUSY
///	PICO_NOT_RESPONDING
///	PICO_DRIVER_FUNCTION
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aGetStreamingLatestValues)
  (
    int16_t									handle,
    ps2000aStreamingReady	lpPs2000aReady,
		void								* pParameter
  );

/// <summary>
/// This function returns the number of samples available after data collection in
///	streaming mode.Call it after calling ps2000aStop.
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="noOfValues">On exit, the number of samples.</param>
/// <returns>
/// PICO_OK
///	PICO_INVALID_HANDLE
///	PICO_NULL_PARAMETER
///	PICO_NO_SAMPLES_AVAILABLE
///	PICO_NOT_USED
///	PICO_BUSY
///	PICO_DRIVER_FUNCTION
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aNoOfStreamingValues)
	(
	  int16_t								handle,
		uint32_t			*	noOfValues
	);

/// <summary>
/// This function returns the maximum downsampling ratio that can be used for a given
///	number of samples in a given downsampling mode
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="noOfUnaggreatedSamples">The number of unprocessed samples to be downsampled.</param>
/// <param name="maxDownSampleRatio">The maximum possible downsampling ratio output.</param>
/// <param name="downSampleRatioMode">See PS2000A_RATIO_MODE available modes.</param>
/// <param name="segmentIndex">The memory segment where the data is stored.</param>
/// <returns>
/// PICO_OK
///	PICO_INVALID_HANDLE
///	PICO_NO_SAMPLES_AVAILABLE
///	PICO_NULL_PARAMETER
///	PICO_INVALID_PARAMETER
///	PICO_SEGMENT_OUT_OF_RANGE
///	PICO_TOO_MANY_SAMPLES
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aGetMaxDownSampleRatio)
	(
	  int16_t								handle,
		uint32_t 			noOfUnaggreatedSamples,
		uint32_t 		* maxDownSampleRatio,
		PS2000A_RATIO_MODE	downSampleRatioMode,
		uint32_t			segmentIndex
	);

/// <summary>
/// This function returns block-mode data, with or without downsampling, starting at the
///	specified sample number.It is used to get the stored data from the driver after data
///	collection has stopped.
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="startIndex">A zero-based index that indicates the start point for
///	data collection.It is measured in sample intervals from the start of the buffer.</param>
/// <param name="noOfSamples">On entry, the number of samples required. On exit,
/// the actual number retrieved. The number of samples retrieved will not be more than the
/// number requested, and the data retrieved starts at startIndex.</param>
/// <param name="downSampleRatio">The downsampling factor that will be applied to the raw data.</param>
/// <param name="downSampleRatioMode">Downsampling mode to use. The available values are :
///			PS2000A_RATIO_MODE_NONE(downSampleRatio is ignored)
///			PS2000A_RATIO_MODE_AGGREGATE
///			PS2000A_RATIO_MODE_AVERAGE
///			PS2000A_RATIO_MODE_DECIMATE
///	AGGREGATE, AVERAGE, DECIMATE are single - bit constants that can be ORed to apply multiple
/// downsampling modes to the same data.</param>
/// <param name="segmentIndex">The zero-based number of the memory segment 	where the data is stored.</param>
/// <param name="overflow">On exit, a set of flags that indicate whether an overvoltage has occurred
/// on any of the channels.It is a bit field with bit 0 denoting Channel.</param>
/// <returns>
/// PICO_OK
///	PICO_INVALID_HANDLE
///	PICO_NO_SAMPLES_AVAILABLE
///	PICO_DEVICE_SAMPLING
///	PICO_NULL_PARAMETER
///	PICO_SEGMENT_OUT_OF_RANGE
///	PICO_STARTINDEX_INVALID
///	PICO_ETS_NOT_RUNNING
///	PICO_BUFFERS_NOT_SET
///	PICO_INVALID_PARAMETER
///	PICO_TOO_MANY_SAMPLES
///	PICO_DATA_NOT_AVAILABLE
///	PICO_STARTINDEX_INVALID
///	PICO_INVALID_SAMPLERATIO
///	PICO_INVALID_CALL
///	PICO_NOT_RESPONDING
///	PICO_MEMORY
///	PICO_RATIO_MODE_NOT_SUPPORTED
///	PICO_DRIVER_FUNCTION
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aGetValues)
	(
	  int16_t								handle,
		uint32_t 			startIndex,
	  uint32_t			*	noOfSamples,
	  uint32_t				downSampleRatio,
		PS2000A_RATIO_MODE	downSampleRatioMode,
		uint32_t			segmentIndex,
		int16_t							* overflow
	);

/// <summary>
/// This function retrieves waveforms captured using rapid block mode. The waveforms
///	must have been collected sequentially and in the same run.
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="noOfSamples">On entry, the number of samples required; on exit, the actual
///  number retrieved. The number of samples retrieved will not be more than the number
///  requested.The data retrieved always starts with the first sample captured.</param>
/// <param name="fromSegmentIndex">The first segment from which the waveform should be retrieved.</param>
/// <param name="toSegmentIndex">The last segment from which the waveform should be retrieved.</param>
/// <param name="downSampleRatio">The downsampling factor that will be applied to the raw data.</param>
/// <param name="downSampleRatioMode">See PS2000A_RATIO_MODE for available modes.</param>
/// <param name="overflow">An array of integers equal to or larger than the number of waveforms to
/// be retrieved.Each segment index has a corresponding entry in the overflow array, with overflow[0]
/// containing the flags for the segment numbered fromSegmentIndex and the last element in the
/// array containing the flags for the segment numbered toSegmentIndex. Each element in the array
/// is a bit field.</param>
/// <returns>
/// PICO_OK
///	PICO_INVALID_HANDLE
///	PICO_INVALID_PARAMETER
///	PICO_INVALID_SAMPLERATIO
///	PICO_ETS_NOT_RUNNING
///	PICO_BUFFERS_NOT_SET
///	PICO_TOO_MANY_SAMPLES
///	PICO_SEGMENT_OUT_OF_RANGE
///	PICO_NO_SAMPLES_AVAILABLE
///	PICO_NOT_RESPONDING
///	PICO_DRIVER_FUNCTION
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aGetValuesBulk)
	(
	  int16_t								handle,
		uint32_t			*	noOfSamples,
		uint32_t			fromSegmentIndex,
		uint32_t			toSegmentIndex,
	  uint32_t				downSampleRatio,
		PS2000A_RATIO_MODE 	downSampleRatioMode,
		int16_t							* overflow
	);

/// <summary>
/// This function returns data either with or without downsampling, starting at the
/// specified sample number.It is used to get the stored data from the scope after data
/// collection has stopped.It returns the data using a callback.
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="startIndex">A zero-based index that indicates the start point for data collection.
/// It is measured in sample intervals from the start of the buffer.</param>
/// <param name="noOfSamples">On entry, the number of samples required. On exit, the actual number
/// retrieved. The number of samples retrieved will not be more than the number requested, and the
/// data retrieved starts at startIndex.</param>
/// <param name="downSampleRatio">See The downsampling factor that will be applied to the raw data.</param>
/// <param name="downSampleRatioMode">See PS2000A_RATIO_MODE fro available modes.</param>
/// <param name="segmentIndex">The zero-based number of the memory segment where the data is stored.</param>
/// <param name="lpDataReady">A pointer to the user-supplied function that will be
///	called when the data is ready.This will be a ps2000aDataReady function for
/// block - mode data or a ps2000aStreamingReady function for streaming - mode data.</param>
/// <param name="pParameter">a void pointer that will be passed to the callback function.The
/// data type is determined by the application.</param>
/// <returns>
/// PICO_OK
///	PICO_INVALID_HANDLE
///	PICO_NO_SAMPLES_AVAILABLE
///	PICO_DEVICE_SAMPLING
///	PICO_NULL_PARAMETER
///	PICO_STARTINDEX_INVALID
///	PICO_SEGMENT_OUT_OF_RANGE
///	PICO_INVALID_PARAMETER
///	PICO_DATA_NOT_AVAILABLE
///	PICO_INVALID_SAMPLERATIO
///	PICO_INVALID_CALL
///	PICO_DRIVER_FUNCTION
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aGetValuesAsync)
	(
	  int16_t								handle,
		uint32_t				startIndex,
	  uint32_t				noOfSamples,
	  uint32_t				downSampleRatio,
		PS2000A_RATIO_MODE		downSampleRatioMode,
		uint32_t			segmentIndex,
	  void							*	lpDataReady,
		void							*	pParameter
	);

/// <summary>
/// This function allows you to make a deferred data-collection request in block mode. The
///	request will be executed, and the arguments validated, when you call
///	ps2000aRunBlock.The advantage of this function is that the driver makes contact with
///	the scope only once, when you call ps2000aRunBlock, compared with the two contacts
///	that occur when you use the conventional ps2000aRunBlock, ps2000aGetValues
///	calling sequence.This slightly reduces the dead time between successive captures in
///	block mode.
///
/// After calling ps2000aRunBlock, you can optionally use ps2000aGetValues to request
///	further copies of the data.This might be required if you wish to display the data with
///	different data reduction settings.
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="startIndex">A zero-based index that indicates the start point for data
/// collection.It is measured in sample intervals from the start of the buffer</param>
/// <param name="noOfSamples">n entry, the number of raw samples to be collected before any
/// downsampling is applied.On exit, the actual number stored in the buffer.The number of
/// samples retrieved will not be more than the number requested, and the data retrieved
/// starts at startIndex.</param>
/// <param name="downSampleRatio">The downsampling factor that will be applied to the raw data.</param>
/// <param name="downSampleRatioMode">See PS2000A_RATIO_MODE for available modes.</param>
/// <param name="segmentIndex">The zero-based number of the memory segment where the data is stored.</param>
/// <param name="overflow">An array of integers equal to or larger than the number of waveforms to
/// be retrieved.Each segment index has a corresponding entry in the overflow array, with overflow[0]
///	containing the flags for the segment numbered fromSegmentIndex and the last element in the array
/// containing the flags for the segment numbered toSegmentIndex.Each element in the array is a bit field</param>
/// <returns>
/// PICO_OK
///	PICO_INVALID_HANDLE
///	PICO_INVALID_PARAMETER
///	PICO_DRIVER_FUNCTION
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aGetValuesOverlapped)
	(
	  int16_t								handle,
	  uint32_t 			startIndex,
	  uint32_t			*	noOfSamples,
	  uint32_t				downSampleRatio,
	  PS2000A_RATIO_MODE	downSampleRatioMode,
		uint32_t      segmentIndex,
	  int16_t				*       overflow
	);


/// <summary>
/// This function allows you to make a deferred data-collection request, which will later be
///	executed, and the arguments validated, when you call ps2000aRunBlock in rapid block
///	mode.The advantage of this method is that the driver makes contact with the scope
///	only once, when you call ps2000aRunBlock, compared with the two contacts that occur
///	when you use the conventional ps2000aRunBlock, ps2000aGetValuesBulk calling
///	sequence.This slightly reduces the dead time between successive captures in rapid
///	block mode.
///
/// After calling ps2000aRunBlock, you can optionally use ps2000aGetValues to request
///	further copies of the data.This might be required if you wish to display the data with
///	different data reduction settings.
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="startIndex">A zero-based index that indicates the start point for data
/// collection.It is measured in sample intervals from the start of the buffer</param>
/// <param name="noOfSamples">On entry, the number of samples required; on exit, the actual
///  number retrieved. The number of samples retrieved will not be more than the number
///  requested.The data retrieved always starts with the first sample captured.</param>
/// <param name="downSampleRatio">The downsampling factor that will be applied to the raw data.</param>
/// <param name="downSampleRatioMode">See PS2000A_RATIO_MODE for available modes.</param>
/// <param name="fromSegmentIndex">The first segment from which the waveform should be retrieved.</param>
/// <param name="toSegmentIndex">The last segment from which the waveform should be retrieved.</param>
/// <param name="overflow">An array of integers equal to or larger than the number of waveforms to
/// be retrieved.Each segment index has a corresponding entry in the overflow array, with overflow[0]
/// containing the flags for the segment numbered fromSegmentIndex and the last element in the
/// array containing the flags for the segment numbered toSegmentIndex. Each element in the array
/// is a bit field.</param>
/// <returns>
/// PICO_OK
///	PICO_INVALID_HANDLE
///	PICO_INVALID_PARAMETER
///	PICO_DRIVER_FUNCTION
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aGetValuesOverlappedBulk)
	(
	  int16_t								handle,
		uint32_t				startIndex,
  	uint32_t 	 	*	noOfSamples,
	  uint32_t				downSampleRatio,
	  PS2000A_RATIO_MODE	downSampleRatioMode,
	  uint32_t			fromSegmentIndex,
	  uint32_t			toSegmentIndex,
	  int16_t							*	overflow
	);

/// <summary>
/// This function stops the scope device from sampling data. If this function is called
/// before a trigger event occurs, the oscilloscope may not contain valid data. Always
/// call this function after the end of a capture to ensure that the scope is ready
///	for the next capture.
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <returns>
/// PICO_OK
///	PICO_INVALID_HANDLE
///	PICO_USER_CALLBACK
///	PICO_DRIVER_FUNCTION
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aStop)
	(
	  int16_t handle
	);

/// <summary>
/// This function has no effect and is reserved for future use.
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="holdoff">Reserved for future use.</param>
/// <param name="type">Reserved for future use.</param>
/// <returns>
/// PICO_OK
///	PICO_INVALID_HANDLE
///	PICO_NULL_PARAMETER
///	PICO_NO_SAMPLES_AVAILABLE
///	PICO_NOT_USED
///	PICO_BUSY
///	PICO_DRIVER_FUNCTION
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aHoldOff)
	(
	  int16_t								handle,
		uint64_t						holdoff,
		PS2000A_HOLDOFF_TYPE	type
	);

/// <summary>
/// This function queries which ranges are available on a scope device.
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="info">The type of information required.
///  The following value iscurrently supported : PS2000A_CI_RANGES</param>
/// <param name="probe">Not used, must be set to 0.</param>
/// <param name="ranges">An array that will be populated with available PS2000A_RANGE
/// values for the given info.If NULL, length is set tothe number of ranges available.</param>
/// <param name="length">Input: length of ranges array; output: number of elements
///  written to ranges.</param>
/// <param name="channels">The channel for which the information is required.</param>
/// <returns>
/// PICO_OK
///	PICO_HANDLE_INVALID
///	PICO_BUSY
///	PICO_DRIVER_FUNCTION
///	PICO_NOT_RESPONDING
///	PICO_NULL_PARAMETER
///	PICO_INVALID_CHANNEL
///	PICO_INVALID_INFO
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aGetChannelInformation)
	(
		int16_t handle,
		PS2000A_CHANNEL_INFO info,
		int32_t probe,
		int32_t * ranges,
		int32_t * length,
		int32_t channels
  );

/// <summary>
/// This function counts the number of PicoScope 2000 Series (A API) units connected to
///	the computer, and returns a list of serial numbers as a string.
/// </summary>
/// <param name="count">On exit, the number of ps2000a units found.</param>
/// <param name="serials">On exit, a list of serial numbers separated by commas and terminated
/// by a final null.
///
///				Example: AQ005 / 139, VDR61 / 356, ZOR14 / 107
///
/// Can be NULL on entry if serial numbers are not required.</param>
/// <param name="serialLth">On entry, the length of the char buffer pointed to by serials;
/// on exit, the length of the string written to serials.</param>
/// <returns>
/// PICO_OK
///	PICO_BUSY
///	PICO_NULL_PARAMETER
///	PICO_FW_FAIL
///	PICO_CONFIG_FAIL
///	PICO_MEMORY_FAIL
///	PICO_CONFIG_FAIL_AWG
///	PICO_INITIALISE_FPGA
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aEnumerateUnits)
	(
	int16_t * count,
	int8_t * serials,
	int16_t * serialLth
	);

/// <summary>
/// This function can be used to check that the already opened device is still connected to
///	the USB port and communication is successful.
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <returns>
/// PICO_OK
///	PICO_INVALID_HANDLE
///	PICO_DRIVER_FUNCTION
///	PICO_BUSY
///	PICO_NOT_RESPONDING
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aPingUnit)
	(
	int16_t handle
	);

/// <summary>
/// This function returns the maximum ADC count returned by calls to the "GetValues"
///	functions.
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="value">Output: the maximum ADC value.</param>
/// <returns>
/// PICO_OK
///	PICO_USER_CALLBACK
///	PICO_INVALID_HANDLE
///	PICO_TOO_MANY_SEGMENTS
///	PICO_MEMORY
///	PICO_DRIVER_FUNCTION
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aMaximumValue)
	(
	int16_t		handle,
	int16_t * value
	);

/// <summary>
/// This function returns the minimum ADC count returned by calls to the GetValues
///	functions
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="value">Output: the minimum ADC value.</param>
/// <returns>
/// PICO_OK
///	PICO_USER_CALLBACK
///	PICO_INVALID_HANDLE
///	PICO_TOO_MANY_SEGMENTS
///	PICO_MEMORY
///	PICO_DRIVER_FUNCTION
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aMinimumValue)
	(
	int16_t		handle,
	int16_t * value
	);

/// <summary>
/// This function is used to get the maximum and minimum allowable analog offset for a
///	specific voltage range.
///
///	If both maximumVoltage and minimumVoltage are NULL, the driver will return PICO_NULL_PARAMETER
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="range">The voltage range to be used when gathering the min and max information.</param>
/// <param name="coupling">The type of AC/DC coupling used</param>
/// <param name="maximumVoltage">Output: maximum voltage allowed for the range. Pointer will be
/// ignored if NULL.If device does not support analog offset, zero will be returned.</param>
/// <param name="minimumVoltage">Output: minimum voltage allowed for the range. Pointer will
/// be ignored if NULL. If device does not support analog offset, zero will be returned.</param>
/// <returns>
/// PICO_OK
///	PICO_INVALID_HANDLE
///	PICO_DRIVER_FUNCTION
///	PICO_INVALID_VOLTAGE_RANGE
///	PICO_NULL_PARAMETER
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aGetAnalogueOffset)
	(
	int16_t handle,
	PS2000A_RANGE range,
	PS2000A_COUPLING	coupling,
	float * maximumVoltage,
	float * minimumVoltage
	);

/// <summary>
/// This function returns the maximum number of segments allowed for the opened
///	variant.Refer to ps2000aMemorySegments for specific figures.
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="maxSegments">Output: maximum number of segments allowed.</param>
/// <returns>
/// PICO_OK
///	PICO_INVALID_HANDLE
///	PICO_DRIVER_FUNCTION
///	PICO_NULL_PARAMETER
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps2000aGetMaxSegments)
	(
	int16_t		handle,
	uint32_t * maxSegments
	);

/// <summary>
/// Retrieves the current state of the output edge detect flag
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="state">Output: The current of the output edge detect</param>
/// <returns>
/// PICO_OK
/// PICO_NOT_USED
/// PICO_NULL_PARAMETER
/// PICO_NOT_SUPPORTED_BY_THIS_DEVICE
///	PICO_INVALID_HANDLE
///	PICO_DRIVER_FUNCTION
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps2000aQueryOutputEdgeDetect)
(
	int16_t		handle,
	int16_t * state
	);

/// <summary>
/// Sets the state of the output edge detect flag, Default value is TRUE
/// </summary>
/// <param name="handle">Device identifier returned by ps2000aOpenUnit.</param>
/// <param name="state">The output edge detect state to be set:
///			any none 0 value: enable
///			0: disable</param>
/// <returns>
/// PICO_OK
/// PICO_NOT_USED
/// PICO_NULL_PARAMETER
/// PICO_NOT_SUPPORTED_BY_THIS_DEVICE
///	PICO_INVALID_HANDLE
///	PICO_DRIVER_FUNCTION
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps2000aSetOutputEdgeDetect)
(
	int16_t	handle,
	int16_t state
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps2000aGetScalingValues)
(
	int16_t	handle,
	PS2000A_SCALING_FACTORS_VALUES *scalingValues,
	int16_t nChannels
);

#endif
