#if (ARDUINO >= 100)
//#include <Arduino.h> //ggg
#else
//#include <WProgram.h>
//#define Wire.write(x) Wire.send(x)
//#define Wire.read() Wire.receive()
#endif
////////////////////////////////////////////////////////////////
#include <Servo.h>
#include <math.h>
#include <LiquidCrystal.h>
#include <Wire.h>

LiquidCrystal lcd(7,6,5,4,3,2);
Servo sv0,sv1,sv2,sv3;   // nonclear arm
Servo sv4,sv5,sv6,sv7;   //clear arm

const int redp=8,greenp=9,bluep=10;
int loop_cnt=0;
byte accx,accy,zbut,cbut,joyx,joyy;
int CBUT0=0;
double CCX=0, CCY=81, CCZ=81;
double CCX_, CCY_, CCZ_;
double XX=0, YY=81, ZZ=81;

int ledPin = 13;
String readstring="";
char c;
String rx, ry, rz, rc;
const int p4=12,p5=13,p6=14,p7=15;
const int PP = A0;
const int bp0 = 12;
//int i=0; might have to put back in but doubtfully
double pr4,pr5,pr6,pr7;
double ps4,ps5,ps6,ps7;
double a0=PI/2,a1=0,ra1=PI/2,a2=PI/2,fa2=0;
double bicep=81, forearm=81, wrist=68;  //81 81 68
double XXX,YYY,ZZZ;
double x=0,y=81,z=81,cl=.5;
double _x=0,_y=81,_z=81;
double N_x=0,N_y=81,N_z=81;
double C_x=0,C_y=81,C_z=81;
double NX=0,NY=81,NZ=81;
double NNX=0,NNY=81,NNZ=81,NCX=0,NCY=81,NCZ=81;
int bs0, bs1, bcount;
unsigned long time0=0, time1=0,time2=0,time3=0,time4=0,time5=0,time6=0,time7=0,time8=0;

// CALIBRATED FOR ALL CLEAR ARM ONLY***********
void setup() 
{
  Serial.begin(115200);
  pinMode(p4, INPUT);
  pinMode(p5, INPUT);
  pinMode(p6, INPUT);
  pinMode(p7, INPUT);
  pinMode(bp0, INPUT);
  pinMode(PP,INPUT);
  pinMode(redp,OUTPUT);
  pinMode(greenp,OUTPUT);
  pinMode(bluep,OUTPUT);
  sv0.attach(22);
  sv1.attach(24);
  sv2.attach(26);
  sv3.attach(28);
  sv4.attach(30);
  sv5.attach(32);
  sv6.attach(34);
  sv7.attach(36);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("booting up");
  nunchuck_setpowerpins();
  nunchuck_init(); // send the initilization
}
void loop() 
{
  //time8=millis();
  checkMode();

  //doNada();
  //serialToServo();
  //flatDrift();
  //nonFlatDrift();
  //whip();
        //printmath();
        //plotmath();
  //doallpot();
  //doallchuck();              //includes lcd,
        //dothelcdtohere();    //must be included for all "tohere" or Drift functions
        //delay(200);
}
void checkMode()
{
  int mode = map(analogRead(PP),0,1023,7,-1);
  Serial.print(mode);
  Serial.print(" ");
  if(mode == 0)
  {
    setColor(255,0,0); //RED
    doNada();
  }
  else if(mode == 1)
  {
    setColor(255,15,0); //orange
    lazarus();
    //serialToServo();
  }
  else if(mode == 2)
  {
    setColor(255,80,0); //yellow
    lazarus();
    doallpot();
  }
  else if(mode ==3)
  {
    setColor(0,255,0); //GREEN
    flatDrift();
  }
  else if(mode == 4)
  {
    setColor(0,0,255); //blue
    nonFlatDrift();
  } 
  else if(mode == 5)
  {
    setColor(140,0,255); //purple
    whip();         //lcd prolly doesnt work for this mode
  }
  else if(mode == 6)
  {
    setColor(255,0,140); //WHITE
    x=0;y=81;z=81;
    doallchuck();
  }
  else if(mode ==7)
  {
    intro1();
    //intro2();
  }  
  //Serial.print(mode);
  //Serial.print(" ");
}
void intro2()
{
  lcd.setCursor(0,0);
  lcd.print("Good Evening"); 
  setColor(255,255,255);
  lazarus();
  driftToHere2d(0,81,81);
  //driftToHere2dNClear(0,81,81);
  delay(500);
  driftToHere2dClear(0,50,0);
  //driftToHere2dNClear(0,50,90);
  delay(500);
  driftToHere2dClear(40,50,50);
  delay(500);
  driftToHere2dClear(-40,50,50);
  checkMode();
}
void intro1()
{
  lcd.setCursor(0,0);
  lcd.print("Good Evening"); 
  setColor(255,255,255);
  lazarus();
  bcount++;
  //killNonClear();
  driftToHere2d(0,110,110);
  //driftToHere2d(0,70,70);
  //driftToHere2d(-75,130,-10);
  driftToHere2d(-77,132,-30);
  delay(300);
  bcount++;
  delay(700);
  driftToHere2d(0,81,81);
  //driftToHere2d(0,70,70);
  //checkMode();
  //driftToHere2d(0,70,70);
  //driftToHere2d(60,85,-10);
  driftToHere2d(60,85,-30);
  delay(300);
  //bcount++;
  delay(700);
  //lazarus();
  checkMode();
}
void setColor(int red, int green, int blue)
{
  analogWrite(redp, red);
  analogWrite(bluep, blue);
  analogWrite(greenp, green);
}
void mainColors()
{
  setColor(200,0,0); //RED
  delay(1000);
  setColor(0,200,0); //GREEN
  delay(1000);
  setColor(0,0,200); //BLUE
  delay(1000);
  setColor(200,200,0); //YEL0
  delay(1000);
  setColor(0,200,200); //CYAN
  delay(1000);
  setColor(200,0,200); //PURLE
  delay(1000);
  setColor(200,200,200); //WHITE
  delay(1000);
}
void lazarus()
{
  sv0.attach(22);
  sv1.attach(24);
  sv2.attach(26);
  sv3.attach(28);
  sv4.attach(30);
  sv5.attach(32);
  sv6.attach(34);
  sv7.attach(36);
}
void killNonClear()
{
  sv0.detach();
  sv1.detach();
  sv2.detach();
  sv3.detach();
}
void killClear()
{
  sv4.detach();
  sv5.detach();
  sv6.detach();
  sv7.detach();
}
void doNada()
{
  killNonClear();
  killClear();
  lcd.setCursor(0,0);
  lcd.print("Standby baby ;)"); 
}
void dothelcdtohere()
{
  time1=millis();
  if(time1-time0>500)
  {
    printlcdtohere();
    time0=time1;
  }
}
void dothelcdchuck()
{
  time5=millis();
  if(time5-time4>500)
  {
    printlcdchuck();
    time4=time5;
  }
}
void dothelcdpot()
{
  time7=millis();
  if(time7-time6>500)
  {
    printlcdpot();
    time6=time7;
  }
}
void doallchuck()
{
  //killNonClear();
  double stepper = .02;
  time3=millis();
  if(time3-time2>100)
  {
    time2=time3;
    chuckit();
    printchuck();
  }
  
  while(cbut==1)
  { 
      time3=millis();
      if(time3-time2>20)
      {
        time2=time3;
        chuckit();
        //printchuck();
      }
      CCX_ = CCX;
      CCY_ = CCY;
      CCZ_ = CCZ;
      if(abs(joyx-125)>25)
      {
        //if(CCX<136)
        CCX += stepper*(joyx-124)/(3/2);
        Serial.print("    CCX: ");Serial.print(CCX);Serial.println("    ");
      }
      if(abs(accx-125)>20)
      {
        //if(CCX<136)
        CCX += stepper*(accx-125)*2;
        Serial.print("    CCZ: ");Serial.print(CCZ);Serial.println("    ");
      }
      //Serial.print("  ACCY  ");Serial.print(abs(accy-125));Serial.print("  ACCY  ");
      if(abs(joyy-125)>25)
      {
        //if(CCY<150 && sqrt((CCZ*CCZ)+(CCY*CCY))<161)
          CCY += stepper*(joyy-125);
        Serial.print("    CCY: ");Serial.print(CCY);Serial.print("    ");
      }
      if(abs(accy-125)>20)
      {
        //if(CCZ<140 && sqrt((CCZ*CCZ)+(CCY*CCY))<161)
          CCZ -= stepper*(accy-125)*2;
        Serial.print("    CCZ: ");Serial.print(CCZ);Serial.print("    ");
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
      /*else
      {
        _x=CCX;
        _y=CCY;
        _z=CCZ;
        CCX=0;
        CCY=81;
        CCZ=81;
        //bcount=2;    //might be able to take this out so we dont constantly open our shit
        driftToHere2d(CCX,CCY,CCZ);
      }*/
      delay(20);
      dothelcdchuck();
  }
  if(CCZ<140 && CCY<150 && sqrt((CCZ*CCZ)+(CCY*CCY))<162)
  {
    _x=CCX;
    _y=CCY;
    _z=CCZ;
  }
  else
  {
    _x=0;
    _y=81;
    _z=81;
    CCX=0;
    CCY=81;
    CCZ=81;
    whipToHere2d(CCX,CCY,CCZ);
  }
  CCX=0;
  CCY=81;
  CCZ=81;
  //bcount=2;    //might be able to take this out so we dont constantly open our shit
  driftToHere2d(CCX,CCY,CCZ);
}
void chuckit()
{
  nunchuck_get_data();

  accx  = nunchuck_accelx(); // ranges from approx 70 - 182
  accy  = nunchuck_accely(); // ranges from approx 65 - 173
  zbut = nunchuck_zbutton();
  cbut = nunchuck_cbutton(); 
  joyx = nunchuck_joyx();
  joyy = nunchuck_joyy();     
}
void whip()
{
  getxyz();
  whipToHere2d(x,y,z);
}
void flatDrift()
{
  getxyz();
  driftToHere2d(x,y,z);
}
void nonFlatDrift()
{
  getxyz();
  driftToHere3d(x,y,z);
}
void checkbutton()
{
  bs1 = digitalRead(bp0);
  if (bs0 != bs1)
  {
    if(bs1 == 0)
    {
      bcount++;
    }
    delay(170);
  }
  //Serial.print(bcount);
  //Serial.print("    ");
  bs0=bs1;
}
void serialToServo()
{
  killNonClear();
  //x=90;
  //y=90;
  //z=90;
  getxyz();
  sv4.write(x);
  sv5.write(y);
  sv6.write(z);
  sv7.write(x); 
  dothelcdtohere();
}
void doallpot()
{
  checkbutton();
  readandmappot();
  writepots();
  printpots();
  dothelcdpot();

  //plotpots();
}
void driftToHere2d(double XX,double YY,double ZZ)
{
  double distanceToTravel = sqrt((_x-XX)*(_x-XX) + (_y-YY)*(_y-YY) + (_z-ZZ)*(_z-ZZ));
  double stepMe =1;
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
  whipToHere2d(XX, YY, ZZ);
  _x=XX;
  _y=YY;
  _z=ZZ;
  //delayMicroseconds(100);
  dothelcdtohere();
}
void driftToHere2dClear(double XX,double YY,double ZZ)
{
  double distanceToTravel = sqrt((C_x-XX)*(C_x-XX) + (C_y-YY)*(C_y-YY) + (C_z-ZZ)*(C_z-ZZ));
  double stepMe =1;
  for(double j = 0; j < distanceToTravel; j+= stepMe)
  { 
     NCX = C_x + (XX-C_x) * j/distanceToTravel;
     NCY = C_y + (YY-C_y) * j/distanceToTravel;
     NCZ = C_z + (ZZ-C_z) * j/distanceToTravel;
     whipToHere2dClear(NCX, NCY, NCZ);
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
  //whipToHere2dClear(XX, YY, ZZ);
  C_x=XX;
  C_y=YY;
  C_z=ZZ;
  //delayMicroseconds(100);
  dothelcdtohere();
}
void driftToHere2dNClear(double XX,double YY,double ZZ)
{
  double distanceToTravel = sqrt((N_x-XX)*(N_x-XX) + (N_y-YY)*(N_y-YY) + (N_z-ZZ)*(N_z-ZZ));
  double stepMe =1;
  for(double j = 0; j < distanceToTravel; j+= stepMe)
  { 
     NNX = N_x + (XX-N_x) * j/distanceToTravel;
     NNY = N_y + (YY-N_y) * j/distanceToTravel;
     NNZ = N_z + (ZZ-N_z) * j/distanceToTravel;
     whipToHere2dNClear(NNX, NNY, NNZ);
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
  //whipToHere2dNClear(XX, YY, ZZ);
  N_x=XX;
  N_y=YY;
  N_z=ZZ;
  //delayMicroseconds(100);
  dothelcdtohere();
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
  //delayMicroseconds(100);
  dothelcdtohere();
}
void whipToHere2dClear(double XX,double YY,double ZZ)
{
  checkbutton();
  solveangles2d(XX,YY,ZZ);
  //gotoangles(a0,ra1,a2);
  gotoPWMClear(a0,ra1,a2, cl);
  //dothelcdtohere();
  printmath();  
}
void whipToHere2dNClear(double XX,double YY,double ZZ)
{
  checkbutton();
  solveangles2d(XX,YY,ZZ);
  //gotoangles(a0,ra1,a2);
  gotoPWMNClear(a0,ra1,a2, cl);
  //dothelcdtohere();
  printmath();  
}
void whipToHere2d(double XX,double YY,double ZZ)
{
  checkbutton();
  solveangles2d(XX,YY,ZZ);
  //gotoangles(a0,ra1,a2);
  gotoPWMClear(a0,ra1,a2, cl);
  gotoPWMNClear(a0,ra1,a2, cl);
  //dothelcdtohere();
  printmath();
}
void whipToHere3d(double XX,double YY,double ZZ)
{
  checkbutton();
  solveangles3d(XX,YY,ZZ);
  //gotoangles(a0,ra1,a2);
  gotoPWM(a0,ra1,a2, cl);
  //dothelcdtohere();
  printmath();
}
void getxyz()
{
  int i=0;
  while (Serial.available()) 
  {
    c = Serial.read();  //gets one byte from serial buffer
    readstring+=c;
    delayMicroseconds(2000);  //slow looping to allow buffer to fill maybe should shorten
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
    /*while(readstring!=""&&i<readstring.length())
    {
      rc+=readstring.charAt(i+2);
      i++;
      Serial.println("w4");
    }*/
    if(i==readstring.length()&&i!=0)
    {
      i=0;
      readstring="";
      x=rx.toDouble();
      y=ry.toDouble();
      z=rz.toDouble();
      //cl=rc.toDouble();
    }
    readstring="";
    rx="";
    ry="";
    rz="";
    rc="";
  }
}
void solveangles2d(double XX,double YY,double ZZ)
{
  //double r = sqrt((XX*XX)+(YY*YY));    //bird's eye view, cartesian to polar
  //double c1 = XX/r;
  double c1 = XX/81;
  
  if(c1 > 1) c1 = 1;    //lame safety precautions
  if(c1 < -1) c1 = -1;
  
  double th0 = acos(c1);
  double OOsq = YY*YY + ZZ*ZZ;
  double OO = sqrt(OOsq);
  double QQ1 = atan2(ZZ,YY);
  double QQ2 = acos((OOsq + bicep*bicep - forearm*forearm)/(2*forearm*OO)); 

  a0 = th0;
  a1 = QQ1+QQ2;
  ra1 = PI-a1;
  a2 =  a1 - PI/2 + acos((bicep*bicep + forearm*forearm - OOsq)/(2*bicep*bicep));
  fa2 = a2-a1+PI/2;
  if(bcount%2==1)
    cl=3;         //work this button crap out
  else
    cl=.5;
}
void solveangles3d(double XX,double YY,double ZZ)
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
  a0 = th0;
  a1 = th1 + B;
  ra1 = PI - a1;
  a2 = C + a1 - PI/2;
  fa2 = a2-a1+PI/2;
  if(bcount%2==1)
    cl=3;         //work this button crap out
  else
    cl=.5;
}
double toDeg(double a)  //from radians
{
  return a*180/PI;
}
double toPWM(double A) //from radians
{
  return A/PI*1750 +500;
}
void solvexyz(double AAA0, double AAA1, double AAA2)
{
  AAA0 *= PI/180; // base        in radians
  AAA1 *= PI/180; // shoulder
  AAA2 *= PI/180; // elbow

  AAA0 += -PI/2;
  //AAA1 += 0;
  AAA2 += - PI/2;

  /*Serial.print("   A1: ");
  Serial.print(AAA1);
  Serial.print("   A2: ");
  Serial.print(AAA2);
  Serial.print("    ");*/
  
  double x1 = forearm*cos(AAA1); //the components
  double x2 = bicep*cos(AAA2);
  double y1 = forearm*sin(AAA1);
  double y2 = bicep*sin(AAA2);
  
  double xf = x1+x2;  //still in 2d
  double yf = y1+y2;
  
  XXX = xf*sin(AAA0);
  YYY = xf;//*cos(AAA0);    //3d
  ZZZ = yf;
  
}
void readandmappot()
{
  pr4 = analogRead(p4);
  pr5 = analogRead(p5);
  pr6 = analogRead(p6);
  //pr7 = analogRead(p7);

  ps4 = map(pr4, 0, 1023, 500, 2250);
  ps5 = map(pr5, 0, 1023, 2250, 500); //melt the thing for this joint to go lower
  ps6 = map(pr6, 0, 1023, 500, 2250);
  //ps7 = map(pr7, 0, 1023, 500, 2250);
  if(bcount%2==1)
    cl=3;
  else
    cl=.5;
}
void writepots()
{                              //@ point (0,81,81) cl:middle
  sv0.writeMicroseconds(2825-(ps4));         //-61   1451
  sv1.writeMicroseconds(ps5 -72);        //+155  1326  1126????
  sv2.writeMicroseconds(ps6 +372);         //-73   1747
  sv3.writeMicroseconds(toPWM(cl)+30);  //1906
  sv4.writeMicroseconds(2920-(ps4));
  sv5.writeMicroseconds(ps5 -227);
  sv6.writeMicroseconds(ps6 +445);
  sv7.writeMicroseconds(toPWM(cl));
}
void gotoPWMNClear(double A0,double A1,double A2, double A3)
{
  double AA0 = toPWM(A0) +137;    //+137
  double AA1 = toPWM(A1) -227;    //-227
  double AA2 = toPWM(A2) +445;    //+445
  double AA3 = toPWM(A3);
  //if(toDeg(A0)<180&&toDeg(A0)>0 && toDeg(A1)<180&&toDeg(A1)>0 && toDeg(A2)<180&&toDeg(A2)>0)
  //{
  sv0.writeMicroseconds(AA0-61);
  sv1.writeMicroseconds(AA1+155);
  sv2.writeMicroseconds(AA2-73);
  if(AA3 > 600)
  {
    sv3.writeMicroseconds(AA3+300);
  }
  //}
  //else
    //Serial.print("**OoR**OoR**");
}
void gotoPWMClear(double A0,double A1,double A2, double A3)
{
  double AA0 = toPWM(A0) +137;    //+137
  double AA1 = toPWM(A1) -227;    //-227
  double AA2 = toPWM(A2) +445;    //+445
  double AA3 = toPWM(A3);
  //if(toDeg(A0)<180&&toDeg(A0)>0 && toDeg(A1)<180&&toDeg(A1)>0 && toDeg(A2)<180&&toDeg(A2)>0)
  //{
  sv4.writeMicroseconds(AA0);
  sv5.writeMicroseconds(AA1);
  sv6.writeMicroseconds(AA2);
  if(AA3 > 600)
  {
    sv7.writeMicroseconds(AA3);
  }
  //}
  //else
    //Serial.print("**OoR**OoR**");
}
void gotoPWM(double A0,double A1,double A2, double A3)
{
  double AA0 = toPWM(A0) +137;    //+137
  double AA1 = toPWM(A1) -227;    //-227
  double AA2 = toPWM(A2) +445;    //+445
  double AA3 = toPWM(A3);
  //if(toDeg(A0)<180&&toDeg(A0)>0 && toDeg(A1)<180&&toDeg(A1)>0 && toDeg(A2)<180&&toDeg(A2)>0)
  //{
  sv4.writeMicroseconds(AA0);
  sv0.writeMicroseconds(AA0-61);
  sv5.writeMicroseconds(AA1);
  sv1.writeMicroseconds(AA1+155);
  sv6.writeMicroseconds(AA2);
  sv2.writeMicroseconds(AA2-73);
  if(AA3 > 600)
  {
    sv7.writeMicroseconds(AA3);
    sv3.writeMicroseconds(AA3+300);
  }
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
  sv4.write(AA0);
  sv5.write(AA1);
  sv6.write(AA2);
  if(AA3 > 0)
    sv7.write(AA3);
  //}
  //else
    //Serial.print("OOROOROOR");
}


static uint8_t nunchuck_buf[6];   // array to store nunchuck data,

// Uses port C (analog in) pins as power & ground for Nunchuck
static void nunchuck_setpowerpins()
{
#define pwrpin PORTC3
#define gndpin PORTC2
    DDRC |= _BV(pwrpin) | _BV(gndpin);
    PORTC &=~ _BV(gndpin);
    PORTC |=  _BV(pwrpin);
    delay(100);  // wait for things to stabilize        
}

// initialize the I2C system, join the I2C bus,
// and tell the nunchuck we're talking to it
static void nunchuck_init()
{ 
    Wire.begin();                // join i2c bus as master
    Wire.beginTransmission(0x52);// transmit to device 0x52
#if (ARDUINO >= 100)
    Wire.write((uint8_t)0x40);// sends memory address
    Wire.write((uint8_t)0x00);// sends sent a zero.  
#else
    Wire.send((uint8_t)0x40);// sends memory address
    Wire.send((uint8_t)0x00);// sends sent a zero.  
#endif
    Wire.endTransmission();// stop transmitting
}

// Send a request for data to the nunchuck
// was "send_zero()"
static void nunchuck_send_request()
{
    Wire.beginTransmission(0x52);// transmit to device 0x52
#if (ARDUINO >= 100)
    Wire.write((uint8_t)0x00);// sends one byte
#else
    Wire.send((uint8_t)0x00);// sends one byte
#endif
    Wire.endTransmission();// stop transmitting
}

// Encode data to format that most wiimote drivers except
// only needed if you use one of the regular wiimote drivers
static char nunchuk_decode_byte (char x)
{
    x = (x ^ 0x17) + 0x17;
    return x;
}
static int nunchuck_get_data() // Receive data back from the nunchuck, 
{                              // returns 1 on successful read. returns 0 on failure
    int cnt=0;
    Wire.requestFrom (0x52, 6);// request data from nunchuck
    while (Wire.available ()) 
    {
        // receive byte as an integer
#if (ARDUINO >= 100)
        nunchuck_buf[cnt] = nunchuk_decode_byte( Wire.read() );
#else
        nunchuck_buf[cnt] = nunchuk_decode_byte( Wire.receive() );
#endif
        cnt++;
    }
    nunchuck_send_request();  // send request for next data payload
    // If we recieved the 6 bytes, then go print them
    if (cnt >= 5) {
        return 1;   // success
    }
    return 0; //failure
}

// Print the input data we have recieved
// accel data is 10 bits long
// so we read 8 bits, then we have to add
// on the last 2 bits.  That is why I
// multiply them by 2 * 2
static void nunchuck_print_data()
{ 
    static int i=0;
    int joy_x_axis = nunchuck_buf[0];
    int joy_y_axis = nunchuck_buf[1];
    int accel_x_axis = nunchuck_buf[2]; // * 2 * 2; 
    int accel_y_axis = nunchuck_buf[3]; // * 2 * 2;
    int accel_z_axis = nunchuck_buf[4]; // * 2 * 2;

    int z_button = 0;
    int c_button = 0;

    // byte nunchuck_buf[5] contains bits for z and c buttons
    // it also contains the least significant bits for the accelerometer data
    // so we have to check each bit of byte outbuf[5]
    if ((nunchuck_buf[5] >> 0) & 1) 
        z_button = 1;
    if ((nunchuck_buf[5] >> 1) & 1)
        c_button = 1;

    if ((nunchuck_buf[5] >> 2) & 1) 
        accel_x_axis += 1;
    if ((nunchuck_buf[5] >> 3) & 1)
        accel_x_axis += 2;

    if ((nunchuck_buf[5] >> 4) & 1)
        accel_y_axis += 1;
    if ((nunchuck_buf[5] >> 5) & 1)
        accel_y_axis += 2;

    if ((nunchuck_buf[5] >> 6) & 1)
        accel_z_axis += 1;
    if ((nunchuck_buf[5] >> 7) & 1)
        accel_z_axis += 2;

    Serial.print(i,DEC);
    Serial.print("\t");

    Serial.print("joy:");
    Serial.print(joy_x_axis,DEC);
    Serial.print(",");
    Serial.print(joy_y_axis, DEC);
    Serial.print("  \t");

    Serial.print("acc:");
    Serial.print(accel_x_axis, DEC);
    Serial.print(",");
    Serial.print(accel_y_axis, DEC);
    Serial.print(",");
    Serial.print(accel_z_axis, DEC);
    Serial.print("\t");

    Serial.print("but:");
    Serial.print(z_button, DEC);
    Serial.print(",");
    Serial.print(c_button, DEC);

    Serial.print("\r\n");  // newline
    i++;
}
// returns zbutton state: 1=pressed, 0=notpressed
static int nunchuck_zbutton()
{
    return ((nunchuck_buf[5] >> 0) & 1) ? 0 : 1;  // voodoo
}
// returns zbutton state: 1=pressed, 0=notpressed
static int nunchuck_cbutton()
{
    return ((nunchuck_buf[5] >> 1) & 1) ? 0 : 1;  // voodoo
}
// returns value of x-axis joystick
static int nunchuck_joyx()
{
    return nunchuck_buf[0]; 
}
// returns value of y-axis joystick
static int nunchuck_joyy()
{
    return nunchuck_buf[1];
}
// returns value of x-axis accelerometer
static int nunchuck_accelx()
{
    return nunchuck_buf[2];   // FIXME: this leaves out 2-bits of the data
}
// returns value of y-axis accelerometer
static int nunchuck_accely()
{
    return nunchuck_buf[3];   // FIXME: this leaves out 2-bits of the data
}
// returns value of z-axis accelerometer
static int nunchuck_accelz()
{
    return nunchuck_buf[4];   // FIXME: this leaves out 2-bits of the data
}


//////////////////////////////////////////////////////////////////////////////
//                            PRINTING METHODS                              //
//////////////////////////////////////////////////////////////////////////////
int AAA0,AAA1,AAA2;
void printlcdpot()
{
  lcd.clear();
  lcd.setCursor(0,0);   // Set the cursor to the position
  lcd.print((int)XXX); // Print our value
  lcd.setCursor(4,0);   // Set the cursor to the position
  lcd.print((int)YYY); // Print our value
  lcd.setCursor(10,0);   // Set the cursor to the position
  lcd.print((int)ZZZ); // Print our value
  lcd.setCursor(0,1);   // Set the cursor to the position
  lcd.print(AAA0); // Print our value
  lcd.setCursor(4,1);   // Set the cursor to the position
  lcd.print(AAA1); // Print our value
  lcd.setCursor(8,1);   // Set the cursor to the position
  lcd.print(AAA2-AAA1+90); // Print our value
}
void printlcdtohere()
{
  lcd.clear();
  lcd.setCursor(0,0);   // Set the cursor to the position
  lcd.print((int)x); // Print our value
  lcd.setCursor(4,0);   // Set the cursor to the position
  lcd.print((int)y); // Print our value
  lcd.setCursor(8,0);   // Set the cursor to the position
  lcd.print((int)z); // Print our value
  lcd.setCursor(0,1);   // Set the cursor to the position
  lcd.print((int)(round(toDeg(a0)))); // Print our value
  lcd.setCursor(4,1);   // Set the cursor to the position
  lcd.print((int)(round(toDeg(a1)))); // Print our value
  lcd.setCursor(8,1);   // Set the cursor to the position
  lcd.print((int)(round(toDeg(fa2)))); // Print our value
}
void printlcdchuck()
{
  lcd.clear();
  lcd.setCursor(0,0);   // Set the cursor to the position
  lcd.print((int)CCX); // Print our value
  lcd.setCursor(4,0);   // Set the cursor to the position
  lcd.print((int)CCY); // Print our value
  lcd.setCursor(8,0);   // Set the cursor to the position
  lcd.print((int)CCZ); // Print our value
  lcd.setCursor(0,1);   // Set the cursor to the position
  lcd.print((int)(round(toDeg(a0)))); // Print our value
  lcd.setCursor(4,1);   // Set the cursor to the position
  lcd.print((int)(round(toDeg(a1)))); // Print our value
  lcd.setCursor(8,1);   // Set the cursor to the position
  lcd.print((int)(round(toDeg(fa2)))); // Print our value 
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
  AAA0 = (pr4*180/1023);              //((int)ps4+137)*180/1750
  AAA1 = (pr5*180/1023);       //-1*((int)ps5-227)*180/1750 +90
  AAA2 = (pr6*180/1023);          //((int)ps6+445)*180/1750 +90
  solvexyz((AAA0),(AAA1),(AAA2));
  Serial.print("  X: ");
  Serial.print(XXX);
  Serial.print("  Y: ");
  Serial.print(YYY);
  Serial.print("  Z: ");
  Serial.print(ZZZ);
  Serial.print("           a0: ");
  Serial.print(AAA0);
  Serial.print("  a1: ");
  Serial.print(AAA1);
  Serial.print("  a2: ");
  Serial.print(AAA2);
  Serial.print("           ");
  Serial.print(AAA2-AAA1+90);
  Serial.print("           ");

  Serial.print("           pr1: ");
  Serial.print(pr4);
  Serial.print("  pr2: ");
  Serial.print(pr5);
  Serial.print("  pr3: ");
  Serial.print(pr6);
  Serial.print("           ");
  
  /*Serial.print("Base: ");
  Serial.print(ps4);
  Serial.print("      Shoulder:");
  Serial.print(ps5);
  Serial.print("      Elbow:");
  Serial.print(ps6);
  Serial.print("      Claw:");
  Serial.print(bcount);
  Serial.print("      ");*/
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
  Serial.println(toDeg(fa2));
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
  Serial.print("  ra1:");
  Serial.print(toDeg(ra1));
  Serial.print("  a2:");
  Serial.print(toDeg(a2));
  Serial.print("  fa2:");
  Serial.print(toDeg(fa2));
  
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
  Serial.print(toDeg(fa2));
  
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
