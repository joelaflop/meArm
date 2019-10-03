#include <Servo.h>

const int p0 = 12,p1=13,p2=14,p3=15;
const int p4=4,p5=5,p6=6,p7=7;
Servo s0,s1,s2,s3;
Servo s4,s5,s6,s7;
void setup() 
{
  Serial.begin(115200);
  pinMode(p0, INPUT);
  pinMode(p1, INPUT);
  pinMode(p2, INPUT);
  pinMode(p3, INPUT);
  pinMode(p4, INPUT);
  pinMode(p5, INPUT);
  pinMode(p6, INPUT);
  pinMode(p7, INPUT);
  s0.attach(6);
  s1.attach(7);
  s2.attach(8);
  s3.attach(9);
  s4.attach(10);
  s5.attach(11);
  s6.attach(12);
  s7.attach(13);

}

void loop() {
  int pr0 = analogRead(p0);
  int pr1 = analogRead(p1);
  int pr2 = analogRead(p2);
  int pr3 = analogRead(p3);
  int pr4 = analogRead(p4);
  int pr5 = analogRead(p5);
  int pr6 = analogRead(p6);
  int pr7 = analogRead(p7);
  
  int ps0 = map(pr0, 0, 1023, 500, 2250);
  int ps1 = map(pr1, 0, 1023, 500, 2250);
  int ps2 = map(pr2, 0, 1023, 500, 2250);
  int ps3 = map(pr3, 0, 1023, 800, 2250);
  int ps4 = map(pr4, 0, 1023, 500, 2250);
  int ps5 = map(pr5, 0, 1023, 500, 2250);
  int ps6 = map(pr6, 0, 1023, 800, 2250);
  int ps7 = map(pr7, 0, 1023, 500, 2250);
  
  s0.writeMicroseconds(ps0);
  s1.writeMicroseconds(ps1);
  s2.writeMicroseconds(ps2);
  s3.writeMicroseconds(ps3);
  s4.writeMicroseconds(ps4);
  s5.writeMicroseconds(ps5);
  s6.writeMicroseconds(ps6);
  s7.writeMicroseconds(ps7);
  
  Serial.print("Base: ");
  Serial.print(ps0);
  Serial.print("    Shoulder:");
  Serial.print(ps1);
  Serial.print("    Elbow:");
  Serial.print(ps2);
  Serial.print("    Claw:");
  Serial.print(ps3);
  Serial.print("         Base: ");
  Serial.print(ps4);
  Serial.print("    Shoulder:");
  Serial.print(ps5);
  Serial.print("    Elbow:");
  Serial.print(ps6);
  Serial.print("    Claw:");
  Serial.println(ps7);
}
