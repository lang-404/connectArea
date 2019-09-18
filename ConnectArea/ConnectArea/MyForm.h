#pragma once
#include <opencv2\opencv.hpp>

namespace ConnectArea {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace cv;
	using namespace std;

	/// <summary>
	/// MyForm 摘要
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void);

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~MyForm();
		
	private: System::Windows::Forms::Button^  OpenImg;
	private: System::Windows::Forms::Button^  btnCal;
	protected:

	private:
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要修改
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		void InitializeComponent(void);
#pragma endregion
	private: System::Void OpenImg_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void btnCal_Click(System::Object^  sender, System::EventArgs^  e);
			 void CaluateConnectArea(Mat matSrc);

	};
}
