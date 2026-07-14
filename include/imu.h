#pragma once
#include <Arduino.h>

extern bool imuInitialized;
extern uint8_t imuAddr;
extern int16_t gyroBiasX;
extern int16_t gyroBiasY;
extern int16_t gyroBiasZ;

// initialize imu
bool initIMU();

// read raw data from accelerometer and gyroscope
bool readIMUData(int16_t accel[3], int16_t gyro[3]);

// calibrate gyro offsets by averaging stationary samples
void calibrateIMU();
