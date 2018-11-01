/*
* EasyXInput
*
* https://tylerobrien.com
* https://github.com/TylerOBrien/EasyXInput
*
* Copyright (c) 2018 Tyler O'Brien
*
* Permission is hereby granted, free of charge, to any person obtaining
* a copy of this software and associated documentation files (the
* "Software"), to deal in the Software without restriction, including
* without limitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to
* permit persons to whom the Software is furnished to do so, subject to
* the following conditions:
*
* The above copyright notice and this permission notice shall be
* included in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
* LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
* OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
* WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
* */

#include "easyx.hpp"

namespace easyx {

int16_t __angles[XUSER_MAX_COUNT][4];
uint8_t __triggers[XUSER_MAX_COUNT][2];
uint32_t __states[XUSER_MAX_COUNT][14];

int16_t deadzones[] = {
  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE,
  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE,
  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE,
  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE
};

uint16_t buttons[] = {
  XINPUT_GAMEPAD_START,
  XINPUT_GAMEPAD_BACK,
  XINPUT_GAMEPAD_DPAD_UP,
  XINPUT_GAMEPAD_DPAD_DOWN,
  XINPUT_GAMEPAD_DPAD_LEFT,
  XINPUT_GAMEPAD_DPAD_RIGHT,
  XINPUT_GAMEPAD_A,
  XINPUT_GAMEPAD_B,
  XINPUT_GAMEPAD_X,
  XINPUT_GAMEPAD_Y,
  XINPUT_GAMEPAD_LEFT_THUMB,
  XINPUT_GAMEPAD_RIGHT_THUMB,
  XINPUT_GAMEPAD_LEFT_SHOULDER,
  XINPUT_GAMEPAD_RIGHT_SHOULDER
};

/**
  * @param gamepad_i
  * @param trigger_i
  * @param state
  *
  * @author Tyler O'Brien <contact@tylerobrien.com>
  * */
inline void handle_trigger(
  int8_t gamepad_i,
  int8_t trigger_i,
  XINPUT_STATE state)
{
  __triggers[gamepad_i][trigger_i] = *((int8_t*)&state.Gamepad + sizeof(WORD) + trigger_i);
}

/**
  * @param gamepad_i
  * @param analog_i
  * @param deadzone
  * @param state
  *
  * @author Tyler O'Brien <contact@tylerobrien.com>
  * */
inline void handle_analog(
  int8_t gamepad_i,
  int8_t analog_i,
  int16_t deadzone,
  XINPUT_STATE state)
{
  int16_t angle = *(SHORT*)((int8_t*)&state.Gamepad + sizeof(WORD) + 2 + (analog_i * 2));

  if (angle >= deadzone || angle <= -deadzone) {
    __angles[gamepad_i][analog_i] = angle;
  } else {
    __angles[gamepad_i][analog_i] = 0;
  }
}

/**
  * @param gamepad_i
  * @param button_i
  * @param button
  * @param state
  *
  * @author Tyler O'Brien <contact@tylerobrien.com>
  * */
inline void handle_button(
  int8_t gamepad_i,
  int8_t button_i,
  uint16_t button,
  XINPUT_STATE state)
{
  if (state.Gamepad.wButtons & button) {
    if (__states[gamepad_i][button_i] == UP) {
      __states[gamepad_i][button_i] = DOWN | PRESSED;
    } else if (__states[gamepad_i][button_i] == (DOWN | PRESSED)) {
      __states[gamepad_i][button_i] = DOWN;
    }
  } else {
    if (__states[gamepad_i][button_i] == DOWN) {
      __states[gamepad_i][button_i] = UP | RELEASED;
    } else if (__states[gamepad_i][button_i] == (UP | RELEASED)) {
      __states[gamepad_i][button_i] = UP;
    }
  }
}

/**
  * @author Tyler O'Brien <contact@tylerobrien.com>
  * */
void prepare() {
  for (int8_t i = 0; i < XUSER_MAX_COUNT; i++) {
    for (int8_t j = 0; j < (sizeof(buttons)/sizeof(buttons[0])); j++) {
      if (j < 4) {
        if (j < 2) {
          __triggers[i][j] = 0;
        }
        __angles[i][j] = 0;
      }
      __states[i][j] = UP;
    }
  }
}

/**
  * @author Tyler O'Brien <contact@tylerobrien.com>
  * */
void update() {
  XINPUT_STATE state;
  memset(&state, 0, sizeof(XINPUT_STATE));

  for (int8_t i = 0; i < XUSER_MAX_COUNT; i++) {
    if (XInputGetState(i, &state) == ERROR_SUCCESS) {
      for (int8_t j = 0; j < (sizeof(buttons)/sizeof(buttons[0])); j++) {
        if (j < 4) {
          if (j < 2) {
            handle_trigger(i, j, state);
          }
          handle_analog(i, j, deadzones[j], state);
        }
        handle_button(i, j, buttons[j], state);
      }
    }
  }
}

}