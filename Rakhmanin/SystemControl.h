#pragma once
#include "DeviceControl.h"
#include <list>

class SystemControl
{
public:
	/// <summary>
	/// Добавление контролера в систему
	/// </summary>
	/// <param name="Device"></param>
	void add(DeviceControl* Device);

	/// <summary>
	/// Создание контроллера
	/// </summary>
	/// <param name="type"></param>
	/// <returns></returns>
	DeviceControl* create(TypeControl type);

	/// <summary>
	/// Удаление контолера из системы
	/// </summary>
	/// <param name="Device"></param>
	void remove(DeviceControl* Device);

	/// <summary>
	/// Поиск контролера
	/// </summary>
	/// <param name="typeDevice"></param>
	/// <returns></returns>
	DeviceControl* search(TypeControl typeDevice);

	/// <summary>
	/// Выполнить решение по регулированию климата на основе стратегии
	/// </summary>
	/// <param name="solut">Решение</param>
	void solution(list<pair<TypeControl, TypeStatus>> solut);

	void setWindowSetting(int minVal, int maxVal);

private:
	std::list<DeviceControl*> listDevice;
};

