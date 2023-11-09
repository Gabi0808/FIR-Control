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
        for (int j = mesaEncontrada + 1; j < ultimoRegistroMesas; j++)
        {
            informacionMesas[j] = informacionMesas[j + 1];
        }
        ultimoRegistroMesas--;

        sobreescribirDatosMesa();

        cout << "La mesa " << mesaAEliminar << " ha sido eliminada exitosamente. " << endl;
        system("pause");
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
        }
        archivo.close();
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

// CRUD ORDENES

int obtenerFechaHoy()
{
    auto now = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);
    struct tm *tm = localtime(&currentTime);

    // Extraer el día, mes y año
    int dia = tm->tm_mday;
    int mes = tm->tm_mon + 1;      // El mes se almacena de 0 a 11, por lo que sumamos 1
    int anio = tm->tm_year + 1900; // El año se almacena como el número de años desde 1900

    // Crear una cadena en formato DDMMAA
    stringstream fechaString;
    fechaString << setfill('0') << setw(2) << dia;
    fechaString << setfill('0') << setw(2) << mes;
    fechaString << setfill('0') << setw(2) << (anio % 100);

    string fechaStr = fechaString.str();
    int fechaInt = stoi(fechaStr);

    return fechaInt;
}

string construirCodigoOrden(int numeroMesa, int fechaOrden)
{

    // Crear una cadena (string) para el código numérico
    stringstream codigo;
    codigo << std::setfill('0') << std::setw(2) << numeroMesa;
    codigo << std::setfill('0') << std::setw(6) << fechaOrden;
    codigo << std::setfill('0') << std::setw(3) << ultimoRegistroOrdenesAbiertas + 1;

    string codigoNumerico = codigo.str();

    return codigoNumerico;
}

void abrirOrden(int numeroMesa)
{

    ordenesAbiertas[ultimoRegistroOrdenesAbiertas].codigoOrden = construirCodigoOrden(numeroMesa, obtenerFechaHoy());
    ordenesAbiertas[ultimoRegistroOrdenesAbiertas].productoOrdenado[0].codigoProducto = "000000";
    ordenesAbiertas[ultimoRegistroOrdenesAbiertas].cantidadProductoOrdenado[0] = 0;
    ordenesAbiertas[ultimoRegistroOrdenesAbiertas].observacionesOrden = " ";
    ordenesAbiertas[ultimoRegistroOrdenesAbiertas].detalleOrden = " ";

    ultimoRegistroOrdenesAbiertas++;
}

