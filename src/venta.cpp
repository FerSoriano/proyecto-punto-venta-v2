#include "../include/venta.h"
#include "../include/utils.h"
#include "../include/producto.h"
#include "../include/usuario.h"
#include <iostream>
#include <string>
#include <iomanip> // uso de setw()

using namespace std;

static int totalVentas = 0;
static Venta ventas[100];

void hacerVenta(){
    if (validarLogin(2)){
        limpiarConsola();
        Producto producto;
        Venta ventaActual;
        string nombreProducto;
        int cantidad;
        
        cout << "\n\n\tVENTAS: " << currentUser <<"\n\n";
        while(true){
            cout << "Producto: "; cin >> nombreProducto;

            if(nombreProducto == "*"){ // imprimir ticket
                limpiarConsola(); 
                ventas[totalVentas] = ventaActual; // agregamos la venta a la lista
                imprimirTicket(ventaActual); 
                totalVentas++; // se incrementa en uno las ventas
                reiniciarVenta(ventaActual); // se vuelve a inicializar vacio
                continue;
            }
            if(nombreProducto == "**"){ // corte de caja vendedor
                limpiarConsola();
                corteCajaVendedor(currentUser);
                break;
            }

            producto = buscarProducto(nombreProducto);
            // validamos que el producto exista o no este dado de baja
            if(producto.status == 0){ cout << "\n\n*** No se encontro el producto. Intenta de nuevo ***\n\n"; continue; }
            // validamos que tengan existencias
            if(producto.existencias <= 0){ cout << "\n\n*** El producto no tiene existencia. Intenta de nuevo ***\n\n"; continue; }

            cout << "Cantidad: "; cin >> cantidad; validarInput();
            if(cantidad <= 0){cout << "\n\n*** Cantidad invalida. Intenta de nuevo ***\n\n"; continue;}

            // validamos que tengamos las existencias que solicita el cliente
            if(producto.existencias < cantidad){
                string resp;
                cout << "\n\nNo hay " << cantidad << ", solo hay " << producto.existencias << ", ¿realizar la venta de " << producto.existencias << "? ('Y' para aceptar / cualquiera para omitir): ";
                cin >> resp;
                if( convertirMinus(resp) != "y") { cout << "\n"; continue; }
                cantidad = producto.existencias;
                cout << "Se agregaron " << producto.existencias << endl;
            }
            
            // creamos la venta dentro de la estructura de Ventas
            ventaActual.vendedor = currentUser; // vendedor loggeado
            ventaActual.productos[ventaActual.totalProductosVentas] = producto.producto; // nombre del producto
            ventaActual.cantidad[ventaActual.totalProductosVentas] = cantidad;
            ventaActual.pc[ventaActual.totalProductosVentas] = producto.pc;
            ventaActual.pv[ventaActual.totalProductosVentas] = producto.pv;
            ventaActual.totalProductosVentas++;

            // Restar producto al inventario
            restarInventario(producto.id, cantidad);

            cout << "\n";
        }
    }
}

void imprimirTicket(Venta venta){
    float total = 0;
    cout << "\n\n-------------------------------------------------------\n\n";
    cout << "\t\tAbarrotes \"El Inge\"";
    cout << "\n\t\t Ticket de Venta\n\n\n";
    cout << "Vendedor: " << venta.vendedor << endl;

    cout << "\n" << left << setw(15) << "Producto"
                    << setw(10) << "Cantidad"
                    << setw(20) << "Precio Unitario"
                    << "Subtotal" << endl;
    for(int i = 0; i < venta.totalProductosVentas; i++){
        float subtotal = venta.cantidad[i] * venta.pv[i];
        total += subtotal;
        cout << left << setw(15) << venta.productos[i]
                << setw(10) << venta.cantidad[i]
                << setw(20) << venta.pv[i]
                << subtotal << endl;
    }
    cout << "\n\t\t\t\t     Total: $" << total << "\n\n-------------------------------------------------------\n\n";
}

// void reiniciarVenta(Venta &venta); // valid if neccesary
void corteCajaVendedor(string vendedor){
    float ingresos = 0, egresos = 0;
    
    cout << "\n\n-------------------------------------------------------\n\n";
    cout << "\t\tCorte de Caja: " << vendedor << "\n\n";
    for(int i=0; i < totalVentas; i++){
        if(ventas[i].vendedor == vendedor){
            for(int k=0; k < ventas[i].totalProductosVentas; k++){
                ingresos += (ventas[i].pv[k] * ventas[i].cantidad[k]);
                egresos  += (ventas[i].pc[k] * ventas[i].cantidad[k]);
            }
        }
    }
    cout << "Ingresos: $" << ingresos << endl;
    cout << "Egresos:  $" << egresos << endl;
    cout << "\nUtilidad: $" << ingresos - egresos << endl;
    cout << "\n-------------------------------------------------------\n\n";
}

void corteCajaGeneral(){
    float ingresos = 0, egresos = 0;
    cout << "\n\n-------------------------------------------------------\n\n";
    cout << "\t\tCorte general\n\n";
    for(int i=0; i<totalVentas; i++){
        for(int j=0; j < ventas[i].totalProductosVentas; j++){
            ingresos += (ventas[i].pv[j] * ventas[i].cantidad[j]);
            egresos  += (ventas[i].pc[j] * ventas[i].cantidad[j]);
        }
    }
    cout << "Ingresos: $" << ingresos << endl;
    cout << "Egresos:  $" << egresos << endl;
    cout << "\nUtilidad: $" << ingresos - egresos << endl;
    cout << "\n-------------------------------------------------------\n\n";
}

void reiniciarVenta(Venta &venta) {
    venta.vendedor = "";
    for (int i = 0; i < venta.totalProductosVentas; i++) {
        venta.productos[i] = "";
        venta.cantidad[i] = 0;  
        venta.pc[i] = 0.0;      
        venta.pv[i] = 0.0;
    }
    venta.totalProductosVentas = 0;
}