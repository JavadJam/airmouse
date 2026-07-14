#pragma once

#include <Arduino.h>

// oled
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C
#define I2C_SDA 8
#define I2C_SCL 9

// menu buttons
constexpr int BTN_LEFT = 1;
constexpr int BTN_RIGHT = 10;

// touchpad inputs
constexpr int PIN_TOUCH_LEFT = 20;  // pin for left-click touchpad
constexpr int PIN_TOUCH_TASK = 21;  // pin for task-view touchpad
#define TOUCH_PRESSED HIGH          // ttp223 default output is high when touched (change to low if active-low)

// battery
constexpr int BATTERY_PIN = 0; // changed from a0 to 0
constexpr float BATTERY_MIN = 3.0f;
constexpr float BATTERY_MAX = 4.2f;

// i2s microphone
#define I2S_SD 5
#define I2S_SCK 6
#define I2S_WS 7
#define I2S_PORT_0 I2S_NUM_0

// air mouse gyro configuration
constexpr int GYRO_DEADZONE = 40;          // ignore gyro values below this threshold to prevent drift
constexpr int SENSITIVITY_DIVIDER = 240;   // higher values make the cursor move slower

#define AUDIO_SAMPLES 64

// initial clock time
constexpr unsigned long INIT_HOUR = 12;
constexpr unsigned long INIT_MIN = 30;
constexpr unsigned long INIT_SEC = 0;
