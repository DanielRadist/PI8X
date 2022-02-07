#pragma once
#include "TypeSensor.h"

class DataClimat;

class Prototype
{
public:
	virtual DataClimat clone() = 0;
};

class DataClimat : public Prototype
{
public:

	DataClimat clone()
	{
		return (new DataClimat(this));
	}

	DataClimat(DataClimat* data)
	{
		this->temperature = data->temperature;
		this->co2 = data->co2;
		this->light = data->light;
		this->humidity = data->humidity;
		this->soilHumidity = data->soilHumidity;
	}

	DataClimat()
	{
		this->temperature = INT32_MIN;
		this->co2 = INT32_MIN;
		this->light = INT32_MIN;
		this->humidity = INT32_MIN;
		this->soilHumidity = INT32_MIN;
	}

	float getData(TypeSensor type)
	{
		switch (type)
		{
		case TypeSensor::Temperature:
			return temperature;

		case TypeSensor::Light:
			return light;

		case TypeSensor::Humidity:
			return humidity;

		case TypeSensor::CO2:
			return co2;

		case TypeSensor::SoilHumidity:
			return soilHumidity;

		default:
			return INT32_MIN + 1;
		}
	}

	void setData(TypeSensor type, float value)
	{
		switch (type)
		{
		case TypeSensor::Temperature:
			temperature = value;
			break;
		case TypeSensor::Light:
			light = value;
			break;
		case TypeSensor::Humidity:
			humidity = value;
			break;
		case TypeSensor::CO2:
			co2 = value;
			break;
		case TypeSensor::SoilHumidity:
			soilHumidity = value;
			break;
		default:
			return;
		}
	}

private:

	float temperature;
	float light;
	float co2;
	float humidity;
	float soilHumidity;
};