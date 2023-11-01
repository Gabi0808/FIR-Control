#include <iostream>
#include <string>
#include <fstream>

using namespace std;

<<<<<<< HEAD

struct producto {
=======
typedef struct
{
>>>>>>> 4358ab8a12a474a39a74cebbc74609dc68e47c60
    string codigoProducto;
    string nombreProducto;
    float precioProducto;
    int cantidadProducto;
<<<<<<< HEAD
} Producto;
=======
<<<<<<< HEAD
};


void menuProducto() {
    system("cls");

    cout << "Menu de insumos." << endl;
    cout << "Codigo de insumo: " << endl;
    cout << "Nombre de insumo: " << endl;
    cout << "Precio del insumo: " << endl;
    cout << "Cantidad del insumo: " << endl;
}

void ingresarInsumo() {
    int codigo;
    string nombre;
    float precio;
    int cantidad;

    cout << "Ingrese el codigo de insumo: ";
    cin >> codigo;
    cin.ignore();
    cout << "Ingrese el nombre de insumo: ";
    getline(cin, nombre);
    cout << "Ingrese el precio del insumo: ";
    cin >> precio;
    cout << "Ingrese la cantidad del insumo: ";
    cin >> cantidad;
}

int main() {

   ingresarInsumo();

    return 0;
}
=======
} producto;
>>>>>>> d35b45735e405ec910c13eef1a0a082476101483

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
<<<<<<< HEAD



=======
>>>>>>> 4358ab8a12a474a39a74cebbc74609dc68e47c60
>>>>>>> d35b45735e405ec910c13eef1a0a082476101483
