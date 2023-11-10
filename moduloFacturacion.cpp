#include "estructuras.hpp"
#include <iostream>

void agregarMesa()
{
    if (ultimoRegistroMesas < MAX)
    {
        Mesa nuevaMesa;
        cout << "\n\tNumero de mesa: ";
        cin >> nuevaMesa.numeroMesa;
        nuevaMesa.estadoMesa = "libre";
        nuevaMesa.ordenActual.codigoOrden = "No hay orden";
        nuevaMesa.ordenActual.numeroProductosOrdenados = 0;

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
    cout << "\nOrden actual: " << endl;
    cout << "Codigo de la orden: " << mesaAMostrar.ordenActual.codigoOrden << endl;
    cout << "Numero de productos ordenados: " << mesaAMostrar.ordenActual.numeroProductosOrdenados << endl;

    for (int i = 0; i < mesaAMostrar.ordenActual.numeroProductosOrdenados; i++)
    {
        cout << " Producto #" << i + 1 << ":" << endl;
        cout << "\tCodigo del producto: " << mesaAMostrar.ordenActual.productoOrdenado[i].codigoProducto << endl;
        cout << "\tNombre del producto: " << mesaAMostrar.ordenActual.productoOrdenado[i].nombreProducto << endl;
        cout << "\tPrecio del producto: $" << mesaAMostrar.ordenActual.productoOrdenado[i].precioProducto << endl;
        cout << "\tCantidad ordenada: " << mesaAMostrar.ordenActual.cantidadProductoOrdenado[i] << endl;
    }
}

void guardarMesa(Mesa mesaAGuardar[])
{
    ofstream archivo("mesas.txt", ios::trunc);
    if (archivo.is_open())
    {
        for (int i = 0; i < ultimoRegistroMesas; i++)
        {
            archivo << mesaAGuardar[i].numeroMesa << endl;
            archivo << mesaAGuardar[i].estadoMesa << endl;
            archivo << mesaAGuardar[i].ordenActual.codigoOrden << endl;
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
    codigo << std::setfill('0') << std::setw(3) << ultimoRegistroOrdenes + 1;

    string codigoNumerico = codigo.str();

    return codigoNumerico;
}

void incializarOrden(int numeroMesa)
{

    ordenesAbiertas[numeroMesa].codigoOrden = construirCodigoOrden(numeroMesa, obtenerFechaHoy());
    ordenesAbiertas[numeroMesa].productoOrdenado[0].codigoProducto = "000000";
    ordenesAbiertas[numeroMesa].cantidadProductoOrdenado[0] = 0;
    ordenesAbiertas[numeroMesa].numeroProductosOrdenados = 0;
    ultimoRegistroOrdenesAbiertas++;
}

void agregarProductoOrden(int numeroMesa)
{

    Orden ordenActual;
    string codigoProductoIngresado;

    ordenActual.numeroProductosOrdenados = 0;
    for (int i = 0; i < 50; i++)
    {
        cout << "Escriba 'salir' si termino de agregar productos a la orden." << endl;
        cout << "Ingrese el codigo del producto que desea agregar: ";
        cin >> codigoProductoIngresado;
        if (codigoProductoIngresado == "salir")
        {
            break;
        }
        ordenActual.productoOrdenado[i].codigoProducto = codigoProductoIngresado;
        cout << "Ingrese la cantidad de producto ordenado: ";
        cin >> ordenActual.cantidadProductoOrdenado[i];
        ordenesAbiertas[numeroMesa].productoOrdenado[i].codigoProducto = ordenActual.productoOrdenado[i].codigoProducto;
        ordenesAbiertas[numeroMesa].cantidadProductoOrdenado[i] = ordenActual.cantidadProductoOrdenado[i];
        ordenActual.numeroProductosOrdenados++;
    }
    cout << "Productos guardados con exito." << endl;
}

void eliminarProductoOrden(int numeroMesa, string codigoProductoAEliminar)
{

    for (int i = 0; i < 50; i++)
    {
        if (ordenesAbiertas[numeroMesa].productoOrdenado[i].codigoProducto == codigoProductoAEliminar)
        {
            ordenesAbiertas[numeroMesa].productoOrdenado[i].codigoProducto = "";
            ordenesAbiertas[numeroMesa].cantidadProductoOrdenado[i] = 0;
            cout << "Producto eliminado con éxito." << endl;

            // Reorganizamos el arreglo para eliminar lugares en blanco
            for (int j = i; j < ordenesAbiertas[numeroMesa].numeroProductosOrdenados; j++)
            {
                ordenesAbiertas[numeroMesa].productoOrdenado[j].codigoProducto = ordenesAbiertas[numeroMesa].productoOrdenado[j + 1].codigoProducto;
            }
            ordenesAbiertas[numeroMesa].productoOrdenado[ordenesAbiertas[numeroMesa].numeroProductosOrdenados - 1].codigoProducto = "";
            ordenesAbiertas[numeroMesa].cantidadProductoOrdenado[ordenesAbiertas[numeroMesa].numeroProductosOrdenados - 1] = 0;

            return;
        }
    }
}

void cerrarOrden(int numeroMesa)
{
    if (ordenesAbiertas[numeroMesa].numeroProductosOrdenados != 0)
    {
        registroOrdenes[ultimoRegistroOrdenes] = ordenesAbiertas[numeroMesa];
        ultimoRegistroOrdenes++;
        guardarOrden(registroOrdenes);
        incializarOrden(numeroMesa);
    }
    else
    {
        cout << "No puedes guardar una orden vacia." << endl;
    }
}

void guardarOrden(Orden ordenesAGuardar[])
{

    ofstream archivo("registroOrdenes.txt", ios::trunc);

    if (archivo.is_open())
    {
        for (int i = 0; i < ultimoRegistroOrdenes; i++)
        {
            archivo << ordenesAGuardar[i].codigoOrden << endl;
            archivo << ordenesAGuardar[i].numeroProductosOrdenados << endl;

            for (int j = 0; j < ordenesAGuardar[i].numeroProductosOrdenados; j++)
            {
                archivo << ordenesAGuardar[i].productoOrdenado[j].codigoProducto << " ";
            }
            archivo << endl;
            for (int k = 0; k < ordenesAGuardar[i].numeroProductosOrdenados; k++)
            {
                archivo << ordenesAGuardar[i].cantidadProductoOrdenado[k] << " ";
            }
            archivo << endl;
        }

        archivo.close();

        cout << "El inventario se ha guardado en el archivo 'inventario.txt'." << endl;
    }
    else
    {
        cerr << "No se pudo abrir el archivo." << endl;
    }
}

void recuperarOrden(Orden ordenesARecuperar[], int &cantidadRegistroOrdenes)
{
    ifstream archivo("registroOrdenes.txt");

    if (archivo.is_open())
    {
        while (archivo >> ordenesARecuperar[cantidadRegistroOrdenes].codigoOrden)
        {
            archivo.ignore();
            archivo >> ordenesARecuperar[cantidadRegistroOrdenes].numeroProductosOrdenados;
            for (int j = 0; j < ordenesARecuperar[cantidadRegistroOrdenes].numeroProductosOrdenados; j++)
            {
                archivo >> ordenesARecuperar[cantidadRegistroOrdenes].productoOrdenado[j].codigoProducto;
            }
            for (int k = 0; k < ordenesARecuperar[cantidadRegistroOrdenes].numeroProductosOrdenados; k++)
            {
                archivo >> ordenesARecuperar[cantidadRegistroOrdenes].cantidadProductoOrdenado[k];
            }
        }

        cantidadRegistroOrdenes++;

        archivo.close();
    }
    else
    {
        cerr << "No se pudo abrir el archivo." << endl;
    }
}

void mostrarOrden(Orden ordenAMostrar)
{
    int resultadoBusqueda = -1;
    cout << "Codigo orden: " << ordenAMostrar.codigoOrden << endl;
    if (ordenAMostrar.numeroProductosOrdenados != 0)
    {
        for (int i = 0; i < ordenAMostrar.numeroProductosOrdenados; i++)
        {
            cout << "Codigo Producto " << i + 1 << ": " << ordenAMostrar.productoOrdenado[i].codigoProducto << endl;
            resultadoBusqueda = buscarProducto(codigoABuscar);
            if (resultadoBusqueda != -1)
            {
                cout << "Nombre Producto " << i + 1 << ": " << inventarioProducto[resultadoBusqueda].nombreProducto;
                cout << "Precio Producto " << i + 1 << ": " << inventarioProducto[resultadoBusqueda].precioProducto;
                cout << "Cantidad Producto "<< i + 1 << ": "<< ordenAMostrar.cantidadProductoOrdenado[i];
            }
            else
            {
                cout << "No se encontro producto con ese codigo." << endl;
            }
           
        }
    }
}