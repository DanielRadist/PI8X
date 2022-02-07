#include "DataSource.h"

DataSource::DataSource(Sensor* sensor)
{
	this->_sensor = sensor;
}

void DataSource::setData(int val)
{
	this->_sensor->data = val;
}
