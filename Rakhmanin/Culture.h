#pragma once
#include <string>
//#include "TypeSensor.h"
#include "DataClimat.h"

class Culture
{
public:
	Culture(std::string name, DataClimat min, DataClimat max);

	/// <summary>
	/// �������� ���������� �������� �������������� �������, ������� ��������� Sensor'�� ���� TypeSensor
	/// </summary>
	/// <param name="typeValue">��� ������� - ��� ��������</param>
	/// <returns>����������� �������� �������������� �������</returns>
	int getMin(TypeSensor typeValue);

	/// <summary>
	/// �������� ������������ �������� �������������� �������, ������� ��������� Sensor'�� ���� TypeSensor
	/// </summary>
	/// <param name="typeValue">��� ������� - ��� ��������</param>
	/// <returns>������������ �������� �������������� �������</returns>
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

