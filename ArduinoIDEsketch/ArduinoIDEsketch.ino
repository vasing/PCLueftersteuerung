void setup() {
  // put your setup code here, to run once:
  pinMode(16, INPUT_PULLDOWN_16); //D0
  pinMode(2, OUTPUT); //D4
  attachInterrupt(digitalPinToInterrupt(16), ISR, RISING);

}

void loop() {
  // put your main code here, to run repeatedly:

}

void ISR() {
 digitalWrite(2, !digitalRead(2));
}