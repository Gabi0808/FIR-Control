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
        if (productoActual.numeroInsumosUsados != 0)
        {
            int cantidadPosible = calcularProductosDisponibles(productoActual, inventarioInsumo, ultimoRegistroInsumos);
            productoActual.cantidadProducto = cantidadPosible;
            cout << "Se pueden elaborar " << cantidadPosible << " productos de " << productoActual.nombreProducto << endl;
            system("pause");
        }
        else
        {
            productoActual.insumosNecesarios[0].codigoInsumo = "N/A";
            productoActual.cantidadInsumosNecesarios[0] = 0;
            cout << "Ingrese la cantidad del producto: ";
            cin >> productoActual.cantidadProducto;
        }

        inventarioProducto[ultimoRegistro] = productoActual;
        ultimoRegistro++;
        cout << "El inventario se ha guardado en el archivo 'inventario.txt'." << endl;
        system("pause");
        guardarProductos(inventarioProducto);
    }
    else
    {
        cerr << "El inventario esta lleno, no se pueden agregar mas productos." << endl;
        system("pause");
    }
}

int calcularProductosDisponibles(Producto producto, Insumo inventarioInsumos[], int numInsumos)
{
    int cantidadMinima = INT_MAX;

    for (int i = 0; i < producto.numeroInsumosUsados; i++)
    {
        string codigoInsumoRequerido = producto.insumosNecesarios[i].codigoInsumo;
        float cantidadRequerida = producto.cantidadInsumosNecesarios[i];
        bool insumoEncontrado = false;

        for (int j = 0; j < numInsumos; j++)
        {
            if (codigoInsumoRequerido == inventarioInsumos[j].codigoInsumo)
            {
                float cantidadDisponible = inventarioInsumos[j].cantidadInsumo;
                int cantidadProductosPosibles = cantidadDisponible / cantidadRequerida;

                if (cantidadProductosPosibles < cantidadMinima)
                {
                    cantidadMinima = cantidadProductosPosibles;
                }

                insumoEncontrado = true;
                break;
            }
        }

        if (!insumoEncontrado)
        {
            // No se encontró el insumo en el inventario, por lo que no se pueden hacer productos.
            return 0;
        }
    }

    return cantidadMinima;
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
            if (productosARecuperar[cantidadRegistros].numeroInsumosUsados != 0)
            {
                // Leer insumos y cantidades en función del número de insumos usados
                for (int j = 0; j < productosARecuperar[cantidadRegistros].numeroInsumosUsados; j++)
                {
                    archivo >> productosARecuperar[cantidadRegistros].insumosNecesarios[j].codigoInsumo;
                }
                for (int k = 0; k < productosARecuperar[cantidadRegistros].numeroInsumosUsados; k++)
                {
                    archivo >> productosARecuperar[cantidadRegistros].cantidadInsumosNecesarios[k];
                }
            }
            else
            {
                archivo >> productosARecuperar[cantidadRegistros].insumosNecesarios[0].codigoInsumo;
                archivo >> productosARecuperar[cantidadRegistros].cantidadInsumosNecesarios[0];
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

void mostrarInventarioProductos(Producto productosAMostrar[])
{
    int ultimaPos = 2;
    for (int i = 0; i < ultimoRegistro; i++)
    {

        gotoxy(5, ultimaPos++);
        cout << "Codigo: " << productosAMostrar[i].codigoProducto << endl;

        gotoxy(5, ultimaPos++);
        cout << "Nombre: " << productosAMostrar[i].nombreProducto << endl;

        gotoxy(5, ultimaPos++);
        cout << "Precio: " << productosAMostrar[i].precioProducto << endl;

        gotoxy(5, ultimaPos++);
        cout << "Cantidad: " << productosAMostrar[i].cantidadProducto << endl;

        if (productosAMostrar[i].numeroInsumosUsados != 0)
        {

            for (int j = 0; j < productosAMostrar[i].numeroInsumosUsados; j++)
            {
                gotoxy(5, ultimaPos++);
                cout << "Codigo Insumo " << j + 1 << ": " << productosAMostrar[i].insumosNecesarios[j].codigoInsumo << endl;

                gotoxy(5, ultimaPos++);
                cout << "Cantidad requerida de Insumo " << j + 1 << ": " << productosAMostrar[i].cantidadInsumosNecesarios[j] << endl;
            }
        }

        gotoxy(5, ultimaPos++);
        cout << "------------------------------" << endl;
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
        cout << "------------------------------" << endl;
    }
}

void guardarProductos(Producto productosAGuardar[])
{
    ofstream archivo("inventario.txt", ios::trunc);

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
            else
            {
                archivo << productosAGuardar[i].insumosNecesarios[0].codigoInsumo << endl;
                archivo << productosAGuardar[i].cantidadInsumosNecesarios[0] << endl;
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
            archivo << inventarioProducto[i].numeroInsumosUsados << endl;
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
            else
            {
                archivo << inventarioProducto[i].insumosNecesarios[0].codigoInsumo << endl;
                archivo << inventarioProducto[i].cantidadInsumosNecesarios[0] << endl;
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
        cout << "No se encontro un producto con el código especificado." << endl;
    }
}

void modificarProducto(string codigoABuscar)
{
    string codigoInsumoIngresado;
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
        cout << "Ingrese los insumos que necesita el producto." << endl;
        cout << "Escriba 'salir' si no desea ingresar mas insumos" << endl;
        inventarioProducto[codigoAModificar].numeroInsumosUsados = 0;
        for (; inventarioProducto[codigoAModificar].numeroInsumosUsados < 20; inventarioProducto[codigoAModificar].numeroInsumosUsados++)
        {
            cout << "Ingrese el codigo del insumo " << inventarioProducto[codigoAModificar].numeroInsumosUsados + 1 << endl;
            cin >> codigoInsumoIngresado;
            if (codigoInsumoIngresado == "salir")
            {
                break;
            }
            inventarioProducto[codigoAModificar].insumosNecesarios[inventarioProducto[codigoAModificar].numeroInsumosUsados].codigoInsumo = codigoInsumoIngresado;
            cout << "Ingrese la cantidad necesaria de ese insumo" << endl;
            cin >> inventarioProducto[codigoAModificar].cantidadInsumosNecesarios[inventarioProducto[codigoAModificar].numeroInsumosUsados];
        }
        if (inventarioProducto[codigoAModificar].numeroInsumosUsados != 0)
        {
            int cantidadPosible = calcularProductosDisponibles(inventarioProducto[codigoAModificar], inventarioInsumo, ultimoRegistroInsumos);
            inventarioProducto[codigoAModificar].cantidadProducto = cantidadPosible;
            cout << "Se pueden elaborar " << cantidadPosible << " productos de " << inventarioProducto[codigoAModificar].nombreProducto << endl;
            system("pause");
        }
        else
        {
            inventarioProducto[codigoAModificar].insumosNecesarios[0].codigoInsumo = "N/A";
            inventarioProducto[codigoAModificar].cantidadInsumosNecesarios[0] = 0;
            cout << "Ingrese la cantidad del producto: ";
            cin >> inventarioProducto[codigoAModificar].cantidadProducto;
        }

        sobreescribirDatos();
    }
    else
    {
        cout << "No se encontró un producto con el código especificado." << endl;
    }
}

void actualizarCantidadProductos()
{

    for (int i = 0; i < ultimoRegistro; i++)
    {
        if (inventarioProducto[i].numeroInsumosUsados != 0)
        {
            inventarioProducto[i].cantidadProducto = calcularProductosDisponibles(inventarioProducto[i], inventarioInsumo, ultimoRegistroInsumos);
        }
    }
    sobreescribirDatos();
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
            registrarEntradaInsumos(inventarioProducto[codigoAModificar], cantidadARegistrar);

            sobreescribirDatos();
            cout << "Entrada registrada exitosamente." << endl;
            system("pause");

            break;
        case 2:
            cout << "Ingrese la cantidad de salida (-) del producto ";
            cin >> cantidadARegistrar;
            inventarioProducto[codigoAModificar].cantidadProducto -= cantidadARegistrar;
            registrarSalidaInsumos(inventarioProducto[codigoAModificar], cantidadARegistrar);

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

void recuperarRegistroInsumos(Insumo insumosARecuperar[], int &cantidadRegistrosInsumos)
{

    {
        ifstream archivo("inventarioInsumos.txt");

        if (archivo.is_open())
        {
            while (archivo >> insumosARecuperar[cantidadRegistrosInsumos].codigoInsumo)
            {
                archivo.ignore();
                getline(archivo, insumosARecuperar[cantidadRegistrosInsumos].nombreInsumo);
                archivo >> insumosARecuperar[cantidadRegistrosInsumos].precioInsumo;
                archivo >> insumosARecuperar[cantidadRegistrosInsumos].cantidadInsumo;
                archivo >> insumosARecuperar[cantidadRegistrosInsumos].unidadMedidaInsumo;

                cantidadRegistrosInsumos++;
            }
            archivo.close();
        }
        else
        {
            cerr << "No se pudo abrir el archivo." << endl;
        }
    }
}

void ingresarInsumo()
{
    if (ultimoRegistroInsumos < MAX)
    {
        Insumo insumoActual;

        cout << "Ingrese el codigo del insumo: ";
        cin >> insumoActual.codigoInsumo;
        cin.ignore();
        cout << "Ingrese el nombre del insumo: ";
        getline(cin, insumoActual.nombreInsumo);
        cout << "Ingrese el precio del producto: ";
        cin >> insumoActual.precioInsumo;
        cout << "Ingrese la cantidad del producto: ";
        cin >> insumoActual.cantidadInsumo;
        cout << "Ingrese la unidad de medida del insumo: ";
        cin >> insumoActual.unidadMedidaInsumo;
        inventarioInsumo[ultimoRegistroInsumos] = insumoActual;
        ultimoRegistroInsumos++;
        cout << "El inventario de insumos se ha guardado en el archivo 'inventarioInsumos.txt'." << endl;
        guardarInsumos(inventarioInsumo);
        system("pause");
    }
    else
    {
        cerr << "El inventario esta lleno, no se pueden agregar mas productos." << endl;
    }
}
void guardarInsumos(Insumo insumosAGuardar[])
{
    ofstream archivo("inventarioInsumos.txt", ios::trunc);

    if (archivo.is_open())
    {
        for (int i = 0; i < ultimoRegistroInsumos; i++)
        {
            archivo << insumosAGuardar[i].codigoInsumo << endl;
            archivo << insumosAGuardar[i].nombreInsumo << endl;
            archivo << insumosAGuardar[i].precioInsumo << endl;
            archivo << insumosAGuardar[i].cantidadInsumo << endl;
            archivo << insumosAGuardar[i].unidadMedidaInsumo << endl;
        }

        archivo.close();

        cout << "El inventario se ha guardado en el archivo 'inventarioInsumos.txt'." << endl;
    }
    else
    {
        cerr << "No se pudo abrir el archivo." << endl;
    }
}

void mostrarInsumo(Insumo insumoAMostrar)
{

    cout << "Codigo: " << insumoAMostrar.codigoInsumo << endl;
    cout << "Nombre: " << insumoAMostrar.nombreInsumo << endl;
    cout << "Precio: " << insumoAMostrar.precioInsumo << endl;
    cout << "Cantidad: " << insumoAMostrar.cantidadInsumo << endl;
    cout << "Unidad de medida: " << insumoAMostrar.unidadMedidaInsumo << endl;
    cout << "------------------------------" << endl;
}

int buscarInsumo(string codigoABuscar)
{

    {

        for (int i = 0; i < ultimoRegistroInsumos; i++)
        {
            if (inventarioInsumo[i].codigoInsumo == codigoABuscar)
            {
                return i;
            }
        }
        return -1;
    }
}

void sobreescribirDatosInsumos()
{
    ofstream archivo("inventarioInsumos.txt", ios::trunc);

    if (archivo.is_open())
    {
        for (int i = 0; i < ultimoRegistroInsumos; i++)
        {
            archivo << inventarioInsumo[i].codigoInsumo << endl;
            archivo << inventarioInsumo[i].nombreInsumo << endl;
            archivo << inventarioInsumo[i].precioInsumo << endl;
            archivo << inventarioInsumo[i].cantidadInsumo << endl;
            archivo << inventarioInsumo[i].unidadMedidaInsumo << endl;
        }
    }
    else
    {
        cerr << "No se pudo abrir el archivo para sobrescribir." << endl;
    }
    archivo.close();
}

void modificarInsumo(string codigoABuscar)
{

    int codigoAModificar = buscarInsumo(codigoABuscar);

    if (codigoAModificar != -1)
    {
        mostrarInsumo(inventarioInsumo[codigoAModificar]);

        cout << "Ingrese los nuevos datos para el producto:" << endl;
        cout << "Ingrese el nuevo nombre: ";
        cin.ignore();
        getline(cin, inventarioInsumo[codigoAModificar].nombreInsumo);
        cout << "Ingrese el nuevo precio: ";
        cin >> inventarioInsumo[codigoAModificar].precioInsumo;
        cout << "Ingrese la nueva cantidad: ";
        cin >> inventarioInsumo[codigoAModificar].cantidadInsumo;
        cout << "Ingrese la nueva unidad de medida: " << endl;
        sobreescribirDatosInsumos();
    }
    else
    {
        cout << "No se encontró un producto con el código especificado." << endl;
    }
}
void eliminarInsumo(string codigoABuscar)
{

    int codigoAEliminar = -1;
    codigoAEliminar = buscarInsumo(codigoABuscar);

    if (codigoAEliminar != -1)
    {
        // Elimina el producto moviendo los elementos restantes
        for (int i = codigoAEliminar; i < ultimoRegistroInsumos - 1; i++)
        {
            inventarioInsumo[i] = inventarioInsumo[i + 1];
        }

        ultimoRegistroInsumos--;

        sobreescribirDatosInsumos();
    }
    else
    {
        cout << "No se encontró un producto con el código especificado." << endl;
    }
}
void registrarEntradaSalidaInsumo(string codigoARegistrar)
{
    int opcion = 0;
    int cantidadARegistrar = 0;
    int codigoAModificar = buscarInsumo(codigoARegistrar);

    while (opcion != 3)
    {
        mostrarInsumo(inventarioInsumo[codigoAModificar]);
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
            inventarioInsumo[codigoAModificar].cantidadInsumo += cantidadARegistrar;
            actualizarCantidadProductos();
            cout << "Entrada registrada exitosamente." << endl;
            system("pause");

            break;
        case 2:
            cout << "Ingrese la cantidad de salida (-) del producto ";
            cin >> cantidadARegistrar;
            inventarioInsumo[codigoAModificar].cantidadInsumo -= cantidadARegistrar;

            actualizarCantidadProductos();
            break;
        case 3:
            cout << "Saliendo al menu..." << endl;
            break;
        default:

            break;
        }
    }
}

void registrarEntradaInsumos(Producto productoARegistrar, int cantidadProductoOrdenado)
{

    int resultadoBusqueda = -1;
    for (int i = 0; i < productoARegistrar.numeroInsumosUsados; i++)
    {
        resultadoBusqueda = buscarInsumo(productoARegistrar.insumosNecesarios[i].codigoInsumo);
        if (resultadoBusqueda != -1)
        {
            inventarioInsumo[resultadoBusqueda].cantidadInsumo += productoARegistrar.cantidadInsumosNecesarios[i] * cantidadProductoOrdenado;
        }
        sobreescribirDatosInsumos();
    }
}