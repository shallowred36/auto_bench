#pragma once

#include <tchar.h>
#include <Windows.h>
#include <fileapi.h>

namespace auto_bench {

	using namespace System;
	using namespace System::Diagnostics;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Windows::Automation;
	using namespace System::Windows;
	using namespace Microsoft::Test::Input;
	using namespace System::Threading;
	using namespace System::Text::RegularExpressions;

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
			resultsUpdateThread = nullptr;
			IometerInitialize();
			CDMInitialize();
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
	private: System::Windows::Forms::Button^  button1;

    //Iometer-related form objects
	private:
		System::Windows::Forms::Panel^ iometerPanel;
		System::Windows::Forms::GroupBox^ blockSizeGroup;
		System::Windows::Forms::Label^ blockSizeLabel;
		System::Windows::Forms::Label^ blockSizeUnitLabel;
		System::Windows::Forms::TextBox^ blockSizeInput;
		System::Windows::Forms::GroupBox^ iometerTargetGroup;
		System::Windows::Forms::Label^ iometerTargetLabel;
		System::Windows::Forms::ComboBox^ iometerTargetCombo;
		System::Windows::Forms::GroupBox^ iometerDataSizeGroup;
		System::Windows::Forms::Label^ iometerDataSizeLabel;
		System::Windows::Forms::Label^ iometerDataSizeUnitLabel;
		System::Windows::Forms::TextBox^ iometerDataSizeInput;
		System::Windows::Forms::GroupBox^ iometerQueueGroup;
		System::Windows::Forms::Label^ iometerQueueLabel;
		System::Windows::Forms::TextBox^ iometerQueueInput;
		System::Windows::Forms::DataGridView^ iometerResultsDataView;
		System::Windows::Forms::GroupBox^ iometerRampUpTimeGroup;
		System::Windows::Forms::Label^ iometerRampUpTimeLabel;
		System::Windows::Forms::Label^ iometerRampUpTimeUnitLabel;
		System::Windows::Forms::TextBox^ iometerRampUpTimeInput;
		System::Windows::Forms::GroupBox^ iometerRunTimeGroup;
		System::Windows::Forms::Label^ iometerRunTimeLabel;
		System::Windows::Forms::Label^ iometerRunTimeUnitLabel;
		System::Windows::Forms::TextBox^ iometerRunTimeInput;
		IEnumerator^ eachBlockSize;
		Process^ iometerProcess;

	//CDM-related form objects
	private:
		System::Windows::Forms::Panel^ CDMPanel;
		System::Windows::Forms::GroupBox^ dataSizeGroup;
		System::Windows::Forms::Label^ dataSizeLabel;
		System::Windows::Forms::ComboBox^ dataSizeCombo;
		System::Windows::Forms::GroupBox^ CDMTargetGroup;
		System::Windows::Forms::Label^ CDMTargetLabel;
		System::Windows::Forms::ComboBox^ CDMTargetCombo;
		System::Windows::Forms::GroupBox^ CDMQueueGroup;
		System::Windows::Forms::Label^ CDMQueueLabel;
		System::Windows::Forms::ComboBox^ CDMQueueCombo;
		System::Windows::Forms::DataGridView^ CDMResultsDataView;
		System::Windows::Forms::GroupBox^ CDMTestCountGroup;
		System::Windows::Forms::Label^ CDMTestCountLabel;
		System::Windows::Forms::ComboBox^ CDMTestCountCombo;
		Process^ cdmProcess;

	//Common properties
	private:
		Thread^ resultsUpdateThread;

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
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->splitContainer2 = (gcnew System::Windows::Forms::SplitContainer());
			this->checkedListBox1 = (gcnew System::Windows::Forms::CheckedListBox());
			this->splitContainer3 = (gcnew System::Windows::Forms::SplitContainer());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->BeginInit();
			this->splitContainer1->Panel1->SuspendLayout();
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
			// splitContainer1.Panel1
			// 
			this->splitContainer1->Panel1->Controls->Add(this->button1);
			// 
			// splitContainer1.Panel2
			// 
			this->splitContainer1->Panel2->Controls->Add(this->splitContainer2);
			this->splitContainer1->Size = System::Drawing::Size(700, 500);
			this->splitContainer1->SplitterDistance = 28;
			this->splitContainer1->TabIndex = 0;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(3, 2);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(40, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"開始";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &AutoBenchUI::button1_Click);
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
			this->splitContainer2->Size = System::Drawing::Size(700, 468);
			this->splitContainer2->SplitterDistance = 70;
			this->splitContainer2->TabIndex = 0;
			// 
			// checkedListBox1
			// 
			this->checkedListBox1->FormattingEnabled = true;
			this->checkedListBox1->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Iometer", L"CDM" });
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
			this->splitContainer3->Size = System::Drawing::Size(626, 468);
			this->splitContainer3->SplitterDistance = 123;
			this->splitContainer3->TabIndex = 0;
			// 
			// AutoBenchUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1130, 500);
			this->Controls->Add(this->splitContainer1);
			this->Name = L"AutoBenchUI";
			this->Text = L"Automatic Benchmark Launcher";
			this->splitContainer1->Panel1->ResumeLayout(false);
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
		void ListDrives(int index);
		void IometerInitialize(void);
		void CDMInitialize(void);
		System::Void checkedListBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
		System::Void button1_Click(System::Object^  sender, System::EventArgs^  e);
		void IometerResultsConfigure(void);
		void IometerConfigure(void);
		void CDMResultsConfigure(void);
		void CDMConfigure(void);
		void StopThread(void);
	public:
		void UpdateThreadProc(void);
		void CDMUpdateThreadProc(void);
};
}
