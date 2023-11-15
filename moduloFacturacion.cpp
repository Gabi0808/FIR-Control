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
        for (int j = mesaEncontrada; j < ultimoRegistroMesas - 1; j++)
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
        system("pause");
    }
}

void modificarMesa()
{
    int numeroMesa;
    cout << "Ingrese el numero de la mesa a modificar: " << endl;
    cin >> numeroMesa;

    int mesaEncontrada = -1;
    for (int i = 0; i < ultimoRegistroMesas; i++)
    {
        if (informacionMesas[i].numeroMesa == numeroMesa)
        {
            mesaEncontrada = i;
            break;
            ;
        }
    }
    if (mesaEncontrada != -1)
    {
        cout << "\nInformacion actual de la mesa: " << endl;
        mostrarInfoMesas(informacionMesas[mesaEncontrada], ordenesAbiertas[mesaEncontrada]);

        string nuevoEstado;
        cout << "\nIngrese el nuevo estado de la mesa: " << endl;
        cin >> nuevoEstado;

        informacionMesas[mesaEncontrada].estadoMesa = nuevoEstado;

        sobreescribirDatosMesa();

        cout << "El estado de la mesa " << numeroMesa << " se ha modificado exitosamente." << endl;
        system("pause");
    }
    else
    {
        cout << " No se encontro una mesa con el numero " << numeroMesa << endl;
        system("pause");
    }
}

void mostrarInfoMesas(Mesa mesaAMostrar, Orden ordenAMostrar)
{
    cout << "Numero de mesa: " << mesaAMostrar.numeroMesa << endl;
    cout << "Estado de la mesa: " << mesaAMostrar.estadoMesa << endl;
    mostrarOrden(ordenAMostrar);

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
            archivo << informacionMesas[i].estadoMesa << endl;
            archivo << informacionMesas[i].ordenActual.codigoOrden << endl;
        }
        archivo.close();
    }
    else
    {
        cerr << "No se pudo abrir el archivo para sobreescribir. " << endl;
        system("pause");
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
            getline(archivo, mesasARecuperar[cantidadRegistros].ordenActual.codigoOrden);

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

    int dia = tm->tm_mday;
    int mes = tm->tm_mon + 1;
    int anio = tm->tm_year + 1900;  


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
numeroMesa++;
    stringstream codigo;
    codigo << setfill('0') << setw(2) << numeroMesa;
    codigo << setfill('0') << setw(6) << fechaOrden;
    codigo << setfill('0') << setw(3) << ultimoRegistroOrdenes + 1;

    string codigoNumerico = codigo.str();

    return codigoNumerico;
}

void incializarOrden(int numeroMesa)
{

    ordenesAbiertas[numeroMesa].codigoOrden = construirCodigoOrden(numeroMesa, obtenerFechaHoy());
    ordenesAbiertas[numeroMesa].productoOrdenado[0].codigoProducto = "000000";
    ordenesAbiertas[numeroMesa].cantidadProductoOrdenado[0] = 0;
    ordenesAbiertas[numeroMesa].numeroProductosOrdenados = 0;
}

void agregarProductoOrden(int numeroMesa)
{

    Orden ordenActual;
    string codigoProductoIngresado;

    ordenActual.codigoOrden = construirCodigoOrden(numeroMesa, obtenerFechaHoy());
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
    ordenesAbiertas[numeroMesa] = ordenActual;
    cout << "Productos guardados con exito." << endl;
}

void eliminarProductoOrden(int numeroMesa, string codigoProductoAEliminar)
{

    for (int i = 0; i < ordenesAbiertas[numeroMesa].numeroProductosOrdenados; i++)
    {
        if (ordenesAbiertas[numeroMesa].productoOrdenado[i].codigoProducto == codigoProductoAEliminar)
        {
            ordenesAbiertas[numeroMesa].productoOrdenado[i].codigoProducto = ordenesAbiertas[numeroMesa].productoOrdenado[i + 1].codigoProducto;
            ordenesAbiertas[numeroMesa].cantidadProductoOrdenado[i] = ordenesAbiertas[numeroMesa].cantidadProductoOrdenado[i + 1];
            ordenesAbiertas[numeroMesa].numeroProductosOrdenados--;
            cout << "Producto eliminado con éxito." << endl;

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
        registrarSalidaProductos(ordenesAbiertas[numeroMesa]);
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
            resultadoBusqueda = buscarProducto(ordenAMostrar.productoOrdenado[i].codigoProducto);
            if (resultadoBusqueda != -1)
            {
                cout << "Nombre Producto " << i + 1 << ": " << inventarioProducto[resultadoBusqueda].nombreProducto << endl;
                cout << "Precio Producto " << i + 1 << ": " << inventarioProducto[resultadoBusqueda].precioProducto << endl;
                cout << "Cantidad Producto " << i + 1 << ": " << ordenAMostrar.cantidadProductoOrdenado[i] << endl;
            }
            else
            {
                cout << "No se encontro producto con ese codigo." << endl;
            }
        }
    }
    cout << "------------------------------------" << endl;
}

void registrarSalidaProductos(Orden ordenARegistrar)
{
    int resultadoBusqueda = -1;
    for (int i = 0; i < ordenARegistrar.numeroProductosOrdenados; i++)
    {
       resultadoBusqueda = buscarProducto(ordenARegistrar.productoOrdenado[i].codigoProducto);
       if (resultadoBusqueda != -1)
       {
            inventarioProducto[resultadoBusqueda].cantidadProducto -= ordenARegistrar.cantidadProductoOrdenado[i];
       }
       guardarProductos(inventarioProducto);
    }
}

string construirNumeroFactura(int tipoFactura, int &numeroUnico) {
    time_t now = time(nullptr);
    tm* timeinfo = localtime(&now);
    int year = timeinfo->tm_year % 100;

    string numeroFactura = "";

    if (year < 10) {
        numeroFactura += "0" + to_string(year);
    } else {
        numeroFactura += to_string(year);
    }

    if (tipoFactura == 1) {
        numeroFactura += "01";
    } else if (tipoFactura == 2) {
        numeroFactura += "02";
    } else {
        return "Tipo de factura no valido";
    }

    if (numeroUnico < 10) {
        numeroFactura += "0" + to_string(numeroUnico);
    } else if (numeroUnico >= 10 && numeroUnico < 100) {
        numeroFactura += to_string(numeroUnico);
    } else {
        return "Enumeración excede el límite";
    }

    numeroUnico++;

    return numeroFactura;
}

void generarFactura(int tipoFactura, int &numeroUnico){
    string factura = construirNumeroFactura(tipoFactura, numeroUnico);
    int fecha = obtenerFechaHoy();
    cout << "\t\t\t\tBAR BROTHER" << endl;
    cout << "Barrio Luis Delgadillo frente a la pista de aterrizaje Siuna, RACCN" << endl;
    cout << "RUC : 0011306740000X";
    cout << "\t\t\t\tTelefono 2794-2387" << endl;
    cout << "No. Factura " << factura << endl;
    cout << "Fecha: " << fecha << endl;

    cout << "Cantidad " << "\tDescripcion " << "\tPrecio" "\t\tTotal" << endl;

}