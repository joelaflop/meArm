#include <Servo.h>
#include <math.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,5,4,3,2);
String readstring="";
char c;
String rx, ry, rz, rc;
const int p4=4,p5=5,p6=6,p7=7;
//int i=0; might have to put back in but doubtfully
Servo sv0,sv1,sv2,sv3, sv4,sv5,sv6,sv7;
double pr4,pr5,pr6,pr7;
double ps4,ps5,ps6,ps7;
double a0,a1,ra1,a2;
double bicep=81, forearm=81, wrist=68;  //81 81 68
double x=0,y=81,z=81,cl=1;
double _x=0,_y=81,_z=81;
double NX=81,NY=81,NZ=81;

// CALIBRATED FOR ALL CLEAR ARM ONLY***********
void setup() 
{
  Serial.begin(115200);
  pinMode(p4, INPUT);
  pinMode(p5, INPUT);
  pinMode(p6, INPUT);
  pinMode(p7, INPUT);
  sv0.attach(22);
  sv1.attach(24);
  sv2.attach(26);
  sv3.attach(28);
  sv4.attach(30);
  sv5.attach(32);
  sv6.attach(34);
  sv7.attach(36);
}
void loop() 
{
  getxyz();
  driftToHere(x,y,z,cl);
  //whipToHere(x,y,z,cl);
  //printmath();
  //plotmath();
  //delay(500);
  //serialToServo();
  //doallpot();
}
void serialToServo()
{
  getxyz();
  sv4.write(x);
  sv5.write(y);
  sv6.write(z);
  sv7.write(x); 
}
void doallpot()
{
  readandmappot();
  writepots();
  //printpots();
  plotpots();
}

void driftToHere(double XX,double YY,double ZZ,double CL)
{
  double distanceToTravel = sqrt((_x-XX)*(_x-XX) + (_y-YY)*(_y-YY) + (_z-ZZ)*(_z-ZZ));
  double stepMe =.5;
  for(double j = 0; j < distanceToTravel; j+= stepMe)
  { 
     NX = _x + (XX-_x) * j/distanceToTravel;
     NY = _y + (YY-_y) * j/distanceToTravel;
     NZ = _z + (ZZ-_z) * j/distanceToTravel;
     whipToHere(NX, NY, NZ, CL);
     Serial.print("   x: ");
     Serial.print(NX);
     Serial.print("   y: ");
     Serial.print(NY);
     Serial.print("    z: ");
     Serial.print(NZ);
     Serial.print("   D0:");
     Serial.print(toPWM(a0)+137);
     Serial.print("  D1:");
     Serial.print(toPWM(a1)-237);
     Serial.print("  rD1:");
     Serial.print(toPWM(ra1)-237);
     Serial.print("  D2:");
     Serial.print(toPWM(a2)+445);
     delayMicroseconds(100);
  }
  cl =CL;
  whipToHere(x, y, z, cl);
  _x=x;
  _y=y;
  _z=z;
  delayMicroseconds(100);
}
void whipToHere(double XX,double YY,double ZZ, double CL)
{
  solveangles3d(XX,YY,ZZ, CL);
  //gotoangles(a0,ra1,a2);
  gotoPWM(a0,ra1,a2, cl);
}
void readandmappot()
{
  pr4 = analogRead(p4);
  pr5 = analogRead(p5);
  pr6 = analogRead(p6);
  pr7 = analogRead(p7);
  
  ps4 = map(pr4, 0, 1023, 500, 2250);
  ps5 = map(pr5, 0, 1023, 500, 2250); //melt the thing for this joint to go lower
  ps6 = map(pr6, 0, 1023, 500, 2250);
  ps7 = map(pr7, 0, 1023, 500, 2250);
}
void getxyz()
{
  int i=0;
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
      Serial.println("w1");
    }
    while(readstring!=""&&i<readstring.length()&&readstring.charAt(i+1)!=' ')
    {
      ry+=readstring.charAt(i+1);
      i++;
      Serial.println("w2");
    }
    while(readstring!=""&&i<readstring.length()&&readstring.charAt(i+2)!=' ')
    {
      rz+=readstring.charAt(i+2);
      i++;
      Serial.println("w3");
    }
    while(readstring!=""&&i<readstring.length())
    {
      rc+=readstring.charAt(i+2);
      i++;
      Serial.println("w4");
    }
    if(i==readstring.length()&&i!=0)
    {
     i=0;
     readstring="";
     x=rx.toDouble();
     y=ry.toDouble();
     z=rz.toDouble();
     cl=rc.toDouble();
    }
    readstring="";
    rx="";
    ry="";
    rz="";
    rc="";
  }
}
void solveangles3d(double XX,double YY,double ZZ, double CL)
{
  //bird's eye view, cartesian to polar
  double r = sqrt((XX*XX)+(YY*YY));
    //Serial.print(r);  //1
    //Serial.print("   ");
  double c1 = XX/r;
  if(c1 > 1) c1 = 1;  //lame safety precautions
  if(c1 < -1) c1 = -1;
    //Serial.print(c1);  //2         111111
    //Serial.print("   ");
  double th0 = acos(c1);
    //Serial.print(toDeg(th0));  //3        222222
    //Serial.print("    ");
  //r-=wrist;                   //UNDO THIS COMMENT TO ACCOUNT FOR THE WRIST
  double R = sqrt((r*r)+(ZZ*ZZ));   //in the plane created by the arm
    //Serial.print(R);  //4
    //Serial.print("     ");
  double Rsq = r*r + ZZ*ZZ;
  double c2 = r/R;
  if(c2 > 1) c2 = 1;
  if(c2 < -1) c2 = -1;
    //Serial.print(c2);  //5         333333
    //Serial.print("   ");
  double th1 = acos(c2);
  if(ZZ<0) th1*=-1;
    //Serial.print(toDeg(th1));  //6        444444    
    //Serial.print("   ");
  double den1 = 2*bicep*R;    //inner arm angles
    //Serial.print(den1);  //7       555555
    //Serial.print("   ");
  double e = (bicep*bicep + Rsq - forearm*forearm);
    //Serial.print(e);     //8       666666
    //Serial.print("   ");
  double B = acos(e/den1);
    //Serial.print(toDeg(B));    //9        777777
    //Serial.print("   ");
  double F = (bicep*bicep + forearm*forearm - Rsq);
    //Serial.print(F);      //11     888888
    //Serial.print("   ");
  double den2 = 2*bicep*forearm;
    //Serial.print(den2);    //10    999999
    //Serial.print("   ");
  double C = acos(F/den2);
    //Serial.print(toDeg(C));      //12     000000
    //Serial.print("   ");
  cl = CL;
  a0 = th0;
  a1 = th1 + B;
  ra1 = PI - a1;
  a2 = C + a1 - PI/2;
}
double toDeg(double a)
{
  return a*180/PI;
}
double toPWM(double A)
{
  return A/PI*1750 +500;
}
void solvexyz(double A0, double A1, double A2)
{
  A0 = pr4*PI/1023; // base        in radians
  A1 = pr5*PI/1023; // shoulder
  A2 = pr6*PI/1023; // elbow
  
  double x1 = forearm*cos(A1); //the components
  double x2 = bicep*cos(A2);
  double y1 = forearm*sin(A1);
  double y2 = bicep*cos(A2);
  
  double xf = x1+x2+wrist;  //still in 2d
  double yf = y1+y2;
  
  y = xf*cos(a0);    //3d
  x = xf*sin(a0);
  z = yf;
}
void writepots()
{
  sv4.writeMicroseconds(ps4);
  sv5.writeMicroseconds(ps5);
  sv6.writeMicroseconds(ps6);
  sv7.writeMicroseconds(ps7);
}
void gotoPWM(double A0, double A1, double A2, double A3)
{
  double AA0 = toPWM(A0) +137;
  double AA1 = toPWM(A1) -227;
  double AA2 = toPWM(A2) +445;
  double AA3 = toPWM(A3);
  if(toDeg(A0)<180&&toDeg(A0)>0 && toDeg(A1)<180&&toDeg(A1)>0 && toDeg(A2)<180&&toDeg(A2)>0)
  {
  sv4.writeMicroseconds(AA0);
  sv5.writeMicroseconds(AA1);
  sv6.writeMicroseconds(AA2);
  if(AA3>600);
    sv7.writeMicroseconds(AA3);
  }
  else
    Serial.print("**OoR**OoR**");
}
void gotoangles(double A0,double A1,double A2, double A3)
{
  double AA0 = toDeg(A0) + 5;
  double AA1 = toDeg(A1) - 31;
  double AA2 = toDeg(A2) + 35;
  double AA3 = toDeg(A3);
  if(AA0<150&&AA0>30 && AA1<150&&AA1>30 && AA2<150&&AA2>30)
  {
  sv4.write(AA0);
  sv5.write(AA1);
  sv6.write(AA2);
  if(AA3 > 0)
    sv7.write(AA3);
  }
  else
    Serial.print("OOROOROOR");
}
void plotpots()
{
  Serial.print(2400);
  Serial.print(" ");
  Serial.print(0);
  Serial.print(" ");
  Serial.print(ps4);
  Serial.print(" ");
  Serial.print(ps5);
  Serial.print(" ");
  Serial.print(ps6);
  Serial.print(" ");
  Serial.println(ps7);
}
void printpots()
{
  Serial.print("Base: ");
  Serial.print(ps4);
  Serial.print("      Shoulder:");
  Serial.print(ps5);
  Serial.print("      Elbow:");
  Serial.print(ps6);
  Serial.print("      Claw:");
  Serial.println(ps7);
}
void plotmath()
{
  Serial.print(180);
  Serial.print(" ");
  Serial.print(0);
  Serial.print(" ");
  Serial.print(toDeg(a0));
  Serial.print(" ");
  Serial.print(toDeg(a1));
  Serial.print(" ");
  Serial.println(toDeg(a2));
}
void printmath()
{
  Serial.print("   D0:");
  Serial.print(toPWM(a0)+137);
  Serial.print("  D1:");
  Serial.print(toPWM(a1)-237);
  Serial.print("  rD1:");
  Serial.print(toPWM(ra1)-237);
  Serial.print("  D2:");
  Serial.print(toPWM(a2)+445);
  
  Serial.print("     a0:");
  Serial.print(toDeg(a0));
  Serial.print("  a1:");
  Serial.print(toDeg(a1));
  Serial.print("  a2:");
  Serial.print(toDeg(a2));
  
  Serial.print("      (");
  Serial.print(x,0);
  Serial.print(", ");
  Serial.print(y,0);
  Serial.print(", ");
  Serial.print(z,0);
  Serial.print(")");
  Serial.print("  cl:");
  Serial.println(cl);
}
