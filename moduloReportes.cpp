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

void generarReporteConsumo(int tipoReporte)
{
    Reporte nuevoReporte;
    string substringAComparar;
    string substringFecha;
    int ordenExtraida = 0;
    nuevoReporte.fechaReporte = obtenerFechaHoy();
    nuevoReporte.tipoReporte = tipoReporte;
    switch (tipoReporte)
    {
    case 1:
        substringFecha = obtenerFechaHoyComparar();
        for (int i = 0; i < ultimoRegistroOrdenes; i++)
        {
            substringAComparar = registroOrdenes[i].codigoOrden.substr(2, 6);
            if (substringFecha == substringAComparar)
            {
                nuevoReporte.detalleReporte[ordenExtraida] = registroOrdenes[i].codigoOrden;
                extraerProductosHoy(nuevoReporte.detalleReporte[ordenExtraida], productosEnReporte[ultimoRegistroReportes]);
                ordenExtraida++;
            }
        }
        nuevoReporte.periodoReporte = nuevoReporte.fechaReporte;
        reportesGenerados[ultimoRegistroReportes] = nuevoReporte;
        ultimoRegistroReportes++;
        ultimoRegistroProductosEnReporte++;
        break;
    case 2:
        break;
    case 3:
        break;
    default:
        break;
    }
}

void extraerProductosHoy(const string &ordenAExtraer, ProductosMovidos &productosACopiar)
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

void extraerProductoSemana()
{
}
void extraerProductoMes()
{
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