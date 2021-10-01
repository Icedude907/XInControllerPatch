#pragma once

#ifdef XINPUT1_3
    #define XINPUT_DLL_NAME "xinput1_3.dll"
#elif  XINPUT1_4
    #define XINPUT_DLL_NAME "XInput1_4.dll"
#elif  XINPUT9_1_0
    #define XINPUT_DLL_NAME "XInput9_1_0.dll"
#endif
#define XINPUT_SOURCE_NAME "C:\\Windows\\System32\\" XINPUT_DLL_NAME