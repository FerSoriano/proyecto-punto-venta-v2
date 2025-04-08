// modulos
#include "../include/utils.h"
#include "../include/venta.h"
#include "../include/menu.h"
#include <iostream>

using namespace std;

int main(){
    bool isExcecute = true;
    int optionMenu;
    while (isExcecute){
        optionMenu = menuPrincipal();
        switch (optionMenu){
            case 1:
                menuAdmin();
                break;
            case 2:
                hacerVenta();
                break;
            case 3:
                cout << "\n-------------------------------------------------\n     SALIENDO DEL SISTEMA. FIN DEL PROGRAMA.\n-------------------------------------------------\n\n";
                isExcecute = false;
                break;
            default:
                limpiarConsola();
                cout << "\n*** Opcion invalida. Intenta de nuevo. ***";
                break;
        }
    }
    return 0;
}