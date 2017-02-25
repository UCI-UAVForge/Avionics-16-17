#include <Wire.h>

void setup() {
  // begin I2C
  Wire.begin(8);
  Wire.onReceive(receiveEvent);

  // begin Serial (for serial monitor display)
  Serial.begin(115200);

}

void loop() {
  delay(100);

}

// function that executes whenever data is received from master
void receiveEvent(int howMany) {

  // for storing floats
  float distance;
  float angle;
  bool  startBit;
  byte  quality;
  
  // for receiving bytes
  byte allData[10];

  // receive all sent data
  if (Wire.available()) {
    int i = 0;
    while (Wire.available()) {
      allData[i] = Wire.read();
      i++;
    }
  }

  // store data
  dataToFloat(allData, distance, angle);
  startBit = allData[8];
  quality = allData[9];

  Serial.println(distance);
  Serial.println(angle);
}

// function for converting distance/angle bytes to float
void dataToFloat (byte* data, float distance, float angle) {
  // get distance bytes into union
  union distanceData {
    byte distanceBytes[4];
    float distanceValue;
  } dData;
  dData.distanceBytes[0] = data[0];
  dData.distanceBytes[1] = data[1];
  dData.distanceBytes[2] = data[2];
  dData.distanceBytes[3] = data[3];
  // set distance
  distance = dData.distanceValue;

  // get angle bytes into union
  union angleData {
    byte angleBytes[4];
    float angleValue;
  } aData;
  aData.angleBytes[0] = data[4];
  aData.angleBytes[1] = data[5];
  aData.angleBytes[2] = data[6];
  aData.angleBytes[3] = data[7];
  // set angle
  angle = aData.angleValue;
}

