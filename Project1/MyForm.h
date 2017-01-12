#pragma once
#include "Sorts.h"
#include <windows.h>





namespace Project1 {

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
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::Button^  button6;
	public:
		Sorts s1;

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
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(223, 54);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(130, 56);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Bucket Sort";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(223, 116);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(130, 56);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Radix Sort";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(223, 178);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(130, 56);
			this->button3->TabIndex = 2;
			this->button3->Text = L"Merge Sort Merging";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(223, 425);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(130, 24);
			this->button4->TabIndex = 3;
			this->button4->Text = L"Exit!";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(223, 252);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(130, 56);
			this->button5->TabIndex = 4;
			this->button5->Text = L"Hashing\r\n(Linear Probing)";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &MyForm::button5_Click);
			// 
			// button6
			// 
			this->button6->Location = System::Drawing::Point(223, 324);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(130, 56);
			this->button6->TabIndex = 5;
			this->button6->Text = L"Hashing\r\n(Separate Chaining)";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &MyForm::button6_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->ClientSize = System::Drawing::Size(584, 461);
			this->ControlBox = false;
			this->Controls->Add(this->button6);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->MaximizeBox = false;
			this->Name = L"MyForm";
			this->Text = L"Sorting and Hashing Applet";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				 s1.playbucketsort();
	}

    private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
			 s1.playradixsort();
	}

	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
				 s1.playmergesort();
	}
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
			 exit(0);
}
private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {
			 s1.playlinearprobing();
}
private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e) {
			 s1.playseparatechaining();
}

};
}
