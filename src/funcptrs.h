#pragma once

#include <Windows.h>
#include <Xinput.h>

#include "macros.h"

//
// Ordinals and other functions
//
typedef DWORD(*FPXGetState)(DWORD, XINPUT_STATE*);
    static FPXGetState PAXInputGetState;
typedef DWORD(*FPXSetState)(DWORD, XINPUT_VIBRATION*);
    static FPXSetState PAXInputSetState;
typedef DWORD(*FPXGetCapabilities)(DWORD, DWORD, XINPUT_CAPABILITIES*);
    static FPXGetCapabilities PAXInputGetCapabilities;
typedef void(*FPXEnable)(BOOL);
    static FPXEnable PAXInputEnable;
typedef DWORD(*FPXGetBatteryInformation)(DWORD, BYTE, XINPUT_BATTERY_INFORMATION*);
    static FPXGetBatteryInformation PAXInputGetBatteryInformation;
typedef DWORD(*FPXGetKeystroke)(DWORD, DWORD, PXINPUT_KEYSTROKE);
    static FPXGetKeystroke PAXInputGetKeystroke;

#if defined XINPUT1_3 || defined XINPUT9_1_0
typedef DWORD(*FPXGetDSoundAudioDeviceGuids)(DWORD, GUID*, GUID*);
    static FPXGetDSoundAudioDeviceGuids PAXInputGetDSoundAudioDeviceGuids;
#endif
#ifdef XINPUT1_4
typedef DWORD(*FPXGetAudioDeviceIds)(DWORD, LPWSTR, UINT*, LPWSTR, UINT*);
    static FPXGetAudioDeviceIds PAXInputGetAudioDeviceIds;
#endif