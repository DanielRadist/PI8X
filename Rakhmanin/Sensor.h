#pragma once
#include "DataClimat.h"

class Sensor
{
public:
	Sensor(TypeSensor type);

	TypeSensor getType();

	virtual int getData();

	friend class DataSource;

protected:
	TypeSensor type;

	int data;
};


class SensorTemperature : public Sensor
{
public:
	SensorTemperature();
};

class SensorLight : public Sensor
{
public:
	SensorLight();
};

class SensorCO2 : public Sensor
{
public:
	SensorCO2();
};

class SensorHumidity : public Sensor
{
public:
	SensorHumidity();
};

class SensorSoilHumidity : public Sensor
{
public:
	SensorSoilHumidity();
};