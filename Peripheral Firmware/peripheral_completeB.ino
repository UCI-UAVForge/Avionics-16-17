//#include <Wire.h>
#include <Adafruit_INA219.h>
#include "Wire.h"

#include <Adafruit_L3GD20.h>

// Comment this next line to use SPI
#define USE_I2C

#ifdef USE_I2C
  // The default constructor uses I2C
  Adafruit_L3GD20 gyro;
#else
  // To use SPI, you have to define the pins
  #define GYRO_CS 4 // labeled CS
  #define GYRO_DO 5 // labeled SA0
  #define GYRO_DI 6  // labeled SDA
  #define GYRO_CLK 7 // labeled SCL
  Adafruit_L3GD20 gyro(GYRO_CS, GYRO_DO, GYRO_DI, GYRO_CLK);
#endif

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
//MAGNETOMETER
//Initialize Serial and I2C communications
  Serial.begin(115200);
  Wire.begin();
  
  //Put the HMC5883 IC into the correct operating mode
  Wire.beginTransmission(address); //open communication with HMC5883
  Wire.write(0x02); //select mode register
  Wire.write(0x00); //continuous measurement mode
  Wire.endTransmission();

//RANGE
  Wire.beginTransmission(address); //open communication with HMC5883
  Wire.write(0x02); //select mode register
  Wire.write(0x00); //continuous measurement mode
  Wire.endTransmission();

//GYRO
// Try to initialise and warn if we couldn't detect the chip
  //if (!gyro.begin(gyro.L3DS20_RANGE_250DPS))
  //if (!gyro.begin(gyro.L3DS20_RANGE_500DPS))
  if (!gyro.begin(gyro.L3DS20_RANGE_2000DPS))
  {
    Serial.println("Oops ... unable to initialize the L3GD20. Check your wiring!");
    while (1);
  }

//CURRENT

  #ifndef ESP8266
    while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
  #endif
  uint32_t currentFrequency;
    
  Serial.println("Hello!");
  
  ina219.begin();

  Serial.println("Measuring voltage and current with INA219 ...");

}

void loop() {
//MAGNETOMETER
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

//RANGE
takeRangeReading(); //Tell the sensor to perform a ranging cycle
 delay(100); //Wait for sensor to finish
 word range = requestRange(); //Get the range from the sensor
 Serial.print("Range: "); Serial.println(range); //Print to the user

 //float rangetest = requestRange();
 //Serial.print("Range Test:   "); Serial.print(range);


  delay(1000);


//GYRO
  gyro.read();

  int gyroX = 0;
  int gyroY = 0;
  int gyroZ = 0;

  gyroX = (int)gyro.data.x;
  gyroY = (int)gyro.data.y;
  gyroZ = (int)gyro.data.z;
  
  
  Serial.print("Gyro X: "); Serial.print(gyroX);   Serial.println(" ");
  Serial.print("Gyro Y: "); Serial.print(gyroY);   Serial.println(" ");
  Serial.print("Gyro Z: "); Serial.println(gyroZ); Serial.println(" ");
  delay(1000);

}



//RANGE
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

//CURRENT

  float shuntvoltage = 0;
  float busvoltage = 0;
  float current_mA = 0;
  float loadvoltage = 0;

  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  loadvoltage = busvoltage + (shuntvoltage / 1000);
  
  Serial.print("Bus Voltage:   "); Serial.print(busvoltage); Serial.println(" V");
  Serial.print("Shunt Voltage: "); Serial.print(shuntvoltage); Serial.println(" mV");
  Serial.print("Load Voltage:  "); Serial.print(loadvoltage); Serial.println(" V");
  Serial.print("Current:       "); Serial.print(current_mA); Serial.println(" mA");
  Serial.println("");

  delay(1000);
} 


