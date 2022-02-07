#include <iostream>
#include <string>

#include "DeviceControl.h"
#include "Control.h"
#include "Log.h"


ONState::ONState() {}

bool ONState::on()
{
    return false;       // ������ ��������, ��� ���������
}

bool ONState::off()
{
    return true;        // ����� ���������, ��� ���������
}

TypeStatus ONState::get()
{
    return TypeStatus::ON;
}


OFFState::OFFState() {}

bool OFFState::on()
{
    return true;        // ����� ��������, ��� ���������
}

bool OFFState::off()
{
    return false;       // ������ ����������, ��� ���������
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
        ControlWindow* window = new ControlWindow();            // ������ ������ ����������� ����
        _window = new AdapterControlWindow(window);             // ������� ������ ����������� ����
        this->control = _window;
        break;
    }


    default:
        this->control = nullptr;
        break;
    }

    state = new OFFState();                                     // ���������� ��������
}


void DeviceControl::on()
{
    if (state->get() == TypeStatus::ON)
    {
        //Log::add("���������� " + TypeControlToStr(control->getType()) + " ��� ON. ");
    }
    else
    {
        control->on();                  // ���������

        delete state;                   // ��������� ���������
        state = new ONState();

        //Log::add("�������� ��������� " + TypeControlToStr(control->getType()) + " �� ON. ");
    }
}

void DeviceControl::off()
{
    if (state->get() == TypeStatus::OFF)
    {
        //Log::add("���������� " + TypeControlToStr(control->getType()) + " ��� ���������. ");
    }
    else
    {
        control->off();                 // ����������

        delete state;                   // ��������� ���������
        state = new OFFState();

        //Log::add("�������� ��������� " + TypeControlToStr(control->getType()) + " �� OFF. ");
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


