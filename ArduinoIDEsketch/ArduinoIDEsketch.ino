/*PINS*/
const int tacho_PIN = 5
const int DHT1_PIN = 12
const int DHT2_PIN = 13
const int luefter_PIN = 4
const int heizung_PIN = 0
//const int pwmPIN = 15 
const int safety_PIN = 15
const int safety_temp_PIN = 14

/*VARIABLES*/
const int T_Tmin = 23 //tbd
const int T_Tmax = 27 //tbd
const int t_N = 6000  //tbd Luefter Nachlaufzeit [ms]
const int t_soll = 25 //tbd Soll-Temp 
const int t_hy = 2    //tbd Hysterese Abweichung
/* NodeMCU PWM-Pins
  D1  5 Tacho
  D2  4 Luefter
  D3  0 Heizung
  D4  2 
  D5  14 Safety Temp (DS18B20)
  D6  12  DHT1
  D7  13  DHT2
  D8  15  Safety LED
*/


int incomingByte = 0; // serial incomming data
int dutyCycle = 100; // PWM dutyCycle initial

void ICACHE_RAM_ATTR ISR();

void setup() {
/*PINs*/
  pinMode(tacho_PIN, INPUT); 
  attachInterrupt(digitalPinToInterrupt(tacho_PIN), ISR, CHANGE);
  pinMode(DHT1_PIN, INPUT);
  pinMode(DHT2_PIN, INPUT);
  pinMode(luefter_PIN, OUTPUT);
  pinMode(heizung_PIN, OUTPUT);
  pinMode(safety_PIN, OUTPUT); 
  pinMode(safety_temp_PIN, INPUT_PULLUP); 

/*SERIAL UART*/
  Serial.begin(115200);

/*PWM Setup*/
  //analogWriteFreq(25000); // set PWM frequency to 20kHz
  //analogWrite(pwmPIN, 128);
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
      Serial.println(State: warm);
      break;

    case heizen:
      // do stuff
      Serial.println(State: heizen);
      break;

    case nachlauf:
      // do stuff
      Serial.println(State: nachlauf);
      break;

    case safe:
      // do stuff
      Serial.println(State: safe);
      break;

  }
}



}

void ICACHE_RAM_ATTR ISR() {
 digitalWrite(2, !digitalRead(2));
  Serial.println("ISR");
}