#ifndef LEITURASENORES_H
#define LEITURASENORES_H

//Inclusão de Bibliotecas de leitura dos sensores
#include <OneWire.h>
#include <DallasTemperature.h>
#include <DHT.h>

// Definição dos pinos
#define SOIL_MOISTURE_SENSOR_PIN 34 // SM
#define DALLAS_ONEWIRE_SENSOR_PIN 21 // ST
#define DHT_SENSOR_PIN 14 // AM, AT
#define LDR_SENSOR_PIN 36 // AL

// Config
#define DHT_SENSOR_TYPE DHT11

// Declaração das funções
void setupSensors(); // Configuração dos Sensores
void processCommand(String command); // Envio via String
String smGetSensors(); // Retorna os resultados dos sensores como uma string

#endif
