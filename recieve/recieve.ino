#include <VirtualWire.h> 
#include <Wire.h>
byte serval[2]={0,0};
int serVal[2]={0,0};
//Servo ser0, ser1;
int Work=0;

//14511

void setup()
{
  Wire.begin();
  Serial.begin(115200);
  vw_setup(2000);
  vw_set_rx_pin(8);
  vw_rx_start();
  //ser0.attach(10);
  //ser1.attach(11);
  //Wire.onRequest(requestEvent); // register event int
  //Wire.onReceive(receiveEvent); // register event int
}
void loop()
{
  grab();   //byte
  //resend(); //byte

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
    serval[0] = buf[0];
    serval[1] = buf[1];
    
  }
  //Serial.write(buf);
  //Serial.write(serval1);
}

/*void resend() //byte   for resending to another arduino
{
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write(serval, 2);           
  Wire.endTransmission();    // stop transmitting
}
void requestEvent() //int
{
  uint8_t Buffer[3];
  Buffer[0]=22;//serval[0];
  Buffer[1]=31;//serval[1];
  Wire.write(Buffer,2);
}

void receiveEvent(int howMany)
{
  Work = Wire.read();
}*/
