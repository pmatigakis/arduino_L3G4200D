#include "L3G4200D.h"
#include "Wire.h"

//Constructor. Specify the address of the gyroscope
L3G4200D::L3G4200D(char device_address){
  _device_address = device_address;
}

/*
Initialize the gyroscope.
dr: the required data transmit rate
bw: bandwidth selection
axes: the axes to use
 */
void L3G4200D::begin(char dr, char bw, char axes){
  //enable the gyroscope and set the datarate and bandwith
  char ctrl_reg1 = dr | bw | axes;
  
  ctrl_reg1 |= PD;
  
  Wire.beginTransmission(_device_address);
  Wire.write(CTRL_REG1);
  Wire.write(ctrl_reg1);
  Wire.endTransmission();
}

//get the rotation on X axis
short L3G4200D::x_rotation(){
  short xr = (readRegister(OUT_X_H) << 8) | readRegister(OUT_X_L);

  return xr;
}

//get the rotation on Y axis
short L3G4200D::y_rotation(){
  short yr = (readRegister(OUT_Y_H) << 8) | readRegister(OUT_Y_L);

  return yr;
}

//get the rotation on z axis
short L3G4200D::z_rotation(){
  short zr = (readRegister(OUT_Z_H) << 8) | readRegister(OUT_Z_L);

  return zr;
}

//read the contents of a register
//register_address: the address of the register
char L3G4200D::readRegister(char register_address){
  Wire.beginTransmission(_device_address);
  Wire.write(register_address);
  Wire.endTransmission();

  Wire.requestFrom(_device_address, 1);
  while(!Wire.available()){}
  char data = Wire.read();

  return data;
}

//write a value to a register
//register_address: the address of the register
//data: the value to write
void L3G4200D::writeRegister(char register_address, char data){
  Wire.beginTransmission(_device_address);
  Wire.write(register_address);
  Wire.write(data);
  Wire.endTransmission();
}
