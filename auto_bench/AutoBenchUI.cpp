#include "AutoBenchUI.h"

using namespace auto_bench;

System::Void AutoBenchUI::checkedListBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	if (checkedListBox1->SelectedIndex == 0) {
		splitContainer3->Panel1->Controls->Clear();
		ListDrives();
		splitContainer3->Panel1->Controls->Add(iometerPanel);
	}
	else if (checkedListBox1->SelectedIndex == 1) {
		splitContainer3->Panel1->Controls->Clear();
		splitContainer3->Panel1->Controls->Add(CDMPanel);
	}
	else if (checkedListBox1->SelectedIndex == 2) {

	}
}

System::Void AutoBenchUI::button1_Click(System::Object^  sender, System::EventArgs^  e) {
	IEnumerator^ benchEnum = checkedListBox1->CheckedIndices->GetEnumerator();
	while (benchEnum->MoveNext()) {
		Int32 indexChecked = *safe_cast<Int32^>(benchEnum->Current);
		if (indexChecked == 0) {
			Process::Start("iometer\\IOmeter.exe");
		}
		else if (indexChecked == 1) {
			Process::Start("CDM\\DiskMark32.exe");
		}
	}
}

void AutoBenchUI::ListDrives(void) {
	TCHAR szDrives[256] = { 0 };
	LPTSTR pDrive = szDrives;
	GetLogicalDriveStrings(255, szDrives);
	//List<String ^>^ drives = gcnew List<String ^>();
	//String^ test = gcnew String(pDrive);
	//MessageBox::Show(test);
	while (pDrive[0] != _T('\0')) {
		int result = GetDriveType(pDrive);
		int forward = (int)_tcslen(pDrive);
		if (result == DRIVE_FIXED || result == DRIVE_REMOTE || result == DRIVE_REMOVABLE || result == DRIVE_RAMDISK) {
			iometerTargetCombo->Items->Add(String::Format("%C: ", pDrive[0]));
		}
		pDrive += forward + 1;
	}
}

void AutoBenchUI::IometerInitialize(void) {
	iometerPanel = (gcnew System::Windows::Forms::Panel());
	blockSizeGroup = (gcnew System::Windows::Forms::GroupBox());
	blockSizeLabel = (gcnew System::Windows::Forms::Label());
	blockSizeUnitLabel = (gcnew System::Windows::Forms::Label());
	blockSizeInput = (gcnew System::Windows::Forms::TextBox());
	iometerTargetGroup = (gcnew System::Windows::Forms::GroupBox());
	iometerTargetLabel = (gcnew System::Windows::Forms::Label());
	iometerTargetCombo = (gcnew System::Windows::Forms::ComboBox());
	blockSizeLabel->Text = "Block size";
	blockSizeLabel->AutoSize = true;
	blockSizeUnitLabel->Text = "KiB";
	blockSizeUnitLabel->AutoSize = true;
	blockSizeUnitLabel->Location = Point(75, 18);
	blockSizeInput->Text = "128";
	blockSizeInput->Location = Point(2, 15);
	blockSizeInput->Width = 70;
	blockSizeGroup->Controls->Add(blockSizeLabel);
	blockSizeGroup->Controls->Add(blockSizeUnitLabel);
	blockSizeGroup->Controls->Add(blockSizeInput);
	iometerTargetLabel->Text = "Target";
	iometerTargetLabel->AutoSize = true;
	iometerTargetCombo->AutoSize = true;
	iometerTargetGroup->Controls->Add(iometerTargetLabel);
	iometerTargetGroup->Controls->Add(iometerTargetCombo);
	iometerTargetGroup->Location = Point(0, 50);
	iometerPanel->Controls->Add(blockSizeGroup);
	iometerPanel->Controls->Add(iometerTargetGroup);
}

void AutoBenchUI::CDMInitialize(void) {
	CDMPanel = (gcnew System::Windows::Forms::Panel());
	dataSizeGroup = (gcnew System::Windows::Forms::GroupBox());
	dataSizeLabel = (gcnew System::Windows::Forms::Label());
	dataSizeCombo = (gcnew System::Windows::Forms::ComboBox());
	dataSizeLabel->Text = "Data size";
	dataSizeLabel->AutoSize = true;
	//dataSizeCombo->Anchor = (System::Windows::Forms::AnchorStyles)(
	//	(System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) |
	//	System::Windows::Forms::AnchorStyles::Right);
	array<Object ^>^ sizeArray = { "50MiB", "100MiB", "500MiB", "1GiB", "2GiB", "4GiB", "8GiB", "16GiB", "32GiB" };
	dataSizeCombo->Items->AddRange(sizeArray);
	dataSizeCombo->AutoSize = true;
	dataSizeCombo->Location = Point(2, 15);
	dataSizeCombo->Text = "1GiB";
	dataSizeGroup->Controls->Add(dataSizeLabel);
	dataSizeGroup->Controls->Add(dataSizeCombo);
	CDMPanel->Controls->Add(dataSizeGroup);
}

void AutoBenchUI::ASSSDInitialize(void) {

}