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

//CRUD
void ingresarProducto();
void mostrarProducto();
void modificarProducto();
void modificarInventario();
void buscarProducto();
void eliminarProducto();

void ingresarProducto()
{
    Producto productoActual;
    for (int i = 0; i < 4; i++)
    {
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
    }
}

void mostrarRegistroInventario()
{
    ifstream archivo("inventario.txt");
    if (archivo.is_open())
    {
        Producto producto;

        while (getline(archivo, producto.codigoProducto) &&
               getline(archivo, producto.nombreProducto) &&
               archivo >> producto.precioProducto >> producto.cantidadProducto)
        {
            cout << "Codigo: " << producto.codigoProducto << endl;
            cout << "Nombre: " << producto.nombreProducto << endl;
            cout << "Precio: " << producto.precioProducto << endl;
            cout << "Cantidad: " << producto.cantidadProducto << endl;
            cout << "------------------------------" << endl;

            archivo.ignore();
        }

        archivo.close();
        system("pause");
    }
    else
    {
        cerr << "No se pudo abrir el archivo." << endl;
    }
}

void guardarProductos(Producto productosAGuardar[])
{
    ofstream archivo("inventario.txt");

    if (archivo.is_open())
    {
        for (int i = 0; i < ultimoRegistro; i++)
        {
            archivo << productosAGuardar[i].codigoProducto << endl;
            archivo << productosAGuardar[i].nombreProducto << endl;
            archivo << productosAGuardar[i].precioProducto << ' ' << productosAGuardar[i].cantidadProducto << endl;
        }

        archivo.close();

        cout << "El inventario se ha guardado en el archivo 'inventario.txt'." << endl;
    }
    else
    {
        cerr << "No se pudo abrir el archivo." << endl;
    }
}

void eliminarRegistro(string codigoProducto, Producto *productos, int &numProductos)
{
    bool encontrado = false;

    for (int i = 0; i < ultimoRegistro; i++)
    {
        if (inventarioProducto[i].codigoProducto == codigoProducto)
        {
            for (int j = i; j < numProductos - 1; j++)
            {
                productos[j] = productos[j + 1];
            }

            numProductos--;
            encontrado = true;
            break;
        }
    }
    if (encontrado)
    {
        cout << "Se elimino correctamente el producto con codigo: " << codigoProducto << endl;
    }
    else
    {
        cout << "No se encontro un producto con el codigo especificado." << endl;
    }
}