#pragma once
#include <map>
#include <string>

enum class TypeSensor
{
	Temperature,			// ������ �����������
	Light,					// ������ ������������
	Humidity,				// ������ ���������
	CO2,					// ������ ����������� ����
	SoilHumidity,			// ������ ��������� �����
	System
};

inline std::string TypeSensorToStr(TypeSensor type)
{
	std::map<TypeSensor, std::string> nameSensor
	{
		{TypeSensor::Temperature, "Temperature"},
		{TypeSensor::Light, "Light"},
		{TypeSensor::Humidity, "Humidity"},
		{TypeSensor::CO2, "CO2"},
		{TypeSensor::SoilHumidity, "Soil_Humidity"},
		{TypeSensor::System, "System"}
	};
	return nameSensor.at(type);
}