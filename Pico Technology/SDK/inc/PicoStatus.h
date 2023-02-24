/**************************************************************************
*
* Filename:    PicoStatus.h
* Copyright:   Pico Technology Limited 2002 - 2022
* Description:
*
* This header files defines the status codes returned by a
*	Pico device, a PC Oscilloscope or Data Logger.
*
* In comments, "<API>" is a placeholder for the name of the scope or
* data logger API. For example, for the ps5000a API, it stands for
* "PS5000A" or "ps5000a".
*
*************************************************************************/
#ifndef __PICOSTATUS_H__
#define __PICOSTATUS_H__

#include <stdint.h>

typedef void * PICO_POINTER;

#define	PICO_DRIVER_VERSION                         0x00000000UL
#define	PICO_USB_VERSION                            0x00000001UL
#define	PICO_HARDWARE_VERSION                       0x00000002UL
#define	PICO_VARIANT_INFO                           0x00000003UL
#define	PICO_BATCH_AND_SERIAL                       0x00000004UL
#define	PICO_CAL_DATE                               0x00000005UL
#define	PICO_KERNEL_VERSION                         0x00000006UL

#define PICO_DIGITAL_HARDWARE_VERSION               0x00000007UL
#define PICO_ANALOGUE_HARDWARE_VERSION              0x00000008UL

#define PICO_FIRMWARE_VERSION_1                     0x00000009UL
#define PICO_FIRMWARE_VERSION_2                     0x0000000AUL

#define PICO_MAC_ADDRESS                            0x0000000BUL

#define PICO_SHADOW_CAL                             0x0000000CUL

#define PICO_IPP_VERSION                            0x0000000DUL

#define PICO_DRIVER_PATH                            0x0000000EUL

#define PICO_FIRMWARE_VERSION_3                     0x0000000FUL

#define PICO_FRONT_PANEL_FIRMWARE_VERSION           0x00000010UL

#define PICO_BOOTLOADER_VERSION						0x10000001UL

typedef uint32_t PICO_INFO;

// The PicoScope is functioning correctly.
#define PICO_OK                                     0x00000000UL

// An attempt has been made to open more than <API>_MAX_UNITS.
#define PICO_MAX_UNITS_OPENED                       0x00000001UL

// Not enough memory could be allocated on the host machine.
#define PICO_MEMORY_FAIL                            0x00000002UL

// No Pico Technology device could be found.
#define PICO_NOT_FOUND                              0x00000003UL

// Unable to download firmware.
#define PICO_FW_FAIL                                0x00000004UL

// The driver is busy opening a device.
#define PICO_OPEN_OPERATION_IN_PROGRESS             0x00000005UL

// An unspecified failure occurred.
#define PICO_OPERATION_FAILED                       0x00000006UL

// The PicoScope is not responding to commands from the PC.
#define PICO_NOT_RESPONDING                         0x00000007UL

// The configuration information in the PicoScope is corrupt or missing.
#define PICO_CONFIG_FAIL                            0x00000008UL

// The picopp.sys file is too old to be used with the device driver.
#define PICO_KERNEL_DRIVER_TOO_OLD                  0x00000009UL

// The EEPROM has become corrupt, so the device will use a default setting.
#define PICO_EEPROM_CORRUPT                         0x0000000AUL

// The operating system on the PC is not supported by this driver.
#define PICO_OS_NOT_SUPPORTED                       0x0000000BUL

// There is no device with the handle value passed.
#define PICO_INVALID_HANDLE                         0x0000000CUL

// A parameter value is not valid.
#define PICO_INVALID_PARAMETER                      0x0000000DUL

// The timebase is not supported or is invalid.
#define PICO_INVALID_TIMEBASE                       0x0000000EUL

// The voltage range is not supported or is invalid.
#define PICO_INVALID_VOLTAGE_RANGE                  0x0000000FUL

// The channel number is not valid on this device or no channels have been set.
#define PICO_INVALID_CHANNEL                        0x00000010UL

// The channel set for a trigger is not available on this device.
#define PICO_INVALID_TRIGGER_CHANNEL                0x00000011UL

// The channel set for a condition is not available on this device.
#define PICO_INVALID_CONDITION_CHANNEL              0x00000012UL

// The device does not have a signal generator.
#define PICO_NO_SIGNAL_GENERATOR                    0x00000013UL

// Streaming has failed to start or has stopped without user request.
#define PICO_STREAMING_FAILED                       0x00000014UL

// Block failed to start - a parameter may have been set wrongly.
#define PICO_BLOCK_MODE_FAILED                      0x00000015UL

// A parameter that was required is NULL.
#define PICO_NULL_PARAMETER                         0x00000016UL

// The current functionality is not available while using ETS capture mode.
#define PICO_ETS_MODE_SET                           0x00000017UL

// No data is available from a run block call.
#define PICO_DATA_NOT_AVAILABLE                     0x00000018UL

// The buffer passed for the information was too small.
#define PICO_STRING_BUFFER_TO_SMALL                 0x00000019UL

// ETS is not supported on this device.
#define PICO_ETS_NOT_SUPPORTED                      0x0000001AUL

// The auto trigger time is less than the time it will take to collect the pre-trigger data.
#define PICO_AUTO_TRIGGER_TIME_TO_SHORT             0x0000001BUL

// The collection of data has stalled as unread data would be overwritten.
#define PICO_BUFFER_STALL                           0x0000001CUL

// Number of samples requested is more than available in the current memory segment.
#define PICO_TOO_MANY_SAMPLES                       0x0000001DUL

// Not possible to create number of segments requested.
#define PICO_TOO_MANY_SEGMENTS                      0x0000001EUL

// A null pointer has been passed in the trigger function or one of the parameters is out of range.
#define PICO_PULSE_WIDTH_QUALIFIER                  0x0000001FUL

// One or more of the hold-off parameters are out of range.
#define PICO_DELAY                                  0x00000020UL

// One or more of the source details are incorrect.
#define	PICO_SOURCE_DETAILS                         0x00000021UL

// One or more of the conditions are incorrect.
#define PICO_CONDITIONS                             0x00000022UL

// The driver's thread is currently in the <API>Ready callback
// function and therefore the action cannot be carried out.
#define	PICO_USER_CALLBACK                          0x00000023UL

// An attempt is being made to get stored data while streaming.
// Either stop streaming by calling <API>Stop, or use <API>GetStreamingLatestValues.
#define PICO_DEVICE_SAMPLING                        0x00000024UL

// Data is unavailable because a run has not been completed.
#define PICO_NO_SAMPLES_AVAILABLE                   0x00000025UL

// The memory segment index is out of range.
#define PICO_SEGMENT_OUT_OF_RANGE                   0x00000026UL

// The device is busy so data cannot be returned yet.
#define PICO_BUSY                                   0x00000027UL

// The start time to get stored data is out of range.
#define PICO_STARTINDEX_INVALID                     0x00000028UL

// The information number requested is not a valid number.
#define PICO_INVALID_INFO                           0x00000029UL

// The handle is invalid so no information is available about the device.
// Only PICO_DRIVER_VERSION is available.
#define PICO_INFO_UNAVAILABLE                       0x0000002AUL

// The sample interval selected for streaming is out of range.
#define PICO_INVALID_SAMPLE_INTERVAL                0x0000002BUL

// ETS is set but no trigger has been set. A trigger setting is required for ETS.
#define PICO_TRIGGER_ERROR                          0x0000002CUL

// Driver cannot allocate memory.
#define PICO_MEMORY                                 0x0000002DUL

// Incorrect parameter passed to the signal generator.
#define PICO_SIG_GEN_PARAM                          0x0000002EUL

// Conflict between the shots and sweeps parameters sent to the signal generator.
#define PICO_SHOTS_SWEEPS_WARNING                   0x0000002FUL

// A software trigger has been sent but the trigger source is not a software trigger.
#define PICO_SIGGEN_TRIGGER_SOURCE                  0x00000030UL

// An <API>SetTrigger call has found a conflict between the trigger source and the AUX output enable.
#define PICO_AUX_OUTPUT_CONFLICT                    0x00000031UL

// ETS mode is being used and AUX is set as an input.
#define PICO_AUX_OUTPUT_ETS_CONFLICT                0x00000032UL

// Attempt to set different EXT input thresholds set for signal generator and oscilloscope trigger.
#define PICO_WARNING_EXT_THRESHOLD_CONFLICT         0x00000033UL

// An <API>SetTrigger... function has set AUX as an output and the signal generator is using it as a trigger.
#define PICO_WARNING_AUX_OUTPUT_CONFLICT            0x00000034UL

// The combined peak-to-peak voltage and the analog offset voltage exceed the maximum voltage the signal generator can produce.
#define PICO_SIGGEN_OUTPUT_OVER_VOLTAGE             0x00000035UL

// NULL pointer passed as delay parameter.
#define PICO_DELAY_NULL                             0x00000036UL

// The buffers for overview data have not been set while streaming.
#define PICO_INVALID_BUFFER                         0x00000037UL

// The analog offset voltage is out of range.
#define PICO_SIGGEN_OFFSET_VOLTAGE                  0x00000038UL

// The analog peak-to-peak voltage is out of range.
#define PICO_SIGGEN_PK_TO_PK                        0x00000039UL

// A block collection has been cancelled.
#define PICO_CANCELLED                              0x0000003AUL

// The segment index is not currently being used.
#define PICO_SEGMENT_NOT_USED                       0x0000003BUL

// The wrong GetValues function has been called for the collection mode in use.
#define PICO_INVALID_CALL                           0x0000003CUL

#define PICO_GET_VALUES_INTERRUPTED                 0x0000003DUL

// The function is not available.
#define PICO_NOT_USED                               0x0000003FUL

// The aggregation ratio requested is out of range.
#define PICO_INVALID_SAMPLERATIO                    0x00000040UL

// Device is in an invalid state.
#define PICO_INVALID_STATE                          0x00000041UL

// The number of segments allocated is fewer than the number of captures requested.
#define PICO_NOT_ENOUGH_SEGMENTS                    0x00000042UL

// A driver function has already been called and not yet finished.
// Only one call to the driver can be made at any one time.
#define PICO_DRIVER_FUNCTION                        0x00000043UL

// Not used.
#define PICO_RESERVED                               0x00000044UL

// An invalid coupling type was specified in <API>SetChannel.
#define PICO_INVALID_COUPLING                       0x00000045UL

// An attempt was made to get data before a data buffer was defined.
#define PICO_BUFFERS_NOT_SET                        0x00000046UL

// The selected downsampling mode (used for data reduction) is not allowed.
#define PICO_RATIO_MODE_NOT_SUPPORTED               0x00000047UL

// Aggregation was requested in rapid block mode.
#define PICO_RAPID_NOT_SUPPORT_AGGREGATION          0x00000048UL

// An invalid parameter was passed to <API>SetTriggerChannelProperties(V2).
#define PICO_INVALID_TRIGGER_PROPERTY               0x00000049UL

// The driver was unable to contact the oscilloscope.
#define PICO_INTERFACE_NOT_CONNECTED                0x0000004AUL

// Resistance-measuring mode is not allowed in conjunction with the specified probe.
#define PICO_RESISTANCE_AND_PROBE_NOT_ALLOWED       0x0000004BUL

// The device was unexpectedly powered down.
#define PICO_POWER_FAILED                           0x0000004CUL

// A problem occurred in <API>SetSigGenBuiltIn or <API>SetSigGenArbitrary.
#define PICO_SIGGEN_WAVEFORM_SETUP_FAILED           0x0000004DUL

// FPGA not successfully set up.
#define PICO_FPGA_FAIL                              0x0000004EUL

#define PICO_POWER_MANAGER                          0x0000004FUL

// An impossible analog offset value was specified in <API>SetChannel.
#define PICO_INVALID_ANALOGUE_OFFSET                0x00000050UL

// There is an error within the device hardware.
#define PICO_PLL_LOCK_FAILED                        0x00000051UL

// There is an error within the device hardware.
#define PICO_ANALOG_BOARD                           0x00000052UL

// Unable to configure the signal generator.
#define PICO_CONFIG_FAIL_AWG                        0x00000053UL

// The FPGA cannot be initialized, so unit cannot be opened.
#define PICO_INITIALISE_FPGA                        0x00000054UL

// The frequency for the external clock is not within 15% of the nominal value.
#define PICO_EXTERNAL_FREQUENCY_INVALID             0x00000056UL

// The FPGA could not lock the clock signal.
#define PICO_CLOCK_CHANGE_ERROR                     0x00000057UL

// You are trying to configure the AUX input as both a trigger and a reference clock.
#define PICO_TRIGGER_AND_EXTERNAL_CLOCK_CLASH       0x00000058UL

// You are trying to configure the AUX input as both a pulse width qualifier and a reference clock.
#define PICO_PWQ_AND_EXTERNAL_CLOCK_CLASH           0x00000059UL

// The requested scaling file cannot be opened.
#define PICO_UNABLE_TO_OPEN_SCALING_FILE            0x0000005AUL

// The frequency of the memory is reporting incorrectly.
#define PICO_MEMORY_CLOCK_FREQUENCY                 0x0000005BUL

// The I2C that is being actioned is not responding to requests.
#define PICO_I2C_NOT_RESPONDING                     0x0000005CUL

// There are no captures available and therefore no data can be returned.
#define PICO_NO_CAPTURES_AVAILABLE                  0x0000005DUL

// The number of trigger channels is greater than 4,
// except for a PicoScope 4824 where 8 channels are allowed for rising/falling/rising_or_falling trigger directions.
#define PICO_TOO_MANY_TRIGGER_CHANNELS_IN_USE				0x0000005FUL

// If you have specified a trigger direction which is not allowed, for example specifying PICO_ABOVE
// without another condition which crosses a threshold on another channel.
#define PICO_INVALID_TRIGGER_DIRECTION							0x00000060UL

// When more than 4 trigger channels are set and their trigger condition states are not <API>_CONDITION_TRUE.
#define PICO_INVALID_TRIGGER_STATES									0x00000061UL

// The capture mode the device is currently running in does not support the current request.
#define PICO_NOT_USED_IN_THIS_CAPTURE_MODE          0x0000005EUL

#define PICO_GET_DATA_ACTIVE                        0x00000103UL

// Codes 104 to 10B are used by the PT104 (USB) when connected via the Network Socket.

// The device is currently connected via the IP Network socket and thus the call made is not supported.
#define PICO_IP_NETWORKED                           0x00000104UL

// An incorrect IP address has been passed to the driver.
#define PICO_INVALID_IP_ADDRESS                     0x00000105UL

// The IP socket has failed.
#define PICO_IPSOCKET_FAILED                        0x00000106UL

// The IP socket has timed out.
#define PICO_IPSOCKET_TIMEDOUT                      0x00000107UL

// Failed to apply the requested settings.
#define PICO_SETTINGS_FAILED                        0x00000108UL

// The network connection has failed.
#define PICO_NETWORK_FAILED                         0x00000109UL

// Unable to load the WS2 DLL.
#define PICO_WS2_32_DLL_NOT_LOADED                  0x0000010AUL

// The specified IP port is invalid.
#define PICO_INVALID_IP_PORT                        0x0000010BUL

// The type of coupling requested is not supported on the opened device.
#define PICO_COUPLING_NOT_SUPPORTED                 0x0000010CUL

// Bandwidth limiting is not supported on the opened device.
#define PICO_BANDWIDTH_NOT_SUPPORTED                0x0000010DUL

// The value requested for the bandwidth limit is out of range.
#define PICO_INVALID_BANDWIDTH                      0x0000010EUL

// The arbitrary waveform generator is not supported by the opened device.
#define PICO_AWG_NOT_SUPPORTED                      0x0000010FUL

// Data has been requested with ETS mode set but run block has not been called,
// or stop has been called.
#define PICO_ETS_NOT_RUNNING                        0x00000110UL

// White noise output is not supported on the opened device.
#define PICO_SIG_GEN_WHITENOISE_NOT_SUPPORTED       0x00000111UL

// The wave type requested is not supported by the opened device.
#define PICO_SIG_GEN_WAVETYPE_NOT_SUPPORTED         0x00000112UL

// The requested digital port number is out of range (MSOs only).
#define PICO_INVALID_DIGITAL_PORT                   0x00000113UL

// The digital channel is not in the range <API>_DIGITAL_CHANNEL0 to
// <API>_DIGITAL_CHANNEL15, the digital channels that are supported.
#define PICO_INVALID_DIGITAL_CHANNEL                0x00000114UL

// The digital trigger direction is not a valid trigger direction and should be equal
// in value to one of the <API>_DIGITAL_DIRECTION enumerations.
#define PICO_INVALID_DIGITAL_TRIGGER_DIRECTION      0x00000115UL

// Signal generator does not generate pseudo-random binary sequence.
#define	PICO_SIG_GEN_PRBS_NOT_SUPPORTED             0x00000116UL

// When a digital port is enabled, ETS sample mode is not available for use.
#define PICO_ETS_NOT_AVAILABLE_WITH_LOGIC_CHANNELS  0x00000117UL

// There has been no new sample taken, this value has already been returned previously.
#define PICO_WARNING_REPEAT_VALUE                   0x00000118UL

// The DC power supply is connected.
#define PICO_POWER_SUPPLY_CONNECTED                 0x00000119UL

// The DC power supply is not connected.
// For many 4+ Channel devices this will mean a restricted feature set is offered e.g. for a 4 channel device - C and D are usually disabled.
// Check the respective API programmers guide of your device for the full details.
#define PICO_POWER_SUPPLY_NOT_CONNECTED             0x0000011AUL

// Incorrect power mode passed for current power source.
#define PICO_POWER_SUPPLY_REQUEST_INVALID           0x0000011BUL

// The supply voltage from the USB source is too low.
#define PICO_POWER_SUPPLY_UNDERVOLTAGE              0x0000011CUL

// The oscilloscope is in the process of capturing data.
#define PICO_CAPTURING_DATA                         0x0000011DUL

// A USB 3.0 device is connected to a non-USB 3.0 port.
#define PICO_USB3_0_DEVICE_NON_USB3_0_PORT          0x0000011EUL

// A function has been called that is not supported by the current device.
#define PICO_NOT_SUPPORTED_BY_THIS_DEVICE           0x0000011FUL

// The device resolution is invalid (out of range).
#define PICO_INVALID_DEVICE_RESOLUTION              0x00000120UL

// The number of channels that can be enabled is limited in 15 and 16-bit modes.
// (Flexible Resolution Oscilloscopes only)
#define PICO_INVALID_NUMBER_CHANNELS_FOR_RESOLUTION 0x00000121UL

// USB power not sufficient for all requested channels.
#define PICO_CHANNEL_DISABLED_DUE_TO_USB_POWERED    0x00000122UL

// The signal generator does not have a configurable DC offset.
#define PICO_SIGGEN_DC_VOLTAGE_NOT_CONFIGURABLE     0x00000123UL

// An attempt has been made to define pre-trigger delay without first enabling a trigger.
#define PICO_NO_TRIGGER_ENABLED_FOR_TRIGGER_IN_PRE_TRIG  0x00000124UL

// An attempt has been made to define pre-trigger delay without first arming a trigger.
#define PICO_TRIGGER_WITHIN_PRE_TRIG_NOT_ARMED           0x00000125UL

// Pre-trigger delay and post-trigger delay cannot be used at the same time.
#define PICO_TRIGGER_WITHIN_PRE_NOT_ALLOWED_WITH_DELAY   0x00000126UL

// The array index points to a nonexistent trigger.
#define PICO_TRIGGER_INDEX_UNAVAILABLE                   0x00000127UL

#define PICO_AWG_CLOCK_FREQUENCY									0x00000128UL

// There are more than 4 analog channels with a trigger condition set.
#define PICO_TOO_MANY_CHANNELS_IN_USE							0x00000129UL

// The condition parameter is a null pointer.
#define PICO_NULL_CONDITIONS											0x0000012AUL

// There is more than one condition pertaining to the same channel.
#define PICO_DUPLICATE_CONDITION_SOURCE						0x0000012BUL

// The parameter relating to condition information is out of range.
#define PICO_INVALID_CONDITION_INFO								0x0000012CUL

// Reading the meta data has failed.
#define PICO_SETTINGS_READ_FAILED									0x0000012DUL

// Writing the meta data has failed.
#define PICO_SETTINGS_WRITE_FAILED								0x0000012EUL

// A parameter has a value out of the expected range.
#define PICO_ARGUMENT_OUT_OF_RANGE								0x0000012FUL

// The driver does not support the hardware variant connected.
#define PICO_HARDWARE_VERSION_NOT_SUPPORTED				0x00000130UL

// The driver does not support the digital hardware variant connected.
#define PICO_DIGITAL_HARDWARE_VERSION_NOT_SUPPORTED				0x00000131UL

// The driver does not support the analog hardware variant connected.
#define PICO_ANALOGUE_HARDWARE_VERSION_NOT_SUPPORTED				0x00000132UL

// Converting a channel's ADC value to resistance has failed.
#define PICO_UNABLE_TO_CONVERT_TO_RESISTANCE			0x00000133UL

// The channel is listed more than once in the function call.
#define PICO_DUPLICATED_CHANNEL										0x00000134UL

// The range cannot have resistance conversion applied.
#define PICO_INVALID_RESISTANCE_CONVERSION				0x00000135UL

// An invalid value is in the max buffer.
#define PICO_INVALID_VALUE_IN_MAX_BUFFER					0x00000136UL

// An invalid value is in the min buffer.
#define PICO_INVALID_VALUE_IN_MIN_BUFFER					0x00000137UL

// When calculating the frequency for phase conversion,
// the frequency is greater than that supported by the current variant.
#define PICO_SIGGEN_FREQUENCY_OUT_OF_RANGE				0x00000138UL

// The device's EEPROM is corrupt. Contact Pico Technology support: https://www.picotech.com/tech-support.
#define PICO_EEPROM2_CORRUPT											0x00000139UL

// The EEPROM has failed.
#define PICO_EEPROM2_FAIL													0x0000013AUL

// The serial buffer is too small for the required information.
#define PICO_SERIAL_BUFFER_TOO_SMALL							0x0000013BUL

// The signal generator trigger and the external clock have both been set.
// This is not allowed.
#define PICO_SIGGEN_TRIGGER_AND_EXTERNAL_CLOCK_CLASH 0x0000013CUL

// The AUX trigger was enabled and the external clock has been enabled,
// so the AUX has been automatically disabled.
#define PICO_WARNING_SIGGEN_AUXIO_TRIGGER_DISABLED 0x0000013DUL

// The AUX I/O was set as a scope trigger and is now being set as a signal generator
// gating trigger. This is not allowed.
#define PICO_SIGGEN_GATING_AUXIO_NOT_AVAILABLE	 	 0x00000013EUL

// The AUX I/O was set by the signal generator as a gating trigger and is now being set
// as a scope trigger. This is not allowed.
#define PICO_SIGGEN_GATING_AUXIO_ENABLED				 	 0x00000013FUL

// A resource has failed to initialise.
#define PICO_RESOURCE_ERROR												 0x00000140UL

// The temperature type is out of range.
#define PICO_TEMPERATURE_TYPE_INVALID							 0x000000141UL

// A requested temperature type is not supported on this device.
#define PICO_TEMPERATURE_TYPE_NOT_SUPPORTED				 0x000000142UL

// A read/write to the device has timed out.
#define PICO_TIMEOUT															 0x00000143UL

// The device cannot be connected correctly.
#define PICO_DEVICE_NOT_FUNCTIONING							   0x00000144UL

// The driver has experienced an unknown error and is unable to recover from this error.
#define PICO_INTERNAL_ERROR												 0x00000145UL

// Used when opening units via IP and more than multiple units have the same IP address.
#define PICO_MULTIPLE_DEVICES_FOUND								 0x00000146UL

#define PICO_WARNING_NUMBER_OF_SEGMENTS_REDUCED 	 					0x00000147UL

// The calibration pin states argument is out of range.
#define PICO_CAL_PINS_STATES											0x00000148UL

// The calibration pin frequency argument is out of range.
#define PICO_CAL_PINS_FREQUENCY										0x00000149UL

// The calibration pin amplitude argument is out of range.
#define PICO_CAL_PINS_AMPLITUDE										0x0000014AUL

// The calibration pin wavetype argument is out of range.
#define PICO_CAL_PINS_WAVETYPE										0x0000014BUL

// The calibration pin offset argument is out of range.
#define PICO_CAL_PINS_OFFSET											0x0000014CUL

// The probe's identity has a problem.
#define PICO_PROBE_FAULT													0x0000014DUL

// The probe has not been identified.
#define PICO_PROBE_IDENTITY_UNKNOWN								0x0000014EUL

// Enabling the probe would cause the device to exceed the allowable current limit.
#define PICO_PROBE_POWER_DC_POWER_SUPPLY_REQUIRED 0x0000014FUL

// The DC power supply is connected; enabling the probe would cause the device to exceed the
// allowable current limit.
#define PICO_PROBE_NOT_POWERED_WITH_DC_POWER_SUPPLY 0x00000150UL

// Failed to complete probe configuration.
#define	PICO_PROBE_CONFIG_FAILURE									0x00000151UL

// Failed to set the callback function, as currently in current callback function.
#define	PICO_PROBE_INTERACTION_CALLBACK						0x00000152UL

// The probe has been verified but not known on this driver.
#define	PICO_UNKNOWN_INTELLIGENT_PROBE						0x00000153UL

// The intelligent probe cannot be verified.
#define	PICO_INTELLIGENT_PROBE_CORRUPT						0x00000154UL

// The callback is null, probe collection will only start when
// first callback is a none null pointer.
#define PICO_PROBE_COLLECTION_NOT_STARTED					0x00000155UL

// The current drawn by the probe(s) has exceeded the allowed limit.
#define PICO_PROBE_POWER_CONSUMPTION_EXCEEDED    0x00000156UL

// The channel range limits have changed due to connecting or disconnecting a probe
// the channel has been enabled.
#define PICO_WARNING_PROBE_CHANNEL_OUT_OF_SYNC 0x00000157UL

#define PICO_ENDPOINT_MISSING									 0x00000158UL
#define PICO_UNKNOWN_ENDPOINT_REQUEST							 0x00000159UL

// The ADC on board the device has not been correctly identified.
#define PICO_ADC_TYPE_ERROR													0x0000015AUL

#define PICO_FPGA2_FAILED														0x0000015BUL

#define PICO_FPGA2_DEVICE_STATUS										0x0000015CUL

#define PICO_ENABLE_PROGRAM_FPGA2_FAILED						0x0000015DUL
#define PICO_NO_CHANNELS_OR_PORTS_ENABLED									0x0000015EUL

#define PICO_INVALID_RATIO_MODE											0x0000015FUL

#define PICO_READS_NOT_SUPPORTED_IN_CURRENT_CAPTURE_MODE 0x00000160UL

// These selection tests can be masked together to show that mode than one read selection has failed the tests,
// therefore theses error codes cover 0x00000161UL to 0x0000016FUL.
#define PICO_TRIGGER_READ_SELECTION_CHECK_FAILED						0x00000161UL
#define PICO_DATA_READ1_SELECTION_CHECK_FAILED						0x00000162UL
#define PICO_DATA_READ2_SELECTION_CHECK_FAILED						0x00000164UL
#define PICO_DATA_READ3_SELECTION_CHECK_FAILED						0x00000168UL

// The requested read is not one of the reads available in enPicoReadSelection.
#define PICO_READ_SELECTION_OUT_OF_RANGE						0x00000170UL

// The downsample ratio options cannot be combined together for this request.
#define PICO_MULTIPLE_RATIO_MODES										0x00000171UL

// The enPicoReadSelection request has no samples available.
#define PICO_NO_SAMPLES_READ			                  0x00000172UL

// The enPicoReadSelection did not include one of the downsample ratios now requested.
#define PICO_RATIO_MODE_NOT_REQUESTED								0x00000173UL

// No read requests have been made.
#define PICO_NO_USER_READ_REQUESTS_SET							0x00000174UL

// The parameter for <number of values> cannot be zero.
#define PICO_ZERO_SAMPLES_INVALID										0x00000175UL

// The analog hardware cannot be identified; contact Pico Technology Technical Support.
#define	PICO_ANALOGUE_HARDWARE_MISSING							0x00000176UL

// Setting of the analog hardware pins failed.
#define PICO_ANALOGUE_HARDWARE_PINS									0x00000177UL

// An SMPS fault has occurred.
#define PICO_ANALOGUE_HARDWARE_SMPS_FAULT						0x00000178UL

// There appears to be a conflict between the expected and actual hardware in the device; contact Pico Technology Technical Support.
#define PICO_DIGITAL_ANALOGUE_HARDWARE_CONFLICT			0x00000179UL

// One or more of the enPicoRatioMode requested do not have a data buffer set.
#define PICO_RATIO_MODE_BUFFER_NOT_SET							0x0000017AUL

// The resolution is valid but not supported by the opened device.
#define PICO_RESOLUTION_NOT_SUPPORTED_BY_VARIANT		0x0000017BUL

// The requested trigger threshold is out of range for the current device resolution.
#define PICO_THRESHOLD_OUT_OF_RANGE									0x0000017CUL

// The simple trigger only supports upper edge direction options.
#define PICO_INVALID_SIMPLE_TRIGGER_DIRECTION				0x0000017DUL

// The aux trigger is not supported on this variant.
#define PICO_AUX_NOT_SUPPORTED											0x0000017EUL

// The trigger directions pointer may not be null.
#define PICO_NULL_DIRECTIONS												0x0000017FUL

// The trigger channel properties pointer may not be null.
#define PICO_NULL_CHANNEL_PROPERTIES								0x00000180UL

// A trigger is set on a channel that has not been enabled.
#define PICO_TRIGGER_CHANNEL_NOT_ENABLED						0x00000181UL

// A trigger condition has been set but a trigger property not set.
#define PICO_CONDITION_HAS_NO_TRIGGER_PROPERTY			0x00000182UL

// When requesting trigger data, this option can only be combined with the segment header ratio mode flag.
#define PICO_RATIO_MODE_TRIGGER_MASKING_INVALID			0x00000183UL

// The trigger data buffer must be 40 or more samples in size.
#define PICO_TRIGGER_DATA_REQUIRES_MIN_BUFFER_SIZE_OF_40_SAMPLES 0x00000184UL

// The number of requested waveforms is greater than the number of memory segments allocated.
#define PICO_NO_OF_CAPTURES_OUT_OF_RANGE						0x00000185UL

// When requesting segment header information, the segment header does not require a data buffer,
// to get the segment information use GetTriggerInfo.
#define PICO_RATIO_MODE_SEGMENT_HEADER_DOES_NOT_REQUIRE_BUFFERS	0x00000186UL

// Use GetTriggerInfo to retrieve the segment header information.
#define PICO_FOR_SEGMENT_HEADER_USE_GETTRIGGERINFO	0x00000187UL

// A read request has not been set.
#define PICO_READ_NOT_SET														0x00000188UL

// The expected and actual states of the ADCs do not match.
#define PICO_ADC_SETTING_MISMATCH										0x00000189UL

// The requested data type is not one of the enPicoDataType listed.
#define PICO_DATATYPE_INVALID												0x0000018AUL

// The down sample ratio mode requested does not support the enPicoDataType option chosen.
#define PICO_RATIO_MODE_DOES_NOT_SUPPORT_DATATYPE		0x0000018BUL

// The channel combination is not valid for the resolution.
#define PICO_CHANNEL_COMBINATION_NOT_VALID_IN_THIS_RESOLUTION 0x0000018CUL


#define PICO_USE_8BIT_RESOLUTION										0x0000018DUL

// The buffer for minimum data values and maximum data values are the same buffers.
#define PICO_AGGREGATE_BUFFERS_SAME_POINTER					0x0000018EUL

// The read request number of samples requested for an overlapped operation are more
// than the total number of samples to capture.
#define PICO_OVERLAPPED_READ_VALUES_OUT_OF_RANGE		0x0000018FUL

// The overlapped read request has more segments specified than segments allocated.
#define PICO_OVERLAPPED_READ_SEGMENTS_OUT_OF_RANGE	0x00000190UL

// The number of channel combinations available are greater than the array size received.
#define PICO_CHANNELFLAGSCOMBINATIONS_ARRAY_SIZE_TOO_SMALL 0x00000191UL

// The number of captures is larger than the maximum number of segments allowed for the device variant.
#define PICO_CAPTURES_EXCEEDS_NO_OF_SUPPORTED_SEGMENTS 0x00000192UL

// The time unit requested is not one of the listed enPicoTimeUnits.
#define PICO_TIME_UNITS_OUT_OF_RANGE								0x00000193UL

// The number of samples parameter may not be zero.
#define PICO_NO_SAMPLES_REQUESTED										0x00000194UL

// The action requested is not listed in enPicoAction.
#define PICO_INVALID_ACTION													0x00000195UL

// When adding buffers for the same read request the buffers for all ratio mode requests have to be the same size.
#define PICO_NO_OF_SAMPLES_NEED_TO_BE_EQUAL_WHEN_ADDING_BUFFERS 0x00000196UL

// The data is being processed but there is no empty data buffers available, a new data buffer needs to be set sent to the driver
// so that the data can be processed.
#define PICO_WAITING_FOR_DATA_BUFFERS								0x00000197UL

// when streaming data, only one read option is available.
#define PICO_STREAMING_ONLY_SUPPORTS_ONE_READ				0x00000198UL

// A clear read request is not one of the enPicoAction listed.
#define PICO_CLEAR_DATA_BUFFER_INVALID					0x00000199UL

// The combination of action flags are not allowed.
#define PICO_INVALID_ACTION_FLAGS_COMBINATION				0x0000019AUL

//  PICO_ADD request has been made but both data buffers are set to null and so there is nowhere to put the data.
#define PICO_BOTH_MIN_AND_MAX_NULL_BUFFERS_CANNOT_BE_ADDED 0x0000019BUL

// A conflict between the data buffers being set has occurred. Please use the PICO_CLEAR_ALL action to reset.
#define PICO_CONFLICT_IN_SET_DATA_BUFFERS_CALL_REMOVE_DATA_BUFFER_TO_RESET 0x0000019CUL

// While processing data, buffers cannot be removed from the data buffers list.
#define PICO_REMOVING_DATA_BUFFER_ENTRIES_NOT_ALLOWED_WHILE_DATA_PROCESSING  0x0000019DUL

//  An USB request has failed.
#define PICO_CYUSB_REQUEST_FAILED						0x00000200UL

// A request has been made to retrieve the latest streaming data, but with either a null pointer or an array size set to zero.
#define PICO_STREAMING_DATA_REQUIRED				0x00000201UL

// A buffer being set has a length that is invalid (ie less than zero).
#define PICO_INVALID_NUMBER_OF_SAMPLES			0x00000202UL

// The distribution size may not be zero.
#define PICO_INVALID_DISTRIBUTION						0x00000203UL

// The buffer length in bytes is greater than a 4-byte word.
#define PICO_BUFFER_LENGTH_GREATER_THAN_INT32_T 0x00000204UL

// The PLL has failed.
#define PICO_PLL_MUX_OUT_FAILED             0x00000209UL

// Pulse width only supports one direction.
#define PICO_ONE_PULSE_WIDTH_DIRECTION_ALLOWED 0x0000020AUL

// There is no external trigger available on the device specified by the handle.
#define PICO_EXTERNAL_TRIGGER_NOT_SUPPORTED 0x0000020BUL

// The condition parameter is a null pointer.
#define PICO_NO_TRIGGER_CONDITIONS_SET							0x0000020CUL

// The number of trigger channel properties it outside the allowed range (is less than zero).
#define PICO_NO_OF_CHANNEL_TRIGGER_PROPERTIES_OUT_OF_RANGE 0x0000020DUL

// A probe has been plugged into a channel, but can not be identified correctly.
#define PICO_PROBE_COMPONENT_ERROR					0x0000020EUL

// The requested channel for ETS triggering is not supported.
#define PICO_INVALID_TRIGGER_CHANNEL_FOR_ETS              0x00000210UL

// While the device is streaming the get values method is not available
#define PICO_NOT_AVAILABLE_WHEN_STREAMING_IS_RUNNING 0x00000211UL

// the requested state is not one of the enSharedTriggerWithinPreTrigger values
#define PICO_INVALID_TRIGGER_WITHIN_PRE_TRIGGER_STATE 0x00000212UL

// the number of captures have to be greater than zero
#define PICO_ZERO_NUMBER_OF_CAPTURES_INVALID 0x00000213UL

// the trigger delay is greater than supported by the hardware
#define PICO_TRIGGER_DELAY_OUT_OF_RANGE 0x00000300UL

// the requested threshold direction is not allowed with the specified channel
#define PICO_INVALID_THRESHOLD_DIRECTION 0x00000301UL

// the requested threshold mode is not allowed with the specified channel
#define PICO_INVALID_THRESHOLD_MODE 0x00000302UL

// The device variant is not supported by this current driver.
#define PICO_INVALID_VARIANT															0x00001000UL

// The actual memory module does not match the expected memory module.
#define PICO_MEMORY_MODULE_ERROR													0x00001001UL

// A null pointer has been passed in the trigger function or one of the parameters is out of range.
#define PICO_PULSE_WIDTH_QUALIFIER_LOWER_UPPER_CONFILCT  0x00002000UL

// The pulse width qualifier type is not one of the listed options.
#define PICO_PULSE_WIDTH_QUALIFIER_TYPE  0x00002001UL

// The pulse width qualifier direction is not one of the listed options.
#define PICO_PULSE_WIDTH_QUALIFIER_DIRECTION 0x00002002UL

// The threshold range is not one of the listed options.
#define PICO_THRESHOLD_MODE_OUT_OF_RANGE 0x00002003UL

// The trigger direction and pulse width option conflict with each other.
#define PICO_TRIGGER_AND_PULSEWIDTH_DIRECTION_IN_CONFLICT 0x00002004UL

// The thresholds upper limits and thresholds lower limits conflict with each other.
#define PICO_THRESHOLD_UPPER_LOWER_MISMATCH 0x00002005UL

// The pulse width lower count is out of range.
#define PICO_PULSE_WIDTH_LOWER_OUT_OF_RANGE	0x00002006UL

// The pulse width upper count is out of range.
#define PICO_PULSE_WIDTH_UPPER_OUT_OF_RANGE 0x00002007UL

// The devices front panel has caused an error.
#define PICO_FRONT_PANEL_ERROR 0x00002008UL

// The actual and expected mode of the front panel do not match.
#define PICO_FRONT_PANEL_MODE 0x0000200BUL

// A front panel feature is not available or failed to configure.
#define PICO_FRONT_PANEL_FEATURE 0x0000200CUL

// When setting the pulse width conditions either the pointer is null or the number of conditions is set to zero.
#define PICO_NO_PULSE_WIDTH_CONDITIONS_SET	0x0000200DUL

// a trigger condition exists for a port, but the port has not been enabled
#define PICO_TRIGGER_PORT_NOT_ENABLED 0x0000200EUL

// a trigger condition exists for a port, but no digital channel directions have been set
#define PICO_DIGITAL_DIRECTION_NOT_SET 0x0000200FUL

#define PICO_I2C_DEVICE_INVALID_READ_COMMAND 0x00002010UL

#define PICO_I2C_DEVICE_INVALID_RESPONSE 0x00002011UL

#define PICO_I2C_DEVICE_INVALID_WRITE_COMMAND 0x00002012UL

#define PICO_I2C_DEVICE_ARGUMENT_OUT_OF_RANGE 0x00002013UL

// The actual and expected mode do not match.
#define PICO_I2C_DEVICE_MODE 0x00002014UL

// While trying to configure the device, set up failed.
#define PICO_I2C_DEVICE_SETUP_FAILED 0x00002015UL

// A feature is not available or failed to configure.
#define PICO_I2C_DEVICE_FEATURE 0x00002016UL

// The device did not pass the validation checks.
#define PICO_I2C_DEVICE_VALIDATION_FAILED 0x00002017UL

#define PICO_INTERNAL_HEADER_ERROR 0x00002018UL

// The device couldn't write the channel settings due to a hardware fault
#define PICO_FAILED_TO_WRITE_HARDWARE_FAULT 0x00002019UL

// The number of MSO's edge transitions being set is not supported by this device (RISING, FALLING, or RISING_OR_FALLING).
#define PICO_MSO_TOO_MANY_EDGE_TRANSITIONS_WHEN_USING_PULSE_WIDTH 0x00003000UL

// A probe LED position requested is not one of the available probe positions in the ProbeLedPosition enum.
#define PICO_INVALID_PROBE_LED_POSITION 0x00003001UL

// The LED position is not supported by the selected variant.
#define PICO_PROBE_LED_POSITION_NOT_SUPPORTED 0x00003002UL

// A channel has more than one of the same LED position in the ProbeChannelLedSetting struct.
#define PICO_DUPLICATE_PROBE_CHANNEL_LED_POSITION 0x00003003UL

// Setting the probes LED has failed.
#define PICO_PROBE_LED_FAILURE 0x00003004UL

// Probe is not supported by the selected variant.
#define PICO_PROBE_NOT_SUPPORTED_BY_THIS_DEVICE 0x00003005UL

// The probe name is not in the list of enPicoConnectProbe enums.
#define PICO_INVALID_PROBE_NAME 0x00003006UL

// The number of colour settings are zero or a null pointer passed to the function.
#define PICO_NO_PROBE_COLOUR_SETTINGS 0x00003007UL

// Channel has no probe connected to it.
#define PICO_NO_PROBE_CONNECTED_ON_REQUESTED_CHANNEL 0x00003008UL

// Connected probe does not require calibration.
#define PICO_PROBE_DOES_NOT_REQUIRE_CALIBRATION 0x00003009UL

// Connected probe could not be calibrated - hardware fault is a possible cause.
#define PICO_PROBE_CALIBRATION_FAILED 0x0000300AUL

// A probe has been connected, but the version is not recognised.
#define PICO_PROBE_VERSION_ERROR 0x0000300BUL

// The requested trigger time is to long for the selected variant.
#define PICO_AUTO_TRIGGER_TIME_TOO_LONG   0x00004000UL

// The MSO pod did not pass the validation checks.
#define PICO_MSO_POD_VALIDATION_FAILED 0x00005000UL

// No MSO pod found on the requested digital port.
#define PICO_NO_MSO_POD_CONNECTED 0x00005001UL

// the digital port enum value is not in the enPicoDigitalPortHysteresis declaration
#define PICO_DIGITAL_PORT_HYSTERESIS_OUT_OF_RANGE 0x00005002UL

#define PICO_MSO_POD_FAILED_UNIT 0x00005003UL

// The device's EEPROM is corrupt. Contact Pico Technology support: https://www.picotech.com/tech-support.
#define PICO_ATTENUATION_FAILED 0x00005004UL

// a channel set to the 50Ohm Path has Tripped due to the input signal
#define PICO_DC_50OHM_OVERVOLTAGE_TRIPPED 0x00005005UL

// The MSO pod over current protection activated, unplug and replug the MSO pod 
#define PICO_MSO_OVER_CURRENT_TRIPPED 0x00005006UL

// Status error for when the device has overheated.
#define PICO_NOT_RESPONDING_OVERHEATED 0x00005010UL

// waiting for the device to capture timed out
#define PICO_HARDWARE_CAPTURE_TIMEOUT 0x00006000UL

// waiting for the device be ready for capture timed out
#define PICO_HARDWARE_READY_TIMEOUT   0x00006001UL

// the driver is performing a capture requested by RunStreaming or RunBlock
// to interrupt this capture call Stop on the device first
#define PICO_HARDWARE_CAPTURING_CALL_STOP   0x00006002UL

// the number of samples is less than the minimum number allowed
#define PICO_TOO_FEW_REQUESTED_STREAMING_SAMPLES 0x00007000UL

// a streaming capture has been made but re-reading the data is not allowed
#define PICO_STREAMING_REREAD_DATA_NOT_AVAILABLE 0x00007001UL

// When requesting data only Raw and one of the following aggregation data types allowed
//   - PICO_RATIO_MODE_AGGREGATE (Min Max),
//     PICO_RATIO_MODE_DECIMATE,
//     PICO_RATIO_MODE_AVERAGE and/or PICO_RATIO_MODE_SUM,
//     PICO_RATIO_MODE_DISTRIBUTION
//
//	 average and sum are classed as one aggregation type
#define PICO_STREAMING_COMBINATION_OF_RAW_DATA_AND_ONE_AGGREGATION_DATA_TYPE_ALLOWED 0x00007002UL

// The time stamp per waveform segment has been reset.
#define PICO_DEVICE_TIME_STAMP_RESET							0x01000000UL

// When requesting the TriggerTimeOffset the trigger time has not been set.
#define PICO_TRIGGER_TIME_NOT_REQUESTED						0x02000001UL

// Trigger time buffer not set.
#define PICO_TRIGGER_TIME_BUFFER_NOT_SET          0x02000002UL

// The trigger time failed to be calculated.
#define PICO_TRIGGER_TIME_FAILED_TO_CALCULATE     0x02000004UL

// The trigger time failed to be calculated.
#define PICO_TRIGGER_WITHIN_A_PRE_TRIGGER_FAILED_TO_CALCULATE 0x02000008UL

// The trigger time stamp was not requested.
#define PICO_TRIGGER_TIME_STAMP_NOT_REQUESTED			0x02000100UL

// RATIO_MODE_TRIGGER_DATA_FOR_TIME_CALCULATION cannot have a buffer set
#define PICO_RATIO_MODE_TRIGGER_DATA_FOR_TIME_CALCULATION_DOES_NOT_REQUIRE_BUFFERS 0x02200000UL

// it is not possible to set a buffer for RATIO_MODE_TRIGGER_DATA_FOR_TIME_CALCULATION therefore
// information is not available pertaining to samples
#define PICO_RATIO_MODE_TRIGGER_DATA_FOR_TIME_CALCULATION_DOES_NOT_HAVE_BUFFERS 0x02200001UL

// to get the trigger time use either GetTriggerInfo or GetTriggerTimeOffset api calls
#define PICO_RATIO_MODE_TRIGGER_DATA_FOR_TIME_CALCULATION_USE_GETTRIGGERINFO 0x02200002UL


// PICO_RATIO_MDOE_TRIGGER and RATIO_MODE_TRIGGER_DATA_FOR_TIME_CALCULATION is not supported in streaming capture
#define PICO_STREAMING_DOES_NOT_SUPPORT_TRIGGER_RATIO_MODES 0x02200003UL

// only the PICO_TRIGGER_READ may be used to read PICO_RATIO_MODE_TRIGGER, and PICO_RATIO_MODE_TRIGGER_FOR_CALCULATION
#define PICO_USE_THE_TRIGGER_READ 0x02200004UL

// one of the PICO_DATA_READs should be used to read:
// PICO_RATIO_MODE_RAW
// PICO_RATIO_MODE_AGGREGATE
// PICO_RATIO_MODE_DECIMATE
// PICO_RATIO_MODE_AVERAGE
#define PICO_USE_A_DATA_READ 0x02200005UL

// trigger data always requires a PICO_INT16_T data type
#define PICO_TRIGGER_READ_REQUIRES_INT16_T_DATA_TYPE 0x02200006UL

// a ratio mode passed to the API call requires the number of samples to be greater than zero
#define PICO_RATIO_MODE_REQUIRES_NUMBER_OF_SAMPLES_TO_BE_SET 0x02200007UL

// Attempted to set up the signal generator with an inconsistent configuration.
#define PICO_SIGGEN_SETTINGS_MISMATCH             0x03000010UL

// The signal generator has been partially reconfigured and the new settings must be applied before it can be paused or restarted.
#define PICO_SIGGEN_SETTINGS_CHANGED_CALL_APPLY   0x03000011UL

// The wave type is not listed in enPicoWaveType.
#define PICO_SIGGEN_WAVETYPE_NOT_SUPPORTED        0x03000012UL

// The trigger type is not listed in enSigGenTrigType.
#define PICO_SIGGEN_TRIGGERTYPE_NOT_SUPPORTED     0x03000013UL

// The trigger source is not listed in enSigGenTrigSource.
#define PICO_SIGGEN_TRIGGERSOURCE_NOT_SUPPORTED   0x03000014UL

// The filter state is not listed in enPicoSigGenFilterState.
#define PICO_SIGGEN_FILTER_STATE_NOT_SUPPORTED    0x03000015UL

// The arbitrary waveform buffer is a null pointer.
#define PICO_SIGGEN_NULL_PARAMETER                0x03000020UL

// The arbitrary waveform buffer length is zero.
#define PICO_SIGGEN_EMPTY_BUFFER_SUPPLIED         0x03000021UL

// The sig gen voltage offset and peak to peak have not been set.
#define PICO_SIGGEN_RANGE_NOT_SUPPLIED            0x03000022UL

// The sig gen arbitrary waveform buffer not been set.
#define PICO_SIGGEN_BUFFER_NOT_SUPPLIED           0x03000023UL

// The sig gen frequency have not been set.
#define PICO_SIGGEN_FREQUENCY_NOT_SUPPLIED        0x03000024UL

// The sig gen sweep information has not been set.
#define PICO_SIGGEN_SWEEP_INFO_NOT_SUPPLIED       0x03000025UL

// The sig gen trigger information has not been set.
#define PICO_SIGGEN_TRIGGER_INFO_NOT_SUPPLIED     0x03000026UL

// The sig gen clock frequency have not been set.
#define PICO_SIGGEN_CLOCK_FREQ_NOT_SUPPLIED       0x03000027UL

// The sig gen arbitrary waveform buffer length is too long.
#define PICO_SIGGEN_TOO_MANY_SAMPLES              0x03000030UL

// The duty cycle value is out of range.
#define PICO_SIGGEN_DUTYCYCLE_OUT_OF_RANGE        0x03000031UL

// The number of cycles is out of range.
#define PICO_SIGGEN_CYCLES_OUT_OF_RANGE           0x03000032UL

// The pre-scaler is out of range.
#define PICO_SIGGEN_PRESCALE_OUT_OF_RANGE         0x03000033UL

// The sweep type is not listed in enPicoSweepType.
#define PICO_SIGGEN_SWEEPTYPE_INVALID             0x03000034UL

// A mismatch has occurred while checking the sweeps wave type.
#define PICO_SIGGEN_SWEEP_WAVETYPE_MISMATCH       0x03000035UL

// The sweeps or shots and trigger type are not valid when combined together.
#define PICO_SIGGEN_INVALID_SWEEP_PARAMETERS      0x03000036UL

// The sweep and prescaler are not valid when combined together.
#define PICO_SIGGEN_SWEEP_PRESCALE_NOT_SUPPORTED  0x03000037UL

// The potential applied to the AWG output exceeds the maximum voltage range of the AWG.
#define PICO_AWG_OVER_VOLTAGE_RANGE               0x03000038UL

// The reference signal cannot be locked to.
#define PICO_NOT_LOCKED_TO_REFERENCE_FREQUENCY  0x03000039UL

// (Linux only.) udev rules are incorrectly configured. The user does
// not have read/write permissions on the device's file descriptor.
#define PICO_PERMISSIONS_ERROR  0x03000040UL

// The digital ports without analog channels are only allowed in 8-bit resolution.
#define PICO_PORTS_WITHOUT_ANALOGUE_CHANNELS_ONLY_ALLOWED_IN_8BIT_RESOLUTION 0x03001000UL

#define PICO_ANALOGUE_FRONTEND_MISSING 0x03003001UL
#define PICO_FRONT_PANEL_MISSING 0x03003002UL
#define PICO_ANALOGUE_FRONTEND_AND_FRONT_PANEL_MISSING 0x03003003UL

// The digital board has reported an error to the driver
#define PICO_DIGITAL_BOARD_HARDWARE_ERROR 0x03003800UL

// checking if the firmware needs updating the updateRequired parameter is null
#define PICO_FIRMWARE_UPDATE_REQUIRED_TO_USE_DEVICE_WITH_THIS_DRIVER		          0x03004000UL
#define PICO_UPDATE_REQUIRED_NULL																				          0x03004001UL
#define PICO_FIRMWARE_UP_TO_DATE																				          0x03004002UL
#define PICO_FLASH_FAIL																									          0x03004003UL
#define PICO_INTERNAL_ERROR_FIRMWARE_LENGTH_INVALID											          0x03004004UL
#define PICO_INTERNAL_ERROR_FIRMWARE_NULL																          0x03004005UL
#define PICO_FIRMWARE_FAILED_TO_BE_CHANGED															          0x03004006UL
#define PICO_FIRMWARE_FAILED_TO_RELOAD																	          0x03004007UL
#define PICO_FIRMWARE_FAILED_TO_BE_UPDATE																          0x03004008UL
#define PICO_FIRMWARE_VERSION_OUT_OF_RANGE															          0x03004009UL

#define PICO_OPTIONAL_BOOTLOADER_UPDATE_AVAILABLE_WITH_THIS_DRIVER	0x03005000UL
#define PICO_BOOTLOADER_VERSION_NOT_AVAILABLE 0x03005001UL

#define PICO_NO_APPS_AVAILABLE                                          0x03008000UL
#define PICO_UNSUPPORTED_APP                                            0x03008001UL

// the adc is powered down when trying to capture data
#define PICO_ADC_POWERED_DOWN 0x03002000UL

// An internal error has occurred and a watchdog timer has been called.
#define PICO_WATCHDOGTIMER                        0x10000000UL

// The picoipp.dll has not been found.
#define PICO_IPP_NOT_FOUND                				0x10000001UL

// A function in the picoipp.dll does not exist.
#define PICO_IPP_NO_FUNCTION					            0x10000002UL

// The Pico IPP call has failed.
#define PICO_IPP_ERROR					                  0x10000003UL

// Shadow calibration is not available on this device.
#define PICO_SHADOW_CAL_NOT_AVAILABLE             0x10000004UL

// Shadow calibration is currently disabled.
#define PICO_SHADOW_CAL_DISABLED                  0x10000005UL

// Shadow calibration error has occurred.
#define PICO_SHADOW_CAL_ERROR                     0x10000006UL

// The shadow calibration is corrupt.
#define PICO_SHADOW_CAL_CORRUPT                   0x10000007UL

// The memory on board the device has overflowed.
#define PICO_DEVICE_MEMORY_OVERFLOW               0x10000008UL

//The device Adc test failed.
#define PICO_ADC_TEST_FAILURE                     0x10000010UL

#define PICO_RESERVED_1														0x11000000UL

// The PicoSource device is not ready to accept instructions.
#define PICO_SOURCE_NOT_READY											0x20000000UL
#define PICO_SOURCE_INVALID_BAUD_RATE							0x20000001UL
#define PICO_SOURCE_NOT_OPENED_FOR_WRITE					0x20000002UL
#define PICO_SOURCE_FAILED_TO_WRITE_DEVICE				0x20000003UL
#define PICO_SOURCE_EEPROM_FAIL										0x20000004UL
#define PICO_SOURCE_EEPROM_NOT_PRESENT 						0x20000005UL
#define PICO_SOURCE_EEPROM_NOT_PROGRAMMED					0x20000006UL
#define PICO_SOURCE_LIST_NOT_READY								0x20000007UL
#define PICO_SOURCE_FTD2XX_NOT_FOUND							0x20000008UL
#define PICO_SOURCE_FTD2XX_NO_FUNCTION						0x20000009UL

typedef uint32_t PICO_STATUS;

typedef enum enPicoStringValue
{
	PICO_SV_MEMORY,
	PICO_SV_MEMORY_NO_OF_SEGMENTS,
	PICO_SV_MEMORY_MAX_SAMPLES,

	PICO_SV_NO_OF_CHANNELS,
	PICO_SV_ARRAY_OF_CHANNELS,
	PICO_SV_CHANNEL,
	PICO_SV_CHANNEL_NAME,
	PICO_SV_CHANNEL_RANGE,
	PICO_SV_CHANNEL_COUPLING,
	PICO_SV_CHANNEL_ENABLED,
	PICO_SV_CHANNEL_ANALOGUE_OFFSET,
	PICO_SV_CHANNEL_FILTER,

	PICO_SV_TRIGGER,
	PICO_SV_TRIGGER_AUXIO_OUTPUT_ENABLED,
	PICO_SV_TRIGGER_AUTO_TRIGGER_MICROSECONDS,

	PICO_SV_TRIGGER_PROPERTIES,
	PICO_SV_NO_OF_TRIGGER_PROPERTIES,

	PICO_SV_TRIGGER_PROPERTIES_CHANNEL,
	PICO_SV_TRIGGER_PROPERTIES_THRESHOLD_UPPER,
	PICO_SV_TRIGGER_PROPERTIES_THRESHOLD_UPPER_HYSTERESIS,
	PICO_SV_TRIGGER_PROPERTIES_THRESHOLD_LOWER,
	PICO_SV_TRIGGER_PROPERTIES_THRESHOLD_LOWER_HYSTERESIS,
	PICO_SV_TRIGGER_PROPERTIES_THRESHOLD_MODE,

	PICO_SV_TRIGGER_ARRAY_OF_BLOCK_CONDITIONS,
	PICO_SV_TRIGGER_NO_OF_BLOCK_CONDITIONS,
	PICO_SV_TRIGGER_CONDITIONS,
	PICO_SV_TRIGGER_NO_OF_CONDITIONS,
	PICO_SV_TRIGGER_CONDITION_SOURCE,
	PICO_SV_TRIGGER_CONDITION_STATE,

	PICO_SV_TRIGGER_DIRECTION,
	PICO_SV_TRIGGER_NO_OF_DIRECTIONS,
	PICO_SV_TRIGGER_DIRECTION_CHANNEL,
	PICO_SV_TRIGGER_DIRECTION_DIRECTION,

	PICO_SV_TRIGGER_DELAY,
	PICO_SV_TRIGGER_DELAY_MS,

	PICO_SV_FREQUENCY_COUNTER,
	PICO_SV_FREQUENCY_COUNTER_ENABLED,
	PICO_SV_FREQUENCY_COUNTER_CHANNEL,
	PICO_SV_FREQUENCY_COUNTER_RANGE,
	PICO_SV_FREQUENCY_COUNTER_TRESHOLDMAJOR,
	PICO_SV_FREQUENCY_COUNTER_TRESHOLDMINOR,

	PICO_SV_PULSE_WIDTH_PROPERTIES,
	PICO_SV_PULSE_WIDTH_PROPERTIES_DIRECTION,
	PICO_SV_PULSE_WIDTH_PROPERTIES_LOWER,
	PICO_SV_PULSE_WIDTH_PROPERTIES_UPPER,
	PICO_SV_PULSE_WIDTH_PROPERTIES_TYPE,

	PICO_SV_PULSE_WIDTH_ARRAY_OF_BLOCK_CONDITIONS,
	PICO_SV_PULSE_WIDTH_NO_OF_BLOCK_CONDITIONS,
	PICO_SV_PULSE_WIDTH_CONDITIONS,
	PICO_SV_PULSE_WIDTH_NO_OF_CONDITIONS,
	PICO_SV_PULSE_WIDTH_CONDITIONS_SOURCE,
	PICO_SV_PULSE_WIDTH_CONDITIONS_STATE,

	PICO_SV_SAMPLE_PROPERTIES,
	PICO_SV_SAMPLE_PROPERTIES_PRE_TRIGGER_SAMPLES,
	PICO_SV_SAMPLE_PROPERTIES_POST_TRIGGER_SAMPLES,
	PICO_SV_SAMPLE_PROPERTIES_TIMEBASE,
	PICO_SV_SAMPLE_PROPERTIES_NO_OF_CAPTURES,
	PICO_SV_SAMPLE_PROPERTIES_RESOLUTION,

	PICO_SV_SAMPLE_PROPERTIES_OVERLAPPED,
	PICO_SV_SAMPLE_PROPERTIES_OVERLAPPED_DOWN_SAMPLE_RATIO,
	PICO_SV_SAMPLE_PROPERTIES_OVERLAPPED_DOWN_SAMPLE_RATIO_MODE,
	PICO_SV_SAMPLE_PROPERTIES_OVERLAPPED_REQUERSTED_NO_OF_SAMPLES,
	PICO_SV_SAMPLE_PROPERTIES_OVERLAPPED_SEGMENT_INDEX_FROM,
	PICO_SV_SAMPLE_PROPERTIES_OVERLAPPED_SEGMENT_INDEX_TO,

	PICO_SV_SIGNAL_GENERATOR,
	PICO_SV_SIGNAL_GENERATOR_BUILT_IN,
	PICO_SV_SIGNAL_GENERATOR_BUILT_IN_WAVE_TYPE,
	PICO_SV_SIGNAL_GENERATOR_BUILT_IN_START_FREQUENCY,
	PICO_SV_SIGNAL_GENERATOR_BUILT_IN_STOP_FREQUENCY,
	PICO_SV_SIGNAL_GENERATOR_BUILT_IN_INCREMENT,
	PICO_SV_SIGNAL_GENERATOR_BUILT_IN_DWELL_TIME,
	PICO_SV_SIGNAL_GENERATOR_AWG,
	PICO_SV_SIGNAL_GENERATOR_AWG_START_DELTA_PHASE,
	PICO_SV_SIGNAL_GENERATOR_AWG_STOP_DELTA_PHASE,
	PICO_SV_SIGNAL_GENERATOR_AWG_DELTA_PHASE_INCREMENT,
	PICO_SV_SIGNAL_GENERATOR_AWG_DWELL_COUNT,
	PICO_SV_SIGNAL_GENERATOR_AWG_INDEX_MODE,
	PICO_SV_SIGNAL_GENERATOR_AWG_WAVEFORM_SIZE,
	PICO_SV_SIGNAL_GENERATOR_ARRAY_OF_AWG_WAVEFORM_VALUES,
	PICO_SV_SIGNAL_GENERATOR_OFFSET_VOLTAGE,
	PICO_SV_SIGNAL_GENERATOR_PK_TO_PK,
	PICO_SV_SIGNAL_GENERATOR_OPERATION,
	PICO_SV_SIGNAL_GENERATOR_SHOTS,
	PICO_SV_SIGNAL_GENERATOR_SWEEPS,
	PICO_SV_SIGNAL_GENERATOR_SWEEP_TYPE,
	PICO_SV_SIGNAL_GENERATOR_TRIGGER_TYPE,
	PICO_SV_SIGNAL_GENERATOR_TRIGGER_SOURCE,
	PICO_SV_SIGNAL_GENERATOR_EXT_IN_THRESHOLD,

	PICO_SV_ETS,
	PICO_SV_ETS_STATE,
	PICO_SV_ETS_CYCLE,
	PICO_SV_ETS_INTERLEAVE,
	PICO_SV_ETS_SAMPLE_TIME_PICOSECONDS

} PICO_STRING_VALUE;

#endif
