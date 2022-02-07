#include "Culture.h"

Culture::Culture(std::string name, DataClimat min, DataClimat max)
{
	this->name = name;

	temperature.first = min.getData(TypeSensor::Temperature);
	temperature.second = max.getData(TypeSensor::Temperature);

	light.first = min.getData(TypeSensor::Light);
	light.second = max.getData(TypeSensor::Light);

	co2.first = min.getData(TypeSensor::CO2);
	co2.second = max.getData(TypeSensor::CO2);

	humidity.first = min.getData(TypeSensor::Humidity);
	humidity.second = max.getData(TypeSensor::Humidity);

	soilHumidity.first = min.getData(TypeSensor::SoilHumidity);
	soilHumidity.second = max.getData(TypeSensor::SoilHumidity);
}

int Culture::getMin(TypeSensor typeValue)
{
	switch (typeValue)
	{
	case TypeSensor::Temperature:
		return temperature.first;
	case TypeSensor::Light:
		return light.first;
	case TypeSensor::CO2:
		return co2.first;
	case TypeSensor::Humidity:
		return humidity.first;
	case TypeSensor::SoilHumidity:
		return soilHumidity.first;
	default:
		break;
	}
	return INT32_MIN;
}

int Culture::getMax(TypeSensor typeValue)
{
	switch (typeValue)
	{
	case TypeSensor::Temperature:
		return temperature.second;
	case TypeSensor::Light:
		return light.second;
	case TypeSensor::CO2:
		return co2.second;
	case TypeSensor::Humidity:
		return humidity.second;
	case TypeSensor::SoilHumidity:
		return soilHumidity.second;
	default:
		break;
	}
	return INT32_MAX;
}

std::string Culture::getName()
{
	return name;
}
