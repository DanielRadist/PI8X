#pragma once
#include <utility>
#include <list>
#include <string>
#include <sstream>

#include "Log.h"
#include "Culture.h"

#include "MainSystem.h"
#include "DataSource.h"


namespace Greenhouse 
{
	using namespace System;
	using namespace System::IO;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;


	/// <summary>
	/// Сводка для MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	private:
		/// <summary>
		/// Список культур
		/// </summary>
		std::map<
			std::string,						// название
			Culture*>							// указатель на объект
			* cultures;

		Culture* selectCulture = nullptr;		// Выбранная культура
		IStrategy* selectStrategy = nullptr;	// Выбраный режим работы

		// Доступ к сенсором, чтобы устанавливать значени с интерфейса
		// -- Ключ
		// -- -- TypeSensor - тип датчика
		// -- -- bool: true - с метеостанции, false - с теплицы
		// -- Не ключ: DataSource*: поток для передачи данных
		std::map<pair<TypeSensor, bool>, DataSource*>* streamToSensor;

		MainSystem* centerClimat;				// Центр управления климатом

	public:
		MainForm(void)
		{
			// Загружаем интерфес
			Log::add("Загрузка интерфейса... ");
			InitializeComponent();
			logUpdate();


			loadGreenhouse();
			loadCulture();

			// культуры -> comboBox
			for (auto it = cultures->begin(); it != cultures->end(); it++)
				comboBoxСulture->Items->Add(toClrString(it->first));

			logUpdate();

			
			Log::add("WARNING. Выберети режим работы. ");
			logUpdate();
		}

	protected:

		// создание теплицы
		void loadGreenhouse()
		{
			Log::add("Инициализация системы... ");
			logUpdate();

			centerClimat = new MainSystem();
			logUpdate();

			// Подключение Sensor's к интерфесу программы через DataSource
			list<Sensor*> sensorsGreenHouse = centerClimat->getListSensorGH();
			list<Sensor*> sensorsMeteoStation = centerClimat->getListSensorMS();
			streamToSensor = new std::map<pair<TypeSensor, bool>, DataSource*>();

			for (auto it = sensorsGreenHouse.begin(); it != sensorsGreenHouse.end(); it++)
				streamToSensor->insert(
					{
						{(*it)->getType(), false},
						new DataSource(*it)
					}
			);
			for (auto it = sensorsMeteoStation.begin(); it != sensorsMeteoStation.end(); it++)
				streamToSensor->insert(
					{
						{(*it)->getType(), true},
						new DataSource(*it)
					}
			);

			Log::add("Инициализация системы выполнена успешно. ");
			logUpdate();
		}

		/// <summary>
		/// Загрузка из файла списка культур в comboBox и их характеристик в список сultures
		/// </summary>
		void loadCulture()
		{
			Log::add("Загрузка культур... ");
			cultures = new std::map<std::string, Culture*>();

			StreamReader sr("Cultures.txt");
			String^ line;
			line = sr.ReadLine();
			while (line != nullptr)
			{
				//Название
				std::string bufName = toStdString(line);

				DataClimat* minData = new DataClimat();
				DataClimat* maxData = new DataClimat();

				line = sr.ReadLine();
				while (line != L"#")
				{
					std::string tmp = toStdString(line);
					std::stringstream ss(tmp);

					

					std::string namePar, minPar, maxPar;
					ss >> namePar;
					ss >> minPar;
					ss >> maxPar;

					if (namePar == "T")
					{
						minData->setData(TypeSensor::Temperature, std::stoi(minPar));
						maxData->setData(TypeSensor::Temperature, std::stoi(maxPar));
					}
					else if (namePar == "L")
					{
						minData->setData(TypeSensor::Light, std::stoi(minPar));
						maxData->setData(TypeSensor::Light, std::stoi(maxPar));
					}
					else if (namePar == "C")
					{
						minData->setData(TypeSensor::CO2, std::stoi(minPar));
						maxData->setData(TypeSensor::CO2, std::stoi(maxPar));
					}
					else if (namePar == "H")
					{
						minData->setData(TypeSensor::Humidity, std::stoi(minPar));
						maxData->setData(TypeSensor::Humidity, std::stoi(maxPar));
					}
					else if (namePar == "S")
					{
						minData->setData(TypeSensor::SoilHumidity, std::stoi(minPar));
						maxData->setData(TypeSensor::SoilHumidity, std::stoi(maxPar));
					}
					else
					{
						Log::add("Error: Загрузка культур выполнена с ошибкой! ");
						return;
					}

					line = sr.ReadLine();
				}

				Culture* cultTmp = new Culture(bufName, minData, maxData);

				cultures->insert({ bufName, cultTmp });

				delete minData;
				delete maxData;
				line = sr.ReadLine();
			}
			sr.Close();
			Log::add("Загрузка культур выполнена успешно. ");
		}

		/// <summary>
		/// Произошли изменения, пора пересчитать параметры климата
		/// </summary>
		void goToSolution()
		{
			// собрать данные и отправить в поток
			// Датчики теплицы:
			streamToSensor->at({ TypeSensor::Temperature, false })->setData(Convert::ToInt32(numericGHTemperature->Value));
			streamToSensor->at({ TypeSensor::Light, false })->setData(Convert::ToInt32(numericGHLight->Value));
			streamToSensor->at({ TypeSensor::CO2, false })->setData(Convert::ToInt32(numericGHco2->Value));
			streamToSensor->at({ TypeSensor::Humidity, false })->setData(Convert::ToInt32(numericGHHumidity->Value));
			streamToSensor->at({ TypeSensor::SoilHumidity, false })->setData(Convert::ToInt32(numericGHSoilHumidity->Value));
			// Датчики метеостанции:
			streamToSensor->at({ TypeSensor::Temperature, true })->setData(Convert::ToInt32(numericMSTemperature->Value));
			streamToSensor->at({ TypeSensor::Humidity, true })->setData(Convert::ToInt32(numericMSHumidity->Value));
			streamToSensor->at({ TypeSensor::CO2, true })->setData(Convert::ToInt32(numericMSco2->Value));


			if (selectCulture == nullptr)
				Log::add("WARNING! Выберите культуру! ");
			if (selectStrategy == nullptr)
				Log::add("WARNING! Выберите режим работы! ");
			if (selectStrategy != nullptr && selectCulture != nullptr)
			{
				centerClimat->setCulture(selectCulture);
				centerClimat->setStrategy(selectStrategy);
				logUpdate();
				centerClimat->solutionStrategy();
				logUpdate();
			}
			logUpdate();
		}

		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}

	public:

		
		void logUpdate()
		{
			while (Log::size() != 0)
			{
				logAdd(Log::pop());
			}
		}

		/// <summary>
		/// Добавление в textBoxLog строки
		/// </summary>
		/// <param name="info">данные для вывода</param>
		void logAdd(std::string info)
		{
			info += "\r\n";
			String^ t = gcnew String(info.c_str());
			textBoxLog->AppendText(t);
			textBoxLog->ScrollToCaret();
		}

		/// <summary>
		/// Очистка textBoxLog
		/// </summary>
		void logClear()
		{
			textBoxLog->Clear();
		}

		std::string toStdString(String^ str)
		{
			std::string ret = "";
			for (int i = 0; i < str->Length; i++)
				ret += (char)str[i];
			return ret;
		}

		String^ toClrString(std::string str)
		{
			String^ t = gcnew String(str.c_str());
			return t;
		}

	

	private: System::Windows::Forms::GroupBox^ groupBoxMeteoStation;
	private: System::Windows::Forms::GroupBox^ groupBoxGreenHouse;

	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::Label^ label10;

	private: System::Windows::Forms::Label^ label6;

	private: System::Windows::Forms::NumericUpDown^ numericGHLight;
	private: System::Windows::Forms::NumericUpDown^ numericGHco2;
	private: System::Windows::Forms::NumericUpDown^ numericGHHumidity;
	private: System::Windows::Forms::NumericUpDown^ numericGHSoilHumidity;
	private: System::Windows::Forms::NumericUpDown^ numericGHTemperature;

	private: System::Windows::Forms::NumericUpDown^ numericMSco2;
	private: System::Windows::Forms::NumericUpDown^ numericMSHumidity;
	private: System::Windows::Forms::NumericUpDown^ numericMSTemperature;

	private: System::Windows::Forms::TextBox^ textBoxLog;
	private: System::Windows::Forms::Label^ label11;

	private: System::Windows::Forms::GroupBox^ groupBoxStrategy;
	private: System::Windows::Forms::RadioButton^ radioButtonEcoStrategy;
	private: System::Windows::Forms::RadioButton^ radioButtonNormalStrategy;





	protected:

	protected:


	private:

		
	private: System::Windows::Forms::ComboBox^ comboBoxСulture;
	private: System::Windows::Forms::TextBox^ textBoxСulture;

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void);
#pragma endregion

	private: System::Void radioButtonNormalStrategy_CheckedChanged(System::Object^ sender, System::EventArgs^ e) 
	{
		if (radioButtonNormalStrategy->Checked == true)
		{
			selectStrategy = new NormalStrategy();
			logUpdate();
			goToSolution();
		}
	}
	private: System::Void radioButtonEcoStrategy_CheckedChanged(System::Object^ sender, System::EventArgs^ e) 
	{
		if (radioButtonEcoStrategy->Checked == true)
		{
			selectStrategy = new EcoStrategy();
			logUpdate();
			goToSolution();
		}
	}
	private: System::Void comboBoxСulture_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) 
	{
		std::string selectStr = toStdString(comboBoxСulture->SelectedItem->ToString());
		selectCulture = cultures->at(selectStr);
		textBoxСulture->Clear();
		
		std::string buf = "Требуемый климат: \r\n";

		buf += "Темпер. : " + std::to_string(selectCulture->getMin(TypeSensor::Temperature)) + " : " + std::to_string(selectCulture->getMax(TypeSensor::Temperature)) + " *C" + "\r\n";
		buf += "Освещ.  : " + std::to_string(selectCulture->getMin(TypeSensor::Light)) + " : " + std::to_string(selectCulture->getMax(TypeSensor::Light)) + " lm" + "\r\n";
		buf += "Ур. CO2 : " + std::to_string(selectCulture->getMin(TypeSensor::CO2)) + " : " + std::to_string(selectCulture->getMax(TypeSensor::CO2)) + " %" + "\r\n";
		buf += "Воз. Вл.: " + std::to_string(selectCulture->getMin(TypeSensor::Humidity)) + " : " + std::to_string(selectCulture->getMax(TypeSensor::Humidity)) + " %" + "\r\n";
		buf += "Поч. Вл.: " + std::to_string(selectCulture->getMin(TypeSensor::SoilHumidity)) + " : " + std::to_string(selectCulture->getMax(TypeSensor::SoilHumidity)) + " %";
	
		textBoxСulture->Text = toClrString(buf);

		Log::add("ИЗМЕНЕНА КУЛЬТУРА! Изменена на: " + selectCulture->getName() + ". ");
		logUpdate();
		goToSolution();
	}

	// Показатели климата теплицы
	private: System::Void numericGHTemperature_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		goToSolution();
	}
	private: System::Void numericGHSoilHumidity_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		goToSolution();
	}
	private: System::Void numericGHHumidity_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		goToSolution();
	}
	private: System::Void numericGHco2_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		goToSolution();
	}
	private: System::Void numericGHLight_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		goToSolution();
	}
	// Покахатели климата с метеостанции
	private: System::Void numericMSTemperature_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		goToSolution();
	}
	private: System::Void numericMSHumidity_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		goToSolution();
	}
	private: System::Void numericMSco2_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		goToSolution();
	}
private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
	textBoxLog->ScrollToCaret();
}
private: System::Void MainForm_Shown(System::Object^ sender, System::EventArgs^ e) {
	textBoxLog->ScrollToCaret();
}
};
}
