#include <iostream>
#include <string>
#include "moduloInventario.cpp"
#include "moduloFacturacion.cpp"

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
void ordenesActivas();
void ordenMesas();
void seleccionarAccionOrden();

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
            cout << "Usuario o contrasena Incorrecto, intente de nuevo";
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
                seleccionarAccionControlInventario();
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
                seleccionarAccionControlInventario();
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

void menuControlInventario()
{
    system("cls");
    cout << "Seleccione una opcion: " << endl;
    cout << "\t1. Control de productos " << endl;
    cout << "\t2. Control de insumos" << endl;
    cout << "\t3. Salir. " << endl;
}

void seleccionarAccionControlInventario()
{
    int opcion = 0;
    while (opcion != 3)
    {
        menuControlInventario();
        cin >> opcion;
        switch (opcion)
        {
        case 1:
            seleccionarAccionModuloInventario();
            break;
        case 2:
            seleccionarAccionInsumos();
            break;
        case 3:
            cout << "Regresando al menu principal..." << endl;
            return;
            break;
        default:
            cout << "Opcion no valida, por favor intente nuevamente." << endl;
        }
    }
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

void seleccionarAccionModuloInventario()
{
    ultimoRegistro = 0;
    int resultadoBusqueda = -1;
    recuperarRegistroInventario(inventarioProducto, ultimoRegistro);
    int opcion = 0;
    while (opcion != 7)
    {
        menuModuloInventario();
        cin >> opcion;
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
}

void seleccionarAccionInsumos()
{
    ultimoRegistroInsumos = 0;
    int resultadoBusqueda = -1;
    recuperarRegistroInsumos(inventarioInsumo, ultimoRegistroInsumos);
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

void menuMF()
{
    system("cls");
    cout << "Modulo de Facturacion." << endl
         << endl;
    cout << "Seleccione la opcion a realizar." << endl
         << endl;
    cout << "1. Control de mesas y ordenes." << endl;
    cout << "2. Control de facturas" << endl;
    cout << "3. Regresando al menu principal." << endl;
}

void menuOrdenesYMesa()
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

void ordenesActivas()
{
    system("cls");
    cout << "Seleccione la Mesa que desea usar." << endl
         << endl;
    cout << "1. ???? ." << endl;
    cout << "2. ????." << endl;
    cout << "3. ????." << endl;
    cout << "4. ????." << endl;
    cout << "5. ????." << endl;
    cout << "6. ???? ." << endl;
}

void ordenMesas()
{

    system("cls");
    cout << "Control de ordenes." << endl
         << endl;
    cout << "Seleccione la opcion a realizar." << endl
         << endl;
    cout << "1. Ver estado de la orden." << endl;
    cout << "2. Agregar producto." << endl;
    cout << "3. Eliminar producto." << endl;
    cout << "4. Regresar al menu principal." << endl;
}

void seleccionarAccionOrden()
{
    int opcion = 0;
    while (opcion != 4)
    {
        ordenMesas();
        cin >> opcion;
        switch (opcion)
        {
        case 1:
            cout << "Funcion no implementada";
            break;
        case 2:
            cout << "Funcion No implementada";
            break;
        case 3:
            cout << "Funcion no implementada";
            break;
        case 4:
            cout << "Regresando al menu principal" << endl;
            return;
        default:
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
    cout << "3. Agregar Factura." << endl;
    cout << "4. Eliminar Factura." << endl;
    cout << "5. Modificar Factura." << endl;
    cout << "6. Regresar al menu principal." << endl;
}

void seleccionarAccionModuloMesa()
{
    recuperarRegistroInventario(inventarioProducto, ultimoRegistro);
    recuperarRegistroInsumos(inventarioInsumo, ultimoRegistroInsumos);
    recuperarRegistroMesas(informacionMesas, ultimoRegistroMesas);
    int opcion = 0;
    while (opcion != 6)
    {
        menuOrdenesYMesa();
        cin >> opcion;
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
            cout << "Funcion no Implementada";
            break;
        case 6:
            cout << "Regresando al menu principal..." << endl;
            return;
            break;
        default:
            break;
        }
    }
}

void seleccionarAccionModuloFacturacion()
{
    int opcion = 0;
    while (opcion != 3)
    {
        menuMF();
        cin >> opcion;
        switch (opcion)
        {
        case 1:
            seleccionarAccionModuloMesa();
            break;
        case 2:
            seleccionarAccionControlFactura();
            system("pause");
            break;
        case 3:
            cout << "Regresando al menu principal..." << endl;
            return;
        default:
            break;
        }
    }
}

void menuSeleccionMesa()
{
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
    cout << " Cual mesa desea atender? ";
    cin >> numeroMesa;
    if (numeroMesa < 1 || numeroMesa > ultimoRegistroMesas)
    {
        cerr << "Número de mesa no valido." << endl;
        return;
    }
    numeroMesa--;
    if (ordenesAbiertas[numeroMesa].numeroProductosOrdenados == 0)
    {
        incializarOrden(numeroMesa);
    }

    int opcion = 0;

    while (opcion != 5)
    {
        menuSeleccionMesa();
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            if (ordenesAbiertas[numeroMesa].numeroProductosOrdenados > 0)
            {
                mostrarOrden(ordenesAbiertas[numeroMesa]);
            }
            else
            {
                cout << "No hay ordenes abiertas en esta mesa" << endl;
            }

            break;

        case 2:
            agregarProductoOrden(numeroMesa);
            break;
        case 3:
            cout << "Ingrese el codigo del producto que desea eliminar de la orden: " << endl;
            cin >> codigoProductoAEliminar;
            eliminarProductoOrden(numeroMesa, codigoProductoAEliminar);
            break;
        case 4:
            cerrarOrden(numeroMesa);
            break;

        case 5:
            cout << "Regresando al menú anterior" << endl;
            return;
            break;
        default:
            cout << "Opcion no valida" << endl;
            break;
        }
    }
}

void seleccionarAccionControlFactura()
{
    recuperarOrden(registroOrdenes, ultimoRegistroOrdenes);
    int opcion = 0;
    while (opcion != 7)
    {
        controlFactura();
        cin >> opcion;
        switch (opcion)
        {
        case 1:
            system("cls");
            generarFactura(1, registroOrdenes[0]);
            mostrarFactura(informacionFacturas[ultimoRegistroFacturas]);
            system("pause");
            break;
        case 2:
            cout << "Funcion no Implementada";
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
            modificarFactura();
            break;
        case 6:
            cout << "Regresando al menu principal..." << endl;
            system("pause");
            return;
            break;
        default:
            cout << "Seleccione una opcion valida. ";
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
            break;
        default:
            cout << "Ingresar opcion valida" << endl;
            break;
        }
    }
}
