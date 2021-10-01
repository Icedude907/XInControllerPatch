#include <Windows.h>
#include <Xinput.h>

#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip>
int main(){
    // TODO: Test all functions
    XINPUT_STATE lastS{};
    bool stillconnected = false;
    while(true){
        XINPUT_STATE s;
        auto res = XInputGetState(0, &s);
        auto connected = res == ERROR_SUCCESS;
        if(!connected){
            if(!stillconnected){
                stillconnected = true;
                std::cout << "p1 Not connected" << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(16));
            continue;
        }
        stillconnected = false;

        std::string buttonString = "";
        if(res == ERROR_SUCCESS && lastS.dwPacketNumber != s.dwPacketNumber){
            // If change
            #define CB(code, char) if(s.Gamepad.wButtons & XINPUT_GAMEPAD_##code){buttonString.push_back(char);}else{buttonString.push_back(' ');}
            CB(A, 'A')  CB(B, 'B')  CB(X, 'X')  CB(Y, 'Y')
            CB(DPAD_UP, '^')        CB(DPAD_DOWN, 'D')
            CB(DPAD_LEFT, '<')      CB(DPAD_RIGHT, '>')
            CB(LEFT_SHOULDER, 'L')  CB(RIGHT_SHOULDER, 'R')
            CB(LEFT_THUMB, '[')     CB(RIGHT_THUMB, ']')
            CB(START, '+')          CB(BACK, '-')
            #undef CB
            std::cout << std::setfill(' ') << std::setw(6) << s.dwPacketNumber << ": " << buttonString
                      << "    x1: " << std::setw(6) << s.Gamepad.sThumbLX << " y1: " << std::setw(6) << s.Gamepad.sThumbLY 
                      << "    x2: " << std::setw(6) << s.Gamepad.sThumbRX << " y2: " << std::setw(6) << s.Gamepad.sThumbRY
                      << "    ZL: " << std::setw(3) << (uint16_t)s.Gamepad.bLeftTrigger << " ZR: " << std::setw(3) << (uint16_t)s.Gamepad.bRightTrigger
                      << std::setw(0) << std::endl;
        }
        lastS = s;
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}