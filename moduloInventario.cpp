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
} producto;

int main(){
producto inventarioProductos[] = {
    {"081501", "Victoria Clasica Lata 355mL", 45, 100}};

ofstream archivo("inventario.bin", ios::binary);

 if (archivo.is_open()) {
        for (const producto &producto : inventarioProductos) {
            archivo.write(reinterpret_cast<const char*>(&producto), sizeof(producto));
        }

        archivo.close();

        cout << "El inventario se ha guardado en el archivo 'inventario.bin'." << endl;
    } else {
        cerr << "No se pudo abrir el archivo." << endl;
    }

    return 0;
}