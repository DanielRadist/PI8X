#include "Control.h"
#include "Log.h"

IControl::IControl(TypeControl type)
{
    this->type = type;
}

TypeControl IControl::getType()
{
    return type;
}



ControlHeater::ControlHeater() : IControl(TypeControl::Heater)
{
    Log::add("����������� ����������� ������������. ");
}

void ControlHeater::on()
{
    Log::add("��������� ������������. ");
}

void ControlHeater::off()
{
    Log::add("���������� ������������. ");
}


ControlCooler::ControlCooler() : IControl(TypeControl::Cooler)
{
    Log::add("����������� ����������� ������������. ");
}

void ControlCooler::on()
{
    Log::add("��������� ������������. ");
}

void ControlCooler::off()
{
    Log::add("���������� ������������. ");
}


ControlLight::ControlLight() : IControl(TypeControl::Light)
{
    Log::add("����������� ����������� �������������� ���������. ");
}

void ControlLight::on()
{
    Log::add("��������� �������������� ���������. ");
}

void ControlLight::off()
{
    Log::add("���������� �������������� ���������. ");
}



AdapterControlWindow::AdapterControlWindow(ControlWindow* window) : IControl(TypeControl::Window)
{
    Log::add("����������� ����������� ������� ����. ");
    this->window = window;
}

void AdapterControlWindow::on()
{
    Log::add("�������� ���� " + window->openness(valueOpen));
}

void AdapterControlWindow::off()
{
    Log::add("�������� ���� " + window->openness(valueClose));
}

void AdapterControlWindow::setValueOpen(int value)
{
    valueOpen = value;
}

void AdapterControlWindow::setValueClose(int value)
{
    valueClose = value;
}



ControlWindow::ControlWindow()
{
}

string ControlWindow::openness(int value)
{
    return string("(" + to_string(value) + "%) ");
}



ControlHumidity::ControlHumidity() : IControl(TypeControl::Humidity)
{
    Log::add("����������� ����������� �����������. ");
}

void ControlHumidity::on()
{
    Log::add("��������� �����������. ");
}

void ControlHumidity::off()
{
    Log::add("���������� �����������. ");
}

ControlCO2::ControlCO2() : IControl(TypeControl::CO2)
{
    Log::add("����������� ����������� ����� ��2. ");
}

void ControlCO2::on()
{
    Log::add("�������� ����� ��2. ");
}

void ControlCO2::off()
{
    Log::add("�������� ����� ��2. ");
}

ControlSoilHumidity::ControlSoilHumidity() : IControl(TypeControl::SoilHumidity)
{
    Log::add("����������� ����������� ����� ������. ");
}

void ControlSoilHumidity::on()
{
    Log::add("�������� ����� ������. ");
}

void ControlSoilHumidity::off()
{
    Log::add("�������� ����� ������. ");
}

