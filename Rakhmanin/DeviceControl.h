#pragma once

#include "Control.h"
#include "TypeStatus.h"

/// <summary>
/// ��������� �������� ������� ���������� ������ � �������: ������������, ������������, ���� ������ � �.�.
/// </summary>
class IState
{
public:
    virtual bool on() = 0;
    virtual bool off() = 0;
    virtual TypeStatus get() = 0;
};

class ONState : public IState
{
public:
    ONState();

    bool on();
    bool off();
    TypeStatus get();

private:
    IControl* control;
};

class OFFState : public IState
{
public:
    OFFState();

    bool on();
    bool off();
    TypeStatus get();

private:
    IControl* control;
};

/// <summary>
/// ������������� DeviceControl ��������� ��������� ��������� IControl
/// </summary>
class DeviceControl
{
public:

    DeviceControl(TypeControl type);

private:

    void on();

    void off();

public:

    void setStatus(TypeStatus status);

    TypeControl getType();

    TypeStatus getStatus();

    static void setWindowSetting(int minVal, int maxVal);

    ~DeviceControl();

private:
    IControl* control;
    IState* state;

    static AdapterControlWindow* _window;
};

