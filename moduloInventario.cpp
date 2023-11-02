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

// CRUD
void ingresarProducto();
void guardarProductos(Producto productosAGuardar[]);
void mostrarProducto();
int calcularUltimoRegistro(const char* nombreArchivo);
void modificarProducto();
void modificarInventario();
void buscarProducto();
void eliminarProducto();

void ingresarProducto()
{
    if(ultimoRegistro < MAX){
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
    } else {
        cerr << "El inventario esta lleno, no se pueden agregar mas productos." << endl;
    }
}

int calcularUltimoRegistro(const char* nombreArchivo) {
    fstream archivo(nombreArchivo, ios::in | ios::binary);

    if (!archivo) {
        cerr << "No se pudo abrir el archivo." << endl;
        return -1;
    }

    size_t tamano_registro = sizeof(Producto);
    archivo.seekg(0, ios::end);
    streampos tamano_archivo = archivo.tellg();
    int ultimo_registro = tamano_archivo / tamano_registro;

    archivo.close();

    return ultimo_registro;
}

void mostrarRegistroInventario(Producto productosARecuperar[])
{
    ifstream archivo("inventario.txt");
    int i = 0; 

    if (archivo.is_open())
    {
        while (archivo >> productosARecuperar[i].codigoProducto)
        {
            archivo.ignore(); 
            getline(archivo, productosARecuperar[i].nombreProducto);
            archivo >> productosARecuperar[i].precioProducto;
            archivo >> productosARecuperar[i].cantidadProducto;

            cout << "Codigo: " << productosARecuperar[i].codigoProducto << endl;
            cout << "Nombre: " << productosARecuperar[i].nombreProducto << endl;
            cout << "Precio: " << productosARecuperar[i].precioProducto << endl;
            cout << "Cantidad: " << productosARecuperar[i].cantidadProducto << endl;
            cout << "------------------------------" << endl;

            i++; 
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