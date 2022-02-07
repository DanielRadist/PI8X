#pragma once

#include "SystemSensor.h"
#include "SystemControl.h"
#include "SystemBuilder.h"
#include "MeteoStation.h"
#include "Culture.h"

#include <iostream>
#include <list>

using namespace std;

class IStrategy;

class MainSystem
{
private:

	IStrategy* strategy;		// Стретегия работы (режим работы)
	SystemSensor* sysSens;		// Система сенсоров
	SystemControl* sysCtrl;		// Система контроля
	MeteoStation* meteoS;		// Метеостанция
	Culture* culrure;			// Выращиваемая культура

public:

	MainSystem();

	/// <summary>
	/// Установка режима работы
	/// </summary>
	/// <param name="strategy"></param>
	void setStrategy(IStrategy* strategy);

	/// <summary>
	/// Установка выращиваемой культуры
	/// </summary>
	/// <param name="culture"></param>
	void setCulture(Culture* culture);

	/// <summary>
	/// воспользоваться стратегией
	/// </summary>
	void solutionStrategy();

	list<Sensor*> getListSensorGH();
	list<Sensor*> getListSensorMS();
};

/// <summary>
/// Интерфес стратегии (режим работы)
/// </summary>
class IStrategy
{
public:
	virtual list<pair<TypeControl, TypeStatus>> solution(DataClimat climat, DataClimat greenhouse, Culture* culture) = 0;
};

/// <summary>
/// Обычный режим работы
/// </summary>
class NormalStrategy : public IStrategy
{
public:
	NormalStrategy();
	list<pair<TypeControl, TypeStatus>> solution(DataClimat climat, DataClimat greenhouse, Culture* culture);
};

/// <summary>
/// Экономичный режим работы
/// </summary>
class EcoStrategy : public IStrategy
{
public:
	EcoStrategy();
	list<pair<TypeControl, TypeStatus>> solution(DataClimat climat, DataClimat greenhouse, Culture* culture);
};

