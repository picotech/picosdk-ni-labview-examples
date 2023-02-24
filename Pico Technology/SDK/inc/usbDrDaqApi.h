/**************************************************************************
*
* Filename:    usbDrDaqApi.h
* Author:      RPM & MAS
* Description:
*
* This header defines the interface to driver routines for the
* USB DrDAQ Data Logger.
*
* Copyright © 2010-2018 Pico Technology Ltd. All rights reserved.
*
*************************************************************************/
#ifndef __USBDRDAQAPI_H__
#define  __USBDRDAQAPI_H__

#include <stdint.h>

#define USB_DRDAQ_MAX_AWG_VALUE 1000

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

//	If you are dynamically linking usbdrdaq.dll into your project #define DYNLINK
//  somewhere in your project before here.
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

typedef enum enUsbDrDaqInputs
{
 	USB_DRDAQ_CHANNEL_EXT1 = 1,				//Ext. sensor 1
  USB_DRDAQ_CHANNEL_EXT2,						//Ext. sensor 2
  USB_DRDAQ_CHANNEL_EXT3,						//Ext. sensor 3
	USB_DRDAQ_CHANNEL_SCOPE,					//Scope channel
  USB_DRDAQ_CHANNEL_PH,							//PH
	USB_DRDAQ_CHANNEL_RES,						//Resistance
  USB_DRDAQ_CHANNEL_LIGHT,					//Light
	USB_DRDAQ_CHANNEL_TEMP,						//Thermistor
  USB_DRDAQ_CHANNEL_MIC_WAVE,				//Microphone waveform
	USB_DRDAQ_CHANNEL_MIC_LEVEL,			//Microphone level
	USB_DRDAQ_MAX_CHANNELS = USB_DRDAQ_CHANNEL_MIC_LEVEL
} USB_DRDAQ_INPUTS;

typedef enum enUsbDrDaqScopeRange
{
	USB_DRDAQ_1V25,
	USB_DRDAQ_2V5,
	USB_DRDAQ_5V,
	USB_DRDAQ_10V
}USB_DRDAQ_SCOPE_RANGE;

typedef enum enUsbDrDaqWave
{
	USB_DRDAQ_SINE,
	USB_DRDAQ_SQUARE,
	USB_DRDAQ_TRIANGLE,
	USB_DRDAQ_RAMP_UP,
	USB_DRDAQ_RAMP_DOWN,
	USB_DRDAQ_DC
}USB_DRDAQ_WAVE;

typedef enum enUsbDrDaqDO
{
	USB_DRDAQ_GPIO_1 = 1,
	USB_DRDAQ_GPIO_2,
	USB_DRDAQ_GPIO_3,
	USB_DRDAQ_GPIO_4
}USB_DRDAQ_GPIO;

typedef enum enUSBDrDAQInfo
{
  USBDrDAQ_DRIVER_VERSION,
  USBDrDAQ_USB_VERSION,
  USBDrDAQ_HARDWARE_VERSION,
  USBDrDAQ_VARIANT_INFO,
  USBDrDAQ_BATCH_AND_SERIAL,
  USBDrDAQ_CAL_DATE,	
  USBDrDAQ_KERNEL_DRIVER_VERSION, 
  USBDrDAQ_ERROR,
  USBDrDAQ_SETTINGS,
  USBDrDAQ_FIRMWARE_VERSION,
  USBDrDAQ_DRIVER_PATH = 14
} USBDrDAQ_INFO;
											
#ifndef BM_DEFINED
#define BM_DEFINED
typedef enum _BLOCK_METHOD{BM_SINGLE, BM_WINDOW, BM_STREAM} BLOCK_METHOD;
#endif

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (UsbDrDaqOpenUnit)
(
	int16_t *handle
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (UsbDrDaqCloseUnit)
(
	int16_t handle
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (UsbDrDaqGetUnitInfo)
(	
	int16_t			handle,		
	int8_t			*string, 
	int16_t			stringLength, 
	int16_t			*requiredSize, 
	PICO_INFO info
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (UsbDrDaqRun) 
(
	int16_t						handle, 
	uint32_t		no_of_values, 
	BLOCK_METHOD		method
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (UsbDrDaqReady)
(
	int16_t handle, 
	int16_t *ready
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (UsbDrDaqStop) 
(
	int16_t handle
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (UsbDrDaqSetInterval)
(	
	int16_t							handle,
	uint32_t			*us_for_block,
	uint32_t			ideal_no_of_samples,
	USB_DRDAQ_INPUTS	*channels,
	int16_t							no_of_channels
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (UsbDrDaqSetIntervalF)
(	
	int16_t							handle,
	float						*	us_for_block,
	uint32_t			ideal_no_of_samples,
	USB_DRDAQ_INPUTS	*channels,
	int16_t							no_of_channels
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (UsbDrDaqSetTrigger)
(
	int16_t						handle,
	uint16_t	enabled,
	uint16_t	auto_trigger,
	uint16_t	auto_ms,
	uint16_t	channel,
	uint16_t	dir,
	int16_t						threshold,
	uint16_t	hysterisis,
	float						delay
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (UsbDrDaqGetValues) 
(
	int16_t						handle,
	int16_t						*values,
	uint32_t		*noOfValues, 
	uint16_t	*overflow,
	uint32_t		*triggerIndex
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (UsbDrDaqGetValuesF) 
	(
	int16_t						handle,
	float						*values,
	uint32_t		*noOfValues, 
	uint16_t	*overflow,
	uint32_t		*triggerIndex
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (UsbDrDaqGetTriggerTimeOffsetNs)	
(
	int16_t		handle, 
	int64_t *time
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (UsbDrDaqGetSingle) 
(
	int16_t							handle, 
	USB_DRDAQ_INPUTS	channel, 
	int16_t							*value, 
	uint16_t		*overflow
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (UsbDrDaqGetSingleF) 
	(
	int16_t							handle, 
	USB_DRDAQ_INPUTS	channel, 
	float							*value, 
	uint16_t		*overflow
	);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (UsbDrDaqOpenUnitAsync) 
(
	int16_t *status
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (UsbDrDaqOpenUnitProgress) 
(
	int16_t *handle, 
	int16_t *progress, 
	int16_t *complete
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (UsbDrDaqGetScalings)
(
	int16_t							handle, 
	USB_DRDAQ_INPUTS	channel, 
	int16_t							*nScales, 
	int16_t							*currentScale, 
	int8_t							*names, 
	int16_t							namesSize
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (UsbDrDaqSetScalings)
(
	int16_t							handle, 
	USB_DRDAQ_INPUTS	channel, 
	int16_t							scalingNumber
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (UsbDrDaqSetSigGenBuiltIn)
(
	int16_t						handle, 
	int32_t						offsetVoltage,
	uint32_t		pkToPk,
	int16_t						frequency,
	USB_DRDAQ_WAVE	waveType
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (UsbDrDaqSetSigGenArbitrary)
(
	int16_t					handle, 
	int32_t					offsetVoltage,
	uint32_t	pkToPk,
	int16_t					*arbitraryWaveform,
	int16_t					arbitraryWaveformSize,
	int32_t					updateRate
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (UsbDrDaqStopSigGen)
(
	int16_t	handle
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (UsbDrDaqSetDO)
(
	int16_t						handle,
	USB_DRDAQ_GPIO	IOChannel,
	int16_t						value
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (UsbDrDaqSetPWM)
(
	int16_t						handle,
	USB_DRDAQ_GPIO	IOChannel,
	uint16_t	period,
	uint8_t		cycle
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (UsbDrDaqGetInput)
(
	int16_t						handle,
	USB_DRDAQ_GPIO	IOChannel,
	int16_t						pullUp,
	int16_t						*value
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (UsbDrDaqStartPulseCount)
(
	int16_t						handle,
	USB_DRDAQ_GPIO	IOChannel,
	int16_t						direction
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (UsbDrDaqGetPulseCount)
(
	int16_t						handle,
	USB_DRDAQ_GPIO	IOChannel,
	int16_t						*count
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (UsbDrDaqEnableRGBLED)
(
	int16_t	handle,
	int16_t enabled
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (UsbDrDaqSetRGBLED)
(
	int16_t	handle,
	uint16_t	red,
	uint16_t	green,
	uint16_t	blue
);

PREF0 PREF1 PICO_STATUS PREF2 PREF3 (UsbDrDaqGetChannelInfo)
(
	int16_t							handle,
	float							*min,
	float							*max,
	int16_t							*places,
	int16_t 						*divider,
	USB_DRDAQ_INPUTS	channel
);

PREF0 PREF1 PICO_STATUS PREF2  PREF3 (UsbDrDaqPingUnit) (int16_t handle);

PREF0 PREF1 PICO_STATUS PREF2 PREF3(UsbDrDaqPhTemperatureCompensation)
(
	int16_t	handle,
	uint16_t enabled
	);
#endif
