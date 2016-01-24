#include "StdAfx.h"
#include "Client_Form.h"
#define MAX_MESSAGE 1024

namespace FTPClientVerNetwork {

System::Void Client_Form::Client_Form_Load(System::Object^  sender, System::EventArgs^  e)
{
	threadClientDir = gcnew Thread(gcnew ThreadStart(this, &Client_Form::thread_Client_Dir));
	currentPath = Directory::GetCurrentDirectory();
	threadClientDir->Start();
}

System::Void Client_Form::Client_Form_Closing(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e)
{
	if (!button1->Enabled) {
		for (int i = 0; i < transCount; i++)
		{
			if (threadTrans[i]->IsAlive)
			{
				threadTrans[i]->Abort();
			}
		}
		send(socketServerCmd, "EXIT", MAX_MESSAGE, 0);
		this->richTextBox1->SelectionColor = Color::Black;
		this->richTextBox1->AppendText(String::Concat("狀態:\t已從伺服器離線\n"));
		this->richTextBox1->Focus();
		this->richTextBox1->ScrollToCaret();
		closesocket(socketServerCmd);
		WSACleanup();
	}
}

System::Void Client_Form::button1_Click(System::Object^  sender, System::EventArgs^  e)
{
	this->button1->Enabled = false;
	this->textBox1->Enabled = false;
	this->textBox2->Enabled = false;
	this->textBox3->Enabled = false;
	this->textBox4->Enabled = false;
	this->textBox7->Enabled = false;
	threadMain = gcnew Thread(gcnew ThreadStart(this, &Client_Form::thread_Login));
	threadMain->Start();

	if (transCount > -1)
	{
		for (int i = 0; i < transCount; i++)
		{
			delete labelFileName[i];
			delete labelFileDire[i];
			delete labelFileSize[i];
			delete labelFileState[i];
			delete progressBarTrans[i];
		}
	}
		
	try
	{
		transCount = Int32::Parse(textBox7->Text);
	}
	catch(System::Exception^ e)
	{
		transCount = 5;
	}
	turn = gcnew array<int>(transCount);
	flag = gcnew array<int>(transCount + 1);

	labelFileName = gcnew array<Label ^>(transCount);
	labelFileDire = gcnew array<Label ^>(transCount);
	labelFileSize = gcnew array<Label ^>(transCount);
	labelFileState = gcnew array<Label ^>(transCount);
	progressBarTrans = gcnew array<ProgressBar ^>(transCount);
	for (int i = 0; i < transCount; i++)
	{
		labelFileName[i] = (gcnew System::Windows::Forms::Label());
		labelFileDire[i] = (gcnew System::Windows::Forms::Label());
		labelFileSize[i] = (gcnew System::Windows::Forms::Label());
		labelFileState[i] = (gcnew System::Windows::Forms::Label());
		progressBarTrans[i] = (gcnew System::Windows::Forms::ProgressBar());
		tabPage1->Controls->Add(labelFileName[i]);
		tabPage1->Controls->Add(labelFileDire[i]);
		tabPage1->Controls->Add(labelFileSize[i]);
		tabPage1->Controls->Add(labelFileState[i]);
		tabPage1->Controls->Add(progressBarTrans[i]);
		labelFileName[i]->Visible = false;
		labelFileDire[i]->Visible = false;
		labelFileSize[i]->Visible = false;
		labelFileState[i]->Visible = false;
		progressBarTrans[i]->Visible = false;
		labelFileName[i]->AutoEllipsis = true;
		labelFileDire[i]->AutoEllipsis = true;
		labelFileSize[i]->AutoEllipsis = true;
		labelFileState[i]->AutoEllipsis = true;
		labelFileName[i]->Size = Drawing::Size(400, 15);
		labelFileDire[i]->Size = Drawing::Size(30, 15);
		labelFileSize[i]->Size = Drawing::Size(145, 15);
		labelFileState[i]->Size = Drawing::Size(45, 15);
		progressBarTrans[i]->Size = Drawing::Size(100, 15);
		labelFileName[i]->TextAlign = Drawing::ContentAlignment::MiddleLeft;
		labelFileDire[i]->TextAlign = Drawing::ContentAlignment::MiddleLeft;
		labelFileSize[i]->TextAlign = Drawing::ContentAlignment::MiddleLeft;
		labelFileState[i]->TextAlign = Drawing::ContentAlignment::MiddleLeft;
	}
}

System::Void Client_Form::button2_Click(System::Object^  sender, System::EventArgs^  e)
{
	this->button2->Enabled = false;
	for (int i = 0;threadMain->IsAlive && i < 100000; i++);

	if (!threadMain->IsAlive)
	{
		threadMain = gcnew Thread(gcnew ThreadStart(this, &Client_Form::thread_Logout));
		threadMain->Start();
	}
	else
	{
		threadForceLogout = gcnew Thread(gcnew ThreadStart(this, &Client_Form::thread_Force_Logout));
		threadForceLogout->Start();
	}
}

System::Void Client_Form::button3_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (listBox1->SelectedIndex >= 0)
	{
		if (File::Exists(String::Concat(currentPath, "/", listBox1->SelectedItem->ToString())))
		{
			for (int i = 0; i < transCount; i++)
			{
				if (!threadTrans[i]->IsAlive)
				{
					threadTrans[i] = gcnew Thread(gcnew ParameterizedThreadStart(this, &Client_Form::thread_Upload));
					threadTrans[i]->Start(gcnew array<Object^> {textBox6->Text, listBox1->SelectedItem->ToString(), textBox5->Text, i, (Object^)0, 1});
					break;
				}
			}
		}
	}
}

System::Void Client_Form::button4_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (listBox1->SelectedIndex >= 0)
	{
		if (File::Exists(listBox1->SelectedItem->ToString()))
		{
			File::Delete(listBox1->SelectedItem->ToString());
		}
		else if (Directory::Exists(listBox1->SelectedItem->ToString()))
		{
			Directory::Delete(listBox1->SelectedItem->ToString(), true);
		}
		threadClientDir = gcnew Thread(gcnew ThreadStart(this, &Client_Form::thread_Client_Dir));
		threadClientDir->Start();
	}
}

System::Void Client_Form::button6_Click(System::Object^  sender, System::EventArgs^  e)
{
	threadClientDir = gcnew Thread(gcnew ThreadStart(this, &Client_Form::thread_Client_Dir));
	threadClientDir->Start();
}

System::Void Client_Form::button8_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (!button1->Enabled && !threadMain->IsAlive)
	{
		threadMain = gcnew Thread(gcnew ThreadStart(this, &Client_Form::thread_Refresh_Dir));
		threadMain->Start();
	}
}

System::Void Client_Form::button9_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (listBox2->SelectedIndex >= 0)
	{
		if (listBox2->SelectedIndex > dirSplit)
		{
			for (int i = 0; i < transCount; i++)
			{
				if (!threadTrans[i]->IsAlive)
				{
					threadTrans[i] = gcnew Thread(gcnew ParameterizedThreadStart(this, &Client_Form::thread_Download));
					threadTrans[i]->Start(gcnew array<Object^> {textBox6->Text, listBox2->SelectedItem->ToString(), textBox5->Text, i, (Object^)0, 2});
					break;
				}
			}
		}
	}
}

System::Void Client_Form::button10_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (listBox2->SelectedIndex >= 0)
	{
		if (listBox2->SelectedIndex > dirSplit)
		{
			if (!threadMain->IsAlive)
			{
				threadMain = gcnew Thread(gcnew ParameterizedThreadStart(this, &Client_Form::thread_Delete));
				threadMain->Start(listBox2->SelectedItem->ToString());
			}
		}
	}
}

System::Void Client_Form::listBox1_DoubleClick(System::Object^  sender, System::EventArgs^  e)
{
	if (File::Exists(String::Concat(currentPath, "/", listBox1->SelectedItem->ToString())))
	{
		for (int i = 0; i < transCount; i++)
		{
			if (!threadTrans[i]->IsAlive)
			{
				threadTrans[i] = gcnew Thread(gcnew ParameterizedThreadStart(this, &Client_Form::thread_Upload));
				threadTrans[i]->Start(gcnew array<Object^> {textBox6->Text, listBox1->SelectedItem->ToString(), textBox5->Text, i, (Object^)0, 1});
				break;
			}
		}
	}
	else if (Directory::Exists(String::Concat(currentPath, "/", listBox1->SelectedItem->ToString())))
	{
		threadClientDir = gcnew Thread(gcnew ThreadStart(this, &Client_Form::thread_Client_Dir));
		currentPath = String::Concat(currentPath, "/", listBox1->SelectedItem->ToString());
		threadClientDir->Start();
	}
}

System::Void Client_Form::listBox2_DoubleClick(System::Object^  sender, System::EventArgs^  e)
{
	if (listBox2->SelectedIndex == 0)
	{
		if (!threadMain->IsAlive)
		{
			threadMain = gcnew Thread(gcnew ThreadStart(this, &Client_Form::thread_Up_Dir));
			threadMain->Start();
		}
	}
	else if (listBox2->SelectedIndex < dirSplit)
	{
		if (!threadMain->IsAlive)
		{
			threadMain = gcnew Thread(gcnew ParameterizedThreadStart(this, &Client_Form::thread_Change_Dir));
			threadMain->Start(listBox2->SelectedItem->ToString());
		}
	}
	else if (listBox2->SelectedIndex > dirSplit)
	{
		for (int i = 0; i < transCount; i++)
		{
			if (!threadTrans[i]->IsAlive)
			{
				threadTrans[i] = gcnew Thread(gcnew ParameterizedThreadStart(this, &Client_Form::thread_Download));
				threadTrans[i]->Start(gcnew array<Object^> {textBox6->Text, listBox2->SelectedItem->ToString(), textBox5->Text, i, (Object^)0, 2});
				break;
			}
		}
	}
}

void Client_Form::thread_Client_Dir(void)
{
	listBox1->Items->Clear();
	DirectoryInfo^ dirInfo = gcnew DirectoryInfo(currentPath);
	currentPath = dirInfo->FullName;
	textBox5->Text = currentPath;

	array<FileSystemInfo ^>^ dirEntries = dirInfo->GetDirectories();
	listBox1->Items->Add("..");
	for (int i = 0; i < dirEntries->Length; i++)
    {
		listBox1->Items->Add(dirEntries[i]);
    }

	listBox1->Items->Add("----------------------------------");
	array<FileSystemInfo ^>^ fileEntries = dirInfo->GetFiles();
	for (int i = 0; i < fileEntries->Length; i++)
    {
		listBox1->Items->Add(fileEntries[i]);
    }
}

void Client_Form::thread_Login(void)
{
	WSADATA info;
	if (WSAStartup(MAKEWORD(1,1), &info) !=0)
	{
		this->richTextBox1->SelectionColor = Color::Red;
		this->richTextBox1->AppendText("錯誤:\tWinsock 啟動失敗。\n");
		this->richTextBox1->Focus();
		this->richTextBox1->ScrollToCaret();
		this->button1->Enabled = true;
		this->textBox1->Enabled = true;
		this->textBox2->Enabled = true;
		this->textBox3->Enabled = true;
		this->textBox4->Enabled = true;
		this->textBox7->Enabled = true;
		return;
	}
	this->richTextBox1->SelectionColor = Color::Black;
	this->richTextBox1->AppendText("狀態:\tWinsock 啟動完成。\n");
	this->richTextBox1->Focus();
	this->richTextBox1->ScrollToCaret();

	try
	{
		transCount = Int32::Parse(textBox7->Text);
	}
	catch(System::Exception^ e)
	{
		this->richTextBox1->SelectionColor = Color::Red;
		this->richTextBox1->AppendText("錯誤:\t最大連接數不符合格式。\n");
		this->richTextBox1->Focus();
		this->richTextBox1->ScrollToCaret();
		this->button1->Enabled = true;
		this->textBox1->Enabled = true;
		this->textBox2->Enabled = true;
		this->textBox3->Enabled = true;
		this->textBox4->Enabled = true;
		this->textBox7->Enabled = true;
		return;
	}
	threadTrans = gcnew array<Thread ^>(transCount);
	for (int i = 0; i < transCount; i++) threadTrans[i] = gcnew Thread(gcnew ParameterizedThreadStart(this, &Client_Form::thread_Download));

	struct hostent *hostentServer;
	hostentServer = gethostbyname((char*)(void*)Marshal::StringToHGlobalAnsi(textBox1->Text));
	if (!hostentServer)
	{
		this->richTextBox1->SelectionColor = Color::Red;
		this->richTextBox1->AppendText("錯誤:\t無效的主機。\n");
		this->richTextBox1->ScrollToCaret();
		this->button1->Enabled = true;
		this->textBox1->Enabled = true;
		this->textBox2->Enabled = true;
		this->textBox3->Enabled = true;
		this->textBox4->Enabled = true;
		this->textBox7->Enabled = true;
		return;
	}

	struct sockaddr_in addressServer;
	addressServer.sin_family = AF_INET;
	addressServer.sin_addr = *((struct in_addr *)hostentServer->h_addr);
	try
	{
		addressServer.sin_port = htons(Int32::Parse(textBox4->Text));
	}
	catch(System::Exception^ e)
	{
		this->richTextBox1->SelectionColor = Color::Red;
		this->richTextBox1->AppendText("錯誤:\t連接埠不符合格式。\n");
		this->richTextBox1->ScrollToCaret();
		this->button1->Enabled = true;
		this->textBox1->Enabled = true;
		this->textBox2->Enabled = true;
		this->textBox3->Enabled = true;
		this->textBox4->Enabled = true;
		this->textBox7->Enabled = true;
		return;
	}
	memset(&(addressServer.sin_zero), '\0', 8);

	socketServerCmd = socket(PF_INET, SOCK_STREAM, 0);
	if (socketServerCmd == INVALID_SOCKET)
	{
		this->richTextBox1->SelectionColor = Color::Red;
		this->richTextBox1->AppendText("錯誤:\tSocket 建立失敗。\n");
		this->richTextBox1->ScrollToCaret();
		this->button1->Enabled = true;
		this->textBox1->Enabled = true;
		this->textBox2->Enabled = true;
		this->textBox3->Enabled = true;
		this->textBox4->Enabled = true;
		this->textBox7->Enabled = true;
		return;
	}
	this->richTextBox1->SelectionColor = Color::Black;
	this->richTextBox1->AppendText("狀態:\tSocket 建立成功。\n");
	this->richTextBox1->ScrollToCaret();

	if (connect(socketServerCmd, (struct sockaddr *)&addressServer, sizeof(addressServer)) == SOCKET_ERROR)
	{
		this->richTextBox1->SelectionColor = Color::Red;
		this->richTextBox1->AppendText(String::Concat("錯誤:\t與 ", textBox1->Text, " 連線失敗。\n"));
		this->richTextBox1->ScrollToCaret();
		this->button1->Enabled = true;
		this->textBox1->Enabled = true;
		this->textBox2->Enabled = true;
		this->textBox3->Enabled = true;
		this->textBox4->Enabled = true;
		this->textBox7->Enabled = true;
		return;
	}
	this->richTextBox1->SelectionColor = Color::Black;
	this->richTextBox1->AppendText(String::Concat("狀態:\t與 ", textBox1->Text, " 連線成功。\n"));
	this->richTextBox1->ScrollToCaret();

	char buffer[MAX_MESSAGE];

	strcpy_s(buffer, MAX_MESSAGE, "USER ");
	strcat_s(buffer, MAX_MESSAGE, (char*)(void*)Marshal::StringToHGlobalAnsi(textBox2->Text));
	this->richTextBox1->SelectionColor = Color::Navy;
	this->richTextBox1->AppendText(String::Concat("指令:\t", gcnew String(buffer), "\n"));
	this->richTextBox1->ScrollToCaret();
	send(socketServerCmd, buffer, MAX_MESSAGE, 0);
	recv(socketServerCmd, buffer, MAX_MESSAGE, 0);
	this->richTextBox1->SelectionColor = Color::Green;
	this->richTextBox1->AppendText(String::Concat("回應:\t", gcnew String(buffer), "\n"));
	this->richTextBox1->ScrollToCaret();
	
	strcpy_s(buffer, MAX_MESSAGE, "PASS ");
	strcat_s(buffer, MAX_MESSAGE, (char*)(void*)Marshal::StringToHGlobalAnsi(textBox3->Text));
	this->richTextBox1->SelectionColor = Color::Navy;
	this->richTextBox1->AppendText(String::Concat("指令:\tPASS ****\n"));
	this->richTextBox1->ScrollToCaret();
	send(socketServerCmd, buffer, MAX_MESSAGE, 0);
	recv(socketServerCmd, buffer, MAX_MESSAGE, 0);
	this->richTextBox1->SelectionColor = Color::Green;
	this->richTextBox1->AppendText(String::Concat("回應:\t", gcnew String(buffer), "\n"));
	this->richTextBox1->ScrollToCaret();

	if (!String::Compare(gcnew String(buffer), "530 Login or Password incorrect."))
	{
		this->button1->Enabled = true;
		this->textBox1->Enabled = true;
		this->textBox2->Enabled = true;
		this->textBox3->Enabled = true;
		this->textBox4->Enabled = true;
		this->textBox7->Enabled = true;
		return;
	}

	this->button2->Enabled = true;

	listBox2->Items->Clear();
	this->richTextBox1->SelectionColor = Color::Navy;
	this->richTextBox1->AppendText(String::Concat("指令:\tPWD\n"));
	this->richTextBox1->ScrollToCaret();
	send(socketServerCmd, "PWD", MAX_MESSAGE, 0);
	recv(socketServerCmd, buffer, MAX_MESSAGE, 0);
	listBox2->Items->Add("..");
	dirSplit = atoi(buffer) + 1;
	for (int i = dirSplit - 1; i > 0; i--)
	{
		send(socketServerCmd, "PWD", MAX_MESSAGE, 0);
		recv(socketServerCmd, buffer, MAX_MESSAGE, 0);
		listBox2->Items->Add(gcnew String(buffer));
	}
	send(socketServerCmd, "PWD", MAX_MESSAGE, 0);
	recv(socketServerCmd, buffer, MAX_MESSAGE, 0);
	listBox2->Items->Add("----------------------------------");
	for (int i = atoi(buffer); i > 0; i--)
	{
		send(socketServerCmd, "PWD", MAX_MESSAGE, 0);
		recv(socketServerCmd, buffer, MAX_MESSAGE, 0);
		listBox2->Items->Add(gcnew String(buffer));
	}
	send(socketServerCmd, "PWD", MAX_MESSAGE, 0);
	recv(socketServerCmd, buffer, MAX_MESSAGE, 0);
	this->richTextBox1->SelectionColor = Color::Green;
	this->richTextBox1->AppendText(String::Concat("回應:\t", gcnew String(buffer), "\n"));
	this->richTextBox1->ScrollToCaret();
	this->textBox6->Text = "/";

	for (int i = queueFile->Count; i > 0; i--)
	{
		Object^ obj = queueFile->Dequeue();
		if ((int)((array<Object^>^)obj)[5] == 1)
		{
			for (int j = 0; j < transCount; j++)
			{
				if (!threadTrans[j]->IsAlive)
				{
					threadTrans[j] = gcnew Thread(gcnew ParameterizedThreadStart(this, &Client_Form::thread_Upload));
					threadTrans[j]->Start(obj);
					break;
				}
			}
		}
		else if ((int)((array<Object^>^)obj)[5] == 2)
		{
			for (int j = 0; j < transCount; j++)
			{
				if (!threadTrans[j]->IsAlive)
				{
					threadTrans[j] = gcnew Thread(gcnew ParameterizedThreadStart(this, &Client_Form::thread_Download));
					threadTrans[j]->Start(obj);
					break;
				}
			}
		}
		Sleep(100);
	}
}

void Client_Form::thread_Logout(void)
{
	for (int i = 0; i < transCount; i++)
	{
		if (threadTrans[i]->IsAlive)
		{
			threadTrans[i]->Abort();
		}
	}
	send(socketServerCmd, "EXIT", MAX_MESSAGE, 0);
	this->richTextBox1->SelectionColor = Color::Black;
	this->richTextBox1->AppendText(String::Concat("狀態:\t已從伺服器離線\n"));
	this->richTextBox1->ScrollToCaret();
	closesocket(socketServerCmd);
	WSACleanup();
	processCount = 0;
	this->button1->Enabled = true;
	this->textBox1->Enabled = true;
	this->textBox2->Enabled = true;
	this->textBox3->Enabled = true;
	this->textBox4->Enabled = true;
	this->textBox7->Enabled = true;
	listBox2->Items->Clear();
	this->textBox6->Text = "";
}

void Client_Form::thread_Force_Logout(void)
{
	for (int i = 0; i < transCount; i++)
	{
		if (threadTrans[i]->IsAlive)
		{
			threadTrans[i]->Abort();
		}
	}
	threadMain->Abort();

	struct hostent *hostentServer;
	hostentServer = gethostbyname((char*)(void*)Marshal::StringToHGlobalAnsi(textBox1->Text));
	if (!hostentServer)
	{
		this->richTextBox1->SelectionColor = Color::Red;
		this->richTextBox1->AppendText("錯誤:\t無效的主機。\n");
		this->richTextBox1->ScrollToCaret();
		this->button1->Enabled = true;
		return;
	}

	struct sockaddr_in addressServer;
	addressServer.sin_family = AF_INET;
	addressServer.sin_addr = *((struct in_addr *)hostentServer->h_addr);
	addressServer.sin_port = htons(Int32::Parse(textBox4->Text));
	memset(&(addressServer.sin_zero), '\0', 8);

	SOCKET socketServer;
	socketServer = socket(PF_INET, SOCK_STREAM, 0);
	if (socketServer == INVALID_SOCKET)
	{
		this->richTextBox1->SelectionColor = Color::Red;
		this->richTextBox1->AppendText("錯誤:\tSocket 建立失敗。\n");
		this->richTextBox1->ScrollToCaret();
		this->button1->Enabled = true;
		return;
	}
	this->richTextBox1->SelectionColor = Color::Black;
	this->richTextBox1->AppendText("狀態:\tSocket 建立成功。\n");
	this->richTextBox1->ScrollToCaret();

	if (connect(socketServer, (struct sockaddr *)&addressServer, sizeof(addressServer)) == SOCKET_ERROR)
	{
		this->richTextBox1->SelectionColor = Color::Red;
		this->richTextBox1->AppendText(String::Concat("錯誤:\t與 ", textBox1->Text, " 連線失敗。\n"));
		this->richTextBox1->ScrollToCaret();
		this->button1->Enabled = true;
		return;
	}
	this->richTextBox1->SelectionColor = Color::Black;
	this->richTextBox1->AppendText(String::Concat("狀態:\t與 ", textBox1->Text, " 連線成功。\n"));
	this->richTextBox1->ScrollToCaret();

	char buffer[MAX_MESSAGE];

	strcpy_s(buffer, MAX_MESSAGE, "USER ");
	strcat_s(buffer, MAX_MESSAGE, (char*)(void*)Marshal::StringToHGlobalAnsi(textBox2->Text));
	this->richTextBox1->SelectionColor = Color::Navy;
	this->richTextBox1->AppendText(String::Concat("指令:\t", gcnew String(buffer), "\n"));
	this->richTextBox1->ScrollToCaret();
	send(socketServer, buffer, MAX_MESSAGE, 0);
	recv(socketServer, buffer, MAX_MESSAGE, 0);
	this->richTextBox1->SelectionColor = Color::Green;
	this->richTextBox1->AppendText(String::Concat("回應:\t", gcnew String(buffer), "\n"));
	this->richTextBox1->ScrollToCaret();
	
	strcpy_s(buffer, MAX_MESSAGE, "PASS ");
	strcat_s(buffer, MAX_MESSAGE, (char*)(void*)Marshal::StringToHGlobalAnsi(textBox3->Text));
	this->richTextBox1->SelectionColor = Color::Navy;
	this->richTextBox1->AppendText(String::Concat("指令:\tPASS ****\n"));
	this->richTextBox1->ScrollToCaret();
	send(socketServer, buffer, MAX_MESSAGE, 0);
	recv(socketServer, buffer, MAX_MESSAGE, 0);
	this->richTextBox1->SelectionColor = Color::Green;
	this->richTextBox1->AppendText(String::Concat("回應:\t", gcnew String(buffer), "\n"));
	this->richTextBox1->ScrollToCaret();

	send(socketServerCmd, "EXIT", MAX_MESSAGE, 0);
	this->richTextBox1->SelectionColor = Color::Black;
	this->richTextBox1->AppendText(String::Concat("狀態:\t已從伺服器離線\n"));
	this->richTextBox1->ScrollToCaret();
	closesocket(socketServerCmd);
	WSACleanup();
	processCount = 0;
	this->button1->Enabled = true;
	this->textBox1->Enabled = true;
	this->textBox2->Enabled = true;
	this->textBox3->Enabled = true;
	this->textBox4->Enabled = true;
	this->textBox7->Enabled = true;
	listBox2->Items->Clear();
	this->textBox6->Text = "";
}

void Client_Form::thread_Up_Dir(void)
{
	char buffer[MAX_MESSAGE];

	listBox2->Items->Clear();
	this->richTextBox1->SelectionColor = Color::Navy;
	this->richTextBox1->AppendText(String::Concat("指令:\tCDUP\n"));
	this->richTextBox1->ScrollToCaret();
	send(socketServerCmd, "CDUP", MAX_MESSAGE, 0);
	recv(socketServerCmd, buffer, MAX_MESSAGE, 0);
	listBox2->Items->Add("..");
	dirSplit = atoi(buffer) + 1;
	for (int i = dirSplit - 1; i > 0; i--)
	{
		send(socketServerCmd, "CDUP", MAX_MESSAGE, 0);
		recv(socketServerCmd, buffer, MAX_MESSAGE, 0);
		listBox2->Items->Add(gcnew String(buffer));
	}
	send(socketServerCmd, "CDUP", MAX_MESSAGE, 0);
	recv(socketServerCmd, buffer, MAX_MESSAGE, 0);
	listBox2->Items->Add("----------------------------------");
	for (int i = atoi(buffer); i > 0; i--)
	{
		send(socketServerCmd, "CDUP", MAX_MESSAGE, 0);
		recv(socketServerCmd, buffer, MAX_MESSAGE, 0);
		listBox2->Items->Add(gcnew String(buffer));
	}
	send(socketServerCmd, "CDUP", MAX_MESSAGE, 0);
	recv(socketServerCmd, buffer, MAX_MESSAGE, 0);
	this->richTextBox1->SelectionColor = Color::Green;
	this->richTextBox1->AppendText(String::Concat("回應:\t", gcnew String(buffer), "\n"));
	this->richTextBox1->ScrollToCaret();
	if (String::Compare(textBox6->Text, "/"))
	{
		textBox6->Text = textBox6->Text->String::Substring(0, textBox6->Text->String::LastIndexOf('/'));
	}
	if (!String::Compare(textBox6->Text, ""))
	{
		this->textBox6->Text = "/";
	}
}

void Client_Form::thread_Change_Dir(Object^ obj)
{
	char buffer[MAX_MESSAGE];
	
	strcpy_s(buffer, MAX_MESSAGE, "CWD ");
	strcat_s(buffer, MAX_MESSAGE, (char*)(void*)Marshal::StringToHGlobalAnsi((String ^)obj));
	this->richTextBox1->SelectionColor = Color::Navy;
	this->richTextBox1->AppendText(String::Concat("指令:\tCWD ", obj, "\n"));
	this->richTextBox1->ScrollToCaret();
	send(socketServerCmd, buffer, MAX_MESSAGE, 0);
	recv(socketServerCmd, buffer, MAX_MESSAGE, 0);
	this->richTextBox1->SelectionColor = Color::Green;
	this->richTextBox1->AppendText(String::Concat("回應:\t", gcnew String(buffer), "\n"));
	this->richTextBox1->ScrollToCaret();

	listBox2->Items->Clear();
	this->richTextBox1->SelectionColor = Color::Navy;
	this->richTextBox1->AppendText(String::Concat("指令:\tPWD\n"));
	this->richTextBox1->ScrollToCaret();
	send(socketServerCmd, "PWD", MAX_MESSAGE, 0);
	recv(socketServerCmd, buffer, MAX_MESSAGE, 0);
	listBox2->Items->Add("..");
	dirSplit = atoi(buffer) + 1;
	for (int i = dirSplit - 1; i > 0; i--)
	{
		send(socketServerCmd, "PWD", MAX_MESSAGE, 0);
		recv(socketServerCmd, buffer, MAX_MESSAGE, 0);
		listBox2->Items->Add(gcnew String(buffer));
	}
	send(socketServerCmd, "PWD", MAX_MESSAGE, 0);
	recv(socketServerCmd, buffer, MAX_MESSAGE, 0);
	listBox2->Items->Add("----------------------------------");
	for (int i = atoi(buffer); i > 0; i--)
	{
		send(socketServerCmd, "PWD", MAX_MESSAGE, 0);
		recv(socketServerCmd, buffer, MAX_MESSAGE, 0);
		listBox2->Items->Add(gcnew String(buffer));
	}
	send(socketServerCmd, "PWD", MAX_MESSAGE, 0);
	recv(socketServerCmd, buffer, MAX_MESSAGE, 0);
	this->richTextBox1->SelectionColor = Color::Green;
	this->richTextBox1->AppendText(String::Concat("回應:\t", gcnew String(buffer), "\n"));
	this->richTextBox1->ScrollToCaret();

	if (String::Compare(textBox6->Text, "/"))
	{
		this->textBox6->Text = String::Concat(textBox6->Text, "/", obj);
	}
	else
	{
		this->textBox6->Text = String::Concat("/", obj);
	}
}

void Client_Form::thread_Download(Object^ obj)
{
	int fileSize, remain, progress, progressTemp, startPos;
	int s = (int)((array<Object^>^)obj)[3];
	try
	{
		struct hostent *hostentServer;
		hostentServer = gethostbyname((char*)(void*)Marshal::StringToHGlobalAnsi(textBox1->Text));
		if (!hostentServer)
		{
			this->richTextBox1->SelectionColor = Color::Red;
			this->richTextBox1->AppendText("錯誤:\t無效的主機。\n");
			this->richTextBox1->ScrollToCaret();
			this->button1->Enabled = true;
			return;
		}

		struct sockaddr_in addressServer;
		addressServer.sin_family = AF_INET;
		addressServer.sin_addr = *((struct in_addr *)hostentServer->h_addr);
		addressServer.sin_port = htons(Int32::Parse(textBox4->Text));
		memset(&(addressServer.sin_zero), '\0', 8);

		SOCKET socketServer;
		socketServer = socket(PF_INET, SOCK_STREAM, 0);
		if (socketServer == INVALID_SOCKET)
		{
			this->richTextBox1->SelectionColor = Color::Red;
			this->richTextBox1->AppendText("錯誤:\tSocket 建立失敗。\n");
			this->richTextBox1->ScrollToCaret();
			this->button1->Enabled = true;
			return;
		}
		this->richTextBox1->SelectionColor = Color::Black;
		this->richTextBox1->AppendText("狀態:\tSocket 建立成功。\n");
		this->richTextBox1->ScrollToCaret();

		if (connect(socketServer, (struct sockaddr *)&addressServer, sizeof(addressServer)) == SOCKET_ERROR)
		{
			this->richTextBox1->SelectionColor = Color::Red;
			this->richTextBox1->AppendText(String::Concat("錯誤:\t與 ", textBox1->Text, " 連線失敗。\n"));
			this->richTextBox1->ScrollToCaret();
			this->button1->Enabled = true;
			return;
		}
		this->richTextBox1->SelectionColor = Color::Black;
		this->richTextBox1->AppendText(String::Concat("狀態:\t與 ", textBox1->Text, " 連線成功。\n"));
		this->richTextBox1->ScrollToCaret();

		char buffer[MAX_MESSAGE];

		strcpy_s(buffer, MAX_MESSAGE, "USER ");
		strcat_s(buffer, MAX_MESSAGE, (char*)(void*)Marshal::StringToHGlobalAnsi(textBox2->Text));
		this->richTextBox1->SelectionColor = Color::Navy;
		this->richTextBox1->AppendText(String::Concat("指令:\t", gcnew String(buffer), "\n"));
		this->richTextBox1->ScrollToCaret();
		send(socketServer, buffer, MAX_MESSAGE, 0);
		recv(socketServer, buffer, MAX_MESSAGE, 0);
		this->richTextBox1->SelectionColor = Color::Green;
		this->richTextBox1->AppendText(String::Concat("回應:\t", gcnew String(buffer), "\n"));
		this->richTextBox1->ScrollToCaret();
	
		strcpy_s(buffer, MAX_MESSAGE, "PASS ");
		strcat_s(buffer, MAX_MESSAGE, (char*)(void*)Marshal::StringToHGlobalAnsi(textBox3->Text));
		this->richTextBox1->SelectionColor = Color::Navy;
		this->richTextBox1->AppendText(String::Concat("指令:\tPASS ****\n"));
		this->richTextBox1->ScrollToCaret();
		send(socketServer, buffer, MAX_MESSAGE, 0);
		recv(socketServer, buffer, MAX_MESSAGE, 0);
		this->richTextBox1->SelectionColor = Color::Green;
		this->richTextBox1->AppendText(String::Concat("回應:\t", gcnew String(buffer), "\n"));
		this->richTextBox1->ScrollToCaret();

		strcpy_s(buffer, MAX_MESSAGE, "CWD ");
		strcat_s(buffer, MAX_MESSAGE, (char*)(void*)Marshal::StringToHGlobalAnsi((String^)((array<Object^>^)obj)[0]));
		this->richTextBox1->SelectionColor = Color::Navy;
		this->richTextBox1->AppendText(String::Concat("指令:\tCWD ", (String^)((array<Object^>^)obj)[0], "\n"));
		this->richTextBox1->ScrollToCaret();
		send(socketServer, buffer, MAX_MESSAGE, 0);
		recv(socketServer, buffer, MAX_MESSAGE, 0);
		this->richTextBox1->SelectionColor = Color::Green;
		this->richTextBox1->AppendText(String::Concat("回應:\t", gcnew String(buffer), "\n"));
		this->richTextBox1->Focus();
		this->richTextBox1->ScrollToCaret();

		String^ fileName = (String^)((array<Object^>^)obj)[1];
		String^ filePath = (String^)((array<Object^>^)obj)[2];
		strcpy_s(buffer, MAX_MESSAGE, "RETR ");
		strcat_s(buffer, MAX_MESSAGE, (char*)(void*)Marshal::StringToHGlobalAnsi(fileName));
		this->richTextBox1->SelectionColor = Color::Navy;
		this->richTextBox1->AppendText(String::Concat("指令:\tRETR ", fileName, "\n"));
		this->richTextBox1->Focus();
		this->richTextBox1->ScrollToCaret();
		send(socketServer, buffer, MAX_MESSAGE, 0);
		recv(socketServer, buffer, MAX_MESSAGE, 0);
		this->richTextBox1->SelectionColor = Color::Green;
		this->richTextBox1->AppendText(String::Concat("回應:\t", gcnew String(buffer), "\n"));
		this->richTextBox1->Focus();
		this->richTextBox1->ScrollToCaret();

		startPos = (int)((array<Object^>^)obj)[4];
		sprintf_s(buffer, "%d", startPos);

		send(socketServer, buffer, MAX_MESSAGE, 0);
		recv(socketServer, buffer, MAX_MESSAGE, 0);
		fileSize = atoi(buffer);
		remain = fileSize - startPos;
		progressTemp = 0;

		//UI
		labelFileName[s]->Location = Drawing::Point(4, 5 + (processCount * 17));
		labelFileName[s]->Visible = true;
		labelFileName[s]->Text = fileName;
		labelFileDire[s]->Location = Drawing::Point(516, 5 + (processCount * 17));
		labelFileDire[s]->Visible = true;
		labelFileDire[s]->Text = "下載";
		labelFileSize[s]->Location = Drawing::Point(552, 5 + (processCount * 17));
		labelFileSize[s]->Visible = true;
		labelFileSize[s]->Text = String::Concat(Convert::ToString(fileSize - remain), " / ", Convert::ToString(fileSize), " Bytes");
		labelFileState[s]->Location = Drawing::Point(705, 5 + (processCount * 17));
		labelFileState[s]->Visible = true;
		labelFileState[s]->Text = "傳輸中";
		progressBarTrans[s]->Location = Drawing::Point(410, 5 + (processCount * 17));
		progressBarTrans[s]->Visible = true;
		if (remain > 0) progressBarTrans[s]->Value = (int)(((double)(fileSize - remain) / (double)fileSize) * 100);
		processCount++;

		fstream file;
		if (startPos == 0)
		{
			file.open((char*)(void*)Marshal::StringToHGlobalAnsi(String::Concat(filePath, "/", fileName)), ios::out|ios::binary);
		}
		else
		{
			file.open((char*)(void*)Marshal::StringToHGlobalAnsi(String::Concat(filePath, "/", fileName)), ios::in|ios::out|ios::binary);
		}
		file.seekg(startPos, ios::beg);
		while (remain > 0)
		{
			send(socketServer, "RETR", MAX_MESSAGE, 0);
			recv(socketServer, buffer, MAX_MESSAGE, 0);
			if (remain < MAX_MESSAGE)
			{
				file.write(buffer, remain);
				remain = 0;
			}
			else
			{
				remain -= MAX_MESSAGE;
				file.write(buffer, MAX_MESSAGE);
			}
			progress = (int)(((double)(fileSize - remain) / (double)fileSize) * 100);
			if (progressTemp % 999 == 0)
			{
				progressTemp = 0;
				progressBarTrans[s]->Value = progress;
				labelFileSize[s]->Text = String::Concat(Convert::ToString(fileSize - remain), " / ", Convert::ToString(fileSize), " Bytes");
			}
			progressTemp++;
		}
		file.close();

		send(socketServer, "RETR", MAX_MESSAGE, 0);
		recv(socketServer, buffer, MAX_MESSAGE, 0);
		this->richTextBox1->SelectionColor = Color::Green;
		this->richTextBox1->AppendText(String::Concat("回應:\t", gcnew String(buffer), "\n"));
		this->richTextBox1->Focus();
		this->richTextBox1->ScrollToCaret();
	
		threadClientDir = gcnew Thread(gcnew ThreadStart(this, &Client_Form::thread_Client_Dir));
		threadClientDir->Start();

		labelFileName[s]->Visible = false;
		labelFileDire[s]->Visible = false;
		labelFileSize[s]->Visible = false;
		labelFileState[s]->Visible = false;
		progressBarTrans[s]->Visible = false;
		processCount--;
		int sy = labelFileName[s]->Location.Y - 17;
		for (int i = 0; i < transCount; i++)
		{
			int y = labelFileName[i]->Location.Y - 17;
			if (y > sy)
			{
				labelFileName[i]->Location = Drawing::Point(4, y);
				labelFileDire[i]->Location = Drawing::Point(516, y);
				labelFileSize[i]->Location = Drawing::Point(552, y);
				labelFileState[i]->Location = Drawing::Point(705, y);
				progressBarTrans[i]->Location = Drawing::Point(410, y);
			}
		}

		closesocket(socketServer);
	}
	catch (ThreadAbortException^ e)
	{
		((array<Object^>^)obj)[4] = (Object^)(fileSize - remain);

		//peterson
		for (int i = 1; i <= transCount - 1; i++) {
			flag[s] = i;
			turn[i] = s;
			for (int j = 1; j <= transCount; j++) {
				if (j == s) continue;
				while (flag[j] >= i && turn[i] == s) ;
			}
		}
		queueFile->Enqueue(obj);
		flag[s] = 0;

		labelFileState[s]->Text = "中斷";
	}
}

void Client_Form::thread_Upload(Object^ obj)
{
	int fileSize, sended, progress, progressTemp, startPos;
	int s = (int)((array<Object^>^)obj)[3];
	try
	{
		struct hostent *hostentServer;
		hostentServer = gethostbyname((char*)(void*)Marshal::StringToHGlobalAnsi(textBox1->Text));
		if (!hostentServer)
		{
			this->richTextBox1->SelectionColor = Color::Red;
			this->richTextBox1->AppendText("錯誤:\t無效的主機。\n");
			this->richTextBox1->Focus();
			this->richTextBox1->ScrollToCaret();
			this->button1->Enabled = true;
			return;
		}

		struct sockaddr_in addressServer;
		addressServer.sin_family = AF_INET;
		addressServer.sin_addr = *((struct in_addr *)hostentServer->h_addr);
		addressServer.sin_port = htons(Int32::Parse(textBox4->Text));
		memset(&(addressServer.sin_zero), '\0', 8);

		SOCKET socketServer;
		socketServer = socket(PF_INET, SOCK_STREAM, 0);
		if (socketServer == INVALID_SOCKET)
		{
			this->richTextBox1->SelectionColor = Color::Red;
			this->richTextBox1->AppendText("錯誤:\tSocket 建立失敗。\n");
			this->richTextBox1->Focus();
			this->richTextBox1->ScrollToCaret();
			this->button1->Enabled = true;
			return;
		}
		this->richTextBox1->SelectionColor = Color::Black;
		this->richTextBox1->AppendText("狀態:\tSocket 建立成功。\n");
		this->richTextBox1->Focus();
		this->richTextBox1->ScrollToCaret();

		if (connect(socketServer, (struct sockaddr *)&addressServer, sizeof(addressServer)) == SOCKET_ERROR)
		{
			this->richTextBox1->SelectionColor = Color::Red;
			this->richTextBox1->AppendText(String::Concat("錯誤:\t與 ", textBox1->Text, " 連線失敗。\n"));
			this->richTextBox1->Focus();
			this->richTextBox1->ScrollToCaret();
			this->button1->Enabled = true;
			return;
		}
		this->richTextBox1->SelectionColor = Color::Black;
		this->richTextBox1->AppendText(String::Concat("狀態:\t與 ", textBox1->Text, " 連線成功。\n"));
		this->richTextBox1->Focus();
		this->richTextBox1->ScrollToCaret();

		char buffer[MAX_MESSAGE];

		strcpy_s(buffer, MAX_MESSAGE, "USER ");
		strcat_s(buffer, MAX_MESSAGE, (char*)(void*)Marshal::StringToHGlobalAnsi(textBox2->Text));
		this->richTextBox1->SelectionColor = Color::Navy;
		this->richTextBox1->AppendText(String::Concat("指令:\t", gcnew String(buffer), "\n"));
		this->richTextBox1->Focus();
		this->richTextBox1->ScrollToCaret();
		send(socketServer, buffer, MAX_MESSAGE, 0);
		recv(socketServer, buffer, MAX_MESSAGE, 0);
		this->richTextBox1->SelectionColor = Color::Green;
		this->richTextBox1->AppendText(String::Concat("回應:\t", gcnew String(buffer), "\n"));
		this->richTextBox1->Focus();
		this->richTextBox1->ScrollToCaret();
	
		strcpy_s(buffer, MAX_MESSAGE, "PASS ");
		strcat_s(buffer, MAX_MESSAGE, (char*)(void*)Marshal::StringToHGlobalAnsi(textBox3->Text));
		this->richTextBox1->SelectionColor = Color::Navy;
		this->richTextBox1->AppendText(String::Concat("指令:\tPASS ****\n"));
		this->richTextBox1->Focus();
		this->richTextBox1->ScrollToCaret();
		send(socketServer, buffer, MAX_MESSAGE, 0);
		recv(socketServer, buffer, MAX_MESSAGE, 0);
		this->richTextBox1->SelectionColor = Color::Green;
		this->richTextBox1->AppendText(String::Concat("回應:\t", gcnew String(buffer), "\n"));
		this->richTextBox1->Focus();
		this->richTextBox1->ScrollToCaret();

		strcpy_s(buffer, MAX_MESSAGE, "CWD ");
		strcat_s(buffer, MAX_MESSAGE, (char*)(void*)Marshal::StringToHGlobalAnsi((String^)((array<Object^>^)obj)[0]));
		this->richTextBox1->SelectionColor = Color::Navy;
		this->richTextBox1->AppendText(String::Concat("指令:\tCWD ", (String^)((array<Object^>^)obj)[0], "\n"));
		this->richTextBox1->Focus();
		this->richTextBox1->ScrollToCaret();
		send(socketServer, buffer, MAX_MESSAGE, 0);
		recv(socketServer, buffer, MAX_MESSAGE, 0);
		this->richTextBox1->SelectionColor = Color::Green;
		this->richTextBox1->AppendText(String::Concat("回應:\t", gcnew String(buffer), "\n"));
		this->richTextBox1->Focus();
		this->richTextBox1->ScrollToCaret();

		String^ fileName = (String^)((array<Object^>^)obj)[1];
		String^ filePath = (String^)((array<Object^>^)obj)[2];
		strcpy_s(buffer, MAX_MESSAGE, "SETR ");
		strcat_s(buffer, MAX_MESSAGE, (char*)(void*)Marshal::StringToHGlobalAnsi(fileName));
		this->richTextBox1->SelectionColor = Color::Navy;
		this->richTextBox1->AppendText(String::Concat("指令:\tSETR ", fileName, "\n"));
		this->richTextBox1->Focus();
		this->richTextBox1->ScrollToCaret();
		send(socketServer, buffer, MAX_MESSAGE, 0);
		recv(socketServer, buffer, MAX_MESSAGE, 0);
		if (String::Compare(gcnew String(buffer), "200 Command okay."))
		{
			this->richTextBox1->SelectionColor = Color::Green;
			this->richTextBox1->AppendText(String::Concat("回應:\t", gcnew String(buffer), "\n"));
			this->richTextBox1->Focus();
			this->richTextBox1->ScrollToCaret();
			closesocket(socketServer);
			return;
		}
	
		fstream file;
		file.open((char*)(void*)Marshal::StringToHGlobalAnsi(String::Concat(filePath, "/", fileName)), ios::in|ios::binary);
		file.seekg(0, ios::end);
		fileSize = (int)file.tellg();
		sended = startPos = (int)((array<Object^>^)obj)[4];
		file.seekg(startPos, ios::beg);

		sprintf_s(buffer, "%d", fileSize);
		send(socketServer, buffer, MAX_MESSAGE, 0);
		recv(socketServer, buffer, MAX_MESSAGE, 0);
		this->richTextBox1->SelectionColor = Color::Green;
		this->richTextBox1->AppendText(String::Concat("回應:\t", gcnew String(buffer), "\n"));
		this->richTextBox1->Focus();
		this->richTextBox1->ScrollToCaret();
	
		sprintf_s(buffer, "%d", startPos);
		send(socketServer, buffer, MAX_MESSAGE, 0);
		recv(socketServer, buffer, MAX_MESSAGE, 0);
	
		//UI
		labelFileName[s]->Location = Drawing::Point(4, 5 + (processCount * 17));
		labelFileName[s]->Visible = true;
		labelFileName[s]->Text = fileName;
		labelFileDire[s]->Location = Drawing::Point(516, 5 + (processCount * 17));
		labelFileDire[s]->Visible = true;
		labelFileDire[s]->Text = "上傳";
		labelFileSize[s]->Location = Drawing::Point(552, 5 + (processCount * 17));
		labelFileSize[s]->Visible = true;
		labelFileSize[s]->Text = String::Concat(Convert::ToString(sended), " / ", Convert::ToString(fileSize), " Bytes");
		labelFileState[s]->Location = Drawing::Point(705, 5 + (processCount * 17));
		labelFileState[s]->Visible = true;
		labelFileState[s]->Text = "傳輸中";
		progressBarTrans[s]->Location = Drawing::Point(410, 5 + (processCount * 17));
		progressBarTrans[s]->Visible = true;
		progressBarTrans[s]->Value = (int)(((double)sended / (double)fileSize) * 100);
		processCount++;
		progressTemp = 0;

		while (!file.eof())
		{
			file.read(buffer, MAX_MESSAGE);
			send(socketServer, buffer, MAX_MESSAGE, 0);
			sended += MAX_MESSAGE;
			if (sended > fileSize) sended = fileSize;
			recv(socketServer, buffer, MAX_MESSAGE, 0);

			progress = (int)(((double)sended / (double)fileSize) * 100);
			if (progressTemp % 999 == 0)
			{
				progressTemp = 0;
				progressBarTrans[s]->Value = progress;
				labelFileSize[s]->Text = String::Concat(Convert::ToString(sended), " / ", Convert::ToString(fileSize), " Bytes");
			}
			progressTemp++;
		}
		file.close();

		send(socketServer, "SETR", MAX_MESSAGE, 0);
		recv(socketServer, buffer, MAX_MESSAGE, 0);
		this->richTextBox1->SelectionColor = Color::Green;
		this->richTextBox1->AppendText(String::Concat("回應:\t", gcnew String(buffer), "\n"));
		this->richTextBox1->SelectionColor = Color::Black;
		this->richTextBox1->AppendText(String::Concat("狀態:\t檔案傳輸成功。\n"));
		this->richTextBox1->Focus();
		this->richTextBox1->ScrollToCaret();
	
		if (!threadMain->IsAlive)
		{
			threadMain = gcnew Thread(gcnew ThreadStart(this, &Client_Form::thread_Refresh_Dir));
			threadMain->Start();
		}

		labelFileName[s]->Visible = false;
		labelFileDire[s]->Visible = false;
		labelFileSize[s]->Visible = false;
		labelFileState[s]->Visible = false;
		progressBarTrans[s]->Visible = false;
		processCount--;
		int sy = labelFileName[s]->Location.Y - 17;
		for (int i = 0; i < transCount; i++)
		{
			int y = labelFileName[i]->Location.Y - 17;
			if (y > sy)
			{
				labelFileName[i]->Location = Drawing::Point(4, y);
				labelFileDire[i]->Location = Drawing::Point(516, y);
				labelFileSize[i]->Location = Drawing::Point(552, y);
				labelFileState[i]->Location = Drawing::Point(705, y);
				progressBarTrans[i]->Location = Drawing::Point(410, y);
			}
		}

		closesocket(socketServer);
	}
	catch (ThreadAbortException^ e)
	{
		((array<Object^>^)obj)[4] = (Object^)(sended);

		//peterson
		for (int i = 1; i <= transCount - 1; i++) {
			flag[s] = i;
			turn[i] = s;
			for (int j = 1; j <= transCount; j++) {
				if (j == s) continue;
				while (flag[j] >= i && turn[i] == s) ;
			}
		}
		queueFile->Enqueue(obj);
		flag[s] = 0;

		labelFileState[s]->Text = "中斷";
	}
}

void Client_Form::thread_Refresh_Dir(void)
{
	char buffer[MAX_MESSAGE];

	listBox2->Items->Clear();
	this->richTextBox1->SelectionColor = Color::Navy;
	this->richTextBox1->AppendText(String::Concat("指令:\tPWD\n"));
	this->richTextBox1->Focus();
	this->richTextBox1->ScrollToCaret();
	send(socketServerCmd, "PWD", MAX_MESSAGE, 0);
	recv(socketServerCmd, buffer, MAX_MESSAGE, 0);
	listBox2->Items->Add("..");
	dirSplit = atoi(buffer) + 1;
	for (int i = dirSplit - 1; i > 0; i--)
	{
		send(socketServerCmd, "PWD", MAX_MESSAGE, 0);
		recv(socketServerCmd, buffer, MAX_MESSAGE, 0);
		listBox2->Items->Add(gcnew String(buffer));
	}
	send(socketServerCmd, "PWD", MAX_MESSAGE, 0);
	recv(socketServerCmd, buffer, MAX_MESSAGE, 0);
	listBox2->Items->Add("----------------------------------");
	for (int i = atoi(buffer); i > 0; i--)
	{
		send(socketServerCmd, "PWD", MAX_MESSAGE, 0);
		recv(socketServerCmd, buffer, MAX_MESSAGE, 0);
		listBox2->Items->Add(gcnew String(buffer));
	}
	send(socketServerCmd, "PWD", MAX_MESSAGE, 0);
	recv(socketServerCmd, buffer, MAX_MESSAGE, 0);
	this->richTextBox1->SelectionColor = Color::Green;
	this->richTextBox1->AppendText(String::Concat("回應:\t", gcnew String(buffer), "\n"));
	this->richTextBox1->Focus();
	this->richTextBox1->ScrollToCaret();
}

void Client_Form::thread_Delete(Object^ obj)
{
	char buffer[MAX_MESSAGE];
	
	strcpy_s(buffer, MAX_MESSAGE, "DELE ");
	strcat_s(buffer, MAX_MESSAGE, (char*)(void*)Marshal::StringToHGlobalAnsi((String ^)obj));
	this->richTextBox1->SelectionColor = Color::Navy;
	this->richTextBox1->AppendText(String::Concat("指令:\tDELE ", obj, "\n"));
	this->richTextBox1->Focus();
	this->richTextBox1->ScrollToCaret();
	send(socketServerCmd, buffer, MAX_MESSAGE, 0);
	recv(socketServerCmd, buffer, MAX_MESSAGE, 0);
	this->richTextBox1->SelectionColor = Color::Green;
	this->richTextBox1->AppendText(String::Concat("回應:\t", gcnew String(buffer), "\n"));
	this->richTextBox1->Focus();
	this->richTextBox1->ScrollToCaret();

	listBox2->Items->Clear();
	this->richTextBox1->SelectionColor = Color::Navy;
	this->richTextBox1->AppendText(String::Concat("指令:\tPWD\n"));
	this->richTextBox1->Focus();
	this->richTextBox1->ScrollToCaret();
	send(socketServerCmd, "PWD", MAX_MESSAGE, 0);
	recv(socketServerCmd, buffer, MAX_MESSAGE, 0);
	listBox2->Items->Add("..");
	dirSplit = atoi(buffer) + 1;
	for (int i = dirSplit - 1; i > 0; i--)
	{
		send(socketServerCmd, "PWD", MAX_MESSAGE, 0);
		recv(socketServerCmd, buffer, MAX_MESSAGE, 0);
		listBox2->Items->Add(gcnew String(buffer));
	}
	send(socketServerCmd, "PWD", MAX_MESSAGE, 0);
	recv(socketServerCmd, buffer, MAX_MESSAGE, 0);
	listBox2->Items->Add("----------------------------------");
	for (int i = atoi(buffer); i > 0; i--)
	{
		send(socketServerCmd, "PWD", MAX_MESSAGE, 0);
		recv(socketServerCmd, buffer, MAX_MESSAGE, 0);
		listBox2->Items->Add(gcnew String(buffer));
	}
	send(socketServerCmd, "PWD", MAX_MESSAGE, 0);
	recv(socketServerCmd, buffer, MAX_MESSAGE, 0);
	this->richTextBox1->SelectionColor = Color::Green;
	this->richTextBox1->AppendText(String::Concat("回應:\t", gcnew String(buffer), "\n"));
	this->richTextBox1->Focus();
	this->richTextBox1->ScrollToCaret();
}

}