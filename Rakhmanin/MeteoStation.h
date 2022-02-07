#pragma once
#include "Sensor.h"
#include <list>


class MeteoStation
{
private:

	Sensor* temperature;
	Sensor* co2;
	Sensor* humidity;

public:
	MeteoStation();
	~MeteoStation();

	DataClimat getData();

	std::list<Sensor*> getSensors();

	friend class DataSource;
};

