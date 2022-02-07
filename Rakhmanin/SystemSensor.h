#pragma once
#include "Sensor.h"
#include <list>


class SystemSensor
{
public:
	SystemSensor();

	void add(Sensor* sensor);

	void remove(TypeSensor type);

	DataClimat getDataClimat();

	std::list<Sensor*> getSensors();

private:

	std::list<Sensor*> sensors;
};

