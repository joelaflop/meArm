
const int p0=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(p0,INPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  int pr0=analogRead(p0);
  Serial.println(pr0);
}
