#include "AutoBenchUI.h"

using namespace auto_bench;

[STAThread]//leave this as is
void main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	auto_bench::AutoBenchUI form;
	Application::Run(%form);
}