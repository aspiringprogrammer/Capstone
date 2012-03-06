//   ___________________
//  / XInputManager.cpp \
// |                     ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\ 
// |  Defines an interface to access an  |
// |  Xbox 360 controller via XInput.    |
// |                                      \_______
// |  by lickstab @ http://www.ogre3d.org/forums/ \
//  \ This work is in the public domain.          / 
//   ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯

#include <Ogre.h>
#include "XInputManager.h"

// constructor
XInputManager::XInputManager()
{
   for(int i = 0; i<4;i++)
   {
      Pads[i].error = true;
   }
   PadError.error = true;
}

XInputManager::~XInputManager() { }

// update all input
void XInputManager::Update()
{
   DWORD dwResult;
   
   for(int i = 0; i<4;i++)
   {
      ZeroMemory( &state[i], sizeof(XINPUT_STATE) );
   
      dwResult = XInputGetState(i, &state[i]);

      if(dwResult == ERROR_SUCCESS)
      {
         Pads[i].error = false;

         // get thumbsticks
         // (deadzone stuff from http://www.kmcgrail.com/XInputTut.htm)
         if( (state[i].Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
            state[i].Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
            (state[i].Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
            state[i].Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) )
            {
               Pads[i].LeftStick.X = 0.0f;
               Pads[i].LeftStick.Y = 0.0f;
            }
         else
         {
            Pads[i].LeftStick.X = state[i].Gamepad.sThumbLX / 255.0f;
            Pads[i].LeftStick.Y = state[i].Gamepad.sThumbLY / 255.0f;
         }
         if( (state[i].Gamepad.sThumbRX < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
            state[i].Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) &&
            (state[i].Gamepad.sThumbRY < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
            state[i].Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) )
            {
               Pads[i].RightStick.X = 0.0f;
               Pads[i].RightStick.Y = 0.0f;
            }
         else
         {
            Pads[i].RightStick.X = state[i].Gamepad.sThumbRX / 255.0f;
            Pads[i].RightStick.Y = state[i].Gamepad.sThumbRY / 255.0f;
         }

         // get triggers
         if(state[i].Gamepad.bLeftTrigger >= XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
         {
            Pads[i].LeftTrigger = state[i].Gamepad.bLeftTrigger / 255.0f;
         }
         else
         {
            Pads[i].LeftTrigger = 0.0f;
         }

         if(state[i].Gamepad.bRightTrigger >= XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
         {
            Pads[i].RightTrigger = state[i].Gamepad.bRightTrigger / 255.0f;
         }
         else
         {
            Pads[i].RightTrigger = 0.0f;
         }

         // store old button states
         Pads[i].ButtonsOld.A = Pads[i].Buttons.A;
         Pads[i].ButtonsOld.B = Pads[i].Buttons.B;
         Pads[i].ButtonsOld.X = Pads[i].Buttons.X;
         Pads[i].ButtonsOld.Y = Pads[i].Buttons.Y;
         Pads[i].ButtonsOld.Start = Pads[i].Buttons.Start;
         Pads[i].ButtonsOld.Back = Pads[i].Buttons.Back;
         Pads[i].ButtonsOld.LeftShoulder = Pads[i].Buttons.LeftShoulder;
         Pads[i].ButtonsOld.RightShoulder = Pads[i].Buttons.RightShoulder;
         Pads[i].ButtonsOld.LeftThumb = Pads[i].Buttons.LeftThumb;
         Pads[i].ButtonsOld.RightThumb = Pads[i].Buttons.RightThumb;

         Pads[i].DPadOld.Up = Pads[i].DPad.Up;
         Pads[i].DPadOld.Down = Pads[i].DPad.Down;
         Pads[i].DPadOld.Left = Pads[i].DPad.Left;
         Pads[i].DPadOld.Right = Pads[i].DPad.Right;

         // get buttons
         if(state[i].Gamepad.wButtons & XINPUT_GAMEPAD_A)
         {
            Pads[i].Buttons.A = true;
         } else { Pads[i].Buttons.A = false; }
         if(state[i].Gamepad.wButtons & XINPUT_GAMEPAD_B)
         {
            Pads[i].Buttons.B = true;
         } else { Pads[i].Buttons.B = false; }
         if(state[i].Gamepad.wButtons & XINPUT_GAMEPAD_X)
         {
            Pads[i].Buttons.X = true;
         } else { Pads[i].Buttons.X = false; }
         if(state[i].Gamepad.wButtons & XINPUT_GAMEPAD_Y)
         {
            Pads[i].Buttons.Y = true;
         } else { Pads[i].Buttons.Y = false; }
         if(state[i].Gamepad.wButtons & XINPUT_GAMEPAD_BACK)
         {
            Pads[i].Buttons.Back = true;
         } else { Pads[i].Buttons.Back = false; }
         if(state[i].Gamepad.wButtons & XINPUT_GAMEPAD_START)
         {
            Pads[i].Buttons.Start = true;
         } else { Pads[i].Buttons.Start = false; }
         if(state[i].Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
         {
            Pads[i].Buttons.LeftShoulder = true;
         } else { Pads[i].Buttons.LeftShoulder = false; }
         if(state[i].Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
         {
            Pads[i].Buttons.RightShoulder = true;
         } else { Pads[i].Buttons.RightShoulder = false; }
         if(state[i].Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB)
         {
            Pads[i].Buttons.LeftThumb = true;
         } else { Pads[i].Buttons.LeftThumb = false; }
         if(state[i].Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB)
         {
            Pads[i].Buttons.RightThumb = true;
         } else { Pads[i].Buttons.RightThumb = false; }

         // get dpad
         if(state[i].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
         {
            Pads[i].DPad.Up = true;
         } else { Pads[i].DPad.Up = false; }
         if(state[i].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
         {
            Pads[i].DPad.Down = true;
         } else { Pads[i].DPad.Down = false; }
         if(state[i].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
         {
            Pads[i].DPad.Left = true;
         } else { Pads[i].DPad.Left = false; }
         if(state[i].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
         {
            Pads[i].DPad.Right = true;
         } else { Pads[i].DPad.Right = false; }

         // set single press states
         // A
         if(!Pads[i].Buttons.A)
            Pads[i].ButtonsSingle.A = false;
         else
         {
            if(!Pads[i].ButtonsSingle.A && !Pads[i].ButtonsOld.A)
               Pads[i].ButtonsSingle.A = true;
            else
               Pads[i].ButtonsSingle.A = false;
         }
         // B
         if(!Pads[i].Buttons.B)
            Pads[i].ButtonsSingle.B = false;
         else
         {
            if(!Pads[i].ButtonsSingle.B && !Pads[i].ButtonsOld.B)
               Pads[i].ButtonsSingle.B = true;
            else
               Pads[i].ButtonsSingle.B = false;
         }
                  if(!Pads[i].Buttons.X)
            Pads[i].ButtonsSingle.X = false;
         else
         {
         // X
         if(!Pads[i].ButtonsSingle.X && !Pads[i].ButtonsOld.X)
               Pads[i].ButtonsSingle.X = true;
            else
               Pads[i].ButtonsSingle.X = false;
         }
         // Y
         if(!Pads[i].Buttons.Y)
            Pads[i].ButtonsSingle.Y = false;
         else
         {
            if(!Pads[i].ButtonsSingle.Y && !Pads[i].ButtonsOld.Y)
               Pads[i].ButtonsSingle.Y = true;
            else
               Pads[i].ButtonsSingle.Y = false;
         }
         // Start
         if(!Pads[i].Buttons.Start)
            Pads[i].ButtonsSingle.Start = false;
         else
         {
            if(!Pads[i].ButtonsSingle.Start && !Pads[i].ButtonsOld.Start)
               Pads[i].ButtonsSingle.Start = true;
            else
               Pads[i].ButtonsSingle.Start = false;
         }
         // Back
         if(!Pads[i].Buttons.Back)
            Pads[i].ButtonsSingle.Back = false;
         else
         {
            if(!Pads[i].ButtonsSingle.Back && !Pads[i].ButtonsOld.Back)
               Pads[i].ButtonsSingle.Back = true;
            else
               Pads[i].ButtonsSingle.Back = false;
         }
         // Left Shoulder
         if(!Pads[i].Buttons.LeftShoulder)
            Pads[i].ButtonsSingle.LeftShoulder = false;
         else
         {
            if(!Pads[i].ButtonsSingle.LeftShoulder && !Pads[i].ButtonsOld.LeftShoulder)
               Pads[i].ButtonsSingle.LeftShoulder = true;
            else
               Pads[i].ButtonsSingle.LeftShoulder = false;
         }
         // Right Shoulder
         if(!Pads[i].Buttons.RightShoulder)
            Pads[i].ButtonsSingle.RightShoulder = false;
         else
         {
            if(!Pads[i].ButtonsSingle.RightShoulder && !Pads[i].ButtonsOld.RightShoulder)
               Pads[i].ButtonsSingle.RightShoulder = true;
            else
               Pads[i].ButtonsSingle.RightShoulder = false;
         }
         // Left Thumbstick
         if(!Pads[i].Buttons.LeftThumb)
            Pads[i].ButtonsSingle.LeftThumb = false;
         else
         {
            if(!Pads[i].ButtonsSingle.LeftThumb && !Pads[i].ButtonsOld.LeftThumb)
               Pads[i].ButtonsSingle.LeftThumb = true;
            else
               Pads[i].ButtonsSingle.LeftThumb = false;
         }
         // Right Thumbstick
         if(!Pads[i].Buttons.RightThumb)
            Pads[i].ButtonsSingle.RightThumb = false;
         else
         {
            if(!Pads[i].ButtonsSingle.RightThumb && !Pads[i].ButtonsOld.RightThumb)
               Pads[i].ButtonsSingle.RightThumb = true;
            else
               Pads[i].ButtonsSingle.RightThumb = false;
         }

         // DPad Up
         if(!Pads[i].DPad.Up)
            Pads[i].DPadSingle.Up = false;
         else
         {
            if(!Pads[i].DPadSingle.Up && !Pads[i].DPadOld.Up)
               Pads[i].DPadSingle.Up = true;
            else
               Pads[i].DPadSingle.Up = false;
         }
         // DPad Down
         if(!Pads[i].DPad.Down)
            Pads[i].DPadSingle.Down = false;
         else
         {
            if(!Pads[i].DPadSingle.Down && !Pads[i].DPadOld.Down)
               Pads[i].DPadSingle.Down = true;
            else
               Pads[i].DPadSingle.Down = false;
         }
         // DPad Left
         if(!Pads[i].DPad.Left)
            Pads[i].DPadSingle.Left = false;
         else
         {
            if(!Pads[i].DPadSingle.Left && !Pads[i].DPadOld.Left)
               Pads[i].DPadSingle.Left = true;
            else
               Pads[i].DPadSingle.Left = false;
         }
         // DPad Right
         if(!Pads[i].DPad.Right)
            Pads[i].DPadSingle.Right = false;
         else
         {
            if(!Pads[i].DPadSingle.Right && !Pads[i].DPadOld.Right)
               Pads[i].DPadSingle.Right = true;
            else
               Pads[i].DPadSingle.Right = false;
         }

         // whew. all done!
      }
      else
      {
         // error! error! abort!
         Pads[i].error = true;
      }
   }
}

// get the state of a given pad.
GamepadState XInputManager::GetState(int pad)
{
   // there are only 4 gamepads..
   if(pad > 3)
   {
      return PadError;
   }

   return Pads[pad];
}
// set the vibration rate of a given pad
void XInputManager::SetVibration(int pad, float left, float right)
{
   // we can't have more than 4 pads!
   if(pad > 3)
      return;

   // http://msdn.microsoft.com/en-us/library/bb173045(VS.85).aspx
   XINPUT_VIBRATION vibration;
   ZeroMemory( &vibration, sizeof(XINPUT_VIBRATION) );
   vibration.wLeftMotorSpeed = 65535 * left; // use any value between 0-65535 here
   vibration.wRightMotorSpeed = 65535 * right; // use any value between 0-65535 here
   XInputSetState( pad, &vibration );

}