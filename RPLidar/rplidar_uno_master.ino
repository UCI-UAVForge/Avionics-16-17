// This sketch code is based on the RPLIDAR driver library provided by RoboPeak
#include <RPLidar.h>
#include <Wire.h>

// You need to create an driver instance 
RPLidar lidar;

#define RPLIDAR_MOTOR 3 // The PWM pin for control the speed of RPLIDAR's motor.
                        // This pin should connected with the RPLIDAR's MOTOCTRL signal 
                       
                        
void setup() {
  // bind the RPLIDAR driver to the arduino hardware serial
  lidar.begin(Serial);

  // begin I2C (master)
  Wire.begin();
  
  // set pin modes
  pinMode(RPLIDAR_MOTOR, OUTPUT);
}

void loop() {
  if (IS_OK(lidar.waitPoint())) {
    float distance = lidar.getCurrentPoint().distance; //distance value in mm unit
    float angle    = lidar.getCurrentPoint().angle; //anglue value in degree
    bool  startBit = lidar.getCurrentPoint().startBit; //whether this point is belong to a new scan
    byte  quality  = lidar.getCurrentPoint().quality; //quality of the current measurement

    // convert to bytes
    byte distanceBytes[4];
    byte angleBytes[4];
    floatToByte(distance, distanceBytes);
    floatToByte(angle, angleBytes);

    // transmission I2C
    Wire.beginTransmission(8);
    Wire.write(distanceBytes, 4);
    Wire.write(angleBytes, 4);
    Wire.write(startBit);
    Wire.write(quality);
    Wire.endTransmission();
    
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

// for float to byte conversion (I2C communication sends bytes)
void floatToByte(float value, byte* byteArray) {
  // create union for copying byte array
  union {
    float floatVar;
    byte tempArray[4];
  } u;
  // overwrite bytes in union with float
  u.floatVar = value;

  // assign bytes to input byte array
  memcpy(byteArray, u.tempArray, 4);
}

