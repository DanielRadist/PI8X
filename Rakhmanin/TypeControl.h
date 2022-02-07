#pragma once
#include <map>
#include <string>

enum class TypeControl
{
	Heater,					// Обогреватель
	Cooler,					// Кондиционер
	Light,					// Освещение
	Humidity,				// Увлажнитель воздуха
	SoilHumidity,			// Кран воды
	CO2,					// Кран углекислого газа
	Window,					// Управление окном
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