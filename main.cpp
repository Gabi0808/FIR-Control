#include <iostream>
#include "interfaces.cpp"

using namespace std;

int main()
{
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_MAXIMIZE);
    int resultadoLogin = login();
    if (resultadoLogin == 0)
    {
        return 0;
    }
    seleccionarAccion(resultadoLogin);
    return 0;
}