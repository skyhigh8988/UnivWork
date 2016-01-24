#include <winsock2.h>
#include <io.h>
#include <iostream>
#include <fstream>
#include "Form2.h"

#pragma once

#define SERVER_PORT 5432
#define MAX_MESSAGE 1024

namespace FTPClient {

	using namespace std;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;

	WSADATA info;

	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			file_n = gcnew array<System::String ^>(4);
			file_t = gcnew array<bool>(4);
			file_d = gcnew array<bool>(4);
			for (int i = 0; i < 4; i++) file_t[i] = false;
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
		System::ComponentModel::Container ^components;
		System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel1;
		System::Windows::Forms::CheckedListBox^  checkedListBox1;
		System::Windows::Forms::CheckedListBox^  checkedListBox2;
		System::Windows::Forms::ProgressBar^  progressBar1;
		System::Windows::Forms::ProgressBar^  progressBar2;
		System::Windows::Forms::ProgressBar^  progressBar3;
		System::Windows::Forms::ProgressBar^  progressBar4;
		System::Windows::Forms::Label^  label1;
		System::Windows::Forms::Label^  label2;
		System::Windows::Forms::Label^  label3;
		System::Windows::Forms::Label^  label4;
		System::Windows::Forms::Button^  button1;
		System::Windows::Forms::Button^  button2;
		System::Windows::Forms::Button^  button3;
		System::Windows::Forms::Label^  label5;
		System::Windows::Forms::Label^  label6;
		System::Windows::Forms::Label^  label7;
		System::Windows::Forms::Label^  label8;
		System::ComponentModel::BackgroundWorker^  backgroundWorker1;
		System::ComponentModel::BackgroundWorker^  backgroundWorker2;
		System::ComponentModel::BackgroundWorker^  backgroundWorker3;
		System::ComponentModel::BackgroundWorker^  backgroundWorker4;
		System::ComponentModel::BackgroundWorker^  backgroundWorker5;

	private:
		System::String^ host;
		System::String^ port;
		array<System::String ^>^ file_n;
		array<bool>^ file_t;
		array<bool>^ file_d;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripStatusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->checkedListBox1 = (gcnew System::Windows::Forms::CheckedListBox());
			this->checkedListBox2 = (gcnew System::Windows::Forms::CheckedListBox());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->progressBar2 = (gcnew System::Windows::Forms::ProgressBar());
			this->progressBar3 = (gcnew System::Windows::Forms::ProgressBar());
			this->progressBar4 = (gcnew System::Windows::Forms::ProgressBar());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
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
			this->statusStrip1->Location = System::Drawing::Point(0, 540);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Size = System::Drawing::Size(784, 22);
			this->statusStrip1->TabIndex = 0;
			this->statusStrip1->Text = L"statusStrip1";
			// 
			// toolStripStatusLabel1
			// 
			this->toolStripStatusLabel1->Name = L"toolStripStatusLabel1";
			this->toolStripStatusLabel1->Size = System::Drawing::Size(44, 17);
			this->toolStripStatusLabel1->Text = L"Ready";
			// 
			// checkedListBox1
			// 
			this->checkedListBox1->CheckOnClick = true;
			this->checkedListBox1->Font = (gcnew System::Drawing::Font(L"新細明體", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->checkedListBox1->FormattingEnabled = true;
			this->checkedListBox1->Location = System::Drawing::Point(12, 12);
			this->checkedListBox1->Name = L"checkedListBox1";
			this->checkedListBox1->ScrollAlwaysVisible = true;
			this->checkedListBox1->Size = System::Drawing::Size(360, 382);
			this->checkedListBox1->TabIndex = 1;
			// 
			// checkedListBox2
			// 
			this->checkedListBox2->CheckOnClick = true;
			this->checkedListBox2->Font = (gcnew System::Drawing::Font(L"新細明體", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->checkedListBox2->FormattingEnabled = true;
			this->checkedListBox2->Location = System::Drawing::Point(412, 12);
			this->checkedListBox2->Name = L"checkedListBox2";
			this->checkedListBox2->ScrollAlwaysVisible = true;
			this->checkedListBox2->Size = System::Drawing::Size(360, 382);
			this->checkedListBox2->TabIndex = 2;
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(179, 415);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(426, 23);
			this->progressBar1->TabIndex = 3;
			// 
			// progressBar2
			// 
			this->progressBar2->Location = System::Drawing::Point(179, 445);
			this->progressBar2->Name = L"progressBar2";
			this->progressBar2->Size = System::Drawing::Size(426, 23);
			this->progressBar2->TabIndex = 4;
			// 
			// progressBar3
			// 
			this->progressBar3->Location = System::Drawing::Point(179, 475);
			this->progressBar3->Name = L"progressBar3";
			this->progressBar3->Size = System::Drawing::Size(426, 23);
			this->progressBar3->TabIndex = 5;
			// 
			// progressBar4
			// 
			this->progressBar4->Location = System::Drawing::Point(179, 505);
			this->progressBar4->Name = L"progressBar4";
			this->progressBar4->Size = System::Drawing::Size(426, 23);
			this->progressBar4->TabIndex = 6;
			// 
			// label1
			// 
			this->label1->AutoEllipsis = true;
			this->label1->Location = System::Drawing::Point(13, 419);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(160, 23);
			this->label1->TabIndex = 7;
			this->label1->Text = L"[Idle]";
			// 
			// label2
			// 
			this->label2->AutoEllipsis = true;
			this->label2->Location = System::Drawing::Point(13, 450);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(160, 23);
			this->label2->TabIndex = 8;
			this->label2->Text = L"[Idle]";
			// 
			// label3
			// 
			this->label3->AutoEllipsis = true;
			this->label3->Location = System::Drawing::Point(13, 480);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(160, 23);
			this->label3->TabIndex = 9;
			this->label3->Text = L"[Idle]";
			// 
			// label4
			// 
			this->label4->AutoEllipsis = true;
			this->label4->Location = System::Drawing::Point(13, 510);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(160, 23);
			this->label4->TabIndex = 10;
			this->label4->Text = L"[Idle]";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(379, 139);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(27, 23);
			this->button1->TabIndex = 11;
			this->button1->Text = L"R";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(379, 168);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(27, 23);
			this->button2->TabIndex = 12;
			this->button2->Text = L"→";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(379, 197);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(27, 23);
			this->button3->TabIndex = 13;
			this->button3->Text = L"←";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// label5
			// 
			this->label5->AutoEllipsis = true;
			this->label5->Location = System::Drawing::Point(614, 419);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(160, 23);
			this->label5->TabIndex = 14;
			this->label5->Text = L"0% (0 / 0)";
			// 
			// label6
			// 
			this->label6->AutoEllipsis = true;
			this->label6->Location = System::Drawing::Point(614, 450);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(160, 23);
			this->label6->TabIndex = 15;
			this->label6->Text = L"0% (0 / 0)";
			// 
			// label7
			// 
			this->label7->AutoEllipsis = true;
			this->label7->Location = System::Drawing::Point(614, 480);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(160, 23);
			this->label7->TabIndex = 16;
			this->label7->Text = L"0% (0 / 0)";
			// 
			// label8
			// 
			this->label8->AutoEllipsis = true;
			this->label8->Location = System::Drawing::Point(614, 510);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(160, 23);
			this->label8->TabIndex = 17;
			this->label8->Text = L"0% (0 / 0)";
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
			this->backgroundWorker3->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Form1::backgroundWorker3_RunWorkerCompleted);
			// 
			// backgroundWorker4
			// 
			this->backgroundWorker4->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::backgroundWorker4_DoWork);
			this->backgroundWorker4->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Form1::backgroundWorker4_RunWorkerCompleted);
			// 
			// backgroundWorker5
			// 
			this->backgroundWorker5->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::backgroundWorker5_DoWork);
			this->backgroundWorker5->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Form1::backgroundWorker5_RunWorkerCompleted);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(784, 562);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->progressBar4);
			this->Controls->Add(this->progressBar3);
			this->Controls->Add(this->progressBar2);
			this->Controls->Add(this->progressBar1);
			this->Controls->Add(this->checkedListBox2);
			this->Controls->Add(this->checkedListBox1);
			this->Controls->Add(this->statusStrip1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"Form1";
			this->Text = L"File Transfer Client";
			this->Shown += gcnew System::EventHandler(this, &Form1::Form1_Shown);
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: 
		System::Void Form1_Shown(System::Object^  sender, System::EventArgs^  e) {
			this->Enabled = false;
			Form2^ f2 = gcnew Form2();
			if(f2->ShowDialog(this) == System::Windows::Forms::DialogResult::Cancel) {
				this->Close();
			} else {
				this->Enabled = true;
				host = f2->textBox1->Text;
				port = f2->textBox2->Text;

				if (WSAStartup(MAKEWORD(1,1), &info) !=0) {
					Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), "Error: Winsock startup failed.");
				} else {
					this->backgroundWorker1->RunWorkerAsync();
				}
			}
		}

		System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			if (!backgroundWorker1->IsBusy) this->backgroundWorker1->RunWorkerAsync();
		}

		System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
			IEnumerator^ selectFile = checkedListBox1->CheckedItems->GetEnumerator();
			while (selectFile->MoveNext()) {
				if (file_t[0] == false) {
					file_n[0] = safe_cast<String^>(selectFile->Current);
					file_d[0] = true;
					file_t[0] = true;
					this->backgroundWorker2->RunWorkerAsync();
				} else if (file_t[1] == false) {
					file_n[1] = safe_cast<String^>(selectFile->Current);
					file_d[1] = true;
					file_t[1] = true;
					this->backgroundWorker3->RunWorkerAsync();
				} else if (file_t[2] == false) {
					file_n[2] = safe_cast<String^>(selectFile->Current);
					file_d[2] = true;
					file_t[2] = true;
					this->backgroundWorker4->RunWorkerAsync();
				} else if (file_t[3] == false) {
					file_n[3] = safe_cast<String^>(selectFile->Current);
					file_d[3] = true;
					file_t[3] = true;
					this->backgroundWorker5->RunWorkerAsync();
				} else {
					Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), "Too many thread.");
					break;
				}
				Sleep(500);
			}
		}

		System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
			IEnumerator^ selectFile = checkedListBox2->CheckedItems->GetEnumerator();
			while (selectFile->MoveNext()) {
				if (file_t[0] == false) {
					file_n[0] = safe_cast<String^>(selectFile->Current);
					file_d[0] = false;
					file_t[0] = true;
					this->backgroundWorker2->RunWorkerAsync();
				} else if (file_t[1] == false) {
					file_n[1] = safe_cast<String^>(selectFile->Current);
					file_d[1] = false;
					file_t[1] = true;
					this->backgroundWorker3->RunWorkerAsync();
				} else if (file_t[2] == false) {
					file_n[2] = safe_cast<String^>(selectFile->Current);
					file_d[2] = false;
					file_t[2] = true;
					this->backgroundWorker4->RunWorkerAsync();
				} else if (file_t[3] == false) {
					file_n[3] = safe_cast<String^>(selectFile->Current);
					file_d[3] = false;
					file_t[3] = true;
					this->backgroundWorker5->RunWorkerAsync();
				} else {
					Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), "Too many thread.");
					break;
				}
			}
		}

		System::Void backgroundWorker1_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {

			Invoke(gcnew SetDelegate(this, &Form1::clearCheckedListBox2Item));
			long hdir = 0;
			struct _finddata_t dirinfo;
			if((hdir = _findfirst("./*", &dirinfo)) != -1) {
				do {
					if(!(dirinfo.attrib & _A_SUBDIR) && strcmp(dirinfo.name, ".") && strcmp(dirinfo.name, "..")) {
						Invoke(gcnew SetTextDelegate(this, &Form1::addCheckedListBox2Item), gcnew String(dirinfo.name));
					}
				} while(_findnext(hdir, &dirinfo) == 0);
			}

			struct hostent *hp;
			hp = gethostbyname((char*)(void*)Marshal::StringToHGlobalAnsi(host));
			if (!hp) {
				Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), "Error: Unknow server.");
				this->backgroundWorker1->CancelAsync();
			}

			SOCKET socket_s;
			struct sockaddr_in server_address;
			server_address.sin_family = AF_INET;
			server_address.sin_addr = *((struct in_addr *)hp->h_addr);
			server_address.sin_port = htons(System::Int32::Parse(port));
			memset(&(server_address.sin_zero), '\0', 8);

			socket_s = socket(PF_INET, SOCK_STREAM, 0);
			if (socket_s == INVALID_SOCKET) {
				Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), "Error: Socket creation failed.");
				this->backgroundWorker1->CancelAsync();
			}
			if (connect(socket_s, (struct sockaddr *)&server_address, sizeof(server_address)) == SOCKET_ERROR) {
				Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), "Error: Connecting to server failed.");
				this->backgroundWorker1->CancelAsync();
			}

			Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), "Connecting to server successed.");

			char buffer[MAX_MESSAGE];

			Invoke(gcnew SetDelegate(this, &Form1::clearCheckedListBox1Item));

			send(socket_s, "/GETDIR", MAX_MESSAGE, 0);
			recv(socket_s, buffer, MAX_MESSAGE, 0);
			while (strcmp(buffer, "/FIN")) {
				Invoke(gcnew SetTextDelegate(this, &Form1::addCheckedListBox1Item), gcnew String(buffer));
				send(socket_s, "/ACCEPT", MAX_MESSAGE, 0);
				recv(socket_s, buffer, MAX_MESSAGE, 0);
			}

			Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), "Get directory successed.");
		}

		System::Void backgroundWorker2_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
			int bgw = 0;
			
			struct hostent *hp;
			hp = gethostbyname((char*)(void*)Marshal::StringToHGlobalAnsi(host));
			if (!hp) {
				Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), "Error: Unknow server.");
				this->backgroundWorker2->CancelAsync();
			}

			SOCKET socket_s;
			struct sockaddr_in server_address;
			server_address.sin_family = AF_INET;
			server_address.sin_addr = *((struct in_addr *)hp->h_addr);
			server_address.sin_port = htons(System::Int32::Parse(port));
			memset(&(server_address.sin_zero), '\0', 8);

			socket_s = socket(PF_INET, SOCK_STREAM, 0);
			if (socket_s == INVALID_SOCKET) {
				Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), "Error: Socket creation failed.");
				this->backgroundWorker2->CancelAsync();
			}
			if (connect(socket_s, (struct sockaddr *)&server_address, sizeof(server_address)) == SOCKET_ERROR) {
				Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), "Error: Connecting to server failed.");
				this->backgroundWorker2->CancelAsync();
			}
			
			Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), "Connecting to server successed.");
			
			int total, remain, percent = 0, percentt = 0;
			char buffer[MAX_MESSAGE];

			if (file_d[bgw] == true) {
				send(socket_s, "/DLFILE", MAX_MESSAGE, 0);
				recv(socket_s, buffer, MAX_MESSAGE, 0);
				send(socket_s, (char*)(void*)Marshal::StringToHGlobalAnsi(file_n[bgw]), MAX_MESSAGE, 0);
				recv(socket_s, buffer, MAX_MESSAGE, 0);
				total = remain = atoi(buffer);
				if (total == 0) {
					Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), String::Concat("Error: Unable to download ", file_n[bgw], "."));
				} else {
					Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), String::Concat("Start to download ", file_n[bgw], "."));
					Invoke(gcnew SetTextDelegate(this, &Form1::SetLabel1Text), String::Concat("[Download] ", file_n[bgw]));
					Invoke(gcnew SetTextDelegate(this, &Form1::SetLabel5Text), String::Concat("0% (0 / ", total, ")"));

					fstream fs;
					fs.open((char*)(void*)Marshal::StringToHGlobalAnsi(file_n[bgw]), ios::out|ios::binary);
					while (remain > 0) {
						send(socket_s, "/ACCEPT", MAX_MESSAGE, 0);
						recv(socket_s, buffer, MAX_MESSAGE, 0);
						if (remain < MAX_MESSAGE) {
							fs.write(buffer, remain);
							remain = 0;
						} else {
							remain -= MAX_MESSAGE;
							fs.write(buffer, MAX_MESSAGE);
						}
						percent = (int)(((double)(total - remain) / (double)total) * 100.0);
						if (percent != percentt) {
							percentt = percent;
							Invoke(gcnew SetValueDelegate(this, &Form1::setProgressBar1Value), percent);
							Invoke(gcnew SetTextDelegate(this, &Form1::SetLabel5Text), String::Concat(percent, "% (", total - remain, "/", total, ")"));
						}
					}
					fs.close();
					Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), String::Concat("Download ", file_n[bgw], " successed."));
				}
			} else {
				fstream fs;
				fs.open((char*)(void*)Marshal::StringToHGlobalAnsi(file_n[bgw]), ios::in|ios::binary);
				if (fs.is_open()) {
					send(socket_s, "/ULFILE", MAX_MESSAGE, 0);
					recv(socket_s, buffer, MAX_MESSAGE, 0);
					send(socket_s, (char*)(void*)Marshal::StringToHGlobalAnsi(file_n[bgw]), MAX_MESSAGE, 0);
					recv(socket_s, buffer, MAX_MESSAGE, 0);

					fs.seekg(0, ios::end);
					total = remain = (int)fs.tellg();
					fs.seekg(0, ios::beg);
					_itoa_s(total, buffer, 10);
					send(socket_s, buffer, MAX_MESSAGE, 0);

					Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), String::Concat("Start to upload ", file_n[bgw], "."));
					Invoke(gcnew SetTextDelegate(this, &Form1::SetLabel1Text), String::Concat("[Upload] ", file_n[bgw]));
					Invoke(gcnew SetTextDelegate(this, &Form1::SetLabel5Text), String::Concat("0% (0 / ", total, ")"));
					
					while (!fs.eof()) {
						recv(socket_s, buffer, MAX_MESSAGE, 0);
						fs.read(buffer, MAX_MESSAGE);
						send(socket_s, buffer, MAX_MESSAGE, 0);
						remain -= MAX_MESSAGE;
						if (remain < 0) remain = 0;
						percent = (int)(((double)(total - remain) / (double)total) * 100.0);
						if (percent != percentt) {
							percentt = percent;
							Invoke(gcnew SetValueDelegate(this, &Form1::setProgressBar1Value), percent);
							Invoke(gcnew SetTextDelegate(this, &Form1::SetLabel5Text), String::Concat(percent, "% (", total - remain, "/", total, ")"));
						}
					}
					fs.close();
					Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), String::Concat("Upload ", file_n[bgw], " successed."));
				} else {
					Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), String::Concat("Error: Unable to open ", file_n[bgw], "."));
				}
			}
			
			Sleep(1000);

			Invoke(gcnew SetTextDelegate(this, &Form1::SetLabel1Text), "[Idle]");
			Invoke(gcnew SetTextDelegate(this, &Form1::SetLabel5Text), "0% (0 / 0)");
			Invoke(gcnew SetValueDelegate(this, &Form1::setProgressBar1Value), 0);
			if (!backgroundWorker1->IsBusy) this->backgroundWorker1->RunWorkerAsync();
		}

		System::Void backgroundWorker3_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
			int bgw = 1;
			
			struct hostent *hp;
			hp = gethostbyname((char*)(void*)Marshal::StringToHGlobalAnsi(host));
			if (!hp) {
				Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), "Error: Unknow server.");
				this->backgroundWorker3->CancelAsync();
			}

			SOCKET socket_s;
			struct sockaddr_in server_address;
			server_address.sin_family = AF_INET;
			server_address.sin_addr = *((struct in_addr *)hp->h_addr);
			server_address.sin_port = htons(System::Int32::Parse(port));
			memset(&(server_address.sin_zero), '\0', 8);

			socket_s = socket(PF_INET, SOCK_STREAM, 0);
			if (socket_s == INVALID_SOCKET) {
				Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), "Error: Socket creation failed.");
				this->backgroundWorker3->CancelAsync();
			}
			if (connect(socket_s, (struct sockaddr *)&server_address, sizeof(server_address)) == SOCKET_ERROR) {
				Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), "Error: Connecting to server failed.");
				this->backgroundWorker3->CancelAsync();
			}
			
			Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), "Connecting to server successed.");
			
			int total, remain, percent = 0, percentt = 0;
			char buffer[MAX_MESSAGE];

			if (file_d[bgw] == true) {
				send(socket_s, "/DLFILE", MAX_MESSAGE, 0);
				recv(socket_s, buffer, MAX_MESSAGE, 0);
				send(socket_s, (char*)(void*)Marshal::StringToHGlobalAnsi(file_n[bgw]), MAX_MESSAGE, 0);
				recv(socket_s, buffer, MAX_MESSAGE, 0);
				total = remain = atoi(buffer);
				if (total == 0) {
					Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), String::Concat("Error: Unable to download ", file_n[bgw], "."));
				} else {
					Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), String::Concat("Start to download ", file_n[bgw], "."));
					Invoke(gcnew SetTextDelegate(this, &Form1::SetLabel2Text), String::Concat("[Download] ", file_n[bgw]));
					Invoke(gcnew SetTextDelegate(this, &Form1::SetLabel6Text), String::Concat("0% (0 / ", total, ")"));

					fstream fs;
					fs.open((char*)(void*)Marshal::StringToHGlobalAnsi(file_n[bgw]), ios::out|ios::binary);
					while (remain > 0) {
						send(socket_s, "/ACCEPT", MAX_MESSAGE, 0);
						recv(socket_s, buffer, MAX_MESSAGE, 0);
						if (remain < MAX_MESSAGE) {
							fs.write(buffer, remain);
							remain = 0;
						} else {
							remain -= MAX_MESSAGE;
							fs.write(buffer, MAX_MESSAGE);
						}
						percent = (int)(((double)(total - remain) / (double)total) * 100.0);
						if (percent != percentt) {
							percentt = percent;
							Invoke(gcnew SetValueDelegate(this, &Form1::setProgressBar2Value), percent);
							Invoke(gcnew SetTextDelegate(this, &Form1::SetLabel6Text), String::Concat(percent, "% (", total - remain, "/", total, ")"));
						}
					}
					fs.close();
					Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), String::Concat("Download ", file_n[bgw], " successed."));
				}
			} else {
				fstream fs;
				fs.open((char*)(void*)Marshal::StringToHGlobalAnsi(file_n[bgw]), ios::in|ios::binary);
				if (fs.is_open()) {
					send(socket_s, "/ULFILE", MAX_MESSAGE, 0);
					recv(socket_s, buffer, MAX_MESSAGE, 0);
					send(socket_s, (char*)(void*)Marshal::StringToHGlobalAnsi(file_n[bgw]), MAX_MESSAGE, 0);
					recv(socket_s, buffer, MAX_MESSAGE, 0);

					fs.seekg(0, ios::end);
					total = remain = (int)fs.tellg();
					fs.seekg(0, ios::beg);
					_itoa_s(total, buffer, 10);
					send(socket_s, buffer, MAX_MESSAGE, 0);

					Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), String::Concat("Start to upload ", file_n[bgw], "."));
					Invoke(gcnew SetTextDelegate(this, &Form1::SetLabel2Text), String::Concat("[Upload] ", file_n[bgw]));
					Invoke(gcnew SetTextDelegate(this, &Form1::SetLabel6Text), String::Concat("0% (0 / ", total, ")"));
					
					while (!fs.eof()) {
						recv(socket_s, buffer, MAX_MESSAGE, 0);
						fs.read(buffer, MAX_MESSAGE);
						send(socket_s, buffer, MAX_MESSAGE, 0);
						remain -= MAX_MESSAGE;
						if (remain < 0) remain = 0;
						percent = (int)(((double)(total - remain) / (double)total) * 100.0);
						if (percent != percentt) {
							percentt = percent;
							Invoke(gcnew SetValueDelegate(this, &Form1::setProgressBar2Value), percent);
							Invoke(gcnew SetTextDelegate(this, &Form1::SetLabel6Text), String::Concat(percent, "% (", total - remain, "/", total, ")"));
						}
					}
					fs.close();
					Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), String::Concat("Upload ", file_n[bgw], " successed."));
				} else {
					Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), String::Concat("Error: Unable to open ", file_n[bgw], "."));
				}
			}
			
			Sleep(1000);

			Invoke(gcnew SetTextDelegate(this, &Form1::SetLabel2Text), "[Idle]");
			Invoke(gcnew SetTextDelegate(this, &Form1::SetLabel6Text), "0% (0 / 0)");
			Invoke(gcnew SetValueDelegate(this, &Form1::setProgressBar2Value), 0);
			if (!backgroundWorker1->IsBusy) this->backgroundWorker1->RunWorkerAsync();
		}

		System::Void backgroundWorker4_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
			int bgw = 2;
			
			struct hostent *hp;
			hp = gethostbyname((char*)(void*)Marshal::StringToHGlobalAnsi(host));
			if (!hp) {
				Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), "Error: Unknow server.");
				this->backgroundWorker4->CancelAsync();
			}

			SOCKET socket_s;
			struct sockaddr_in server_address;
			server_address.sin_family = AF_INET;
			server_address.sin_addr = *((struct in_addr *)hp->h_addr);
			server_address.sin_port = htons(System::Int32::Parse(port));
			memset(&(server_address.sin_zero), '\0', 8);

			socket_s = socket(PF_INET, SOCK_STREAM, 0);
			if (socket_s == INVALID_SOCKET) {
				Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), "Error: Socket creation failed.");
				this->backgroundWorker4->CancelAsync();
			}
			if (connect(socket_s, (struct sockaddr *)&server_address, sizeof(server_address)) == SOCKET_ERROR) {
				Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), "Error: Connecting to server failed.");
				this->backgroundWorker4->CancelAsync();
			}
			
			Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), "Connecting to server successed.");
			
			int total, remain, percent = 0, percentt = 0;
			char buffer[MAX_MESSAGE];

			if (file_d[bgw] == true) {
				send(socket_s, "/DLFILE", MAX_MESSAGE, 0);
				recv(socket_s, buffer, MAX_MESSAGE, 0);
				send(socket_s, (char*)(void*)Marshal::StringToHGlobalAnsi(file_n[bgw]), MAX_MESSAGE, 0);
				recv(socket_s, buffer, MAX_MESSAGE, 0);
				total = remain = atoi(buffer);
				if (total == 0) {
					Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), String::Concat("Error: Unable to download ", file_n[bgw], "."));
				} else {
					Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), String::Concat("Start to download ", file_n[bgw], "."));
					Invoke(gcnew SetTextDelegate(this, &Form1::SetLabel3Text), String::Concat("[Download] ", file_n[bgw]));
					Invoke(gcnew SetTextDelegate(this, &Form1::SetLabel7Text), String::Concat("0% (0 / ", total, ")"));

					fstream fs;
					fs.open((char*)(void*)Marshal::StringToHGlobalAnsi(file_n[bgw]), ios::out|ios::binary);
					while (remain > 0) {
						send(socket_s, "/ACCEPT", MAX_MESSAGE, 0);
						recv(socket_s, buffer, MAX_MESSAGE, 0);
						if (remain < MAX_MESSAGE) {
							fs.write(buffer, remain);
							remain = 0;
						} else {
							remain -= MAX_MESSAGE;
							fs.write(buffer, MAX_MESSAGE);
						}
						percent = (int)(((double)(total - remain) / (double)total) * 100.0);
						if (percent != percentt) {
							percentt = percent;
							Invoke(gcnew SetValueDelegate(this, &Form1::setProgressBar3Value), percent);
							Invoke(gcnew SetTextDelegate(this, &Form1::SetLabel7Text), String::Concat(percent, "% (", total - remain, "/", total, ")"));
						}
					}
					fs.close();
					Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), String::Concat("Download ", file_n[bgw], " successed."));
				}
			} else {
				fstream fs;
				fs.open((char*)(void*)Marshal::StringToHGlobalAnsi(file_n[bgw]), ios::in|ios::binary);
				if (fs.is_open()) {
					send(socket_s, "/ULFILE", MAX_MESSAGE, 0);
					recv(socket_s, buffer, MAX_MESSAGE, 0);
					send(socket_s, (char*)(void*)Marshal::StringToHGlobalAnsi(file_n[bgw]), MAX_MESSAGE, 0);
					recv(socket_s, buffer, MAX_MESSAGE, 0);

					fs.seekg(0, ios::end);
					total = remain = (int)fs.tellg();
					fs.seekg(0, ios::beg);
					_itoa_s(total, buffer, 10);
					send(socket_s, buffer, MAX_MESSAGE, 0);

					Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), String::Concat("Start to upload ", file_n[bgw], "."));
					Invoke(gcnew SetTextDelegate(this, &Form1::SetLabel3Text), String::Concat("[Upload] ", file_n[bgw]));
					Invoke(gcnew SetTextDelegate(this, &Form1::SetLabel7Text), String::Concat("0% (0 / ", total, ")"));
					
					while (!fs.eof()) {
						recv(socket_s, buffer, MAX_MESSAGE, 0);
						fs.read(buffer, MAX_MESSAGE);
						send(socket_s, buffer, MAX_MESSAGE, 0);
						remain -= MAX_MESSAGE;
						if (remain < 0) remain = 0;
						percent = (int)(((double)(total - remain) / (double)total) * 100.0);
						if (percent != percentt) {
							percentt = percent;
							Invoke(gcnew SetValueDelegate(this, &Form1::setProgressBar3Value), percent);
							Invoke(gcnew SetTextDelegate(this, &Form1::SetLabel7Text), String::Concat(percent, "% (", total - remain, "/", total, ")"));
						}
					}
					fs.close();
					Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), String::Concat("Upload ", file_n[bgw], " successed."));
				} else {
					Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), String::Concat("Error: Unable to open ", file_n[bgw], "."));
				}
			}
			
			Sleep(1000);

			Invoke(gcnew SetTextDelegate(this, &Form1::SetLabel3Text), "[Idle]");
			Invoke(gcnew SetTextDelegate(this, &Form1::SetLabel7Text), "0% (0 / 0)");
			Invoke(gcnew SetValueDelegate(this, &Form1::setProgressBar3Value), 0);
			if (!backgroundWorker1->IsBusy) this->backgroundWorker1->RunWorkerAsync();
		}

		System::Void backgroundWorker5_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
			int bgw = 3;
			
			struct hostent *hp;
			hp = gethostbyname((char*)(void*)Marshal::StringToHGlobalAnsi(host));
			if (!hp) {
				Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), "Error: Unknow server.");
				this->backgroundWorker5->CancelAsync();
			}

			SOCKET socket_s;
			struct sockaddr_in server_address;
			server_address.sin_family = AF_INET;
			server_address.sin_addr = *((struct in_addr *)hp->h_addr);
			server_address.sin_port = htons(System::Int32::Parse(port));
			memset(&(server_address.sin_zero), '\0', 8);

			socket_s = socket(PF_INET, SOCK_STREAM, 0);
			if (socket_s == INVALID_SOCKET) {
				Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), "Error: Socket creation failed.");
				this->backgroundWorker5->CancelAsync();
			}
			if (connect(socket_s, (struct sockaddr *)&server_address, sizeof(server_address)) == SOCKET_ERROR) {
				Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), "Error: Connecting to server failed.");
				this->backgroundWorker5->CancelAsync();
			}
			
			Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), "Connecting to server successed.");
			
			int total, remain, percent = 0, percentt = 0;
			char buffer[MAX_MESSAGE];

			if (file_d[bgw] == true) {
				send(socket_s, "/DLFILE", MAX_MESSAGE, 0);
				recv(socket_s, buffer, MAX_MESSAGE, 0);
				send(socket_s, (char*)(void*)Marshal::StringToHGlobalAnsi(file_n[bgw]), MAX_MESSAGE, 0);
				recv(socket_s, buffer, MAX_MESSAGE, 0);
				total = remain = atoi(buffer);
				if (total == 0) {
					Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), String::Concat("Error: Unable to download ", file_n[bgw], "."));
				} else {
					Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), String::Concat("Start to download ", file_n[bgw], "."));
					Invoke(gcnew SetTextDelegate(this, &Form1::SetLabel4Text), String::Concat("[Download] ", file_n[bgw]));
					Invoke(gcnew SetTextDelegate(this, &Form1::SetLabel8Text), String::Concat("0% (0 / ", total, ")"));

					fstream fs;
					fs.open((char*)(void*)Marshal::StringToHGlobalAnsi(file_n[bgw]), ios::out|ios::binary);
					while (remain > 0) {
						send(socket_s, "/ACCEPT", MAX_MESSAGE, 0);
						recv(socket_s, buffer, MAX_MESSAGE, 0);
						if (remain < MAX_MESSAGE) {
							fs.write(buffer, remain);
							remain = 0;
						} else {
							remain -= MAX_MESSAGE;
							fs.write(buffer, MAX_MESSAGE);
						}
						percent = (int)(((double)(total - remain) / (double)total) * 100.0);
						if (percent != percentt) {
							percentt = percent;
							Invoke(gcnew SetValueDelegate(this, &Form1::setProgressBar4Value), percent);
							Invoke(gcnew SetTextDelegate(this, &Form1::SetLabel8Text), String::Concat(percent, "% (", total - remain, "/", total, ")"));
						}
					}
					fs.close();
					Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), String::Concat("Download ", file_n[bgw], " successed."));
				}
			} else {
				fstream fs;
				fs.open((char*)(void*)Marshal::StringToHGlobalAnsi(file_n[bgw]), ios::in|ios::binary);
				if (fs.is_open()) {
					send(socket_s, "/ULFILE", MAX_MESSAGE, 0);
					recv(socket_s, buffer, MAX_MESSAGE, 0);
					send(socket_s, (char*)(void*)Marshal::StringToHGlobalAnsi(file_n[bgw]), MAX_MESSAGE, 0);
					recv(socket_s, buffer, MAX_MESSAGE, 0);

					fs.seekg(0, ios::end);
					total = remain = (int)fs.tellg();
					fs.seekg(0, ios::beg);
					_itoa_s(total, buffer, 10);
					send(socket_s, buffer, MAX_MESSAGE, 0);

					Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), String::Concat("Start to upload ", file_n[bgw], "."));
					Invoke(gcnew SetTextDelegate(this, &Form1::SetLabel4Text), String::Concat("[Upload] ", file_n[bgw]));
					Invoke(gcnew SetTextDelegate(this, &Form1::SetLabel8Text), String::Concat("0% (0 / ", total, ")"));
					
					while (!fs.eof()) {
						recv(socket_s, buffer, MAX_MESSAGE, 0);
						fs.read(buffer, MAX_MESSAGE);
						send(socket_s, buffer, MAX_MESSAGE, 0);
						remain -= MAX_MESSAGE;
						if (remain < 0) remain = 0;
						percent = (int)(((double)(total - remain) / (double)total) * 100.0);
						if (percent != percentt) {
							percentt = percent;
							Invoke(gcnew SetValueDelegate(this, &Form1::setProgressBar4Value), percent);
							Invoke(gcnew SetTextDelegate(this, &Form1::SetLabel8Text), String::Concat(percent, "% (", total - remain, "/", total, ")"));
						}
					}
					fs.close();
					Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), String::Concat("Upload ", file_n[bgw], " successed."));
				} else {
					Invoke(gcnew SetTextDelegate(this, &Form1::SettoolStripStatusLabel1Text), String::Concat("Error: Unable to open ", file_n[bgw], "."));
				}
			}
			
			Sleep(1000);

			Invoke(gcnew SetTextDelegate(this, &Form1::SetLabel4Text), "[Idle]");
			Invoke(gcnew SetTextDelegate(this, &Form1::SetLabel8Text), "0% (0 / 0)");
			Invoke(gcnew SetValueDelegate(this, &Form1::setProgressBar4Value), 0);
			if (!backgroundWorker1->IsBusy) this->backgroundWorker1->RunWorkerAsync();
		}
		System::Void backgroundWorker2_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) {
			file_t[0] = false;
		}
		System::Void backgroundWorker3_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) {
			file_t[1] = false;
		}
		System::Void backgroundWorker4_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) {
			file_t[2] = false;
		}
		System::Void backgroundWorker5_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) {
			file_t[3] = false;
		}

	private: 
		delegate void SetTextDelegate(System::String^ s);
	    void SettoolStripStatusLabel1Text(System::String^ s) {
			toolStripStatusLabel1->Text = s;
		}
	    void addCheckedListBox1Item(System::String^ s) {
			checkedListBox1->Items->Add(s, false);
		}
	    void addCheckedListBox2Item(System::String^ s) {
			checkedListBox2->Items->Add(s, false);
		}
	    void SetLabel1Text(System::String^ s) {
			label1->Text = s;
		}
	    void SetLabel2Text(System::String^ s) {
			label2->Text = s;
		}
	    void SetLabel3Text(System::String^ s) {
			label3->Text = s;
		}
	    void SetLabel4Text(System::String^ s) {
			label4->Text = s;
		}
	    void SetLabel5Text(System::String^ s) {
			label5->Text = s;
		}
	    void SetLabel6Text(System::String^ s) {
			label6->Text = s;
		}
	    void SetLabel7Text(System::String^ s) {
			label7->Text = s;
		}
	    void SetLabel8Text(System::String^ s) {
			label8->Text = s;
		}

		delegate void SetDelegate(void);
	    void clearCheckedListBox1Item(void) {
			checkedListBox1->Items->Clear();
		}
	    void clearCheckedListBox2Item(void) {
			checkedListBox2->Items->Clear();
		}

		delegate void SetValueDelegate(int n);
	    void setProgressBar1Value(int n) {
			progressBar1->Value = n;
		}
	    void setProgressBar2Value(int n) {
			progressBar2->Value = n;
		}
	    void setProgressBar3Value(int n) {
			progressBar3->Value = n;
		}
	    void setProgressBar4Value(int n) {
			progressBar4->Value = n;
		}
		
};
}

