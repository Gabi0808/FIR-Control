#include "estructuras.hpp"
#include <iostream>

void agregarMesa()
{
    if (ultimoRegistroMesas < MAX)
    {
        Mesa nuevaMesa;
        cout << "\n\tNumero de mesa: ";
        cin >> nuevaMesa.numeroMesa;
        informacionMesas[ultimoRegistroMesas] = nuevaMesa;
        ultimoRegistroMesas++;
        cout << " La nueva mesa se ha guardado en el archivo 'mesas.txt' ";
        guardarMesa(informacionMesas);
    }
    else
    {
        cerr << "No se pueden agregar mas mesas" << endl;
    }
}

void eliminarMesa()
{
    int mesaAEliminar = -1;
    cout << "\nIngrese el numero de la mesa a eliminar: ";
    cin >> mesaAEliminar;

    int mesaEncontrada = -1;
    for (int i = 0; i < ultimoRegistroMesas; i++)
    {
        if (informacionMesas[i].numeroMesa == mesaAEliminar)
        {
            mesaEncontrada = i;
            break;
        }
    }
    if (mesaEncontrada != -1)
    {
        for (int j = mesaEncontrada + 1; j < ultimoRegistroMesas; j++){
            informacionMesas[j] = informacionMesas[j+1];
        }
        ultimoRegistroMesas--;

        sobreescribirDatosMesa();

        cout << "La mesa " << mesaAEliminar << " ha sido eliminada exitosamente. " << endl;
        system ("pause");
        }
    else
    {
        cout << "No se encontro una mesa con el numero " << mesaAEliminar << endl;
    }
}
        
    

void mostrarInfoMesas(Mesa mesaAMostrar)
{
    cout << "Numero de mesa: " << mesaAMostrar.numeroMesa << endl;
    cout << "Estado de la mesa: " << mesaAMostrar.estadoMesa << endl;
    cout << "Orden actual: " << mesaAMostrar.ordenActual.detalleOrden << endl;
}

void guardarMesa(Mesa mesaAGuardar[])
{
    ofstream archivo("mesas.txt", ios::app);
    if (archivo.is_open())
    {
        for (int i = 0; i < ultimoRegistroMesas; i++)
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

void sobreescribirDatosMesa()
{
    ofstream archivo("mesas.txt", ios::trunc);
    if (archivo.is_open())
    {
        for (int i = 0; i < ultimoRegistroMesas; i++)
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

void recuperarRegistroMesas(Mesa mesasARecuperar[], int &cantidadRegistros)
{
    ifstream archivo("mesas.txt");

    if (archivo.is_open())
    {
        while (archivo >> mesasARecuperar[cantidadRegistros].numeroMesa)
        {
            archivo.ignore();
            getline(archivo, mesasARecuperar[cantidadRegistros].estadoMesa);
            archivo >> mesasARecuperar[cantidadRegistros].ordenActual.detalleOrden;

            cantidadRegistros++;
        }
        archivo.close();
    }
    else
    {
        cerr << "Error al abrir el archivo de las mesas" << endl;
    }
}
