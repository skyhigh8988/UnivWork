#include <winsock2.h>
#include <fstream>
#pragma comment(lib,"wsock32.lib")
#pragma once

namespace FTPClientVerNetwork {
	
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

	public ref class Client_Form : public System::Windows::Forms::Form
	{
	public:
		Client_Form(void)
		{
			InitializeComponent();
			CheckForIllegalCrossThreadCalls = false;
			processCount = 0;
			transCount = -1;
			queueFile = gcnew Queue();
		}

	protected:
		~Client_Form()
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
		System::Windows::Forms::RichTextBox^  richTextBox1;
		System::Windows::Forms::TabControl^  tabControl1;
		System::Windows::Forms::TabPage^  tabPage1;
		System::Windows::Forms::TextBox^  textBox1;
		System::Windows::Forms::TextBox^  textBox2;
		System::Windows::Forms::TextBox^  textBox3;
		System::Windows::Forms::TextBox^  textBox4;
		System::Windows::Forms::TextBox^  textBox5;
		System::Windows::Forms::TextBox^  textBox6;
		System::Windows::Forms::TextBox^  textBox7;
		System::Windows::Forms::ListBox^  listBox1;
		System::Windows::Forms::ListBox^  listBox2;
		System::Windows::Forms::Button^  button1;
		System::Windows::Forms::Button^  button2;
		System::Windows::Forms::Button^  button3;
		System::Windows::Forms::Button^  button4;
		System::Windows::Forms::Button^  button6;
		System::Windows::Forms::Button^  button8;
		System::Windows::Forms::Button^  button9;
		System::Windows::Forms::Button^  button10;
		System::Windows::Forms::Label^  label1;
		System::Windows::Forms::Label^  label2;
		System::Windows::Forms::Label^  label3;
		System::Windows::Forms::Label^  label4;
		System::Windows::Forms::Label^  label5;
		System::Windows::Forms::Panel^  panel1;
		System::Windows::Forms::Panel^  panel2;
		System::Windows::Forms::Panel^  panel3;
		System::Windows::Forms::Panel^  panel4;
		System::ComponentModel::Container ^components;
		array<Label^>^ labelFileName;
		array<Label^>^ labelFileDire;
		array<Label^>^ labelFileSize;
		array<Label^>^ labelFileState;
		array<ProgressBar^>^ progressBarTrans;

	private:
		Thread^ threadMain;
		Thread^ threadClientDir;
		Thread^ threadForceLogout;
		array<Thread^>^ threadTrans;
		Queue^ queueFile;
		String^ currentPath;
		SOCKET socketServerCmd;
		int dirSplit;
		int transCount;
		int processCount;
		array<int>^ turn;
		array<int>^ flag;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->textBox7 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->flowLayoutPanel2 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->listBox2 = (gcnew System::Windows::Forms::ListBox());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->flowLayoutPanel3 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->button10 = (gcnew System::Windows::Forms::Button());
			this->panel4 = (gcnew System::Windows::Forms::Panel());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->tabControl1->SuspendLayout();
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
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->tabControl1->Location = System::Drawing::Point(10, 422);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(764, 130);
			this->tabControl1->TabIndex = 0;
			// 
			// tabPage1
			// 
			this->tabPage1->AutoScroll = true;
			this->tabPage1->BackColor = System::Drawing::Color::White;
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(756, 104);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"傳輸";
			// 
			// flowLayoutPanel1
			// 
			this->flowLayoutPanel1->Controls->Add(this->label1);
			this->flowLayoutPanel1->Controls->Add(this->textBox1);
			this->flowLayoutPanel1->Controls->Add(this->label2);
			this->flowLayoutPanel1->Controls->Add(this->textBox2);
			this->flowLayoutPanel1->Controls->Add(this->label3);
			this->flowLayoutPanel1->Controls->Add(this->textBox3);
			this->flowLayoutPanel1->Controls->Add(this->label4);
			this->flowLayoutPanel1->Controls->Add(this->textBox4);
			this->flowLayoutPanel1->Controls->Add(this->label5);
			this->flowLayoutPanel1->Controls->Add(this->textBox7);
			this->flowLayoutPanel1->Controls->Add(this->button1);
			this->flowLayoutPanel1->Controls->Add(this->button2);
			this->flowLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Top;
			this->flowLayoutPanel1->Location = System::Drawing::Point(10, 10);
			this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
			this->flowLayoutPanel1->Size = System::Drawing::Size(764, 28);
			this->flowLayoutPanel1->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(3, 8);
			this->label1->Margin = System::Windows::Forms::Padding(3, 8, 3, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(32, 12);
			this->label1->TabIndex = 0;
			this->label1->Text = L"主機:";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(41, 3);
			this->textBox1->MaxLength = 64;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 22);
			this->textBox1->TabIndex = 1;
			this->textBox1->Text = L"127.0.0.1";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(147, 8);
			this->label2->Margin = System::Windows::Forms::Padding(3, 8, 3, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(44, 12);
			this->label2->TabIndex = 0;
			this->label2->Text = L"使用者:";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(197, 3);
			this->textBox2->MaxLength = 128;
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(100, 22);
			this->textBox2->TabIndex = 1;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(303, 8);
			this->label3->Margin = System::Windows::Forms::Padding(3, 8, 3, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(32, 12);
			this->label3->TabIndex = 0;
			this->label3->Text = L"密碼:";
			this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(341, 3);
			this->textBox3->MaxLength = 128;
			this->textBox3->Name = L"textBox3";
			this->textBox3->PasswordChar = '*';
			this->textBox3->Size = System::Drawing::Size(80, 22);
			this->textBox3->TabIndex = 1;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(427, 8);
			this->label4->Margin = System::Windows::Forms::Padding(3, 8, 3, 0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(44, 12);
			this->label4->TabIndex = 0;
			this->label4->Text = L"連接埠:";
			this->label4->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(477, 3);
			this->textBox4->MaxLength = 6;
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(50, 22);
			this->textBox4->TabIndex = 1;
			this->textBox4->Text = L"7497";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(533, 8);
			this->label5->Margin = System::Windows::Forms::Padding(3, 8, 3, 0);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(68, 12);
			this->label5->TabIndex = 0;
			this->label5->Text = L"最大連接數:";
			this->label5->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// textBox7
			// 
			this->textBox7->Location = System::Drawing::Point(607, 3);
			this->textBox7->MaxLength = 6;
			this->textBox7->Name = L"textBox7";
			this->textBox7->Size = System::Drawing::Size(50, 22);
			this->textBox7->TabIndex = 1;
			this->textBox7->Text = L"5";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(663, 2);
			this->button1->Margin = System::Windows::Forms::Padding(3, 2, 3, 3);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(40, 23);
			this->button1->TabIndex = 2;
			this->button1->Text = L"連線";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Client_Form::button1_Click);
			// 
			// button2
			// 
			this->button2->Enabled = false;
			this->button2->Location = System::Drawing::Point(709, 2);
			this->button2->Margin = System::Windows::Forms::Padding(3, 2, 3, 3);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(40, 23);
			this->button2->TabIndex = 2;
			this->button2->Text = L"中斷";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Client_Form::button2_Click);
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
			this->richTextBox1->TabIndex = 0;
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
			this->splitContainer1->Panel1->Controls->Add(this->textBox5);
			this->splitContainer1->Panel1->Controls->Add(this->flowLayoutPanel2);
			this->splitContainer1->Panel1MinSize = 380;
			// 
			// splitContainer1.Panel2
			// 
			this->splitContainer1->Panel2->BackColor = System::Drawing::SystemColors::Control;
			this->splitContainer1->Panel2->Controls->Add(this->listBox2);
			this->splitContainer1->Panel2->Controls->Add(this->textBox6);
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
			this->listBox1->HorizontalScrollbar = true;
			this->listBox1->ItemHeight = 15;
			this->listBox1->Location = System::Drawing::Point(0, 50);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(380, 214);
			this->listBox1->TabIndex = 3;
			this->listBox1->DoubleClick += gcnew System::EventHandler(this, &Client_Form::listBox1_DoubleClick);
			// 
			// textBox5
			// 
			this->textBox5->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->textBox5->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->textBox5->Dock = System::Windows::Forms::DockStyle::Top;
			this->textBox5->Location = System::Drawing::Point(0, 28);
			this->textBox5->Name = L"textBox5";
			this->textBox5->ReadOnly = true;
			this->textBox5->Size = System::Drawing::Size(380, 22);
			this->textBox5->TabIndex = 2;
			// 
			// flowLayoutPanel2
			// 
			this->flowLayoutPanel2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->flowLayoutPanel2->Controls->Add(this->button6);
			this->flowLayoutPanel2->Controls->Add(this->button3);
			this->flowLayoutPanel2->Controls->Add(this->button4);
			this->flowLayoutPanel2->Dock = System::Windows::Forms::DockStyle::Top;
			this->flowLayoutPanel2->Location = System::Drawing::Point(0, 0);
			this->flowLayoutPanel2->Name = L"flowLayoutPanel2";
			this->flowLayoutPanel2->Size = System::Drawing::Size(380, 28);
			this->flowLayoutPanel2->TabIndex = 1;
			// 
			// button6
			// 
			this->button6->Location = System::Drawing::Point(3, 2);
			this->button6->Margin = System::Windows::Forms::Padding(3, 2, 3, 3);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(40, 23);
			this->button6->TabIndex = 2;
			this->button6->Text = L"重整";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &Client_Form::button6_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(49, 2);
			this->button3->Margin = System::Windows::Forms::Padding(3, 2, 3, 3);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(40, 23);
			this->button3->TabIndex = 2;
			this->button3->Text = L"上傳";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Client_Form::button3_Click);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(95, 2);
			this->button4->Margin = System::Windows::Forms::Padding(3, 2, 3, 3);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(40, 23);
			this->button4->TabIndex = 2;
			this->button4->Text = L"刪除";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &Client_Form::button4_Click);
			// 
			// listBox2
			// 
			this->listBox2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->listBox2->Font = (gcnew System::Drawing::Font(L"新細明體", 11));
			this->listBox2->FormattingEnabled = true;
			this->listBox2->HorizontalScrollbar = true;
			this->listBox2->ItemHeight = 15;
			this->listBox2->Location = System::Drawing::Point(0, 50);
			this->listBox2->Name = L"listBox2";
			this->listBox2->Size = System::Drawing::Size(380, 214);
			this->listBox2->TabIndex = 4;
			this->listBox2->DoubleClick += gcnew System::EventHandler(this, &Client_Form::listBox2_DoubleClick);
			// 
			// textBox6
			// 
			this->textBox6->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->textBox6->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->textBox6->Dock = System::Windows::Forms::DockStyle::Top;
			this->textBox6->Location = System::Drawing::Point(0, 28);
			this->textBox6->Name = L"textBox6";
			this->textBox6->ReadOnly = true;
			this->textBox6->Size = System::Drawing::Size(380, 22);
			this->textBox6->TabIndex = 3;
			// 
			// flowLayoutPanel3
			// 
			this->flowLayoutPanel3->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->flowLayoutPanel3->Controls->Add(this->button8);
			this->flowLayoutPanel3->Controls->Add(this->button9);
			this->flowLayoutPanel3->Controls->Add(this->button10);
			this->flowLayoutPanel3->Dock = System::Windows::Forms::DockStyle::Top;
			this->flowLayoutPanel3->Location = System::Drawing::Point(0, 0);
			this->flowLayoutPanel3->Name = L"flowLayoutPanel3";
			this->flowLayoutPanel3->Size = System::Drawing::Size(380, 28);
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
			this->button8->Click += gcnew System::EventHandler(this, &Client_Form::button8_Click);
			// 
			// button9
			// 
			this->button9->Location = System::Drawing::Point(49, 2);
			this->button9->Margin = System::Windows::Forms::Padding(3, 2, 3, 3);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(40, 23);
			this->button9->TabIndex = 2;
			this->button9->Text = L"下載";
			this->button9->UseVisualStyleBackColor = true;
			this->button9->Click += gcnew System::EventHandler(this, &Client_Form::button9_Click);
			// 
			// button10
			// 
			this->button10->Location = System::Drawing::Point(95, 2);
			this->button10->Margin = System::Windows::Forms::Padding(3, 2, 3, 3);
			this->button10->Name = L"button10";
			this->button10->Size = System::Drawing::Size(40, 23);
			this->button10->TabIndex = 2;
			this->button10->Text = L"刪除";
			this->button10->UseVisualStyleBackColor = true;
			this->button10->Click += gcnew System::EventHandler(this, &Client_Form::button10_Click);
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
			// Client_Form
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
			this->Name = L"Client_Form";
			this->Padding = System::Windows::Forms::Padding(10);
			this->RightToLeftLayout = true;
			this->Text = L"FTP Client";
			this->Closing += gcnew System::ComponentModel::CancelEventHandler(this, &Client_Form::Client_Form_Closing);
			this->Load += gcnew System::EventHandler(this, &Client_Form::Client_Form_Load);
			this->tabControl1->ResumeLayout(false);
			this->flowLayoutPanel1->ResumeLayout(false);
			this->flowLayoutPanel1->PerformLayout();
			this->panel1->ResumeLayout(false);
			this->panel2->ResumeLayout(false);
			this->splitContainer1->Panel1->ResumeLayout(false);
			this->splitContainer1->Panel1->PerformLayout();
			this->splitContainer1->Panel2->ResumeLayout(false);
			this->splitContainer1->Panel2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->splitContainer1))->EndInit();
			this->splitContainer1->ResumeLayout(false);
			this->flowLayoutPanel2->ResumeLayout(false);
			this->flowLayoutPanel3->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion

	private:
		System::Void Client_Form_Load(System::Object^  sender, System::EventArgs^  e);
		System::Void Client_Form_Closing(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e);
		System::Void button1_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void button2_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void button3_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void button4_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void button6_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void button8_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void button9_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void button10_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void listBox1_DoubleClick(System::Object^  sender, System::EventArgs^  e);
		System::Void listBox2_DoubleClick(System::Object^  sender, System::EventArgs^  e);

		void thread_Client_Dir(void);
		void thread_Login(void);
		void thread_Logout(void);
		void thread_Force_Logout(void);
		void thread_Up_Dir(void);
		void thread_Refresh_Dir(void);
		void thread_Change_Dir(Object^ obj);
		void thread_Download(Object^ obj);
		void thread_Upload(Object^ obj);
		void thread_Delete(Object^ obj);
};
}
