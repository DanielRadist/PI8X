#include "Sensor.h"
#include "Log.h"

// ISensor
//
Sensor::Sensor(TypeSensor type)
{
	this->type = type;
}
/*
void Sensor::сonnection(DataSource* stream)
{
	this->stream = stream;
}*/




TypeSensor Sensor::getType()
{
	return type;
}

int Sensor::getData()
{
	return data;
}


// SensorTemperature
//
SensorTemperature::SensorTemperature() : Sensor(TypeSensor::Temperature)
{
	Log::add("Подключение датчика температуры. ");
}

SensorLight::SensorLight() : Sensor(TypeSensor::Light)
{
	Log::add("Подключение датчика освещенности. ");
}

SensorCO2::SensorCO2() : Sensor(TypeSensor::CO2)
{
	Log::add("Подключение датчика газа СО2. ");
}

SensorHumidity::SensorHumidity() : Sensor(TypeSensor::Humidity)
{
	Log::add("Подключение датчика влажности воздуха. ");
}

SensorSoilHumidity::SensorSoilHumidity() : Sensor(TypeSensor::SoilHumidity)
{
	Log::add("Подключение датчика влажности почвы. ");
}
