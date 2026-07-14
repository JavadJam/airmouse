#pragma once

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <NimBLEDevice.h>
#include <NimBLEHIDDevice.h>
#include "config.h"

struct DonglePacket {
  short mouseX;
  short mouseY;
  bool rightClick;
  bool leftClick;
  short action;
  int16_t audio[AUDIO_SAMPLES];
};

// system
extern bool micOn;
extern String btName;
extern int batteryLevel;

// ui navigation
extern int currentScreen;
extern int menuIndex;
extern const char* menuItems[];

// clock
extern unsigned long clockTime;
extern unsigned long lastUpdateMs;
extern unsigned long lastOledRefreshMs;
extern bool noSleep;
extern bool initialSleepRender;
extern bool blockLeftClick;
extern bool blockBothClick;

// stopwatch
extern unsigned long swStartTime;
extern unsigned long swElapsed;
extern unsigned long swPauseOffset;
extern bool swRunning;
extern int swState;

// timer
extern unsigned long tmSetupSeconds;
extern unsigned long tmStartTime;
extern unsigned long tmElapsed;
extern unsigned long tmPauseOffset;
extern bool tmRunning;
extern int tmState;
extern int tmSetupField;
extern unsigned long tmSetH;
extern unsigned long tmSetM;
extern unsigned long tmSetS;

// set clock
extern int scField;
extern unsigned long scSetH;
extern unsigned long scSetM;
extern unsigned long scSetS;

// dongle / audio
extern bool mic;
extern volatile bool mode;
extern unsigned int dongleCheck;
extern uint8_t receiverAddress[];
extern volatile int sendFailureCounter;
extern DonglePacket dataPacket;
extern int32_t rawBuffer[AUDIO_SAMPLES];

// bluetooth hid
extern NimBLEServer* pServer;
extern NimBLEHIDDevice* pHid;
extern NimBLECharacteristic* pMouseInput;
extern NimBLECharacteristic* pKeyInput;
extern bool deviceConnected;
extern bool bleAdvertisingActive;
extern unsigned long winKeyTimer;
extern int winKeyState;

// air mouse state
extern int16_t accumMouseX;
extern int16_t accumMouseY;
extern bool leftClicked;
extern bool taskViewTriggered;

extern TaskHandle_t audioTaskHandle;
