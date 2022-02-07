#include "Sensor.h"
#include "Log.h"

// ISensor
//
Sensor::Sensor(TypeSensor type)
{
	this->type = type;
}
/*
void Sensor::�onnection(DataSource* stream)
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
	Log::add("����������� ������� �����������. ");
}

SensorLight::SensorLight() : Sensor(TypeSensor::Light)
{
	Log::add("����������� ������� ������������. ");
}

SensorCO2::SensorCO2() : Sensor(TypeSensor::CO2)
{
	Log::add("����������� ������� ���� ��2. ");
}

SensorHumidity::SensorHumidity() : Sensor(TypeSensor::Humidity)
{
	Log::add("����������� ������� ��������� �������. ");
}

SensorSoilHumidity::SensorSoilHumidity() : Sensor(TypeSensor::SoilHumidity)
{
	Log::add("����������� ������� ��������� �����. ");
}
