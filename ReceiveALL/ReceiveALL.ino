#include <VirtualWire.h> 
#include <Wire.h>
#include <ServoTimer2.h>

ServoTimer2 sv0,sv1,sv2,sv3;
ServoTimer2 sv4,sv5,sv6,sv7;

byte accx,accy,zbut,cbut,joyx,joyy;
int CBUT0=0;
double CCX=0, CCY=81, CCZ=81;
double CCX_, CCY_, CCZ_;
int ledPin = 13;
static uint8_t nunchuck_buf[6];   // array to store nunchuck data,
String readstring="";
char c;
String rx, ry, rz, rc;
const int p4=12,p5=13,p6=14,p7=15;
const int bp0 = 12;
//int i=0; might have to put back in but doubtfully
double pr4,pr5,pr6,pr7;
double ps4,ps5,ps6,ps7;
double a0,a1,ra1,a2;
double bicep=81, forearm=81, wrist=68;  //81 81 68
double XXX,YYY,ZZZ;
double x=0,y=81,z=81,cl=1;
double _x=0,_y=81,_z=81;
double NX=0,NY=81,NZ=81;
int bs0, bs1, bcount;
unsigned long time0=0, time1=0,time2=0,time3=0,time4=0,time5=0,time6=0,time7=0;


void setup() {
  sv0.attach(22);
  sv1.attach(24);
  sv2.attach(26);
  sv3.attach(28);
  sv4.attach(30);
  sv5.attach(32);
  sv6.attach(34);
  sv7.attach(36);
  Wire.begin();
  Serial.begin(115200);
  vw_setup(2000);
  vw_set_rx_pin(8);
  vw_rx_start();
}

void loop() {
  grab();
  //doallchuch();
  //

}

void grab() //byte
{
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  uint8_t buf[buflen];
  //Serial.println("m");
  if(vw_get_message(buf, &buflen))
  {
    Serial.print(buf[0]);
    Serial.print("  |  ");
    Serial.print(buf[1]);
    Serial.print("  |  ");
    Serial.println(buf[2]);    
  }
}
void doallchuck()
{
  double stepper = .02;
  time3=millis();
  if(time3-time2>100)
  {
    time2=time3;
    //chuckit();
    grab();
    printchuck();
  }
  
  while(cbut==1)
  { 
      time3=millis();
      if(time3-time2>20)
      {
        time2=time3;
        //chuckit();
        grab();
        //printchuck();
      }
      CCX_ = CCX;
      CCY_ = CCY;
      CCZ_ = CCZ;
      if(abs(joyx-125)>25)
      {
        CCX += stepper*(joyx-124)/(3/2);
        Serial.print("    CCX: ");Serial.print(CCX);Serial.println("    ");
      }
      if(abs(accx-125)>20)
      {
        //if(CCZ<136)
        CCX += stepper*(accx-125)*2;
        Serial.print("    CCZ: ");Serial.print(CCZ);Serial.println("    ");
      }
      //Serial.print("  ACCY  ");Serial.print(abs(accy-125));Serial.print("  ACCY  ");
      if(abs(joyy-125)>25)
      {
        CCY += stepper*(joyy-125);
        Serial.print("    CCY: ");Serial.print(CCY);Serial.println("    ");
      }
      if(abs(accy-125)>20)
      {
        //if(CCZ<136)
        CCZ -= stepper*(accy-125)*2;
        Serial.print("    CCZ: ");Serial.print(CCZ);Serial.println("    ");
      }
      if (CBUT0 != zbut)
      {
        //Serial.print("    cbut ");Serial.print(zbut);Serial.print("    ");
        //Serial.print("    cbut0 ");Serial.print(CBUT0);Serial.print("    ");
        //Serial.print("    bcount ");Serial.print(bcount);Serial.print("  AFSDGFHJ  ");
        if(zbut == 0)
        {
          bcount++;
        }
            CBUT0=zbut;
        //Serial.print("    cbut ");Serial.print(zbut);Serial.print("    ");
        //Serial.print("    cbut0 ");Serial.print(CBUT0);Serial.print("    ");
        //Serial.print("    bcount ");Serial.print(bcount);Serial.println("    ");
      }
      //Serial.print("     DRIFTING      ");
      if(sqrt((CCZ*CCZ)+(CCY*CCY))<162)
      {
        Serial.print("   "); Serial.print(sqrt((CCZ*CCZ)+(CCY*CCY))); Serial.println("   "); 
        whipToHere2d(CCX,CCY,CCZ);
      }
      delay(20);
      //dothelcdchuck();
  }
  _x=CCX;
  _y=CCY;
  _z=CCZ;
  CCX=0;
  CCY=81;
  CCZ=81;
  //bcount=2;    //might be able to take this out so we dont constantly open our shit
  driftToHere2d(CCX,CCY,CCZ);
}
void flatDrift()
{
  //getxyz();
  driftToHere2d(x,y,z);
}
void nonFlatDrift()
{
  //getxyz();
  driftToHere3d(x,y,z);
}
void serialToServo()
{
  //getxyz();
  sv4.write(x); //put it in microseconds PWM
  sv5.write(y);
  sv6.write(z);
  sv7.write(x); 
}

void driftToHere2d(double XX,double YY,double ZZ)
{
  double distanceToTravel = sqrt((_x-XX)*(_x-XX) + (_y-YY)*(_y-YY) + (_z-ZZ)*(_z-ZZ));
  double stepMe =.5;
  for(double j = 0; j < distanceToTravel; j+= stepMe)
  { 
     NX = _x + (XX-_x) * j/distanceToTravel;
     NY = _y + (YY-_y) * j/distanceToTravel;
     NZ = _z + (ZZ-_z) * j/distanceToTravel;
     whipToHere2d(NX, NY, NZ);
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
     Serial.println(toPWM(a2)+445);
     delayMicroseconds(100);
  }
  whipToHere2d(x, y, z);
  _x=x;
  _y=y;
  _z=z;
  delayMicroseconds(100);
}
void driftToHere3d(double XX,double YY,double ZZ)
{
  double distanceToTravel = sqrt((_x-XX)*(_x-XX) + (_y-YY)*(_y-YY) + (_z-ZZ)*(_z-ZZ));
  double stepMe =.5;
  for(double j = 0; j < distanceToTravel; j+= stepMe)
  { 
     NX = _x + (XX-_x) * j/distanceToTravel;
     NY = _y + (YY-_y) * j/distanceToTravel;
     NZ = _z + (ZZ-_z) * j/distanceToTravel;
     whipToHere3d(NX, NY, NZ);
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
     Serial.println(toPWM(a2)+445);
     delayMicroseconds(100);
  }
  whipToHere3d(x, y, z);
  _x=x;
  _y=y;
  _z=z;
  delayMicroseconds(100);
}
void whipToHere2d(double XX,double YY,double ZZ)
{
  //checkbutton();
  //solveangles2d(XX,YY,ZZ);
  //gotoangles(a0,ra1,a2);
  gotoPWM(a0,ra1,a2, cl);
}
void whipToHere3d(double XX,double YY,double ZZ)
{
  //checkbutton();
  //solveangles3d(XX,YY,ZZ);
  //gotoangles(a0,ra1,a2);
  gotoPWM(a0,ra1,a2, cl);
}
double toDeg(double a)  //from radians
{
  return a*180/PI;
}
double toPWM(double A) //from radians
{
  return A/PI*1750 +500;
}
void writepots()
{                              //@ point (0,81,81) cl:middle
  sv0.write(ps4 +76);         //-61   1451
  sv1.write(ps5 -72);        //+155  1326  1126????
  sv2.write(ps6 +372);         //-73   1747
  sv3.write(toPWM(cl)+300);  //1906
  sv4.write(ps4 +137);
  sv5.write(ps5 -227);
  sv6.write(ps6 +445);
  sv7.write(toPWM(cl));
}
void gotoPWM(double A0,double A1,double A2, double A3)
{
  double AA0 = toPWM(A0) +137;    //+137
  double AA1 = toPWM(A1) -227;    //-227
  double AA2 = toPWM(A2) +445;    //+445
  double AA3 = toPWM(A3);
  //if(toDeg(A0)<180&&toDeg(A0)>0 && toDeg(A1)<180&&toDeg(A1)>0 && toDeg(A2)<180&&toDeg(A2)>0)
  //{
  sv4.write(AA0);
  sv5.write(AA1);
  sv6.write(AA2);
  if(AA3 > 600)
    sv7.write(AA3);
  //}
  //else
    //Serial.print("**OoR**OoR**");
}
void gotoangles(double A0,double A1,double A2, double A3)
{
  double AA0 = toDeg(A0) + 5;
  double AA1 = toDeg(A1) - 31;
  double AA2 = toDeg(A2) + 35;
  double AA3 = toDeg(A3);
  //if(AA0<150&&AA0>30 && AA1<150&&AA1>30 && AA2<150&&AA2>30)
  //{
  sv4.write(AA0); //these must be converted to microseconds
  sv5.write(AA1);
  sv6.write(AA2);
  if(AA3 > 0)
    sv7.write(AA3);
  //}
  //else
    //Serial.print("OOROOROOR");
}

//////////////////////////////////////////////////////////////////////////////
//                            PRINTING METHODS                              //
//////////////////////////////////////////////////////////////////////////////

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
  Serial.print("      Claw:");
  Serial.print("Base: ");
  Serial.print(ps4);
  Serial.print("      Shoulder:");
  Serial.print(ps5);
  Serial.print("      Elbow:");
  Serial.print(ps6);
  Serial.print("      Claw:");
  Serial.print(bcount);
  Serial.print("      ");
  Serial.println(cl);
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
void printchuck()
{
  /*Serial.print("accx: "); Serial.print((byte)accx,DEC);
  Serial.print(" accy: "); Serial.print((byte)accy,DEC);
  Serial.print(" zbut: "); Serial.print((byte)zbut,DEC);
  Serial.print(" cbut: "); Serial.print((byte)cbut,DEC);
  Serial.print(" joyx: "); Serial.print((byte)joyx,DEC);
  Serial.print(" joyy: "); Serial.print((byte)joyy,DEC);*/
  Serial.print("accx: "); Serial.print(accx);
  Serial.print(" accy: "); Serial.print(accy);
  Serial.print(" zbut: "); Serial.print(zbut);
  Serial.print(" cbut: "); Serial.print(cbut);
  Serial.print(" joyx: "); Serial.print(joyx);
  Serial.print(" joyy: "); Serial.print(joyy);

  Serial.print("     a0:");
  Serial.print(toDeg(a0));
  Serial.print("  a1:");
  Serial.print(toDeg(a1));
  Serial.print("  a2:");
  Serial.print(toDeg(a2));
  
  Serial.print("      (");
  Serial.print(CCX,0);
  Serial.print(", ");
  Serial.print(CCY,0);
  Serial.print(", ");
  Serial.print(CCZ,0);
  Serial.print(")");
  Serial.print("  cl:");
  Serial.println(cl);
}
void printInfo()
{
  for(int j =0; j<5;j++);
}

