#pragma once
#include <string>
//#include "TypeSensor.h"
#include "DataClimat.h"

class Culture
{
public:
	Culture(std::string name, DataClimat min, DataClimat max);

	/// <summary>
	/// ѕолучить минимально значение характеристики климата, которое считываем Sensor'ом типа TypeSensor
	/// </summary>
	/// <param name="typeValue">“ип датчика - тип значени€</param>
	/// <returns>ћинимальное значение характеристика климата</returns>
	int getMin(TypeSensor typeValue);

	/// <summary>
	/// ѕолучить максимальное значение характеристики климата, которое считываем Sensor'ом типа TypeSensor
	/// </summary>
	/// <param name="typeValue">“ип датчика - тип значени€</param>
	/// <returns>ћаксимальное значение характеристика климата</returns>
	int getMax(TypeSensor typeValue);

	std::string getName();

private:

	std::string name;
	std::pair<int, int> temperature;
	std::pair<int, int> light;
	std::pair<int, int> humidity;
	std::pair<int, int> co2;
	std::pair<int, int> soilHumidity;
};

