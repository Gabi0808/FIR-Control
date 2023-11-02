#include <iostream>
#include <string>
#include "moduloInventario.cpp"

using namespace std;

int login();
void menuPrincipal(int acccesType);
void seleccionarAccion(int accessType);
void menuModuloInventario();
void seleccionarAccionModuloInventario();
void menuModuloFacturacion();
void seleccionarAccionModuloFacturacion();
void menuModuloReportes();
void seleccionarModuloReportes();

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
        cout << "Ingrese su usuario: \n" << endl;
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
        cout << "\n1. Control de Inventario." << endl;
        cout << "2. Control de ordenes y mesas." << endl;
        cout << "3. Generacion de reportes." << endl;
        cout << "4. Salir del programa." << endl;
    }
    else
    {

        cout << "Sistema FIR-Control / Empleados" << endl
             << endl;
        cout << "Acceder a:" << endl;
        cout << "\n1. Control de Inventario." << endl;
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
                seleccionarAccionModuloFacturacion();
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
            mostrarRegistroInventario();
            break;
        case 2:
            ingresarProducto();
            break;
        case 3:
            cout << "Funcion no Implementada";
            break;
        case 4:
            cout << "Funcion no Implementada";
            break;
        case 5:
            cout << "Funcion no Implementada";
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
/*Hay que añadir una seccion de caja chica, asi como un menu de facturacion para controlar de mejor manera 
los pedidos a proveedores*/
/*Hay que añadir el control de cuanto rinden los ingredientes, ejemplo cuantos platos salen de x cantidad de carne
o cuantos tragos salen de una botella*/
    system("cls");
    cout << "Control de ordenes y mesas." << endl
         << endl;
    cout << "Seleccione la opcion a realizar." << endl
         << endl;
    cout << "1. Seleccionar mesa." << endl;
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
            cout << "Funcion no Implementada";
            break;
        case 2:
            cout << "Funcion no Implementada";
            break;
        case 3:
            cout << "Funcion no Implementada";
            break;
        case 4:
            cout << "Funcion no Implementada";
            break;
        case 5:
            cout << "Funcion no Implementada";
            break;
        case 6:
            cout << "Regresando al menu principal..." << endl;
            break;
        default:
            break;
        }
    }
}
void menuModuloReportes()
{
    system("cls");
    cout << "Generacion de reportes " << endl;
    cout << "Seleccione la opcion a realizar " << endl;
    cout << "1. Generar reporte de consumo semanal " << endl;
    cout << "2. Generar reporte de consumo mensual " << endl;
    cout << "3. Generar reporte de control de inventario " << endl;
    cout << "4. Generar historial de transacciones " << endl;
    cout << "5. Generar reporte de control de facturas " << endl;
    cout << "6. Volver al menu principal" << endl;

}

void seleccionarModuloReportes()
{
    int option = 0;
    while (option != 6)
    {
        menuModuloReportes();
        cin >> option;
        switch (option)    
        {
        case 1:
            cout << "Funcion no Implementada";
            break;
        case 2:
            cout << "Funcion no Implementada";
            break;
        case 3:
            cout << "Funcion no Implementada";
            break;
        case 4: 
            cout << "Funcion no Implementada";
            break;
        case 5:
            cout << "Funcion no Implementada";
            break;
        case 6:
            cout << "Regresando al menu principal..." << endl;
        default: 
            cout << "Ingresar opcion valida" << endl;
            break;
        }
    }
}