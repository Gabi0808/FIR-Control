#include <iostream>
#include <string>

using namespace std;

int login();
void mainmenu(int acccesType);
void selectAction(int accessType);

int login()
{

    string username, password;
    int access = 3;
    while (access > 0)
    {
        system("cls");
        cout << "Bienvenido al menu principal de FIR-Control" << endl;
        cout << endl
             << endl
             << "Inicie sesion para acceder a las funciones." << endl;
        cout << "Intentos restantes: " << access << endl;
        cout << "Ingrese su usuario: " << endl;
        cin >> username;
        cout << "Ingrese su contrasena: " << endl;
        cin >> password;

        if (username == "BarBrother" && password == "banana123")
        {
            cout << "Acceso concedido como empeleado de Bar Brother" << endl;
            return 1;
            break;
        }
        else if (username == "BarBrotherG" && password == "banana321")
        {
            cout << "Acceso concedidio como gerente de Bar Brother" << endl;
            return 2;
            break;
        }
        else
        {
            cout << "Usuario o contrasena erroneo, intente de nuevo";
            access--;
            system("pause");
        }
    }
    cout << "Limite de intentos alcanzado" << endl;
    cout << "Saliendo del programa..." << endl;
    return 0;
}

void mainmenu(int accesType)
{
    if (accesType == 2)
    {
        cout << "Sistema FIR-Control / Gerencia" << endl
             << endl;
        cout << "Acceder a:" << endl;
        cout << "1. Control de Inventario." << endl;
        cout << "2. Control de ordenes y mesas." << endl;
        cout << "3. Generacion de reportes." << endl;
        cout << "4. Salir del programa.";
    }
    else
    {

        cout << "Sistema FIR-Control / Empleados" << endl
             << endl;
        cout << "Acceder a:" << endl;
        cout << "1. Control de Inventario." << endl;
        cout << "2. Control de ordenes y mesas." << endl;
        cout << "3. Salir del programa." << endl;
    }
}

void selectAction(int accessType)
{

    int option;
    cin >> option;
    if (accessType == 2)
        do
        {
            mainmenu(login());

            switch (option)
            {
            case 1:
                /* code */
                break;
            case 2:

                break;
            case 3:
                break;
            case 4:
                break;
            default:
                break;
            }

        } while (option != 4);
    else
        do
        {
            mainmenu(login());

            switch (option)
            {
            case 1:
                /* code */
                break;
            case 2:

                break;
            case 3:
                break;
            default:
                break;
            }
        } while (option != 3);
}

int main(int argc, char const *argv[])
{
    login();
    selectAction(login());
    return 0;
}

