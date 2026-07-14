#include <Wire.h>
#include "imu.h"

bool imuInitialized = false;
uint8_t imuAddr = 0x68;
int16_t gyroBiasX = 0;
int16_t gyroBiasY = 0;
int16_t gyroBiasZ = 0;

static bool writeRegister(uint8_t addr, uint8_t reg, uint8_t val) {
  Wire.beginTransmission(addr);
  Wire.write(reg);
  Wire.write(val);
  return (Wire.endTransmission() == 0);
}

static bool readRegisters(uint8_t addr, uint8_t reg, uint8_t* buffer, uint8_t len) {
  Wire.beginTransmission(addr);
  Wire.write(reg);
  if (Wire.endTransmission(false) != 0) return false;  // false for repeated start
  
  Wire.requestFrom(addr, len);
  if (Wire.available() < len) return false; //number of bytes received in i2c buffer of mcu
  for (uint8_t i = 0; i < len; i++) {
    buffer[i] = Wire.read();
  }
  return true;
}

bool initIMU() {
  // probe i2c address (0x68 or 0x69), i chose 0x68
  Wire.beginTransmission(0x68);
  if (Wire.endTransmission() != 0) {
    Wire.beginTransmission(0x69);
    if (Wire.endTransmission() != 0) {
      Serial.println("imu device not found at 0x68 or 0x69");
      return false;
    }
    imuAddr = 0x69;
  } else {
    imuAddr = 0x68;
  }
  
  Serial.printf("imu found device at 0x%02x\n", imuAddr);
  
  // software reset
  writeRegister(imuAddr, 0x02, 0x10);
  delay(50); // wait for reset to complete
  
  // enable both gyro and accel in low noise (ln) mode
  writeRegister(imuAddr, 0x1F, 0x0F);
  delay(50); // wait for sensors to wake
  
  // configure gyro: ±250 dps ui range, 100 hz odr
  writeRegister(imuAddr, 0x20, 0x69);
  delay(10);
  
  // configure accel: ±2g ui range, 100 hz odr
  writeRegister(imuAddr, 0x21, 0x69);
  delay(10);
  
  imuInitialized = true;
  
  // calibrate gyro to find stationary biases
  calibrateIMU();
  
  return true;
}

void calibrateIMU() {
  Serial.println("[imu] calibrating gyro biases... please keep the ring stationary!");
  int32_t sumX = 0, sumY = 0, sumZ = 0;
  int samples = 100;
  int count = 0;
  
  while (count < samples) {
    int16_t accel[3], gyro[3];
    if (readIMUData(accel, gyro)) {
      sumX += gyro[0];
      sumY += gyro[1];
      sumZ += gyro[2];
      count++;
    }
    delay(10);
  }
  
  gyroBiasX = sumX / samples;
  gyroBiasY = sumY / samples;
  gyroBiasZ = sumZ / samples;
  Serial.printf("[imu] calibration complete. biases -> x: %d, y: %d, z: %d\n", gyroBiasX, gyroBiasY, gyroBiasZ);
}

bool readIMUData(int16_t accel[3], int16_t gyro[3]) {
  uint8_t buffer[12];
  if (!readRegisters(imuAddr, 0x0B, buffer, 12)) {
    return false;
  }
  
  // standard two's complement reconstruction
  accel[0] = (int16_t)((buffer[0] << 8) | buffer[1]);
  accel[1] = (int16_t)((buffer[2] << 8) | buffer[3]);
  accel[2] = (int16_t)((buffer[4] << 8) | buffer[5]);
  
  gyro[0] = (int16_t)((buffer[6] << 8) | buffer[7]);
  gyro[1] = (int16_t)((buffer[8] << 8) | buffer[9]);
  gyro[2] = (int16_t)((buffer[10] << 8) | buffer[11]);
  
  return true;
}
