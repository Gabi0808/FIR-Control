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

void mostrarDatosBinarios(const string &nombreArchivo)
{
    ifstream archivo(nombreArchivo, ios::binary);
    if (archivo.is_open())
    {
        Producto producto;
        while (archivo.read(reinterpret_cast<char *>(&producto), sizeof(producto)))
        {
            cout << "Codigo: " << producto.codigoProducto << endl;
            cout << "Nombre: " << producto.nombreProducto << endl;
            cout << "Precio: " << producto.precioProducto << endl;
            cout << "Cantidad: " << producto.cantidadProducto << endl;
            cout << "------------------------------" << endl;
        }

        archivo.close();
    }
    else
    {
        cerr << "No se pudo abrir el archivo. " << endl;
    }
}

void mostrarRegistroInventario()
{
    ifstream archivo("inventario.bin", ios::binary);

    if (!archivo.is_open())
    {
        cerr << "No se pudo abrir el archivo." << endl;
        return;
    }

    Producto producto;

    while (archivo.read(reinterpret_cast<char *>(&producto), sizeof(Producto)))
    {
        cout << "Codigo: " << producto.codigoProducto << endl;
        cout << "Nombre: " << producto.nombreProducto << endl;
        cout << "Precio: " << producto.precioProducto << endl;
        cout << "Cantidad: " << producto.cantidadProducto << endl;
        cout << "------------------------------" << endl;
    }

    archivo.close();
}

void guardarProductos(Producto productosAGuardar[])
{
    ofstream archivo("inventario.bin", ios::binary);

    if (archivo.is_open())
    {
        for (int i = 0; i < ultimoRegistro; i++)
        {
            archivo.write(reinterpret_cast<char*>(&productosAGuardar[i]), sizeof(Producto));
        }

        archivo.close();

        cout << "El inventario se ha guardado en el archivo 'inventario.bin'." << endl;
    }
    else
    {
        cerr << "No se pudo abrir el archivo." << endl;
    }
}


int main(int argc, char const *argv[])
{
    ingresarProducto();
    guardarProductos(inventarioProducto);
    mostrarRegistroInventario();

    return 0;
}
