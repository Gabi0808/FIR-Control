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
    fechaString << setfill('0') << setw(2) << (anio % 100);

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

void inicializarOrden(int numeroMesa)
{

    ordenesAbiertas[numeroMesa].codigoOrden = construirCodigoOrden(numeroMesa, obtenerFechaHoyInt());
    ordenesAbiertas[numeroMesa].productoOrdenado[0].codigoProducto = "000000";
    ordenesAbiertas[numeroMesa].cantidadProductoOrdenado[0] = 0;
    ordenesAbiertas[numeroMesa].numeroProductosOrdenados = 0;
}

void mostrarProductosALaPar(Producto productosAMostrar[])
{

    int distancia = 5; // Ajusta esta distancia según tus necesidades
    for (int i = 0; i < ultimoRegistro; i++)
    {
        gotoxy(60, (i * distancia) + 2);
        cout << "Codigo: " << productosAMostrar[i].codigoProducto << endl;
        gotoxy(60, (i * distancia) + 3);
        cout << "Nombre: " << productosAMostrar[i].nombreProducto << endl;
        gotoxy(60, (i * distancia) + 4);
        cout << "Precio: " << productosAMostrar[i].precioProducto << endl;
        gotoxy(60, (i * distancia) + 5);
        cout << "Cantidad: " << productosAMostrar[i].cantidadProducto << endl;
        gotoxy(60, (i * distancia) + 6);
        cout << "------------------------------" << endl;
    }
}

void agregarProductoOrden(int numeroMesa, Orden ordenActual)
{
    int cantidadOrdenada = 0;
    int resultadoBusqueda = -1;
    int distancia = 3;
    int valordei;
    string codigoProductoIngresado;
    mostrarProductosALaPar(inventarioProducto);
    if (ordenActual.numeroProductosOrdenados == 0)
    {
        ordenActual.codigoOrden = construirCodigoOrden(numeroMesa, obtenerFechaHoyInt());
        ordenActual.numeroProductosOrdenados = 0;
        for (int i = 0; i < 50; i++)
        {
            gotoxy(0, (i * distancia) + 8);
            cout << "Escriba '0' si termino de agregar productos a la orden." << endl;
            gotoxy(0, (i * distancia) + 9);
            cout << "Ingrese el codigo del producto que desea agregar: ";
            cin >> codigoProductoIngresado;
            if (codigoProductoIngresado == "0")
            {
                break;
            }
            ordenActual.productoOrdenado[i].codigoProducto = codigoProductoIngresado;
            gotoxy(0, (i * distancia) + 10);
            cout << "Ingrese la cantidad de producto ordenado: ";
            cin >> ordenActual.cantidadProductoOrdenado[i];
            ordenesAbiertas[numeroMesa].productoOrdenado[i].codigoProducto = ordenActual.productoOrdenado[i].codigoProducto;
            ordenesAbiertas[numeroMesa].cantidadProductoOrdenado[i] = ordenActual.cantidadProductoOrdenado[i];
            ordenActual.numeroProductosOrdenados++;
            valordei = i;
        }
        ordenesAbiertas[numeroMesa] = ordenActual;
        gotoxy(0, (valordei * distancia) + 11);
        cout << "Productos guardados con exito." << endl;
        gotoxy(0, (valordei * distancia) + 12);
        cout << "La mesa # " << numeroMesa + 1 << " ha sido marcada como ocupada. " << endl;
    }
    else
    {
        int contador = 0;
        for (int i = ordenActual.numeroProductosOrdenados; i < 50; i++)
        {
            resultadoBusqueda = -1;

            gotoxy(0, (contador * distancia) + 8);
            cout << "Escriba '0' si termino de agregar productos a la orden." << endl;
            gotoxy(0, (contador * distancia) + 9);
            cout << "Ingrese el codigo del producto que desea agregar: ";
            cin >> codigoProductoIngresado;
            if (codigoProductoIngresado == "0")
            {
                break;
            }
            else
            {
                for (int j = 0; j < ordenActual.numeroProductosOrdenados; j++)
                {
                    if (ordenActual.productoOrdenado[j].codigoProducto == codigoProductoIngresado)
                    {
                        resultadoBusqueda = j;
                        break;
                    }
                }
                if (resultadoBusqueda != -1)
                {
                    gotoxy(0, (contador * distancia) + 10);
                    cout << "Ingrese la cantidad de producto ordenado: ";
                    cin >> cantidadOrdenada;
                    ordenActual.cantidadProductoOrdenado[resultadoBusqueda] += cantidadOrdenada;
                    ordenesAbiertas[numeroMesa].cantidadProductoOrdenado[resultadoBusqueda] = ordenActual.cantidadProductoOrdenado[resultadoBusqueda];
                    i--;
                }
                else
                {
                    ordenActual.productoOrdenado[i].codigoProducto = codigoProductoIngresado;
                    gotoxy(0, (contador * distancia) + 10);
                    cout << "Ingrese la cantidad de producto ordenado: ";
                    cin >> ordenActual.cantidadProductoOrdenado[i];
                    ordenesAbiertas[numeroMesa].productoOrdenado[i].codigoProducto = ordenActual.productoOrdenado[i].codigoProducto;
                    ordenesAbiertas[numeroMesa].cantidadProductoOrdenado[i] = ordenActual.cantidadProductoOrdenado[i];
                    ordenActual.numeroProductosOrdenados++;
                }
            }
            contador++;
            valordei = contador;
        }
        ordenesAbiertas[numeroMesa] = ordenActual;
        gotoxy(0, (valordei * distancia) + 11);
        cout << "Productos guardados con exito." << endl;
    }
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
            cout << "Producto eliminado con exito." << endl;

            return;
        }
    }
}

void cerrarOrden(int numeroMesa)
{
    int resultadoBusqueda = -1;
    if (ordenesAbiertas[numeroMesa].numeroProductosOrdenados != 0)
    {
        for (int j = 0; j < ordenesAbiertas[numeroMesa].numeroProductosOrdenados; j++)
        {
            resultadoBusqueda = buscarProducto(ordenesAbiertas[numeroMesa].productoOrdenado[j].codigoProducto);
            if (resultadoBusqueda != -1)
            {
                if (inventarioProducto[resultadoBusqueda].cantidadProducto < ordenesAbiertas[numeroMesa].cantidadProductoOrdenado[j])
                {
                    cout << "No hay suficiente stock del producto " << ordenesAbiertas[numeroMesa].productoOrdenado[j].codigoProducto << ". Elimine el producto y vuelva a intentar." << endl;
                    system("pause");
                    return;
                }
            }
        }
        registroOrdenes[ultimoRegistroOrdenes] = ordenesAbiertas[numeroMesa];
        ultimoRegistroOrdenes++;
        registrarSalidaProductos(ordenesAbiertas[numeroMesa]);
        guardarOrden(registroOrdenes);
        inicializarOrden(numeroMesa);
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

        cout << "La orden se ha guardado en 'registroOrdenes.txt'." << endl;
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
            cantidadRegistroOrdenes++;
        }

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

void agregarOrden()
{
    Orden nuevaOrden;
    string codigoProductoIngresado;
    int numeroMesa;
    cout << "Ingrese el numero de mesa en que se sirvio la orden" << endl;
    cin >> numeroMesa;
    nuevaOrden.codigoOrden = construirCodigoOrden(numeroMesa, obtenerFechaHoyInt());
    nuevaOrden.numeroProductosOrdenados = 0;
    for (int i = 0; i < 50; i++)
    {
        cout << "Escriba 'salir' si termino de agregar productos a la orden." << endl;
        cout << "Ingrese el codigo del producto que desea agregar: ";
        cin >> codigoProductoIngresado;
        if (codigoProductoIngresado == "salir")
        {
            break;
        }
        nuevaOrden.productoOrdenado[i].codigoProducto = codigoProductoIngresado;
        cout << "Ingrese la cantidad de producto ordenado: ";
        cin >> nuevaOrden.cantidadProductoOrdenado[i];
        nuevaOrden.numeroProductosOrdenados++;
    }
    registroOrdenes[ultimoRegistroOrdenes] = nuevaOrden;
    ultimoRegistroOrdenes++;
    guardarOrden(registroOrdenes);
    cout << "Orden guardada con exito." << endl;
}

void modificarOrden(string codigoAModificar)
{
    string codigoProductoIngresado;
    int numeroMesa;
    int ordenAModificar = buscarOrden(codigoAModificar);
    if (ordenAModificar != -1)
    {
        cout << "Ingrese el numero de mesa en que se sirvio la orden" << endl;
        cin >> numeroMesa;
        registroOrdenes[ordenAModificar].codigoOrden = construirCodigoOrden(numeroMesa, obtenerFechaHoyInt());
        registroOrdenes[ordenAModificar].numeroProductosOrdenados = 0;
        for (int i = 0; i < 50; i++)
        {
            cout << "Escriba 'salir' si termino de agregar productos a la orden." << endl;
            cout << "Ingrese el codigo del producto que desea agregar: ";
            cin >> codigoProductoIngresado;
            if (codigoProductoIngresado == "salir")
            {
                break;
            }
            registroOrdenes[ordenAModificar].productoOrdenado[i].codigoProducto = codigoProductoIngresado;
            cout << "Ingrese la cantidad de producto ordenado: ";
            cin >> registroOrdenes[ordenAModificar].cantidadProductoOrdenado[i];
            registroOrdenes[ordenAModificar].numeroProductosOrdenados++;
        }
        guardarOrden(registroOrdenes);
        cout << "Orden modificada con exito." << endl;
    }
    else
    {

        cout << "No se encontro una orden con el codigo especificado. " << endl;
    }
}

void eliminarOrden(string codigoAEliminar)
{
    int ordenAEliminar = -1;
    ordenAEliminar = buscarOrden(codigoAEliminar);
    if (ordenAEliminar != -1)
    {
        for (int i = 0; i < ultimoRegistroOrdenes; i++)
        {
            registroOrdenes[i] = registroOrdenes[i + 1];
        }
        ultimoRegistroOrdenes--;
        guardarOrden(registroOrdenes);
    }
    else
    {
        cout << "No se encontro una orden con codigo especificado." << endl;
    }
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
            registrarSalidaInsumos(ordenARegistrar.productoOrdenado[i], ordenARegistrar.cantidadProductoOrdenado[i]);
        }
        sobreescribirDatos();
    }
}

void registrarSalidaInsumos(Producto productoARegistrar, int cantidadProductoOrdenado)
{
    int resultadoBusqueda = -1;
    for (int i = 0; i < productoARegistrar.numeroInsumosUsados; i++)
    {
        resultadoBusqueda = buscarInsumo(productoARegistrar.insumosNecesarios[i].codigoInsumo);
        if (resultadoBusqueda != -1)
        {
            inventarioInsumo[resultadoBusqueda].cantidadInsumo -= productoARegistrar.cantidadInsumosNecesarios[i] * cantidadProductoOrdenado;
        }
        sobreescribirDatosInsumos();
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
    gotoxy(15, 2);
    cout << "BAR BROTHER" << endl;
    gotoxy(5, 3);
    cout << "Barrio Luis Delgadillo frente a la pista de aterrizaje Siuna, RACCN" << endl;
    gotoxy(5, 4);
    cout << "RUC : 0011306740000X";
    gotoxy(30, 4);
    cout << "Telefono 2794-2387" << endl;
    gotoxy(5, 5);
    cout << "No. Factura " << facturaAMostrar.numeroFactura;
    gotoxy(30, 5);
    cout << "Numero de orden: " << facturaAMostrar.ordenCompleta.codigoOrden << endl;
    gotoxy(5, 6);
    cout << "Fecha: " << fecha << endl;
    resultadoBusqueda = buscarOrden(facturaAMostrar.ordenCompleta.codigoOrden);
    if (resultadoBusqueda != -1)
    {

        mostrarDetalleFactura(registroOrdenes[resultadoBusqueda]);
        gotoxy(5, 15);
        cout << "Subtotal: " << facturaAMostrar.subtotal << endl;
        gotoxy(5, 16);
        cout << "Impuestos: " << facturaAMostrar.impuestos << endl;
        gotoxy(5, 17);
        cout << "Total: " << facturaAMostrar.total << endl;
        gotoxy(5, 18);
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
    gotoxy(5, 7);
    cout << "Detalle de la Factura: " << endl
         << endl;
    gotoxy(5, 8);
    cout << "Cantidad";
    gotoxy(15, 8);
    cout << "Nombre del Producto ";
    gotoxy(40, 8);
    cout << "Precio" << endl;

    int ultimaPos = 9;
    for (int i = 0; i < ordenDetallada.numeroProductosOrdenados; i++)
    {
        resultadoBusqueda = buscarProducto(ordenDetallada.productoOrdenado[i].codigoProducto);
        if (resultadoBusqueda != -1)
        {
            gotoxy(5, ultimaPos);
            cout << ordenDetallada.cantidadProductoOrdenado[i];
            gotoxy(15, ultimaPos);
            cout <<inventarioProducto[resultadoBusqueda].nombreProducto;
            gotoxy(40, ultimaPos);
            cout << inventarioProducto[resultadoBusqueda].precioProducto << endl;
            ultimaPos++;
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
        cin >> nuevaFactura.tipoFactura;

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

int buscarFactura(string codigoABuscar)
{
    for (int i = 0; i < ultimoRegistroFacturas; i++)
    {
        if (informacionFacturas[i].numeroFactura == codigoABuscar)
        {
            return i;
        }
    }
    return -1;
}

void modificarFactura(string codigoAModificar)
{
    string numeroFactura;
    int facturaAModificar = -1;
    facturaAModificar = buscarFactura(codigoAModificar);

    if (facturaAModificar != -1)
    {
        cout << "\nInformacion actual de la factura: " << endl;
        mostrarFactura(informacionFacturas[facturaAModificar]);
        float nuevoSubtotal;
        float nuevosImpuestos;
        float nuevoTotal;

        cout << "Ingrese el nuevo subtotal: " << endl;
        cin >> nuevoSubtotal;
        cout << "Ingrese los nuevos impuestos: " << endl;
        cin >> nuevosImpuestos;
        nuevoTotal = nuevoSubtotal + nuevosImpuestos;

        informacionFacturas[facturaAModificar].subtotal = nuevoSubtotal;
        informacionFacturas[facturaAModificar].impuestos = nuevosImpuestos;
        informacionFacturas[facturaAModificar].total = nuevoTotal;

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

void mostrarInfoFacturas(Factura facturaAMostrar[])
{

    int ultimaPos = 2;
    for (int i = 0; i < ultimoRegistroFacturas; i++)
    {
        int resultadoBusqueda = -1;
        string fecha = obtenerFechaHoy();
        gotoxy(30, ultimaPos++);
        cout << "BAR BROTHER" << endl;
        gotoxy(5, ultimaPos++);
        cout << "Barrio Luis Delgadillo frente a la pista de aterrizaje Siuna, RACCN" << endl;
        gotoxy(5, ultimaPos++);
        cout << "RUC : 0011306740000X";
        gotoxy(30, ultimaPos);
        cout << "Telefono 2794-2387" << endl;
        gotoxy(5, ultimaPos++);
        cout << "No. Factura " << facturaAMostrar[i].numeroFactura;
        gotoxy(30, ultimaPos);
        cout << "Numero de orden: " << facturaAMostrar[i].ordenCompleta.codigoOrden << endl;
        gotoxy(5, ultimaPos++);
        cout << "Fecha: " << fecha << endl;
        resultadoBusqueda = buscarOrden(facturaAMostrar[i].ordenCompleta.codigoOrden);
        if (resultadoBusqueda != -1)
        {
            ultimaPos++;
            gotoxy(5, ultimaPos++);
            cout << "Detalle de la Factura: " << endl;
            ultimaPos++;
            gotoxy(5, ultimaPos);
            cout << "Cantidad";
            gotoxy(15, ultimaPos); 
            cout << "Nombre del Producto";
            gotoxy(40, ultimaPos);
            cout << "Precio";

            ultimaPos++;
            for (int i = 0; i < registroOrdenes[resultadoBusqueda].numeroProductosOrdenados; i++)
            {
                int resultadoBusquedaProducto = -1;
                resultadoBusquedaProducto = buscarProducto(registroOrdenes[resultadoBusqueda].productoOrdenado[i].codigoProducto);
                if (resultadoBusqueda != -1)
                {
                    gotoxy(5, ultimaPos);
                    cout << registroOrdenes[resultadoBusqueda].cantidadProductoOrdenado[i];
                    gotoxy(15, ultimaPos); 
                    cout << inventarioProducto[resultadoBusquedaProducto].nombreProducto;
                    gotoxy(40, ultimaPos);
                    cout << inventarioProducto[resultadoBusquedaProducto].precioProducto;
                    ultimaPos++;
                }
                else
                {
                    cout << "No se encontro producto con ese codigo." << endl;
                }
            }
            ultimaPos++;
            gotoxy(5, ultimaPos++);
            cout << "Subtotal: " << facturaAMostrar[i].subtotal << endl;
            gotoxy(5, ultimaPos++);
            cout << "Impuestos: " << facturaAMostrar[i].impuestos << endl;
            gotoxy(5, ultimaPos++);
            cout << "Total: " << facturaAMostrar[i].total << endl;
            gotoxy(5, ultimaPos++);
            cout << "-----------------------------------------" << endl;
        }
        else
        {
            cout << "No se encontro orden con ese codigo." << endl;
        }
    }
}

void mostrarInfoOrdenes(Orden ordenAMostrar[], int cantidadOrdenes)
{
    for (int i = 0; i < cantidadOrdenes; i++)
    {
        cout << "Orden # " << i + 1 << ":" << endl;
        mostrarOrden(ordenAMostrar[i]);
        cout << endl;
    }
}

void recuperarRegistroFactura(Factura facturasARecuperar[], int &cantidadRegistros)
{

    ifstream archivo("facturas.txt");

    if (archivo.is_open())
    {
        while (archivo >> facturasARecuperar[cantidadRegistros].numeroFactura)
        {
            archivo.ignore();
            archivo >> facturasARecuperar[cantidadRegistros].ordenCompleta.codigoOrden;
            archivo >> facturasARecuperar[cantidadRegistros].subtotal;
            archivo >> facturasARecuperar[cantidadRegistros].impuestos;
            archivo >> facturasARecuperar[cantidadRegistros].total;
            cantidadRegistros++;
        }

        archivo.close();
    }
    else
    {
        cerr << "No se pudo abrir el archivo." << endl;
    }
}