#include <Servo.h>

const int p0 = 12,p1=13,p2=14,p3=15;
Servo s0,s1,s2,s3;
void setup() 
{
  Serial.begin(9600);
  pinMode(p0, INPUT);
  pinMode(p1, INPUT);
  pinMode(p2, INPUT);
  pinMode(p3, INPUT);
  s0.attach(6);
  s1.attach(7);
  s2.attach(8);
  s3.attach(9);

}

void loop() {
  int pr0 = analogRead(p0);
  int pr1 = analogRead(p1);
  int pr2 = analogRead(p2);
  int pr3 = analogRead(p3);
  int ps0 = map(pr0, 0, 1023, 0, 180);
  int ps1 = map(pr1, 0, 1023, 0, 180);
  int ps2 = map(pr2, 0, 1023, 0, 180);
  int ps3 = map(pr3, 0, 1023, 0, 180);
  s0.write(ps0);
  s1.write(ps1);
  s2.write(ps2);
  s3.write(ps3);
  Serial.print("Base: ");
  Serial.print(ps0);
  Serial.print("    Shoulder:");
  Serial.print(ps1);
  Serial.print("    Elbow:");
  Serial.print(ps2);
  Serial.print("    Claw:");
  Serial.println(ps3);
}
