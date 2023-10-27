#include <iostream>
#include <string>

using namespace std;

int login();
void mainmenu(int acccesType);
void selectAction(int accessType);
void inventoryModuleMenu();
void selectInventoryModuleAction();
void facturationModuleMenu();
void selectFacturationModuleAction();

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
        }
        else if (username == "BarBrotherG" && password == "banana321")
        {
            cout << "Acceso concedidio como gerente de Bar Brother" << endl;
            return 2;
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
    system("cls");
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
    mainmenu(accessType);
    int option;
    if (accessType == 2)
        do
        {
            mainmenu(accessType);
            cin >> option;
            switch (option)
            {
            case 1:
                selectInventoryModuleAction();
                break;
            case 2:
                selectFacturationModuleAction();
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
            mainmenu(accessType);
            cin >> option;
            switch (option)
            {
            case 1:
                selectInventoryModuleAction();
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

void inventoryModuleMenu()
{
    system("cls");
    cout << "Modulo de Inventario." << endl
         << endl;
    cout << "Seleccione la opcion a realizar." << endl
         << endl;
    cout << "1. Ver inventario." << endl;
    cout << "2. Agregar producto al inventario." << endl;
    cout << "3. Eliminar producto al inventario." << endl;
    cout << "4. Modificar producto del inventario." << endl;
    cout << "5. Actualizar inventario." << endl;
    cout << "6. Regresar al menu principal." << endl;
}

void selectInventoryModuleAction()
{

    int option = 0;
    while (option != 6)
    {
        inventoryModuleMenu();
        cin >> option;
        switch (option)
        {
        case 1:
            cout << "Hola";
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            cout << "Regresando al menu principal..." << endl;
            break;
        default:
            break;
        }
    }
}

void facturationModuleMenu()
{

    system("cls");
    cout << "Control de ordenes y mesas." << endl
         << endl;
    cout << "Seleccione la opcion a realizar." << endl
         << endl;
    cout << "1. Selccionar mesa." << endl;
    cout << "2. Mostrar informacion de mesas." << endl;
    cout << "3. Agregar mesa." << endl;
    cout << "4. Eliminar mesa." << endl;
    cout << "5. Modificar mesa." << endl;
    cout << "6. Regresar al menu principal." << endl;
}

void selectFacturationModuleAction()
{
    int option = 0;
    while (option != 6)
    {
        facturationModuleMenu();
        cin >> option;
        switch (option)
        {
        case 1:
            cout << "Hola";
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            cout << "Regresando al menu principal..." << endl;
            break;
        default:
            break;
        }
    }
}
