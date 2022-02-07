#include "MainSystem.h"
#include "Log.h"


MainSystem::MainSystem()
{
	Log::add("Создания центра управления климатом... ");
	this->strategy = nullptr;
	this->meteoS = new MeteoStation();
	this->culrure = nullptr;

			//SystemDirector* dir = SystemDirector::Instance();
			//ISystemBuilder* builder = new SystemSensorBuilder();
			//dir->makeSystemSensor(builder);

	SystemDirector* dir = SystemDirector::Instance();
	SystemSensorBuilder* builderSensors = new SystemSensorBuilder();
	dir->makeSystemSensor(builderSensors);
	
	this->sysSens = builderSensors->getResult();
	delete builderSensors;

	dir = SystemDirector::Instance();
	SystemControlBuilder* builderControl = new SystemControlBuilder();
	dir->makeSystemControl(builderControl);
	
	this->sysCtrl = builderControl->getResult();
	delete builderControl;

	Log::add("Создания центра управления климатом завершено. ");
}

void MainSystem::setStrategy(IStrategy* strategy)
{
	this->strategy = strategy;
}

void MainSystem::setCulture(Culture* culture)
{
	this->culrure = culture;
}

void MainSystem::solutionStrategy()
{
	if (culrure == nullptr)
	{
		Log::add("Error! Культура не выбрана! ");
		return;
	}
	if (strategy == nullptr)
	{
		Log::add("Error! Режим работы не выбран! ");
		return;
	}

						
	
	// Получение информации о климате на улице
	DataClimat climat = meteoS->getData();

	// Решаем на сколько можно открывать окно
	// Зимой на 30% (< 5 *C)
	// Летом на 80% (>= 5 *C)
	if (climat.getData(TypeSensor::Temperature) < 5)
		sysCtrl->setWindowSetting(0, 30);
	else
		sysCtrl->setWindowSetting(0, 80);

	// данные о климате в теплице
	DataClimat greenhouse = sysSens->getDataClimat();

	// Получение решения в соответствии со стратегией (режимом работы)
	list<pair<TypeControl, TypeStatus>> solut = strategy->solution(climat, greenhouse, culrure);

	// Выполнение решения
	sysCtrl->solution(solut);
}

list<Sensor*> MainSystem::getListSensorGH()
{
	return sysSens->getSensors();
}

list<Sensor*> MainSystem::getListSensorMS()
{
	return meteoS->getSensors();
}



NormalStrategy::NormalStrategy()
{
	Log::add("Установлен <Нормальный> режим работы. ");
}

list<pair<TypeControl, TypeStatus>> NormalStrategy::solution(DataClimat climat, DataClimat greenhouse, Culture* culture)
{
	list<pair<TypeControl, TypeStatus>> solut;

	// Температура в теплице ниже минимальной
	if (greenhouse.getData(TypeSensor::Temperature) < culture->getMin(TypeSensor::Temperature))
		solut.push_back(make_pair(TypeControl::Heater, TypeStatus::ON));
	else
		solut.push_back(make_pair(TypeControl::Heater, TypeStatus::OFF));

	// Температура в теплице выше максимальной
	if (greenhouse.getData(TypeSensor::Temperature) > culture->getMax(TypeSensor::Temperature))
		solut.push_back(make_pair(TypeControl::Cooler, TypeStatus::ON));
	else
		solut.push_back(make_pair(TypeControl::Cooler, TypeStatus::OFF));

	// Влажность в теплице ниже минимальной
	if (greenhouse.getData(TypeSensor::Humidity) < culture->getMin(TypeSensor::Humidity))
		solut.push_back(make_pair(TypeControl::Humidity, TypeStatus::ON));
	else
		solut.push_back(make_pair(TypeControl::Humidity, TypeStatus::OFF));

	// Влажность почвы в теплице ниже минимальной
	if (greenhouse.getData(TypeSensor::SoilHumidity) < culture->getMin(TypeSensor::SoilHumidity))
		solut.push_back(make_pair(TypeControl::SoilHumidity, TypeStatus::ON));
	else
		solut.push_back(make_pair(TypeControl::SoilHumidity, TypeStatus::OFF));

	// Недостаток СО2
	if (greenhouse.getData(TypeSensor::CO2) < culture->getMin(TypeSensor::CO2))
		solut.push_back(make_pair(TypeControl::CO2, TypeStatus::ON));
	else
		solut.push_back(make_pair(TypeControl::CO2, TypeStatus::OFF));

	// Солнце село за горизонт
	if (greenhouse.getData(TypeSensor::Light) < culture->getMin(TypeSensor::Light))
		solut.push_back(make_pair(TypeControl::Light, TypeStatus::ON));
	else
		solut.push_back(make_pair(TypeControl::Light, TypeStatus::OFF));

	// Окно всегда загрыто при этой стратегии, кроме случая, когда температура выше макисмума
	solut.push_back(make_pair(TypeControl::Window, TypeStatus::OFF));

	return solut;
}


EcoStrategy::EcoStrategy()
{
	Log::add("Установлен <Экономный> режим работы. ");
}

list<pair<TypeControl, TypeStatus>> EcoStrategy::solution(DataClimat climat, DataClimat greenhouse, Culture* culture)
{
	list<pair<TypeControl, TypeStatus>> solut;

	TypeStatus win = TypeStatus::OFF;

	// Температура выше максимальной
	if (greenhouse.getData(TypeSensor::Temperature) > culture->getMax(TypeSensor::Temperature))
	{
		// если на улице прохладнее чем в теплице - открываем окно, иначе кондиционер
		if (climat.getData(TypeSensor::Temperature) < greenhouse.getData(TypeSensor::Temperature))
			win = TypeStatus::ON;
		else
			solut.push_back(make_pair(TypeControl::Cooler, TypeStatus::ON));
	}
	else
		solut.push_back(make_pair(TypeControl::Cooler, TypeStatus::OFF));
		
	// Температура в теплице ниже минимальной
	if (greenhouse.getData(TypeSensor::Temperature) < culture->getMin(TypeSensor::Temperature))
	{
		// если на улице теплее - открываем окно, иначе только печка
		if (climat.getData(TypeSensor::Temperature) > greenhouse.getData(TypeSensor::Temperature))
			win = TypeStatus::ON;
		else
			solut.push_back(make_pair(TypeControl::Heater, TypeStatus::ON));
	}
	else
		solut.push_back(make_pair(TypeControl::Heater, TypeStatus::OFF));


	// Влажность в теплице не регулируем в данной стратегии
	solut.push_back(make_pair(TypeControl::Humidity, TypeStatus::OFF));

	// Влажность почвы в теплице ниже минимальной
	if (greenhouse.getData(TypeSensor::SoilHumidity) < culture->getMin(TypeSensor::SoilHumidity))
		solut.push_back(make_pair(TypeControl::SoilHumidity, TypeStatus::ON));
	else
		solut.push_back(make_pair(TypeControl::SoilHumidity, TypeStatus::OFF));

	// Недостаток СО2 регулируем окном
	if (greenhouse.getData(TypeSensor::CO2) <= culture->getMin(TypeSensor::CO2)
		&& climat.getData(TypeSensor::CO2) > greenhouse.getData(TypeSensor::CO2))
		win = TypeStatus::ON;
		

	// Солнце село за горизонт не регулируем в данной стратегии
	solut.push_back(make_pair(TypeControl::Light, TypeStatus::OFF));

	// Решение по окну
	solut.push_back(make_pair(TypeControl::Window, win));

	return solut;
}

