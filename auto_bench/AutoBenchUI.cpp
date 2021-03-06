#include "AutoBenchUI.h"

using namespace auto_bench;

System::Void AutoBenchUI::checkedListBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	if (checkedListBox1->SelectedIndex == 0) {
		splitContainer3->Panel1->Controls->Clear();
		splitContainer3->Panel2->Controls->Clear();
		ListDrives(0);
		splitContainer3->Panel1->Controls->Add(iometerPanel);
		splitContainer3->Panel2->Controls->Add(iometerResultsDataView);
	}
	else if (checkedListBox1->SelectedIndex == 1) {
		splitContainer3->Panel1->Controls->Clear();
		splitContainer3->Panel2->Controls->Clear();
		ListDrives(1);
		splitContainer3->Panel1->Controls->Add(CDMPanel);
		splitContainer3->Panel2->Controls->Add(CDMResultsDataView);
	}
}

System::Void AutoBenchUI::button1_Click(System::Object^  sender, System::EventArgs^  e) {
	IEnumerator^ benchEnum = checkedListBox1->CheckedIndices->GetEnumerator();
	safe_cast<Button^>(sender)->Enabled = false;
	while (benchEnum->MoveNext()) {
		Int32 indexChecked = *safe_cast<Int32^>(benchEnum->Current);
		if (indexChecked == 0) {
			checkedListBox1->SetSelected(0, true);
			iometerProcess = gcnew Process;
			ProcessStartInfo^ iometerProcessStartInfo = gcnew ProcessStartInfo;
			iometerProcessStartInfo->FileName = "iometer\\IOmeter.exe";
			iometerProcessStartInfo->Verb = "runas";
			iometerProcess->StartInfo = iometerProcessStartInfo;
			iometerProcess->Start();
			iometerProcess->WaitForInputIdle();
			IometerResultsConfigure();
			IometerConfigure();
			iometerProcess->WaitForExit();
		}
		else if (indexChecked == 1) {
			checkedListBox1->SetSelected(1, true);
			cdmProcess = gcnew Process;
			ProcessStartInfo^ cdmProcessStartInfo = gcnew ProcessStartInfo;
			cdmProcessStartInfo->FileName = "CDM\\DiskMark32.exe";
			cdmProcessStartInfo->Verb = "runas";
			cdmProcess->StartInfo = cdmProcessStartInfo;
			cdmProcess->Start();
			cdmProcess->WaitForInputIdle();
			CDMResultsConfigure();
			CDMConfigure();
			cdmProcess->WaitForExit();
		}
	}
	safe_cast<Button^>(sender)->Enabled = true;
}

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
		//if (result == DRIVE_FIXED || result == DRIVE_REMOTE || result == DRIVE_REMOVABLE || result == DRIVE_RAMDISK) {
		if (result == DRIVE_FIXED) {
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
	iometerRampUpTimeGroup = (gcnew System::Windows::Forms::GroupBox());
	iometerRampUpTimeLabel = (gcnew System::Windows::Forms::Label());
	iometerRampUpTimeUnitLabel = (gcnew System::Windows::Forms::Label());
	iometerRampUpTimeInput = (gcnew System::Windows::Forms::TextBox());
	iometerRunTimeGroup = (gcnew System::Windows::Forms::GroupBox());
	iometerRunTimeLabel = (gcnew System::Windows::Forms::Label());
	iometerRunTimeUnitLabel = (gcnew System::Windows::Forms::Label());
	iometerRunTimeInput = (gcnew System::Windows::Forms::TextBox());
	blockSizeLabel->Text = "Block size";
	blockSizeLabel->AutoSize = true;
	blockSizeUnitLabel->Text = "KiB";
	blockSizeUnitLabel->AutoSize = true;
	blockSizeUnitLabel->Location = System::Drawing::Point(75, 18);
	blockSizeInput->Text = "128";
	blockSizeInput->Location = System::Drawing::Point(5, 15);
	blockSizeInput->Width = 60;
	blockSizeGroup->Height = 40;
	blockSizeGroup->Width = 110;
	blockSizeGroup->Location = System::Drawing::Point(0, 150);
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
	iometerTargetGroup->Width = 110;
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
	iometerDataSizeGroup->Width = 110;
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
	iometerQueueGroup->Width = 110;
	iometerQueueGroup->Location = System::Drawing::Point(0, 100);
	iometerQueueGroup->Controls->Add(iometerQueueLabel);
	iometerQueueGroup->Controls->Add(iometerQueueInput);
	iometerRampUpTimeLabel->Text = "準備時間";
	iometerRampUpTimeLabel->AutoSize = true;
	iometerRampUpTimeUnitLabel->Text = "Secs";
	iometerRampUpTimeUnitLabel->AutoSize = true;
	iometerRampUpTimeUnitLabel->Location = System::Drawing::Point(75, 18);
	iometerRampUpTimeInput->Text = "10";
	iometerRampUpTimeInput->Location = System::Drawing::Point(5, 15);
	iometerRampUpTimeInput->Width = 60;
	iometerRampUpTimeGroup->Height = 40;
	iometerRampUpTimeGroup->Width = 110;
	iometerRampUpTimeGroup->Location = System::Drawing::Point(0,200);
	iometerRampUpTimeGroup->Controls->Add(iometerRampUpTimeLabel);
	iometerRampUpTimeGroup->Controls->Add(iometerRampUpTimeUnitLabel);
	iometerRampUpTimeGroup->Controls->Add(iometerRampUpTimeInput);
	iometerRunTimeLabel->Text = "実行時間";
	iometerRunTimeLabel->AutoSize = true;
	iometerRunTimeUnitLabel->Text = "Secs";
	iometerRunTimeUnitLabel->AutoSize = true;
	iometerRunTimeUnitLabel->Location = System::Drawing::Point(75, 18);
	iometerRunTimeInput->Text = "20";
	iometerRunTimeInput->Location = System::Drawing::Point(5, 15);
	iometerRunTimeInput->Width = 60;
	iometerRunTimeGroup->Height = 40;
	iometerRunTimeGroup->Width = 110;
	iometerRunTimeGroup->Location = System::Drawing::Point(0, 250);
	iometerRunTimeGroup->Controls->Add(iometerRunTimeLabel);
	iometerRunTimeGroup->Controls->Add(iometerRunTimeUnitLabel);
	iometerRunTimeGroup->Controls->Add(iometerRunTimeInput);
	iometerPanel->Controls->Add(blockSizeGroup);
	iometerPanel->Controls->Add(iometerTargetGroup);
	iometerPanel->Controls->Add(iometerDataSizeGroup);
	iometerPanel->Controls->Add(iometerQueueGroup);
	iometerPanel->Controls->Add(iometerRampUpTimeGroup);
	iometerPanel->Controls->Add(iometerRunTimeGroup);
	iometerResultsDataView = (gcnew System::Windows::Forms::DataGridView());
	iometerResultsDataView->ColumnCount = 9;
	iometerResultsDataView->RowCount = 2;
	iometerResultsDataView->Width = 903;
	iometerResultsDataView->Height = 450;
	iometerResultsDataView->ReadOnly = true;
	iometerResultsDataView->RowHeadersVisible = false;
	iometerResultsDataView->ColumnHeadersVisible = false;
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
	CDMTestCountGroup = (gcnew System::Windows::Forms::GroupBox());
	CDMTestCountLabel = (gcnew System::Windows::Forms::Label());
	CDMTestCountCombo = (gcnew System::Windows::Forms::ComboBox());
	dataSizeLabel->Text = "Data size";
	dataSizeLabel->AutoSize = true;
	array<Object ^>^ sizeArray = { "50MiB", "100MiB", "500MiB", "1GiB", "2GiB", "4GiB", "8GiB", "16GiB", "32GiB" };
	dataSizeCombo->Items->AddRange(sizeArray);
	dataSizeCombo->Location = System::Drawing::Point(5, 15);
	dataSizeCombo->Width = 90;
	dataSizeCombo->Text = "1GiB";
	dataSizeGroup->Height = 40;
	dataSizeGroup->Width = 110;
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
	CDMTargetGroup->Width = 110;
	CDMTargetGroup->Height = 40;
	CDMQueueLabel->Text = "Queue depth";
	CDMQueueLabel->AutoSize = true;
	array<Object ^>^ queueArray = { "1", "2", "4", "8", "16", "32", "64", "128", "256", "512" };
	CDMQueueCombo->Items->AddRange(queueArray);
	CDMQueueCombo->Location = System::Drawing::Point(5, 15);
	CDMQueueCombo->Width = 90;
	CDMQueueCombo->Text = "32";
	CDMQueueGroup->Height = 40;
	CDMQueueGroup->Width = 110;
	CDMQueueGroup->Location = System::Drawing::Point(0, 100);
	CDMQueueGroup->Controls->Add(CDMQueueLabel);
	CDMQueueGroup->Controls->Add(CDMQueueCombo);
	CDMTestCountLabel->Text = "Test count";
	CDMTestCountLabel->AutoSize = true;
	array<Object ^>^ testCountArray = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
	CDMTestCountCombo->Items->AddRange(testCountArray);
	CDMTestCountCombo->Location = System::Drawing::Point(5, 15);
	CDMTestCountCombo->Width = 90;
	CDMTestCountCombo->Text = "5";
	CDMTestCountGroup->Height = 40;
	CDMTestCountGroup->Width = 110;
	CDMTestCountGroup->Location = System::Drawing::Point(0, 150);
	CDMTestCountGroup->Controls->Add(CDMTestCountLabel);
	CDMTestCountGroup->Controls->Add(CDMTestCountCombo);
	CDMPanel->Controls->Add(dataSizeGroup);
	CDMPanel->Controls->Add(CDMTargetGroup);
	CDMPanel->Controls->Add(CDMQueueGroup);
	CDMPanel->Controls->Add(CDMTestCountGroup);
	CDMResultsDataView = (gcnew System::Windows::Forms::DataGridView());
	CDMResultsDataView->ColumnCount = 8;
	CDMResultsDataView->RowCount = 2;
	CDMResultsDataView->Width = 803;
	CDMResultsDataView->Height = 450;
	CDMResultsDataView->ReadOnly = true;
	CDMResultsDataView->RowHeadersVisible = false;
	CDMResultsDataView->ColumnHeadersVisible = false;
}

void AutoBenchUI::CDMResultsConfigure(void) {
	int rowCount = CDMResultsDataView->RowCount;
	CDMResultsDataView->Rows[rowCount - 2]->Cells[1]->Value = "Target:";
	CDMResultsDataView->Rows[rowCount - 2]->Cells[2]->Value = CDMTargetCombo->Text;
	CDMResultsDataView->Rows[rowCount - 2]->Cells[3]->Value = "Data size:";
	CDMResultsDataView->Rows[rowCount - 2]->Cells[4]->Value = dataSizeCombo->Text;
	CDMResultsDataView->Rows[rowCount - 2]->Cells[5]->Value = "Thread:";
	CDMResultsDataView->Rows[rowCount - 2]->Cells[6]->Value = "1";
	CDMResultsDataView->Rows[rowCount - 2]->Cells[7]->Value = "単位：MB/s";
	CDMResultsDataView->Rows->Insert(rowCount - 1, 1);
	CDMResultsDataView->Rows[rowCount - 1]->Cells[0]->Value = "Seq. Read(BS=128KiB,Q=" + CDMQueueCombo->Text + ")";
	CDMResultsDataView->Rows[rowCount - 1]->Cells[1]->Value = "Seq. Write(BS=128KiB,Q=" + CDMQueueCombo->Text + ")";
	CDMResultsDataView->Rows[rowCount - 1]->Cells[2]->Value = "Ran. Read(BS=4KiB,Q=" + CDMQueueCombo->Text + ")";
	CDMResultsDataView->Rows[rowCount - 1]->Cells[3]->Value = "Ran. Write(BS=4KiB,Q=" + CDMQueueCombo->Text + ")";
	CDMResultsDataView->Rows[rowCount - 1]->Cells[4]->Value = "Seq. Read(BS=1MiB,Q=1)";
	CDMResultsDataView->Rows[rowCount - 1]->Cells[5]->Value = "Seq. Write(BS=1MiB,Q=1)";
	CDMResultsDataView->Rows[rowCount - 1]->Cells[6]->Value = "Ran. Read(BS=1MiB,Q=1)";
	CDMResultsDataView->Rows[rowCount - 1]->Cells[7]->Value = "Ran. Write(BS=1MiB,Q=1)";
	CDMResultsDataView->Rows->Insert(rowCount, 1);
}

void AutoBenchUI::CDMConfigure(void) {
	Sleep(500);
	AutomationElement^ languageSelect = AutomationElement::RootElement->FindFirst(TreeScope::Descendants, gcnew AndCondition(gcnew PropertyCondition(AutomationElement::AutomationIdProperty, "Item 5"),
		gcnew PropertyCondition(AutomationElement::ControlTypeProperty, ControlType::MenuItem)));
	ExpandCollapsePattern^ languageSelectECPattern = (ExpandCollapsePattern^)languageSelect->GetCurrentPattern(ExpandCollapsePattern::Pattern);
	languageSelectECPattern->Expand();
	AutomationElement^ languageSubSelect = languageSelect->FindFirst(TreeScope::Descendants, (gcnew PropertyCondition(AutomationElement::AutomationIdProperty, "Item 1")));
	ExpandCollapsePattern^ languageSubSelectECPattern = (ExpandCollapsePattern^)languageSubSelect->GetCurrentPattern(ExpandCollapsePattern::Pattern);
	languageSubSelectECPattern->Expand();
	AutomationElement^ englishSelect = languageSubSelect->FindFirst(TreeScope::Descendants, (gcnew PropertyCondition(AutomationElement::AutomationIdProperty, "Item 38921")));
	InvokePattern^ englishSelectInvokePattern = (InvokePattern^)englishSelect->GetCurrentPattern(InvokePattern::Pattern);
	englishSelectInvokePattern->Invoke();
	AutomationElement^ queueSetting = AutomationElement::RootElement->FindFirst(TreeScope::Descendants, gcnew AndCondition(gcnew PropertyCondition(AutomationElement::AutomationIdProperty, "Item 2"),
		gcnew PropertyCondition(AutomationElement::ControlTypeProperty, ControlType::MenuItem)));
	ExpandCollapsePattern^ queueSettingECPattern = (ExpandCollapsePattern^)queueSetting->GetCurrentPattern(ExpandCollapsePattern::Pattern);
	queueSettingECPattern->Expand();
	AutomationElement^ queueSettingMenu = queueSetting->FindFirst(TreeScope::Descendants, (gcnew PropertyCondition(AutomationElement::AutomationIdProperty, "Item 32818")));
	InvokePattern^ queueSettingMenuInvokePattern = (InvokePattern^)queueSettingMenu->GetCurrentPattern(InvokePattern::Pattern);
	queueSettingMenuInvokePattern->Invoke();
	Sleep(500);
	AutomationElement^ queueSettingWindow = AutomationElement::RootElement->FindFirst(TreeScope::Descendants, gcnew AndCondition(gcnew PropertyCondition(AutomationElement::NameProperty, "Queues & Threads"),
		gcnew PropertyCondition(AutomationElement::ControlTypeProperty, ControlType::Pane), gcnew PropertyCondition(AutomationElement::ProcessIdProperty, cdmProcess->Id)));
	AutomationElementCollection^ queueThreadSettings = queueSettingWindow->FindAll(TreeScope::Descendants, gcnew PropertyCondition(AutomationElement::ControlTypeProperty, ControlType::Button));
	AutomationElementCollection^ queueThreadSettingsCombo = queueSettingWindow->FindAll(TreeScope::Descendants, gcnew PropertyCondition(AutomationElement::ControlTypeProperty, ControlType::ComboBox));
	safe_cast<InvokePattern^>(queueThreadSettings[0]->GetCurrentPattern(InvokePattern::Pattern))->Invoke();
	while (!safe_cast<ValuePattern^>(queueThreadSettingsCombo[0]->GetCurrentPattern(ValuePattern::Pattern))->Current.Value->Equals(CDMQueueCombo->Text)) {
		Keyboard::Type(String::Format("{0}", CDMQueueCombo->Text[0]));
		Sleep(500);
	}
	Mouse::MoveTo(System::Drawing::Point(Convert::ToInt32(queueSettingWindow->GetClickablePoint().X), Convert::ToInt32(queueSettingWindow->GetClickablePoint().Y)));
	Mouse::Click(MouseButton::Left);
	safe_cast<InvokePattern^>(queueThreadSettings[0]->GetCurrentPattern(InvokePattern::Pattern))->Invoke();
	safe_cast<InvokePattern^>(queueThreadSettings[1]->GetCurrentPattern(InvokePattern::Pattern))->Invoke();
	while (!safe_cast<ValuePattern^>(queueThreadSettingsCombo[1]->GetCurrentPattern(ValuePattern::Pattern))->Current.Value->Equals("1")) {
		Keyboard::Type("1");
		Sleep(500);
	}
	Mouse::MoveTo(System::Drawing::Point(Convert::ToInt32(queueSettingWindow->GetClickablePoint().X), Convert::ToInt32(queueSettingWindow->GetClickablePoint().Y)));
	Mouse::Click(MouseButton::Left);
	safe_cast<InvokePattern^>(queueThreadSettings[1]->GetCurrentPattern(InvokePattern::Pattern))->Invoke();
	safe_cast<InvokePattern^>(queueThreadSettings[2]->GetCurrentPattern(InvokePattern::Pattern))->Invoke();
	while (!safe_cast<ValuePattern^>(queueThreadSettingsCombo[2]->GetCurrentPattern(ValuePattern::Pattern))->Current.Value->Equals(CDMQueueCombo->Text)) {
		Keyboard::Type(String::Format("{0}", CDMQueueCombo->Text[0]));
		Sleep(500);
	}
	Mouse::MoveTo(System::Drawing::Point(Convert::ToInt32(queueSettingWindow->GetClickablePoint().X), Convert::ToInt32(queueSettingWindow->GetClickablePoint().Y)));
	Mouse::Click(MouseButton::Left);
	safe_cast<InvokePattern^>(queueThreadSettings[2]->GetCurrentPattern(InvokePattern::Pattern))->Invoke();
	safe_cast<InvokePattern^>(queueThreadSettings[3]->GetCurrentPattern(InvokePattern::Pattern))->Invoke();
	while (!safe_cast<ValuePattern^>(queueThreadSettingsCombo[3]->GetCurrentPattern(ValuePattern::Pattern))->Current.Value->Equals("1")) {
		Keyboard::Type("1");
		Sleep(500);
	}
	Mouse::MoveTo(System::Drawing::Point(Convert::ToInt32(queueSettingWindow->GetClickablePoint().X), Convert::ToInt32(queueSettingWindow->GetClickablePoint().Y)));
	Mouse::Click(MouseButton::Left);
	safe_cast<InvokePattern^>(queueThreadSettings[3]->GetCurrentPattern(InvokePattern::Pattern))->Invoke();
	AutomationElement^ queueSettingWindowTitle = AutomationElement::RootElement->FindFirst(TreeScope::Descendants, gcnew AndCondition(gcnew PropertyCondition(AutomationElement::NameProperty, "Queues & Threads"),
		gcnew PropertyCondition(AutomationElement::ControlTypeProperty, ControlType::TitleBar), gcnew PropertyCondition(AutomationElement::ProcessIdProperty, cdmProcess->Id)));
	AutomationElement^ queueSettingWindowClose = queueSettingWindowTitle->FindFirst(TreeScope::Descendants, gcnew PropertyCondition(AutomationElement::AutomationIdProperty, "Close"));
	InvokePattern^ queueSettingWindowCloseInvokePattern = (InvokePattern^)queueSettingWindowClose->GetCurrentPattern(InvokePattern::Pattern);
	queueSettingWindowCloseInvokePattern->Invoke();
	Sleep(500);
	AutomationElement^ titleBar = AutomationElement::RootElement->FindFirst(TreeScope::Descendants, gcnew AndCondition(gcnew PropertyCondition(AutomationElement::AutomationIdProperty, "TitleBar"),
		gcnew PropertyCondition(AutomationElement::ControlTypeProperty, ControlType::TitleBar), gcnew PropertyCondition(AutomationElement::ProcessIdProperty, cdmProcess->Id)));
	AutomationElement^ testCount = AutomationElement::RootElement->FindFirst(TreeScope::Descendants, gcnew AndCondition(gcnew PropertyCondition(AutomationElement::NameProperty, "Test Count"),
		gcnew PropertyCondition(AutomationElement::ControlTypeProperty, ControlType::ComboBox)));
	AutomationElement^ testCountButton = testCount->FindFirst(TreeScope::Descendants, (gcnew PropertyCondition(AutomationElement::ControlTypeProperty, ControlType::Button)));
	InvokePattern^ testCountButtonInvokePattern = (InvokePattern^)testCountButton->GetCurrentPattern(InvokePattern::Pattern);
	testCountButtonInvokePattern->Invoke();
	while (!safe_cast<ValuePattern^>(testCount->GetCurrentPattern(ValuePattern::Pattern))->Current.Value->Equals(CDMTestCountCombo->Text)) {
		Keyboard::Type(String::Format("{0}", CDMTestCountCombo->Text[0]));
		Sleep(500);
	}
	//Mouse::MoveTo(System::Drawing::Point(Convert::ToInt32(testCountButton->GetClickablePoint().X), Convert::ToInt32(testCountButton->GetClickablePoint().Y)));
	Mouse::MoveTo(System::Drawing::Point(Convert::ToInt32(titleBar->GetClickablePoint().X), Convert::ToInt32(titleBar->GetClickablePoint().Y)));
	Mouse::Click(MouseButton::Left);
	testCountButtonInvokePattern->Invoke();
	AutomationElement^ testSize = AutomationElement::RootElement->FindFirst(TreeScope::Descendants, gcnew AndCondition(gcnew PropertyCondition(AutomationElement::NameProperty, "Test Size"),
		gcnew PropertyCondition(AutomationElement::ControlTypeProperty, ControlType::ComboBox)));
	AutomationElement^ testSizeButton = testSize->FindFirst(TreeScope::Descendants, (gcnew PropertyCondition(AutomationElement::ControlTypeProperty, ControlType::Button)));
	InvokePattern^ testSizeButtonInvokePattern = (InvokePattern^)testSizeButton->GetCurrentPattern(InvokePattern::Pattern);
	testSizeButtonInvokePattern->Invoke();
	while (!safe_cast<ValuePattern^>(testSize->GetCurrentPattern(ValuePattern::Pattern))->Current.Value->Equals(dataSizeCombo->Text)) {
		Keyboard::Type(String::Format("{0}", dataSizeCombo->Text[0]));
		Sleep(500);
	}
	//Mouse::MoveTo(System::Drawing::Point(Convert::ToInt32(testSizeButton->GetClickablePoint().X), Convert::ToInt32(testSizeButton->GetClickablePoint().Y)));
	Mouse::MoveTo(System::Drawing::Point(Convert::ToInt32(titleBar->GetClickablePoint().X), Convert::ToInt32(titleBar->GetClickablePoint().Y)));
	Mouse::Click(MouseButton::Left);
	testSizeButtonInvokePattern->Invoke();
	AutomationElement^ testDrive = AutomationElement::RootElement->FindFirst(TreeScope::Descendants, gcnew AndCondition(gcnew PropertyCondition(AutomationElement::NameProperty, "Test Drive"),
		gcnew PropertyCondition(AutomationElement::ControlTypeProperty, ControlType::ComboBox)));
	AutomationElement^ testDriveButton = testDrive->FindFirst(TreeScope::Descendants, (gcnew PropertyCondition(AutomationElement::ControlTypeProperty, ControlType::Button)));
	InvokePattern^ testDriveButtonInvokePattern = (InvokePattern^)testDriveButton->GetCurrentPattern(InvokePattern::Pattern);
	testDriveButtonInvokePattern->Invoke();
	while (!safe_cast<ValuePattern^>(testDrive->GetCurrentPattern(ValuePattern::Pattern))->Current.Value->Contains(CDMTargetCombo->Text)) {
		Keyboard::Type(String::Format("{0}", CDMTargetCombo->Text[0]));
		Sleep(500);
	}
	//Mouse::MoveTo(System::Drawing::Point(Convert::ToInt32(testDriveButton->GetClickablePoint().X), Convert::ToInt32(testDriveButton->GetClickablePoint().Y)));
	Mouse::MoveTo(System::Drawing::Point(Convert::ToInt32(titleBar->GetClickablePoint().X), Convert::ToInt32(titleBar->GetClickablePoint().Y)));
	Mouse::Click(MouseButton::Left);
	testDriveButtonInvokePattern->Invoke();
	Sleep(500);
	AutomationElement^ mainMenu = AutomationElement::RootElement->FindFirst(TreeScope::Descendants, gcnew AndCondition(gcnew PropertyCondition(AutomationElement::NameProperty, "CrystalDiskMark"),
		gcnew PropertyCondition(AutomationElement::ControlTypeProperty, ControlType::Pane)));
	AutomationElement^ startButton = mainMenu->FindFirst(TreeScope::Descendants, gcnew AndCondition(gcnew PropertyCondition(AutomationElement::NameProperty, "All"),
		gcnew PropertyCondition(AutomationElement::ControlTypeProperty, ControlType::Hyperlink)));
	InvokePattern^ startButtonInvokePattern = (InvokePattern^)startButton->GetCurrentPattern(InvokePattern::Pattern);
	StopThread();
	resultsUpdateThread = gcnew Thread(gcnew ThreadStart(this, &AutoBenchUI::CDMUpdateThreadProc));
	resultsUpdateThread->IsBackground = TRUE;
	resultsUpdateThread->Start();
	startButtonInvokePattern->Invoke();
}

void AutoBenchUI::IometerResultsConfigure(void) {
	int rowCount = iometerResultsDataView->RowCount;
	iometerResultsDataView->Rows[rowCount - 2]->Cells[1]->Value = "Target:";
	iometerResultsDataView->Rows[rowCount - 2]->Cells[2]->Value = iometerTargetCombo->Text;
	iometerResultsDataView->Rows[rowCount - 2]->Cells[3]->Value = "Data size:";
	iometerResultsDataView->Rows[rowCount - 2]->Cells[4]->Value = iometerDataSizeInput->Text + " MiB";
	iometerResultsDataView->Rows[rowCount - 2]->Cells[5]->Value = "Queue depth:";
	iometerResultsDataView->Rows[rowCount - 2]->Cells[6]->Value = iometerQueueInput->Text;
	iometerResultsDataView->Rows->Insert(rowCount - 1, 1);
	iometerResultsDataView->Rows[rowCount - 1]->Cells[0]->Value = "Block size (KiB)";
	iometerResultsDataView->Rows[rowCount - 1]->Cells[1]->Value = "Seq. Write";
	iometerResultsDataView->Rows[rowCount - 1]->Cells[2]->Value = "Seq. Write (IOPS)";
	iometerResultsDataView->Rows[rowCount - 1]->Cells[3]->Value = "Seq. Read";
	iometerResultsDataView->Rows[rowCount - 1]->Cells[4]->Value = "Seq. Read (IOPS)";
	iometerResultsDataView->Rows[rowCount - 1]->Cells[5]->Value = "Ran. Write";
	iometerResultsDataView->Rows[rowCount - 1]->Cells[6]->Value = "Ran. Write (IOPS)";
	iometerResultsDataView->Rows[rowCount - 1]->Cells[7]->Value = "Ran. Read";
	iometerResultsDataView->Rows[rowCount - 1]->Cells[8]->Value = "Ran. Read (IOPS)";
	iometerResultsDataView->Rows->Insert(rowCount, 1);
}

void AutoBenchUI::IometerConfigure(void) {
	AutomationElement^ allManagersTree = AutomationElement::RootElement->FindFirst(TreeScope::Descendants, (gcnew PropertyCondition(AutomationElement::NameProperty, "All Managers")));
	ExpandCollapsePattern^ allManagersTreePattern = (ExpandCollapsePattern ^)allManagersTree->GetCurrentPattern(ExpandCollapsePattern::Pattern);
	allManagersTreePattern->Expand();
	Sleep(1000);
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
	AutomationElement^ addButton = AutomationElement::RootElement->FindFirst(TreeScope::Descendants, (gcnew PropertyCondition(AutomationElement::AutomationIdProperty, "1024")));
	InvokePattern^ addButtonInvokePattern = (InvokePattern^)addButton->GetCurrentPattern(InvokePattern::Pattern);
	array<System::String^>^ blockSizes = blockSizeInput->Text->Split(String::Format(",")->ToCharArray());
	eachBlockSize = blockSizes->GetEnumerator();
	while (eachBlockSize->MoveNext()) {
		for (int i = 0; i < 4; i++) {
			newButtonInvokePattern->Invoke();
			Sleep(500);
			AutomationElement^ editAccessWindow = AutomationElement::RootElement->FindFirst(TreeScope::Descendants, (gcnew PropertyCondition(AutomationElement::NameProperty, "Edit Access Specification")));
			AutomationElement^ transRequestSizeMB = editAccessWindow->FindFirst(TreeScope::Children, (gcnew PropertyCondition(AutomationElement::AutomationIdProperty, "1032")));
			RangeValuePattern^ transRequestSizeMBRangePattern = (RangeValuePattern^)transRequestSizeMB->GetCurrentPattern(RangeValuePattern::Pattern);
			AutomationElement^ transRequestSize = editAccessWindow->FindFirst(TreeScope::Children, (gcnew PropertyCondition(AutomationElement::AutomationIdProperty, "1031")));
			RangeValuePattern^ transRequestSizeRangePattern = (RangeValuePattern^)transRequestSize->GetCurrentPattern(RangeValuePattern::Pattern);
			double quotient = (int)Double::Parse((String ^)eachBlockSize->Current) / 1024;
			double remainder = (int)Double::Parse((String ^)eachBlockSize->Current) % 1024;
			transRequestSizeMBRangePattern->SetValue(quotient);
			transRequestSizeRangePattern->SetValue(remainder);
			Mouse::MoveTo(System::Drawing::Point(Convert::ToInt32(transRequestSize->GetClickablePoint().X), Convert::ToInt32(transRequestSize->GetClickablePoint().Y)));
			Mouse::Click(MouseButton::Left);

			AutomationElement^ perSeqRanSlider = editAccessWindow->FindFirst(TreeScope::Children, (gcnew PropertyCondition(AutomationElement::AutomationIdProperty, "5001")));
			AutomationElement^ perSeqRanSliderThumb = perSeqRanSlider->FindFirst(TreeScope::Children, (gcnew PropertyCondition(AutomationElement::ControlTypeProperty, ControlType::Thumb)));

			AutomationElement^ perReadWriteSlider = editAccessWindow->FindFirst(TreeScope::Children, (gcnew PropertyCondition(AutomationElement::AutomationIdProperty, "5000")));
			AutomationElement^ perReadWriteSliderThumb = perReadWriteSlider->FindFirst(TreeScope::Children, (gcnew PropertyCondition(AutomationElement::ControlTypeProperty, ControlType::Thumb)));

			switch (i) {
			case 0: //Seq Write
				Mouse::MoveTo(System::Drawing::Point(Convert::ToInt32(perSeqRanSliderThumb->GetClickablePoint().X), Convert::ToInt32(perSeqRanSliderThumb->GetClickablePoint().Y)));
				Mouse::DragTo(MouseButton::Left, System::Drawing::Point(Convert::ToInt32(perSeqRanSlider->Current.BoundingRectangle.Left + 12), Convert::ToInt32(perSeqRanSlider->Current.BoundingRectangle.Bottom - 12)));
				Mouse::MoveTo(System::Drawing::Point(Convert::ToInt32(perReadWriteSliderThumb->GetClickablePoint().X), Convert::ToInt32(perReadWriteSliderThumb->GetClickablePoint().Y)));
				Mouse::DragTo(MouseButton::Left, System::Drawing::Point(Convert::ToInt32(perReadWriteSlider->Current.BoundingRectangle.Left + 12), Convert::ToInt32(perReadWriteSlider->Current.BoundingRectangle.Bottom - 12)));
				break;
			case 1: //Seq Read
				Mouse::MoveTo(System::Drawing::Point(Convert::ToInt32(perSeqRanSliderThumb->GetClickablePoint().X), Convert::ToInt32(perSeqRanSliderThumb->GetClickablePoint().Y)));
				Mouse::DragTo(MouseButton::Left, System::Drawing::Point(Convert::ToInt32(perSeqRanSlider->Current.BoundingRectangle.Left + 12), Convert::ToInt32(perSeqRanSlider->Current.BoundingRectangle.Bottom - 12)));
				Mouse::MoveTo(System::Drawing::Point(Convert::ToInt32(perReadWriteSliderThumb->GetClickablePoint().X), Convert::ToInt32(perReadWriteSliderThumb->GetClickablePoint().Y)));
				Mouse::DragTo(MouseButton::Left, System::Drawing::Point(Convert::ToInt32(perReadWriteSlider->Current.BoundingRectangle.Right - 12), Convert::ToInt32(perReadWriteSlider->Current.BoundingRectangle.Bottom - 12)));
				break;
			case 2: //Ran Write
				Mouse::MoveTo(System::Drawing::Point(Convert::ToInt32(perSeqRanSliderThumb->GetClickablePoint().X), Convert::ToInt32(perSeqRanSliderThumb->GetClickablePoint().Y)));
				Mouse::DragTo(MouseButton::Left, System::Drawing::Point(Convert::ToInt32(perSeqRanSlider->Current.BoundingRectangle.Right - 12), Convert::ToInt32(perSeqRanSlider->Current.BoundingRectangle.Bottom - 12)));
				Mouse::MoveTo(System::Drawing::Point(Convert::ToInt32(perReadWriteSliderThumb->GetClickablePoint().X), Convert::ToInt32(perReadWriteSliderThumb->GetClickablePoint().Y)));
				Mouse::DragTo(MouseButton::Left, System::Drawing::Point(Convert::ToInt32(perReadWriteSlider->Current.BoundingRectangle.Left + 12), Convert::ToInt32(perReadWriteSlider->Current.BoundingRectangle.Bottom - 12)));
				break;
			case 3: //Ran Read
				Mouse::MoveTo(System::Drawing::Point(Convert::ToInt32(perSeqRanSliderThumb->GetClickablePoint().X), Convert::ToInt32(perSeqRanSliderThumb->GetClickablePoint().Y)));
				Mouse::DragTo(MouseButton::Left, System::Drawing::Point(Convert::ToInt32(perSeqRanSlider->Current.BoundingRectangle.Right - 12), Convert::ToInt32(perSeqRanSlider->Current.BoundingRectangle.Bottom - 12)));
				Mouse::MoveTo(System::Drawing::Point(Convert::ToInt32(perReadWriteSliderThumb->GetClickablePoint().X), Convert::ToInt32(perReadWriteSliderThumb->GetClickablePoint().Y)));
				Mouse::DragTo(MouseButton::Left, System::Drawing::Point(Convert::ToInt32(perReadWriteSlider->Current.BoundingRectangle.Right - 12), Convert::ToInt32(perReadWriteSlider->Current.BoundingRectangle.Bottom - 12)));
			}
			AutomationElement^ okButton = editAccessWindow->FindFirst(TreeScope::Children, (gcnew PropertyCondition(AutomationElement::NameProperty, "OK")));
			InvokePattern^ okButtonInvokePattern = (InvokePattern^)okButton->GetCurrentPattern(InvokePattern::Pattern);
			okButtonInvokePattern->Invoke();
			Sleep(100);
			addButtonInvokePattern->Invoke();
		}
	}
	AutomationElement^ testSetupTab = AutomationElement::RootElement->FindFirst(TreeScope::Descendants, (gcnew PropertyCondition(AutomationElement::NameProperty, "Test Setup")));
	SelectionItemPattern^ testSetupTabSelectPattern = (SelectionItemPattern ^)testSetupTab->GetCurrentPattern(SelectionItemPattern::Pattern);
	testSetupTabSelectPattern->Select();
	AutomationElement^ secondsRunTime = testSetupTab->FindFirst(TreeScope::Children, (gcnew PropertyCondition(AutomationElement::AutomationIdProperty, "3005")));
	ValuePattern^ secondsRunTimePattern = (ValuePattern ^)secondsRunTime->GetCurrentPattern(ValuePattern::Pattern);
	secondsRunTimePattern->SetValue(iometerRunTimeInput->Text);
	AutomationElement^ rampUpTime = testSetupTab->FindFirst(TreeScope::Children, (gcnew PropertyCondition(AutomationElement::AutomationIdProperty, "3000")));
	ValuePattern^ rampUpTimePattern = (ValuePattern ^)rampUpTime->GetCurrentPattern(ValuePattern::Pattern);
	rampUpTimePattern->SetValue(iometerRampUpTimeInput->Text);
	AutomationElement^ recordResults = testSetupTab->FindFirst(TreeScope::Children, (gcnew PropertyCondition(AutomationElement::AutomationIdProperty, "1009")));
	AutomationElement^ recordResultsListItem = recordResults->FindFirst(TreeScope::Descendants, (gcnew PropertyCondition(AutomationElement::NameProperty, "None")));
	SelectionItemPattern^ recordResultsListItemSelectPattern = (SelectionItemPattern ^)recordResultsListItem->GetCurrentPattern(SelectionItemPattern::Pattern);
	recordResultsListItemSelectPattern->Select();
	AutomationElement^ resultsDisplayTab = AutomationElement::RootElement->FindFirst(TreeScope::Descendants, (gcnew PropertyCondition(AutomationElement::NameProperty, "Results Display")));
	SelectionItemPattern^ resultsDisplayTabSelectPattern = (SelectionItemPattern ^)resultsDisplayTab->GetCurrentPattern(SelectionItemPattern::Pattern);
	resultsDisplayTabSelectPattern->Select();
	/*AutomationElement^ lastUpdate = resultsDisplayTab->FindFirst(TreeScope::Children, (gcnew PropertyCondition(AutomationElement::AutomationIdProperty, "1105")));
	SelectionItemPattern^ lastUpdateSelectPattern = (SelectionItemPattern ^)lastUpdate->GetCurrentPattern(SelectionItemPattern::Pattern);
	lastUpdateSelectPattern->Select();
	AutomationElement^ updateFrequency = resultsDisplayTab->FindFirst(TreeScope::Children, (gcnew PropertyCondition(AutomationElement::AutomationIdProperty, "1121")));
	AutomationElement^ updateFrequencyListItem = updateFrequency->FindFirst(TreeScope::Descendants, (gcnew PropertyCondition(AutomationElement::NameProperty, "30")));
	SelectionItemPattern^ updateFrequencyListItemSelectPattern = (SelectionItemPattern ^)updateFrequencyListItem->GetCurrentPattern(SelectionItemPattern::Pattern);
	updateFrequencyListItemSelectPattern->Select();*/
	AutomationElement^ startButton = AutomationElement::RootElement->FindFirst(TreeScope::Descendants, (gcnew PropertyCondition(AutomationElement::NameProperty, "Start Tests")));
	InvokePattern^ startButtonInvokePattern = (InvokePattern^)startButton->GetCurrentPattern(InvokePattern::Pattern);
	StopThread();
	resultsUpdateThread = gcnew Thread(gcnew ThreadStart(this, &AutoBenchUI::UpdateThreadProc));
	resultsUpdateThread->IsBackground = TRUE;
	resultsUpdateThread->Start();
	startButtonInvokePattern->Invoke();
}

void AutoBenchUI::CDMUpdateThreadProc(void) {
	AutomationElement^ mainMenu = AutomationElement::RootElement->FindFirst(TreeScope::Descendants, gcnew AndCondition(gcnew PropertyCondition(AutomationElement::NameProperty, "CrystalDiskMark"),
		gcnew PropertyCondition(AutomationElement::ControlTypeProperty, ControlType::Pane)));
	AutomationElement^ stopButton;
	int rowCount = CDMResultsDataView->RowCount;
	Thread::Sleep(1000);
	stopButton = mainMenu->FindFirst(TreeScope::Descendants, gcnew AndCondition(gcnew PropertyCondition(AutomationElement::NameProperty, "Stop"),
		gcnew PropertyCondition(AutomationElement::ControlTypeProperty, ControlType::Hyperlink)));
	while (true) {
		Thread::Sleep(10000);
		if (stopButton->Current.Name->Equals("All")) {
			AutomationElementCollection^ resultsCollection = mainMenu->FindAll(TreeScope::Descendants, gcnew PropertyCondition(AutomationElement::ControlTypeProperty, ControlType::Text));
			CDMResultsDataView->Rows[rowCount - 2]->Cells[0]->Value = resultsCollection[8]->Current.Name;
			CDMResultsDataView->Rows[rowCount - 2]->Cells[1]->Value = resultsCollection[9]->Current.Name;
			CDMResultsDataView->Rows[rowCount - 2]->Cells[2]->Value = resultsCollection[12]->Current.Name;
			CDMResultsDataView->Rows[rowCount - 2]->Cells[3]->Value = resultsCollection[13]->Current.Name;
			CDMResultsDataView->Rows[rowCount - 2]->Cells[4]->Value = resultsCollection[15]->Current.Name;
			CDMResultsDataView->Rows[rowCount - 2]->Cells[5]->Value = resultsCollection[16]->Current.Name;
			CDMResultsDataView->Rows[rowCount - 2]->Cells[6]->Value = resultsCollection[18]->Current.Name;
			CDMResultsDataView->Rows[rowCount - 2]->Cells[7]->Value = resultsCollection[19]->Current.Name;
			CDMResultsDataView->Rows->Insert(rowCount - 1);
			cdmProcess->CloseMainWindow();
			cdmProcess->Close();
			return;
		}
	}
}

void AutoBenchUI::UpdateThreadProc(void) {
	AutomationElement^ speedText = AutomationElement::RootElement->FindFirst(TreeScope::Descendants, (gcnew PropertyCondition(AutomationElement::AutomationIdProperty, "2101")));
	AutomationElement^ iopsText = AutomationElement::RootElement->FindFirst(TreeScope::Descendants, (gcnew PropertyCondition(AutomationElement::AutomationIdProperty, "2100")));
	AutomationElement^ testStatus0 = AutomationElement::RootElement->FindFirst(TreeScope::Descendants, (gcnew PropertyCondition(AutomationElement::AutomationIdProperty, "StatusBar.Pane0")));
	AutomationElement^ testStatus1 = AutomationElement::RootElement->FindFirst(TreeScope::Descendants, (gcnew PropertyCondition(AutomationElement::AutomationIdProperty, "StatusBar.Pane1")));
	AutomationElement^ testStatus2 = AutomationElement::RootElement->FindFirst(TreeScope::Descendants, (gcnew PropertyCondition(AutomationElement::AutomationIdProperty, "StatusBar.Pane2")));
	int rowCount = iometerResultsDataView->RowCount;
	int currentTest, prevTest = 1;
	eachBlockSize->Reset();
	eachBlockSize->MoveNext();
	while (true) {
		Thread::Sleep(10000);
		if (testStatus0->Current.Name->Equals("Test Completed Successfully")) {
			iometerResultsDataView->Rows[rowCount - 2]->Cells[7]->Value = speedText->Current.Name;
			iometerResultsDataView->Rows[rowCount - 2]->Cells[8]->Value = iopsText->Current.Name;
			iometerResultsDataView->Rows[rowCount - 2]->Cells[0]->Value = eachBlockSize->Current;
			iometerResultsDataView->Rows->Insert(rowCount - 1, 1);
			iometerProcess->CloseMainWindow();
			iometerProcess->Close();
			return;
		}
		if (!testStatus1->Current.Name->Equals("Preparing Drives")) {
			//Match^ testNum = Regex::Match(testStatus2->Current.Name, "Run\\s+(.+)\\s+of");
			currentTest = Int32::Parse(Regex::Match(testStatus2->Current.Name, "Run\\s+(.+)\\s+of")->Groups[1]->Value);
			if (currentTest != 1 && currentTest != prevTest) {
				prevTest = currentTest;
				switch (currentTest % 4) {
				case 0:
					iometerResultsDataView->Rows[rowCount - 2]->Cells[5]->Value = speedText->Current.Name;
					iometerResultsDataView->Rows[rowCount - 2]->Cells[6]->Value = iopsText->Current.Name;
					break;
				case 1:
					iometerResultsDataView->Rows[rowCount - 2]->Cells[7]->Value = speedText->Current.Name;
					iometerResultsDataView->Rows[rowCount - 2]->Cells[8]->Value = iopsText->Current.Name;
					iometerResultsDataView->Rows[rowCount - 2]->Cells[0]->Value = eachBlockSize->Current;
					eachBlockSize->MoveNext();
					iometerResultsDataView->Rows->Insert(rowCount - 1, 1);
					rowCount++;
					break;
				case 2:
					iometerResultsDataView->Rows[rowCount - 2]->Cells[1]->Value = speedText->Current.Name;
					iometerResultsDataView->Rows[rowCount - 2]->Cells[2]->Value = iopsText->Current.Name;
					break;
				case 3:
					iometerResultsDataView->Rows[rowCount - 2]->Cells[3]->Value = speedText->Current.Name;
					iometerResultsDataView->Rows[rowCount - 2]->Cells[4]->Value = iopsText->Current.Name;
				}
			}
		}
	}
}

void AutoBenchUI::StopThread(void) {
	if (resultsUpdateThread != nullptr) {
		resultsUpdateThread->Interrupt();
		resultsUpdateThread = nullptr;
	}
}
