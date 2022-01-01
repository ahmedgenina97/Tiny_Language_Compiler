#include "pch.h"
#include "gui_form.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<System::String^>^ args)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    guitryclr::gui_form form;
    Application::Run(% form);
    return 0;
}