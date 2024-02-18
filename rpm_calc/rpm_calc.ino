const int SensorPin = 4;
/* NodeMCU PWM-Pins
  D1  5
  D2  4
  D3  0
  D4  2
  D5  14
  D6  12
  D7  13
  D8  15
*/

int InterruptCounter, rpm;

void ICACHE_RAM_ATTR countup();

void setup(){
  delay(1000);
  Serial.begin(9600);
  Serial.print("Counting");

  pinMode(SensorPin, INPUT);
}

void loop() {
  meassure();
}

void meassure() {
  InterruptCounter = 0;
  attachInterrupt(digitalPinToInterrupt(SensorPin), countup, RISING);
  delay(1000);
  detachInterrupt(digitalPinToInterrupt(SensorPin));
  rpm = (InterruptCounter / 2) * 60;
  display_rpm();
}

void ICACHE_RAM_ATTR countup() {
  InterruptCounter++;
}

void display_rpm() {
  Serial.print("Counts: ");
  Serial.print(InterruptCounter, 1);
  Serial.print(" RPM: ");
  Serial.println(rpm);
}