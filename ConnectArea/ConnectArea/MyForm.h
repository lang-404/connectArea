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
	/// MyForm ժҪ
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void);

	protected:
		/// <summary>
		/// ������������ʹ�õ���Դ��
		/// </summary>
		~MyForm();
		
	private: System::Windows::Forms::Button^  OpenImg;
	private: System::Windows::Forms::Button^  btnCal;
	protected:

	private:
		/// <summary>
		/// ����������������
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// �����֧������ķ��� - ��Ҫ�޸�
		/// ʹ�ô���༭���޸Ĵ˷��������ݡ�
		/// </summary>
		void InitializeComponent(void);
#pragma endregion
	private: System::Void OpenImg_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void btnCal_Click(System::Object^  sender, System::EventArgs^  e);
			 void CaluateConnectArea(Mat matSrc);

	};
}
