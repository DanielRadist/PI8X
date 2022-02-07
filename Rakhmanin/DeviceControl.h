#pragma once

#include "Control.h"
#include "TypeStatus.h"

/// <summary>
/// Состояния устроств которые регулируют климат в теплицы: обогреватель, кондиционеры, кран полива и т.д.
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
/// Делегирование DeviceControl безопасно управляет объектами IControl
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

