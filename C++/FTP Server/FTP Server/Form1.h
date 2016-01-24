#include <winsock2.h>
#include <stdlib.h>
#include <string>
#include <io.h>
#include <iostream>
#include <fstream>

#pragma once

#define SERVER_PORT 5432
#define MAX_MESSAGE 1024

namespace FTPServer {
	
	using namespace std;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;


	SOCKET socket_i[4];

	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			host = gcnew array<System::String ^>(4);
			socket_ib = gcnew array<bool>(4);
			for (int i = 0; i < 4; i++) socket_ib[i] = false;
		}

	protected:
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: 
		System::Windows::Forms::StatusStrip^  statusStrip1;
		System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel1;
		System::ComponentModel::BackgroundWorker^  backgroundWorker1;
		System::ComponentModel::BackgroundWorker^  backgroundWorker2;
		System::ComponentModel::BackgroundWorker^  backgroundWorker3;
		System::ComponentModel::BackgroundWorker^  backgroundWorker4;
		System::ComponentModel::BackgroundWorker^  backgroundWorker5;
		System::ComponentModel::Container ^components;

	private:
		array<System::String ^>^ host;
		array<bool>^ socket_ib;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripStatusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->backgroundWorker2 = (gcnew System::ComponentModel::BackgroundWorker());
			this->backgroundWorker3 = (gcnew System::ComponentModel::BackgroundWorker());
			this->backgroundWorker4 = (gcnew System::ComponentModel::BackgroundWorker());
			this->backgroundWorker5 = (gcnew System::ComponentModel::BackgroundWorker());
			this->statusStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// statusStrip1
			// 
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->toolStripStatusLabel1});
			this->statusStrip1->Location = System::Drawing::Point(0, 20);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Size = System::Drawing::Size(284, 22);
			this->statusStrip1->TabIndex = 0;
			this->statusStrip1->Text = L"statusStrip1";
			// 
			// toolStripStatusLabel1
			// 
			this->toolStripStatusLabel1->Name = L"toolStripStatusLabel1";
			this->toolStripStatusLabel1->Size = System::Drawing::Size(55, 17);
			this->toolStripStatusLabel1->Text = L"Standby";
			// 
			// backgroundWorker1
			// 
			this->backgroundWorker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::backgroundWorker1_DoWork);
			// 
			// backgroundWorker2
			// 
			this->backgroundWorker2->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::backgroundWorker2_DoWork);
			this->backgroundWorker2->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Form1::backgroundWorker2_RunWorkerCompleted);
			// 
			// backgroundWorker3
			// 
			this->backgroundWorker3->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::backgroundWorker3_DoWork);
			this->backgroundWorker2->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Form1::backgroundWorker3_RunWorkerCompleted);
			// 
			// backgroundWorker4
			// 
			this->backgroundWorker4->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::backgroundWorker4_DoWork);
			this->backgroundWorker2->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Form1::backgroundWorker4_RunWorkerCompleted);
			// 
			// backgroundWorker5
			// 
			this->backgroundWorker5->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::backgroundWorker5_DoWork);
			this->backgroundWorker2->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Form1::backgroundWorker5_RunWorkerCompleted);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 42);
			this->Controls->Add(this->statusStrip1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"Form1";
			this->Text = L"File Transfer Server";
			this->Shown += gcnew System::EventHandler(this, &Form1::Form1_Shown);
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: 
		System::Void backgroundWorker1_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
			WSADATA info;
			if (WSAStartup(MAKEWORD(1,1), &info) !=0) {
				Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), "Error: Winsock startup failed.");
				this->backgroundWorker1->CancelAsync();
			} else {
				

				struct sockaddr_in server_address;
				struct sockaddr_in client_address;
				SOCKET socket_s;
				
				server_address.sin_family = AF_INET;
				server_address.sin_addr.s_addr = INADDR_ANY;
				server_address.sin_port = htons(SERVER_PORT);
				memset(&(server_address.sin_zero),'\0', 8);

				socket_s = socket(PF_INET, SOCK_STREAM, 0);
				if (socket_s == INVALID_SOCKET) {
					Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), "Error: Socket creation failed.");
					this->backgroundWorker1->CancelAsync();
				} else if (bind(socket_s, (struct sockaddr *)&server_address, sizeof(server_address)) == SOCKET_ERROR) {
					Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), "Error: Bind failed.");
					this->backgroundWorker1->CancelAsync();
				} else {
					Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), "Ready");
					int len = sizeof(client_address);

					while (1) {
						listen(socket_s, 4);

						if (socket_ib[0] == false) {
							socket_i[0] = accept(socket_s, (struct sockaddr *)&client_address, &len);
							if (socket_i[0] == INVALID_SOCKET) {
								Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), String::Concat("Error: Connect failed from ", gcnew String(inet_ntoa(client_address.sin_addr)), "."));
							} else {
								socket_ib[0] = true;
								host[0] = gcnew String(inet_ntoa(client_address.sin_addr));
								Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), String::Concat("Connected from ", gcnew String(inet_ntoa(client_address.sin_addr)), "."));
								this->backgroundWorker2->RunWorkerAsync();
							}
						} else if (socket_ib[1] == false) {
							socket_i[1] = accept(socket_s, (struct sockaddr *)&client_address, &len);
							if (socket_i[1] == INVALID_SOCKET) {
								Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), String::Concat("Error: Connect failed from ", gcnew String(inet_ntoa(client_address.sin_addr)), "."));
							} else {
								socket_ib[1] = true;
								host[1] = gcnew String(inet_ntoa(client_address.sin_addr));
								Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), String::Concat("Connected from ", gcnew String(inet_ntoa(client_address.sin_addr)), "."));
								this->backgroundWorker3->RunWorkerAsync();
							}
						} else if (socket_ib[2] == false) {
							socket_i[2] = accept(socket_s, (struct sockaddr *)&client_address, &len);
							if (socket_i[2] == INVALID_SOCKET) {
								Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), String::Concat("Error: Connect failed from ", gcnew String(inet_ntoa(client_address.sin_addr)), "."));
							} else {
								socket_ib[2] = true;
								host[2] = gcnew String(inet_ntoa(client_address.sin_addr));
								Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), String::Concat("Connected from ", gcnew String(inet_ntoa(client_address.sin_addr)), "."));
								this->backgroundWorker4->RunWorkerAsync();
							}
						} else if (socket_ib[3] == false) {
							socket_i[3] = accept(socket_s, (struct sockaddr *)&client_address, &len);
							if (socket_i[3] == INVALID_SOCKET) {
								Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), String::Concat("Error: Connect failed from ", gcnew String(inet_ntoa(client_address.sin_addr)), "."));
							} else {
								socket_ib[3] = true;
								host[3] = gcnew String(inet_ntoa(client_address.sin_addr));
								Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), String::Concat("Connected from ", gcnew String(inet_ntoa(client_address.sin_addr)), "."));
								this->backgroundWorker5->RunWorkerAsync();
							}
						} else {
							Sleep(100);
							Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), String::Concat("Error: Connect failed from ", gcnew String(inet_ntoa(client_address.sin_addr)), "."));
						}
					}
					closesocket(socket_s);
					WSACleanup();
				}
			}
		}

		System::Void backgroundWorker2_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
			int bgw = 0;
			char buffer[MAX_MESSAGE];
			int n = recv(socket_i[bgw], buffer, MAX_MESSAGE, 0);
			if (n > 0 && !strcmp(buffer, "/GETDIR")) {
				long hdir = 0;
				struct _finddata_t dirinfo;
				if((hdir = _findfirst("./*", &dirinfo)) != -1) {
					do {
						if(!(dirinfo.attrib & _A_SUBDIR) && strcmp(dirinfo.name, ".") && strcmp(dirinfo.name, "..")) {
							send(socket_i[bgw], dirinfo.name, MAX_MESSAGE, 0);
							recv(socket_i[bgw], buffer, MAX_MESSAGE, 0);
						}
					} while(_findnext(hdir, &dirinfo) == 0);
				}
				send(socket_i[bgw], "/FIN", MAX_MESSAGE, 0);
				Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), String::Concat("Send dirinfo to ", host[bgw], "."));
			} else if (n > 0 && !strcmp(buffer, "/DLFILE")) {
				send(socket_i[bgw], "/ACCEPT", MAX_MESSAGE, 0);
				recv(socket_i[bgw], buffer, MAX_MESSAGE, 0);
				fstream fs;
				fs.open(buffer, ios::in|ios::binary);
				if (fs.is_open()) {

					Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), String::Concat("Send ", gcnew String(buffer), " to ", host[bgw], "."));

					fs.seekg(0, ios::end);
					int bytes = (int)fs.tellg();
					fs.seekg(0, ios::beg);
					_itoa_s(bytes, buffer, 10);
					send(socket_i[bgw], buffer, MAX_MESSAGE, 0);
					
					while (!fs.eof()) {
						recv(socket_i[bgw], buffer, MAX_MESSAGE, 0);
						fs.read(buffer, MAX_MESSAGE);
						send(socket_i[bgw], buffer, MAX_MESSAGE, 0);
					}
					fs.close();

				} else {
					send(socket_i[bgw], "0", MAX_MESSAGE, 0);
				}
			} else if (n > 0 && !strcmp(buffer, "/ULFILE")) {
				send(socket_i[bgw], "/ACCEPT", MAX_MESSAGE, 0);
				recv(socket_i[bgw], buffer, MAX_MESSAGE, 0);
				fstream fs;
				fs.open(buffer, ios::out|ios::binary);
				Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), String::Concat("Recvice ", gcnew String(buffer), " from ", host[bgw], "."));
				send(socket_i[bgw], "/ACCEPT", MAX_MESSAGE, 0);
				recv(socket_i[bgw], buffer, MAX_MESSAGE, 0);
				int remain = atoi(buffer);

				while (remain > 0) {
					send(socket_i[bgw], "/ACCEPT", MAX_MESSAGE, 0);
					recv(socket_i[bgw], buffer, MAX_MESSAGE, 0);
					if (remain < MAX_MESSAGE) {
						fs.write(buffer, remain);
						remain = 0;
					} else {
						remain -= MAX_MESSAGE;
						fs.write(buffer, MAX_MESSAGE);
					}
				}
				fs.close();
			}

			socket_ib[bgw] = false;
		}

		System::Void backgroundWorker3_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
			int bgw = 1;
			char buffer[MAX_MESSAGE];
			int n = recv(socket_i[bgw], buffer, MAX_MESSAGE, 0);
			if (n > 0 && !strcmp(buffer, "/GETDIR")) {
				long hdir = 0;
				struct _finddata_t dirinfo;
				if((hdir = _findfirst("./*", &dirinfo)) != -1) {
					do {
						if(!(dirinfo.attrib & _A_SUBDIR) && strcmp(dirinfo.name, ".") && strcmp(dirinfo.name, "..")) {
							send(socket_i[bgw], dirinfo.name, MAX_MESSAGE, 0);
							recv(socket_i[bgw], buffer, MAX_MESSAGE, 0);
						}
					} while(_findnext(hdir, &dirinfo) == 0);
				}
				send(socket_i[bgw], "/FIN", MAX_MESSAGE, 0);
				Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), String::Concat("Send dirinfo to ", host[bgw], "."));
			} else if (n > 0 && !strcmp(buffer, "/DLFILE")) {
				send(socket_i[bgw], "/ACCEPT", MAX_MESSAGE, 0);
				recv(socket_i[bgw], buffer, MAX_MESSAGE, 0);
				fstream fs;
				fs.open(buffer, ios::in|ios::binary);
				if (fs.is_open()) {

					Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), String::Concat("Send ", gcnew String(buffer), " to ", host[bgw], "."));

					fs.seekg(0, ios::end);
					int bytes = (int)fs.tellg();
					fs.seekg(0, ios::beg);
					_itoa_s(bytes, buffer, 10);
					send(socket_i[bgw], buffer, MAX_MESSAGE, 0);
					
					while (!fs.eof()) {
						recv(socket_i[bgw], buffer, MAX_MESSAGE, 0);
						fs.read(buffer, MAX_MESSAGE);
						send(socket_i[bgw], buffer, MAX_MESSAGE, 0);
					}
					fs.close();

				} else {
					send(socket_i[bgw], "0", MAX_MESSAGE, 0);
				}
			} else if (n > 0 && !strcmp(buffer, "/ULFILE")) {
				send(socket_i[bgw], "/ACCEPT", MAX_MESSAGE, 0);
				recv(socket_i[bgw], buffer, MAX_MESSAGE, 0);
				fstream fs;
				fs.open(buffer, ios::out|ios::binary);
				send(socket_i[bgw], "/ACCEPT", MAX_MESSAGE, 0);
				recv(socket_i[bgw], buffer, MAX_MESSAGE, 0);
				int remain = atoi(buffer);

				while (remain > 0) {
					send(socket_i[bgw], "/ACCEPT", MAX_MESSAGE, 0);
					recv(socket_i[bgw], buffer, MAX_MESSAGE, 0);
					if (remain < MAX_MESSAGE) {
						fs.write(buffer, remain);
						remain = 0;
					} else {
						remain -= MAX_MESSAGE;
						fs.write(buffer, MAX_MESSAGE);
					}
				}
				fs.close();
			}

			socket_ib[bgw] = false;
		}

		System::Void backgroundWorker4_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
			int bgw = 2;
			char buffer[MAX_MESSAGE];
			int n = recv(socket_i[bgw], buffer, MAX_MESSAGE, 0);
			if (n > 0 && !strcmp(buffer, "/GETDIR")) {
				long hdir = 0;
				struct _finddata_t dirinfo;
				if((hdir = _findfirst("./*", &dirinfo)) != -1) {
					do {
						if(!(dirinfo.attrib & _A_SUBDIR) && strcmp(dirinfo.name, ".") && strcmp(dirinfo.name, "..")) {
							send(socket_i[bgw], dirinfo.name, MAX_MESSAGE, 0);
							recv(socket_i[bgw], buffer, MAX_MESSAGE, 0);
						}
					} while(_findnext(hdir, &dirinfo) == 0);
				}
				send(socket_i[bgw], "/FIN", MAX_MESSAGE, 0);
				Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), String::Concat("Send dirinfo to ", host[bgw], "."));
			} else if (n > 0 && !strcmp(buffer, "/DLFILE")) {
				send(socket_i[bgw], "/ACCEPT", MAX_MESSAGE, 0);
				recv(socket_i[bgw], buffer, MAX_MESSAGE, 0);
				fstream fs;
				fs.open(buffer, ios::in|ios::binary);
				if (fs.is_open()) {

					Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), String::Concat("Send ", gcnew String(buffer), " to ", host[bgw], "."));

					fs.seekg(0, ios::end);
					int bytes = (int)fs.tellg();
					fs.seekg(0, ios::beg);
					_itoa_s(bytes, buffer, 10);
					send(socket_i[bgw], buffer, MAX_MESSAGE, 0);
					
					while (!fs.eof()) {
						recv(socket_i[bgw], buffer, MAX_MESSAGE, 0);
						fs.read(buffer, MAX_MESSAGE);
						send(socket_i[bgw], buffer, MAX_MESSAGE, 0);
					}
					fs.close();

				} else {
					send(socket_i[bgw], "0", MAX_MESSAGE, 0);
				}
			} else if (n > 0 && !strcmp(buffer, "/ULFILE")) {
				send(socket_i[bgw], "/ACCEPT", MAX_MESSAGE, 0);
				recv(socket_i[bgw], buffer, MAX_MESSAGE, 0);
				fstream fs;
				fs.open(buffer, ios::out|ios::binary);
				send(socket_i[bgw], "/ACCEPT", MAX_MESSAGE, 0);
				recv(socket_i[bgw], buffer, MAX_MESSAGE, 0);
				int remain = atoi(buffer);

				while (remain > 0) {
					send(socket_i[bgw], "/ACCEPT", MAX_MESSAGE, 0);
					recv(socket_i[bgw], buffer, MAX_MESSAGE, 0);
					if (remain < MAX_MESSAGE) {
						fs.write(buffer, remain);
						remain = 0;
					} else {
						remain -= MAX_MESSAGE;
						fs.write(buffer, MAX_MESSAGE);
					}
				}
				fs.close();
			}

			socket_ib[bgw] = false;
		}

		System::Void backgroundWorker5_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
			int bgw = 3;
			char buffer[MAX_MESSAGE];
			int n = recv(socket_i[bgw], buffer, MAX_MESSAGE, 0);
			if (n > 0 && !strcmp(buffer, "/GETDIR")) {
				long hdir = 0;
				struct _finddata_t dirinfo;
				if((hdir = _findfirst("./*", &dirinfo)) != -1) {
					do {
						if(!(dirinfo.attrib & _A_SUBDIR) && strcmp(dirinfo.name, ".") && strcmp(dirinfo.name, "..")) {
							send(socket_i[bgw], dirinfo.name, MAX_MESSAGE, 0);
							recv(socket_i[bgw], buffer, MAX_MESSAGE, 0);
						}
					} while(_findnext(hdir, &dirinfo) == 0);
				}
				send(socket_i[bgw], "/FIN", MAX_MESSAGE, 0);
				Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), String::Concat("Send dirinfo to ", host[bgw], "."));
			} else if (n > 0 && !strcmp(buffer, "/DLFILE")) {
				send(socket_i[bgw], "/ACCEPT", MAX_MESSAGE, 0);
				recv(socket_i[bgw], buffer, MAX_MESSAGE, 0);
				fstream fs;
				fs.open(buffer, ios::in|ios::binary);
				if (fs.is_open()) {

					Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), String::Concat("Send ", gcnew String(buffer), " to ", host[bgw], "."));

					fs.seekg(0, ios::end);
					int bytes = (int)fs.tellg();
					fs.seekg(0, ios::beg);
					_itoa_s(bytes, buffer, 10);
					send(socket_i[bgw], buffer, MAX_MESSAGE, 0);
					
					while (!fs.eof()) {
						recv(socket_i[bgw], buffer, MAX_MESSAGE, 0);
						fs.read(buffer, MAX_MESSAGE);
						send(socket_i[bgw], buffer, MAX_MESSAGE, 0);
					}
					fs.close();

				} else {
					send(socket_i[bgw], "0", MAX_MESSAGE, 0);
				}
			} else if (n > 0 && !strcmp(buffer, "/ULFILE")) {
				send(socket_i[bgw], "/ACCEPT", MAX_MESSAGE, 0);
				recv(socket_i[bgw], buffer, MAX_MESSAGE, 0);
				fstream fs;
				fs.open(buffer, ios::out|ios::binary);
				send(socket_i[bgw], "/ACCEPT", MAX_MESSAGE, 0);
				recv(socket_i[bgw], buffer, MAX_MESSAGE, 0);
				int remain = atoi(buffer);

				while (remain > 0) {
					send(socket_i[bgw], "/ACCEPT", MAX_MESSAGE, 0);
					recv(socket_i[bgw], buffer, MAX_MESSAGE, 0);
					if (remain < MAX_MESSAGE) {
						fs.write(buffer, remain);
						remain = 0;
					} else {
						remain -= MAX_MESSAGE;
						fs.write(buffer, MAX_MESSAGE);
					}
				}
				fs.close();
			}

			socket_ib[bgw] = false;
		}
		System::Void backgroundWorker2_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) {
			socket_ib[0] = false;
		}
		System::Void backgroundWorker3_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) {
			socket_ib[1] = false;
		}
		System::Void backgroundWorker4_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) {
			socket_ib[2] = false;
		}
		System::Void backgroundWorker5_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) {
			socket_ib[3] = false;
		}

		System::Void Form1_Shown(System::Object^  sender, System::EventArgs^  e) {
			this->backgroundWorker1->RunWorkerAsync();
		}
	private: 
		delegate void SetTextDelegate(System::String^ s);
	    void SettoolStripStatusLabel1Text(System::String^ s) {
			toolStripStatusLabel1->Text = s;
		}
};
}

