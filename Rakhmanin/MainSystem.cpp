#include "MainSystem.h"
#include "Log.h"


MainSystem::MainSystem()
{
	Log::add("�������� ������ ���������� ��������... ");
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

	Log::add("�������� ������ ���������� �������� ���������. ");
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
		Log::add("Error! �������� �� �������! ");
		return;
	}
	if (strategy == nullptr)
	{
		Log::add("Error! ����� ������ �� ������! ");
		return;
	}

						
	
	// ��������� ���������� � ������� �� �����
	DataClimat climat = meteoS->getData();

	// ������ �� ������� ����� ��������� ����
	// ����� �� 30% (< 5 *C)
	// ����� �� 80% (>= 5 *C)
	if (climat.getData(TypeSensor::Temperature) < 5)
		sysCtrl->setWindowSetting(0, 30);
	else
		sysCtrl->setWindowSetting(0, 80);

	// ������ � ������� � �������
	DataClimat greenhouse = sysSens->getDataClimat();

	// ��������� ������� � ������������ �� ���������� (������� ������)
	list<pair<TypeControl, TypeStatus>> solut = strategy->solution(climat, greenhouse, culrure);

	// ���������� �������
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
	Log::add("���������� <����������> ����� ������. ");
}

list<pair<TypeControl, TypeStatus>> NormalStrategy::solution(DataClimat climat, DataClimat greenhouse, Culture* culture)
{
	list<pair<TypeControl, TypeStatus>> solut;

	// ����������� � ������� ���� �����������
	if (greenhouse.getData(TypeSensor::Temperature) < culture->getMin(TypeSensor::Temperature))
		solut.push_back(make_pair(TypeControl::Heater, TypeStatus::ON));
	else
		solut.push_back(make_pair(TypeControl::Heater, TypeStatus::OFF));

	// ����������� � ������� ���� ������������
	if (greenhouse.getData(TypeSensor::Temperature) > culture->getMax(TypeSensor::Temperature))
		solut.push_back(make_pair(TypeControl::Cooler, TypeStatus::ON));
	else
		solut.push_back(make_pair(TypeControl::Cooler, TypeStatus::OFF));

	// ��������� � ������� ���� �����������
	if (greenhouse.getData(TypeSensor::Humidity) < culture->getMin(TypeSensor::Humidity))
		solut.push_back(make_pair(TypeControl::Humidity, TypeStatus::ON));
	else
		solut.push_back(make_pair(TypeControl::Humidity, TypeStatus::OFF));

	// ��������� ����� � ������� ���� �����������
	if (greenhouse.getData(TypeSensor::SoilHumidity) < culture->getMin(TypeSensor::SoilHumidity))
		solut.push_back(make_pair(TypeControl::SoilHumidity, TypeStatus::ON));
	else
		solut.push_back(make_pair(TypeControl::SoilHumidity, TypeStatus::OFF));

	// ���������� ��2
	if (greenhouse.getData(TypeSensor::CO2) < culture->getMin(TypeSensor::CO2))
		solut.push_back(make_pair(TypeControl::CO2, TypeStatus::ON));
	else
		solut.push_back(make_pair(TypeControl::CO2, TypeStatus::OFF));

	// ������ ���� �� ��������
	if (greenhouse.getData(TypeSensor::Light) < culture->getMin(TypeSensor::Light))
		solut.push_back(make_pair(TypeControl::Light, TypeStatus::ON));
	else
		solut.push_back(make_pair(TypeControl::Light, TypeStatus::OFF));

	// ���� ������ ������� ��� ���� ���������, ����� ������, ����� ����������� ���� ���������
	solut.push_back(make_pair(TypeControl::Window, TypeStatus::OFF));

	return solut;
}


EcoStrategy::EcoStrategy()
{
	Log::add("���������� <���������> ����� ������. ");
}

list<pair<TypeControl, TypeStatus>> EcoStrategy::solution(DataClimat climat, DataClimat greenhouse, Culture* culture)
{
	list<pair<TypeControl, TypeStatus>> solut;

	TypeStatus win = TypeStatus::OFF;

	// ����������� ���� ������������
	if (greenhouse.getData(TypeSensor::Temperature) > culture->getMax(TypeSensor::Temperature))
	{
		// ���� �� ����� ���������� ��� � ������� - ��������� ����, ����� �����������
		if (climat.getData(TypeSensor::Temperature) < greenhouse.getData(TypeSensor::Temperature))
			win = TypeStatus::ON;
		else
			solut.push_back(make_pair(TypeControl::Cooler, TypeStatus::ON));
	}
	else
		solut.push_back(make_pair(TypeControl::Cooler, TypeStatus::OFF));
		
	// ����������� � ������� ���� �����������
	if (greenhouse.getData(TypeSensor::Temperature) < culture->getMin(TypeSensor::Temperature))
	{
		// ���� �� ����� ������ - ��������� ����, ����� ������ �����
		if (climat.getData(TypeSensor::Temperature) > greenhouse.getData(TypeSensor::Temperature))
			win = TypeStatus::ON;
		else
			solut.push_back(make_pair(TypeControl::Heater, TypeStatus::ON));
	}
	else
		solut.push_back(make_pair(TypeControl::Heater, TypeStatus::OFF));


	// ��������� � ������� �� ���������� � ������ ���������
	solut.push_back(make_pair(TypeControl::Humidity, TypeStatus::OFF));

	// ��������� ����� � ������� ���� �����������
	if (greenhouse.getData(TypeSensor::SoilHumidity) < culture->getMin(TypeSensor::SoilHumidity))
		solut.push_back(make_pair(TypeControl::SoilHumidity, TypeStatus::ON));
	else
		solut.push_back(make_pair(TypeControl::SoilHumidity, TypeStatus::OFF));

	// ���������� ��2 ���������� �����
	if (greenhouse.getData(TypeSensor::CO2) <= culture->getMin(TypeSensor::CO2)
		&& climat.getData(TypeSensor::CO2) > greenhouse.getData(TypeSensor::CO2))
		win = TypeStatus::ON;
		

	// ������ ���� �� �������� �� ���������� � ������ ���������
	solut.push_back(make_pair(TypeControl::Light, TypeStatus::OFF));

	// ������� �� ����
	solut.push_back(make_pair(TypeControl::Window, win));

	return solut;
}

