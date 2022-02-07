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

	IStrategy* strategy;		// ��������� ������ (����� ������)
	SystemSensor* sysSens;		// ������� ��������
	SystemControl* sysCtrl;		// ������� ��������
	MeteoStation* meteoS;		// ������������
	Culture* culrure;			// ������������ ��������

public:

	MainSystem();

	/// <summary>
	/// ��������� ������ ������
	/// </summary>
	/// <param name="strategy"></param>
	void setStrategy(IStrategy* strategy);

	/// <summary>
	/// ��������� ������������ ��������
	/// </summary>
	/// <param name="culture"></param>
	void setCulture(Culture* culture);

	/// <summary>
	/// ��������������� ����������
	/// </summary>
	void solutionStrategy();

	list<Sensor*> getListSensorGH();
	list<Sensor*> getListSensorMS();
};

/// <summary>
/// �������� ��������� (����� ������)
/// </summary>
class IStrategy
{
public:
	virtual list<pair<TypeControl, TypeStatus>> solution(DataClimat climat, DataClimat greenhouse, Culture* culture) = 0;
};

/// <summary>
/// ������� ����� ������
/// </summary>
class NormalStrategy : public IStrategy
{
public:
	NormalStrategy();
	list<pair<TypeControl, TypeStatus>> solution(DataClimat climat, DataClimat greenhouse, Culture* culture);
};

/// <summary>
/// ����������� ����� ������
/// </summary>
class EcoStrategy : public IStrategy
{
public:
	EcoStrategy();
	list<pair<TypeControl, TypeStatus>> solution(DataClimat climat, DataClimat greenhouse, Culture* culture);
};

