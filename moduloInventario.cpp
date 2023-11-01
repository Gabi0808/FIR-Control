#include <iostream>
#include <string>
#include <fstream>

using namespace std;

typedef struct
{
    string codigoProducto;
    string nombreProducto;
    float precioProducto;
    int cantidadProducto;
} Producto;

void mostrarDatosBinarios(const string &nombreArchivo)
{
    ifstream archivo(nombreArchivo, ios::binary);
    if (archivo.is_open())
    {
        Producto producto;
        while (archivo.read(reinterpret_cast< char *>(&producto), sizeof(producto)))
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

int main()
{
    Producto inventarioProductos[] = {
        {"081501", "Victoria Clasica Lata 355mL", 45.0, 100}};

    ofstream archivo("inventario.bin", ios::binary);

    if (archivo.is_open())
    {
        for (const Producto &producto : inventarioProductos)
        {
            archivo.write(reinterpret_cast<const char *>(&producto), sizeof(Producto));
        }

        archivo.close();

        cout << "El inventario se ha guardado en el archivo 'inventario.bin'." << endl;
    }
    else
    {
        cerr << "No se pudo abrir el archivo." << endl;
    }

    mostrarDatosBinarios("inventario.bin");

    return 0;
}



