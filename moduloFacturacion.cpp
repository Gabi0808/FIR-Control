#include "estructuras.hpp"
#include <iostream>

void agregarMesa()
{
    if (ultimoRegistro < MAX)
    {
        Mesa nuevaMesa;
        cout << "\n\tNumero de mesa: ";
        cin >> nuevaMesa.numeroMesa;
        informacionMesas[ultimoRegistro] = nuevaMesa;
        ultimoRegistro++;
        cout << " La nueva mesa se ha guardado en el archivo 'mesas.txt' ";
        guardarMesa(informacionMesas);
    }
    else
    {
        cerr << "No se pueden agregar mas mesas" << endl;
    }
}

void mostrarInfoMesas(Mesa mesaAMostrar){
cout << "Numero de mesa: " << mesaAMostrar.numeroMesa;
cout << "Estado de la mesa: " << mesaAMostrar.estadoMesa;
cout << "Orden actual: " << mesaAMostrar.ordenActual.detalleOrden;
}

void guardarMesa(Mesa mesaAGuardar[])
{
    ofstream archivo("mesas.txt", ios::app);
    if (archivo.is_open())
    {
        for (int i = 0; i < ultimoRegistro; i++)
        {
            archivo << mesaAGuardar[i].numeroMesa << endl;
            archivo.close();
        }
    }
    else
    {
        cerr << "No se pudo abrir el archivo 'mesas.txt'" << endl;
    }
}

void eliminarMesa()
{
    int mesaAEliminar = -1;
    cout << "\nIngrese el numero de la mesa a eliminar:";
    cin >> mesaAEliminar;

    if (mesaAEliminar != 1)
    {
        for (int i = mesaAEliminar; i < ultimoRegistro; i++)
        {
            informacionMesas[i] = informacionMesas[i + 1];
        }
        ultimoRegistro--;

        sobreescribirDatosMesa();
    }
    else
    {
        cout << "No se encontro una mesa con ese numero. ";
    }
}

void sobreescribirDatosMesa()
{
    ofstream archivo("mesas.txt", ios::trunc);
    if (archivo.is_open())
    {
        for (int i = 0; i < ultimoRegistro; i++)
        {
            archivo << informacionMesas[i].numeroMesa << endl;
        }
    }
    else
    {
        cerr << "No se pudo abrir el archivo para sobreescribir." << endl;
    }
    archivo.close();
}
