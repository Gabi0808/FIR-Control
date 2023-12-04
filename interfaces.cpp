#include <iostream>
#include <string>
#include <ctype.h>
#include "moduloInventario.cpp"
#include "moduloFacturacion.cpp"
#include "moduloReportes.cpp"

using namespace std;

int login();
void menuPrincipal(int acccesType);
void seleccionarAccion(int accessType);
void menuModuloInventario();
void seleccionarAccionModuloInventario();
void seleccionarAccionInsumos();
void menuOrdenesYMesa();
void seleccionarAccionModuloFacturacion();
void seleccionarAccionModuloMesa();
void menuModuloReportes();
void seleccionarModuloReportes();
void menuMF();
void controlFactura();
void seleccionarAccionControlFactura();
void seleccionarAccionControlInventario();
void menuControlInventario();
void menuOrdenes();
void menuMesas();
void ordenAbiertaMesas();
void seleccionarAccionOrden();
void menuSeleccionMesa();
void imprimirMarco();

void imprimirMarco()
{
    int pos = 0;
    int posy = 0;
    for (int x = 0; x < 2; x++)
    {
        for (int i = 0; i < 146; i++)
        {
            gotoxy(i, posy);
            cout << BLUE << "*";
        }
        posy = 35;
    }

    for (int j = 0; j < 2; j++)
    {

        for (int k = 0; k < 35; k++)
        {
            gotoxy(pos, k);
            cout << BLUE << "*";
        }
        pos = 145;
    }
    cout << RESET;
}

void imprimirMarcoVerde()
{
    int pos = 0;
    int posy = 0;
    for (int x = 0; x < 2; x++)
    {
        for (int i = 0; i < 146; i++)
        {
            gotoxy(i, posy);
            cout << GREEN << "*";
        }
        posy = 35;
    }

    for (int j = 0; j < 2; j++)
    {

        for (int k = 0; k < 35; k++)
        {
            gotoxy(pos, k);
            cout << GREEN << "*" << RESET;
        }
        pos = 145;
    }
}

void imprimirMarcoRojo()
{
    int pos = 0;
    int posy = 0;
    for (int x = 0; x < 2; x++)
    {
        for (int i = 0; i < 146; i++)
        {
            gotoxy(i, posy);
            cout << RED << "*";
        }
        posy = 35;
    }

    for (int j = 0; j < 2; j++)
    {

        for (int k = 0; k < 35; k++)
        {
            gotoxy(pos, k);
            cout << RED << "*" << RESET;
        }
        pos = 145;
    }
}

int login()
{
    string usuario, contrasena;
    int access = 3;
    while (access > 0)
    {
        system("cls");
        imprimirMarco();
        gotoxy(55, 0);
        cout << BLUE << BOLD << "Bienvenido al sistema FIR-Control" << endl;
        gotoxy(50, 3);
        cout << RESET << "Inicie sesion para acceder a las funciones." << endl;
        gotoxy(8, 5);
        cout << "Intentos restantes: " << access << endl;
        gotoxy(8, 7);
        cout << "Ingrese su usuario: ";
        gotoxy(28, 7);
        cin >> usuario;
        gotoxy(8, 9);
        cout << "Ingrese su contrasena: " << endl;
        gotoxy(32, 9);
        cin >> contrasena;

        if (usuario == "BarBrother" && contrasena == "banana123")
        {

            cout << "Acceso concedido como empleado de Bar Brother" << endl;
            system("pause");
            return 1;
        }
        else if (usuario == "BarBrotherG" && contrasena == "banana321")
        {
            gotoxy(8, 12);
            cout << "Acceso concedido como gerente de Bar Brother" << endl;
            gotoxy(8, 13);
            system("pause");
            return 2;
        }
        else
        {
            cout << "Usuario o contrasena Incorrecto, intente de nuevo" << endl;
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
    imprimirMarco();
    if (accesType == 2)
    {
        gotoxy(4, 2);
        cout << BOLD << BLUE << "FFFFFF  II  RRRRRR       CCCCCC  OOOOOO  NN     NN  TTTTTTTT  RRRRRR    OOOOOO  LL" << RESET << endl;
        gotoxy(4, 3);
        cout << BOLD << BLUE << "FF      II  RR  RR       CC      OO  OO  NN NN  NN  TTTTTTTT  RR  RR    OO  OO  LL  " << RESET << endl;
        gotoxy(4, 4);
        cout << BOLD << BLUE << "FFFF    II  RRRRRR  " << BOLD << CYAN << " ===" << RESET << BOLD << BLUE << " CC      OO  OO  NN  NNNNN    TTTT    RRRRRR    OO  OO  LL" << RESET << endl;
        gotoxy(4, 5);
        cout << BOLD << BLUE << "FF      II  RR  RRR      CC      OO  OO  NN   NNNN    TTTT    RR  RRR   OO  OO  LL" << RESET << endl;
        gotoxy(4, 6);
        cout << BOLD << BLUE << "FF      II  RR   RRR     CCCCCC  OOOOOO  NN    NNN    TTTT    RR   RRR  OOOOOO  LLLLLL " << RESET << endl;

        gotoxy(6, 9);
        cout << "Sistema FIR-Control / Gerencia" << endl;
        gotoxy(6, 11);
        cout << "Acceder a:" << endl;
        gotoxy(6, 13);
        cout << "1. Control de Inventario." << endl;
        gotoxy(6, 14);
        cout << "2. Control de ordenes y mesas." << endl;
        gotoxy(6, 15);
        cout << "3. Generacion de reportes." << endl;
        gotoxy(6, 16);
        cout << "4. Salir del programa." << endl;
        gotoxy(110, 3);
        cout << WHITE << ".sssssssss.";
        gotoxy(105, 4);
        cout << WHITE << ".sssssssssssssssssss";
        gotoxy(103, 5);
        cout << WHITE << "sssssssssssssssssssssssss";
        gotoxy(101, 6);
        cout << WHITE << "ssssssssssssssssssssssssssss";
        gotoxy(101, 7);
        cout << WHITE << "@@sssssssssssssssssssssss@ss";
        gotoxy(101, 8);
        cout << CYAN << "|" << WHITE << "s@@@@sssssssssssssss@@@@s" << CYAN << "|" << WHITE << "s";
        gotoxy(94, 9);
        cout << CYAN << "_______|" << WHITE << "sssss@@@@@sssss@@@@@sssss" << CYAN << "|" << WHITE << "s";
        gotoxy(92, 10);
        cout << CYAN << "/" << WHITE << "         sssssssss@sssss@sssssssss" << CYAN << "|" << WHITE << "s";
        gotoxy(91, 11);
        cout << CYAN << "/  .------+" << YELLOW << "." << WHITE << "ssssssss@sssss@ssssssss" << YELLOW << "." << CYAN << "|";
        gotoxy(90, 12);
        cout << CYAN << "/  /       |" << YELLOW << "..." << WHITE << "sssssss@sss@sssssss" << YELLOW << "..." << CYAN << "|";
        gotoxy(89, 13);
        cout << CYAN << "|  |        |" << YELLOW << "......." << WHITE << "sss@sss@ssss" << YELLOW << "......" << CYAN << "|";
        gotoxy(89, 14);
        cout << CYAN << "|  |        |" << YELLOW << ".........." << WHITE << "s@ss@sss." << YELLOW << "......" << CYAN << "|";
        gotoxy(89, 15);
        cout << CYAN << "|  |        |" << YELLOW << "..........." << WHITE << "@ss@" << YELLOW << ".........." << CYAN << "|";
        gotoxy(90, 16);
        cout << CYAN << "\\  \\       |" << YELLOW << "............" << WHITE << "ss@" << YELLOW << ".........." << CYAN << "|";
        gotoxy(91, 17);
        cout << CYAN << "\\  '------+" << YELLOW << "..........." << WHITE << "ss@" << YELLOW << "..........." << CYAN << "|";
        gotoxy(92, 18);
        cout << CYAN << "\\________ " << YELLOW << "........................." << CYAN << "|";
        gotoxy(101, 19);
        cout << CYAN << "|" << YELLOW << "........................." << CYAN << "|";
        gotoxy(100, 20);
        cout << CYAN << "/" << YELLOW << "..........................." << CYAN << "\\";
        gotoxy(100, 21);
        cout << CYAN << "|" << YELLOW << "............................" << CYAN << "|";
        gotoxy(103, 22);
        cout << CYAN << "|" << YELLOW << "......................." << CYAN << "|";
        gotoxy(107, 23);
        cout << CYAN << "|" << YELLOW << "..............." << CYAN "|" << RESET;
    }
    else
    {

        cout << "Sistema FIR-Control / Empleados" << endl
             << endl;
        cout << "Acceder a:" << endl;
        cout << "\n\t1. Control de Inventario." << endl;
        cout << "\t2. Control de ordenes y mesas." << endl;
        cout << "\t3. Salir del programa." << endl;
    }
}

void seleccionarAccion(int accessType)
{
    menuPrincipal(accessType);
    ultimoRegistro = 0;
    ultimoRegistroFacturas = 0;
    ultimoRegistroInsumos = 0;
    ultimoRegistroMesas = 0;
    ultimoRegistroOrdenes = 0;
    recuperarRegistroInsumos(inventarioInsumo, ultimoRegistroInsumos);
    recuperarRegistroInventario(inventarioProducto, ultimoRegistro);
    recuperarRegistroMesas(informacionMesas, ultimoRegistroMesas);
    recuperarOrden(registroOrdenes, ultimoRegistroOrdenes);
    recuperarRegistroFactura(informacionFacturas, ultimoRegistroFacturas);
    int opcion;
    do
    {
        menuPrincipal(accessType);
        gotoxy(8, 20);
        cout << "Ingrese una opcion: ";
        string input;
        gotoxy(29, 20);
        cin >> input;

        bool esNumero = true;
        for (char c : input)
        {
            if (!isdigit(c))
            {
                esNumero = false;
                break;
            }
        }

        if (esNumero)
        {
            opcion = stoi(input);

            if ((accessType == 2 && opcion >= 1 && opcion <= 4) || (accessType != 2 && opcion >= 1 && opcion <= 3))
            {
                switch (opcion)
                {
                case 1:
                    seleccionarAccionControlInventario();
                    break;
                case 2:
                    seleccionarAccionModuloFacturacion();
                    break;
                case 3:
                    if (accessType == 2)
                    {
                        seleccionarModuloReportes();
                    }
                    else
                    {
                        cout << "Opcion no permitida. Intentelo de nuevo." << endl;
                    }
                    break;
                case 4:
                    break;
                default:
                    break;
                }
            }
            else
            {
                cout << "Opcion fuera de rango. Intentelo de nuevo." << endl;
                system("pause");
                opcion = -1;
            }
        }
        else
        {
            cout << "Por favor, ingrese un numero valido." << endl;
            system("pause");
            opcion = -1;
        }

    } while ((accessType == 2 && opcion != 4) || (accessType != 2 && opcion != 3));
}
void menuControlInventario()
{
    system("cls");
    imprimirMarco();
    gotoxy(62, 0);
    cout << GREEN << "Modulo Inventario" << RESET << endl;
    gotoxy(5, 3);
    cout << "Seleccione una opcion: " << endl;
    gotoxy(13, 5);
    cout << "1. Control de productos " << endl;
    gotoxy(13, 6);
    cout << "2. Control de insumos" << endl;
    gotoxy(13, 7);
    cout << "3. Salir. " << endl;
}

void seleccionarAccionControlInventario()
{
    int opcion = 0;

    do
    {
        menuControlInventario();
        gotoxy(5, 9);
        cout << "Ingrese una opcion: ";
        string input;
        gotoxy(26, 9);
        cin >> input;

        bool esNumero = true;
        for (char c : input)
        {
            if (!isdigit(c))
            {
                esNumero = false;
                break;
            }
        }

        if (esNumero)
        {
            opcion = stoi(input);

            switch (opcion)
            {
            case 1:
                seleccionarAccionModuloInventario();
                break;
            case 2:
                seleccionarAccionInsumos();
                break;
            case 3:
                cout << "Regresando al menu principal... " << endl;
                system("pause");
                break;
            default:
                cout << "Opcion no valida. " << endl;
                system("pause");
                break;
            }
        }
        else
        {
            cout << "\n\n\nIngrese un numero valido. " << endl;
            opcion = -1;
            cin.clear();
            cin.ignore();
            system("pause");
        }
    } while (opcion != 3);
}

void menuModuloInventario()
{
    system("cls");
    imprimirMarco();
    gotoxy(62, 0);
    cout << GREEN << "Modulo de Inventario." << RESET << endl;
    gotoxy(5, 3);
    cout << "Seleccione la opcion a realizar." << endl;
    gotoxy(5, 5);
    cout << "Cantidad de registros: " << ultimoRegistro << endl;
    gotoxy(5, 7);
    cout << "1. Ver inventario." << endl;
    gotoxy(5, 8);
    cout << "2. Agregar producto al inventario." << endl;
    gotoxy(5, 9);
    cout << "3. Buscar producto" << endl;
    gotoxy(5, 10);
    cout << "4. Eliminar producto al inventario." << endl;
    gotoxy(5, 11);
    cout << "5. Modificar producto del inventario." << endl;
    gotoxy(5, 12);
    cout << "6. Registrar entrada/salida." << endl;
    gotoxy(5, 13);
    cout << "7. Regresar al menu principal." << endl;
}
void seleccionarAccionModuloInventario()
{
    int resultadoBusqueda = -1;
    int opcion = 0;

    do
    {
        menuModuloInventario();
        gotoxy(5, 15);
        cout << "Ingrese la opcion a realizar: ";
        string input;
        cin >> input;

        bool esNumero = true;
        for (char c : input)
        {
            if (!isdigit(c))
            {
                esNumero = false;
                break;
            }
        }

        if (esNumero)
        {
            opcion = stoi(input);

            switch (opcion)
            {
            case 1:
                system("cls");
                mostrarInventarioProductos(inventarioProducto);
                system("pause");

                break;
            case 2:
                ingresarProducto();
                break;
            case 3:
                cout << "Ingrese el codigo del producto que desea buscar ";
                cin >> codigoABuscar;
                resultadoBusqueda = buscarProducto(codigoABuscar);
                if (resultadoBusqueda != -1)
                {
                    mostrarProducto(inventarioProducto[resultadoBusqueda]);
                    system("pause");
                }
                else
                {
                    cout << "No se encontro producto con ese codigo." << endl;
                }

                system("pause");
                break;
            case 4:
                cout << "Ingrese el codigo del producto que desea eliminar ";
                cin >> codigoABuscar;
                eliminarProducto(codigoABuscar);
                break;
            case 5:
                cout << "Ingrese el codigo del producto que desea modificar ";
                cin >> codigoABuscar;
                modificarProducto(codigoABuscar);
                break;
            case 6:
                cout << "Ingrese el codigo del producto que entro o salio ";
                cin >> codigoARegistrar;
                registrarEntradaSalida(codigoARegistrar);
                break;
            case 7:
                cout << "Regresando al menu principal..." << endl;
                return;
                break;
            default:
                cout << "Seleccione una opcion valida. ";
                break;
            }
        }
        else
        {
            cout << "\n\nIngrese un numero valido. " << endl;
            opcion = -1;
            cin.clear();
            cin.ignore();
            system("pause");
        }
    } while (opcion != 7);
}

void menuInsumos()
{
    system("cls");
    imprimirMarco();
    gotoxy(5, 3);
    cout << "Control de insumos" << endl;
    gotoxy(5, 5);
    cout << "Seleccione la opcion a realizar." << endl;
    gotoxy(5, 6);
    cout << "Cantidad de registros: " << ultimoRegistroInsumos << endl;
    gotoxy(5, 8);
    cout << "1. Ver insumos." << endl;
    gotoxy(5, 9);
    cout << "2. Agregar insumo." << endl;
    gotoxy(5, 10);
    cout << "3. Buscar insumo." << endl;
    gotoxy(5, 11);
    cout << "4. Eliminar insumo." << endl;
    gotoxy(5, 12);
    cout << "5. Modificar insumo." << endl;
    gotoxy(5, 13);
    cout << "6. Registrar entrada/salida de insumo." << endl;
    gotoxy(5, 14);
    cout << "7. Volver al menu principal." << endl;
}

void seleccionarAccionInsumos()
{
    int resultadoBusqueda = -1;
    int opcion = 0;
    while (opcion != 7)
    {
        menuInsumos();
        cin >> opcion;
        switch (opcion)
        {
        case 1:
            system("cls");
            for (int i = 0; i < ultimoRegistroInsumos; i++)
            {
                mostrarInsumo(inventarioInsumo[i]);
            }
            system("pause");

            break;
        case 2:
            ingresarInsumo();
            break;
        case 3:
            cout << "Ingrese el codigo del insumo que desea buscar ";
            cin >> codigoABuscar;
            resultadoBusqueda = buscarInsumo(codigoABuscar);
            if (resultadoBusqueda != -1)
            {
                mostrarInsumo(inventarioInsumo[resultadoBusqueda]);
                system("pause");
            }
            else
            {
                cout << "No se encontro un insumo con ese codigo. " << endl;
                system("pause");
            }

            break;
        case 4:
            cout << "Ingrese el codigo del insumo que desea eliminar";
            cin >> codigoABuscar;
            eliminarInsumo(codigoABuscar);
            break;
        case 5:
            cout << "Ingrese el codigo del insumo que desea modificar ";
            cin >> codigoABuscar;
            modificarInsumo(codigoABuscar);
            break;
        case 6:
            cout << "Ingrese el codigo del insumo que entro o salio";
            cin >> codigoABuscar;
            registrarEntradaSalidaInsumo(codigoARegistrar);
            break;
        case 7:
            cout << "Regresando al menu principal..." << endl;
            return;
            break;
        default:
            cout << "Seleccione una opcion valida";
            break;
        }
    }
}

void menuMesas()
{
    system("cls");
    imprimirMarcoRojo();
    gotoxy(5, 4);
    cout << "Control de ordenes y mesas." << endl;
    gotoxy(5, 6);
    cout << "Seleccione la opcion a realizar." << endl;
    gotoxy(5, 8);
    cout << "1. Seleccionar mesa." << endl;
    gotoxy(5, 9);
    cout << "2. Mostrar informacion de mesas." << endl;
    gotoxy(5, 10);
    cout << "3. Agregar mesa." << endl;
    gotoxy(5, 11);
    cout << "4. Eliminar mesa." << endl;
    gotoxy(5, 12);
    cout << "5. Modificar mesa." << endl;
    gotoxy(5, 13);
    cout << "6. Regresar al menu principal." << endl;
}

void menuOrdenes()
{
    system("cls");
    cout << "Seleccione la Mesa que desea usar." << endl
         << endl;
    cout << "1. ." << endl;
    cout << "2. " << endl;
    cout << "3. " << endl;
    cout << "4. " << endl;
    cout << "5. " << endl;
    cout << "6. " << endl;
}

void ordenAbiertaMesas()
{

    system("cls");
    imprimirMarcoRojo();
    gotoxy(5, 4);
    cout << "Control de ordenes." << endl;
    gotoxy(5, 6);
    cout << "Seleccione la opcion a realizar." << endl;
    gotoxy(5, 8);
    cout << "1. Mostrar registro de ordenes. " << endl;
    gotoxy(5, 9);
    cout << "2. Buscar orden por codigo. " << endl;
    gotoxy(5, 10);
    cout << "3. Agregar orden. " << endl;
    gotoxy(5, 11);
    cout << "4. Eliminar orden. " << endl;
    gotoxy(5, 12);
    cout << "5. Modificar orden. " << endl;
    gotoxy(5, 13);
    cout << "6. Regresar al menu principal." << endl;
}

void seleccionarAccionOrden()
{
    int resultadoBusqueda = -1;
    string codigoOrdenABuscar;
    int opcion = 0;
    while (opcion != 4)
    {
        ordenAbiertaMesas();
        gotoxy(5, 15);
        cin >> opcion;
        switch (opcion)
        {
        case 1:
            mostrarInfoOrdenes(registroOrdenes, ultimoRegistroOrdenes);
            system("pause");
            break;
        case 2:
            cout << "Ingrese el codigo del producto que desea buscar ";
            cin >> codigoABuscar;
            resultadoBusqueda = buscarProducto(codigoABuscar);
            if (resultadoBusqueda != -1)
            {
                mostrarOrden(registroOrdenes[resultadoBusqueda]);
                system("pause");
            }
            else
            {
                cout << "No se encontro orden con ese codigo." << endl;
            }

            system("pause");
            break;
        case 3:
            system("cls");
            agregarOrden();
            break;
        case 4:
            cout << "Ingrese el codigo de la orden que desea eliminar ";
            cin >> codigoOrdenABuscar;
            eliminarOrden(codigoOrdenABuscar);
            break;
        case 5:
            cout << "Ingrese el codigo de la orden que desea modificar ";
            cin >> codigoOrdenABuscar;
            modificarOrden(codigoOrdenABuscar);
            break;
        case 6:
            cout << "Regresando al menu principal" << endl;
            return;
            break;
        default:
            cout << "Opcion no valida. Ingrese una opcion correcta";
            system("pause");
            break;
        }
    }
}

void menuMF()
{
    system("cls");
    imprimirMarcoRojo();
    gotoxy(5, 4);
    cout << "Modulo de Facturacion." << endl;
    gotoxy(5, 6);
    cout << "Seleccione la opcion a realizar." << endl;
    gotoxy(5, 8);
    cout << "1. Control de mesas." << endl;
    gotoxy(5, 9);
    cout << "2. Control de ordenes." << endl;
    gotoxy(5, 10);
    cout << "3. Control de facturas." << endl;
    gotoxy(5, 11);
    cout << "4. Regresar al menu principal." << endl;
}

void seleccionarAccionModuloFacturacion()
{
    int opcion = 0;

    do
    {
        menuMF();
        string input;
        gotoxy(5, 12);
        cin >> input;

        bool esNumero = true;
        for (char c : input)
        {
            if (!isdigit(c))
            {
                esNumero = false;
                break;
            }
        }

        if (esNumero)
        {
            opcion = stoi(input);

            switch (opcion)
            {
            case 1:
                seleccionarAccionModuloMesa();
                break;
            case 2:
                seleccionarAccionOrden();
                system("pause");
                break;
            case 3:
                seleccionarAccionControlFactura();
                system("pause");
                break;
            case 4:
                cout << "Regresando al menu principal..." << endl;
                system("pause");
                return;
                break;
            default:
                cout << "Ingrese una opcion valida";
                break;
            }
        }
        else
        {
            cout << "Ingrese un numero valido. " << endl;
            opcion = -1;
            cin.clear();
            cin.ignore();
            system("pause");
        }
    } while (opcion != 4);
}

void seleccionarAccionModuloMesa()
{
    int opcion = 0;

    do
    {
        menuMesas();
        string input;
        cin >> input;

        bool esNumero = true;
        for (char c : input)
        {
            if (!isdigit(c))
            {
                esNumero = false;
                break;
            }
        }

        if (esNumero)
        {
            opcion = stoi(input);

            switch (opcion)
            {
            case 1:
                seleccionarMesa();
                break;
            case 2:
                for (int i = 0; i < ultimoRegistroMesas; i++)
                {
                    mostrarInfoMesas(informacionMesas[i], ordenesAbiertas[i]);
                    system("pause");
                }
                break;
            case 3:
                agregarMesa();
                system("pause");
                cout << "La mesa ha sido agregada exitosamente ";
                break;
            case 4:
                eliminarMesa();
                break;
            case 5:
                modificarMesa();
                break;
            case 6:
                cout << "Regresando al menu principal..." << endl;
                system("pause");
                return;
                break;
            default:
                break;
            }
        }
        else
        {
            cout << "\n\nIngrese un numero valido. " << endl;
            opcion = -1;
            cin.clear();
            cin.ignore();
            system("pause");
        }
    } while (opcion != 6);
}

void menuSeleccionMesa()
{
    system("cls");
    cout << " 1. Ver orden actual " << endl;
    cout << " 2. Agregar producto a la Orden" << endl;
    cout << " 3. Eliminar Producto de la Orden" << endl;
    cout << " 4. Cerrar Orden" << endl;
    cout << " 5. Salir" << endl;
}

void seleccionarMesa()
{
    int numeroMesa = 0;
    string codigoProductoAEliminar;
    cout << "Cual mesa desea atender? ";
    cin >> numeroMesa;

    if (cin.fail())
    {
        cerr << "Entrada invalida. Por favor, ingrese un numero valido." << endl;
        cin.clear();
        cin.ignore();
        system("pause");
        return;
    }

    int respuesta;
    if (numeroMesa < 1 || numeroMesa > ultimoRegistroMesas)
    {
        cerr << "Numero de mesa no valido." << endl;
        system("pause");
        return;
    }
    numeroMesa--;

    if (informacionMesas[numeroMesa].estadoMesa == "libre")
    {
        informacionMesas[numeroMesa].estadoMesa = "ocupada";
    }
    else
    {
        cout << "La mesa #" << numeroMesa + 1 << " esta siendo ocupada" << endl;
        cout << "Ingrese una opcion" << endl;
        cout << "1. Seleccionar otra mesa" << endl;
        cout << "2. Manejar orden de la mesa " << numeroMesa + 1 << endl;

        cin >> respuesta;
        if (cin.fail())
        {
            cerr << "Entrada invalida. Por favor, ingrese un numero valido." << endl;
            cin.clear();
            cin.ignore();
            system("pause");
            return;
        }

        if (respuesta == 1)
        {
            return;
        }
        else if (respuesta == 2)
        {
            system("cls");
        }
        else
        {
            cout << "Opcion invalida " << endl;
            return;
        }
    }

    if (ordenesAbiertas[numeroMesa].numeroProductosOrdenados == 0)
    {
        inicializarOrden(numeroMesa);
    }

    int opcion = 0;

    while (opcion != 5)
    {
        menuSeleccionMesa();
        cin >> opcion;

        if (cin.fail())
        {
            cerr << "Entrada invalida. Por favor, ingrese un numero valido." << endl;
            cin.clear();
            cin.ignore();
            continue;
        }

        switch (opcion)
        {
        case 1:
            if (ordenesAbiertas[numeroMesa].numeroProductosOrdenados > 0)
            {
                mostrarOrden(ordenesAbiertas[numeroMesa]);
                system("pause");
            }
            else
            {
                cout << "No hay ordenes abiertas en esta mesa" << endl;
            }
            break;
        case 2:
            agregarProductoOrden(numeroMesa, ordenesAbiertas[numeroMesa]);
            break;
        case 3:
            cout << "Ingrese el codigo del producto que desea eliminar de la orden: " << endl;
            cin >> codigoProductoAEliminar;
            eliminarProductoOrden(numeroMesa, codigoProductoAEliminar);
            break;
        case 4:
            cerrarOrden(numeroMesa);
            informacionMesas[numeroMesa].estadoMesa == "libre";
            system("pause");
            system("clear");

            break;
        case 5:
            cout << "Regresando al menu anterior" << endl;
            return;
            break;
        default:
            cout << "Opcion no valida" << endl;
            break;
        }
    }
}

void controlFactura()
{
    system("cls");
    imprimirMarcoRojo();
    gotoxy(5, 4);
    cout << "Control de Facturas." << endl;
    gotoxy(5, 6);
    cout << "Seleccione la opcion a realizar." << endl;
    gotoxy(5, 8);
    cout << "1. Generar Factura." << endl;
    gotoxy(5, 9);
    cout << "2. Mostrar informacion de Facturas." << endl;
    gotoxy(5, 10);
    cout << "3. Buscar Factura." << endl;
    gotoxy(5, 11);
    cout << "4. Agregar Factura." << endl;
    gotoxy(5, 12);
    cout << "5. Eliminar Factura." << endl;
    gotoxy(5, 13);
    cout << "6. Regresar al menu principal." << endl;
}

void seleccionarAccionControlFactura()
{
    string codigoOrden;
    string codigoFactura;
    int tipoFactura;
    int opcion = 0;
    int resultadoBusqueda = -1;
    int resultadoBusquedaFactura = -1;

    do
    {
        controlFactura();
        string input;
        gotoxy(5, 15);
        cin >> input;

        bool esNumero = true;
        for (char c : input)
        {
            if (!isdigit(c))
            {
                esNumero = false;
                break;
            }
        }
        if (esNumero)
        {
            opcion = stoi(input);
            switch (opcion)
            {
            case 1:

                cout << "Ingrese el tipo de factura (1- Cliente Cuota Fija 2- Cliente)" << endl;
                cin >> tipoFactura;
                cout << "Ingrese el codigo de la orden " << endl;
                cin >> codigoOrden;

                resultadoBusqueda = buscarOrden(codigoOrden);
                if (resultadoBusqueda != -1)
                {
                    generarFactura(tipoFactura, registroOrdenes[resultadoBusqueda]);
                    guardarFactura(informacionFacturas);
                    cout << "Factura generada exitosamente. " << endl;
                    mostrarFactura(informacionFacturas[ultimoRegistroFacturas - 1]);
                }
                else
                {
                    cout << "No se encontro una orden con el codigo " << codigoOrden << endl;
                }
                system("pause");
                break;
            case 2:
                system("cls");
                mostrarInfoFacturas(informacionFacturas);
                system("pause");
                break;
            case 3:
                system("cls");
                gotoxy(5, 2);
                cout<< "Ingrese el numero de factura a buscar."<<endl;
                gotoxy(45, 2);
                cin >> codigoFactura;
                resultadoBusquedaFactura = buscarFactura(codigoFactura);
                system("cls");
                mostrarFactura(informacionFacturas[resultadoBusquedaFactura]);
                system("pause");
                break;
            case 4:
                agregarFactura();
                system("pause");
                cout << "La factura ha sido agregada exitosamente " << endl;
                break;
            case 5:
                eliminarFactura();
                break;
            case 6:
                gotoxy(5, 14);
                cout << "Regresando al menu principal..." << endl;
                break;
            default:
                cout << "Seleccione una opcion valida. ";
                break;
            }
        }
        else
        {
            cout << "\n\nIngrese un numero valido. " << endl;
            opcion = -1;
            cin.clear();
            cin.ignore();
            system("pause");
        }
    } while (opcion != 6);
}

void menuModuloReportes()
{
    system("cls");
    imprimirMarcoVerde();
    gotoxy(5, 3);
    cout << "Generacion de reportes " << endl;
    gotoxy(5, 5);
    cout << "Seleccione la opcion a realizar " << endl;
    gotoxy(10, 8);
    cout << "1. Generar reporte de consumo diario " << endl;
    gotoxy(10, 9);
    cout << "2. Generar reporte de ventas semanal" << endl;
    gotoxy(10, 10);
    cout << "3. Generar reporte de consumo mensual " << endl;
    gotoxy(10, 11);
    cout << "4. Volver al menu principal" << endl;
}

void seleccionarModuloReportes()
{
    int opcion = 0;

    do
    {
        menuModuloReportes();
        string input;
        gotoxy(10, 12);
        cin >> input;

        bool esNumero = true;
        for (char c : input)
        {
            if (!isdigit(c))
            {
                esNumero = false;
                break;
            }
        }
        if (esNumero)
        {
            opcion = stoi(input);
            switch (opcion)
            {
            case 1:
                generarReporteConsumoDiario();
                mostrarReporte(reportesGenerados[ultimoRegistroReportes - 1], productosEnReporte[ultimoRegistroProductosEnReporte - 1]);
                gotoxy(15, 50);
                system("pause");
                break;
            case 2:
                generarReporteConsumoSemanal();
                mostrarReporte(reportesGenerados[ultimoRegistroReportes - 1], productosEnReporte[ultimoRegistroProductosEnReporte - 1]);
                gotoxy(15, 50);
                system("pause");
                break;
            case 3:
                generarReporteConsumoMes();
                mostrarReporte(reportesGenerados[ultimoRegistroReportes - 1], productosEnReporte[ultimoRegistroProductosEnReporte - 1]);
                gotoxy(15, 50);
                system("pause");
                break;
            case 4:
                gotoxy(10, 15);
                cout << "Regresando al menu principal..." << endl;
                gotoxy(10, 16);
                system("pause");
                return;
            default:
                cout << "Ingresar opcion valida" << endl;
                break;
            }
        }
        else
        {
            cout << "\n\nIngrese un numero valido. " << endl;
            opcion = -1;
            cin.clear();
            cin.ignore();
            system("pause");
        }
    } while (opcion != 3);
}