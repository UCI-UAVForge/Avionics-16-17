#include <Wire.h>

const int HMC6343Address_write = 0x32; //for write operations
const int HMC6343Address_read = 0x33; //for read operation
// the operation is a read (LSb=1) or a write (LSb=0)
int headingValue = 0;
int tiltValue = 0;
int rollValue = 0;
byte headingData[6];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);  // Start serial communication at 115200 baud
  delay(500); //Give it half a second to wake up
  Wire.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  //between values, the sensor needs 200ms b/w measurements!
}

void getSensorData(){
  Wire.begin(HMC6343Address_write);
  Wire.write(0x50);    //Post Heading Data
  Wire.endTransmission();
  delay(1); //Sensor needs at least 1ms delay
  Wire.requestFrom(HMC6343Address_write,6);
  int i = 0;
  while(Wire.available() && i < 6){
    headingData[i] = Wire.read();
    i++;
  }
}

void convertDataToValues()
{
 headingValue = headingData[0]*256 + headingData[1];  // Put the MSB and LSB together
 tiltValue = headingData[2]*256 + headingData[3] + 900;     // Put the MSB and LSB together
 rollValue = headingData[4]*256 + headingData[5] + 1800;     // Put the MSB and LSB together
}

//The HMC6343 has three operational modes; Sleep, Standby, and Run. Sleep mode is defined as having the analog
//circuitry powered off, and has the lowest power consumption while power is applied to the VDD pins. Standby mode has
//the HMC6343 fully powered, but with no measurements performed and the processor is waiting for commands to perform.
//Run mode is fully engaged in continuous measurements at the configured rate, and ready to receive further commands.
//The operational mode settings are stored in EEPROM register 0x04, and shown further the HMC6343 protocol definition.
void standbyToRun(){
  Wire.begin(HMC6343Address_write);
  Wire.write(0x75);    
  Wire.endTransmission();
  delay(0.3);
}

void runToStandby(){
  Wire.begin(HMC6343Address_write);
  Wire.write(0x76);    
  Wire.endTransmission();
  delay(0.3);
}

void runToSleep(){
  Wire.begin(HMC6343Address_write);
  Wire.write(0x83);    
  Wire.endTransmission();
  delay(1);
}

void sleeptoStandby(){
  Wire.begin(HMC6343Address_write);
  Wire.write(0x84);    
  Wire.endTransmission();
  delay(20.3); //20 ms to exit sleep and 0.3 to enter standby
}

