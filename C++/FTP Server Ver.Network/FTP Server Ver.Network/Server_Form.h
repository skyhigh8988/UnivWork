#include <winsock2.h>
#include <stdio.h>
#include <fstream>
#pragma comment(lib,"wsock32.lib")

#pragma once

namespace FTPServerVerNetwork {

	using namespace std;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;
	using namespace System::IO;
	using namespace System::Runtime::InteropServices;

	public ref class Server_Form : public System::Windows::Forms::Form
	{
	public:
		Server_Form(void)
		{
			InitializeComponent();
			CheckForIllegalCrossThreadCalls = false;
			fileUser = gcnew ArrayList();
			fileName = gcnew ArrayList();
			userName = gcnew ArrayList();
			userPass = gcnew ArrayList();
			listUser = gcnew ArrayList();
			listIP = gcnew ArrayList();
			currentPath = "";
		}

	protected:
		~Server_Form()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		System::Windows::Forms::FlowLayoutPanel^  flowLayoutPanel1;
		System::Windows::Forms::FlowLayoutPanel^  flowLayoutPanel2;
		System::Windows::Forms::FlowLayoutPanel^  flowLayoutPanel3;
		System::Windows::Forms::SplitContainer^  splitContainer1;



		System::Windows::Forms::DataGridView^  dataGridView1;
		System::Windows::Forms::RichTextBox^  richTextBox1;
		System::Windows::Forms::TabControl^  tabControl1;
		System::Windows::Forms::TabPage^  tabPage3;
		System::Windows::Forms::TextBox^  textBox1;
		System::Windows::Forms::TextBox^  textBox2;
		System::Windows::Forms::TextBox^  textBox3;
		System::Windows::Forms::TextBox^  textBox4;
		System::Windows::Forms::TextBox^  textBox5;
		System::Windows::Forms::TextBox^  textBox6;
		System::Windows::Forms::ListBox^  listBox1;
		System::Windows::Forms::ListBox^  listBox2;
		System::Windows::Forms::Button^  button1;
		System::Windows::Forms::Button^  button2;
		System::Windows::Forms::Button^  button3;
		System::Windows::Forms::Button^  button4;
		System::Windows::Forms::Button^  button5;
		System::Windows::Forms::Button^  button6;
		System::Windows::Forms::Button^  button7;
		System::Windows::Forms::Button^  button8;
		System::Windows::Forms::Button^  button9;
		System::Windows::Forms::Button^  button10;
		System::Windows::Forms::Label^  label1;
		System::Windows::Forms::Label^  label2;
		System::Windows::Forms::Label^  label3;
		System::Windows::Forms::Label^  label4;
		System::Windows::Forms::Label^  label5;
		System::Windows::Forms::Label^  label6;
		System::Windows::Forms::Panel^  panel1;
		System::Windows::Forms::Panel^  panel2;
		System::Windows::Forms::Panel^  panel3;
		System::Windows::Forms::Panel^  panel4;
		System::ComponentModel::Container ^components;

	private:
		Thread^ threadListen;
		Thread^ threadLoadUser;
		Thread^ threadLoadDir;
		array<Thread ^>^ threadConnect;
		array<SOCKET >^ socketClient;
		array<String ^>^ ipClient;
		array<String ^>^ userClient;
		array<DataGridViewRow ^>^ viewRow;
		int connectAmount;
		SOCKET socketServer;
		String^ rootPath;
		String^ currentPath;
		array<String ^>^ user;
		array<String ^>^ password;
		ArrayList^ fileUser;
		ArrayList^ fileName;
		ArrayList^ userName;
		ArrayList^ userPass;
		ArrayList^ listUser;
		ArrayList^ listIP;
		array<int>^ turn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Username_T;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Address_T;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  LastCommand_T;
			 array<int>^ flag;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->flowLayoutPanel2 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->listBox2 = (gcnew System::Windows::Forms::ListBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->flowLayoutPanel3 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->button10 = (gcnew System::Windows::Forms::Button());
			this->panel4 = (gcnew System::Windows::Forms::Panel());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->Username_T = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Address_T = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->LastCommand_T = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->tabControl1->SuspendLayout();
			this->tabPage3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->BeginInit();
			this->flowLayoutPanel1->SuspendLayout();
			this->panel1->SuspendLayout();
			this->panel2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->splitContainer1))->BeginInit();
			this->splitContainer1->Panel1->SuspendLayout();
			this->splitContainer1->Panel2->SuspendLayout();
			this->splitContainer1->SuspendLayout();
			this->flowLayoutPanel2->SuspendLayout();
			this->flowLayoutPanel3->SuspendLayout();
			this->SuspendLayout();
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->tabControl1->Location = System::Drawing::Point(10, 422);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(764, 130);
			this->tabControl1->TabIndex = 0;
			// 
			// tabPage3
			// 
			this->tabPage3->Controls->Add(this->dataGridView1);
			this->tabPage3->Location = System::Drawing::Point(4, 22);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Padding = System::Windows::Forms::Padding(3);
			this->tabPage3->Size = System::Drawing::Size(756, 104);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = L"用戶";
			this->tabPage3->UseVisualStyleBackColor = true;
			// 
			// dataGridView1
			// 
			this->dataGridView1->AllowUserToAddRows = false;
			this->dataGridView1->AllowUserToDeleteRows = false;
			this->dataGridView1->AllowUserToOrderColumns = true;
			this->dataGridView1->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->dataGridView1->BackgroundColor = System::Drawing::SystemColors::ControlLightLight;
			this->dataGridView1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(3) {this->Username_T, 
				this->Address_T, this->LastCommand_T});
			this->dataGridView1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->dataGridView1->Location = System::Drawing::Point(3, 3);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->ReadOnly = true;
			this->dataGridView1->RowHeadersVisible = false;
			this->dataGridView1->RowTemplate->Height = 24;
			this->dataGridView1->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			this->dataGridView1->Size = System::Drawing::Size(750, 98);
			this->dataGridView1->TabIndex = 0;
			// 
			// flowLayoutPanel1
			// 
			this->flowLayoutPanel1->Controls->Add(this->label4);
			this->flowLayoutPanel1->Controls->Add(this->textBox4);
			this->flowLayoutPanel1->Controls->Add(this->label3);
			this->flowLayoutPanel1->Controls->Add(this->textBox3);
			this->flowLayoutPanel1->Controls->Add(this->label1);
			this->flowLayoutPanel1->Controls->Add(this->textBox1);
			this->flowLayoutPanel1->Controls->Add(this->button1);
			this->flowLayoutPanel1->Controls->Add(this->button2);
			this->flowLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Top;
			this->flowLayoutPanel1->Location = System::Drawing::Point(10, 10);
			this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
			this->flowLayoutPanel1->Size = System::Drawing::Size(764, 28);
			this->flowLayoutPanel1->TabIndex = 1;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(3, 8);
			this->label4->Margin = System::Windows::Forms::Padding(3, 8, 3, 0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(44, 12);
			this->label4->TabIndex = 0;
			this->label4->Text = L"連接埠:";
			this->label4->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// textBox4
			// 
			this->textBox4->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->textBox4->Location = System::Drawing::Point(53, 3);
			this->textBox4->MaxLength = 6;
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(50, 22);
			this->textBox4->TabIndex = 1;
			this->textBox4->Text = L"7497";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(109, 8);
			this->label3->Margin = System::Windows::Forms::Padding(3, 8, 3, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(104, 12);
			this->label3->TabIndex = 0;
			this->label3->Text = L"伺服器最大連接數:";
			this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// textBox3
			// 
			this->textBox3->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->textBox3->Location = System::Drawing::Point(219, 3);
			this->textBox3->MaxLength = 6;
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(50, 22);
			this->textBox3->TabIndex = 1;
			this->textBox3->Text = L"512";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(275, 8);
			this->label1->Margin = System::Windows::Forms::Padding(3, 8, 3, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(44, 12);
			this->label1->TabIndex = 0;
			this->label1->Text = L"根目錄:";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// textBox1
			// 
			this->textBox1->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->textBox1->Location = System::Drawing::Point(325, 3);
			this->textBox1->MaxLength = 1024;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(300, 22);
			this->textBox1->TabIndex = 1;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(631, 2);
			this->button1->Margin = System::Windows::Forms::Padding(3, 2, 3, 3);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(40, 23);
			this->button1->TabIndex = 2;
			this->button1->Text = L"啟動";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Server_Form::button1_Click);
			// 
			// button2
			// 
			this->button2->Enabled = false;
			this->button2->Location = System::Drawing::Point(677, 2);
			this->button2->Margin = System::Windows::Forms::Padding(3, 2, 3, 3);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(40, 23);
			this->button2->TabIndex = 2;
			this->button2->Text = L"中斷";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Server_Form::button2_Click);
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::SystemColors::Control;
			this->panel1->Controls->Add(this->richTextBox1);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel1->Location = System::Drawing::Point(10, 38);
			this->panel1->Name = L"panel1";
			this->panel1->Padding = System::Windows::Forms::Padding(0, 10, 0, 0);
			this->panel1->Size = System::Drawing::Size(764, 100);
			this->panel1->TabIndex = 2;
			// 
			// richTextBox1
			// 
			this->richTextBox1->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->richTextBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->richTextBox1->Location = System::Drawing::Point(0, 10);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->ReadOnly = true;
			this->richTextBox1->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::ForcedVertical;
			this->richTextBox1->Size = System::Drawing::Size(764, 90);
			this->richTextBox1->TabIndex = 1;
			this->richTextBox1->Text = L"";
			// 
			// panel2
			// 
			this->panel2->Controls->Add(this->splitContainer1);
			this->panel2->Controls->Add(this->panel4);
			this->panel2->Controls->Add(this->panel3);
			this->panel2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel2->Location = System::Drawing::Point(10, 138);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(764, 284);
			this->panel2->TabIndex = 3;
			// 
			// splitContainer1
			// 
			this->splitContainer1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer1->IsSplitterFixed = true;
			this->splitContainer1->Location = System::Drawing::Point(0, 10);
			this->splitContainer1->Name = L"splitContainer1";
			// 
			// splitContainer1.Panel1
			// 
			this->splitContainer1->Panel1->Controls->Add(this->listBox1);
			this->splitContainer1->Panel1->Controls->Add(this->flowLayoutPanel2);
			this->splitContainer1->Panel1MinSize = 380;
			// 
			// splitContainer1.Panel2
			// 
			this->splitContainer1->Panel2->BackColor = System::Drawing::SystemColors::Control;
			this->splitContainer1->Panel2->Controls->Add(this->listBox2);
			this->splitContainer1->Panel2->Controls->Add(this->textBox2);
			this->splitContainer1->Panel2->Controls->Add(this->flowLayoutPanel3);
			this->splitContainer1->Panel2MinSize = 380;
			this->splitContainer1->Size = System::Drawing::Size(764, 264);
			this->splitContainer1->SplitterDistance = 380;
			this->splitContainer1->TabIndex = 4;
			// 
			// listBox1
			// 
			this->listBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->listBox1->Font = (gcnew System::Drawing::Font(L"新細明體", 11));
			this->listBox1->FormattingEnabled = true;
			this->listBox1->IntegralHeight = false;
			this->listBox1->ItemHeight = 15;
			this->listBox1->Location = System::Drawing::Point(0, 60);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(380, 204);
			this->listBox1->TabIndex = 2;
			this->listBox1->DoubleClick += gcnew System::EventHandler(this, &Server_Form::listBox1_DoubleClick);
			// 
			// flowLayoutPanel2
			// 
			this->flowLayoutPanel2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->flowLayoutPanel2->Controls->Add(this->button6);
			this->flowLayoutPanel2->Controls->Add(this->button4);
			this->flowLayoutPanel2->Controls->Add(this->button3);
			this->flowLayoutPanel2->Controls->Add(this->button5);
			this->flowLayoutPanel2->Controls->Add(this->label2);
			this->flowLayoutPanel2->Controls->Add(this->label5);
			this->flowLayoutPanel2->Controls->Add(this->textBox5);
			this->flowLayoutPanel2->Controls->Add(this->label6);
			this->flowLayoutPanel2->Controls->Add(this->textBox6);
			this->flowLayoutPanel2->Controls->Add(this->button7);
			this->flowLayoutPanel2->Controls->Add(this->button9);
			this->flowLayoutPanel2->Dock = System::Windows::Forms::DockStyle::Top;
			this->flowLayoutPanel2->Location = System::Drawing::Point(0, 0);
			this->flowLayoutPanel2->Name = L"flowLayoutPanel2";
			this->flowLayoutPanel2->Size = System::Drawing::Size(380, 60);
			this->flowLayoutPanel2->TabIndex = 1;
			// 
			// button6
			// 
			this->button6->Location = System::Drawing::Point(3, 2);
			this->button6->Margin = System::Windows::Forms::Padding(3, 2, 3, 3);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(40, 23);
			this->button6->TabIndex = 2;
			this->button6->Text = L"檢視";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &Server_Form::button6_Click);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(49, 2);
			this->button4->Margin = System::Windows::Forms::Padding(3, 2, 3, 3);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(40, 23);
			this->button4->TabIndex = 2;
			this->button4->Text = L"刪除";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &Server_Form::button4_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(95, 2);
			this->button3->Margin = System::Windows::Forms::Padding(3, 2, 3, 3);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(40, 23);
			this->button3->TabIndex = 2;
			this->button3->Text = L"新增";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Server_Form::button3_Click);
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(141, 2);
			this->button5->Margin = System::Windows::Forms::Padding(3, 2, 3, 3);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(40, 23);
			this->button5->TabIndex = 2;
			this->button5->Text = L"編輯";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &Server_Form::button5_Click);
			// 
			// label2
			// 
			this->label2->Location = System::Drawing::Point(187, 8);
			this->label2->Margin = System::Windows::Forms::Padding(3, 8, 3, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(178, 17);
			this->label2->TabIndex = 0;
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(3, 36);
			this->label5->Margin = System::Windows::Forms::Padding(3, 8, 3, 0);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(44, 12);
			this->label5->TabIndex = 0;
			this->label5->Text = L"使用者:";
			this->label5->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->label5->Visible = false;
			// 
			// textBox5
			// 
			this->textBox5->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->textBox5->Location = System::Drawing::Point(53, 31);
			this->textBox5->MaxLength = 128;
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(80, 22);
			this->textBox5->TabIndex = 1;
			this->textBox5->Visible = false;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(139, 36);
			this->label6->Margin = System::Windows::Forms::Padding(3, 8, 3, 0);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(32, 12);
			this->label6->TabIndex = 0;
			this->label6->Text = L"密碼:";
			this->label6->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->label6->Visible = false;
			// 
			// textBox6
			// 
			this->textBox6->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->textBox6->Location = System::Drawing::Point(177, 31);
			this->textBox6->MaxLength = 128;
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(80, 22);
			this->textBox6->TabIndex = 1;
			this->textBox6->Visible = false;
			// 
			// button7
			// 
			this->button7->Location = System::Drawing::Point(263, 30);
			this->button7->Margin = System::Windows::Forms::Padding(3, 2, 3, 3);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(40, 23);
			this->button7->TabIndex = 2;
			this->button7->Text = L"確定";
			this->button7->UseVisualStyleBackColor = true;
			this->button7->Visible = false;
			this->button7->Click += gcnew System::EventHandler(this, &Server_Form::button7_Click);
			// 
			// button9
			// 
			this->button9->Location = System::Drawing::Point(309, 30);
			this->button9->Margin = System::Windows::Forms::Padding(3, 2, 3, 3);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(40, 23);
			this->button9->TabIndex = 2;
			this->button9->Text = L"取消";
			this->button9->UseVisualStyleBackColor = true;
			this->button9->Visible = false;
			this->button9->Click += gcnew System::EventHandler(this, &Server_Form::button9_Click);
			// 
			// listBox2
			// 
			this->listBox2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->listBox2->Font = (gcnew System::Drawing::Font(L"新細明體", 11));
			this->listBox2->FormattingEnabled = true;
			this->listBox2->IntegralHeight = false;
			this->listBox2->ItemHeight = 15;
			this->listBox2->Location = System::Drawing::Point(0, 60);
			this->listBox2->Name = L"listBox2";
			this->listBox2->Size = System::Drawing::Size(380, 204);
			this->listBox2->TabIndex = 4;
			this->listBox2->DoubleClick += gcnew System::EventHandler(this, &Server_Form::listBox2_DoubleClick);
			// 
			// textBox2
			// 
			this->textBox2->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->textBox2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->textBox2->Dock = System::Windows::Forms::DockStyle::Top;
			this->textBox2->Location = System::Drawing::Point(0, 38);
			this->textBox2->Name = L"textBox2";
			this->textBox2->ReadOnly = true;
			this->textBox2->Size = System::Drawing::Size(380, 22);
			this->textBox2->TabIndex = 3;
			// 
			// flowLayoutPanel3
			// 
			this->flowLayoutPanel3->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->flowLayoutPanel3->Controls->Add(this->button8);
			this->flowLayoutPanel3->Controls->Add(this->button10);
			this->flowLayoutPanel3->Dock = System::Windows::Forms::DockStyle::Top;
			this->flowLayoutPanel3->Location = System::Drawing::Point(0, 0);
			this->flowLayoutPanel3->Name = L"flowLayoutPanel3";
			this->flowLayoutPanel3->Size = System::Drawing::Size(380, 38);
			this->flowLayoutPanel3->TabIndex = 2;
			// 
			// button8
			// 
			this->button8->Location = System::Drawing::Point(3, 2);
			this->button8->Margin = System::Windows::Forms::Padding(3, 2, 3, 3);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(40, 23);
			this->button8->TabIndex = 2;
			this->button8->Text = L"重整";
			this->button8->UseVisualStyleBackColor = true;
			this->button8->Click += gcnew System::EventHandler(this, &Server_Form::button8_Click);
			// 
			// button10
			// 
			this->button10->Location = System::Drawing::Point(49, 2);
			this->button10->Margin = System::Windows::Forms::Padding(3, 2, 3, 3);
			this->button10->Name = L"button10";
			this->button10->Size = System::Drawing::Size(40, 23);
			this->button10->TabIndex = 2;
			this->button10->Text = L"刪除";
			this->button10->UseVisualStyleBackColor = true;
			// 
			// panel4
			// 
			this->panel4->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel4->Location = System::Drawing::Point(0, 274);
			this->panel4->Name = L"panel4";
			this->panel4->Size = System::Drawing::Size(764, 10);
			this->panel4->TabIndex = 1;
			// 
			// panel3
			// 
			this->panel3->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel3->Location = System::Drawing::Point(0, 0);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(764, 10);
			this->panel3->TabIndex = 0;
			// 
			// Username_T
			// 
			this->Username_T->FillWeight = 80;
			this->Username_T->HeaderText = L"Username";
			this->Username_T->Name = L"Username_T";
			this->Username_T->ReadOnly = true;
			// 
			// Address_T
			// 
			this->Address_T->HeaderText = L"Address";
			this->Address_T->Name = L"Address_T";
			this->Address_T->ReadOnly = true;
			// 
			// LastCommand_T
			// 
			this->LastCommand_T->FillWeight = 150;
			this->LastCommand_T->HeaderText = L"";
			this->LastCommand_T->Name = L"LastCommand_T";
			this->LastCommand_T->ReadOnly = true;
			// 
			// Server_Form
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoScroll = true;
			this->ClientSize = System::Drawing::Size(784, 562);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->flowLayoutPanel1);
			this->Controls->Add(this->tabControl1);
			this->MinimumSize = System::Drawing::Size(800, 600);
			this->Name = L"Server_Form";
			this->Padding = System::Windows::Forms::Padding(10);
			this->RightToLeftLayout = true;
			this->Text = L"FTP Server";
			this->Closing += gcnew System::ComponentModel::CancelEventHandler(this, &Server_Form::Server_Form_Closing);
			this->Load += gcnew System::EventHandler(this, &Server_Form::Server_Form_Load);
			this->tabControl1->ResumeLayout(false);
			this->tabPage3->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->EndInit();
			this->flowLayoutPanel1->ResumeLayout(false);
			this->flowLayoutPanel1->PerformLayout();
			this->panel1->ResumeLayout(false);
			this->panel2->ResumeLayout(false);
			this->splitContainer1->Panel1->ResumeLayout(false);
			this->splitContainer1->Panel2->ResumeLayout(false);
			this->splitContainer1->Panel2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->splitContainer1))->EndInit();
			this->splitContainer1->ResumeLayout(false);
			this->flowLayoutPanel2->ResumeLayout(false);
			this->flowLayoutPanel2->PerformLayout();
			this->flowLayoutPanel3->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion

	private:
		System::Void Server_Form_Load(System::Object^  sender, System::EventArgs^  e);
		System::Void Server_Form_Closing(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e);
		System::Void button1_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void button2_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void button3_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void button4_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void button5_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void button6_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void button7_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void button8_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void button9_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void listBox1_DoubleClick(System::Object^  sender, System::EventArgs^  e);
		System::Void listBox2_DoubleClick(System::Object^  sender, System::EventArgs^  e);
		void thread_Load_User(void);
		void thread_Load_Dir(void);
		void thread_Load_User_Dir(Object ^);
		void thread_Listen(void);
		void thread_Connect(Object ^);
};
}
