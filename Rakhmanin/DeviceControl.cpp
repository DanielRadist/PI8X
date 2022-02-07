#include <iostream>
#include <string>

#include "DeviceControl.h"
#include "Control.h"
#include "Log.h"


ONState::ONState() {}

bool ONState::on()
{
    return false;       // нельзя включить, что включенно
}

bool ONState::off()
{
    return true;        // можно выключить, что включенно
}

TypeStatus ONState::get()
{
    return TypeStatus::ON;
}


OFFState::OFFState() {}

bool OFFState::on()
{
    return true;        // можно включить, что выключено
}

bool OFFState::off()
{
    return false;       // нельзя вывключить, что выключено
}

TypeStatus OFFState::get()
{
    return TypeStatus::OFF;
}


DeviceControl::DeviceControl(TypeControl type)
{
    switch (type)
    {
    case TypeControl::Heater:
        this->control = new ControlHeater();
        break;

    case TypeControl::Cooler:
        this->control = new ControlCooler();
        break;

    case TypeControl::Light:
        this->control = new ControlLight();
        break;

    case TypeControl::Humidity:
        this->control = new ControlHumidity();
        break;

    case TypeControl::SoilHumidity:
        this->control = new ControlSoilHumidity();
        break;

    case TypeControl::CO2:
        this->control = new ControlCO2();
        break;


    case TypeControl::Window:
    {
        ControlWindow* window = new ControlWindow();            // объект класса контроллера окна
        _window = new AdapterControlWindow(window);             // адаптер класса контроллера окна
        this->control = _window;
        break;
    }


    default:
        this->control = nullptr;
        break;
    }

    state = new OFFState();                                     // изначально выключен
}


void DeviceControl::on()
{
    if (state->get() == TypeStatus::ON)
    {
        //Log::add("Устройство " + TypeControlToStr(control->getType()) + " уже ON. ");
    }
    else
    {
        control->on();                  // включение

        delete state;                   // изменения состояния
        state = new ONState();

        //Log::add("Изменено состояния " + TypeControlToStr(control->getType()) + " на ON. ");
    }
}

void DeviceControl::off()
{
    if (state->get() == TypeStatus::OFF)
    {
        //Log::add("Устройство " + TypeControlToStr(control->getType()) + " уже выключено. ");
    }
    else
    {
        control->off();                 // отключение

        delete state;                   // изменения состояния
        state = new OFFState();

        //Log::add("Изменено состояния " + TypeControlToStr(control->getType()) + " на OFF. ");
    }
}

void DeviceControl::setStatus(TypeStatus status)
{
    if (status == TypeStatus::ON)
        on();
    else if (status == TypeStatus::OFF)
        off();
    else
        return;
}

TypeControl DeviceControl::getType()
{
    return control->getType();
}

TypeStatus DeviceControl::getStatus()
{
    return state->get();
}

void DeviceControl::setWindowSetting(int minVal, int maxVal)
{
    _window->setValueOpen(maxVal);
    _window->setValueClose(minVal);
}

DeviceControl::~DeviceControl()
{
    delete control;
}

AdapterControlWindow* DeviceControl::_window = nullptr;


