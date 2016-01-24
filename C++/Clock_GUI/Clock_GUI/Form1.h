#include <winsock2.h>
#include <stdlib.h>
#include <windows.h>
#include <vcclr.h>


#define SERVER_PORT 5432
#define MAX_MESSAGE 128

#pragma once

namespace Clock_GUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
		}

	protected:
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker1;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker2;
	protected: 

	private:
		System::String^ temp;
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->backgroundWorker2 = (gcnew System::ComponentModel::BackgroundWorker());
			this->SuspendLayout();
			// 
			// backgroundWorker1
			// 
			this->backgroundWorker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::backgroundWorker1_DoWork);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 71);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(45, 12);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Initialize";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"·s²Ó©úÅé", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label2->Location = System::Drawing::Point(46, 29);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(0, 27);
			this->label2->TabIndex = 1;
			// 
			// backgroundWorker2
			// 
			this->backgroundWorker2->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::backgroundWorker2_DoWork);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(294, 92);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"Form1";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Clock GUI";
			this->Shown += gcnew System::EventHandler(this, &Form1::Form1_Shown);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void backgroundWorker1_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
				WSADATA info;
				if (WSAStartup(MAKEWORD(1,1), &info) !=0) {
					this->label1->ForeColor = System::Drawing::Color::Red;
					Invoke(gcnew SetTextDelegate(this, &Form1::Setlabel1Text), "Error: Winsock startup failed.");
					this->backgroundWorker1->CancelAsync();
				} else {
					struct sockaddr_in server_address;
					struct sockaddr_in client_address;
					SOCKET socket_1, socket_2;

					server_address.sin_family = AF_INET;
					server_address.sin_addr.s_addr = INADDR_ANY;
					server_address.sin_port = htons(SERVER_PORT);
					memset(&(server_address.sin_zero),'\0', 8);

					socket_1 = socket(PF_INET, SOCK_STREAM, 0);
					if (socket_1 == INVALID_SOCKET) {
						this->label1->ForeColor = System::Drawing::Color::Red;
						Invoke(gcnew SetTextDelegate(this, &Form1::Setlabel1Text), "Error: Socket creation failed.");
						this->backgroundWorker1->CancelAsync();
					} else if (bind(socket_1, (struct sockaddr *)&server_address, sizeof(server_address)) == SOCKET_ERROR) {
						this->label1->ForeColor = System::Drawing::Color::Red;
						Invoke(gcnew SetTextDelegate(this, &Form1::Setlabel1Text), "Error: Bind failed.");
						this->backgroundWorker1->CancelAsync();
					} else {
						this->label1->ForeColor = System::Drawing::Color::Yellow;
						Invoke(gcnew SetTextDelegate(this, &Form1::Setlabel1Text), "Ready");

						int n, len = sizeof(client_address);
						char buff[MAX_MESSAGE];

						listen(socket_1, 1);
						this->backgroundWorker2->RunWorkerAsync();

						socket_2 = accept(socket_1, (struct sockaddr *)&client_address, &len);

						if (socket_2 == INVALID_SOCKET) {
							this->label1->ForeColor = System::Drawing::Color::Red;
							Invoke(gcnew SetTextDelegate(this, &Form1::Setlabel1Text), "Error: Connect Failed.");
							this->backgroundWorker1->CancelAsync();
						} else {
							this->label1->ForeColor = System::Drawing::Color::Green;
							Invoke(gcnew SetTextDelegate(this, &Form1::Setlabel1Text), "Connected");

							while (1) {
								n = recv(socket_2, buff, MAX_MESSAGE, 0);
								Invoke(gcnew SetTextDelegate(this, &Form1::Setlabel2Text), gcnew String(buff));
							}

							closesocket(socket_1);
							WSACleanup();
						}
					}
				}
			}
	private: System::Void backgroundWorker2_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
				 Sleep(100);
				 system("clock.exe");
			}
	private: System::Void Form1_Shown(System::Object^  sender, System::EventArgs^  e) {
				 this->backgroundWorker1->RunWorkerAsync();
			}

	private: 
		delegate void SetTextDelegate(System::String^ s);
	    void Setlabel1Text(System::String^ s) {
			label1->Text = s;
		}
	    void Setlabel2Text(System::String^ s) {
			label2->Text = s;
		}

};
}

