#ifndef ESTRUCTURAS_HPP
#define ESTRUCTURAS_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#define MAX 1000
#define RESET "\033[0m"
#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define BOLD "\033[1m"
#define UNDERLINE "\033[4m"

using namespace std;

typedef struct
{
    string codigoInsumo;
    string nombreInsumo;
    float precioInsumo;
    float cantidadInsumo;
    string unidadMedidaInsumo;
} Insumo;

typedef struct
{
    string codigoProducto;
    string nombreProducto;
    float precioProducto;
    int cantidadProducto;
    int numeroInsumosUsados;
    Insumo insumosNecesarios[20];
    float cantidadInsumosNecesarios[20];

} Producto;

int ultimoRegistro = 0;
int ultimoRegistroInsumos = 0;
Producto inventarioProducto[MAX];
Insumo inventarioInsumo[MAX];
string codigoInsumoABuscar;
string codigoInsumoARegistrar;
string codigoIngresado;
string codigoABuscar;
string codigoARegistrar;
Producto productoEncontrado;
Insumo insumoEncontrado;

// CRUD
void recuperarRegistroInsumos(Insumo insumosARecuperar[], int &cantidadRegistrosInsumos);
void ingresarInsumo();
void guardarInsumos(Insumo insumosAGuardar[]);
void mostrarInsumo(Insumo insumoAMostrar);
void modificarInsumo(string codigoABuscar);
void sobreescribirDatosInsumos();
int buscarInsumo(string codigoABuscar);
void eliminarInsumo(string codigoABuscar);
void registrarEntradaSalidaInsumo(string codigoARegistrar);
int calcularProductosDisponibles(Producto producto, Insumo inventarioInsumos[], int numInsumos);
void actualizarCantidadProductos();
void registrarEntradaInsumos(Producto ProductoARegistrar, int cantidadProductoOrdenado);

// CRUD
void recuperarRegistroInventario(Producto productosARecuperar[], int &cantidadRegistros);
void ingresarProducto();
void guardarProductos(Producto productosAGuardar[]);
void mostrarInventarioProductos(Producto productosAMostrar[]);
void mostrarProducto(Producto productoAMostrar);
void modificarProducto(string codigoABuscar);
void sobreescribirDatos();
int buscarProducto(string codigoABuscar);
void eliminarProducto(string codigoABuscar);
void registrarEntradaSalida(string codigoARegistrar);

typedef struct
{
    string codigoOrden;
    int numeroProductosOrdenados;
    Producto productoOrdenado[50];
    int cantidadProductoOrdenado[50];

} Orden;

typedef struct
{
    int numeroMesa;
    string estadoMesa;
    Orden ordenActual;
} Mesa;

typedef struct
{
    int tipoFactura;
    Orden ordenCompleta;
    string numeroFactura;
    float subtotal;
    float impuestos;
    float total;
} Factura;



int ultimoRegistroMesas = 0;
Mesa informacionMesas[MAX];
//COLORS
void imprimirMarco();
void imprimirMarcoVerde();

// CRUD
void seleccionarMesa();
void mostrarInfoMesas(Mesa mesaAMostrar, Orden ordenAMostrar);
void agregarMesa();
void guardarMesa(Mesa mesaAGuardar[]);
void eliminarMesa();
void modificarMesa();
void sobreescribirDatosMesa();
void recuperarRegistroMesas(Mesa mesasARecuperar[], int &cantidadRegistros);

void mostrarProductosALaPar(Producto productosAMostrar[]);
int obtenerFechaHoyInt();
string obtenerFechaHoy();
string construirCodigoOrden(int numeroMesa, int fechaOrden);
void inicializarOrden(int numeroMesa);
void agregarProductoOrden(int numeroMesa, Orden ordenActual);
void eliminarProductoOrden(int numeroMesa, string codigoProductoAEliminar);
void guardarOrden(Orden ordenesAGuardar[]);
void recuperarOrden(Orden ordenesARecuperar[], int &cantidadRegistroOrdenes);
void cerrarOrden(int numeroMesa);
void mostrarOrden(Orden ordenAMostrar);
void modificarOrden(string codigoAModificar);
void eliminarOrden(string codigoAEliminar);
void agregarOrden();
int buscarOrden(string codigoABuscar);
void registrarSalidaProductos(Orden ordenARegistrar);
void registrarSalidaInsumos(Producto productoARegistrar, int cantidadProductoOrdenado);
void mostrarInfoOrdenes(Orden ordenAMostrar[], int cantidadOrdenes);

int ultimoRegistroOrdenes = 0;
Orden ordenesAbiertas[50];
Orden registroOrdenes[MAX];

// Crud Facturacion
string construirCodigoFactura(int tipoFactura, int fechaFactura);
void generarFactura(int tipoFactura, Orden ordenDetallada);
float calcularSubtotal(Orden ordenDetallada);
float calcularImpuesto(float subtotal, int tipoFactura);
float calcularTotal(float impuestos, float subtotal);
void eliminarFactura();
int buscarFactura(string codigoABuscar);
void modificarFactura(string codigoAModificar);
void guardarFactura(Factura facturaAGuardar[]);
void sobreescribirDatosFactura();
void recuperarRegistroFactura(Factura facturasARecuperar[], int &cantidadRegistros);
void mostrarDetalleFactura(Orden ordenDetallada);
void mostrarInfoFacturas(Factura facturasAMostrar);

int ultimoRegistroFacturas = 0;
Factura informacionFacturas[MAX];

// CRUD Modulo generacion de reportes

typedef struct
{
    string fechaReporte;
    int tipoReporte;
    string periodoReporte;
    string detalleReporte[100];

} Reporte;

typedef struct
{
    int numeroProductosmovidos;
    string productosMovidos[100];
    int cantidadProductosMovidos[100];

} ProductosMovidos;

int ultimoRegistroReportes = 0;
int ultimoRegistroProductosEnReporte = 0;
Reporte reportesGenerados[MAX];
ProductosMovidos productosEnReporte[MAX];
string obtenerFechaHoyComparar();
int extraerDiaFactura(string codigoFactura);
int extraerMesFactura(string codigoFactura);
int extraerAnioFactura(string codigoFactura);
void generarReporteConsumoDiario();
void extraerProductos(const string &ordenAExtraer, ProductosMovidos &productosACopiar);
string determinarPeriodo(int &dia, int &mes, int &anio);
void mostrarReporte(Reporte reporteAMostrar);

#ifdef _WIN32 // Para Windows
#include <windows.h>
void gotoxy(short int x, short int y)
{
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
#elif __linux__ // Para Linux
#include <ncurses.h>
void gotoxy(int x, int y)
{
    move(y, x);
}
#else // Para otros sistemas operativos
void gotoxy(int x, int y)
{
    printf("\033[%d;%df", y, x);
}
#endif

#endif
