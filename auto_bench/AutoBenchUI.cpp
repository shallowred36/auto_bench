#include "AutoBenchUI.h"

using namespace auto_bench;

System::Void AutoBenchUI::checkedListBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
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
		splitContainer3->Panel1->Controls->Add(blockSizeGroup);
	}
}

System::Void AutoBenchUI::button1_Click(System::Object^  sender, System::EventArgs^  e) {
	Process::Start("IOmeter.exe");
}