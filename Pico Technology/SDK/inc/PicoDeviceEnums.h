/****************************************************************************
 *
 * Filename:    PicoDeviceEnums.h
 * Copyright:   Pico Technology Limited 2016 - 2022
 * Description:
 *
 * This header contains definitions of enumerated types that describe
 * various operating modes, trigger types, bandwidth limiters, etc.
 *
 ****************************************************************************/

#ifndef __PICODEVICEENUMS_H__
#define __PICODEVICEENUMS_H__

typedef enum enPicoRatioMode
{
  PICO_RATIO_MODE_AGGREGATE = 1,
  PICO_RATIO_MODE_DECIMATE = 2,
  PICO_RATIO_MODE_AVERAGE = 4,
  PICO_RATIO_MODE_DISTRIBUTION = 8,
  PICO_RATIO_MODE_SUM = 16,

  PICO_RATIO_MODE_TRIGGER_DATA_FOR_TIME_CALCULATION = 0x10000000, // buffers cannot be set for this mode
  PICO_RATIO_MODE_SEGMENT_HEADER = 0x20000000, // buffers do not need to be set for this
  PICO_RATIO_MODE_TRIGGER = 0x40000000, // this cannot be combined with any other ratio mode
  PICO_RATIO_MODE_RAW = 0x80000000
} PICO_RATIO_MODE;

typedef enum enPicoChannel
{
  PICO_CHANNEL_A = 0,
  PICO_CHANNEL_B = 1,
  PICO_CHANNEL_C = 2,
  PICO_CHANNEL_D = 3,
  PICO_CHANNEL_E = 4,
  PICO_CHANNEL_F = 5,
  PICO_CHANNEL_G = 6,
  PICO_CHANNEL_H = 7,

  PICO_PORT0 = 128,
  PICO_PORT1 = 129,
  PICO_PORT2 = 130,
  PICO_PORT3 = 131,

  PICO_EXTERNAL = 1000,
  PICO_TRIGGER_AUX = 1001,

  PICO_PULSE_WIDTH_SOURCE = 0x10000000,
  PICO_DIGITAL_SOURCE = 0x10000001
} PICO_CHANNEL;

typedef enum enPicoChannelFlags
{
  PICO_CHANNEL_A_FLAGS = 1,
  PICO_CHANNEL_B_FLAGS = 2,
  PICO_CHANNEL_C_FLAGS = 4,
  PICO_CHANNEL_D_FLAGS = 8,
  PICO_CHANNEL_E_FLAGS = 16,
  PICO_CHANNEL_F_FLAGS = 32,
  PICO_CHANNEL_G_FLAGS = 64,
  PICO_CHANNEL_H_FLAGS = 128,

  PICO_PORT0_FLAGS = 65536,
  PICO_PORT1_FLAGS = 131072,
  PICO_PORT2_FLAGS = 262144,
  PICO_PORT3_FLAGS = 524288,

} PICO_CHANNEL_FLAGS;

typedef enum enPicoPortDigitalChannel
{
  PICO_PORT_DIGITAL_CHANNEL0,
  PICO_PORT_DIGITAL_CHANNEL1,
  PICO_PORT_DIGITAL_CHANNEL2,
  PICO_PORT_DIGITAL_CHANNEL3,
  PICO_PORT_DIGITAL_CHANNEL4,
  PICO_PORT_DIGITAL_CHANNEL5,
  PICO_PORT_DIGITAL_CHANNEL6,
  PICO_PORT_DIGITAL_CHANNEL7
} PICO_PORT_DIGITAL_CHANNEL;

typedef enum enPicoDataType
{
  PICO_INT8_T,
  PICO_INT16_T,
  PICO_INT32_T,
  PICO_UINT32_T,
  PICO_INT64_T
} PICO_DATA_TYPE;

typedef enum enPicoCoupling
{
  PICO_AC = 0,
  PICO_DC = 1,

  PICO_DC_50OHM = 50
} PICO_COUPLING;

typedef enum enPicoBandwidthLimiterFlags
{
  PICO_BW_FULL_FLAG = (1 << 0),
  PICO_BW_20KHZ_FLAG = (1 << 1),
  PICO_BW_100KHZ_FLAG = (1 << 2), //( default when current clamp detected: can be changed)
  PICO_BW_1MHZ_FLAG = (1 << 3), //( default for 14 bits: can be changed)
  PICO_BW_20MHZ_FLAG = (1 << 4),
  PICO_BW_200MHZ_FLAG = (1 << 5),
} PICO_BANDWIDTH_LIMITER_FLAGS;

typedef enum enPicoBandwidthLimiter
{
  PICO_BW_FULL = 0,

  PICO_BW_100KHZ = 100000,

  PICO_BW_20KHZ = 20000,

  PICO_BW_1MHZ = 1000000,
  PICO_BW_20MHZ = 20000000,

  PICO_BW_25MHZ = 25000000,

  PICO_BW_50MHZ = 50000000,

  PICO_BW_200MHZ = 200000000,
  PICO_BW_250MHZ = 250000000,

  PICO_BW_500MHZ = 500000000,

} PICO_BANDWIDTH_LIMITER;

typedef enum enPicoPulseWidthType
{
  PICO_PW_TYPE_NONE = 0,
  PICO_PW_TYPE_LESS_THAN = 1,
  PICO_PW_TYPE_GREATER_THAN = 2,
  PICO_PW_TYPE_IN_RANGE = 3,
  PICO_PW_TYPE_OUT_OF_RANGE = 4
} PICO_PULSE_WIDTH_TYPE;

typedef enum enPicoSweepType
{
  PICO_UP = 0,
  PICO_DOWN = 1,
  PICO_UPDOWN = 2,
  PICO_DOWNUP = 3,
} PICO_SWEEP_TYPE;

typedef enum enPicoWaveType
{
  PICO_SINE = 0x00000011,
  PICO_SQUARE = 0x00000012,
  PICO_TRIANGLE = 0x00000013,
  PICO_RAMP_UP = 0x00000014,
  PICO_RAMP_DOWN = 0x00000015,
  PICO_SINC = 0x00000016,
  PICO_GAUSSIAN = 0x00000017,
  PICO_HALF_SINE = 0x00000018,

  PICO_DC_VOLTAGE = 0x00000400,

  PICO_PWM = 0x00001000,

  PICO_WHITENOISE = 0x00002001,
  PICO_PRBS = 0x00002002, // Pseudo-Random Bit Stream

  PICO_ARBITRARY = 0x10000000
} PICO_WAVE_TYPE;

typedef enum enPicoSigGenTrigType
{
  PICO_SIGGEN_RISING = 0,
  PICO_SIGGEN_FALLING = 1,
  PICO_SIGGEN_GATE_HIGH = 2,
  PICO_SIGGEN_GATE_LOW = 3
} PICO_SIGGEN_TRIG_TYPE;

typedef enum enPicoSigGenTrigSource
{
  PICO_SIGGEN_NONE = 0,
  PICO_SIGGEN_SCOPE_TRIG = 1,
  PICO_SIGGEN_AUX_IN = 2,
  PICO_SIGGEN_EXT_IN = 3,
  PICO_SIGGEN_SOFT_TRIG = 4,
  PICO_SIGGEN_TRIGGER_RAW = 5
} PICO_SIGGEN_TRIG_SOURCE;

typedef enum enPicoSigGenFilterState
{
  PICO_SIGGEN_FILTER_AUTO = 0,
  PICO_SIGGEN_FILTER_OFF = 1,
  PICO_SIGGEN_FILTER_ON = 2
} PICO_SIGGEN_FILTER_STATE;

typedef enum enPicoSigGenParameter
{
  PICO_SIGGEN_PARAM_OUTPUT_VOLTS = 0,
  PICO_SIGGEN_PARAM_SAMPLE = 1,
  PICO_SIGGEN_PARAM_BUFFER_LENGTH = 2
} PICO_SIGGEN_PARAMETER;

typedef enum enPicoTimeUnits
{
  PICO_FS = 0,
  PICO_PS = 1,
  PICO_NS = 2,
  PICO_US = 3,
  PICO_MS = 4,
  PICO_S = 5,
} PICO_TIME_UNITS;

typedef enum enPicoThresholdDirection
{
  PICO_ABOVE = 0, //using upper threshold
  PICO_BELOW = 1, //using upper threshold
  PICO_RISING = 2, // using upper threshold
  PICO_FALLING = 3, // using upper threshold
  PICO_RISING_OR_FALLING = 4, // using both thresholds
  PICO_ABOVE_LOWER = 5, // using lower threshold
  PICO_BELOW_LOWER = 6, // using lower threshold
  PICO_RISING_LOWER = 7, // using lower threshold
  PICO_FALLING_LOWER = 8, // using lower threshold

  // Windowing using both thresholds
  PICO_INSIDE = PICO_ABOVE,
  PICO_OUTSIDE = PICO_BELOW,
  PICO_ENTER = PICO_RISING,
  PICO_EXIT = PICO_FALLING,
  PICO_ENTER_OR_EXIT = PICO_RISING_OR_FALLING,
  PICO_POSITIVE_RUNT = 9,
  PICO_NEGATIVE_RUNT,

  // no trigger set
  PICO_NONE = PICO_RISING
} PICO_THRESHOLD_DIRECTION;

typedef enum enPicoThresholdMode
{
  PICO_LEVEL = 0,
  PICO_WINDOW = 1
} PICO_THRESHOLD_MODE;

typedef enum enPicoEtsMode
{
  PICO_ETS_OFF = 0, // ETS disabled
  PICO_ETS_FAST = 1, // Return ready as soon as requested no of interleaves is available
  PICO_ETS_SLOW = 2, // Return ready every time a new set of no_of_cycles is collected
} PICO_ETS_MODE;

typedef enum enPicoIndexMode
{
  PICO_SINGLE = 0,
  PICO_DUAL = 1,
  PICO_QUAD = 2,
} PICO_INDEX_MODE;

typedef enum enPicoAction
{
  PICO_CLEAR_ALL = 0x00000001,
  PICO_ADD = 0x00000002,

  PICO_CLEAR_THIS_DATA_BUFFER = 0x00001000,
  PICO_CLEAR_WAVEFORM_DATA_BUFFERS = 0x00002000,
  PICO_CLEAR_WAVEFORM_READ_DATA_BUFFERS = 0x00004000,

} PICO_ACTION;

typedef enum enPicoTriggerState
{
  PICO_CONDITION_DONT_CARE = 0,
  PICO_CONDITION_TRUE = 1,
  PICO_CONDITION_FALSE = 2,
} PICO_TRIGGER_STATE;

typedef enum enPicoDeviceResolution
{
  PICO_DR_8BIT = 0,
  PICO_DR_12BIT = 1,
  PICO_DR_14BIT = 2,
  PICO_DR_15BIT = 3,
  PICO_DR_16BIT = 4,

  PICO_DR_10BIT = 10,

} PICO_DEVICE_RESOLUTION;

typedef enum enPicoReadSelection
{
  PICO_READSELECTION_NONE = 0,
  PICO_TRIGGER_READ = 1,
  PICO_DATA_READ1 = 2,
  PICO_DATA_READ2 = 3,
  PICO_DATA_READ3 = 4,
} PICO_READ_SELECTION;

typedef enum enPicoTrimAction
{
  PICO_OLDEST,
  PICO_RECENT
} PICO_TRIM_ACTION;

typedef enum enPicoDigitalPortHysteresis
{
  PICO_VERY_HIGH_400MV,
  PICO_HIGH_200MV,
  PICO_NORMAL_100MV,
  PICO_LOW_50MV
} PICO_DIGITAL_PORT_HYSTERESIS;

typedef enum enPicoDigitalDirection
{
  PICO_DIGITAL_DONT_CARE,
  PICO_DIGITAL_DIRECTION_LOW,
  PICO_DIGITAL_DIRECTION_HIGH,
  PICO_DIGITAL_DIRECTION_RISING,
  PICO_DIGITAL_DIRECTION_FALLING,
  PICO_DIGITAL_DIRECTION_RISING_OR_FALLING,
  PICO_DIGITAL_MAX_DIRECTION
} PICO_DIGITAL_DIRECTION;

typedef enum enPicoConditionsInfo
{
  PICO_CLEAR_CONDITIONS = 0x00000001,
  PICO_ADD_CONDITION = 0x00000002
} PICO_CONDITIONS_INFO;

typedef enum enPicoClockReference
{
  PICO_INTERNAL_REF,
  PICO_EXTERNAL_REF
} PICO_CLOCK_REFERENCE;

typedef enum enPicoTriggerWithinPreTrigger
{
  PICO_DISABLE,
  PICO_ARM
} PICO_TRIGGER_WITHIN_PRE_TRIGGER;

typedef enum tPicoTemperatureReference
{
  PICO_TEMPERATURE_UNINITIALISED,
  PICO_TEMPERATURE_NORMAL,
  PICO_TEMPERATURE_WARNING,
  PICO_TEMPERATURE_CRITICAL
} PICO_TEMPERATURE_REFERENCE;

typedef enum enPicoDigitalPort
{
  PICO_DIGITAL_PORT_NONE = 0,

  PICO_DIGITAL_PORT_MSO_POD = 1000,

  PICO_DIGITAL_PORT_UNKNOWN_DEVICE = -2,

} PICO_DIGITAL_PORT;

#endif