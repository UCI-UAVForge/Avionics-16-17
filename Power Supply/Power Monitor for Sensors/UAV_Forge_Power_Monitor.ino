#include <Wire.h>

const int configuration_reg = 0x0;
const int shunt_voltage_reg = 0x1;
const int bus_voltage_reg = 0x2;
const int power_reg = 0x3;
const int  current_reg= 0x4;
const int calibration_reg = 0x5; 
const int ina219_i2caddr = 0b1000000;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  setConfiguration();           //specifies the mode for configuration register
}                     //currently at shunt and bus triggered

void loop() {
  // put your main code here, to run repeatedly:
 int16_t value = read_shunt_voltage();
}

int16_t read_shunt_voltage(){
  return read_register(shunt_voltage_reg);
}

int16_t read_bus_voltage(){
  return read_register(bus_voltage_reg);
}

int16_t read_power(){
  return read_register(power_reg);
}

int16_t read_current(){
  return read_register(current_reg);
}

int16_t read_register(int register_num){
  Wire.beginTransmission(ina219_i2caddr);
  Wire.write(register_num);
  Wire.requestFrom(ina219_i2caddr,2);
  int h = Wire.read();
  int l = Wire.read();
  Wire.endTransmission();
  return (h << 8) | l;
}

void setConfiguration(){
  Wire.beginTransmission(ina219_i2caddr);
  Wire.write(configuration_reg);
  Wire.write(0x219B);
  Wire.endTransmission();
  Wire.beginTransmission(ina219_i2caddr);
  Wire.write(calibration_reg);
  Wire.write(0x5761);
  Wire.endTransmission();

}


