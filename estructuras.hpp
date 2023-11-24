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
int ultimoRegistroInsumos =0;
Producto inventarioProducto[MAX];
Insumo inventarioInsumo[MAX];
string codigoInsumoABuscar;
string codigoInsumoARegistrar;
string codigoIngresado;
string codigoABuscar;
string codigoARegistrar;
Producto productoEncontrado;
Insumo insumoEncontrado;

//CRUD
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

// CRUD
void recuperarRegistroInventario(Producto productosARecuperar[], int &cantidadRegistros);
void ingresarProducto();
void guardarProductos(Producto productosAGuardar[]);
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
// CRUD
void seleccionarMesa();
void mostrarInfoMesas(Mesa mesaAMostrar, Orden ordenAMostrar);
void agregarMesa();
void guardarMesa(Mesa mesaAGuardar[]);
void eliminarMesa();
void modificarMesa();
void actualizarEstadoMesa();
void sobreescribirDatosMesa();
void recuperarRegistroMesas(Mesa mesasARecuperar[], int &cantidadRegistros);

int obtenerFechaHoyInt();
string obtenerFechaHoy();
string construirCodigoOrden(int numeroMesa, int fechaOrden);
void incializarOrden(int numeroMesa);
void agregarProductoOrden(int numeroMesa);
void eliminarProductoOrden(int numeroMesa, string codigoProductoAEliminar);
void guardarOrden(Orden ordenesAGuardar[]);
void recuperarOrden(Orden ordenesARecuperar[], int &cantidadRegistroOrdenes);
void cerrarOrden(int numeroMesa);
void mostrarOrden(Orden ordenAMostrar);
void modificarOrden(Orden ordenAModificar);
void eliminarOrden(Orden ordenAEliminar);
void agregarOrden();
int buscarOrden(string codigoABuscar);
void registrarSalidaProductos(Orden ordenARegistrar);
void registrarSalidaInsumos(Producto productoARegistrar);
void mostrarInfoOrdenes(Orden ordenAMostrar);

int ultimoRegistroOrdenes = 0;
Orden ordenesAbiertas[50];
Orden registroOrdenes[MAX];

//Crud proveedores
int ultimoRegistroOrdenesProveedor = 0;
void guardarOrdenProveedor();
void agregarOrdenProveedor();
void mostrarInfoProveedores();


//Crud Facturacion
string construirCodigoFactura(int tipoFactura, int fechaFactura);
void generarFactura(int tipoFactura, Orden ordenDetallada);
float calcularSubtotal(Orden ordenDetallada);
float calcularImpuesto (float subtotal, int tipoFactura);
float calcularTotal(float impuestos, float subtotal);
void mostrarFacturas();
void eliminarFactura();
int buscarFactura(string codigoABuscar);
void modificarFactura(string codigoAModificar);
void guardarFactura(Factura facturaAGuardar[]);
void sobreescribirDatosFactura();
void recuperarRegistroFactura(Factura facturasARecuperar[], int &cantidadRegistros);
void mostrarDetalleFactura(Orden ordenDetallada);
void mostrarInfoFacturas();
void agregarOrdenFactura();
void mostrarRegistroFactura(Factura facturaAMostrar);

int ultimoRegistroFacturas = 0;
Factura informacionFacturas[MAX];

//CRUD Modulo generacion de reportes

typedef struct
{
    string fechaTransaccion;
    int tipoTransaccion;
    Factura detalleTransaccion;
} Transaccion;

int ultimoRegistroTransaccion = 0;
Transaccion registroTransacciones[MAX];
void generarReporteConsumo();
void generarReporteInventario();
void generarHistorialTransacciones();
void generarReporteControlFacturas();



#endif