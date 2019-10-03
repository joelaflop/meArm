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
double a1=0, a2=0, dega1=0,dega2=0;
double olda1=0,olda2=0;
double oldmu1=1500,oldmu2=1500,mu1=1499,mu2=1499;
double bicep = 81, forearm=81;
double bicepsq = pow(bicep,2), forearmsq = pow(forearm,2);
double mumax = 2400, mumin = 1000;

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
  delay(500);
  //printlife();

}
void doservo()
{
  printlife();
  double freq=5;
  //oldmu1=mu1,oldmu2=mu2;
  if(mu1<=mumax && mu1>=mumin && mu2<=mumax && mu2>=mumin)
  {
    while((int)oldmu1/10!=(int)mu1/10 || (int)oldmu2/10!=(int)mu2/10)
    {
     if((int)oldmu1<(int)mu1)
      {
        oldmu1+=freq;
        s1.writeMicroseconds(oldmu1);
      }
      else if((int)oldmu1>(int)mu1)
      {
        oldmu1-=freq;
       s1.writeMicroseconds(oldmu1);  //i switched s1 and s0
      }
      if((int)oldmu2<(int)mu2)
      {
        oldmu2+=freq;
        s0.writeMicroseconds(oldmu2);
      }
      else if((int)oldmu2>(int)mu2)
      {
        oldmu2-=freq;
        s0.writeMicroseconds(oldmu2);
      }
      Serial.print("not equal");      
      printlife();
      //delayMicroseconds(2);
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
    mu1 = a1*(mumax-mumin)/PI +mumin;
    mu2 = a2*(mumax-mumin)/PI +mumin;
    dega1 = a1*180/PI;
    dega2 = a2*180/PI;
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
     Serial.print(")  oldmu1: ");
     Serial.print(oldmu1);
     Serial.print(",  oldmu2: ");
     Serial.print(oldmu2);
     /*Serial.print("     a1: ");
     Serial.print(a1/PI);
     Serial.print(",  a2: ");
     Serial.print(a2/PI);*/
     Serial.print("     mu1: ");
     Serial.print(mu1);
     Serial.print(",  mu2: ");
     Serial.print(mu2);
     Serial.print("   hypot: ");
     Serial.print(b);
     Serial.print("     a1: ");
     Serial.print(dega1);
     Serial.print(",  a2: ");
     Serial.print(dega2);
     Serial.print("     q1: ");
     Serial.print(q1*180/PI);
     Serial.print(",  q2: ");
     Serial.println(q2*180/PI);
}

