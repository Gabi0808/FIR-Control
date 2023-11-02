#include <iostream>
#include "interfaces.cpp"

using namespace std;

int main()
{
    int resultadoLogin = login();
    if (resultadoLogin == 0)
    {
        return 0;
    }
    seleccionarAccion(resultadoLogin);
    return 0;
}
