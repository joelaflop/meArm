#include <Servo.h>
#include <math.h>

const int p0 = 0,p1=1;
Servo s0,s1;
String readstring="";
char c;
String rx, ry;
int x=100, y=100;
int i=0;
int j=0;
double q1=0,q2=0;
double b=0, bsq=0;
double a1=121, a2=75;
double olda1=121,oldq1=75;
double dega1=121,dega2=75;
double olddega1=121, olddega2=75;
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
  delay(1000);
  //printlife();

}
void doservo()
{
  printlife();
  dega1=a1*180/PI;
  dega2=a2*180/PI;
  double freq=.1;
  if(dega1<141&&dega1>34 && dega2<151&&dega1>26)
  {
    while((int)olddega1!=(int)dega1 || (int)olddega2!=(int)dega2)
    {
     if((int)olddega1<(int)dega1)
      {
        olddega1+=freq;
        s0.write(olddega1);
      }
      else if((int)olddega1>(int)dega1)
      {
        olddega1-=freq;
       s0.write(olddega1);
      }
      if((int)olddega2<(int)dega2)
      {
        olddega2+=freq;
        s1.write(olddega2);
      }
      else if((int)olddega2>(int)dega2)
      {
        olddega2-=freq;
        s1.write(olddega2);
      }
      printlife();
      delay(10);
      Serial.print("not equal");
    }

  }
  else
    Serial.print("  ***out of range***  ");
}
void invkin()
{
    b = sqrt(pow(x,2)+pow(y,2));
    bsq = pow(x,2)+pow(y,2);
    q1 = atan2(y,x);
    q2 = acos((bsq+bicepsq-forearmsq)/(2*forearm*b));
    a1 = (q1+q2);
    a2 = acos((bicepsq+forearmsq-bsq)/(2*forearm*bicep));  
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
    {
     i=0;
     readstring="";
     y=rx.toDouble();
     x=ry.toDouble();
    }
    readstring=""; rx="";ry="";
  }
}
void printlife()
{
     Serial.print("(");
     Serial.print(y);
     Serial.print(", ");
     Serial.print(x);
     Serial.print(")  olda1: ");
     Serial.print(olddega1);
     Serial.print(",  olda2: ");
     Serial.print(olddega2);
     Serial.print("     a1: ");
     Serial.print(dega1);
     Serial.print(",  a2: ");
     Serial.print(dega2);
     Serial.print("   hypot: ");
     Serial.println(b);
}

