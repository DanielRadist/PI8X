#include "SystemControl.h"
#include <iostream>
#include "Log.h"


void SystemControl::add(DeviceControl* Device)
{
	listDevice.push_back(Device);
}

DeviceControl* SystemControl::create(TypeControl type)
{
	return new DeviceControl(type);
}

void SystemControl::remove(DeviceControl* Device)
{
	listDevice.remove(Device);
}

DeviceControl* SystemControl::search(TypeControl typeDevice)
{
	for (auto it = listDevice.begin(); it != listDevice.end(); it++)
		if ((*it)->getType() == typeDevice)
			return (*it);
	return nullptr;
}


void SystemControl::solution(list<pair<TypeControl, TypeStatus>> solut)
{
	while (solut.size() != 0)
	{
		// Поиск контроллера 
		DeviceControl* select = search(solut.front().first);
		if (select == nullptr)
			Log::add("Error!. Не найден контроллер: " + TypeControlToStr(solut.front().first) + ". ");
		// Попытка измененить состояние
		select->setStatus(solut.front().second);

		solut.pop_front();
	}
}

void SystemControl::setWindowSetting(int minVal, int maxVal)
{
	DeviceControl::setWindowSetting(minVal, maxVal);
}
