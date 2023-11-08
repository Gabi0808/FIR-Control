#include "estructuras.hpp"
#include <iostream>
void ingresarProducto()
{
    if (ultimoRegistro < MAX)
    {
        string codigoInsumoIngresado;
        Producto productoActual;

        cout << "Ingrese el codigo del producto: ";
        cin >> productoActual.codigoProducto;
        cin.ignore();
        cout << "Ingrese el nombre del producto: ";
        getline(cin, productoActual.nombreProducto);
        cout << "Ingrese el precio del producto: ";
        cin >> productoActual.precioProducto;
        cout << "Ingrese la cantidad del producto: ";
        cin >> productoActual.cantidadProducto;
        cout << "Ingrese los insumos que necesita el producto." << endl;
        cout << "Escriba 'salir' si no desea ingresar mas insumos" << endl;
        productoActual.numeroInsumosUsados = 0;
        for (; productoActual.numeroInsumosUsados < 20; productoActual.numeroInsumosUsados++)
        {
            cout << "Ingrese el codigo del insumo " << productoActual.numeroInsumosUsados + 1 << endl;
            cin >> codigoInsumoIngresado;
            if (codigoInsumoIngresado == "salir")
            {
                break;
            }
            productoActual.insumosNecesarios[productoActual.numeroInsumosUsados].codigoInsumo = codigoInsumoIngresado;
            cout << "Ingrese la cantidad necesaria de ese insumo" << endl;
            cin >> productoActual.cantidadInsumosNecesarios[productoActual.numeroInsumosUsados];
        }
        inventarioProducto[ultimoRegistro] = productoActual;
        ultimoRegistro++;
        cout << "El inventario se ha guardado en el archivo 'inventario.txt'." << endl;
        guardarProductos(inventarioProducto);
    }
    else
    {
        cerr << "El inventario esta lleno, no se pueden agregar mas productos." << endl;
    }
}

void recuperarRegistroInventario(Producto productosARecuperar[], int &cantidadRegistros)
{
    ifstream archivo("inventario.txt");

    if (archivo.is_open())
    {
        while (archivo >> productosARecuperar[cantidadRegistros].codigoProducto)
        {
            archivo.ignore();
            getline(archivo, productosARecuperar[cantidadRegistros].nombreProducto);
            archivo >> productosARecuperar[cantidadRegistros].precioProducto;
            archivo >> productosARecuperar[cantidadRegistros].cantidadProducto;

            // Leer el número de insumos usados
            archivo >> productosARecuperar[cantidadRegistros].numeroInsumosUsados;

            // Leer insumos y cantidades en función del número de insumos usados
            for (int j = 0; j < productosARecuperar[cantidadRegistros].numeroInsumosUsados; j++)
            {
                archivo >> productosARecuperar[cantidadRegistros].insumosNecesarios[j].codigoInsumo;
            }
            for (int k = 0; k < productosARecuperar[cantidadRegistros].numeroInsumosUsados; k++)
            {
                archivo >> productosARecuperar[cantidadRegistros].cantidadInsumosNecesarios[k];
            }

            cantidadRegistros++;
        }
        archivo.close();
    }
    else
    {
        cerr << "No se pudo abrir el archivo." << endl;
    }
}

void mostrarProducto(Producto productoAMostrar)
{

    cout << "Codigo: " << productoAMostrar.codigoProducto << endl;
    cout << "Nombre: " << productoAMostrar.nombreProducto << endl;
    cout << "Precio: " << productoAMostrar.precioProducto << endl;
    cout << "Cantidad: " << productoAMostrar.cantidadProducto << endl;
    if (productoAMostrar.numeroInsumosUsados != 0)
    {
        for (int i = 0; i < productoAMostrar.numeroInsumosUsados; i++)
        {
            cout << "Codigo Insumo " << i + 1 << ": " << productoAMostrar.insumosNecesarios[i].codigoInsumo << endl;
            cout << "Cantidad requerida de Insumo " << i + 1 << ": " << productoAMostrar.cantidadInsumosNecesarios[i] << endl;
        }
    }

    cout << "------------------------------" << endl;
}

void guardarProductos(Producto productosAGuardar[])
{
    ofstream archivo("inventario.txt", ios::app);

    if (archivo.is_open())
    {
        for (int i = 0; i < ultimoRegistro; i++)
        {
            archivo << productosAGuardar[i].codigoProducto << endl;
            archivo << productosAGuardar[i].nombreProducto << endl;
            archivo << productosAGuardar[i].precioProducto << endl;
            archivo << productosAGuardar[i].cantidadProducto << endl;
            archivo << productosAGuardar[i].numeroInsumosUsados << endl;
            if (productosAGuardar[i].numeroInsumosUsados != 0)
            {
                for (int j = 0; j < productosAGuardar[i].numeroInsumosUsados; j++)
                {

                    archivo << productosAGuardar[i].insumosNecesarios[j].codigoInsumo << " ";
                }
                archivo << endl;
                for (int k = 0; k < productosAGuardar[i].numeroInsumosUsados; k++)
                {
                    archivo << productosAGuardar[i].cantidadInsumosNecesarios[k] << " ";
                }
                archivo << endl;
            }
        }

        archivo.close();

        cout << "El inventario se ha guardado en el archivo 'inventario.txt'." << endl;
    }
    else
    {
        cerr << "No se pudo abrir el archivo." << endl;
    }
}

int buscarProducto(string codigoABuscar)
{

    for (int i = 0; i < ultimoRegistro; i++)
    {
        if (inventarioProducto[i].codigoProducto == codigoABuscar)
        {
            return i;
        }
    }
    return -1;
}

void sobreescribirDatos()
{

    ofstream archivo("inventario.txt", ios::trunc);
    if (archivo.is_open())
    {
        for (int i = 0; i < ultimoRegistro; i++)
        {
            archivo << inventarioProducto[i].codigoProducto << endl;
            archivo << inventarioProducto[i].nombreProducto << endl;
            archivo << inventarioProducto[i].precioProducto << endl;
            archivo << inventarioProducto[i].cantidadProducto << endl;
            if (inventarioProducto[i].numeroInsumosUsados != 0)
            {
                for (int j = 0; j < inventarioProducto[i].numeroInsumosUsados; j++)
                {

                    archivo << inventarioProducto[i].insumosNecesarios[j].codigoInsumo << " ";
                }
                archivo << endl;
                for (int k = 0; k < inventarioProducto[i].numeroInsumosUsados; k++)
                {
                    archivo << inventarioProducto[i].cantidadInsumosNecesarios[k] << " ";
                }
                archivo << endl;
            }
        }
    }
    else
    {
        cerr << "No se pudo abrir el archivo para sobrescribir." << endl;
    }
    archivo.close();
}
void eliminarProducto(string codigoABuscar)
{
    int codigoAEliminar = -1;
    codigoAEliminar = buscarProducto(codigoABuscar);

    if (codigoAEliminar != -1)
    {
        // Elimina el producto moviendo los elementos restantes
        for (int i = codigoAEliminar; i < ultimoRegistro - 1; i++)
        {
            inventarioProducto[i] = inventarioProducto[i + 1];
        }

        ultimoRegistro--;

        sobreescribirDatos();
    }
    else
    {
        cout << "No se encontró un producto con el código especificado." << endl;
    }
}

void modificarProducto(string codigoABuscar)
{
    int codigoAModificar = buscarProducto(codigoABuscar);

    if (codigoAModificar != -1)
    {
        mostrarProducto(inventarioProducto[codigoAModificar]);

        cout << "Ingrese los nuevos datos para el producto:" << endl;
        cout << "Ingrese el nuevo nombre: ";
        cin.ignore();
        getline(cin, inventarioProducto[codigoAModificar].nombreProducto);
        cout << "Ingrese el nuevo precio: ";
        cin >> inventarioProducto[codigoAModificar].precioProducto;
        cout << "Ingrese la nueva cantidad: ";
        cin >> inventarioProducto[codigoAModificar].cantidadProducto;

        sobreescribirDatos();
    }
    else
    {
        cout << "No se encontró un producto con el código especificado." << endl;
    }
}

void registrarEntradaSalida(string codigoARegistrar)
{
    int opcion = 0;
    int cantidadARegistrar = 0;
    int codigoAModificar = buscarProducto(codigoARegistrar);

    while (opcion != 3)
    {
        mostrarProducto(inventarioProducto[codigoAModificar]);
        cout << " 1. Registrar Entrada " << endl;
        cout << " 2. Registrar Salida " << endl;
        cout << " 3. Salir al menu." << endl;
        cout << " Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:

            cout << "Ingrese la cantidad de entrada (+) del producto ";
            cin >> cantidadARegistrar;
            inventarioProducto[codigoAModificar].cantidadProducto += cantidadARegistrar;

            sobreescribirDatos();
            cout << "Entrada registrada exitosamente." << endl;
            system("pause");

            break;
        case 2:
            cout << "Ingrese la cantidad de salida (-) del producto ";
            cin >> cantidadARegistrar;
            inventarioProducto[codigoAModificar].cantidadProducto -= cantidadARegistrar;

            sobreescribirDatos();
            break;
        case 3:
            cout << "Saliendo al menu..." << endl;
            break;
        default:

            break;
        }
    }
}
