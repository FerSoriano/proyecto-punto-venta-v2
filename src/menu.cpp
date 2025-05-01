#include "../include/menu.h"
#include "../include/utils.h"
#include "../include/usuario.h"
#include "../include/producto.h"
#include "../include/venta.h"
#include <iostream>
#include <stdexcept> // manejo de excepciones


using namespace std;

int menuPrincipal(){
    int option;
    cout << "\n\n\tMENU PRINCIPAL\n\n";
    cout << "1. Administrador\n2. Ventas\n3. Salir\n\n";
    cout << "\tOpcion: "; cin >> option;
    validarInput();
    return option;
}

void menuCrearCSV(){
    try{
        limpiarConsola();
        char response;
        do{
            cout << "\nDeseas crear el CSV de PRODUCTOS con los valores por default? (y: si): ";
            cin >> response;
            if(tolower(response)=='y') {
                if(crearProductosCSV(true)) break;
            } else {
                actualizarVectorProductos();
                break;
            }
        } while(true);

        do{
            cout << "\n\nDeseas crear el CSV de USUARIOS con los valores por default? (y: si): ";
            cin >> response;
            if(tolower(response) == 'y'){
                if(crearUsuariosCSV(true)) break;
            } else {
                actualizarVectorUsuarios();
                break;
            }
        } while(true);

    } catch(const runtime_error& e){
        cerr << "Runtime error exception: " << e.what() << endl;
    } catch(const exception& e){
        cerr << "Error no esperado: " << e.what() << endl;
    }
}

void menuAdmin(){
    try{
        if (validarLogin(1)){
            limpiarConsola();
            int option;
            bool ejecutarMenu = true;
            
            while(ejecutarMenu){
                cout << "\n\n\tMENU ADMINISTRADOR\n\n";
                cout << "1. Altas\n2. Bajas\n3. Consultas\n4. Modificaciones\n5. Mostrar Inventario\n6. Administracion de Cuentas de Usuario\n7. Corte de caja general\n8. Regresar al menu anterior.\n\n";
                cout << "\tOpcion: ";
                cin >> option;
                validarInput();
                switch (option){
                    case 1:
                        limpiarConsola();
                        altaProducto();
                        break;
                    case 2:
                        limpiarConsola();
                        bajaProducto();
                        break;
                    case 3:
                        limpiarConsola();
                        consultarProducto();
                        break;
                    case 4:
                        limpiarConsola();
                        modificarProducto();
                        break;
                    case 5:
                        limpiarConsola();
                        mostrarInventario();
                        break;
                    case 6:
                        limpiarConsola();
                        mostrarMenuAdminCuentasUsuario();
                        break;
                    case 7:
                        limpiarConsola();
                        corteCajaGeneral();
                        break;
                    case 8:
                        limpiarConsola();
                        ejecutarMenu = false;
                        break;
                    default:
                        limpiarConsola();
                        cout << "\n*** Opcion invalida. Intenta de nuevo. ***";
                        break;
                }
            }
        }
    } catch(const runtime_error& e){
        cerr << "Runtime error exception: " << e.what() << endl;
    } catch(const exception& e){
        cerr << "Error no esperado: " << e.what() << endl;
    }
}
