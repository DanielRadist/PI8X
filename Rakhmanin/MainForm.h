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
	/// ������ ��� MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	private:
		/// <summary>
		/// ������ �������
		/// </summary>
		std::map<
			std::string,						// ��������
			Culture*>							// ��������� �� ������
			* cultures;

		Culture* selectCulture = nullptr;		// ��������� ��������
		IStrategy* selectStrategy = nullptr;	// �������� ����� ������

		// ������ � ��������, ����� ������������� ������� � ����������
		// -- ����
		// -- -- TypeSensor - ��� �������
		// -- -- bool: true - � ������������, false - � �������
		// -- �� ����: DataSource*: ����� ��� �������� ������
		std::map<pair<TypeSensor, bool>, DataSource*>* streamToSensor;

		MainSystem* centerClimat;				// ����� ���������� ��������

	public:
		MainForm(void)
		{
			// ��������� ��������
			Log::add("�������� ����������... ");
			InitializeComponent();
			logUpdate();


			loadGreenhouse();
			loadCulture();

			// �������� -> comboBox
			for (auto it = cultures->begin(); it != cultures->end(); it++)
				comboBox�ulture->Items->Add(toClrString(it->first));

			logUpdate();

			
			Log::add("WARNING. �������� ����� ������. ");
			logUpdate();
		}

	protected:

		// �������� �������
		void loadGreenhouse()
		{
			Log::add("������������� �������... ");
			logUpdate();

			centerClimat = new MainSystem();
			logUpdate();

			// ����������� Sensor's � ��������� ��������� ����� DataSource
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

			Log::add("������������� ������� ��������� �������. ");
			logUpdate();
		}

		/// <summary>
		/// �������� �� ����� ������ ������� � comboBox � �� ������������� � ������ �ultures
		/// </summary>
		void loadCulture()
		{
			Log::add("�������� �������... ");
			cultures = new std::map<std::string, Culture*>();

			StreamReader sr("Cultures.txt");
			String^ line;
			line = sr.ReadLine();
			while (line != nullptr)
			{
				//��������
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
						Log::add("Error: �������� ������� ��������� � �������! ");
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
			Log::add("�������� ������� ��������� �������. ");
		}

		/// <summary>
		/// ��������� ���������, ���� ����������� ��������� �������
		/// </summary>
		void goToSolution()
		{
			// ������� ������ � ��������� � �����
			// ������� �������:
			streamToSensor->at({ TypeSensor::Temperature, false })->setData(Convert::ToInt32(numericGHTemperature->Value));
			streamToSensor->at({ TypeSensor::Light, false })->setData(Convert::ToInt32(numericGHLight->Value));
			streamToSensor->at({ TypeSensor::CO2, false })->setData(Convert::ToInt32(numericGHco2->Value));
			streamToSensor->at({ TypeSensor::Humidity, false })->setData(Convert::ToInt32(numericGHHumidity->Value));
			streamToSensor->at({ TypeSensor::SoilHumidity, false })->setData(Convert::ToInt32(numericGHSoilHumidity->Value));
			// ������� ������������:
			streamToSensor->at({ TypeSensor::Temperature, true })->setData(Convert::ToInt32(numericMSTemperature->Value));
			streamToSensor->at({ TypeSensor::Humidity, true })->setData(Convert::ToInt32(numericMSHumidity->Value));
			streamToSensor->at({ TypeSensor::CO2, true })->setData(Convert::ToInt32(numericMSco2->Value));


			if (selectCulture == nullptr)
				Log::add("WARNING! �������� ��������! ");
			if (selectStrategy == nullptr)
				Log::add("WARNING! �������� ����� ������! ");
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
		/// ���������� � textBoxLog ������
		/// </summary>
		/// <param name="info">������ ��� ������</param>
		void logAdd(std::string info)
		{
			info += "\r\n";
			String^ t = gcnew String(info.c_str());
			textBoxLog->AppendText(t);
			textBoxLog->ScrollToCaret();
		}

		/// <summary>
		/// ������� textBoxLog
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

		
	private: System::Windows::Forms::ComboBox^ comboBox�ulture;
	private: System::Windows::Forms::TextBox^ textBox�ulture;

	private:
		/// <summary>
		/// ������������ ���������� ������������.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// ��������� ����� ��� ��������� ������������ � �� ��������� 
		/// ���������� ����� ������ � ������� ��������� ����.
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
	private: System::Void comboBox�ulture_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) 
	{
		std::string selectStr = toStdString(comboBox�ulture->SelectedItem->ToString());
		selectCulture = cultures->at(selectStr);
		textBox�ulture->Clear();
		
		std::string buf = "��������� ������: \r\n";

		buf += "������. : " + std::to_string(selectCulture->getMin(TypeSensor::Temperature)) + " : " + std::to_string(selectCulture->getMax(TypeSensor::Temperature)) + " *C" + "\r\n";
		buf += "�����.  : " + std::to_string(selectCulture->getMin(TypeSensor::Light)) + " : " + std::to_string(selectCulture->getMax(TypeSensor::Light)) + " lm" + "\r\n";
		buf += "��. CO2 : " + std::to_string(selectCulture->getMin(TypeSensor::CO2)) + " : " + std::to_string(selectCulture->getMax(TypeSensor::CO2)) + " %" + "\r\n";
		buf += "���. ��.: " + std::to_string(selectCulture->getMin(TypeSensor::Humidity)) + " : " + std::to_string(selectCulture->getMax(TypeSensor::Humidity)) + " %" + "\r\n";
		buf += "���. ��.: " + std::to_string(selectCulture->getMin(TypeSensor::SoilHumidity)) + " : " + std::to_string(selectCulture->getMax(TypeSensor::SoilHumidity)) + " %";
	
		textBox�ulture->Text = toClrString(buf);

		Log::add("�������� ��������! �������� ��: " + selectCulture->getName() + ". ");
		logUpdate();
		goToSolution();
	}

	// ���������� ������� �������
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
	// ���������� ������� � ������������
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
