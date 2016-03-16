#pragma once

namespace auto_bench {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// AutoBenchUI の概要
	/// </summary>
	public ref class AutoBenchUI : public System::Windows::Forms::Form
	{
	public:
		AutoBenchUI(void)
		{
			InitializeComponent();
			//
			//TODO: ここにコンストラクター コードを追加します
			//
		}

	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		~AutoBenchUI()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::SplitContainer^  splitContainer1;
	private: System::Windows::Forms::SplitContainer^  splitContainer2;
	private: System::Windows::Forms::SplitContainer^  splitContainer3;
	private: System::Windows::Forms::CheckedListBox^  checkedListBox1;

	protected:

	private:
		/// <summary>
		/// 必要なデザイナー変数です。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナー サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディターで変更しないでください。
		/// </summary>
		void InitializeComponent(void)
		{
			this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			this->splitContainer2 = (gcnew System::Windows::Forms::SplitContainer());
			this->checkedListBox1 = (gcnew System::Windows::Forms::CheckedListBox());
			this->splitContainer3 = (gcnew System::Windows::Forms::SplitContainer());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->BeginInit();
			this->splitContainer1->Panel2->SuspendLayout();
			this->splitContainer1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer2))->BeginInit();
			this->splitContainer2->Panel1->SuspendLayout();
			this->splitContainer2->Panel2->SuspendLayout();
			this->splitContainer2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer3))->BeginInit();
			this->splitContainer3->SuspendLayout();
			this->SuspendLayout();
			// 
			// splitContainer1
			// 
			this->splitContainer1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer1->FixedPanel = System::Windows::Forms::FixedPanel::Panel1;
			this->splitContainer1->IsSplitterFixed = true;
			this->splitContainer1->Location = System::Drawing::Point(0, 0);
			this->splitContainer1->Name = L"splitContainer1";
			this->splitContainer1->Orientation = System::Windows::Forms::Orientation::Horizontal;
			// 
			// splitContainer1.Panel2
			// 
			this->splitContainer1->Panel2->Controls->Add(this->splitContainer2);
			this->splitContainer1->Size = System::Drawing::Size(411, 415);
			this->splitContainer1->SplitterDistance = 28;
			this->splitContainer1->TabIndex = 0;
			// 
			// splitContainer2
			// 
			this->splitContainer2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer2->FixedPanel = System::Windows::Forms::FixedPanel::Panel1;
			this->splitContainer2->IsSplitterFixed = true;
			this->splitContainer2->Location = System::Drawing::Point(0, 0);
			this->splitContainer2->Name = L"splitContainer2";
			// 
			// splitContainer2.Panel1
			// 
			this->splitContainer2->Panel1->Controls->Add(this->checkedListBox1);
			// 
			// splitContainer2.Panel2
			// 
			this->splitContainer2->Panel2->Controls->Add(this->splitContainer3);
			this->splitContainer2->Size = System::Drawing::Size(411, 383);
			this->splitContainer2->SplitterDistance = 70;
			this->splitContainer2->TabIndex = 0;
			// 
			// checkedListBox1
			// 
			this->checkedListBox1->FormattingEnabled = true;
			this->checkedListBox1->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Iometer", L"CDM", L"AS SSD" });
			this->checkedListBox1->Location = System::Drawing::Point(3, 0);
			this->checkedListBox1->Name = L"checkedListBox1";
			this->checkedListBox1->Size = System::Drawing::Size(65, 46);
			this->checkedListBox1->TabIndex = 0;
			this->checkedListBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &AutoBenchUI::checkedListBox1_SelectedIndexChanged);
			// 
			// splitContainer3
			// 
			this->splitContainer3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer3->FixedPanel = System::Windows::Forms::FixedPanel::Panel1;
			this->splitContainer3->IsSplitterFixed = true;
			this->splitContainer3->Location = System::Drawing::Point(0, 0);
			this->splitContainer3->Name = L"splitContainer3";
			this->splitContainer3->Size = System::Drawing::Size(337, 383);
			this->splitContainer3->SplitterDistance = 123;
			this->splitContainer3->TabIndex = 0;
			// 
			// AutoBenchUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(411, 415);
			this->Controls->Add(this->splitContainer1);
			this->Name = L"AutoBenchUI";
			this->Text = L"Automatic Benchmark Launcher";
			this->splitContainer1->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->EndInit();
			this->splitContainer1->ResumeLayout(false);
			this->splitContainer2->Panel1->ResumeLayout(false);
			this->splitContainer2->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer2))->EndInit();
			this->splitContainer2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer3))->EndInit();
			this->splitContainer3->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: 
		System::Void checkedListBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			if (checkedListBox1->SelectedIndex == 0) {
				System::Windows::Forms::GroupBox^ blockSizeGroup = (gcnew System::Windows::Forms::GroupBox());
				System::Windows::Forms::Label^ blockSizeLabel = (gcnew System::Windows::Forms::Label());
				System::Windows::Forms::Label^ blockSizeUnitLabel = (gcnew System::Windows::Forms::Label());
				System::Windows::Forms::TextBox^ blockSizeInput = (gcnew System::Windows::Forms::TextBox());
				blockSizeLabel->Text = "Block size";
				blockSizeLabel->AutoSize = true;
				blockSizeUnitLabel->Text = "MiB";
				blockSizeUnitLabel->AutoSize = true;
				blockSizeUnitLabel->Location = Point(75, 18);
				blockSizeInput->Text = "100";
				blockSizeInput->Location = Point(2, 15);
				blockSizeInput->Width = 70;
				blockSizeGroup->Controls->Add(blockSizeLabel);
				blockSizeGroup->Controls->Add(blockSizeUnitLabel);
				blockSizeGroup->Controls->Add(blockSizeInput);
				this->splitContainer3->Panel1->Controls->Add(blockSizeGroup);
			}
		}
};
}
