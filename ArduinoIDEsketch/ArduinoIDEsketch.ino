/*PINS-------------------------*/
//INPPUT
int const tacho_PIN = 13;
int const DHT1_PIN = 9;
int const DHT2_PIN = 10;
int const safety_temp_PIN = 12;
int const heizung_Taster_PIN = 14;   //todo Doku
//OUTPUT
int const luefter_PIN = 4;
int const heizung_PIN = 5;
int const led_PIN = 0;
int const relais_PIN = 2
//const int pwmPIN = 15   
int const safety_PIN = 15;
/*-----------------------------*/

/* ESP8266 NodeMCU GPIO Pins
 PIN   GPIO
(D0) = 16 
  D1 = 5  heizung_PIN
  D2 = 4  luefter_PIN
(D3) = 0  led_PIN
(D4) = 2  relais_PIN
  D5 = 14 Safety Temp (DS18B20)
  D6 = 12 safety_temp_PIN
  D7 = 13 tacho_PIN
  D8 = 15 safety_PIN
(RX) = 3
(TX) = 1
 SD3 = 10 DHT2
 SD2 = 9  DHT1
-----------------------------*/

/*VARIABLEN State Machine*/
int T_Tmin = 23; //tbd
int T_Tmax = 27; //tbd
int t_N = 6000;  //tbd Luefter Nachlaufzeit [ms]
int t_soll = 25; //tbd Soll-Temp 
int t_hy = 2;    //tbd Hysterese Abweichung
bool Heizung_Status = LOW;

/*VARIABLEN SERIAL UART*/
int incomingByte = 0; // serial incomming data

/*VARIABLEN PWM*/
//int dutyCycle = 100; // PWM dutyCycle initial

/*FUNCTIONS*/
void ICACHE_RAM_ATTR ISR_Heizung_Taster();
void ICACHE_RAM_ATTR ISR_TACHO();

void setup() {
/*PINs*/
  pinMode(tacho_PIN, INPUT); 
  
  
  attachInterrupt(digitalPinToInterrupt(heizung_Taster_PIN), ISR_Heizung_Taster, FALLING);
  attachInterrupt(digitalPinToInterrupt(tacho_PIN), ISR_TACHO, CHANGE);
  
  
  pinMode(DHT1_PIN, INPUT);
  pinMode(DHT2_PIN, INPUT);
  pinMode(luefter_PIN, OUTPUT);
  pinMode(heizung_PIN, OUTPUT);
  pinMode(safety_PIN, OUTPUT); 
  pinMode(safety_temp_PIN, INPUT_PULLUP); 
  pinMode(heizung_Taster_PIN, INPUT_PULLUP); 

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

  if (Heizung_Status == HIGH) {
    digitalWrite(heizung_PIN, HIGH);
    Serial.println("Set LED ON");
  } 
  else {
    digitalWrite(heizung_PIN, LOW);
    Serial.println("Set LED OFF");
  }

  delay(1000);
  Serial.println("LOOP");


/*
  switch (state)
  {
    case off:
      // do stuff
      Serial.println(State: off);
      break;

    case on:
      // do stuff
      Serial.println(State: on);
      break;

    case flow_down:
      // do stuff
      Serial.println(State: flow_down);
      break;

    case safe:
      // do stuff
      Serial.println(State: safe);
      break;

  }
*/


}

void ICACHE_RAM_ATTR ISR_Heizung_Taster() {
 digitalWrite(2, !digitalRead(2));
  Serial.println("ISR Tacho");
  delay(1000); //Taster entprellen
}

void ICACHE_RAM_ATTR ISR_TACHO() {
 Heizung_Status = !Heizung_Status;
 Serial.println("ISR Heizung Tater");
}

