#include "SystemBuilder.h"
#include "Log.h"


SystemSensorBuilder::SystemSensorBuilder()
{
	Log::add("�������� ��������� �������� �������. ");
	sysSens = new SystemSensor();
}

void SystemSensorBuilder::makeTemperature()
{
	sysSens->add(new SensorTemperature());
}

void SystemSensorBuilder::makeHumidity()
{
	sysSens->add(new SensorHumidity);
}

void SystemSensorBuilder::makeCO2()
{
	sysSens->add(new SensorCO2);
}

void SystemSensorBuilder::makeSoilHumidity()
{
	sysSens->add(new SensorSoilHumidity);
}

void SystemSensorBuilder::makeLight()
{
	sysSens->add(new SensorLight);
}

SystemSensor* SystemSensorBuilder::getResult()
{
	return sysSens;
}



SystemControlBuilder::SystemControlBuilder()
{
	Log::add("�������� ��������� ������������ �������. ");
	sysCtrl = new SystemControl();
}

void SystemControlBuilder::makeWindow()
{
	sysCtrl->add(sysCtrl->create(TypeControl::Window));
}

void SystemControlBuilder::makeCooler()
{
	sysCtrl->add(sysCtrl->create(TypeControl::Cooler));
}

void SystemControlBuilder::makeHeater()
{
	sysCtrl->add(sysCtrl->create(TypeControl::Heater));
}

void SystemControlBuilder::makeCO2()
{
	sysCtrl->add(sysCtrl->create(TypeControl::CO2));
}

void SystemControlBuilder::makeSoilHumidity()
{
	sysCtrl->add(sysCtrl->create(TypeControl::SoilHumidity));
}

void SystemControlBuilder::makeLight()
{
	sysCtrl->add(sysCtrl->create(TypeControl::Light));
}

void SystemControlBuilder::makeHumidity()
{
	sysCtrl->add(sysCtrl->create(TypeControl::Humidity));
}

SystemControl* SystemControlBuilder::getResult()
{
	return sysCtrl;
}




SystemDirector::SystemDirector()
{
	Log::add("�������� ���������. ");
}

SystemDirector* SystemDirector::Instance()
{
	if (_instance == nullptr)
		_instance = new SystemDirector();
	else
		Log::add("����� ���������. ");
	return _instance;
}

void SystemDirector::makeSystemSensor(ISystemBuilder* builder)
{
	builder->makeTemperature();
	builder->makeLight();
	builder->makeHumidity();
	builder->makeSoilHumidity();
	builder->makeCO2();

	Log::add("�������� ������� �������� ������� �������� �������. ");
}

void SystemDirector::makeSystemControl(ISystemBuilder* builder)
{
	builder->makeHeater();
	builder->makeCooler();
	builder->makeLight();
	builder->makeHumidity();
	builder->makeSoilHumidity();
	builder->makeCO2();
	builder->makeWindow();

	Log::add("�������� ������� ����������� ������� ��������. ");
}

SystemDirector* SystemDirector::_instance = nullptr;