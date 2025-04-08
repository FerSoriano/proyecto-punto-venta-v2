#ifndef VENTA_H
#define VENTA_H

#include <string>

struct Venta{
    std::string vendedor;
    std::string productos[100];
    int cantidad[100];
    float pc[100];
    float pv[100];
    int totalProductosVentas = 0;
};

void hacerVenta();
void imprimirTicket(Venta venta);
void reiniciarVenta(Venta &venta);
void corteCajaVendedor(std::string vendedor);
void corteCajaGeneral();

#endif