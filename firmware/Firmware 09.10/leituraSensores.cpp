/*********************Inclusão de Cabeçalho***********************/
#include "leituraSensores.h"

OneWire oneWire(DALLAS_ONEWIRE_SENSOR_PIN);
DallasTemperature dallasSensor(&oneWire);
DHT DHT11Sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

//Função de Configuração dos sensores
void setupSensors() {
  pinMode(SOIL_MOISTURE_SENSOR_PIN, INPUT); //Umidade do Solo
  pinMode(LDR_SENSOR_PIN, INPUT); //Luminosidade

  dallasSensor.begin(); //Temperatura
  DHT11Sensor.begin(); //DHT

  Serial.begin(9600);
  Serial.println("DevTITANS Plant.io inicializado.");
}

//Função de processamento
void processCommand(String command) {
  command.trim();
  command.toUpperCase();

  if (command == "GET_SM") {
    Serial.println(smGetSensors());
  } 
}

//Função de leitura e envio como string
String smGetSensors() {
  int soilMoisture = map(analogRead(SOIL_MOISTURE_SENSOR_PIN), 0, 4095, 10000, 0);
  int dallasTemperature = static_cast<int>(dallasSensor.getTempCByIndex(0) * 100);
  int humidity = static_cast<int>(DHT11Sensor.readHumidity() * 100);
  int temperature = static_cast<int>(DHT11Sensor.readTemperature() * 100);
  int ldrValue = map(analogRead(LDR_SENSOR_PIN), 0, 4095, 0, 10000);

  // Construa a string com os resultados separados por espaço
  String result = String(soilMoisture) + " " + String(dallasTemperature) + " " + String(humidity) + " " + String(temperature) + " " + String(ldrValue);
  
  return result;
}
