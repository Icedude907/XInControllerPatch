# XInputControllerPatch
A couple years back the right joystick on my *xbox one wireless controller* started drifting up on the y axis while in neutral. After failing to fix it I decided to develop a software solution (and it still works!)

## How to use it:
Simply drag the XInput dll version you require into the same directory as the executable, and windows should load it in place of the regular XInput dll. It will apply to any XInput device loaded in the application.
Depending on the application, different DLL versions may be loaded. This project supports:
- XInput 1.3 (`xinput1_3.dll`)
- XInput 9.1.0 (`XInput9_1_0.dll`)
- XInput 1.4 (`XInput1_4.dll`)

## How do my edits work?
When windows loads the dll, it loads the normal XInput dll its associated with.
Any commands it then receives from the application it forwards to the original dll, except for `XInputGetState`.

If the controller's joystick is in what I've marked as the *updriftzone* (this covers all the range my controller drifts while its actually in neutral), all changes to the y axis are ignored. Once the y axis exits that zone (because someone physically moves it outside of the zone), controller operation resumes as normal. Once the control stick enters the *beginzone* (i.e.: neutral), it will lock again until exiting the *updriftzone*.

This is better than just setting a massive deadzone in a game because it doesn't restrain the X axis (which doesn't drift on my controller), and allows for fine control on the y axis by tapping outside of the *updriftzone*, and then slowly returning it to the desired level.

## What's going to happen to this project?
Currently the project is considered fit for the purposes I needed it for. So don't expect many future changes.

I figure this project is a good place for others to start with - feel free to make your own changes.

## Other
There is an additional file in this project called `XInputTest`. You may wish to use it to test controllers or this dll.  

## Building
Building the project requires CMake. You must use a Visual Studio compiler (MSVC). MINGW / GCC do not work due to different linking mechanisms. Support is Windows only (other systems *may* support this via WINE or Proton).