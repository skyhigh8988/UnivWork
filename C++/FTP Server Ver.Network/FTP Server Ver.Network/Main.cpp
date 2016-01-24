// FTP Server Ver.Network.cpp: 主要專案檔。

#include "stdafx.h"
#include "Server_Form.h"

using namespace FTPServerVerNetwork;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	Application::Run(gcnew Server_Form());
	return 0;
}
