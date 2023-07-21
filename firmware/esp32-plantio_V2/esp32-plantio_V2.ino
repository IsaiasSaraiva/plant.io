#include <OneWire.h>
#include <DallasTemperature.h>
#include <DHT.h>

// GPIO Sensor LDR
#define LDR 36 // ESP32 pin GIOP36 (ADC0)

// GPIO Sensor DHT11
#define DHT_SENSOR_PIN  14 // Pino do ESP32 GIOP21 conectado ao sensor DHT11
#define DHT_SENSOR_TYPE DHT11
DHT dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

// GPIO Sensor Temperatura do Solo
const int oneWireBus = 21;

//GPIO Sensor Umidade do Solo
const int SOIL_MOISTURE_SENSOR_PIN = 34;

// Configura uma instância OneWire para se comunicar com dispositivos OneWire
OneWire oneWire(oneWireBus);

// Referência oneWire para o sensor de temperatura Dallas
DallasTemperature sensors(&oneWire);

int pool_delay = 200;

void setup() {
  Serial.begin(9600);
  pinMode(SOIL_MOISTURE_SENSOR_PIN, INPUT);

  Serial.println("DevTITANS Plant.io inicializado.");
  sensors.begin();
  dht_sensor.begin();
}

void loop() {
  String serialCommand;

  while (Serial.available() > 0) {
    char serialChar = Serial.read();
    serialCommand += serialChar;

    if (serialChar == '\n') {
      processCommand(serialCommand);
      serialCommand = "";
    }
  }

  delay(pool_delay);
}

void processCommand(String command) {
  command.trim();
  command.toUpperCase();
  // Umidade do Solo = SM
  if (command == "GET_SM") {
    Serial.println("RES GET_SM " + String(smGetValue(), 2));
  } // Temperatura do Solo = ST
  else if (command == "GET_ST") {
    sensors.requestTemperatures();
    float temperatureC = sensors.getTempCByIndex(0);
    Serial.print("RES GET_ST ");
    Serial.println(temperatureC);
  } // Umidade Ambiente = AM
  else if (command == "GET_AM") {
    float humi = dht_sensor.readHumidity();
    Serial.print("RES GET_AM ");
    Serial.println(humi);
  } // Temperatura Ambiente = AT
  else if (command == "GET_AT") {
    float tempC = dht_sensor.readTemperature();
    Serial.print("RES GET_AT ");
    Serial.println(tempC);
  }// LDR = AL
  else if(command == "GET_AL"){
   Serial.println("RES GET_AL " + String(alGetValue(), 2));
  } else if (command.startsWith("POLL_DELAY")) {
    int poll_value = command.substring(11).toInt();

    if (poll_value >= 100) {
      pool_delay = poll_value;
      Serial.printf("RES POLL_DELAY %d\n", poll_value);
    } else {
      Serial.printf("RES POLL_DELAY -1\n");
    }
  } else {
    Serial.println("ERR Unknown command.");
  }
}

float smGetValue() {
  return (map(analogRead(SOIL_MOISTURE_SENSOR_PIN), 0, 4095, 10000, 0) / 100.0);
}

float alGetValue() {
  return (map(analogRead(LDR), 0, 4095, 10000, 0) / 100.0);
}

