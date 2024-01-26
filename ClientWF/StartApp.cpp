#include "ConForm.h"
#include <Windows.h>

using namespace ClientWF;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    Application::Run(gcnew ConForm);
    return 0;
}