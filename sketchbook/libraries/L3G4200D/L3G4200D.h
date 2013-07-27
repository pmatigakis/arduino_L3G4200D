#ifndef L3G4200D_H
#define L3G4200D_H

#include "Arduino.h"

#define L3G4200D_ADDRESS_0 0x68
#define L3G4200D_ADDRESS_1 0x69
#define CTRL_REG1 0x20

#define DR_100HZ 0x00
#define DR_200HZ 0x40
#define DR_400HZ 0x80
#define DR_800HZ 0xc0

#define BW_00 0x00
#define BW_01 0x10
#define BW_10 0x20
#define BW_11 0x30

#define PD 0x08

#define X_EN 0x01
#define Y_EN 0x02
#define Z_EN 0x04

#define OUT_X_L 0x28
#define OUT_X_H 0x29
#define OUT_Y_L 0x2a
#define OUT_Y_H 0x2b
#define OUT_Z_L 0x2c
#define OUT_Z_H 0x2d

class L3G4200D{
  public:
  L3G4200D(char device_address);
  void begin(char dr, char bw, char axes);
  short x_rotation();
  short y_rotation();
  short z_rotation();

 private:
 char _device_address;
 char readRegister(char register_address);
 void writeRegister(char register_address, char data);
};

#endif
