// RPLIDAR Arduino Uno slave writer program
// File name: rplidar_uno_slave.ino
// Author: Kyle Lam
// Date: 2/27/16
// Revision: 1.1
// SLAVE WRITER for UNO

#include <RPLidar.h>
#include <Wire.h>

RPLidar lidar;

#define RPLIDAR_MOTOR 3 // The PWM pin for control the speed of RPLIDAR's motor.
                        // This pin should connected with the RPLIDAR's MOTOCTRL signal
                        
volatile byte* distanceBytes;
volatile byte* angleBytes;
volatile byte* startBytes;

float distance;
float angle;
bool startBit;
byte quality;

void setup() {
  // bind the RPLIDAR driver to the arduino hardware serial
  lidar.begin(Serial);

  // initialize i2c, listen for write request
  Wire.begin(8);
  Wire.onRequest(requestEvent);

  // set pin modes
  pinMode(RPLIDAR_MOTOR, OUTPUT);
}

void loop() {
  if (IS_OK(lidar.waitPoint())) {
    distance = lidar.getCurrentPoint().distance; //distance value in mm unit
    angle    = lidar.getCurrentPoint().angle; //anglue value in degree
    startBit = lidar.getCurrentPoint().startBit; //whether this point is belong to a new scan
    quality  = lidar.getCurrentPoint().quality; //quality of the current measurement

//    // convert to bytes
//    byte distanceBytes[4];
//    byte angleBytes[4];
//    floatToByte(distance, distanceBytes);
//    floatToByte(angle, angleBytes);
    
  } else {
    analogWrite(RPLIDAR_MOTOR, 0); //stop the rplidar motor
    
    // try to detect RPLIDAR... 
    rplidar_response_device_info_t info;
    if (IS_OK(lidar.getDeviceInfo(info, 100))) {
       // detected...
       lidar.startScan();
       
       // start motor rotating at max allowed speed
       analogWrite(RPLIDAR_MOTOR, 255);
       delay(1000);
    }
  }
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  byte* sendData;
  
  distanceBytes = (byte*) &distance;
  angleBytes = (byte*) &angle;
//  startBytes = (byte*) &startBit;
  
  sendData[0] = distanceBytes[0];
  sendData[1] = distanceBytes[1];
  sendData[2] = distanceBytes[2];
  sendData[3] = distanceBytes[3];
  sendData[4] = angleBytes[0];
  sendData[5] = angleBytes[1];
  sendData[6] = angleBytes[2];
  sendData[7] = angleBytes[3];
//  sendData[8] = startBytes[0];
//  sendData[9] = startBytes[1];
//  sendData[10] = quality;
  
  Wire.write(sendData, 8);
}

//// for float to byte conversion (I2C communication sends bytes)
//void floatToByte(float value, byte* byteArray) {
//  // create union for copying byte array
//  union {
//    float floatVar;
//    byte tempArray[4];
//  } u;
//  // overwrite bytes in union with float
//  u.floatVar = value;
//
//  // assign bytes to input byte array
//  memcpy(byteArray, u.tempArray, 4);
//}
