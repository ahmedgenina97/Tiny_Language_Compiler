#pragma once
#include "scanner.h"
#include <list>
#include <string>
#include <msclr\marshal_cppstd.h>




namespace TinyCompiler {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;


	

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ editToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ helpToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ teamToolStripMenuItem;
	private: System::Windows::Forms::Label^ lb1;

	private: System::Windows::Forms::ListBox^ tokenlist;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ scanbtn;

	private: System::Windows::Forms::RichTextBox^ richTextBox1;

	private: System::Windows::Forms::Button^ clear;
	private: System::Windows::Forms::ContextMenuStrip^ contextMenuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ clearToolStripMenuItem;

	private: System::Windows::Forms::ToolStripMenuItem^ pastToolStripMenuItem;





	protected:


	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->editToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->teamToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->lb1 = (gcnew System::Windows::Forms::Label());
			this->tokenlist = (gcnew System::Windows::Forms::ListBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->scanbtn = (gcnew System::Windows::Forms::Button());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->contextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->clearToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pastToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->clear = (gcnew System::Windows::Forms::Button());
			this->menuStrip1->SuspendLayout();
			this->contextMenuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->fileToolStripMenuItem,
					this->editToolStripMenuItem, this->helpToolStripMenuItem, this->teamToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(793, 24);
			this->menuStrip1->TabIndex = 1;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->fileToolStripMenuItem->Text = L"File";
			this->fileToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::fileToolStripMenuItem_Click);
			// 
			// editToolStripMenuItem
			// 
			this->editToolStripMenuItem->Name = L"editToolStripMenuItem";
			this->editToolStripMenuItem->Size = System::Drawing::Size(39, 20);
			this->editToolStripMenuItem->Text = L"Edit";
			this->editToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::editToolStripMenuItem_Click);
			// 
			// helpToolStripMenuItem
			// 
			this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
			this->helpToolStripMenuItem->Size = System::Drawing::Size(44, 20);
			this->helpToolStripMenuItem->Text = L"Help";
			this->helpToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::helpToolStripMenuItem_Click);
			// 
			// teamToolStripMenuItem
			// 
			this->teamToolStripMenuItem->Name = L"teamToolStripMenuItem";
			this->teamToolStripMenuItem->Size = System::Drawing::Size(47, 20);
			this->teamToolStripMenuItem->Text = L"Team";
			this->teamToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::teamToolStripMenuItem_Click);
			// 
			// lb1
			// 
			this->lb1->AutoSize = true;
			this->lb1->Location = System::Drawing::Point(179, 30);
			this->lb1->Name = L"lb1";
			this->lb1->Size = System::Drawing::Size(106, 13);
			this->lb1->TabIndex = 2;
			this->lb1->Text = L"Tiny Language Code";
			// 
			// tokenlist
			// 
			this->tokenlist->FormattingEnabled = true;
			this->tokenlist->Location = System::Drawing::Point(518, 45);
			this->tokenlist->Name = L"tokenlist";
			this->tokenlist->Size = System::Drawing::Size(263, 667);
			this->tokenlist->TabIndex = 3;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(628, 30);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(43, 13);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Tokens";
			// 
			// scanbtn
			// 
			this->scanbtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->scanbtn->Location = System::Drawing::Point(121, 718);
			this->scanbtn->Name = L"scanbtn";
			this->scanbtn->Size = System::Drawing::Size(181, 34);
			this->scanbtn->TabIndex = 5;
			this->scanbtn->Text = L"Tokens Scan";
			this->scanbtn->UseVisualStyleBackColor = true;
			this->scanbtn->Click += gcnew System::EventHandler(this, &MyForm::scanbtn_Click);
			// 
			// richTextBox1
			// 
			this->richTextBox1->ContextMenuStrip = this->contextMenuStrip1;
			this->richTextBox1->Location = System::Drawing::Point(12, 45);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(500, 667);
			this->richTextBox1->TabIndex = 7;
			this->richTextBox1->Text = L"";
			// 
			// contextMenuStrip1
			// 
			this->contextMenuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->clearToolStripMenuItem,
					this->pastToolStripMenuItem
			});
			this->contextMenuStrip1->Name = L"contextMenuStrip1";
			this->contextMenuStrip1->Size = System::Drawing::Size(103, 48);
			this->contextMenuStrip1->Opening += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::contextMenuStrip1_Opening);
			// 
			// clearToolStripMenuItem
			// 
			this->clearToolStripMenuItem->Name = L"clearToolStripMenuItem";
			this->clearToolStripMenuItem->Size = System::Drawing::Size(101, 22);
			this->clearToolStripMenuItem->Text = L"Clear";
			this->clearToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::clearToolStripMenuItem_Click);
			// 
			// pastToolStripMenuItem
			// 
			this->pastToolStripMenuItem->Name = L"pastToolStripMenuItem";
			this->pastToolStripMenuItem->Size = System::Drawing::Size(102, 22);
			this->pastToolStripMenuItem->Text = L"Paste";
			this->pastToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::pastToolStripMenuItem_Click);
			// 
			// clear
			// 
			this->clear->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->clear->Location = System::Drawing::Point(322, 718);
			this->clear->Name = L"clear";
			this->clear->Size = System::Drawing::Size(181, 34);
			this->clear->TabIndex = 9;
			this->clear->Text = L"Clear";
			this->clear->UseVisualStyleBackColor = true;
			this->clear->Click += gcnew System::EventHandler(this, &MyForm::clear_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(793, 759);
			this->Controls->Add(this->clear);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->scanbtn);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->tokenlist);
			this->Controls->Add(this->lb1);
			this->Controls->Add(this->menuStrip1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Tiny Language Compiler";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->contextMenuStrip1->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	
private: System::Void scanbtn_Click(System::Object^ sender, System::EventArgs^ e) {

	tokenlist->Items->Clear();
	if (richTextBox1->TextLength == 0)
	{
		MessageBox::Show("Please Put Some Code", "Error");
	}

	else {

		array<String^>^ strLines = richTextBox1->Lines;
		std::list<tokens> code_tokens;
		auto len = strLines->Length;
		std::string codeline = "";

		for (int i = 0; i < len; i++)
		{
			System::String^ managed = strLines[i];
			std::string unmanaged = msclr::interop::marshal_as<std::string>(managed);
			codeline = codeline + " " + unmanaged;
			//richTextBox1->AppendText("#");
		}

		getToken(codeline, code_tokens);
		for (auto v : code_tokens)
		{
			String^ token_id = gcnew String(v.token.c_str());
			String^ token_ty = gcnew String(v.token_type.c_str());
			tokenlist->Items->Add(token_id + "		-------	" + token_ty);
		}

	}

	
}


private: System::Void clear_Click(System::Object^ sender, System::EventArgs^ e) {
	richTextBox1->Clear();
	tokenlist->Items->Clear();
	
}


private: System::Void fileToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	MessageBox::Show("Not Activated Yet", "Tiny Compiler CSE422");
}
private: System::Void editToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	MessageBox::Show("Not Activated Yet", "Tiny Compiler CSE422");
}
private: System::Void helpToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	MessageBox::Show("Not Activated Yet", "Tiny Compiler CSE422");
}
private: System::Void teamToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	MessageBox::Show("Mohamed Fathi Mohamed Razzk - 16x0103\n\
Mohamed Amr Yahia Syaed - 1601251\n\
Salma Ali AbdElrahim Awad - 1600654\n\
Mamdouh Walid Mamdouh - 1501482\n\
Asmaa Gamal ElSayed Alioah - 1400281\n\
Ahmed Mostafa Mostafa ElSayed -16E0030\n\
Mariam Adel AbdElmohsed AbdElhamed - 1701402 \n\
Marwa Fouad Hussain Mohamed - 1701394\n\
", "Tiny Compiler CSE422 - Team ");
}
private: System::Void clearToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	richTextBox1->Clear();
}
private: System::Void pastToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	richTextBox1->Paste();
}
private: System::Void contextMenuStrip1_Opening(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e) {
}
};
}
