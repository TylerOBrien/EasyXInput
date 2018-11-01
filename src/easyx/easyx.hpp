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

#ifndef _EASYXINPUT_EASYX_HPP_
#define _EASYXINPUT_EASYX_HPP_

#include <stdint.h>
#include <windows.h>
#include <xinput.h>

namespace easyx {

enum {
  PLAYER_1, PLAYER_2, PLAYER_3, PLAYER_4
};

enum {
  START, BACK,
  DPAD_UP, DPAD_DOWN, DPAD_LEFT, DPAD_RIGHT,
  A, B, X, Y,
  LEFT_THUMB, RIGHT_THUMB,
  LEFT_BUMPER, RIGHT_BUMPER
};

enum {
  LEFT_ANALOG_X, LEFT_ANALOG_Y,
  RIGHT_ANALOG_X, RIGHT_ANALOG_Y
};

enum {
  LEFT_TRIGGER, RIGHT_TRIGGER
};

enum {
  UP = 0x0001,
  DOWN = 0x0010,
  PRESSED = 0x0100,
  RELEASED = 0x1000
};

extern int16_t __angles[XUSER_MAX_COUNT][4];
extern uint8_t __triggers[XUSER_MAX_COUNT][2];
extern uint32_t __states[XUSER_MAX_COUNT][14];

void prepare();
void update();

/**
  * @param gamepad_i
  * @param analog_i
  *
  * @author Tyler O'Brien <contact@tylerobrien.com>
  * */
inline int16_t analog(
  int8_t gamepad_i,
  int8_t analog_i)
{
  return __angles[gamepad_i][analog_i];
}

/**
  * @param gamepad_i
  * @param trigger_i
  *
  * @author Tyler O'Brien <contact@tylerobrien.com>
  * */
inline uint8_t trigger(
  int8_t gamepad_i,
  int8_t trigger_i)
{
  return __triggers[gamepad_i][trigger_i];
}

/**
  * @param gamepad_i
  * @param button_i
  *
  * @author Tyler O'Brien <contact@tylerobrien.com>
  * */
inline uint32_t button(
  int8_t gamepad_i,
  int8_t button_i)
{
  return __states[gamepad_i][button_i];
}

}

#endif