#include "MainForm.h"

void Greenhouse::MainForm::InitializeComponent(void)
{
    this->groupBoxGreenHouse = (gcnew System::Windows::Forms::GroupBox());
    this->numericGHLight = (gcnew System::Windows::Forms::NumericUpDown());
    this->numericGHco2 = (gcnew System::Windows::Forms::NumericUpDown());
    this->numericGHHumidity = (gcnew System::Windows::Forms::NumericUpDown());
    this->numericGHSoilHumidity = (gcnew System::Windows::Forms::NumericUpDown());
    this->numericGHTemperature = (gcnew System::Windows::Forms::NumericUpDown());
    this->label5 = (gcnew System::Windows::Forms::Label());
    this->label4 = (gcnew System::Windows::Forms::Label());
    this->label3 = (gcnew System::Windows::Forms::Label());
    this->label2 = (gcnew System::Windows::Forms::Label());
    this->label1 = (gcnew System::Windows::Forms::Label());
    this->groupBoxMeteoStation = (gcnew System::Windows::Forms::GroupBox());
    this->numericMSco2 = (gcnew System::Windows::Forms::NumericUpDown());
    this->label7 = (gcnew System::Windows::Forms::Label());
    this->numericMSHumidity = (gcnew System::Windows::Forms::NumericUpDown());
    this->label9 = (gcnew System::Windows::Forms::Label());
    this->numericMSTemperature = (gcnew System::Windows::Forms::NumericUpDown());
    this->label10 = (gcnew System::Windows::Forms::Label());
    this->textBoxLog = (gcnew System::Windows::Forms::TextBox());
    this->label11 = (gcnew System::Windows::Forms::Label());
    this->groupBoxStrategy = (gcnew System::Windows::Forms::GroupBox());
    this->radioButtonEcoStrategy = (gcnew System::Windows::Forms::RadioButton());
    this->radioButtonNormalStrategy = (gcnew System::Windows::Forms::RadioButton());
    this->comboBoxÑulture = (gcnew System::Windows::Forms::ComboBox());
    this->textBoxÑulture = (gcnew System::Windows::Forms::TextBox());
    this->label6 = (gcnew System::Windows::Forms::Label());
    this->groupBoxGreenHouse->SuspendLayout();
    (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericGHLight))->BeginInit();
    (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericGHco2))->BeginInit();
    (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericGHHumidity))->BeginInit();
    (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericGHSoilHumidity))->BeginInit();
    (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericGHTemperature))->BeginInit();
    this->groupBoxMeteoStation->SuspendLayout();
    (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericMSco2))->BeginInit();
    (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericMSHumidity))->BeginInit();
    (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericMSTemperature))->BeginInit();
    this->groupBoxStrategy->SuspendLayout();
    this->SuspendLayout();
    // 
    // groupBoxGreenHouse
    // 
    this->groupBoxGreenHouse->Controls->Add(this->numericGHLight);
    this->groupBoxGreenHouse->Controls->Add(this->numericGHco2);
    this->groupBoxGreenHouse->Controls->Add(this->numericGHHumidity);
    this->groupBoxGreenHouse->Controls->Add(this->numericGHSoilHumidity);
    this->groupBoxGreenHouse->Controls->Add(this->numericGHTemperature);
    this->groupBoxGreenHouse->Controls->Add(this->label5);
    this->groupBoxGreenHouse->Controls->Add(this->label4);
    this->groupBoxGreenHouse->Controls->Add(this->label3);
    this->groupBoxGreenHouse->Controls->Add(this->label2);
    this->groupBoxGreenHouse->Controls->Add(this->label1);
    this->groupBoxGreenHouse->Location = System::Drawing::Point(12, 12);
    this->groupBoxGreenHouse->Name = L"groupBoxGreenHouse";
    this->groupBoxGreenHouse->Size = System::Drawing::Size(173, 148);
    this->groupBoxGreenHouse->TabIndex = 1;
    this->groupBoxGreenHouse->TabStop = false;
    this->groupBoxGreenHouse->Text = L"Òåïëèöà";
    // 
    // numericGHLight
    // 
    this->numericGHLight->Location = System::Drawing::Point(107, 118);
    this->numericGHLight->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
    this->numericGHLight->Name = L"numericGHLight";
    this->numericGHLight->Size = System::Drawing::Size(56, 20);
    this->numericGHLight->TabIndex = 10;
    this->numericGHLight->ValueChanged += gcnew System::EventHandler(this, &MainForm::numericGHLight_ValueChanged);
    // 
    // numericGHco2
    // 
    this->numericGHco2->Location = System::Drawing::Point(107, 92);
    this->numericGHco2->Name = L"numericGHco2";
    this->numericGHco2->Size = System::Drawing::Size(56, 20);
    this->numericGHco2->TabIndex = 9;
    this->numericGHco2->ValueChanged += gcnew System::EventHandler(this, &MainForm::numericGHco2_ValueChanged);
    // 
    // numericGHHumidity
    // 
    this->numericGHHumidity->Location = System::Drawing::Point(107, 66);
    this->numericGHHumidity->Name = L"numericGHHumidity";
    this->numericGHHumidity->Size = System::Drawing::Size(56, 20);
    this->numericGHHumidity->TabIndex = 8;
    this->numericGHHumidity->ValueChanged += gcnew System::EventHandler(this, &MainForm::numericGHHumidity_ValueChanged);
    // 
    // numericGHSoilHumidity
    // 
    this->numericGHSoilHumidity->Location = System::Drawing::Point(107, 40);
    this->numericGHSoilHumidity->Name = L"numericGHSoilHumidity";
    this->numericGHSoilHumidity->Size = System::Drawing::Size(56, 20);
    this->numericGHSoilHumidity->TabIndex = 7;
    this->numericGHSoilHumidity->ValueChanged += gcnew System::EventHandler(this, &MainForm::numericGHSoilHumidity_ValueChanged);
    // 
    // numericGHTemperature
    // 
    this->numericGHTemperature->Location = System::Drawing::Point(107, 14);
    this->numericGHTemperature->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
    this->numericGHTemperature->Name = L"numericGHTemperature";
    this->numericGHTemperature->Size = System::Drawing::Size(56, 20);
    this->numericGHTemperature->TabIndex = 3;
    this->numericGHTemperature->ValueChanged += gcnew System::EventHandler(this, &MainForm::numericGHTemperature_ValueChanged);
    // 
    // label5
    // 
    this->label5->AutoSize = true;
    this->label5->Location = System::Drawing::Point(18, 120);
    this->label5->Name = L"label5";
    this->label5->Size = System::Drawing::Size(83, 13);
    this->label5->TabIndex = 6;
    this->label5->Text = L"Îñâåùåííîñòü";
    // 
    // label4
    // 
    this->label4->AutoSize = true;
    this->label4->Location = System::Drawing::Point(26, 94);
    this->label4->Name = L"label4";
    this->label4->Size = System::Drawing::Size(75, 13);
    this->label4->TabIndex = 6;
    this->label4->Text = L"Óðîâåíü CO2";
    // 
    // label3
    // 
    this->label3->AutoSize = true;
    this->label3->Location = System::Drawing::Point(2, 42);
    this->label3->Name = L"label3";
    this->label3->Size = System::Drawing::Size(99, 13);
    this->label3->TabIndex = 3;
    this->label3->Text = L"Âëàæíîñòü Ïî÷âû";
    // 
    // label2
    // 
    this->label2->AutoSize = true;
    this->label2->Location = System::Drawing::Point(38, 68);
    this->label2->Name = L"label2";
    this->label2->Size = System::Drawing::Size(63, 13);
    this->label2->TabIndex = 2;
    this->label2->Text = L"Âëàæíîñòü";
    // 
    // label1
    // 
    this->label1->AutoSize = true;
    this->label1->Location = System::Drawing::Point(27, 16);
    this->label1->Name = L"label1";
    this->label1->Size = System::Drawing::Size(74, 13);
    this->label1->TabIndex = 1;
    this->label1->Text = L"Òåìïåðàòóðà";
    // 
    // groupBoxMeteoStation
    // 
    this->groupBoxMeteoStation->Controls->Add(this->numericMSco2);
    this->groupBoxMeteoStation->Controls->Add(this->label7);
    this->groupBoxMeteoStation->Controls->Add(this->numericMSHumidity);
    this->groupBoxMeteoStation->Controls->Add(this->label9);
    this->groupBoxMeteoStation->Controls->Add(this->numericMSTemperature);
    this->groupBoxMeteoStation->Controls->Add(this->label10);
    this->groupBoxMeteoStation->Location = System::Drawing::Point(191, 12);
    this->groupBoxMeteoStation->Name = L"groupBoxMeteoStation";
    this->groupBoxMeteoStation->Size = System::Drawing::Size(173, 148);
    this->groupBoxMeteoStation->TabIndex = 2;
    this->groupBoxMeteoStation->TabStop = false;
    this->groupBoxMeteoStation->Text = L"Ìåòåî Ñòàíöèÿ";
    // 
    // numericMSco2
    // 
    this->numericMSco2->Location = System::Drawing::Point(107, 66);
    this->numericMSco2->Name = L"numericMSco2";
    this->numericMSco2->Size = System::Drawing::Size(56, 20);
    this->numericMSco2->TabIndex = 14;
    this->numericMSco2->ValueChanged += gcnew System::EventHandler(this, &MainForm::numericMSco2_ValueChanged);
    // 
    // label7
    // 
    this->label7->AutoSize = true;
    this->label7->Location = System::Drawing::Point(26, 68);
    this->label7->Name = L"label7";
    this->label7->Size = System::Drawing::Size(75, 13);
    this->label7->TabIndex = 6;
    this->label7->Text = L"Óðîâåíü CO2";
    // 
    // numericMSHumidity
    // 
    this->numericMSHumidity->Location = System::Drawing::Point(107, 40);
    this->numericMSHumidity->Name = L"numericMSHumidity";
    this->numericMSHumidity->Size = System::Drawing::Size(56, 20);
    this->numericMSHumidity->TabIndex = 13;
    this->numericMSHumidity->ValueChanged += gcnew System::EventHandler(this, &MainForm::numericMSHumidity_ValueChanged);
    // 
    // label9
    // 
    this->label9->AutoSize = true;
    this->label9->Location = System::Drawing::Point(38, 42);
    this->label9->Name = L"label9";
    this->label9->Size = System::Drawing::Size(63, 13);
    this->label9->TabIndex = 2;
    this->label9->Text = L"Âëàæíîñòü";
    // 
    // numericMSTemperature
    // 
    this->numericMSTemperature->Location = System::Drawing::Point(107, 14);
    this->numericMSTemperature->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
    this->numericMSTemperature->Name = L"numericMSTemperature";
    this->numericMSTemperature->Size = System::Drawing::Size(56, 20);
    this->numericMSTemperature->TabIndex = 11;
    this->numericMSTemperature->ValueChanged += gcnew System::EventHandler(this, &MainForm::numericMSTemperature_ValueChanged);
    // 
    // label10
    // 
    this->label10->AutoSize = true;
    this->label10->Location = System::Drawing::Point(27, 16);
    this->label10->Name = L"label10";
    this->label10->Size = System::Drawing::Size(74, 13);
    this->label10->TabIndex = 1;
    this->label10->Text = L"Òåìïåðàòóðà";
    // 
    // textBoxLog
    // 
    this->textBoxLog->Font = (gcnew System::Drawing::Font(L"Consolas", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
        static_cast<System::Byte>(204)));
    this->textBoxLog->Location = System::Drawing::Point(12, 190);
    this->textBoxLog->Multiline = true;
    this->textBoxLog->Name = L"textBoxLog";
    this->textBoxLog->ReadOnly = true;
    this->textBoxLog->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
    this->textBoxLog->Size = System::Drawing::Size(692, 333);
    this->textBoxLog->TabIndex = 3;
    // 
    // label11
    // 
    this->label11->AutoSize = true;
    this->label11->Location = System::Drawing::Point(12, 174);
    this->label11->Name = L"label11";
    this->label11->Size = System::Drawing::Size(101, 13);
    this->label11->TabIndex = 4;
    this->label11->Text = L"Ñîñòîÿíèå ðàáîòû";
    // 
    // groupBoxStrategy
    // 
    this->groupBoxStrategy->Controls->Add(this->radioButtonEcoStrategy);
    this->groupBoxStrategy->Controls->Add(this->radioButtonNormalStrategy);
    this->groupBoxStrategy->Location = System::Drawing::Point(370, 12);
    this->groupBoxStrategy->Name = L"groupBoxStrategy";
    this->groupBoxStrategy->Size = System::Drawing::Size(146, 67);
    this->groupBoxStrategy->TabIndex = 5;
    this->groupBoxStrategy->TabStop = false;
    this->groupBoxStrategy->Text = L"Ñòðàòåãèÿ";
    // 
    // radioButtonEcoStrategy
    // 
    this->radioButtonEcoStrategy->AutoSize = true;
    this->radioButtonEcoStrategy->Location = System::Drawing::Point(6, 42);
    this->radioButtonEcoStrategy->Name = L"radioButtonEcoStrategy";
    this->radioButtonEcoStrategy->Size = System::Drawing::Size(132, 17);
    this->radioButtonEcoStrategy->TabIndex = 1;
    this->radioButtonEcoStrategy->TabStop = true;
    this->radioButtonEcoStrategy->Text = L"Ýêîíîìè÷íûé ðåæèì";
    this->radioButtonEcoStrategy->UseVisualStyleBackColor = true;
    this->radioButtonEcoStrategy->CheckedChanged += gcnew System::EventHandler(this, &MainForm::radioButtonEcoStrategy_CheckedChanged);
    // 
    // radioButtonNormalStrategy
    // 
    this->radioButtonNormalStrategy->AutoSize = true;
    this->radioButtonNormalStrategy->Location = System::Drawing::Point(6, 19);
    this->radioButtonNormalStrategy->Name = L"radioButtonNormalStrategy";
    this->radioButtonNormalStrategy->Size = System::Drawing::Size(128, 17);
    this->radioButtonNormalStrategy->TabIndex = 0;
    this->radioButtonNormalStrategy->TabStop = true;
    this->radioButtonNormalStrategy->Text = L"Íîðìàëüíûé ðåæèì";
    this->radioButtonNormalStrategy->UseVisualStyleBackColor = true;
    this->radioButtonNormalStrategy->CheckedChanged += gcnew System::EventHandler(this, &MainForm::radioButtonNormalStrategy_CheckedChanged);
    // 
    // comboBoxÑulture
    // 
    this->comboBoxÑulture->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
    this->comboBoxÑulture->FormattingEnabled = true;
    this->comboBoxÑulture->Location = System::Drawing::Point(531, 28);
    this->comboBoxÑulture->Name = L"comboBoxÑulture";
    this->comboBoxÑulture->Size = System::Drawing::Size(173, 21);
    this->comboBoxÑulture->TabIndex = 6;
    this->comboBoxÑulture->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::comboBoxÑulture_SelectedIndexChanged);
    // 
    // textBoxÑulture
    // 
    this->textBoxÑulture->Font = (gcnew System::Drawing::Font(L"Consolas", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
        static_cast<System::Byte>(0)));
    this->textBoxÑulture->Location = System::Drawing::Point(531, 55);
    this->textBoxÑulture->Multiline = true;
    this->textBoxÑulture->Name = L"textBoxÑulture";
    this->textBoxÑulture->ReadOnly = true;
    this->textBoxÑulture->Size = System::Drawing::Size(173, 105);
    this->textBoxÑulture->TabIndex = 7;
    // 
    // label6
    // 
    this->label6->AutoSize = true;
    this->label6->Location = System::Drawing::Point(528, 12);
    this->label6->Name = L"label6";
    this->label6->Size = System::Drawing::Size(53, 13);
    this->label6->TabIndex = 8;
    this->label6->Text = L"Êóëüòóðà";
    // 
    // MainForm
    // 
    this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
    this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
    this->ClientSize = System::Drawing::Size(716, 535);
    this->Controls->Add(this->label6);
    this->Controls->Add(this->textBoxÑulture);
    this->Controls->Add(this->comboBoxÑulture);
    this->Controls->Add(this->groupBoxStrategy);
    this->Controls->Add(this->label11);
    this->Controls->Add(this->textBoxLog);
    this->Controls->Add(this->groupBoxMeteoStation);
    this->Controls->Add(this->groupBoxGreenHouse);
    this->Name = L"MainForm";
    this->Text = L"MainForm";
    this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
    this->Shown += gcnew System::EventHandler(this, &MainForm::MainForm_Shown);
    this->groupBoxGreenHouse->ResumeLayout(false);
    this->groupBoxGreenHouse->PerformLayout();
    (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericGHLight))->EndInit();
    (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericGHco2))->EndInit();
    (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericGHHumidity))->EndInit();
    (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericGHSoilHumidity))->EndInit();
    (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericGHTemperature))->EndInit();
    this->groupBoxMeteoStation->ResumeLayout(false);
    this->groupBoxMeteoStation->PerformLayout();
    (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericMSco2))->EndInit();
    (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericMSHumidity))->EndInit();
    (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericMSTemperature))->EndInit();
    this->groupBoxStrategy->ResumeLayout(false);
    this->groupBoxStrategy->PerformLayout();
    this->ResumeLayout(false);
    this->PerformLayout();

}
