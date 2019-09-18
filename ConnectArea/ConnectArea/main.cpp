#include "MyForm.h"

using namespace ConnectArea;
[STAThreadAttribute]

int main()
{
	Application::EnableVisualStyles();
	Application::Run(gcnew MyForm());
	return 0;
}