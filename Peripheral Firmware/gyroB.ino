#include <Wire.h> 
#include <Adafruit_L3GD20.h>

#define USE_I2C

#ifdef USE_I2C

  Adafruit_L3GD20 gyro;
  
#else

  // To use SPI, you have to define the pins
  #define GYRO_CS 4 // labeled CS
  #define GYRO_DO 5 // labeled SA0
  #define GYRO_DI 6  // labeled SDA
  #define GYRO_CLK 7 // labeled SCL
  Adafruit_L3GD20 gyro(GYRO_CS, GYRO_DO, GYRO_DI, GYRO_CLK);
  
#endif

void setup() 
{
  Serial.begin(115200);
  
  // Try to initialise and warn if we couldn't detect the chip
  //if (!gyro.begin(gyro.L3DS20_RANGE_250DPS))
  //if (!gyro.begin(gyro.L3DS20_RANGE_500DPS))
  if (!gyro.begin(gyro.L3DS20_RANGE_2000DPS))
  {
    Serial.println("Oops ... unable to initialize the L3GD20. Check your wiring!");
    while (1);
  }
  
}

void loop() 
{
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
