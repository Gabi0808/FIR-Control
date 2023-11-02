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
    }

    // Calcula el tamaño del archivo para saber cuántos registros hay
    archivo.seekg(0, ios::end);
    int numRegistros = archivo.tellg() / sizeof(Producto);
    archivo.seekg(0, ios::beg);

    // Crea un arreglo para almacenar los registros
    Producto productos[numRegistros];

    // Lee los registros desde el archivo
    archivo.read(reinterpret_cast<char *>(productos), sizeof(productos));

    archivo.close();

    // Muestra los registros en pantalla
    for (int i = 0; i < numRegistros; i++)
    {
        cout << "Registro " << i + 1 << ":\n";
        cout << "Codigo: " << productos[i].codigoProducto << endl;
        cout << "Nombre: " << productos[i].nombreProducto << endl;
        cout << "Precio: " << productos[i].precioProducto << endl;
        cout << "Cantidad: " << productos[i].cantidadProducto << endl;
        // Muestra otros campos si los hay
        cout << endl;
    }
}

void guardarProductos(Producto productosAGuardar[])
{

    ofstream archivo("inventario.bin", ios::binary);

    if (archivo.is_open())
    {

        archivo.write(reinterpret_cast<const char *>(productosAGuardar), sizeof(Producto));

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
