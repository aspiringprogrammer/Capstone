//   ___________________
//  / XInputManager.h   \
// |                     ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\ 
// |  Defines an interface to access an  |
// |  Xbox 360 controller via XInput.    |
// |                                      \_______
// |  by lickstab @ http://www.ogre3d.org/forums/ \
//  \ This work is in the public domain.          /
//   ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯

// only include once, link to XInput.lib
#pragma once
#pragma comment(lib, "XInput.lib")

// include files
#include <windows.h>
#include <XInput.h>

// holds information about a single gamepad
struct GamepadState
{
public:
   // used for disconnected gamepads and when trying to access a non-existant gamepad (ie higher than number 4)
   bool error; 
   // for thumbsticks
   struct { float X, Y; } LeftStick, RightStick;
   // triggers
   float LeftTrigger, RightTrigger;
   // buttons except dpad
   struct
   {
      bool LeftShoulder,
         RightShoulder,
         A,
         B,
         X,
         Y,
         Back,
         Start,
         LeftThumb,
         RightThumb;
   } Buttons;
   // dpad
   struct
   {
      bool Up, Down, Left, Right;
   } DPad;

   // for limiting repeat 'presses'
   struct
   {
      bool LeftShoulder,
         RightShoulder,
         A,
         B,
         X,
         Y,
         Back,
         Start,
         LeftThumb,
         RightThumb;
   } ButtonsSingle;
   struct
   {
      bool Up, Down, Left, Right;
   } DPadSingle;
   struct
   {
      bool LeftShoulder,
         RightShoulder,
         A,
         B,
         X,
         Y,
         Back,
         Start,
         LeftThumb,
         RightThumb;
   } ButtonsOld;
   struct
   {
      bool Up, Down, Left, Right;
   } DPadOld;
};

// handles XInput gamepads
class XInputManager
{
private:
   XINPUT_STATE state[4];         // xinput states
   GamepadState Pads[4];         // represents each gamepad
   GamepadState PadError;         // returned on error
public:
   XInputManager();
   void Update();               // update pads
   GamepadState GetState(int pad);   // get a pad's info
   void SetVibration(int pad, float left, float right); // set vibration strength
   ~XInputManager();
};