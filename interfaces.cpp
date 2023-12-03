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
        cout << "Ingrese su usuario: \n"
             << endl;
        cin >> usuario;
        cout << "Ingrese su contrasena: " << endl;
        cin >> contrasena;

        if (usuario == "BarBrother" && contrasena == "banana123")
        {
            cout << "Acceso concedido como empleado de Bar Brother" << endl;
            system("pause");
            return 1;
        }
        else if (usuario == "BarBrotherG" && contrasena == "banana321")
        {
            cout << "Acceso concedido como gerente de Bar Brother" << endl;
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
    if (accesType == 2)
    {
        cout << "Sistema FIR-Control / Gerencia" << endl
             << endl;
        cout << "Acceder a:" << endl;
        cout << "\n\t1. Control de Inventario." << endl;
        cout << "\t2. Control de ordenes y mesas." << endl;
        cout << "\t3. Generacion de reportes." << endl;
        cout << "\t4. Salir del programa." << endl;
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
        cout << "\nIngrese una opcion: ";
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
    cout << "Seleccione una opcion: " << endl
         << endl;
    cout << "\t1. Control de productos " << endl;
    cout << "\t2. Control de insumos" << endl;
    cout << "\t3. Salir. " << endl;
}

void seleccionarAccionControlInventario()
{
    int opcion = 0;

    do
    {
        menuControlInventario();
        cout << "Ingrese una opcion: ";
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
    cout << "Modulo de Inventario." << endl
         << endl;
    cout << "Seleccione la opcion a realizar." << endl
         << endl;
    cout << "Cantidad de registros: " << ultimoRegistro << endl;
    cout << "1. Ver inventario." << endl;
    cout << "2. Agregar producto al inventario." << endl;
    cout << "3. Buscar producto" << endl;
    cout << "4. Eliminar producto al inventario." << endl;
    cout << "5. Modificar producto del inventario." << endl;
    cout << "6. Registrar entrada/salida." << endl;
    cout << "7. Regresar al menu principal." << endl;
}
void seleccionarAccionModuloInventario()
{
    int resultadoBusqueda = -1;
    int opcion = 0;

    do
    {
        menuModuloInventario();
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
                for (int i = 0; i < ultimoRegistro; i++)
                {
                    mostrarProducto(inventarioProducto[i]);
                }
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
    cout << "Insumos del inventario" << endl;
    cout << "\nSeleccione la opcion a realizar." << endl;
    cout << "Cantidad de registros: " << ultimoRegistroInsumos << endl;
    cout << "1. Ver insumos." << endl;
    cout << "2. Agregar insumo." << endl;
    cout << "3. Buscar insumo." << endl;
    cout << "4. Eliminar insumo." << endl;
    cout << "5. Modificar insumo." << endl;
    cout << "6. Registrar entrada/salida de insumo." << endl;
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
            }

            system("pause");
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
    cout << "Control de ordenes." << endl
         << endl;
    cout << "Seleccione la opcion a realizar." << endl
         << endl;
    cout << "1. Mostrar registro de ordenes. " << endl;
    cout << "2. Buscar orden por codigo. " << endl;
    cout << "3. Agregar orden. " << endl;
    cout << "4. Eliminar orden. " << endl;
    cout << "5. Modificar orden. " << endl;
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
    cout << "Modulo de Facturacion." << endl
         << endl;
    cout << "Seleccione la opcion a realizar." << endl
         << endl;
    cout << "1. Control de mesas." << endl;
    cout << "2. Control de ordenes." << endl;
    cout << "3. Control de facturas." << endl;
    cout << "4. Regresar al menu principal." << endl;
}

void seleccionarAccionModuloFacturacion()
{
    int opcion = 0;

    do
    {
        menuMF();
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
                cout << "Regresando al menu principal...";
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
    cout << "Control de Facturas." << endl
         << endl;
    cout << "Seleccione la opcion a realizar." << endl
         << endl;
    cout << "1. Generar Factura." << endl;
    cout << "2. Mostrar informacion de Facturas." << endl;
    cout << "3. Eliminar Factura." << endl;
    cout << "4. Modificar Factura." << endl;
    cout << "5. Regresar al menu principal." << endl;
}

void seleccionarAccionControlFactura()
{
    string codigoOrden;
    int tipoFactura;
    int opcion = 0;
    int resultadoBusqueda = -1;

    do
    {
        controlFactura();
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
                mostrarInfoFacturas();
                system("pause");
                break;
            case 3:
                agregarFactura();
                system("pause");
                cout << "La factura ha sido agregada exitosamente " << endl;
                break;
            case 4:
                eliminarFactura();
                break;
            case 5:
                cout << "Regresando al menu principal..." << endl;
                system("pause");
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
    } while (opcion != 5);
}

void menuModuloReportes()
{
    system("cls");
    cout << "Generacion de reportes " << endl;
    cout << "\nSeleccione la opcion a realizar " << endl;
    cout << "\n\n\t1. Generar reporte de consumo diario " << endl;
    cout << "\t2. Generar reporte de ventas semanal" << endl;
    cout << "\t3. Generar reporte de consumo mensual " << endl;
    cout << "\t4. Volver al menu principal" << endl;
}

void seleccionarModuloReportes()
{
    int opcion = 0;

    do
    {
        menuModuloReportes();
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
                generarReporteConsumoDiario();
                mostrarReporte(reportesGenerados[ultimoRegistroReportes - 1], productosEnReporte[ultimoRegistroProductosEnReporte - 1]);
                system("pause");
                break;
            case 2:
                generarReporteConsumoSemanal();
                mostrarReporte(reportesGenerados[ultimoRegistroReportes - 1], productosEnReporte[ultimoRegistroProductosEnReporte - 1]);
                system("pause");
                break;
            case 3:
                generarReporteConsumoMes();
                mostrarReporte(reportesGenerados[ultimoRegistroReportes - 1], productosEnReporte[ultimoRegistroProductosEnReporte - 1]);
                system("pause");
                break;
            case 4:
                cout << "Regresando al menu principal..." << endl;
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