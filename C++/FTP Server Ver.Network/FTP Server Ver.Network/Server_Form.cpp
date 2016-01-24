#include "StdAfx.h"
#include "Server_Form.h"
#define MAX_MESSAGE 1024

namespace FTPServerVerNetwork {

System::Void Server_Form::Server_Form_Load(System::Object^  sender, System::EventArgs^  e)
{
	textBox1->Text = Directory::GetCurrentDirectory();
}

System::Void Server_Form::button1_Click(System::Object^  sender, System::EventArgs^  e)
{
	this->button1->Enabled = false;
	this->textBox1->Enabled = false;
	this->textBox3->Enabled = false;
	this->textBox4->Enabled = false;
	threadListen = gcnew Thread(gcnew ThreadStart(this, &Server_Form::thread_Listen));
	threadListen->Start();
}

System::Void Server_Form::button2_Click(System::Object^  sender, System::EventArgs^  e)
{
	this->button2->Enabled = false;
	for (int i = 0; i < connectAmount; i++)
	{
		if (threadConnect[i]->IsAlive)
		{
			closesocket(socketClient[i]);
			threadConnect[i]->Abort();
		}
	}
	threadListen->Abort();
	closesocket(socketServer);
	WSACleanup();

	this->listBox1->Items->Clear();
	this->listBox2->Items->Clear();
	this->dataGridView1->Rows->Clear();
	this->button1->Enabled = true;
	this->textBox1->Enabled = true;
	this->textBox3->Enabled = true;
	this->textBox4->Enabled = true;
}

System::Void Server_Form::button3_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (!button1->Enabled)
	{
		this->button3->Enabled = false;
		this->button5->Enabled = true;
		this->label5->Visible = true;
		this->textBox5->Enabled = true;
		this->textBox5->Visible = true;
		this->label6->Visible = true;
		this->textBox6->Visible = true;
		this->button7->Visible = true;
		this->button9->Visible = true;
		this->textBox5->Text = "";
		this->textBox6->Text = "";
	}
}

System::Void Server_Form::button4_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (listBox1->SelectedIndex >= 0)
	{
		userPass->RemoveAt(userName->LastIndexOf(listBox1->SelectedItem->ToString()));
		userName->Remove(listBox1->SelectedItem->ToString());

		StreamWriter^ fileWrite = gcnew StreamWriter( "user.dat" , false , System::Text::Encoding::Default);
		for (int i = 0; i < userName->Count; i++)
		{
			fileWrite->WriteLine(String::Concat(userName[i], "\t" , userPass[i]));
			fileWrite->Flush();
		}
		fileWrite->Close();

		listBox1->Items->RemoveAt(listBox1->SelectedIndex);
	}
}

System::Void Server_Form::button5_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (listBox1->SelectedIndex >= 0)
	{
		this->button5->Enabled = false;
		this->button3->Enabled = true;
		this->label5->Visible = true;
		this->textBox5->Enabled = false;
		this->textBox5->Visible = true;
		this->label6->Visible = true;
		this->textBox6->Visible = true;
		this->button7->Visible = true;
		this->button9->Visible = true;
		textBox5->Text = listBox1->SelectedItem->ToString();
		textBox6->Text = (String ^)userPass[userName->LastIndexOf(listBox1->SelectedItem->ToString())];
	}
}

System::Void Server_Form::button6_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (listBox1->SelectedIndex >= 0)
	{
		threadLoadDir = gcnew Thread(gcnew ParameterizedThreadStart(this, &Server_Form::thread_Load_User_Dir));
		threadLoadDir->Start(listBox1->SelectedItem->ToString());
	}
}

System::Void Server_Form::button7_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (!button5->Enabled)
	{
		userPass->RemoveAt(userName->LastIndexOf(textBox5->Text));
		userName->Remove(textBox5->Text);
		userName->Add(textBox5->Text);
		userPass->Add(textBox6->Text);

		StreamWriter^ fileWrite = gcnew StreamWriter( "user.dat" , false , System::Text::Encoding::Default);
		for (int i = 0; i < userName->Count; i++)
		{
			fileWrite->WriteLine(String::Concat(userName[i], "\t" , userPass[i]));
			fileWrite->Flush();
		}
		fileWrite->Close();

		this->button9->Visible = false;
		this->button7->Visible = false;
		this->textBox6->Visible = false;
		this->label6->Visible = false;
		this->textBox5->Visible = false;
		this->label5->Visible = false;
		this->button5->Enabled = true;
		this->textBox5->Text = "";
		this->textBox6->Text = "";
	}
	else if (!button3->Enabled)
	{
		if (userName->LastIndexOf(textBox5->Text) < 0)
		{
			userName->Add(textBox5->Text);
			userPass->Add(textBox6->Text);
			listBox1->Items->Add(textBox5->Text);
			
			StreamWriter^ fileWrite = gcnew StreamWriter( "user.dat" , true , System::Text::Encoding::Default);
			fileWrite->WriteLine(String::Concat(textBox5->Text, "\t" , textBox6->Text));
			fileWrite->Flush();
			fileWrite->Close();

			this->button9->Visible = false;
			this->button7->Visible = false;
			this->textBox6->Visible = false;
			this->label6->Visible = false;
			this->textBox5->Visible = false;
			this->label5->Visible = false;
			this->button3->Enabled = true;
			this->textBox5->Text = "";
			this->textBox6->Text = "";
		}
	}

}

System::Void Server_Form::button8_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (!button1->Enabled)
	{
		threadLoadDir = gcnew Thread(gcnew ThreadStart(this, &Server_Form::thread_Load_Dir));
		threadLoadDir->Start();
	}
}

System::Void Server_Form::button9_Click(System::Object^  sender, System::EventArgs^  e)
{
	this->button9->Visible = false;
	this->button7->Visible = false;
	this->textBox6->Visible = false;
	this->label6->Visible = false;
	this->textBox5->Visible = false;
	this->label5->Visible = false;
	this->button5->Enabled = true;
	this->button3->Enabled = true;
	this->textBox5->Text = "";
	this->textBox6->Text = "";
}

System::Void Server_Form::Server_Form_Closing(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e)
{
	if (!button1->Enabled) {
		for (int i = 0; i < connectAmount; i++)
		{
			if (threadConnect[i]->IsAlive)
			{
				closesocket(socketClient[i]);
				threadConnect[i]->Abort();
			}
		}
		threadListen->Abort();
		closesocket(socketServer);
		WSACleanup();
	}
}

System::Void Server_Form::listBox1_DoubleClick(System::Object^  sender, System::EventArgs^  e)
{
	threadLoadDir = gcnew Thread(gcnew ParameterizedThreadStart(this, &Server_Form::thread_Load_User_Dir));
	threadLoadDir->Start(listBox1->SelectedItem->ToString());
}

System::Void Server_Form::listBox2_DoubleClick(System::Object^  sender, System::EventArgs^  e)
{
	if (Directory::Exists(String::Concat(rootPath, "/", currentPath, "/", listBox2->SelectedItem->ToString())))
	{
		threadLoadDir = gcnew Thread(gcnew ThreadStart(this, &Server_Form::thread_Load_Dir));
		currentPath = String::Concat(currentPath, "/", listBox2->SelectedItem->ToString());
		threadLoadDir->Start();
	}
}

void Server_Form::thread_Load_User(void)
{
	listBox1->Items->Clear();
	if (File::Exists("user.dat"))
	{
		StreamReader ^ fileReader = gcnew StreamReader("user.dat", System::Text::Encoding::Default);
		String^ line;
		while (line = fileReader->ReadLine()) 
		{
			array<String^>^ split = line->Split('\t');
			if (split->Length < 2) break;
			userName->Add(split[0]);
			userPass->Add(split[1]);
			listBox1->Items->Add(split[0]);
		}
		fileReader->Close();
	}
	
	if (File::Exists("file.dat"))
	{
		StreamReader ^ fileReader = gcnew StreamReader("file.dat", System::Text::Encoding::Default);
		String^ line;
		while (line = fileReader->ReadLine()) 
		{
			array<String^>^ split = line->Split('\t');
			if (split->Length < 2) break;
			fileUser->Add(split[0]);
			fileName->Add(split[1]);
		}
		fileReader->Close();
	}
}

void Server_Form::thread_Load_Dir(void)
{
	listBox2->Items->Clear();
	DirectoryInfo^ dirInfo = gcnew DirectoryInfo(String::Concat(rootPath, "/", currentPath));
	currentPath = dirInfo->FullName->Substring(rootPath->Length);
	if (currentPath->Length == 0) currentPath = "\\";
	textBox2->Text = String::Concat(currentPath);

	array<FileSystemInfo ^>^ dirEntries = dirInfo->GetDirectories();
	listBox2->Items->Add("..");
	for (int i = 0; i < dirEntries->Length; i++)
    {
		listBox2->Items->Add(dirEntries[i]);
    }

	listBox2->Items->Add("----------------------------------");
	array<FileSystemInfo ^>^ fileEntries = dirInfo->GetFiles();
	for (int i = 0; i < fileEntries->Length; i++)
    {
		listBox2->Items->Add(fileEntries[i]);
    }
}

void Server_Form::thread_Load_User_Dir(Object^ obj)
{
	String^ temp = (String^)obj;
	listBox2->Items->Clear();
	DirectoryInfo^ dirInfo = gcnew DirectoryInfo(String::Concat(rootPath, "/", currentPath));
	currentPath = dirInfo->FullName->Substring(rootPath->Length);
	if (currentPath->Length == 0) currentPath = "\\";
	textBox2->Text = String::Concat(currentPath);

	array<FileSystemInfo ^>^ dirEntries = dirInfo->GetDirectories();
	listBox2->Items->Add("..");
	for (int i = 0; i < dirEntries->Length; i++)
    {
		listBox2->Items->Add(dirEntries[i]);
    }

	listBox2->Items->Add("----------------------------------");
	array<FileSystemInfo ^>^ fileEntries = dirInfo->GetFiles();
	for (int i = 0; i < fileEntries->Length; i++)
    {
		int s = fileName->LastIndexOf(fileEntries[i]->FullName);
		if (s >= 0 && !String::Compare((String^)fileUser[s], temp))
		{
			listBox2->Items->Add(fileEntries[i]);
		}
    }
}

void Server_Form::thread_Listen(void)
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
		this->textBox3->Enabled = true;
		this->textBox4->Enabled = true;
		return;
	}
	this->richTextBox1->SelectionColor = Color::Black;
	this->richTextBox1->AppendText("狀態:\tWinsock 啟動完成。\n");
	this->richTextBox1->Focus();
	this->richTextBox1->ScrollToCaret();

	rootPath = textBox1->Text;
	if (!Directory::Exists(rootPath))
	{
		this->richTextBox1->SelectionColor = Color::Red;
		this->richTextBox1->AppendText("錯誤:\t根目錄不存在。\n");
		this->richTextBox1->Focus();
		this->richTextBox1->ScrollToCaret();
		this->button1->Enabled = true;
		this->textBox1->Enabled = true;
		this->textBox3->Enabled = true;
		this->textBox4->Enabled = true;
		return;
	}
	threadLoadUser = gcnew Thread(gcnew ThreadStart(this, &Server_Form::thread_Load_User));
	threadLoadUser->Start();
	threadLoadDir = gcnew Thread(gcnew ThreadStart(this, &Server_Form::thread_Load_Dir));
	threadLoadDir->Start();

	struct sockaddr_in addressServer;
	struct sockaddr_in addressClient;

	addressServer.sin_family = AF_INET;
	addressServer.sin_addr.s_addr = INADDR_ANY;
	try
	{
		addressServer.sin_port = htons(Int32::Parse(this->textBox4->Text));
	}
	catch(System::Exception^ e)
	{
		this->richTextBox1->SelectionColor = Color::Red;
		this->richTextBox1->AppendText("錯誤:\t連接埠不符合格式。\n");
		this->richTextBox1->Focus();
		this->richTextBox1->ScrollToCaret();
		this->button1->Enabled = true;
		this->textBox1->Enabled = true;
		this->textBox3->Enabled = true;
		this->textBox4->Enabled = true;
		return;
	}
	memset(&(addressServer.sin_zero),'\0', 8);

	socketServer = socket(PF_INET, SOCK_STREAM, 0);
	if (socketServer == INVALID_SOCKET)
	{
		this->richTextBox1->SelectionColor = Color::Red;
		this->richTextBox1->AppendText("錯誤:\tSocket 建立失敗。\n");
		this->richTextBox1->Focus();
		this->richTextBox1->ScrollToCaret();
		this->button1->Enabled = true;
		this->textBox1->Enabled = true;
		this->textBox3->Enabled = true;
		this->textBox4->Enabled = true;
		return;
	}
	this->richTextBox1->SelectionColor = Color::Black;
	this->richTextBox1->AppendText("狀態:\tSocket 建立成功。\n");
	this->richTextBox1->Focus();
	this->richTextBox1->ScrollToCaret();
	if (bind(socketServer, (struct sockaddr *)&addressServer, sizeof(addressServer)) == SOCKET_ERROR)
	{
		this->richTextBox1->SelectionColor = Color::Red;
		this->richTextBox1->AppendText("錯誤:\t綁定失敗。\n");
		this->richTextBox1->Focus();
		this->richTextBox1->ScrollToCaret();
		this->button1->Enabled = true;
		this->textBox1->Enabled = true;
		this->textBox3->Enabled = true;
		this->textBox4->Enabled = true;
		return;
	}
	this->richTextBox1->SelectionColor = Color::Black;
	this->richTextBox1->AppendText("狀態:\t初始化完成。\n");
	this->richTextBox1->Focus();
	this->richTextBox1->ScrollToCaret();

	this->button2->Enabled = true;
	int length = sizeof(addressClient);

	try
	{
		connectAmount = Int32::Parse(this->textBox3->Text);
	}
	catch(System::Exception^ e)
	{
		this->richTextBox1->SelectionColor = Color::Red;
		this->richTextBox1->AppendText("錯誤:\t連接數不符合格式。\n");
		this->richTextBox1->Focus();
		this->richTextBox1->ScrollToCaret();
		this->button1->Enabled = true;
		this->textBox1->Enabled = true;
		this->textBox3->Enabled = true;
		this->textBox4->Enabled = true;
		return;
	}
	
	ipClient = gcnew array<String ^>(connectAmount);
	userClient = gcnew array<String ^>(connectAmount);
	viewRow = gcnew array<DataGridViewRow ^>(connectAmount);
	threadConnect = gcnew array<Thread ^>(connectAmount);
	socketClient = gcnew array<SOCKET>(connectAmount);
	for (int i = 0; i < connectAmount; i++) threadConnect[i] = gcnew Thread(gcnew ParameterizedThreadStart(this, &Server_Form::thread_Connect));
	listen(socketServer, connectAmount);

	this->richTextBox1->SelectionColor = Color::Black;
	this->richTextBox1->AppendText("狀態:\t等待連接。\n");
	this->richTextBox1->Focus();
	this->richTextBox1->ScrollToCaret();

	while (1)
	{
		for (int i = 0; i < connectAmount; i++)
		{
			if (!threadConnect[i]->IsAlive)
			{
				socketClient[i] = accept(socketServer, (struct sockaddr *)&addressClient, &length);
				ipClient[i] = gcnew String(inet_ntoa(addressClient.sin_addr));
				if (socketClient[i] == INVALID_SOCKET)
				{
					this->richTextBox1->SelectionColor = Color::Red;
					this->richTextBox1->AppendText(String::Concat("錯誤:\t與 ", ipClient[i], " 建立Socket失敗。\n"));
					this->richTextBox1->Focus();
					this->richTextBox1->ScrollToCaret();
				}
				else
				{
					this->richTextBox1->SelectionColor = Color::Black;
					this->richTextBox1->AppendText(String::Concat("狀態:\t與 ", ipClient[i], " 建立Socket成功。\n"));
					this->richTextBox1->Focus();
					this->richTextBox1->ScrollToCaret();
					threadConnect[i] = gcnew Thread(gcnew ParameterizedThreadStart(this, &Server_Form::thread_Connect));
					threadConnect[i]->Start(i);
				}
			}
		}
	}
}

void Server_Form::thread_Connect(Object^ obj) {

	int i = (int)obj;
	char buffer[MAX_MESSAGE];
	array<String^>^ split;
	String^ dirCurrent = "";

	recv(socketClient[i], buffer, MAX_MESSAGE, 0);
	this->richTextBox1->SelectionColor = Color::Blue;
	this->richTextBox1->AppendText(String::Concat("指令:\t", gcnew String(buffer), " (",i ,", ", ipClient[i], ")\n"));
	this->richTextBox1->Focus();
	this->richTextBox1->ScrollToCaret();
	split = (gcnew String(buffer))->Split(' ');
	if (String::Compare(split[0], "USER"))
	{
		send(socketClient[i], "332 Need account for login.", MAX_MESSAGE, 0);
		this->richTextBox1->SelectionColor = Color::Green;
		this->richTextBox1->AppendText(String::Concat("回應:\t332 Need account for login. (",i ,", ", ipClient[i], ")\n"));
		this->richTextBox1->Focus();
		this->richTextBox1->ScrollToCaret();
		return;
	}
	if (split->Length < 2)
	{
		send(socketClient[i], "501 Syntax error in parameters or arguments.", MAX_MESSAGE, 0);
		this->richTextBox1->SelectionColor = Color::Green;
		this->richTextBox1->AppendText(String::Concat("回應:\t501 Syntax error in parameters or arguments. (",i ,", ", ipClient[i], ")\n"));
		this->richTextBox1->Focus();
		this->richTextBox1->ScrollToCaret();
		return;
	}

	userClient[i] = split[1];
	strcpy_s(buffer, MAX_MESSAGE, "331 Password required for ");
	strcat_s(buffer, MAX_MESSAGE, (char*)(void*)Marshal::StringToHGlobalAnsi(split[1]));
	strcat_s(buffer, MAX_MESSAGE, ".");
	this->richTextBox1->SelectionColor = Color::Green;
	this->richTextBox1->AppendText(String::Concat("回應:\t", gcnew String(buffer), " (",i ,", ", ipClient[i], ")\n"));
	this->richTextBox1->Focus();
	this->richTextBox1->ScrollToCaret();
	send(socketClient[i], buffer, MAX_MESSAGE, 0);

	recv(socketClient[i], buffer, MAX_MESSAGE, 0);
	this->richTextBox1->SelectionColor = Color::Blue;
	this->richTextBox1->AppendText(String::Concat("指令:\t", gcnew String(buffer), " (",i ,", ", ipClient[i], ")\n"));
	this->richTextBox1->Focus();
	this->richTextBox1->ScrollToCaret();
	split = (gcnew String(buffer))->Split(' ');
	if (String::Compare(split[0], "PASS"))
	{
		send(socketClient[i], "332 Need account for login.", MAX_MESSAGE, 0);
		this->richTextBox1->SelectionColor = Color::Green;
		this->richTextBox1->AppendText(String::Concat("回應:\t332 Need account for login. (",i ,", ", ipClient[i], ")\n"));
		this->richTextBox1->Focus();
		this->richTextBox1->ScrollToCaret();
		return;
	}
	if (split->Length < 2)
	{
		send(socketClient[i], "501 Syntax error in parameters or arguments.", MAX_MESSAGE, 0);
		this->richTextBox1->SelectionColor = Color::Green;
		this->richTextBox1->AppendText(String::Concat("回應:\t501 Syntax error in parameters or arguments. (",i ,", ", ipClient[i], ")\n"));
		this->richTextBox1->Focus();
		this->richTextBox1->ScrollToCaret();
		return;
	}
	
	int id = userName->LastIndexOf(userClient[i]);
	if (id < 0 || String::Compare((String^)userPass[id], split[1]))
	{
		send(socketClient[i], "530 Login or Password incorrect.", MAX_MESSAGE, 0);
		this->richTextBox1->SelectionColor = Color::Green;
		this->richTextBox1->AppendText(String::Concat("回應:\t530 Login or Password incorrect. (",i ,", ", ipClient[i], ")\n"));
		this->richTextBox1->Focus();
		this->richTextBox1->ScrollToCaret();
		return;
	}

	this->richTextBox1->SelectionColor = Color::Teal;
	this->richTextBox1->AppendText(String::Concat("訊息:\t以 ", userClient[i], " 登入. (",i ,", ", ipClient[i], ")\n"));

	/*array<String^>^ row = gcnew array<String^>{i.ToString(), userClient[i], ipClient[i], gcnew String(buffer)};
	this->dataGridView1->Rows->Add(row);
	viewRow[i] = dataGridView1->Rows[dataGridView1->Rows->GetLastRow(DataGridViewElementStates::None)];*/
	if (listUser->LastIndexOf(userClient[i]) < 0)
	{
		listUser->Add(userClient[i]);
		listIP->Add(ipClient[i]);
	}
	this->dataGridView1->Rows->Clear();
	for (int j = 0; j < listUser->Count; j++)
	{
		this->dataGridView1->Rows->Add(gcnew array<String^>{(String^)listUser[j], (String^)listIP[j], ""});
	}

	this->richTextBox1->SelectionColor = Color::Green;
	this->richTextBox1->AppendText(String::Concat("回應:\t230 User logged in, proceed. (",i ,", ", ipClient[i], ")\n"));
	this->richTextBox1->Focus();
	this->richTextBox1->ScrollToCaret();
	send(socketClient[i], "230 User logged in, proceed.", MAX_MESSAGE, 0);

	while (1)
	{
		recv(socketClient[i], buffer, MAX_MESSAGE, 0);
		split = (gcnew String(buffer))->Split(' ');
		if (!String::Compare(split[0], "EXIT"))
		{
			this->richTextBox1->SelectionColor = Color::Teal;
			this->richTextBox1->AppendText(String::Concat("訊息:\t結束連線 (",i ,", ", ipClient[i], ", ", userClient[i], ")\n"));
			this->richTextBox1->Focus();
			this->richTextBox1->ScrollToCaret();
			
			for (int j = 0; j < connectAmount; j++)
			{
				if (i != j && threadConnect[j]->IsAlive && ipClient[j] == ipClient[i] && userClient[j] == userClient[i])
				{
					threadConnect[j]->Abort();
					closesocket(socketClient[j]);
				}
			}
			closesocket(socketClient[i]);

			id = listUser->LastIndexOf(userClient[i]);
			if (id >= 0)
			{
				listUser->RemoveAt(id);
				listIP->RemoveAt(id);
			}
			this->dataGridView1->Rows->Clear();
			for (int j = 0; j < listUser->Count; j++)
			{
				this->dataGridView1->Rows->Add(gcnew array<String^>{(String^)listUser[j], (String^)listIP[j], ""});
			}
			return;
		}

		this->richTextBox1->SelectionColor = Color::Blue;
		this->richTextBox1->AppendText(String::Concat("指令:\t", gcnew String(buffer), " (",i ,", ", ipClient[i], ", ", userClient[i], ")\n"));
		this->richTextBox1->Focus();
		this->richTextBox1->ScrollToCaret();

		if (!String::Compare(split[0], "PWD"))
		{
			DirectoryInfo^ dirInfo = gcnew DirectoryInfo(String::Concat(rootPath, dirCurrent));
			array<FileSystemInfo ^>^ dirEntries = dirInfo->GetDirectories();
			sprintf_s(buffer, "%d", dirEntries->Length);
			send(socketClient[i], buffer, MAX_MESSAGE, 0);
			recv(socketClient[i], buffer, MAX_MESSAGE, 0);
			for (int j = 0; j < dirEntries->Length; j++)
			{
				send(socketClient[i], (char*)(void*)Marshal::StringToHGlobalAnsi(dirEntries[j]->	Name), MAX_MESSAGE, 0);
				recv(socketClient[i], buffer, MAX_MESSAGE, 0);
			}
			
			array<FileSystemInfo ^>^ fileEntries = dirInfo->GetFiles();
			sprintf_s(buffer, "%d", fileEntries->Length);
			send(socketClient[i], buffer, MAX_MESSAGE, 0);
			recv(socketClient[i], buffer, MAX_MESSAGE, 0);
			for (int j = 0; j < fileEntries->Length; j++)
			{
				send(socketClient[i], (char*)(void*)Marshal::StringToHGlobalAnsi(fileEntries[j]->Name), MAX_MESSAGE, 0);
				recv(socketClient[i], buffer, MAX_MESSAGE, 0);
			}
			
			strcpy_s(buffer, MAX_MESSAGE, "257 \"");
			strcat_s(buffer, MAX_MESSAGE, (char*)(void*)Marshal::StringToHGlobalAnsi(dirCurrent));
			strcat_s(buffer, MAX_MESSAGE, "\" is current directory.");
			send(socketClient[i], buffer, MAX_MESSAGE, 0);
			this->richTextBox1->SelectionColor = Color::Green;
			this->richTextBox1->AppendText(String::Concat("回應:\t257 \"", dirCurrent, "\" is current directory. (",i ,", ", ipClient[i], ", ", userClient[i], ")\n"));
			this->richTextBox1->Focus();
			this->richTextBox1->ScrollToCaret();
		}
		else if (!String::Compare(split[0], "CWD"))
		{
			dirCurrent = String::Concat(dirCurrent, "/", split[1]);
			strcpy_s(buffer, MAX_MESSAGE, "257 \"");
			strcat_s(buffer, MAX_MESSAGE, (char*)(void*)Marshal::StringToHGlobalAnsi(dirCurrent));
			strcat_s(buffer, MAX_MESSAGE, "\" is current directory.");
			send(socketClient[i], buffer, MAX_MESSAGE, 0);
			this->richTextBox1->SelectionColor = Color::Green;
			this->richTextBox1->AppendText(String::Concat("回應:\t257 \"", dirCurrent, "\" is current directory. (",i ,", ", ipClient[i], ", ", userClient[i], ")\n"));
			this->richTextBox1->Focus();
			this->richTextBox1->ScrollToCaret();
		}
		else if (!String::Compare(split[0], "CDUP"))
		{
			if (String::Compare(dirCurrent, "/") && String::Compare(dirCurrent, ""))
			{
				dirCurrent = dirCurrent->String::Substring(0, dirCurrent->String::LastIndexOf('/'));
			}
			DirectoryInfo^ dirInfo = gcnew DirectoryInfo(String::Concat(rootPath, dirCurrent));
			array<FileSystemInfo ^>^ dirEntries = dirInfo->GetDirectories();
			sprintf_s(buffer, "%d", dirEntries->Length);
			send(socketClient[i], buffer, MAX_MESSAGE, 0);
			recv(socketClient[i], buffer, MAX_MESSAGE, 0);
			for (int j = 0; j < dirEntries->Length; j++)
			{
				send(socketClient[i], (char*)(void*)Marshal::StringToHGlobalAnsi(dirEntries[j]->	Name), MAX_MESSAGE, 0);
				recv(socketClient[i], buffer, MAX_MESSAGE, 0);
			}
			
			array<FileSystemInfo ^>^ fileEntries = dirInfo->GetFiles();
			sprintf_s(buffer, "%d", fileEntries->Length);
			send(socketClient[i], buffer, MAX_MESSAGE, 0);
			recv(socketClient[i], buffer, MAX_MESSAGE, 0);
			for (int j = 0; j < fileEntries->Length; j++)
			{
				send(socketClient[i], (char*)(void*)Marshal::StringToHGlobalAnsi(fileEntries[j]->	Name), MAX_MESSAGE, 0);
				recv(socketClient[i], buffer, MAX_MESSAGE, 0);
			}
			
			strcpy_s(buffer, MAX_MESSAGE, "257 \"");
			strcat_s(buffer, MAX_MESSAGE, (char*)(void*)Marshal::StringToHGlobalAnsi(dirCurrent));
			strcat_s(buffer, MAX_MESSAGE, "\" is current directory.");
			send(socketClient[i], buffer, MAX_MESSAGE, 0);
			this->richTextBox1->SelectionColor = Color::Green;
			this->richTextBox1->AppendText(String::Concat("回應:\t257 \"", dirCurrent, "\" is current directory. (",i ,", ", ipClient[i], ", ", userClient[i], ")\n"));
			this->richTextBox1->Focus();
			this->richTextBox1->ScrollToCaret();
		}
		else if (!String::Compare(split[0], "RETR"))
		{
			for (int j = 2; j < split->Length; j++)
			{
				split[1] = String::Concat(split[1], " ", split[j]);
			}
			FileInfo^ fileRequest;
			int fileSize = 0, startPos;
			if (File::Exists(String::Concat(rootPath, dirCurrent, "/", split[1])))
			{
				fileRequest = gcnew FileInfo(String::Concat(rootPath, "/", dirCurrent, "/", split[1]));
				fileSize = (int)fileRequest->Length;
			}

			sprintf_s(buffer, "150 Data connection accepted ; transfer starting for \"%s\" (%d bytes)", (char*)(void*)Marshal::StringToHGlobalAnsi(split[1]), fileSize);
			send(socketClient[i], buffer, MAX_MESSAGE, 0);
			this->richTextBox1->SelectionColor = Color::Green;
			this->richTextBox1->AppendText(String::Concat("回應:\t", gcnew String(buffer), " (",i ,", ", ipClient[i], ", ", userClient[i], ")\n"));
			this->richTextBox1->Focus();
			this->richTextBox1->ScrollToCaret();
			recv(socketClient[i], buffer, MAX_MESSAGE, 0);
			startPos = atoi(buffer);
			sprintf_s(buffer, "%d", fileSize);
			send(socketClient[i], buffer, MAX_MESSAGE, 0);

			if (fileSize > 0) {
				fstream file;
				file.open((char*)(void*)Marshal::StringToHGlobalAnsi(fileRequest->FullName), ios::in|ios::binary);
				file.seekg(startPos, ios::beg);

				while (!file.eof())
				{
					recv(socketClient[i], buffer, MAX_MESSAGE, 0);
					file.read(buffer, MAX_MESSAGE);
					send(socketClient[i], buffer, MAX_MESSAGE, 0);
				}
				file.close();
			}
			
			recv(socketClient[i], buffer, MAX_MESSAGE, 0);
			send(socketClient[i], "226 Transfer ok.", MAX_MESSAGE, 0);
			this->richTextBox1->SelectionColor = Color::Green;
			this->richTextBox1->AppendText(String::Concat("回應:\t226 Transfer ok. (",i ,", ", ipClient[i], ", ", userClient[i], ")\n"));
			this->richTextBox1->Focus();
			this->richTextBox1->ScrollToCaret();
			
			closesocket(socketClient[i]);
			return;
		}
		else if (!String::Compare(split[0], "SETR"))
		{
			for (int j = 2; j < split->Length; j++)
			{
				split[1] = String::Concat(split[1], " ", split[j]);
			}
			if (File::Exists(String::Concat(rootPath, dirCurrent, split[1])))
			{
				int s = fileName->LastIndexOf(Path::GetFullPath(String::Concat(rootPath, "/", dirCurrent, "/", split[1])));
				if (s < 0 || String::Compare((String^)fileUser[s], userClient[i]))
				{
					send(socketClient[i], "550 No permission.", MAX_MESSAGE, 0);
					this->richTextBox1->SelectionColor = Color::Green;
					this->richTextBox1->AppendText(String::Concat("回應:\t", gcnew String(buffer), " (",i ,", ", ipClient[i], ", ", userClient[i], ")\n"));
					this->richTextBox1->Focus();
					this->richTextBox1->ScrollToCaret();
					this->dataGridView1->Rows->Remove(viewRow[i]);
					closesocket(socketClient[i]);
					return;
				}
			}
			send(socketClient[i], "200 Command okay.", MAX_MESSAGE, 0);
			recv(socketClient[i], buffer, MAX_MESSAGE, 0);
			int fileSize, remain, startPos;
			fileSize = atoi(buffer);

			sprintf_s(buffer, "150 Data connection accepted ; transfer starting for \"%s\" (%d bytes)", (char*)(void*)Marshal::StringToHGlobalAnsi(split[1]), fileSize);
			send(socketClient[i], buffer, MAX_MESSAGE, 0);
			this->richTextBox1->SelectionColor = Color::Green;
			this->richTextBox1->AppendText(String::Concat("回應:\t", gcnew String(buffer), " (",i ,", ", ipClient[i], ", ", userClient[i], ")\n"));
			this->richTextBox1->Focus();
			this->richTextBox1->ScrollToCaret();

			recv(socketClient[i], buffer, MAX_MESSAGE, 0);
			send(socketClient[i], "200 Command okay.", MAX_MESSAGE, 0);
			startPos = atoi(buffer);
			remain = fileSize - startPos;
			
			fstream file;
			if (startPos == 0)
			{
				file.open((char*)(void*)Marshal::StringToHGlobalAnsi(String::Concat(rootPath, dirCurrent, split[1])), ios::out|ios::binary);
			}
			else
			{
				file.open((char*)(void*)Marshal::StringToHGlobalAnsi(String::Concat(rootPath, dirCurrent, split[1])), ios::out|ios::in|ios::binary);
			}
			file.seekg(startPos, ios::beg);

			StreamWriter^ fileWrite = gcnew StreamWriter("file.dat", true, System::Text::Encoding::Default);
			fileWrite->WriteLine(String::Concat(userClient[i], "\t", Path::GetFullPath(String::Concat(rootPath, dirCurrent, split[1]))));
			fileWrite->Flush();
			fileWrite->Close();

			fileUser->Add(userClient[i]);
			fileName->Add(Path::GetFullPath(String::Concat(rootPath, dirCurrent, split[1])));

			while (remain > 0)
			{
				recv(socketClient[i], buffer, MAX_MESSAGE, 0);
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
				send(socketClient[i], "200 Command okay.", MAX_MESSAGE, 0);
			}
			file.close();

			recv(socketClient[i], buffer, MAX_MESSAGE, 0);
			send(socketClient[i], "226 Transfer ok.", MAX_MESSAGE, 0);
			this->richTextBox1->SelectionColor = Color::Green;
			this->richTextBox1->AppendText(String::Concat("回應:\t226 Transfer ok. (",i ,", ", ipClient[i], ", ", userClient[i], ")\n"));
			this->richTextBox1->Focus();
			this->richTextBox1->ScrollToCaret();
			
			closesocket(socketClient[i]);
			return;
		}
		else if (!String::Compare(split[0], "DELE"))
		{
			for (int j = 2; j < split->Length; j++)
			{
				split[1] = String::Concat(split[1], " ", split[j]);
			}
			if (File::Exists(String::Concat(rootPath, "/", dirCurrent, "/", split[1])))
			{
				int s = fileName->LastIndexOf(Path::GetFullPath(String::Concat(rootPath, "/", dirCurrent, "/", split[1])));
				if (s >= 0 && !String::Compare((String^)fileUser[s], userClient[i]))
				{
					File::Delete(String::Concat(rootPath, "/", dirCurrent, "/", split[1]));
					sprintf_s(buffer, "250 File \"%s\" deleted.", (char*)(void*)Marshal::StringToHGlobalAnsi(split[1]));
					send(socketClient[i], buffer, MAX_MESSAGE, 0);
				}
				else
				{
					sprintf_s(buffer, "550 Cannot delete %s. No permission.", (char*)(void*)Marshal::StringToHGlobalAnsi(split[1]));
					send(socketClient[i], buffer, MAX_MESSAGE, 0);
				}
				this->richTextBox1->SelectionColor = Color::Green;
				this->richTextBox1->AppendText(String::Concat("回應:\t", gcnew String(buffer), " (",i ,", ", ipClient[i], ", ", userClient[i], ")\n"));
				this->richTextBox1->Focus();
				this->richTextBox1->ScrollToCaret();
			}
			else
			{
				sprintf_s(buffer, "550 \"%s\": no such file.", (char*)(void*)Marshal::StringToHGlobalAnsi(split[1]));
				send(socketClient[i], buffer, MAX_MESSAGE, 0);
				this->richTextBox1->SelectionColor = Color::Green;
				this->richTextBox1->AppendText(String::Concat("回應:\t", gcnew String(buffer), " (",i ,", ", ipClient[i], ", ", userClient[i], ")\n"));
				this->richTextBox1->Focus();
				this->richTextBox1->ScrollToCaret();
			}
		}
		else
		{
			this->richTextBox1->SelectionColor = Color::Green;
			this->richTextBox1->AppendText(String::Concat("回應:\t230 500 Command unrecognized. (",i ,", ", ipClient[i], ", ", userClient[i], ")\n"));
			this->richTextBox1->Focus();
			this->richTextBox1->ScrollToCaret();
			send(socketClient[i], "500 Command unrecognized.", MAX_MESSAGE, 0);
		}
	}
}

}