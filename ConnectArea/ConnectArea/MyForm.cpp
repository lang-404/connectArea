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
		// 1、获取当前路径文件
		System::Windows::Forms::OpenFileDialog ^ ofd01;
		ofd01 = (gcnew System::Windows::Forms::OpenFileDialog());
		ofd01->InitialDirectory = System::Windows::Forms::Application::StartupPath;
		ofd01->FileName = "";
		// 2、判断读取状态
		if (ofd01->ShowDialog() != System::Windows::Forms::DialogResult::OK)
		{
			MessageBox::Show("没有读入图片");
			return;
		}
		// 3、获取读入图片
		Mat matReadImage = imread((char*)(void*)Marshal::StringToHGlobalAnsi(ofd01->FileName), 1);
		matReadImage.copyTo(matRead);
		imshow("读入图", matReadImage);

	}

	System::Void MyForm::btnCal_Click(System::Object^  sender, System::EventArgs^  e)
	{
		// 灰度化，二值化
		Mat matColor, matValue;
		cvtColor(matRead,matColor,CV_BGR2GRAY);

		threshold(matColor, matValue,10,255, THRESH_BINARY);
		imshow("二值图",matValue);
		CaluateConnectArea(matValue);


	}

	void MyForm::CaluateConnectArea(Mat matSrc)
	{
		// 1、定义变量
		int iw, ih;// 图像的宽度，高度
		int v1, v2, v3, v4;// 四邻域值
		int ilabel;// 标签值
		int iareaquantity;// 区域数量
		int i, j, m, n;// 循环变量
		int k;
		int* iDst;
		int imin, t;
		// 2、初始化
		iw = matSrc.cols;
		ih = matSrc.rows;
		iDst = new int[iw*ih];

		// 3、定义指针变量
		uchar* ubarrtmatSrc = matSrc.ptr<uchar>(0);
		ilabel = 0;

		// 为每个有效点设置一个label值
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

		// 第二次扫描 更改邻域label
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
		// 7、第三次扫描
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

		// 8、统计区域数量,区域编号重新排列
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

		// 9、区域数值重新排列1，2，3，4，5
		for (i = 0; i < iw; i++)// iwidth
		{
			for (j = 0; j < ih; j++)// iheigh
			{
				t = iDst[i + j*iw];
				if (t > 0)
				{
					//	访问当前像素B(x, y)，如果B(x, y) > 1：
					//	则b（x，y） = Labelset 【B(x, y)】;
					iDst[i + j*iw] = iarr[t];
				}
			}// for (j = 0; j < ih; j++) end
		}// for (i = 0; i < iw; i++) end

		 // 10、释放内存
		delete[] iRank;
		delete[] iarr;

		printf("count := %d\n", iareaquantity);// 控制台输出 连通区数量
		

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
			string s = to_string(k) + "结果.png";
			imwrite(s,show);
		}

	}

	
}