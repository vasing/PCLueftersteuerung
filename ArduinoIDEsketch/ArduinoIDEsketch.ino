const int outPIN = 2
const int InterruptPIN = 5
const int pwmPIN = 15 
const int T_Tmin = 23 //tbd
const int T_Tmax = 27 //tbd
const int t_N = 6000  //tbd Luefter Nachlaufzeit [ms]
const int t_soll = 25 //tbd Soll-Temp 
const int t_hy = 2    //tbd Hysterese Abweichung
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
  /*  %   DEC
      0   0
      10  
      20
      30
      40
      50  128
      60
      70
      80
      90
      100 255
  */
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

  switch (state)
  {
    case warm:
      // do stuff
      // maybe change state
      break;

    case heizen:
      // do stuff
      // maybe change state
      break;

    case nachlauf:
      // do stuff
      // maybe change state
      break;

    case save:
      // do stuff
      // maybe change state
      break;

  }
}



}

void ICACHE_RAM_ATTR ISR() {
 digitalWrite(2, !digitalRead(2));
  Serial.println("ISR");
}