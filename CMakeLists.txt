cmake_minimum_required(VERSION 3.19)

project(XInputHook VERSION 1.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# TODO: Other versions with other definitions
# The case decisions are intentional and reflect the names of the dlls in system32
# Def files are used to rename the functions, while preventing clashes while compiling
add_library(XInput1_4 SHARED "src/dllmain.cpp" "src/dllmain1_4.def")
target_compile_definitions(XInput1_4 PUBLIC "XINPUT1_4")

add_library(XInput9_1_0 SHARED "src/dllmain.cpp" "src/dllmain9_1_0.def")
target_compile_definitions(XInput9_1_0 PUBLIC "XINPUT9_1_0")

add_library(xinput1_3 SHARED "src/dllmain.cpp" "src/dllmain1_3.def")
target_compile_definitions(xinput1_3 PUBLIC "XINPUT1_3")


# Test
add_executable(XInputTest "test/XInputTest.cpp")
target_link_libraries(XInputTest XInput)
