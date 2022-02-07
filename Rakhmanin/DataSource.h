#pragma once
#include "Sensor.h"
#include "TypeSensor.h"


class DataSource
{
private:

	Sensor*_sensor;

public:

	/// <summary>
	/// Создание порта между источником и объектом класса
	/// </summary>
	/// <param name="sensor">Объект, которому будем отсылать данные</param>
	DataSource(Sensor* sensor);

	/// <summary>
	/// Присвоение полю data класс Sensor значение val
	/// </summary>
	void setData(int val);
};


