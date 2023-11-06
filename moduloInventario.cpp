#include <iostream>
#include <string>
#include <fstream>
#define MAX 1000
using namespace std;

typedef struct
{
    string codigoProducto;
    string nombreProducto;
    float precioProducto;
    int cantidadProducto;
} Producto;

int ultimoRegistro = 0;
Producto inventarioProducto[MAX];
string codigoIngresado;
// CRUD
void ingresarProducto();
void guardarProductos(Producto productosAGuardar[]);
void mostrarProducto(Producto productoAMostrar);
void modificarProducto(string codigoABuscar);
void sobreescribirDatos();
void modificarInventario();
int buscarProducto(string codigoABuscar);
void eliminarProducto(string codigoABuscar);
void registrarEntradaSalida();
string codigoABuscar;
string codigoARegistrar;
Producto productoEncontrado;

void ingresarProducto()
{
    if (ultimoRegistro < MAX)
    {
        Producto productoActual;

        cout << "Ingrese el codigo de insumo: ";
        cin >> productoActual.codigoProducto;
        cin.ignore();
        cout << "Ingrese el nombre de insumo: ";
        getline(cin, productoActual.nombreProducto);
        cout << "Ingrese el precio del insumo: ";
        cin >> productoActual.precioProducto;
        cout << "Ingrese la cantidad del insumo: ";
        cin >> productoActual.cantidadProducto;
        inventarioProducto[ultimoRegistro] = productoActual;
        ultimoRegistro++;
        cout << "El inventario se ha guardado en el archivo 'inventario.txt'." << endl;
        guardarProductos(inventarioProducto);
    }
    else
    {
        cerr << "El inventario esta lleno, no se pueden agregar mas productos." << endl;
    }
}

void recuperarRegistroInventario(Producto productosARecuperar[], int &cantidadRegistros)
{

    ifstream archivo("inventario.txt");

    if (archivo.is_open())
    {
        while (archivo >> productosARecuperar[cantidadRegistros].codigoProducto)
        {
            archivo.ignore();
            getline(archivo, productosARecuperar[cantidadRegistros].nombreProducto);
            archivo >> productosARecuperar[cantidadRegistros].precioProducto;
            archivo >> productosARecuperar[cantidadRegistros].cantidadProducto;

            cantidadRegistros++;
        }
        archivo.close();
    }

    else
    {
        cerr << "No se pudo abrir el archivo." << endl;
    }
}

void mostrarProducto(Producto productoAMostrar)
{

    cout << "Codigo: " << productoAMostrar.codigoProducto << endl;
    cout << "Nombre: " << productoAMostrar.nombreProducto << endl;
    cout << "Precio: " << productoAMostrar.precioProducto << endl;
    cout << "Cantidad: " << productoAMostrar.cantidadProducto << endl;
    cout << "------------------------------" << endl;

    system("pause");
}

void guardarProductos(Producto productosAGuardar[])
{
    ofstream archivo("inventario.txt", ios::app);

    if (archivo.is_open())
    {
        for (int i = 0; i < ultimoRegistro; i++)
        {
            archivo << productosAGuardar[i].codigoProducto << endl;
            archivo << productosAGuardar[i].nombreProducto << endl;
            archivo << productosAGuardar[i].precioProducto << endl;
            archivo << productosAGuardar[i].cantidadProducto << endl;
        }

        archivo.close();

        cout << "El inventario se ha guardado en el archivo 'inventario.txt'." << endl;
    }
    else
    {
        cerr << "No se pudo abrir el archivo." << endl;
    }
}

int buscarProducto(string codigoABuscar)
{

    for (int i = 0; i < ultimoRegistro; i++)
    {
        if (inventarioProducto[i].codigoProducto == codigoABuscar)
        {
            return i;
        }
    }
    return -1;
}

void sobreescribirDatos()
{

    ofstream archivo("inventario.txt", ios::trunc);
    if (archivo.is_open())
    {
        for (int i = 0; i < ultimoRegistro; i++)
        {
            archivo << inventarioProducto[i].codigoProducto << endl;
            archivo << inventarioProducto[i].nombreProducto << endl;
            archivo << inventarioProducto[i].precioProducto << endl;
            archivo << inventarioProducto[i].cantidadProducto << endl;
        }
    }
    else
    {
        cerr << "No se pudo abrir el archivo para sobrescribir." << endl;
    }
    archivo.close();
}
void eliminarProducto(string codigoABuscar)
{
    int codigoAEliminar = -1;
    codigoAEliminar = buscarProducto(codigoABuscar);

    if (codigoAEliminar != -1)
    {
        // Elimina el producto moviendo los elementos restantes
        for (int i = codigoAEliminar; i < ultimoRegistro - 1; i++)
        {
            inventarioProducto[i] = inventarioProducto[i + 1];
        }

        ultimoRegistro--;

        sobreescribirDatos();
    }
    else
    {
        cout << "No se encontró un producto con el código especificado." << endl;
    }
}

void modificarProducto(string codigoABuscar)
{
    int codigoAModificar = buscarProducto(codigoABuscar);

    if (codigoAModificar != -1)
    {
        mostrarProducto(inventarioProducto[codigoAModificar]);

        cout << "Ingrese los nuevos datos para el producto:" << endl;
        cout << "Ingrese el nuevo nombre: ";
        cin.ignore();
        getline(cin, inventarioProducto[codigoAModificar].nombreProducto);
        cout << "Ingrese el nuevo precio: ";
        cin >> inventarioProducto[codigoAModificar].precioProducto;
        cout << "Ingrese la nueva cantidad: ";
        cin >> inventarioProducto[codigoAModificar].cantidadProducto;

        sobreescribirDatos();
    }
    else
    {
        cout << "No se encontró un producto con el código especificado." << endl;
    }
}

void registrarEntradaSalida(string codigoARegistrar)
{
    int opcion = 0;
    int cantidadARegistrar = 0;
    int codigoAModificar = buscarProducto(codigoARegistrar);

    while (opcion != 3)
    {
        mostrarProducto(inventarioProducto[codigoAModificar]);
        cout << " 1. Registrar Entrada " << endl;
        cout << " 2. Registrar Salida " << endl;
        cout << " 3. Salir al menu." << endl;
        cout << " Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:

            cout << "Ingrese la cantidad de entrada (+) del producto ";
            cin >> cantidadARegistrar;
            inventarioProducto[codigoAModificar].cantidadProducto += cantidadARegistrar;

            sobreescribirDatos();
            cout << "Entrada registrada exitosamente." << endl;
            system("pause");

            break;
        case 2:
            cout << "Ingrese la cantidad de salida (-) del producto ";
            cin >> cantidadARegistrar;
            inventarioProducto[codigoAModificar].cantidadProducto -= cantidadARegistrar;

            sobreescribirDatos();
            break;
        case 3:
            cout << "Saliendo al menu..." << endl;
            break;
        default:

            break;
        }
    }
}
