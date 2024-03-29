/*LIBS-------------------------*/
//DS18B20 Temperature Sensor
#include "OneWire.h"
#include "DallasTemperature.h"
/*-----------------------------*/

// Define to which pin of the Arduino the 1-Wire bus is connected:
#define ONE_WIRE_BUS 2

// Create a new instance of the oneWire class to communicate with any OneWire device:
OneWire oneWire(ONE_WIRE_BUS);

// Pass the oneWire reference to DallasTemperature library:
DallasTemperature sensors(&oneWire);

/*PINS-------------------------*/
//INPPUT
int const tacho_PIN = 13;
int const DHT1_PIN = 9;
int const DHT2_PIN = 10;
//int const safety_temp_PIN = 2;   //Safety Temp (DS18B20)
int const heizung_Taster_PIN = 0;   //todo Doku
//OUTPUT
int const luefter_PIN = 4;
int const heizung_PIN = 5;
int const led_PIN = 14;
int const relais_PIN = 12;
//const int pwmPIN = 15   
int const safety_PIN = 15;
/*-----------------------------*/

/* ESP8266 NodeMCU GPIO Pins
 PIN   GPIO
(D0) = 16 
  D1 = 5  heizung_PIN
  D2 = 4  luefter_PIN
(D3) = 0  heizung_Taster_PIN
(D4) = 2  Safety Temp (DS18B20)
  D5 = 14 led_PIN
  D6 = 12 relais_PIN
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
//INPPUT
  pinMode(tacho_PIN, INPUT); 
  attachInterrupt(digitalPinToInterrupt(heizung_Taster_PIN), ISR_Heizung_Taster, FALLING);
  attachInterrupt(digitalPinToInterrupt(tacho_PIN), ISR_TACHO, CHANGE);
  pinMode(DHT1_PIN, INPUT);
//  pinMode(safety_temp_PIN, INPUT_PULLUP); 
  pinMode(heizung_Taster_PIN, INPUT_PULLUP); 
//OUTPUT
  //RALAIS
  pinMode(luefter_PIN, OUTPUT); //init output tbd
  pinMode(heizung_PIN, OUTPUT); //init output tbd
  pinMode(relais_PIN, OUTPUT);  //init output tbd
  pinMode(led_PIN, OUTPUT);     //init output tbd
  delay(1000);
    /*
    //RALAIS INIT SEQUENCE
    digitalWrite(luefter_PIN, HIGH);
    Serial.println("luefter_OFF");
    delay(1000);
    digitalWrite(heizung_PIN, HIGH);
    Serial.println("heizung_OFF");
    delay(1000);
    digitalWrite(led_PIN, HIGH);
    Serial.println("led_OFF");
    delay(1000);
    digitalWrite(relais_PIN, HIGH);
    Serial.println("relais_OFF");
    delay(1000);
    */
  //SAFETY PIN
  pinMode(safety_PIN, OUTPUT); 


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

  sensors.begin();  //DS18B20 Temperature Sensor

}

void loop() {

  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);
  Serial.print("Temperature: ");
  Serial.print(tempC);  
/*
//Test HW Relais
  digitalWrite(luefter_PIN, HIGH);
  Serial.println("luefter_OFF");
  delay(1000);
  digitalWrite(heizung_PIN, HIGH);
  Serial.println("heizung_OFF");
  delay(1000);
  digitalWrite(led_PIN, HIGH);
  Serial.println("led_OFF");
  delay(1000);
  digitalWrite(relais_PIN, HIGH);
  Serial.println("relais_OFF");
  delay(1000);
 
 
  digitalWrite(luefter_PIN, LOW);
  Serial.println("luefter_ON");
  delay(1000);
  digitalWrite(heizung_PIN, LOW);
  Serial.println("heizung_ON");
  delay(1000);
  digitalWrite(led_PIN, LOW);
  Serial.println("led_ON");
  delay(1000);
  digitalWrite(relais_PIN, LOW);
  Serial.println("relais_ON");
  delay(1000);
*/
  Serial.println("LOOP");
  delay(1000);

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

