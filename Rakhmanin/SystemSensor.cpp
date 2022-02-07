#include "SystemSensor.h"
#include "Log.h"

SystemSensor::SystemSensor()
{
    Log::add("Создание системы датчиков...");
}

void SystemSensor::add(Sensor* sensor)
{
    sensors.push_back(sensor);
}

void SystemSensor::remove(TypeSensor type)
{
    auto it = sensors.begin();
    while (it != sensors.end())
    {
        if ((*it)->getType() == type)
        {
            sensors.remove(*it);
        }
        it++;
    }   
}

DataClimat SystemSensor::getDataClimat()
{
    // first - сумма, second - делитель суммы
    std::pair<float, int> temp = { 0, 0 };
    std::pair<float, int> light = { 0, 0 };
    std::pair<float, int> co2 = { 0, 0 };
    std::pair<float, int> hum = { 0, 0 };
    std::pair<float, int> soilHum = { 0, 0 };

    for (auto it = sensors.begin(); it != sensors.end(); it++)
    {
        switch ((*it)->getType())
        {
        case TypeSensor::Temperature:
            temp.first += (*it)->getData();
            temp.second++;
            break;
        case TypeSensor::Light:
            light.first += (*it)->getData();
            light.second++;
            break;
        case TypeSensor::Humidity:
            hum.first += (*it)->getData();
            hum.second++;
            break;
        case TypeSensor::CO2:
            co2.first += (*it)->getData();
            co2.second++;
            break;
        case TypeSensor::SoilHumidity:
            soilHum.first += (*it)->getData();
            soilHum.second++;
            break;
        default:
            break;
        }
    }

    DataClimat data;
    data.setData(TypeSensor::Temperature, temp.first / temp.second);
    data.setData(TypeSensor::Light, light.first / light.second);
    data.setData(TypeSensor::CO2, co2.first / co2.second);
    data.setData(TypeSensor::Humidity, hum.first / hum.second);
    data.setData(TypeSensor::SoilHumidity, soilHum.first / soilHum.second);

    return data;
}

std::list<Sensor*> SystemSensor::getSensors()
{
    return sensors;
}
