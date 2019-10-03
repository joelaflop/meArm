#include <Servo.h>

const int p0 = 1,p1=2;
Servo s0,s1;

void setup() 
{
  Serial.begin(115200);
  pinMode(p0, INPUT);
  pinMode(p1, INPUT);
  s0.attach(11);
  s1.attach(12);

}

void loop() {
  int pr0 = analogRead(p0);
  int pr1 = analogRead(p1);
  int ps0 = map(pr0, 0, 1023, 0, 180);
  int ps1 = map(pr1, 0, 1023, 0, 180);
  s0.write(ps0);
  s1.write(ps1);
  Serial.print(ps0);
  Serial.print("  ");
  Serial.println(ps1);

}
