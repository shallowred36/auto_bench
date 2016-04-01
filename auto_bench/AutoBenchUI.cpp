#include "AutoBenchUI.h"

using namespace auto_bench;

System::Void AutoBenchUI::checkedListBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	if (checkedListBox1->SelectedIndex == 0) {
		splitContainer3->Panel1->Controls->Clear();
		ListDrives(0);
		splitContainer3->Panel1->Controls->Add(iometerPanel);
	}
	else if (checkedListBox1->SelectedIndex == 1) {
		splitContainer3->Panel1->Controls->Clear();
		ListDrives(1);
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
			Process^ iometerProcess = gcnew Process;
			ProcessStartInfo^ iometerProcessStartInfo = gcnew ProcessStartInfo;
			iometerProcessStartInfo->FileName = "iometer\\IOmeter.exe";
			iometerProcess->StartInfo = iometerProcessStartInfo;
			iometerProcess->Start();
			iometerProcess->WaitForInputIdle();
			//MessageBox::Show("Starting IOmeter...");
			IometerConfigure(iometerProcess);
			//Sleep(1000);
			//iometerProcess->CloseMainWindow();
			//iometerProcess->Close();
		}
		else if (indexChecked == 1) {
			Process^ cdmProcess = gcnew Process;
			ProcessStartInfo^ cdmProcessStartInfo = gcnew ProcessStartInfo;
			cdmProcessStartInfo->FileName = "CDM\\DiskMark32.exe";
			cdmProcess->StartInfo = cdmProcessStartInfo;
			cdmProcess->Start();
			cdmProcess->WaitForInputIdle();
			//MessageBox::Show("Starting CrystalDiskMark...");
			//cdmProcess->CloseMainWindow();
			//cdmProcess->Close();
		}
	}
}

/*System::Void AutoBenchUI::groupBox_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {

}*/

void AutoBenchUI::ListDrives(int index) {
	TCHAR szDrives[256] = { 0 };
	LPTSTR pDrive = szDrives;
	GetLogicalDriveStrings(255, szDrives);
	//List<String ^>^ drives = gcnew List<String ^>();
	//String^ test = gcnew String(pDrive);
	//MessageBox::Show(test);
	iometerTargetCombo->Items->Clear();
	CDMTargetCombo->Items->Clear();
	while (pDrive[0] != _T('\0')) {
		int result = GetDriveType(pDrive);
		int forward = (int)_tcslen(pDrive);
		if (result == DRIVE_FIXED || result == DRIVE_REMOTE || result == DRIVE_REMOVABLE || result == DRIVE_RAMDISK) {
			if (index == 0)
				iometerTargetCombo->Items->Add(String::Format("{0}:", pDrive[0]));
			else if (index == 1)
				CDMTargetCombo->Items->Add(String::Format("{0}:", pDrive[0]));
		}
		pDrive += forward + 1;
	}
}

void AutoBenchUI::IometerInitialize(void) {
	iometerPanel = (gcnew System::Windows::Forms::Panel());
	iometerPanel->Size = System::Drawing::Size(110, 468);
	blockSizeGroup = (gcnew System::Windows::Forms::GroupBox());
	blockSizeLabel = (gcnew System::Windows::Forms::Label());
	blockSizeUnitLabel = (gcnew System::Windows::Forms::Label());
	blockSizeInput = (gcnew System::Windows::Forms::TextBox());
	iometerTargetGroup = (gcnew System::Windows::Forms::GroupBox());
	iometerTargetLabel = (gcnew System::Windows::Forms::Label());
	iometerTargetCombo = (gcnew System::Windows::Forms::ComboBox());
	iometerDataSizeGroup = (gcnew System::Windows::Forms::GroupBox());
	iometerDataSizeLabel = (gcnew System::Windows::Forms::Label());
	iometerDataSizeUnitLabel = (gcnew System::Windows::Forms::Label());
	iometerDataSizeInput = (gcnew System::Windows::Forms::TextBox());
	iometerQueueGroup = (gcnew System::Windows::Forms::GroupBox());
	iometerQueueLabel = (gcnew System::Windows::Forms::Label());
	iometerQueueInput = (gcnew System::Windows::Forms::TextBox());
	blockSizeLabel->Text = "Block size";
	blockSizeLabel->AutoSize = true;
	blockSizeUnitLabel->Text = "KiB";
	blockSizeUnitLabel->AutoSize = true;
	blockSizeUnitLabel->Location = System::Drawing::Point(75, 18);
	blockSizeInput->Text = "128";
	blockSizeInput->Location = System::Drawing::Point(5, 15);
	blockSizeInput->Width = 60;
	blockSizeGroup->Height = 40;
	blockSizeGroup->Width = 100;
	blockSizeGroup->Location = System::Drawing::Point(0, 150);
	//blockSizeGroup->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &AutoBenchUI::groupBox_Paint);
	blockSizeGroup->Controls->Add(blockSizeLabel);
	blockSizeGroup->Controls->Add(blockSizeUnitLabel);
	blockSizeGroup->Controls->Add(blockSizeInput);
	iometerTargetLabel->Text = "Target";
	iometerTargetLabel->AutoSize = true;
	iometerTargetCombo->Location = System::Drawing::Point(5, 15);
	iometerTargetCombo->Width = 90;
	iometerTargetCombo->Text = "C:";
	iometerTargetGroup->Controls->Add(iometerTargetLabel);
	iometerTargetGroup->Controls->Add(iometerTargetCombo);
	iometerTargetGroup->Width = 100;
	iometerTargetGroup->Height = 40;
	iometerDataSizeLabel->Text = "Data size";
	iometerDataSizeLabel->AutoSize = true;
	iometerDataSizeUnitLabel->Text = "MiB";
	iometerDataSizeUnitLabel->AutoSize = true;
	iometerDataSizeUnitLabel->Location = System::Drawing::Point(75, 18);
	iometerDataSizeInput->Text = "1024";
	iometerDataSizeInput->Location = System::Drawing::Point(5, 15);
	iometerDataSizeInput->Width = 60;
	iometerDataSizeGroup->Height = 40;
	iometerDataSizeGroup->Width = 100;
	iometerDataSizeGroup->Location = System::Drawing::Point(0, 50);
	iometerDataSizeGroup->Controls->Add(iometerDataSizeLabel);
	iometerDataSizeGroup->Controls->Add(iometerDataSizeUnitLabel);
	iometerDataSizeGroup->Controls->Add(iometerDataSizeInput);
	iometerQueueLabel->Text = "Queue depth";
	iometerQueueLabel->AutoSize = true;
	iometerQueueInput->Text = "32";
	iometerQueueInput->Location = System::Drawing::Point(5, 15);
	iometerQueueInput->Width = 60;
	iometerQueueGroup->Height = 40;
	iometerQueueGroup->Width = 100;
	iometerQueueGroup->Location = System::Drawing::Point(0, 100);
	iometerQueueGroup->Controls->Add(iometerQueueLabel);
	iometerQueueGroup->Controls->Add(iometerQueueInput);
	iometerPanel->Controls->Add(blockSizeGroup);
	iometerPanel->Controls->Add(iometerTargetGroup);
	iometerPanel->Controls->Add(iometerDataSizeGroup);
	iometerPanel->Controls->Add(iometerQueueGroup);
}

void AutoBenchUI::CDMInitialize(void) {
	CDMPanel = (gcnew System::Windows::Forms::Panel());
	CDMPanel->Size = System::Drawing::Size(110, 468);
	dataSizeGroup = (gcnew System::Windows::Forms::GroupBox());
	dataSizeLabel = (gcnew System::Windows::Forms::Label());
	dataSizeCombo = (gcnew System::Windows::Forms::ComboBox());
	CDMTargetGroup = (gcnew System::Windows::Forms::GroupBox());
	CDMTargetLabel = (gcnew System::Windows::Forms::Label());
	CDMTargetCombo = (gcnew System::Windows::Forms::ComboBox());
	CDMQueueGroup = (gcnew System::Windows::Forms::GroupBox());
	CDMQueueLabel = (gcnew System::Windows::Forms::Label());
	CDMQueueCombo = (gcnew System::Windows::Forms::ComboBox());
	dataSizeLabel->Text = "Data size";
	dataSizeLabel->AutoSize = true;
	//dataSizeCombo->Anchor = (System::Windows::Forms::AnchorStyles)(
	//	(System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) |
	//	System::Windows::Forms::AnchorStyles::Right);
	array<Object ^>^ sizeArray = { "50MiB", "100MiB", "500MiB", "1GiB", "2GiB", "4GiB", "8GiB", "16GiB", "32GiB" };
	dataSizeCombo->Items->AddRange(sizeArray);
	dataSizeCombo->Location = System::Drawing::Point(5, 15);
	dataSizeCombo->Width = 90;
	dataSizeCombo->Text = "1GiB";
	dataSizeGroup->Height = 40;
	dataSizeGroup->Width = 100;
	dataSizeGroup->Location = System::Drawing::Point(0, 50);
	dataSizeGroup->Controls->Add(dataSizeLabel);
	dataSizeGroup->Controls->Add(dataSizeCombo);
	CDMTargetLabel->Text = "Target";
	CDMTargetLabel->AutoSize = true;
	CDMTargetCombo->Location = System::Drawing::Point(5, 15);
	CDMTargetCombo->Width = 90;
	CDMTargetCombo->Text = "C:";
	CDMTargetGroup->Controls->Add(CDMTargetLabel);
	CDMTargetGroup->Controls->Add(CDMTargetCombo);
	CDMTargetGroup->Width = 100;
	CDMTargetGroup->Height = 40;
	CDMQueueLabel->Text = "Queue depth";
	CDMQueueLabel->AutoSize = true;
	array<Object ^>^ queueArray = { "1", "2", "4", "8", "16", "32", "64", "128", "256", "512" };
	CDMQueueCombo->Items->AddRange(queueArray);
	CDMQueueCombo->Location = System::Drawing::Point(5, 15);
	CDMQueueCombo->Width = 90;
	CDMQueueCombo->Text = "32";
	CDMQueueGroup->Height = 40;
	CDMQueueGroup->Width = 100;
	CDMQueueGroup->Location = System::Drawing::Point(0, 100);
	CDMQueueGroup->Controls->Add(CDMQueueLabel);
	CDMQueueGroup->Controls->Add(CDMQueueCombo);
	CDMPanel->Controls->Add(dataSizeGroup);
	CDMPanel->Controls->Add(CDMTargetGroup);
	CDMPanel->Controls->Add(CDMQueueGroup);
}

void AutoBenchUI::ASSSDInitialize(void) {

}

void AutoBenchUI::IometerConfigure(Process^ benchPro) {
	//AutomationElement^ mainWin = AutomationElement::RootElement->FindFirst(TreeScope::Children, (gcnew PropertyCondition(AutomationElement::ProcessIdProperty, benchPro->Id)));
	AutomationElement^ allManagersTree = AutomationElement::RootElement->FindFirst(TreeScope::Descendants, (gcnew PropertyCondition(AutomationElement::NameProperty, "All Managers")));
	/*if (!allManagersTree) {
		MessageBox::Show("all managers not found");
		return;
	}*/
	ExpandCollapsePattern^ allManagersTreePattern = (ExpandCollapsePattern ^)allManagersTree->GetCurrentPattern(ExpandCollapsePattern::Pattern);
	allManagersTreePattern->Expand();
	Sleep(500);
	AutomationElement^ firstManagerTree = allManagersTree->FindFirst(TreeScope::Children, (gcnew PropertyCondition(AutomationElement::ControlTypeProperty, ControlType::TreeItem)));
	ExpandCollapsePattern^ firstManagerTreePattern = (ExpandCollapsePattern ^)firstManagerTree->GetCurrentPattern(ExpandCollapsePattern::Pattern);
	firstManagerTreePattern->Expand();
	Sleep(500);
	AutomationElement^ worker1 = firstManagerTree->FindFirst(TreeScope::Children, (gcnew PropertyCondition(AutomationElement::NameProperty, "Worker 1")));
	SelectionItemPattern^ worker1SelectPattern = (SelectionItemPattern ^)worker1->GetCurrentPattern(SelectionItemPattern::Pattern);
	worker1SelectPattern->Select();
	AutomationElement^ targetsTree = AutomationElement::RootElement->FindFirst(TreeScope::Descendants, (gcnew PropertyCondition(AutomationElement::AutomationIdProperty, "1018")));
	AutomationElementCollection^ drives = targetsTree->FindAll(TreeScope::Children, (gcnew PropertyCondition(AutomationElement::ControlTypeProperty, ControlType::TreeItem)));
	IEnumerator^ eachDrive = drives->GetEnumerator();
	while (eachDrive->MoveNext()) {
		AutomationElement^ drive = (AutomationElement^ )eachDrive->Current;
		if (drive->Current.Name->Contains(iometerTargetCombo->Text)) {
			//SelectionItemPattern^ driveSelectPattern = (SelectionItemPattern ^)drive->GetCurrentPattern(SelectionItemPattern::Pattern);
			//Sleep(500);
			//driveSelectPattern->Select();
			System::Windows::Point p = drive->GetClickablePoint();
			System::Drawing::Point pp = System::Drawing::Point(Convert::ToInt32(p.X), Convert::ToInt32(p.Y));
			Mouse::MoveTo(pp);
			Mouse::Click(MouseButton::Left);
			break;
		}
	}
	AutomationElement^ maxDiskSize = AutomationElement::RootElement->FindFirst(TreeScope::Descendants, (gcnew PropertyCondition(AutomationElement::AutomationIdProperty, "3001")));
	ValuePattern^ maxDiskSizeValuePattern = (ValuePattern^)maxDiskSize->GetCurrentPattern(ValuePattern::Pattern);
	maxDiskSizeValuePattern->SetValue(String::Format("{0}", (Int32::Parse(iometerDataSizeInput->Text) * 1024 / 4)));
	AutomationElement^ outstandingIO = AutomationElement::RootElement->FindFirst(TreeScope::Descendants, (gcnew PropertyCondition(AutomationElement::AutomationIdProperty, "3012")));
	ValuePattern^ outstandingIOValuePattern = (ValuePattern^)outstandingIO->GetCurrentPattern(ValuePattern::Pattern);
	outstandingIOValuePattern->SetValue(String::Format("{0}", iometerQueueInput->Text));
	AutomationElement^ accessSpecTab = AutomationElement::RootElement->FindFirst(TreeScope::Descendants, (gcnew PropertyCondition(AutomationElement::NameProperty, "Access Specifications")));
	SelectionItemPattern^ accessSpecTabSelectPattern = (SelectionItemPattern ^)accessSpecTab->GetCurrentPattern(SelectionItemPattern::Pattern);
	accessSpecTabSelectPattern->Select();
	AutomationElement^ newButton = AutomationElement::RootElement->FindFirst(TreeScope::Descendants, (gcnew PropertyCondition(AutomationElement::AutomationIdProperty, "1025")));
	InvokePattern^ newButtonInvokePattern = (InvokePattern^)newButton->GetCurrentPattern(InvokePattern::Pattern);
	array<System::String^>^ blockSizes = blockSizeInput->Text->Split(String::Format(",")->ToCharArray());
	IEnumerator^ eachBlockSize = blockSizes->GetEnumerator();
	while (eachBlockSize->MoveNext()) {
		newButtonInvokePattern->Invoke();
		Sleep(500);
		for (int i = 0; i < 4; i++) {
			AutomationElement^ editAccessWindow = AutomationElement::RootElement->FindFirst(TreeScope::Descendants, (gcnew PropertyCondition(AutomationElement::NameProperty, "Edit Access Specification")));
			/*if (!editAccessWindow) {
			MessageBox::Show("edit window not found");
			return;
			}*/
			AutomationElement^ transRequestSize = editAccessWindow->FindFirst(TreeScope::Children, (gcnew PropertyCondition(AutomationElement::AutomationIdProperty, "1031")));
			RangeValuePattern^ transRequestSizeRangePattern = (RangeValuePattern^)transRequestSize->GetCurrentPattern(RangeValuePattern::Pattern);
			transRequestSizeRangePattern->SetValue(Int32::Parse((String ^)eachBlockSize->Current));
			AutomationElement^ perSeqRanSlider = editAccessWindow->FindFirst(TreeScope::Children, (gcnew PropertyCondition(AutomationElement::AutomationIdProperty, "5001")));
			RangeValuePattern^ perSeqRanSliderRangePattern = (RangeValuePattern^)perSeqRanSlider->GetCurrentPattern(RangeValuePattern::Pattern);
			AutomationElement^ perReadWriteSlider = editAccessWindow->FindFirst(TreeScope::Children, (gcnew PropertyCondition(AutomationElement::AutomationIdProperty, "5000")));
			RangeValuePattern^ perReadWriteSliderRangePattern = (RangeValuePattern^)perReadWriteSlider->GetCurrentPattern(RangeValuePattern::Pattern);
			switch (i) {
			case 0: //Seq Write
				perSeqRanSliderRangePattern->SetValue(0);
				perReadWriteSliderRangePattern->SetValue(0);
				break;
			case 1: //Seq Read
				perSeqRanSliderRangePattern->SetValue(0);
				perReadWriteSliderRangePattern->SetValue(100);
				break;
			case 2: //Ran Write
				perSeqRanSliderRangePattern->SetValue(100);
				perReadWriteSliderRangePattern->SetValue(0);
				break;
			case 3: //Ran Read
				perSeqRanSliderRangePattern->SetValue(100);
				perReadWriteSliderRangePattern->SetValue(100);
				break;
			default: //Seq Write
				perSeqRanSliderRangePattern->SetValue(0);
				perReadWriteSliderRangePattern->SetValue(0);
			}
			//AutomationElement^ okButton = editAccessWindow->FindFirst(TreeScope::Children, (gcnew PropertyCondition(AutomationElement::AutomationIdProperty, "1")));
			AutomationElement^ okButton = editAccessWindow->FindFirst(TreeScope::Children, (gcnew PropertyCondition(AutomationElement::NameProperty, "OK")));
			InvokePattern^ okButtonInvokePattern = (InvokePattern^)okButton->GetCurrentPattern(InvokePattern::Pattern);
			okButtonInvokePattern->Invoke();
		}
	}
}