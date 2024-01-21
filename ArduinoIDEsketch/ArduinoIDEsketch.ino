void ICACHE_RAM_ATTR ISR();

void setup() {
  // put your setup code here, to run once:
  pinMode(5, INPUT); //D1
  pinMode(2, OUTPUT); //D4
  attachInterrupt(digitalPinToInterrupt(5), ISR, CHANGE);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
    delay(1000);
    Serial.println("loop");
}

void ICACHE_RAM_ATTR ISR() {
 digitalWrite(2, !digitalRead(2));
  Serial.println("ISR");
}