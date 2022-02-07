#pragma once
#include <map>
#include <string>

enum class TypeControl
{
	Heater,					// ������������
	Cooler,					// �����������
	Light,					// ���������
	Humidity,				// ����������� �������
	SoilHumidity,			// ���� ����
	CO2,					// ���� ����������� ����
	Window,					// ���������� �����
	System
};

inline std::string TypeControlToStr(TypeControl type)
{
	std::map<TypeControl, std::string> nameSensor
	{
		{TypeControl::Heater, "Heater"},
		{TypeControl::Light, "Light"},
		{TypeControl::Humidity, "Humidity"},
		{TypeControl::SoilHumidity, "Valve_water"},
		{TypeControl::CO2, "Valve_CO2"},
		{TypeControl::Cooler, "Cooler"},
		{TypeControl::Window, "Window"},
		{TypeControl::System, "System"}
	};
	return nameSensor.at(type);
}