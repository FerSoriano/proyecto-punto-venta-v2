// modulos
#include "../include/utils.h"
#include "../include/venta.h"
#include "../include/menu.h"
#include <iostream>
#include <stdexcept>

using namespace std;

int main(){
    bool isExcecute = true;
    int optionMenu;
    menuCrearCSV();
    while (isExcecute){
        try{
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
        } catch(const exception& e){
            cerr << "Error no esperado: " << e.what() << endl;
        }
    }
    return 0;
}