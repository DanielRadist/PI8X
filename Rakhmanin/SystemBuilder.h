#pragma once
#include <list>
#include "SystemSensor.h"
#include "SystemControl.h"

class ISystemBuilder
{
public:

	virtual void makeTemperature() = 0;			//��� MS ��������
	virtual void makeCooler() = 0;				//��� GH �����������
	virtual void makeHeater() = 0;				//��� GH ������������

	virtual void makeHumidity() = 0;			//��� MS � GH ���������
	virtual void makeCO2() = 0;					//��� MS � GH ������� ��2
	virtual void makeSoilHumidity() = 0;		//��� GH ��������� �����
	virtual void makeLight() = 0;				//��� GH ������������
	virtual void makeWindow() = 0;				//��� GH ���� � �������
};

/// <summary>
/// ��������� ������� �������� �������
/// </summary>
class SystemSensorBuilder : public ISystemBuilder
{
public:
	SystemSensorBuilder();

	// realizable
	void makeTemperature();				// ���������
	void makeHumidity();				// ������ ��������� �������
	void makeCO2();						// ������ ������ ��2
	void makeSoilHumidity();			// ������ ��������� �����
	void makeLight();					// ������ ������������

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
/// ��������� ������� �������� �������
/// </summary>
class SystemControlBuilder : public ISystemBuilder
{
public:
	SystemControlBuilder();

	// realizable
	void makeWindow();				// ������ ����
	void makeCooler();				// �����������
	void makeHeater();				// ������������
	void makeCO2();					// ���� ��2
	void makeSoilHumidity();		// ���� ������
	void makeLight();				// ���������� ����������
	void makeHumidity();			// ����������� �������

	// Non realizable
	void makeTemperature() {}
	
	SystemControl* getResult();

private:

	SystemControl* sysCtrl;
};

/// <summary>
/// �������� ���������� �������
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