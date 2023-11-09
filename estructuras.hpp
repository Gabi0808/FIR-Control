#ifndef ESTRUCTURAS_HPP
#define ESTRUCTURAS_HPP

#include <iostream>
#include <string>
#include <fstream>
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
    Producto productoOrdenado[50];
    int cantidadProductoOrdenado[50];
    string observacionesOrden;
    string detalleOrden;
} Orden;

typedef struct
{
    int numeroMesa;
    string estadoMesa;
    Orden ordenActual;
} Mesa;

typedef struct
{
    Orden ordenCompleta;
    float subtotal;
    float impuestos;
    float descuentos;
    float total;
} Factura;

int ultimoRegistroMesas = 0;
Mesa informacionMesas[MAX];
Factura informacionFacturas[MAX];
// CRUD
void seleccionarMesa();
void mostrarInfoMesas(Mesa mesaAMostrar);
void agregarMesa();
void guardarMesa(Mesa mesaAGuardar[]);
void eliminarMesa();
void actualizarEstadoMesa();
void crearNuevaOrden();
void modificarOrden();
void cancelarOrden();
void sobreescribirDatosMesa();
void recuperarRegistroMesas(Mesa mesasARecuperar[], int &cantidadRegistros);

#endif