// FTP Client Ver.Network.cpp: 主要專案檔。

#include "stdafx.h"
#include "Client_Form.h"

using namespace FTPClientVerNetwork;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// 建立主視窗並執行
	Application::Run(gcnew Client_Form());
	return 0;
}
