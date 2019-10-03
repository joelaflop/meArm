#include <Arduino.h>
#include <Servo.h>

const int potPin0 = 0;
const int potPin1 = 1;
const int potPin2 = 2;
const int flexPin0 = 15;
Servo servo0, servo1, servo2;
int potRead0, potRead1, potRead2;
int potForServo0, potForServo1, potForServo2;
int flexPosition0;
int flexForServo0;

void setup() {
  Serial.begin(9600);
  pinMode(potPin0, INPUT);
  pinMode(potPin1, INPUT);
  pinMode(potPin2, INPUT);
  pinMode(flexPin0, INPUT);
  servo0.attach(2);
  servo1.attach(3);
  servo2.attach(5);

}

void loop()
{
  flexRead();
  potsToServos();
  printitall();

}

/////////////////////////////////////////////////////////////////////////
///////////////////////////////functions/////////////////////////////////
/////////////////////////////////////////////////////////////////////////

  void flexRead()
  {
    flexPosition0 = analogRead(flexPin0);
    flexForServo0 = map(flexPosition0, 350, 530, 0, 180); //-> arbitrary
    flexForServo0 = constrain(flexForServo0, 0, 180);
  }

  void potsToServos()
  {
    potRead0 = analogRead(potPin0);
    potRead1 = analogRead(potPin1);
    potRead2 = analogRead(potPin2);
    potForServo0 = map(potRead0, 0, 1023, 180, 0); //680 for 3.3 v
    potForServo1 = map(potRead1, 0, 1023, 180, 0);
    potForServo2 = map(potRead2, 0, 1023, 180, 0);
    servo0.write(potForServo0);
    servo1.write(potForServo1);
    servo2.write(flexForServo0); //can use pot positions (potForServo#)

  }

  void printitall()
  {

    Serial.print(potForServo0);
    Serial.write("  ||  ");
    Serial.print(potForServo1);
    Serial.write("  ||  ");
    Serial.print(potForServo2);

    Serial.write("        flex: ");
    Serial.print(flexPosition0);
    Serial.write(" flexservo:  ");
    Serial.println(flexForServo0);
  }
