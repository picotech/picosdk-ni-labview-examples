/****************************************************************************
 *
 * Filename:    ps6000aApi.h
 * Copyright:   Pico Technology Limited 2002 - 2022
 * Description:
 *
 * This header defines the interface to driver routines for the
 *  PicoScope 6000 range of PC Oscilloscopes.
 *
 ****************************************************************************/
#ifndef __PS6000AAPI_H__
#define __PS6000AAPI_H__

#include <stdint.h>

#include "PicoStatus.h"
#include "PicoDeviceEnums.h"
#include "PicoDeviceStructs.h"
#include "PicoCallback.h"
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
	 //If you are dynamically linking PS6000A.DLL into your project #define DYNLINK here>
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

typedef void (PREF4 *ps6000aBlockReady)
(
	int16_t				handle,
	PICO_STATUS		status,
	PICO_POINTER	pParameter
	);

typedef void (PREF4 *ps6000aDataReady)
(
	int16_t    					handle,
	PICO_STATUS					status,
	uint64_t     				noOfSamples,
	int16_t    					overflow,
	PICO_POINTER				pParameter
	);

typedef void (PREF4 *ps6000aProbeInteractions)
(
	int16_t    											handle,
	PICO_STATUS											status,
	PICO_USER_PROBE_INTERACTIONS *	probes,
	uint32_t												nProbes
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000aOpenUnit)
(
	int16_t										*	handle,
	int8_t										*	serial,
	PICO_DEVICE_RESOLUTION		resolution
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000aOpenUnitAsync)
(
	int16_t										*	status,
	int8_t										*	serial,
	PICO_DEVICE_RESOLUTION		resolution
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000aOpenUnitProgress)
(
	int16_t *	handle,
	int16_t *	progressPercent,
	int16_t *	complete
);

// This function retrieves information about the specified oscilloscope or driver software.
// If the device fails to open or no device is opened, it is still possible to read the driver version.
//
// parameters:
// handle: identifies the device from which information is required. If an invalid handle is passed, only the driver versions can be read.
// string: on exit, the unit information string selected specified by the info argument. If string is NULL, only requiredSize is returned.
// stringLength: the maximum number of 8-bit integers (int8_t) that may be written to string.
// requiredSize: on exit, the required length of the string array.
// info: a number specifying what information is required.
//
// return:
// PICO_OK
// PICO_INVALID_HANDLE
// PICO_NULL_PARAMETER
// PICO_INVALID_INFO
// PICO_INFO_UNAVAILABLE
// PICO_DRIVER_FUNCTION
PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aGetUnitInfo)
(
	int16_t				handle,
	int8_t			*	string,
	int16_t				stringLength,
	int16_t     *	requiredSize,
	PICO_INFO			info
);

// This function retrieves information about the accessory (probe, or MSO Pod) attached to the specified channel.
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
// PICO_NOT_SUPPORTED_BY_THIS_DEVICE (no accessory is connected, or the connected accessory does not support any info.)
// PICO_DRIVER_FUNCTION (another thread is already calling a driver function.)
PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aGetAccessoryInfo)
(
	int16_t				handle,
	PICO_CHANNEL	channel,
	int8_t			* string,
	int16_t				stringLength,
	int16_t			* requiredSize,
	PICO_INFO			info
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (ps6000aCloseUnit)
(
	int16_t handle
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aFlashLed)
(
	int16_t handle,
	int16_t start
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aMemorySegments)
(
	int16_t     handle,
	uint64_t		nSegments,
	uint64_t *	nMaxSamples
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aMemorySegmentsBySamples)
(
	int16_t			handle,
	uint64_t 		nSamples,
	uint64_t	* nMaxSegments
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aGetMaximumAvailableMemory)
(
	int16_t     handle,
	uint64_t *	nMaxSamples,
	PICO_DEVICE_RESOLUTION resolution
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aQueryMaxSegmentsBySamples)
(
	int16_t handle,
	uint64_t nSamples,
	uint32_t nChannelEnabled,
	uint64_t * nMaxSegments,
	PICO_DEVICE_RESOLUTION resolution
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aSetChannelOn)
(
	int16_t                       handle,
	PICO_CHANNEL                  channel,
	PICO_COUPLING                 coupling,
	PICO_CONNECT_PROBE_RANGE      range,
	double                        analogueOffset,
	PICO_BANDWIDTH_LIMITER        bandwidth
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aSetChannelOff)
(
  int16_t                       handle,
  PICO_CHANNEL                  channel
  );

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aSetDigitalPortOn)
(
	int16_t					              handle,
	PICO_CHANNEL		              port,
	int16_t *				              logicThresholdLevel,
	int16_t					              logicThresholdLevelLength,
	PICO_DIGITAL_PORT_HYSTERESIS  hysteresis
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aSetDigitalPortOff)
(
  int16_t					              handle,
  PICO_CHANNEL		              port
  );

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aGetTimebase)
(
	int16_t         handle,
	uint32_t				timebase,
	uint64_t				noSamples,
	double        *	timeIntervalNanoseconds,
	uint64_t			*	maxSamples,
	uint64_t			  segmentIndex
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aSigGenWaveform)
(
	int16_t						handle,
	PICO_WAVE_TYPE		waveType,
	int16_t					* buffer,
	uint64_t					bufferLength
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aSigGenRange)
(
	int16_t         handle,
	double          peakToPeakVolts,
	double          offsetVolts
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aSigGenWaveformDutyCycle)
(
	int16_t					handle,
	double				  dutyCyclePercent
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aSigGenTrigger)
(
	int16_t											handle,
	PICO_SIGGEN_TRIG_TYPE				triggerType,
	PICO_SIGGEN_TRIG_SOURCE			triggerSource,
	uint64_t										cycles,
	uint64_t                    autoTriggerPicoSeconds
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aSigGenFilter)
(
	int16_t											handle,
	PICO_SIGGEN_FILTER_STATE		filterState
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aSigGenFrequency)
(
	int16_t							handle,
	double							frequencyHz
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aSigGenFrequencySweep)
(
	int16_t							handle,
	double						  stopFrequencyHz,
	double							frequencyIncrement,
	double							dwellTimeSeconds,
	PICO_SWEEP_TYPE			sweepType
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aSigGenPhase)
(
	int16_t							handle,
	uint64_t						deltaPhase
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aSigGenPhaseSweep)
(
	int16_t							handle,
	uint64_t						stopDeltaPhase,
	uint64_t						deltaPhaseIncrement,
	uint64_t						dwellCount,
	PICO_SWEEP_TYPE			sweepType
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aSigGenClockManual)
(
	int16_t							handle,
	double							dacClockFrequency,
	uint64_t						prescaleRatio
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aSigGenSoftwareTriggerControl)
(
	int16_t										handle,
	PICO_SIGGEN_TRIG_TYPE			triggerState
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aSigGenApply)
(
	int16_t							handle,
	int16_t             sigGenEnabled,
	int16_t             sweepEnabled,
	int16_t             triggerEnabled,
	int16_t							automaticClockOptimisationEnabled,
  int16_t             overrideAutomaticClockAndPrescale,
	double						* frequency,
	double						* stopFrequency,
	double						* frequencyIncrement,
	double						* dwellTime
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aSigGenLimits)
(
	int16_t							     handle,
	PICO_SIGGEN_PARAMETER    parameter,
	double                 * minimumPermissibleValue,
	double                 * maximumPermissibleValue,
	double                 * step
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aSigGenFrequencyLimits)
(
	int16_t							     handle,
  PICO_WAVE_TYPE           waveType,
  uint64_t               * numSamples,
  double                 * startFrequency,
  int16_t                  sweepEnabled,
  double                 * manualDacClockFrequency,
  uint64_t               * manualPrescaleRatio,
  double                 * maxStopFrequencyOut,
  double                 * minFrequencyStepOut,
  double                 * maxFrequencyStepOut,
  double                 * minDwellTimeOut,
  double                 * maxDwellTimeOut
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aSigGenPause)
(
	int16_t										handle
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aSigGenRestart)
(
	int16_t										handle
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aSetSimpleTrigger)
(
	int16_t                   handle,
	int16_t                   enable,
	PICO_CHANNEL              source,
	int16_t                   threshold,
	PICO_THRESHOLD_DIRECTION  direction,
	uint64_t									delay,
	uint32_t                  autoTriggerMicroSeconds
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aTriggerWithinPreTriggerSamples)
(
  int16_t handle,
  PICO_TRIGGER_WITHIN_PRE_TRIGGER state
  );

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aSetTriggerChannelProperties)
(
	int16_t                           handle,
	PICO_TRIGGER_CHANNEL_PROPERTIES *	channelProperties,
	int16_t                           nChannelProperties,
	int16_t                           auxOutputEnable,
	uint32_t                          autoTriggerMicroSeconds
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aSetTriggerChannelConditions)
(
	int16_t						handle,
	PICO_CONDITION	*	conditions,
	int16_t						nConditions,
	PICO_ACTION				action
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aSetTriggerChannelDirections)
(
	int16_t											handle,
	PICO_DIRECTION					*		directions,
	int16_t											nDirections
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aSetTriggerDelay)
(
	int16_t   handle,
	uint64_t  delay
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aSetPulseWidthQualifierProperties)
(
	int16_t											handle,
	uint32_t										lower,
	uint32_t										upper,
	PICO_PULSE_WIDTH_TYPE				type
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aSetPulseWidthQualifierConditions)
(
	int16_t						handle,
	PICO_CONDITION	*	conditions,
	int16_t						nConditions,
	PICO_ACTION				action
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aSetPulseWidthQualifierDirections)
(
	int16_t											handle,
	PICO_DIRECTION					*		directions,
	int16_t											nDirections
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aSetTriggerDigitalPortProperties)
(
  int16_t handle,
  PICO_CHANNEL port,
  PICO_DIGITAL_CHANNEL_DIRECTIONS * directions,
  int16_t														nDirections
  );

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aSetPulseWidthDigitalPortProperties)
(
  int16_t handle,
  PICO_CHANNEL port,
  PICO_DIGITAL_CHANNEL_DIRECTIONS* directions,
  int16_t														nDirections
  );

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aGetTriggerTimeOffset)
(
	int16_t           handle,
	int64_t         *	time,
	PICO_TIME_UNITS *	timeUnits,
	uint64_t					segmentIndex
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aGetValuesTriggerTimeOffsetBulk)
(
	int16_t             handle,
	int64_t           *	times,
	PICO_TIME_UNITS		*	timeUnits,
	uint64_t						fromSegmentIndex,
	uint64_t						toSegmentIndex
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aSetDataBuffer)
(
	int16_t								handle,
	PICO_CHANNEL					channel,
	PICO_POINTER					buffer,
	int32_t								nSamples,
	PICO_DATA_TYPE				dataType,
	uint64_t							waveform,
	PICO_RATIO_MODE				downSampleRatioMode,
	PICO_ACTION						action
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aSetDataBuffers)
(
	int16_t           handle,
	PICO_CHANNEL			channel,
	PICO_POINTER			bufferMax,
	PICO_POINTER			bufferMin,
	int32_t						nSamples,
	PICO_DATA_TYPE		dataType,
	uint64_t					waveform,
	PICO_RATIO_MODE		downSampleRatioMode,
	PICO_ACTION				action
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aRunBlock)
(
	int16_t							handle,
	uint64_t						noOfPreTriggerSamples,
	uint64_t						noOfPostTriggerSamples,
	uint32_t						timebase,
	double           *	timeIndisposedMs,
	uint64_t						segmentIndex,
	ps6000aBlockReady		lpReady,
	PICO_POINTER				pParameter
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aIsReady)
(
	int16_t   handle,
	int16_t * ready
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aRunStreaming)
(
	int16_t           handle,
	double				*	sampleInterval,
	PICO_TIME_UNITS		sampleIntervalTimeUnits,
	uint64_t					maxPreTriggerSamples,
	uint64_t					maxPostPreTriggerSamples,
	int16_t           autoStop,
	uint64_t					downSampleRatio,
	PICO_RATIO_MODE		downSampleRatioMode
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aGetStreamingLatestValues)
(
	int16_t															handle,
	PICO_STREAMING_DATA_INFO					*	streamingDataInfo,
	uint64_t														nStreamingDataInfos,
	PICO_STREAMING_DATA_TRIGGER_INFO	* triggerInfo
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aNoOfStreamingValues)
(
	int16_t     handle,
	uint64_t *	noOfValues
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aGetValues)
(
	int16_t           handle,
	uint64_t					startIndex,
	uint64_t				*	noOfSamples,
	uint64_t					downSampleRatio,
	PICO_RATIO_MODE		downSampleRatioMode,
	uint64_t					segmentIndex,
	int16_t         *	overflow
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aGetValuesBulk)
(
	int16_t           handle,
	uint64_t					startIndex,
	uint64_t				*	noOfSamples,
	uint64_t					fromSegmentIndex,
	uint64_t					toSegmentIndex,
	uint64_t					downSampleRatio,
	PICO_RATIO_MODE		downSampleRatioMode,
	int16_t         *	overflow
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aGetValuesAsync)
(
	int16_t           handle,
	uint64_t					startIndex,
	uint64_t					noOfSamples,
	uint64_t					downSampleRatio,
	PICO_RATIO_MODE		downSampleRatioMode,
	uint64_t					segmentIndex,
	PICO_POINTER			lpDataReady,
	PICO_POINTER			pParameter
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aGetValuesBulkAsync)
(
	int16_t           handle,
	uint64_t					startIndex,
	uint64_t					noOfSamples,
	uint64_t					fromSegmentIndex,
	uint64_t					toSegmentIndex,
	uint64_t					downSampleRatio,
	PICO_RATIO_MODE		downSampleRatioMode,
	PICO_POINTER			lpDataReady,
	PICO_POINTER			pParameter
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aGetValuesOverlapped)
(
	int16_t           handle,
	uint64_t					startIndex,
	uint64_t				*	noOfSamples,
	uint64_t					downSampleRatio,
	PICO_RATIO_MODE		downSampleRatioMode,
	uint64_t					fromSegmentIndex,
	uint64_t					toSegmentIndex,
	int16_t         *	overflow
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aStopUsingGetValuesOverlapped)
(
  int16_t           handle
  );

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aGetNoOfCaptures)
(
	int16_t     handle,
	uint64_t *	nCaptures
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aGetNoOfProcessedCaptures)
(
	int16_t     handle,
	uint64_t *	nProcessedCaptures
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aStop)
(
	int16_t  handle
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aSetNoOfCaptures)
(
	int16_t   handle,
	uint64_t  nCaptures
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aGetTriggerInfo)
(
	int16_t									handle,
	PICO_TRIGGER_INFO			*	triggerInfo,
	uint64_t								firstSegmentIndex,
	uint64_t								segmentCount
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aEnumerateUnits)
(
	int16_t *	count,
	int8_t  *	serials,
	int16_t *	serialLth
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aPingUnit)
(
	int16_t  handle
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aGetAnalogueOffsetLimits)
(
  int16_t                     handle,
  PICO_CONNECT_PROBE_RANGE    range,
  PICO_COUPLING               coupling,
  double                      * maximumVoltage,
  double                      * minimumVoltage
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aGetMinimumTimebaseStateless)
(
	int16_t                     handle,
  PICO_CHANNEL_FLAGS          enabledChannelFlags,
	uint32_t                    * timebase,
	double                      * timeInterval,
	PICO_DEVICE_RESOLUTION      resolution
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aNearestSampleIntervalStateless)
(
	int16_t                 handle,
  PICO_CHANNEL_FLAGS      enabledChannelFlags,
	double		              timeIntervalRequested,
	PICO_DEVICE_RESOLUTION  resolution,
	uint32_t	            * timebase,
	double		            * timeIntervalAvailable
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aChannelCombinationsStateless)
(
	int16_t   handle,
	PICO_CHANNEL_FLAGS * channelFlagsCombinations,
	uint32_t * nChannelCombinations,
	PICO_DEVICE_RESOLUTION resolution,
	uint32_t timebase
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aSetDeviceResolution)
(
	int16_t  handle,
	PICO_DEVICE_RESOLUTION resolution
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aGetDeviceResolution)
(
	int16_t  handle,
	PICO_DEVICE_RESOLUTION * resolution
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aQueryOutputEdgeDetect)
(
	int16_t		handle,
	int16_t * state
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aSetOutputEdgeDetect)
(
	int16_t	handle,
	int16_t state
	);


PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aGetScalingValues)
(
	int16_t	handle,
	PICO_SCALING_FACTORS_VALUES *scalingValues,
	int16_t nChannels
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aGetAdcLimits)
(
	int16_t   handle,
	PICO_DEVICE_RESOLUTION resolution,
	int16_t * minValue,
	int16_t * maxValue
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aCheckForUpdate)
(
	int16_t	handle,
	PICO_FIRMWARE_INFO* firmwareInfos,
	int16_t* nFirmwareInfos,
	uint16_t* updatesRequired
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aStartFirmwareUpdate)
(
	int16_t	handle,
	PicoUpdateFirmwareProgress progress
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aResetChannelsAndReportAllChannelsOvervoltageTripStatus)(
  int16_t handle,
  PICO_CHANNEL_OVERVOLTAGE_TRIPPED* allChannelsTrippedStatus,
  uint8_t nChannelTrippedStatus);

PREF0 PREF1 PICO_STATUS PREF2
  PREF3(ps6000aReportAllChannelsOvervoltageTripStatus)(int16_t handle,
                                                       PICO_CHANNEL_OVERVOLTAGE_TRIPPED* allChannelsTrippedStatus,
                                                       uint8_t nChannelTrippedStatus);

#endif
