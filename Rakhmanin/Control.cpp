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
    Log::add("Подключение контроллера обогревателя. ");
}

void ControlHeater::on()
{
    Log::add("Включение обогревателя. ");
}

void ControlHeater::off()
{
    Log::add("Отключение обогревателя. ");
}


ControlCooler::ControlCooler() : IControl(TypeControl::Cooler)
{
    Log::add("Подключение контроллера кондиционера. ");
}

void ControlCooler::on()
{
    Log::add("Включение кондиционера. ");
}

void ControlCooler::off()
{
    Log::add("Отключение кондиционера. ");
}


ControlLight::ControlLight() : IControl(TypeControl::Light)
{
    Log::add("Подключение контроллера искусственного освещения. ");
}

void ControlLight::on()
{
    Log::add("Включение искусственного освещения. ");
}

void ControlLight::off()
{
    Log::add("Отключение искусственного освещения. ");
}



AdapterControlWindow::AdapterControlWindow(ControlWindow* window) : IControl(TypeControl::Window)
{
    Log::add("Подключение контроллера привода окна. ");
    this->window = window;
}

void AdapterControlWindow::on()
{
    Log::add("Открытие окна " + window->openness(valueOpen));
}

void AdapterControlWindow::off()
{
    Log::add("Закрытие окна " + window->openness(valueClose));
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
    Log::add("Подключение контроллера увлажнителя. ");
}

void ControlHumidity::on()
{
    Log::add("Включение увлажнителя. ");
}

void ControlHumidity::off()
{
    Log::add("Отключение увлажнителя. ");
}

ControlCO2::ControlCO2() : IControl(TypeControl::CO2)
{
    Log::add("Подключение контроллера крана СО2. ");
}

void ControlCO2::on()
{
    Log::add("Открытие крана СО2. ");
}

void ControlCO2::off()
{
    Log::add("Закрытие крана СО2. ");
}

ControlSoilHumidity::ControlSoilHumidity() : IControl(TypeControl::SoilHumidity)
{
    Log::add("Подключение контроллера крана полива. ");
}

void ControlSoilHumidity::on()
{
    Log::add("Открытие крана полива. ");
}

void ControlSoilHumidity::off()
{
    Log::add("Закрытие крана полива. ");
}

