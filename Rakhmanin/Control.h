#pragma once

#include "TypeControl.h"

using namespace std;

class IControl
{
protected:
    TypeControl type;

public:

    IControl(TypeControl type);

    virtual void on() = 0;      // ���������
    virtual void off() = 0;     // ����������

    TypeControl getType();
};

/// <summary>
/// ������������
/// </summary>
class ControlHeater : public IControl
{
public:
    ControlHeater();

    void on();
    void off();
};

/// <summary>
/// �����������
/// </summary>
class ControlCooler : public IControl
{
public:
    ControlCooler();

    void on();
    void off();
};

/// <summary>
/// ������������� ����
/// </summary>
class ControlLight : public IControl
{
public:
    ControlLight();

    void on();
    void off();
};

/// <summary>
/// ���� �������
/// </summary>
class ControlWindow
{
public:
    ControlWindow();

    string openness(int value);
};

/// <summary>
/// ������ ���� �������
/// </summary>
class AdapterControlWindow : public IControl
{
protected:
    int valueOpen;
    int valueClose;

    ControlWindow* window;

public:
    AdapterControlWindow(ControlWindow* window);

    void on();
    void off();

    void setValueOpen(int value);
    void setValueClose(int value);
};

/// <summary>
/// �����������
/// </summary>
class ControlHumidity : public IControl
{
public:
    ControlHumidity();

    void on();
    void off();
};

/// <summary>
/// ���� ������
/// </summary>
class ControlSoilHumidity : public IControl
{
public:
    ControlSoilHumidity();

    void on();
    void off();
};

/// <summary>
/// ���� ������ ��2
/// </summary>
class ControlCO2 : public IControl
{
public:
    ControlCO2();

    void on();
    void off();
};



