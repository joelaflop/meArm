#include <Servo.h>
#include <math.h>

const int p0 = 0,p1=1;
Servo s0,s1,s2,s3,s4,s5,s6,s7;
String readstring="";
char c;
String rx, ry;
double x=100, y=100;
double oldx=100,oldy=100;
int i=0;
double q1=0,q2=0;
double b=0, bsq=0, dist=0;
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
  s5.attach(7);
  s6.attach(8);
  Serial.println("Enter the x and y values serpated by a space: ");

}

void loop() 
{
  getxandy();
  //invkin();
  doservo();
  printlife();
  delay(1000);


}
void doservo()
{
  double freq=5; double step=1;
  if(mu1<=mumax && mu1>=mumin && mu2<=mumax && mu2>=mumin)
  {

    dist = sqrt(((oldx-x)*(oldx-x))+((oldy-y)*(oldy-y)));
    for(double j=0; j<dist;j+=step)
    {
      Serial.print("for:");
      Serial.print(j);
      Serial.print(" ");
       oldx= (oldx- (oldx-x)*j/dist);
       oldy= (oldy- (oldy-y)*j/dist);
       invkin(oldx, oldy);
       s0.writeMicroseconds(mu1);
       s1.writeMicroseconds(mu2);
       s5.writeMicroseconds(mu1+200); //shoulder
       s6.writeMicroseconds(mu2+360); //elbow
       printlife();
       delay(50);
    }
    oldx=x;oldy=y;
    printlife();
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
    oldmu1=mu1; oldmu2=mu2;  
    mu1 = a1*(mumax-mumin)/PI +mumin;
    mu2 = a2*(mumax-mumin)/PI +mumin;
    dega1 = a1*180/PI;
    dega2 = a2*180/PI;
}
void invkin(double x,double y)
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
     oldy=y;
     oldx=x;
     x=rx.toDouble();
     y=ry.toDouble();
    }
    readstring=""; rx="";ry="";
  }
}
void printlife()
{
     Serial.print("new:(");
     Serial.print(x);
     Serial.print(", ");
     Serial.print(y);
     Serial.print(") old:(");
     Serial.print(oldx);
     Serial.print(", ");
     Serial.print(oldy);
     Serial.print(")   oldmu1: ");
     Serial.print(oldmu1);
     Serial.print(", oldmu2: ");
     Serial.print(oldmu2);
     Serial.print("      mu1: ");
     Serial.print(mu1);
     Serial.print(", mu2: ");
     Serial.print(mu2);
     Serial.print("     hypot: ");
     Serial.print(b);
     Serial.print(", dist: ");
     Serial.print(dist);
     Serial.print("      a1: ");
     Serial.print(dega1);
     Serial.print(", a2: ");
     Serial.print(dega2);
     Serial.print("       q1: ");
     Serial.print(q1*180/PI);
     Serial.print(", q2: ");
     Serial.println(q2*180/PI);
}

