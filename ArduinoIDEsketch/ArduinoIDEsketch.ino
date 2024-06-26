/*LIBS-------------------------*/
//DS18B20 Temperature Sensor
#include "OneWire.h"
#include "DallasTemperature.h"
//DHT22
#include "DHT.h"
/*-----------------------------*/



// Define to which pin of the Arduino the 1-Wire bus is connected:
#define ONE_WIRE_BUS 34

#define DHTPIN 35

// Create a new instance of the oneWire class to communicate with any OneWire device:
OneWire oneWire(ONE_WIRE_BUS);

// Pass the oneWire reference to DallasTemperature library:
DallasTemperature sensors(&oneWire);

#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

/*PINS-------------------------*/
//INPPUT
//int const tacho_PIN = 13;
//int const DHT1_PIN = 9;
//int const DHT2_PIN = 10;
//int const safety_temp_PIN = 2;   //Safety Temp (DS18B20)
//int const heizung_Taster_PIN = 0;   //todo Doku
//OUTPUT
int const luefter_PIN = 19;
int const heizung_PIN = 18;
int const led_PIN = 17;
int const relais_PIN = 16;
//const int pwmPIN = 15   
//int const safety_PIN = 15;
/*-----------------------------*/

/* ESP32 GPIO Pins
 PIN   GPIO
 G18 = 18 heizung_PIN
 G19 = 19 luefter_PIN

 G34 = 34 Safety Temp (DS18B20)
 G17 = 17 led_PIN
 G16 = 16 relais_PIN

 G35 = 35 DHT22 1

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
//  pinMode(tacho_PIN, INPUT); 
//  attachInterrupt(digitalPinToInterrupt(heizung_Taster_PIN), ISR_Heizung_Taster, FALLING);
//  attachInterrupt(digitalPinToInterrupt(tacho_PIN), ISR_TACHO, CHANGE);
//  pinMode(DHT1_PIN, INPUT);
//  pinMode(safety_temp_PIN, INPUT_PULLUP); 
//  pinMode(heizung_Taster_PIN, INPUT_PULLUP); 
//OUTPUT
  //RALAIS
  pinMode(luefter_PIN, OUTPUT); //init output tbd
  pinMode(heizung_PIN, OUTPUT); //init output tbd
  pinMode(relais_PIN, OUTPUT);  //init output tbd
  pinMode(led_PIN, OUTPUT);     //init output tbd
  
  //delay(1000);
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
//  pinMode(safety_PIN, OUTPUT); 


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

  dht.begin();

}

void loop() {

  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);
  Serial.println("Temperature: ");
  Serial.println(tempC);  

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

//Test HW Relais Test
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));



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

