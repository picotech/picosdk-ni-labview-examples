/****************************************************************************
 *
 * Filename:    PicoDeviceDefinitionsExperimental.h
 * Copyright:   Pico Technology Limited 2016 - 2022
 * Description:
 *
 * This header contains definitions of enumerated types and structs which
 * are at the beta stage of development and their signatures may change.
 ****************************************************************************/

#ifndef __PICODEVICEDEFINITIONSEXPERIMENTAL_H__
#define __PICODEVICEDEFINITIONSEXPERIMENTAL_H__

#include <stdint.h>

/// <summary>
/// Probe user action (only button press events supported for now). Other event types
/// may be added in future to support new probes.
/// </summary>
typedef enum enPicoProbeUserAction
{
  PICO_PROBE_BUTTON_PRESS, /// parameter struct -> PICO_PROBE_BUTTON_PRESS_PARAMETER
} PICO_PROBE_USER_ACTION;

/// <summary>
/// The duration of the button press event.
/// </summary>
typedef enum enPicoProbeButtonPressType
{
  PICO_PROBE_BUTTON_SHORT_DURATION_PRESS,
  PICO_PROBE_BUTTON_LONG_DURATION_PRESS,
} PICO_PROBE_BUTTON_PRESS_TYPE;

#pragma pack(push, 1)
/// <summary>
/// The parameter struct for a button press event, indicating which button was
/// pressed (in case future probes have multiple) and the type of press.
/// </summary>
typedef struct tPicoProbeButtonPressParameter
{
  uint8_t buttonIndex;
  PICO_PROBE_BUTTON_PRESS_TYPE buttonPressType;
} PICO_PROBE_BUTTON_PRESS_PARAMETER;
#pragma pack(pop)

#endif