#pragma once
#include "syntax_tree.h"
namespace guitryclr {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	// using namespace msclr::interop;

	void MarshalString(String^ s, std::string& os) {
		using namespace Runtime::InteropServices;
		const char* chars =
			(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
		os = chars;
		Marshal::FreeHGlobal(IntPtr((void*)chars));
	}
	std::list<tokens> tokens_list;
	std::string cpp_str;
	/// <summary>
	/// Summary for gui_form
	/// </summary>
	public ref class gui_form : public System::Windows::Forms::Form
	{
	public:
		gui_form(void)
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
		~gui_form()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
	protected:
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::TextBox^ textBox2;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(12, 12);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(90, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Scan From Text";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &gui_form::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(108, 12);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(90, 23);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Open File";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &gui_form::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(204, 12);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(90, 23);
			this->button3->TabIndex = 2;
			this->button3->Text = L"Parse";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &gui_form::button3_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(12, 41);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(294, 282);
			this->textBox1->TabIndex = 3;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(312, 41);
			this->textBox2->Multiline = true;
			this->textBox2->Name = L"textBox2";
			this->textBox2->ReadOnly = true;
			this->textBox2->Size = System::Drawing::Size(209, 282);
			this->textBox2->TabIndex = 4;
			this->textBox2->ScrollBars = ScrollBars::Vertical;
			// 
			// gui_form
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(533, 335);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Name = L"gui_form";
			this->Text = L"Tiny Compiler";
			this->Load += gcnew System::EventHandler(this, &gui_form::gui_form_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void gui_form_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ user_txt = textBox1->Text;
		MarshalString(user_txt, cpp_str);
		tokens_list.clear();
		getToken(cpp_str, tokens_list);
		std::string tokens_str;
		for (auto i = tokens_list.begin(); i != tokens_list.end(); i++)
		{
			tokens_str += i->token + "\t:" + i->token_type + "\r\n";
		}
		String^ txt_box_cs = gcnew String(tokens_str.c_str());
		textBox2->Text = txt_box_cs;
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		OpenFileDialog^ open_text_file = gcnew OpenFileDialog();
		open_text_file->FileName = "Select a text file";
		open_text_file->Filter = "Text files (*.txt)|*.txt";
		open_text_file->Title = "Open text file";
		if (open_text_file->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			auto sr = gcnew StreamReader(open_text_file->FileName);
			textBox1->Text = sr->ReadToEnd();
		}

	}
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		draw_tree(cpp_str);
	}
	};
}
