#pragma once

#include <Adafruit_SSD1306.h>

extern Adafruit_SSD1306 display;

bool initDisplay();
void clearDisplay();
void printOLED(int x, int y, String text, int size = 1);
void drawStatusBar();
void timePrint(unsigned long time, int x, int y, int size);
