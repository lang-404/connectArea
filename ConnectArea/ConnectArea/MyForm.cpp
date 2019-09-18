#include "MyForm.h"

namespace ConnectArea {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;
	using namespace cv;
	using namespace std;

	Mat matRead;

	System::Void MyForm::OpenImg_Click(System::Object^  sender, System::EventArgs^  e)
	{
		// 1����ȡ��ǰ·���ļ�
		System::Windows::Forms::OpenFileDialog ^ ofd01;
		ofd01 = (gcnew System::Windows::Forms::OpenFileDialog());
		ofd01->InitialDirectory = System::Windows::Forms::Application::StartupPath;
		ofd01->FileName = "";
		// 2���ж϶�ȡ״̬
		if (ofd01->ShowDialog() != System::Windows::Forms::DialogResult::OK)
		{
			MessageBox::Show("û�ж���ͼƬ");
			return;
		}
		// 3����ȡ����ͼƬ
		Mat matReadImage = imread((char*)(void*)Marshal::StringToHGlobalAnsi(ofd01->FileName), 1);
		matReadImage.copyTo(matRead);
		imshow("����ͼ", matReadImage);

	}

	System::Void MyForm::btnCal_Click(System::Object^  sender, System::EventArgs^  e)
	{
		// �ҶȻ�����ֵ��
		Mat matColor, matValue;
		cvtColor(matRead,matColor,CV_BGR2GRAY);

		threshold(matColor, matValue,10,255, THRESH_BINARY);
		imshow("��ֵͼ",matValue);
		CaluateConnectArea(matValue);


	}

	void MyForm::CaluateConnectArea(Mat matSrc)
	{
		// 1���������
		int iw, ih;// ͼ��Ŀ�ȣ��߶�
		int v1, v2, v3, v4;// ������ֵ
		int ilabel;// ��ǩֵ
		int iareaquantity;// ��������
		int i, j, m, n;// ѭ������
		int k;
		int* iDst;
		int imin, t;
		// 2����ʼ��
		iw = matSrc.cols;
		ih = matSrc.rows;
		iDst = new int[iw*ih];

		// 3������ָ�����
		uchar* ubarrtmatSrc = matSrc.ptr<uchar>(0);
		ilabel = 0;

		// Ϊÿ����Ч������һ��labelֵ
		for (i = 0; i < iw; i++)
		{
			for (j = 0; j < ih; j++)
			{
				k = ubarrtmatSrc[i + j*iw];
				if (k == 0)
				{
					iDst[i + j*iw] = 0;
				}
				else
				{
					if (i - 1 < 0)
					{
						v1 = 0;
					}
					else
					{
						v1 = iDst[i - 1 + j*iw];
					}
					if (i + 1 >= iw)
					{
						v2 = 0;
					}
					else
					{
						v2 = iDst[i + 1 + j*iw];
					}
					if (j - 1 < 0)
					{
						v3 = 0;
					}
					else
					{
						v3 = iDst[i + (j - 1)*iw];
					}
					if (j + 1 >= 0)
					{
						v4 = 0;
					}
					else
					{
						v4 = iDst[i + (j - 1)*iw];
					}
					if (v1 == 0 && v2 == 0 && v3 == 0 && v4 == 0)
					{
						ilabel++;
						iDst[i + j*iw] = ilabel;
					}
					else
					{
						imin = v1 + v2 + v3 + v4;
						if (v1 > 0 && imin > v1)
						{
							imin = v1;
						}
						if (v2 > 0 && imin > v2)
						{
							imin = v2;
						}
						if (v3 > 0 && imin > v3)
						{
							imin = v3;
						}
						if (v4 > 0 && imin > v4)
						{
							imin = v4;
						}
						iDst[i + j*iw] = imin;
					}// else

				}// else
			
			}// for (j = 0; j < ih; j++)
		}// for (i = 0; i < iw; i++)

		ilabel++;
		int *iRank = new int[ilabel];

		for (i = 0; i < ilabel; i++)
		{
			iRank[i] = i;
		}

		// �ڶ���ɨ�� ��������label
		for (i = 0; i < iw; i++)
		{
			for (j = 0; j < ih; j++)
			{
				t = iDst[i + j*iw];
				if (t > 0)
				{
					if (i - 1 < 0)
					{
						v1 = 0;
					}
					else
					{
						v1 = iDst[i - 1 + j*iw];
					}
					if (i + 2 >= iw)
					{
						v2 = 0;
					}
					else
					{
						v2 = iDst[i + 1 + j*iw];
					}
					if (j - 1 < 0)
					{
						v3 = 0;
					}
					else
					{
						v3 = iDst[i + (j - 1)*iw];
					}
					if (j + 2 >= ih)
					{
						v4 = 0;
					}
					else
					{
						v4 = iDst[i + (j + 1)*iw];
					}
					imin = v1 + v2 + v3 + v4;
					if (v1 > 0 && imin > v1)
					{
						imin = v1;
					}
					if (v2 > 0 && imin > v2)
					{
						imin = v2;
					}
					if (v3 > 0 && imin > v3)
					{
						imin = v3;
					}
					if (v4 > 0 && imin > v4)
					{
						imin = v4;
					}
					if (imin > 0 && imin < t)
					{
						iRank[t] = imin;
					}
				}
			}
		}
		for (i = 0; i < ilabel; i++)
		{
			iRank[i] = iRank[iRank[i]];
		}
		// 7��������ɨ��
		for (i = 0; i < iw; i++)////iwidth
		{
			for (j = 0; j < ih; j++)/////iheigh
			{
				t = iDst[i + j*iw];
				if (t > 0)
				{
					iDst[i + j*iw] = iRank[t];
				}
			}
		}

		// 8��ͳ����������,��������������
		int *iarr = new int[ilabel];
		for (i = 0; i < ilabel; i++)
		{
			iarr[i] = 0;
		}// for (i = 0; i < ilabel; i++) end

		for (i = 0; i < ilabel; i++)
		{
			iarr[iRank[i]] = iRank[i];
		}// for (i = 0; i < ilabel; i++) end

		j = 0;
		for (i = 0; i < ilabel; i++) {
			if (iarr[i] > 0) {
				j++;
				iarr[i] = j;
			}
		}// for (i = 0; i < ilabel; i++) end
		iareaquantity = j;

		// 9��������ֵ��������1��2��3��4��5
		for (i = 0; i < iw; i++)// iwidth
		{
			for (j = 0; j < ih; j++)// iheigh
			{
				t = iDst[i + j*iw];
				if (t > 0)
				{
					//	���ʵ�ǰ����B(x, y)�����B(x, y) > 1��
					//	��b��x��y�� = Labelset ��B(x, y)��;
					iDst[i + j*iw] = iarr[t];
				}
			}// for (j = 0; j < ih; j++) end
		}// for (i = 0; i < iw; i++) end

		 // 10���ͷ��ڴ�
		delete[] iRank;
		delete[] iarr;

		printf("count := %d\n", iareaquantity);// ����̨��� ��ͨ������
		

		for (k = 1; k < iareaquantity + 1; k++)
		{
			Mat show = Mat(matSrc.size(), CV_8UC3);
			for (i = 0; i < iw; i++)
			{
				for (j = 0; j < ih; j++)
				{
					t = iDst[i + j*iw];
					if (t == 0)
					{
						continue;
					}
					else
					{
						if (t == k)
						{
							show.at<Vec3b>(j, i)[1] = 255;
						}
					}
				}
			}
			string s = to_string(k) + "���.png";
			imwrite(s,show);
		}

	}

	
}