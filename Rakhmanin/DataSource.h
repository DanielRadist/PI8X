#pragma once
#include "Sensor.h"
#include "TypeSensor.h"


class DataSource
{
private:

	Sensor*_sensor;

public:

	/// <summary>
	/// �������� ����� ����� ���������� � �������� ������
	/// </summary>
	/// <param name="sensor">������, �������� ����� �������� ������</param>
	DataSource(Sensor* sensor);

	/// <summary>
	/// ���������� ���� data ����� Sensor �������� val
	/// </summary>
	void setData(int val);
};


