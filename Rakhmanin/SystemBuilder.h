#pragma once
#include <list>
#include "SystemSensor.h"
#include "SystemControl.h"

class ISystemBuilder
{
public:

	virtual void makeTemperature() = 0;			//для MS термоетр
	virtual void makeCooler() = 0;				//для GH кондиционер
	virtual void makeHeater() = 0;				//для GH обогреватель

	virtual void makeHumidity() = 0;			//для MS и GH влажность
	virtual void makeCO2() = 0;					//для MS и GH уровень СО2
	virtual void makeSoilHumidity() = 0;		//для GH влажность почвы
	virtual void makeLight() = 0;				//для GH освещенность
	virtual void makeWindow() = 0;				//для GH окно в теплице
};

/// <summary>
/// Строитель системы датчиков климата
/// </summary>
class SystemSensorBuilder : public ISystemBuilder
{
public:
	SystemSensorBuilder();

	// realizable
	void makeTemperature();				// термометр
	void makeHumidity();				// датчик влажности воздуха
	void makeCO2();						// датчик уровня СО2
	void makeSoilHumidity();			// датчик влажности почвы
	void makeLight();					// датчик освещенности

	// Not realizable:
	void makeWindow() {}
	void makeCooler() {}
	void makeHeater() {}

	SystemSensor* getResult();

	std::list<Sensor*> sensors;

private:

	SystemSensor* sysSens;
};


/// <summary>
/// Строитель системы контроля климата
/// </summary>
class SystemControlBuilder : public ISystemBuilder
{
public:
	SystemControlBuilder();

	// realizable
	void makeWindow();				// Привод окна
	void makeCooler();				// Кондиционер
	void makeHeater();				// Обогреватель
	void makeCO2();					// Кран СО2
	void makeSoilHumidity();		// Кран полива
	void makeLight();				// Управление освещением
	void makeHumidity();			// Увлажнитель воздуха

	// Non realizable
	void makeTemperature() {}
	
	SystemControl* getResult();

private:

	SystemControl* sysCtrl;
};

/// <summary>
/// Директор строителей климата
/// </summary>
class SystemDirector
{
public:
	SystemDirector();

	static SystemDirector* Instance();

	void makeSystemSensor(ISystemBuilder* builder);

	void makeSystemControl(ISystemBuilder* builder);

private:
	static SystemDirector* _instance;
};