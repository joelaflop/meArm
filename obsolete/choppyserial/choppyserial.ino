#include <Servo.h>
#include <math.h>

const int p0 = 0,p1=1;
Servo s0,s1;
String readstring="";
char c;
String rx, ry;
int x=0, y=0;
int i=0;
int j=0;
double q1=0,q2=0;
double a1=0, a2=0;
double b=0, bsq=0;
double olda1=0,oldq1=0;
double bicep = 81, forearm=81;
double bicepsq = pow(81,2), forearmsq = pow(81,2);

void setup() 
{
  Serial.begin(115200);
  pinMode(p0, INPUT);
  pinMode(p1, INPUT);
  s0.attach(11);  //arm
  s1.attach(12);  //forearm
  Serial.println("Enter the x and y values serpated by a space: ");

}

void loop() 
{
  getxandy();
  invkin();
  doservo();
     /*Serial.print("(");
     Serial.print(x);
     Serial.print(", ");
     Serial.print(y);
     Serial.print(")  a1: ");
     Serial.print(dega1);
     Serial.print(",  a2: ");
     Serial.print(dega2);
     Serial.print("   hypot: ");
     Serial.println(b);*/

  /*Serial.print(ps0);
  Serial.print("  ");
  Serial.println(ps1);*/

}
void doservo()
{
  double dega1=a1*180/PI;
  double dega2=a2*180/PI;
  if(dega1<141&&dega1>34 && dega2<151&&dega1>26)
  {
    s0.write(dega1);
    s1.write(dega2);
     Serial.print("(");
     Serial.print(x);
     Serial.print(", ");
     Serial.print(y);
     Serial.print(")  a1: ");
     Serial.print(dega1);
     Serial.print(",  a2: ");
     Serial.print(dega2);
     Serial.print("   hypot: ");
     Serial.println(b);
  }
  else
  {Serial.print("  ***out of range***  ");
     Serial.print("(");
     Serial.print(x);
     Serial.print(", ");
     Serial.print(y);
     Serial.print(")  a1: ");
     Serial.print(dega1);
     Serial.print(",  a2: ");
     Serial.print(dega2);
     Serial.print("   hypot: ");
     Serial.println(b);
  }
}
void invkin()
{
    b = sqrt(pow(x,2)+pow(y,2));
    bsq = pow(x,2)+pow(y,2);
    q1 = atan2(y,x);
    q2 = acos((bsq+bicepsq-forearmsq)/(2*forearm*b));
    a1 = (q1+q2);
    a2 = acos((bicepsq+forearmsq-bsq)/(2*forearm*bicep));  
    /*delay(1000);
    Serial.print(a1*180/PI);  
    Serial.print("  ");
    Serial.println(a2*180/PI);*/
}

void getxandy()
{
  while (Serial.available()) 
  {
    c = Serial.read();  //gets one byte from serial buffer
    readstring+=c;
    delayMicroseconds(2000);  //slow looping to allow buffer to fill
  }

  if(readstring!="");
  {
    while(readstring!=""&&readstring.charAt(i)!=' ') 
    {
      rx+=readstring.charAt(i);
      i++;
    }
    while(readstring!=""&&i<readstring.length())
    {
      ry+=readstring.charAt(i+1);
      i++;
    }
    if(i==readstring.length()&&i!=0)
    {//Serial.print("if");Serial.print("   ");
     i=0;
     readstring="";
     y=rx.toDouble();
     x=ry.toDouble();
    }
    readstring=""; rx="";ry="";
  }
}
