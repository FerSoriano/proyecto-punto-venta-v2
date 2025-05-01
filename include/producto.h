#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <string>

struct Producto{
    int id;
    std::string producto;
    float pc;
    float pv;
    int existencias;
    int nivelReorden;
    int status;
};

Producto buscarProducto(std::string nombreProducto);
void mostrarInventario();
bool compararPorId(const Producto &a, const Producto &b);
bool compararPorNombre(const Producto &a, const Producto &b);
void mostrarProductos(int tipoOrden);
void altaProducto();
void consultarProducto();
void modificarProducto();
void bajaProducto();
void restarInventario(int id, int cantidad);
bool crearProductosCSV(bool valoresDefault);
void agregarProductoCSV(const std::string& nuevoProducto);
void actualizarVectorProductos();

#endif