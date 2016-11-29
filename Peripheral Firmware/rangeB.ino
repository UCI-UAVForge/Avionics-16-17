/* Code for Arduino Uno R3
Assumes the sensor is using the default address
Sensor Connections:
Pin 7 to GND
Pin 6 to 5V
Pin 5 to SCL
Pin 4 to SDA
Requires pull-ups for SCL and SDA connected to 5V to work reliably
*/

//#include <Wire.h>
#include <Adafruit_INA219.h>
#include "Wire.h"


#define address 0x1E //0011110b, I2C 7bit address of HMC5883


//The Arduino Wire library uses the 7-bit version of the address, so the code example uses 0x70 instead of the 8-bit 0xE0
#define SensorAddress byte(0x70)
//The sensors ranging command has a value of 0x51
#define RangeCommand byte(0x51)
//These are the two commands that need to be sent in sequence to change the sensor address
#define ChangeAddressCommand1 byte(0xAA)
#define ChangeAddressCommand2 byte(0xA5)

Adafruit_INA219 ina219;

#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
   #define Serial SerialUSB
#endif

void setup() {
 Serial.begin(115200); //Open serial connection at 9600 baud
 Wire.begin(); //Initiate Wire library for I2C communications with the I2CXL-MaxSonar-EZ


 //Put the HMC5883 IC into the correct operating mode
  Wire.beginTransmission(address); //open communication with HMC5883
  Wire.write(0x02); //select mode register
  Wire.write(0x00); //continuous measurement mode
  Wire.endTransmission();


  #ifndef ESP8266
    while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
  #endif
  uint32_t currentFrequency;
    
  Serial.println("Hello!");
  
 
}
void loop(){
 takeRangeReading(); //Tell the sensor to perform a ranging cycle
 delay(100); //Wait for sensor to finish
 word range = requestRange(); //Get the range from the sensor
 Serial.print("Range: "); Serial.println(range); //Print to the user

 //float rangetest = requestRange();
 //Serial.print("Range Test:   "); Serial.print(range);


  delay(1000);


  
 

}
//Commands the sensor to take a range reading
void takeRangeReading(){
 Wire.beginTransmission(SensorAddress); //Start addressing
 Wire.write(RangeCommand); //send range command
 Wire.endTransmission(); //Stop and do something else now
}
//Returns the last range that the sensor determined in its last ranging cycle in centimeters. Returns 0 if there is no communication.
word requestRange(){
 Wire.requestFrom(SensorAddress, byte(2));
 if(Wire.available() >= 2){ //Sensor responded with the two bytes
 byte HighByte = Wire.read(); //Read the high byte back
 byte LowByte = Wire.read(); //Read the low byte back
 word range = word(HighByte, LowByte); //Make a 16-bit word out of the two bytes for the range
 return range;
 }
 else {
 return word(0); //Else nothing was received, return 0
 }
}

/* Commands a sensor at oldAddress to change its address to newAddress
oldAddress must be the 7-bit form of the address that is used by Wire
7BitHuh determines whether newAddress is given as the new 7 bit version or the 8 bit version of the address
If true, if is the 7 bit version, if false, it is the 8 bit version
*/
void changeAddress(byte oldAddress, byte newAddress, boolean SevenBitHuh){
 Wire.beginTransmission(oldAddress); //Begin addressing
 Wire.write(ChangeAddressCommand1); //Send first change address command
 Wire.write(ChangeAddressCommand2); //Send second change address command
 byte temp;
 if(SevenBitHuh){ temp = newAddress << 1; } //The new address must be written to the sensor
 else { temp = newAddress; } //in the 8bit form, so this handles automatic shifting

 Wire.write(temp); //Send the new address to change to
 Wire.endTransmission();


 
  int x,y,z; //triple axis data

  //Tell the HMC5883 where to begin reading data
  Wire.beginTransmission(address);
  Wire.write(0x03); //select register 3, X MSB register
  Wire.endTransmission();
  
 
 //Read data from each axis, 2 registers per axis
  Wire.requestFrom(address, 6);
  if(6<=Wire.available()){
    x = Wire.read()<<8; //X msb
    x |= Wire.read(); //X lsb
    z = Wire.read()<<8; //Z msb
    z |= Wire.read(); //Z lsb
    y = Wire.read()<<8; //Y msb
    y |= Wire.read(); //Y lsb
  }
  
  //Print out values of each axis
  Serial.print("x: ");
  Serial.print(x);
  Serial.print("  y: ");
  Serial.print(y);
  Serial.print("  z: ");
  Serial.println(z);
  
  delay(1000);
} 






