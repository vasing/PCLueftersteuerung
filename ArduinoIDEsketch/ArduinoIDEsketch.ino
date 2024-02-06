#define outPIN 2
#define InterruptPIN 5
#define pwmPIN 15

int incomingByte = 0; // serial incomming data
int dutyCycle = 100; // PWM dutyCycle initial

void ICACHE_RAM_ATTR ISR();

void setup() {
  // put your setup code here, to run once:
  pinMode(InterruptPIN, INPUT); //D1
  pinMode(outPIN, OUTPUT); //D4
  pinMode(pwmPIN, OUTPUT); //D8 PWM
  attachInterrupt(digitalPinToInterrupt(InterruptPIN), ISR, CHANGE);
  Serial.begin(115200);

  analogWriteFreq(25000); // set PWM frequency to 20kHz
  analogWrite(pwmPIN, 128);
}

void loop() {
  // put your main code here, to run repeatedly:
    // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();

    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);
    dutyCycle = dutyCycle;
    delay(1000);
  }
  
  
  analogWrite(0, dutyCycle);
  Serial.println(incomingByte, DEC);
}

void ICACHE_RAM_ATTR ISR() {
 digitalWrite(2, !digitalRead(2));
  Serial.println("ISR");
}