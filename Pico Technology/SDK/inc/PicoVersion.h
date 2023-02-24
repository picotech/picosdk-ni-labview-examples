/****************************************************************************
 *
 * Filename:    PicoVersion.h
 * Copyright:   Pico Technology Limited 2018 - 2022
 * Description:
 *
 * This header defines the version struct.
 *
 ****************************************************************************/

#ifndef __PICOVERSION_H__
#define __PICOVERSION_H__

#include <stdint.h>

#include "PicoStatus.h"

#pragma pack(push, 1)

typedef struct tPicoVersion
{
	int16_t major_;
	int16_t minor_;
	int16_t revision_;
	int16_t build_;
} PICO_VERSION;

typedef struct tPicoFirmwareInfo {
	PICO_INFO firmwareType;
	PICO_VERSION currentVersion;
	PICO_VERSION updateVersion;
	uint16_t updateRequired;
} PICO_FIRMWARE_INFO;

#pragma pack(pop)

#endif
