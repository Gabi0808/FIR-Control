#include "estructuras.hpp"

int extraerDiaFactura(string codigoFactura)
{
    int diaEmision;
    diaEmision = stoi(codigoFactura.substr(0, 2));

    return diaEmision;
}

int extraerMesFactura(string codigoFactura)
{
    int mesEmision;
    mesEmision = stoi(codigoFactura.substr(2, 4));

    return mesEmision;
}

int extraerAnioFactura(string codigoFactura)
{
    int anioEmision;
    anioEmision = stoi(codigoFactura.substr(4, 6));

    return anioEmision;
}

string construirFormatoFecha(int dia, int mes, int anio)
{

    stringstream fechaString;
    fechaString << setfill('0') << setw(2) << dia;
    fechaString << setfill('0') << setw(2) << mes;
    fechaString << setfill('0') << setw(2) << (anio % 100);
    return fechaString.str();
}

string obtenerFechaHoyComparar()
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

    return fechaString.str();
}

void generarReporteConsumoDiario()
{
    Reporte nuevoReporte;
    string substringAComparar;
    string substringFecha;
    string periodoTiempo[7];
    int ordenExtraida = 0;
    nuevoReporte.fechaReporte = obtenerFechaHoy();
    nuevoReporte.tipoReporte = 1;

    substringFecha = obtenerFechaHoyComparar();
    for (int i = 0; i < ultimoRegistroOrdenes; i++)
    {
        substringAComparar = registroOrdenes[i].codigoOrden.substr(2, 6);
        if (substringFecha == substringAComparar)
        {
            nuevoReporte.detalleReporte[ordenExtraida] = registroOrdenes[i].codigoOrden;
            extraerProductos(nuevoReporte.detalleReporte[ordenExtraida], productosEnReporte[ultimoRegistroReportes]);
            ordenExtraida++;
        }
    }
    nuevoReporte.periodoReporte = nuevoReporte.fechaReporte;
    reportesGenerados[ultimoRegistroReportes] = nuevoReporte;
    ultimoRegistroReportes++;
    ultimoRegistroProductosEnReporte++;
    cout << "Reporte generado con exito";
}

void generarReporteConsumoSemanal()
{

    Reporte nuevoReporte;
    string substringAComparar;
    string substringFecha;
    string periodoTiempo[7];
    int ordenExtraida, dia, mes, anio = 0;

    substringFecha = obtenerFechaHoyComparar();
    cout << substringFecha << endl;
    dia = stoi(substringFecha.substr(0, 2));
    mes = stoi(substringFecha.substr(2, 2));
    anio = stoi(substringFecha.substr(4, 2));
    periodoTiempo[6] = substringFecha;
    for (int i = 5; i >= 0; i--)
    {
        periodoTiempo[i] = determinarPeriodo(dia, mes, anio);
    }
    for (int k = 0; k < 7; k++)
    {
        substringFecha = periodoTiempo[k];
        cout << substringFecha << endl;
        system("pause");
        for (int j = 0; j < ultimoRegistroOrdenes; j++)
        {
            substringAComparar = registroOrdenes[j].codigoOrden.substr(2, 6);
            if (substringFecha == substringAComparar)
            {
                nuevoReporte.detalleReporte[ordenExtraida] = registroOrdenes[j].codigoOrden;
                extraerProductos(nuevoReporte.detalleReporte[ordenExtraida], productosEnReporte[ultimoRegistroReportes]);
                ordenExtraida++;
            }
        }
    }

    nuevoReporte.periodoReporte = periodoTiempo[0];
    reportesGenerados[ultimoRegistroReportes] = nuevoReporte;
    ultimoRegistroReportes++;
    ultimoRegistroProductosEnReporte++;
}

void generarReporteConsumoMes()
{

    Reporte nuevoReporte;
    string substringAComparar;
    string substringFecha;
    string mesString;
    int ordenExtraida = 0;

    mesString = obtenerFechaHoyComparar();
    substringFecha = mesString.substr(2, 2);

    for (int j = 0; j < ultimoRegistroOrdenes; j++)
    {
        substringAComparar = registroOrdenes[j].codigoOrden.substr(4, 2);
        if (substringFecha == substringAComparar)
        {
            nuevoReporte.detalleReporte[ordenExtraida] = registroOrdenes[j].codigoOrden;
            extraerProductos(nuevoReporte.detalleReporte[ordenExtraida], productosEnReporte[ultimoRegistroReportes]);
            ordenExtraida++;
        }
    }

    nuevoReporte.periodoReporte = substringFecha;
    reportesGenerados[ultimoRegistroReportes] = nuevoReporte;
    ultimoRegistroReportes++;
    ultimoRegistroProductosEnReporte++;
}

void extraerProductos(const string &ordenAExtraer, ProductosMovidos &productosACopiar)
{
    int resultadoBusquedaOrden = buscarOrden(ordenAExtraer);

    if (resultadoBusquedaOrden != -1)
    {
        if (productosACopiar.numeroProductosmovidos == 0)
        {
            productosACopiar.numeroProductosmovidos = registroOrdenes[resultadoBusquedaOrden].numeroProductosOrdenados;
            for (int i = 0; i < registroOrdenes[resultadoBusquedaOrden].numeroProductosOrdenados; i++)
            {
                productosACopiar.productosMovidos[i] = registroOrdenes[resultadoBusquedaOrden].productoOrdenado[i].codigoProducto;
                productosACopiar.cantidadProductosMovidos[i] = registroOrdenes[resultadoBusquedaOrden].cantidadProductoOrdenado[i];
            }
        }
        else
        {
            for (int k = 0; k < registroOrdenes[resultadoBusquedaOrden].numeroProductosOrdenados; k++)
            {
                bool encontrado = false;

                for (int j = 0; j < productosACopiar.numeroProductosmovidos; j++)
                {
                    if (productosACopiar.productosMovidos[j] == registroOrdenes[resultadoBusquedaOrden].productoOrdenado[k].codigoProducto)
                    {
                        productosACopiar.cantidadProductosMovidos[j] += registroOrdenes[resultadoBusquedaOrden].cantidadProductoOrdenado[k];
                        encontrado = true;
                        break;
                    }
                }

                if (!encontrado)
                {
                    productosACopiar.productosMovidos[productosACopiar.numeroProductosmovidos] = registroOrdenes[resultadoBusquedaOrden].productoOrdenado[k].codigoProducto;
                    productosACopiar.cantidadProductosMovidos[productosACopiar.numeroProductosmovidos] = registroOrdenes[resultadoBusquedaOrden].cantidadProductoOrdenado[k];
                    productosACopiar.numeroProductosmovidos++;
                }
            }
        }
    }
    else
    {
        cout << "No se encontro la orden." << endl;
    }
}

string determinarPeriodo(int &dia, int &mes, int &anio)
{
    string fecha;
    if (dia == 1)
    {
        if (mes == 1)
        {
            mes = 12;
            anio -= 1;
            dia = 31;
        }
        else
        {
            mes -= 1;
            if (mes == 4 || mes == 6 || mes == 9 || mes == 11)
            {
                dia = 30;
            }
            else if (mes == 2)
            {
                if ((anio % 4 == 0 && anio % 100 != 0) || anio % 400 == 0)
                {
                    dia = 29;
                }
                else
                {
                    dia = 28;
                }
            }
            else
            {
                dia = 31;
            }
        }
    }
    else
    {
        dia -= 1;
    }
    fecha = construirFormatoFecha(dia, mes, anio);
    return fecha;
}

void mostrarReporte(Reporte reporteAMostrar, ProductosMovidos productosReportados)
{
    int resultadoBusqueda = -1;
    cout << "Reporte generado en la fecha: " << reporteAMostrar.fechaReporte << endl;
    cout << "Reporte ";
    switch (reporteAMostrar.tipoReporte)
    {
    case 1:
        cout << "Diario " << endl;
        break;
    case 2:
        cout << "Semanal" << endl;
        break;
    case 3:
        cout << "Mensual" << endl;
        break;
    default:
        break;
    }
    cout << "Periodo de reporte: " << reporteAMostrar.periodoReporte << endl
         << endl;
    cout << "Se consumieron en total " << productosReportados.numeroProductosmovidos << " productos distintos" << endl
         << endl;
    cout << "Detalle de productos que fueron consumidos: " << endl
         << endl;
    cout << "Cantidad \tNombre del Producto \t\tPrecio" << endl;

    for (int i = 0; i < productosReportados.numeroProductosmovidos; i++)
    {
        resultadoBusqueda = buscarProducto(productosReportados.productosMovidos[i]);
        if (resultadoBusqueda != -1)
        {

            cout << productosReportados.cantidadProductosMovidos[i] << "\t" << inventarioProducto[resultadoBusqueda].nombreProducto << "\t\t" << inventarioProducto[resultadoBusqueda].precioProducto << endl;
        }
        else
        {
            cout << "No se encontro producto con ese codigo." << endl;
        }
    }
}