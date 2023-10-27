#include <iostream>
#include <string>

using namespace std;

int login();
<<<<<<< HEAD
void mainmenu(int acccesType);
void selectAction(int accessType);
void inventoryModuleMenu();
void selectInventoryModuleAction();
void facturationModuleMenu();
void selectFacturationModuleAction();
void seleccionarModuloReportes();
void menuReportes();
=======
void menuPrincipal(int acccesType);
void seleccionarAccion(int accessType);
void menuModuloInventario();
void seleccionarAccionModuloInventario();
void menuModuloFacturacion();
void seleccionarAccionModuloFacturacion();
>>>>>>> d90fd5e302e482836b1624cd08851e1d5df2ba0d

int login()
{
    string usuario, contrasena;
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
        cin >> usuario;
        cout << "Ingrese su contrasena: " << endl;
        cin >> contrasena;

        if (usuario == "BarBrother" && contrasena == "banana123")
        {
            cout << "Acceso concedido como empeleado de Bar Brother" << endl;
            return 1;
        }
        else if (usuario == "BarBrotherG" && contrasena == "banana321")
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

void menuPrincipal(int accesType)
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

void seleccionarAccion(int accessType)
{
    menuPrincipal(accessType);
    int opcion;
    if (accessType == 2)
        do
        {
            menuPrincipal(accessType);
            cin >> opcion;
            switch (opcion)
            {
            case 1:
                seleccionarAccionModuloInventario();
                break;
            case 2:
                seleccionarAccionModuloFacturacion();
                break;
            case 3:
                seleccionarModuloReportes();
                break;
            case 4:
                break;
            default:
                break;
            }

        } while (opcion != 4);
    else
        do
        {
            menuPrincipal(accessType);
            cin >> opcion;
            switch (opcion)
            {
            case 1:
                seleccionarAccionModuloInventario();
                break;
            case 2:

                break;
            case 3:
                break;
            default:
                break;
            }
        } while (opcion != 3);
}

void menuModuloInventario()
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

void seleccionarAccionModuloInventario()
{

    int opcion = 0;
    while (opcion != 6)
    {
        menuModuloInventario();
        cin >> opcion;
        switch (opcion)
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

void menuModuloFacturacion()
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

void seleccionarAccionModuloFacturacion()
{
    int opcion = 0;
    while (opcion != 6)
    {
        menuModuloFacturacion();
        cin >> opcion;
        switch (opcion)
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

void seleccionarModuloReportes()
{
    int option = 0;
    while (option != 6)
    {
        menuReportes();
        cin >> option;
        switch (option)    
        {
        case1:
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
        default: 
            cout << "Ingresar opcion valida" << endl;
            break;
        }
    }
}