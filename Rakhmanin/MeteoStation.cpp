#include "MeteoStation.h"
#include "Log.h"
//#include <list>

MeteoStation::MeteoStation()
{
	Log::add("Подключение к Метеостанции. ");
	temperature = new SensorTemperature();
	co2 = new SensorCO2();
	humidity = new SensorHumidity();
}

MeteoStation::~MeteoStation()
{
	Log::add("Отключение от Метеостанции. ");
	delete temperature;
	delete co2;
	delete humidity;
}

DataClimat MeteoStation::getData()
{
	DataClimat tmp;
	tmp.setData(TypeSensor::Temperature, temperature->getData());
	tmp.setData(TypeSensor::CO2, co2->getData());
	tmp.setData(TypeSensor::Humidity, humidity->getData());
	return tmp;
}

std::list<Sensor*> MeteoStation::getSensors()
{
	std::list<Sensor*> tmp;
	tmp.push_back(temperature);
	tmp.push_back(co2);
	tmp.push_back(humidity);
	return tmp;
}
