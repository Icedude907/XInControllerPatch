#include <Windows.h>
#include <Xinput.h>

#include <string>
#include <unordered_set>

/* TODOLIST:
    TODO: Still got to do the ordinals
    TODO: Load xinput in the current directory if there is a hook
*/

#include "macros.h"
#include "funcptrs.h"

// Other statics
static bool loadedXInput = false;

void loadXInput(){
    // TODO: Load xinput in the current directory if we can e.g.:"xinput1_3R.dll" R meaning real.
    HMODULE xdll;
    // Load in the same folder or else in system32
    // if(xdll == nullptr){
        xdll = LoadLibraryA(XINPUT_SOURCE_NAME);
    // }

    // remove file extension

    // Load addrs
    PAXInputGetState                = (FPXGetState)                 GetProcAddress(xdll, "XInputGetState");
    PAXInputSetState                = (FPXSetState)                 GetProcAddress(xdll, "XInputSetState");
    PAXInputGetCapabilities         = (FPXGetCapabilities)          GetProcAddress(xdll, "XInputGetCapabilities");
    PAXInputEnable                  = (FPXEnable)                   GetProcAddress(xdll, "XInputEnable");
    PAXInputGetBatteryInformation   = (FPXGetBatteryInformation)    GetProcAddress(xdll, "XInputGetBatteryInformation");
    PAXInputGetKeystroke            = (FPXGetKeystroke)             GetProcAddress(xdll, "XInputGetKeystroke");

    #if defined XINPUT1_3 || defined XINPUT9_1_0
        PAXInputGetDSoundAudioDeviceGuids   = (FPXGetDSoundAudioDeviceGuids)GetProcAddress(xdll, "XInputGetDSoundAudioDeviceGuids");
    #endif
    #ifdef XINPUT1_4
        PAXInputGetAudioDeviceIds           = (FPXGetAudioDeviceIds)        GetProcAddress(xdll, "XInputGetAudioDeviceIds");
    #endif

    loadedXInput = true;
}

BOOL APIENTRY _DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved){
    if(!loadedXInput) loadXInput();
    return TRUE;
}

////////////////
struct driftZone{
    int16_t lowerzone, upperzone;
    bool inside(int16_t coord) const {
        bool a = coord >= lowerzone;
        bool b = coord <= upperzone;
        return a && b;
    }
};
constexpr driftZone   beginzone{-4600, 4600};
constexpr driftZone updriftzone{-4600, (int16_t)(INT16_MAX * 0.77)};

static std::unordered_set<DWORD> ignoreAxisUsers;
////////////////

DWORD APIENTRY _XInputGetState(
    _In_  DWORD         dwUserIndex,  // 
    _Out_ XINPUT_STATE* pState        // Receives the current state
){
    if(!loadedXInput) loadXInput();
    
    auto res = PAXInputGetState(dwUserIndex, pState);
    if(   beginzone.inside(pState->Gamepad.sThumbRY)){ ignoreAxisUsers.insert(dwUserIndex); }
    if(!updriftzone.inside(pState->Gamepad.sThumbRY)){ ignoreAxisUsers.erase(dwUserIndex); }

    // Ignore axis
    if(ignoreAxisUsers.find(dwUserIndex) != ignoreAxisUsers.end()){ pState->Gamepad.sThumbRY = 0; }
    return res;
}

DWORD APIENTRY _XInputSetState(
    _In_ DWORD             dwUserIndex,  // 
    _In_ XINPUT_VIBRATION* pVibration    // The vibration information to send to the controller
){
    if(!loadedXInput) loadXInput();
    return PAXInputSetState(dwUserIndex, pVibration);
}

DWORD APIENTRY _XInputGetCapabilities(
    _In_  DWORD                dwUserIndex,   //
    _In_  DWORD                dwFlags,       // Input flags that identify the device type
    _Out_ XINPUT_CAPABILITIES* pCapabilities  // Receives the capabilities
){
    if(!loadedXInput) loadXInput();
    return PAXInputGetCapabilities(dwUserIndex, dwFlags, pCapabilities);
}
#ifndef XINPUT9_1_0
    void APIENTRY _XInputEnable(_In_ BOOL enable){
        if(!loadedXInput) loadXInput();
        PAXInputEnable(enable);
    }

    DWORD APIENTRY _XInputGetBatteryInformation(
        _In_  DWORD                       dwUserIndex,        //
        _In_  BYTE                        devType,            // Which device on this user index
        _Out_ XINPUT_BATTERY_INFORMATION* pBatteryInformation // Contains the level and types of batteries
    ){
        if(!loadedXInput) loadXInput();
        return PAXInputGetBatteryInformation(dwUserIndex, devType, pBatteryInformation);
    }

    DWORD APIENTRY _XInputGetKeystroke(
        _In_       DWORD dwUserIndex,              //
        _Reserved_ DWORD dwReserved,               // Reserved for future use
        _Out_      PXINPUT_KEYSTROKE pKeystroke    // Pointer to an XINPUT_KEYSTROKE structure that receives an input event.
    ){
        if(!loadedXInput) loadXInput();
        return PAXInputGetKeystroke(dwUserIndex, dwReserved, pKeystroke);
    }
#endif

#if defined XINPUT1_3 || defined XINPUT9_1_0
    DWORD APIENTRY _XInputGetDSoundAudioDeviceGuids(
        DWORD dwUserIndex,
        GUID  *pDSoundRenderGuid,
        GUID  *pDSoundCaptureGuid
    ){
        if(!loadedXInput) loadXInput();
        return PAXInputGetDSoundAudioDeviceGuids(dwUserIndex, pDSoundRenderGuid, pDSoundCaptureGuid);
    }
#endif
#ifdef XINPUT1_4
    DWORD APIENTRY _XInputGetAudioDeviceIds(
        _In_  DWORD                             dwUserIndex,        //
        _Out_writes_opt_(*pRenderCount) LPWSTR  pRenderDeviceId,    // Windows Core Audio device ID string for render (speakers)
        _Inout_opt_ UINT*                       pRenderCount,       // Size of render device ID string buffer (in wide-chars)
        _Out_writes_opt_(*pCaptureCount) LPWSTR pCaptureDeviceId,   // Windows Core Audio device ID string for capture (microphone)
        _Inout_opt_ UINT*                       pCaptureCount       // Size of capture device ID string buffer (in wide-chars)
    ){
        if(!loadedXInput) loadXInput();
        return PAXInputGetAudioDeviceIds(dwUserIndex, pRenderDeviceId, pRenderCount, pCaptureDeviceId, pCaptureCount);
    }
#endif


// Ordinal passthrough
// 
// TODO: