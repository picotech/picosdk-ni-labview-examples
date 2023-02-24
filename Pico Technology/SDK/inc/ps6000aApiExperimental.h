/****************************************************************************
 *
 * Filename:    ps6000aApiExperimental.h
 * Copyright:   Pico Technology Limited 2002 - 2022
 * Description:
 *
 * This header defines the interface to driver routines for the
 *  PicoScope 6000 range of PC Oscilloscopes.
 *
 * These functions are at the beta stage of development and their
 * signatures may change.
 *
 ****************************************************************************/

#ifndef __PS6000AAPIEXPERIMENTAL_H__
#define __PS6000AAPIEXPERIMENTAL_H__


#include "ps6000aApi.h"
#include "PicoCallback.h"
#include "PicoDeviceDefinitionsExperimental.h"

#include <stdint.h>

typedef void (PREF4 *ps6000aDigitalPortInteractions)
(
  int16_t    											handle,
  PICO_STATUS											status,
  PICO_DIGITAL_PORT_INTERACTIONS *	ports,
  uint32_t												nPorts
  );

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aSetDigitalPortInteractionCallback)
(
  int16_t													handle,
  ps6000aDigitalPortInteractions	callback
  );

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aSetProbeInteractionCallback)
(
  int16_t		handle,
  PicoProbeInteractions callback
  );

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aSetExternalReferenceInteractionCallback)
(
  int16_t		handle,
  PicoExternalReferenceInteractions callback
  );

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aSetAWGOverrangeInteractionCallback)
(
  int16_t		handle,
  PicoAWGOverrangeInteractions callback
  );

PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aSetTemperatureSensorInteractionCallback)
(
  int16_t		handle,
  PicoTemperatureSensorInteractions callback
  );

/// <summary>
/// Callback signature for a probe user action notification (not to be confused with
/// the connection / fault status change which is notified via PicoProbeInteractions).
/// </summary>
/// <param name="handle">The handle to the device to which the probe is attached.</param>
/// <param name="status">
/// Indicates if anything went wrong while handling the probe event
/// (e.g. probe signaled an interrupt, but then communication with the probe failed).</param>
/// <param name="channel">The channel to which the probe was attached that signaled
/// the interrupt.
/// </param>
/// <param name="probe">The type of probe connected to the channel.</param>
/// <param name="action">The probe action which the user performed.</param>
/// <param name="pActionParameter">
/// A pointer to a struct containing the parameters for
/// the action, (e.g. in case of PICO_PROBE_BUTTON_PRESS, this is a
/// PICO_PROBE_BUTTON_PRESS_PARAMETER *).
/// </param>
/// <param name="pParameter">A pointer to the user parameter given when setting the callback.</param>
typedef void(PREF5* PicoProbeUserAction)(int16_t handle,
                                         PICO_STATUS status,
                                         PICO_CHANNEL channel,
                                         PICO_CONNECT_PROBE probe,
                                         PICO_PROBE_USER_ACTION action,
                                         PICO_POINTER pActionParameter,
                                         PICO_POINTER pParameter);

/// <summary>
/// Sets a callback for probe-specific user actions (such as button-press events).
/// Note that ps6000aSetProbeInteractionCallback must have already been called before calling this
/// function. Also note that like all other user callbacks (probe arrival / status, MSO arrival,
/// temperature, external reference, AWG overrange), this callback will occur on the user interaction
/// event loop, so it is guaranteed not to be invoked concurrently with any others. The parameter
/// pointer will be passed back to the user via the last argument on the callback on subsequent
/// invocations.
/// </summary>
/// <param name="handle">The handle to the device to which the probe is attached.</param>
/// <param name="callback">A pointer to the callback function.</param>
/// <param name="pParameter">A pointer to the user data.</param>
/// <returns>
/// A status indicating whether the callback was configured successfully. Possible errors:
///   PICO_INVALID_HANDLE - the given handle is unknown to the driver or has been closed
///   PICO_DRIVER_FUNCTION - a driver function has been called on another thread
///   PICO_NOT_SUPPORTED_BY_THIS_DEVICE - the device associated with this handle does not support
///     intelligent probes
///   PICO_PROBE_COLLECTION_NOT_STARTED - no probe interaction callback is currently set
/// </returns>
PREF0 PREF1 PICO_STATUS PREF2 PREF3(ps6000aSetProbeUserActionCallback) (
  int16_t handle,
  PicoProbeUserAction callback,
  PICO_POINTER pParameter
  );

#endif
