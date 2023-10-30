#include <iostream>
#include <string>

using namespace std;


struct producto {
    string codigoProducto;
    string nombreProducto;
    float precioProducto;
    int cantidadProducto;
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
