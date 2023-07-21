// Inclui esse cabeçalho apenas uma vez
#pragma once

// Classe ifstream
#include <fstream>

// Função GetBoolProperty
#include <android-base/properties.h>

// Função e struct stat
#include <sys/stat.h>

// Permite usar string diretamente ao invés de std::string
using namespace std;

namespace devtitans::plantio {       // Pacote Plantio

class Plantio {
    public:
        /**
         * Verifica se o diretório /sys/kernel/plantio existe. Se existir
         * o dispositivo Plantio está conectado via USB.
         * 
         * Retorna:
         *      0: dispositivo não encontrado
         *      1: sucesso
         */
        int connect();

        int getSoilMoisture();
        long getSoilMoistureInterval();
        bool setSoilMoistureInterval(long milliseconds);
        
        int getSoilTemperature();
        long getSoilTemperatureInterval();
        bool setSoilTemperatureInterval(long milliseconds);

        int getAmbientMoisture();
        long getAmbientMoistureInterval();
        bool setAmbientMoistureInterval(long milliseconds);

        int getAmbientTemperature();
        long getAmbientTemperatureInterval();
        bool setAmbientTemperatureInterval(long milliseconds);

        int getAmbientLight();
        long getAmbientLightInterval();
        bool setAmbientLightInterval(long milliseconds);

    private:
        int readFileValue(string file);
        bool writeFileValue(string file, long value);
};

} // namespace