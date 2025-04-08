#include "../include/utils.h"
#include <iostream>
#include <limits>
#include <string>
//#include <cstdlib> // para system()

using namespace std;

void validarInput(){
    // si el usuario ingresa un dato no numerico, se limpia el cache de cin.
    if (!cin.good()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string convertirMinus(string str){
    for (char &c : str) c = tolower(c);
    return str;
}

void limpiarConsola(){
    #ifdef _WIN32
        system("cls"); // Windows
    #else
        system("clear"); // macOS/Linux
    #endif
};