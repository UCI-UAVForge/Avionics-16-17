int sensor1 = 1;
int sensor2 = 2;
int sensor3 = 3;
int sensor4 = 4;
int sensor5 = 5;
int sensor6 = 6;
int sensor7 = 7;
int sensor8 = 8;
int sensor9 = 9;
int sensor10 = 10;
int sensor11 = 11;
int sensor12 = 12;
int sensor13 = 13;
int sensor14 = 14;
int sensor15 = 15;
int sensor16 = 16;
int sensor17 = 17;
int sensor18 = 18;
int sensor19 = 19;
int sensor20 = 20;


void setup() {
  // put your setup code here, to run once:
  pinMode(sensor1, OUTPUT);
  pinMode(sensor2, OUTPUT);
  pinMode(sensor3, OUTPUT);
  pinMode(sensor4, OUTPUT);
  pinMode(sensor5, OUTPUT);
  pinMode(sensor6, OUTPUT);
  pinMode(sensor7, OUTPUT);
  pinMode(sensor8, OUTPUT);
  pinMode(sensor9, OUTPUT);
  pinMode(sensor10, OUTPUT);
  pinMode(sensor11, OUTPUT);
  pinMode(sensor12, OUTPUT);
  pinMode(sensor13, OUTPUT);
  pinMode(sensor14, OUTPUT);
  pinMode(sensor15, OUTPUT);
  pinMode(sensor16, OUTPUT);
  pinMode(sensor17, OUTPUT);
  pinMode(sensor18, OUTPUT);
  pinMode(sensor19, OUTPUT);
  pinMode(sensor20, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void turnSensorOnOff(int sensor, int onOff) {
  if ( onOff == 1) {
    digitalWrite(sensor, HIGH);
  }
  else if (onOff == 0) {
    digitalWrite(sensor, LOW);
  }
}

