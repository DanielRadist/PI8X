#pragma once
#include "DeviceControl.h"
#include <list>

class SystemControl
{
public:
	/// <summary>
	/// ���������� ���������� � �������
	/// </summary>
	/// <param name="Device"></param>
	void add(DeviceControl* Device);

	/// <summary>
	/// �������� �����������
	/// </summary>
	/// <param name="type"></param>
	/// <returns></returns>
	DeviceControl* create(TypeControl type);

	/// <summary>
	/// �������� ��������� �� �������
	/// </summary>
	/// <param name="Device"></param>
	void remove(DeviceControl* Device);

	/// <summary>
	/// ����� ����������
	/// </summary>
	/// <param name="typeDevice"></param>
	/// <returns></returns>
	DeviceControl* search(TypeControl typeDevice);

	/// <summary>
	/// ��������� ������� �� ������������� ������� �� ������ ���������
	/// </summary>
	/// <param name="solut">�������</param>
	void solution(list<pair<TypeControl, TypeStatus>> solut);

	void setWindowSetting(int minVal, int maxVal);

private:
	std::list<DeviceControl*> listDevice;
};

