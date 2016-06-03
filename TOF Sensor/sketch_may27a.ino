int q1Pin = 31;
int q2Pin = 37;
//int laser = 43;
int q1Val = 0;
int q2Val = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(q1Pin, INPUT);
  pinMode(q2Pin, INPUT);
  //pinMode(laser, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  q1Val = digitalRead(q1Pin);
  q2Val = digitalRead(q2Pin);
  
  //digitalWrite(laser, q1Val);
  
  Serial.print("Q1: ");
  Serial.println(q1Val);
  delay(100);
  Serial.print("Q2: ");
  Serial.println(q2Val);
  delay(100);
}
