# XInputControllerPatch
A couple months back the right joystick on my *xbox one wireless controller* started drifting up on the y axis while in neutral. After failing to fix it I decided to develop a software solution.

## How to use it:
Simply drag the XInput dll version you require into the same directory as the executable, and windows will load it in place of the regular XInput dll. It will apply to any XInput device loaded in the application.

## How does it work?
When windows loads the dll, it loads the normal XInput dll its associated with.
Any commands it then receives from the application it forwards to the original dll, except for `XInputGetState`.

If the controller's joystick is in what I've marked as the *updriftzone* (this covers all the range my controller drifts while its actually in neutral), all changes to the y axis are ignored. Once the y axis exits that zone (because someone physically moves it outside of the zone), controller operation resumes as normal. Once the control stick enters the *beginzone* (i.e.: neutral), it will lock again until exiting the *updriftzone*.

This is better than just setting a massive deadzone in a game because it doesn't restrain the X axis (which doesn't drift on my controller), and allows for fine control on the y axis by tapping outside of the *updriftzone*, and then slowly returning it to the desired level.

## What can I do with it?
You are free to use this application however you like, whether its to fix the same issue I had, or to change something else (in which case you will need to edit the code).
I figure this project is a good place for others to start with, as I've gone to all the trouble of hooking all XInput functions already.

## What's going to happen to this project?
Currently the project is considered fit for the purposes I needed it for.
However, there are some updates I'll consider doing when I'm bored:
- Supporting older XInput functions
- Passing through unnamed functions (ordinals). This would be useful for hooking into the home button, etc.
- General code maintenance and documentation
- Loading XInput from other locations & thereby allowing for you to replace the System32 XInput with this one for coverage across the whole machine. 
    - (DONT DO THIS AT THE MOMENT. This dll is dependent on the real one. Renaming/deleting the real one will probably cause this to crash / get stuck.)

## Other
There is an additional file in this project called `XInputTest`. You may wish to use it to test controllers or this dll.

## Building
Building the project requires CMake. You must use a Visual Studio compiler (MSVC). MINGW / GCC do not work due to different linking mechanisms. Support is windows only (other systems may support this via *WINE*, but this isn't official or confirmed).