#pragma once
#include "MyForm.h"

namespace ConnectArea {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	MyForm::MyForm(void)
	{
		InitializeComponent();

	}
	MyForm::~MyForm()
	{
		if (components)
		{
			delete components;
		}
	}

	void MyForm::InitializeComponent(void)
	{
		this->OpenImg = (gcnew System::Windows::Forms::Button());
		this->btnCal = (gcnew System::Windows::Forms::Button());
		this->SuspendLayout();
		// 
		// OpenImg
		// 
		this->OpenImg->Location = System::Drawing::Point(728, 66);
		this->OpenImg->Name = L"OpenImg";
		this->OpenImg->Size = System::Drawing::Size(84, 42);
		this->OpenImg->TabIndex = 0;
		this->OpenImg->Text = L"Open";
		this->OpenImg->UseVisualStyleBackColor = true;
		this->OpenImg->Click += gcnew System::EventHandler(this, &MyForm::OpenImg_Click);
		// 
		// btnCal
		// 
		this->btnCal->Location = System::Drawing::Point(728, 145);
		this->btnCal->Name = L"btnCal";
		this->btnCal->Size = System::Drawing::Size(84, 41);
		this->btnCal->TabIndex = 1;
		this->btnCal->Text = L"¼ÆËã";
		this->btnCal->UseVisualStyleBackColor = true;
		this->btnCal->Click += gcnew System::EventHandler(this, &MyForm::btnCal_Click);
		// 
		// MyForm
		// 
		this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->ClientSize = System::Drawing::Size(837, 497);
		this->Controls->Add(this->btnCal);
		this->Controls->Add(this->OpenImg);
		this->Name = L"MyForm";
		this->Text = L"MyForm";
		this->ResumeLayout(false);

	}
}