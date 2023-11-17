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

int obtenerFechaHoyInt()
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

string obtenerFechaHoy()
{

    auto now = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);
    struct tm *tm = localtime(&currentTime);

    int dia = tm->tm_mday;
    int mes = tm->tm_mon + 1;
    int anio = tm->tm_year + 1900;

    stringstream fechaString;
    fechaString << setfill('0') << setw(2) << dia << '/';
    fechaString << setfill('0') << setw(2) << mes << '/';
    fechaString << setfill('0') << setw(2) << (anio % 100) << '/';

    return fechaString.str();
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

    ordenesAbiertas[numeroMesa].codigoOrden = construirCodigoOrden(numeroMesa, obtenerFechaHoyInt());
    ordenesAbiertas[numeroMesa].productoOrdenado[0].codigoProducto = "000000";
    ordenesAbiertas[numeroMesa].cantidadProductoOrdenado[0] = 0;
    ordenesAbiertas[numeroMesa].numeroProductosOrdenados = 0;
}

void agregarProductoOrden(int numeroMesa)
{

    Orden ordenActual;
    string codigoProductoIngresado;

    ordenActual.codigoOrden = construirCodigoOrden(numeroMesa, obtenerFechaHoyInt());
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
        system("pause");
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

int buscarOrden(string codigoABuscar)
{

    for (int i = 0; i < ultimoRegistroOrdenes; i++)
    {
        if (registroOrdenes[i].codigoOrden == codigoABuscar)
        {
            return i;
        }
    }
    return -1;
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

string construirCodigoFactura(int tipoFactura, int fechaFactura)
{

    stringstream codigo;
    codigo << setfill('0') << setw(6) << fechaFactura;
    codigo << setfill('0') << setw(2) << tipoFactura;
    codigo << setfill('0') << setw(3) << ultimoRegistroFacturas + 1;

    string codigoNumerico = codigo.str();

    return codigoNumerico;
}

float calcularSubtotal(Orden ordenDetallada)
{
    float subtotal = 0;
    int resultadoBusqueda = -1;
    for (int i = 0; i < ordenDetallada.numeroProductosOrdenados; i++)
    {
        resultadoBusqueda = buscarProducto(ordenDetallada.productoOrdenado[i].codigoProducto);
        if (resultadoBusqueda != -1)
        {
            subtotal += inventarioProducto[resultadoBusqueda].precioProducto * ordenDetallada.cantidadProductoOrdenado[i];
        }
        else
        {
            cout << "No se encontro producto con ese codigo." << endl;
        }
    }
    return subtotal;
}

float calcularImpuesto(float subtotal, int tipoFactura)
{
    float iva = 0;
    if (tipoFactura != 1)
    {
        iva = subtotal * 0.15;
        return iva;
    }

    return iva;
}

float calcularTotal(float impuestos, float subtotal)
{
    float total = 0;

    total = impuestos + subtotal;

    return total;
}

void generarFactura(int tipoFactura, Orden ordenDetallada)
{
    float subtotal = calcularSubtotal(ordenDetallada);
    float impuestos = calcularImpuesto(subtotal, tipoFactura);
    float total = calcularTotal(subtotal, impuestos);
    informacionFacturas[ultimoRegistroFacturas].tipoFactura = tipoFactura;
    informacionFacturas[ultimoRegistroFacturas].numeroFactura = construirCodigoFactura(tipoFactura, obtenerFechaHoyInt());
    informacionFacturas[ultimoRegistroFacturas].ordenCompleta.codigoOrden = ordenDetallada.codigoOrden;
    informacionFacturas[ultimoRegistroFacturas].subtotal = subtotal;
    informacionFacturas[ultimoRegistroFacturas].impuestos = impuestos;
    informacionFacturas[ultimoRegistroFacturas].total = total;

    ultimoRegistroFacturas++;
}

void mostrarFactura(Factura facturaAMostrar)
{
    int resultadoBusqueda = -1;
    string fecha = obtenerFechaHoy();
    cout << "\t\t\t\tBAR BROTHER" << endl;
    cout << "Barrio Luis Delgadillo frente a la pista de aterrizaje Siuna, RACCN" << endl;
    cout << "RUC : 0011306740000X";
    cout << "\t\t\t\tTelefono 2794-2387" << endl;
    cout << "No. Factura " << facturaAMostrar.numeroFactura << endl;
    cout << "Fecha: " << fecha << endl;
    resultadoBusqueda = buscarOrden(facturaAMostrar.ordenCompleta.codigoOrden);
    if (resultadoBusqueda != -1)
    {

        mostrarDetalleFactura(registroOrdenes[resultadoBusqueda]);

        cout << endl
             << "\t\t\tSubtotal: " << facturaAMostrar.subtotal << endl;
        cout << "\t\t\tImpuestos: " << facturaAMostrar.impuestos << endl;
        cout << "\t\t\tTotal: " << facturaAMostrar.total << endl;

        cout << "-----------------------------------------" << endl;
    }
    else
    {
        cout << "No se encontro orden con ese codigo." << endl;
    }
}

void mostrarDetalleFactura(Orden ordenDetallada)
{
    int resultadoBusqueda = -1;
    cout << "Detalle de la Factura: " << endl
         << endl;

    cout << "Cantidad \tNombre del Producto \t\tPrecio" << endl;

    for (int i = 0; i < ordenDetallada.numeroProductosOrdenados; i++)
    {
        resultadoBusqueda = buscarProducto(ordenDetallada.productoOrdenado[i].codigoProducto);
        if (resultadoBusqueda != -1)
        {

            cout << ordenDetallada.cantidadProductoOrdenado[i] << "\t" << inventarioProducto[resultadoBusqueda].nombreProducto << "\t\t" << inventarioProducto[resultadoBusqueda].precioProducto << endl;
        }
        else
        {
            cout << "No se encontro producto con ese codigo." << endl;
        }
    }
}

void guardarFactura(Factura facturaAGuardar[])
{
    ofstream archivo("facturas.txt", ios::trunc);
    if (archivo.is_open())
    {
        for (int i = 0; i < ultimoRegistroFacturas; i++)
        {
            archivo << facturaAGuardar[i].numeroFactura << endl;
            archivo << facturaAGuardar[i].ordenCompleta.codigoOrden << endl;
            archivo << facturaAGuardar[i].subtotal << endl;
            archivo << facturaAGuardar[i].impuestos << endl;
            archivo << facturaAGuardar[i].total << endl;
        }
        archivo.close();
    }
    else
    {
        cerr << "No se pudo abrir el archivo 'facturas.txt' " << endl;
        system("pause");
    }
}

void sobreescribirDatosFactura()
{
    ofstream archivo("facturas.txt", ios::trunc);
    if (archivo.is_open())
    {
        for (int i = 0; i < ultimoRegistroFacturas; i++)
        {
            archivo << informacionFacturas[i].numeroFactura << endl;
            archivo << informacionFacturas[i].ordenCompleta.codigoOrden << endl;
            archivo << informacionFacturas[i].subtotal << endl;
            archivo << informacionFacturas[i].impuestos << endl;
            archivo << informacionFacturas[i].total << endl;
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

void eliminarFactura()
{
    string facturaAEliminar;
    cout << "\nIngrese el numero de la factura a eliminar: ";
    cin >> facturaAEliminar;

    bool facturaEncontrada = false;
    int indiceFacturaEncontrada = -1;

    for (int i = 0; i < ultimoRegistroFacturas; i++)
    {
        if (informacionFacturas[i].numeroFactura == facturaAEliminar)
        {
            facturaEncontrada = true;
            indiceFacturaEncontrada = i;
            break;
        }
    }

    if (facturaEncontrada)
    {
        for (int j = indiceFacturaEncontrada; j < ultimoRegistroFacturas - 1; j++)
        {
            informacionFacturas[j] = informacionFacturas[j + 1];
        }
        ultimoRegistroFacturas--;

        sobreescribirDatosFactura();

        cout << "La factura " << facturaAEliminar << " ha sido eliminada exitosamente." << endl;
    }
    else
    {
        cout << "No se encontro una factura con el número " << facturaAEliminar << endl;
    }
}

void agregarFactura()
{
    int resultadoBusqueda = -1;

    if (ultimoRegistroFacturas < MAX)
    {
        Factura nuevaFactura;
        cout << "\n\tIngrese el tipo de factura: " << endl;
        cout << "\t1. Cliente cuota fija " << endl;
        cout << "\t2. Cliente " << endl;
        cout << "\t3. Proveedores " << endl;
        cin >> nuevaFactura.tipoFactura;

        if (nuevaFactura.tipoFactura == 1 || nuevaFactura.tipoFactura == 2)
        {
            cout << "Ingrese el codigo de la orden: ";
            cin >> nuevaFactura.ordenCompleta.codigoOrden;
            buscarOrden(nuevaFactura.ordenCompleta.codigoOrden);
            if (resultadoBusqueda != -1)
            {
                float subtotal = calcularSubtotal(registroOrdenes[resultadoBusqueda]);
                float impuestos = calcularImpuesto(subtotal, nuevaFactura.tipoFactura);
                float total = calcularTotal(subtotal, impuestos);
                nuevaFactura.subtotal = subtotal;
                nuevaFactura.impuestos = impuestos;
                nuevaFactura.total = total;
            }
        }
        else
        {
            cout << "Ingrese el subtotal de la factura: ";
            cin >> nuevaFactura.subtotal;

            cout << "Ingrese los impuestos: ";
            cin >> nuevaFactura.impuestos;
            nuevaFactura.total = nuevaFactura.subtotal + nuevaFactura.impuestos;
        }

        nuevaFactura.numeroFactura = construirCodigoFactura(nuevaFactura.tipoFactura, obtenerFechaHoyInt());

        informacionFacturas[ultimoRegistroFacturas] = nuevaFactura;
        ultimoRegistroFacturas++;

        cout << "La nueva factura se ha guardado en el archivo 'facturas.txt'." << endl;
        guardarFactura(informacionFacturas);
    }
    else
    {
        cerr << "No se pueden agregar más facturas." << endl;
        system("pause");
    }
}

void modificarFactura()
{
    string numeroFactura;
    cout << "Ingrese el numero de la factura a modificar: " << endl;
    cin >> numeroFactura;

    bool facturaEncontrada = false;
    int indiceFacturaEncontrada = -1;

    for (int i = 0; i < ultimoRegistroFacturas; i++)
    {
        if (informacionFacturas[i].numeroFactura == numeroFactura)
        {
            facturaEncontrada = true;
            indiceFacturaEncontrada = i;
            break;
        }
    }
    if (facturaEncontrada != -1)
    {
        cout << "\nInformacion actual de la factura: " << endl;
        mostrarInfoFacturas(informacionFacturas[facturaEncontrada]);

        float nuevoSubtotal;
        float nuevosImpuestos;
        float nuevoTotal;

        cout << "Ingrese el nuevo subtotal: " << endl;
        cin >> nuevoSubtotal;
        cout << "Ingrese los nuevos impuestos: " << endl;
        cin >> nuevosImpuestos;
        nuevoTotal = nuevoSubtotal + nuevosImpuestos;

        informacionFacturas[facturaEncontrada].subtotal = nuevoSubtotal;
        informacionFacturas[facturaEncontrada].impuestos = nuevosImpuestos;
        informacionFacturas[facturaEncontrada].total = nuevoTotal;

        sobreescribirDatosFactura();

        cout << "Los datos de la factura " << numeroFactura << " se han modificado exitosamente." << endl;
        system("pause");
    }
    else
    {
        cerr << "La factura no existe en el registro. No es posible realizar la operación solicitada." << endl;
        system("pause");
    }
}

void mostrarInfoFacturas(Factura facturaAMostrar)
{
    cout << "Numero de factura: " << facturaAMostrar.numeroFactura << endl;
    cout << "Subtotal: $" << facturaAMostrar.subtotal << endl;
    cout << "Impuestos: $" << facturaAMostrar.impuestos << endl;
    cout << "Total: $" << facturaAMostrar.total << endl;
}

void mostrarInfoOrdenes(Orden ordenAMostrar[], int cantidadOrdenes){
for (int i =0; i < cantidadOrdenes; i++){
    cout << "Orden # " << i+1 << ":" <<endl;
    mostrarOrden(ordenAMostrar[i]);
    cout<<endl;
}
}