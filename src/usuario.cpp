#include "../include/usuario.h"
#include "../include/utils.h"
#include <iostream>
#include <string>
#include <iomanip> // uso de setw()

using namespace std;

string currentUser;

static int totalUsuarios = 3;
static Usuario usuarios[100] = {
    {"admin", "123", 1, 1}, 
    {"vend1", "123", 2, 1}, 
    {"vend2", "123", 2, 1}
};

bool validarLogin(int tipoUsuario){
    bool isValid = false;
    string usuario, pass;
    do{
        cout << "\nUsuario: ";
        cin >> usuario;
        if(usuario == "*"){limpiarConsola(); break;}
        cout << "\nPassword: ";
        cin >> pass;

        for (int i = 0; i < totalUsuarios; i++){
            if (usuarios[i].usuario == usuario && usuarios[i].pass == pass && usuarios[i].tipo == tipoUsuario && usuarios[i].status == 1){
                currentUser = usuario;
                isValid = true;
                break;
            }
        }
        if (isValid == false) cout << "\n\n*** Usuario o contraseña incorrectos. Intenta de nuevo. ***" << endl;
    } while (!isValid);
    return isValid;
}


Usuario buscarUsuario(string nombreUsuario){
    Usuario usuario = {"", "", 0, 0};
    for(int i = 0; i < totalUsuarios; i++){
        if(convertirMinus(usuarios[i].usuario) == convertirMinus(nombreUsuario)) { usuario = usuarios[i]; break; }
    }
    return usuario;
}

void mostrarMenuAdminCuentasUsuario(){
    int option;
    bool ejecutarMenu = true;
    
    while(ejecutarMenu){
        cout << "\n\n\tMENU ADMINISTRACION DE CUENTAS DE USUARIOS\n\n";
        cout << "1. Altas\n2. Bajas\n3. Consultas\n4. Modificaciones\n5. Mostrar cuentas de usuarios\n6. Regresar al menu anterior.\n\n";
        cout << "\tOpcion: ";
        cin >> option;
        validarInput();
        switch (option){
            case 1:
                limpiarConsola();
                altaUsuario();
                break;
            case 2:
                limpiarConsola();
                bajaUsuario();
                break;
            case 3:
                limpiarConsola();
                consultarUsuario();
                break;
            case 4:
                limpiarConsola();
                modificarUsuario();
                break;
            case 5:
                limpiarConsola();
                mostrarCuentasUsuarios();
                break;
            case 6:
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

void altaUsuario(){
    Usuario usuario;
    string nombreUsuario;
    string pass;
    int tipo;

    cout << "\n\n\tALTA USUARIO\n\n";
    while(true){
        cout << "Usuario: "; cin >> nombreUsuario;
        if (nombreUsuario == "*"){limpiarConsola(); break;}

        usuario = buscarUsuario(nombreUsuario);
        if(usuario.status == 1){cout << "\n\n*** El usuario \"" << nombreUsuario << "\"  ya existe. Intenta de nuevo. ***\n\n"; continue;} // validacion estatus.

        cout << "Contraseña: "; cin >> pass;
        while (tipo != 1 && tipo != 2) {
            cout << "Tipo (1 admin / 2 vendedor): "; cin >> tipo; validarInput();
            if (tipo != 1 && tipo != 2)
                cout << "*** Tipo incorrecto. Intenta de nuevo ***" << endl;
        }

        // se agrega el producto.
        usuarios[totalUsuarios].usuario = nombreUsuario;
        usuarios[totalUsuarios].pass = pass;
        usuarios[totalUsuarios].tipo = tipo;
        usuarios[totalUsuarios].status = 1;
        totalUsuarios++; // se incrementa en 1 la cantidad de usuarios.

        cout << "\n\nEl Usuario \"" << nombreUsuario << "\" se agrego correctamente.\n\n";
    }
}

void bajaUsuario(){
    string nombreUsuario;
    
    while(true){
        bool usuarioEncontrado = false;
        cout << "\n\n\tBAJA USUARIO\n\n";
        cout << "Usuario: "; cin >> nombreUsuario;
        if (nombreUsuario == "*"){limpiarConsola(); break;}

        for(int i = 0; i<totalUsuarios; i++){
            if(convertirMinus(usuarios[i].usuario) == convertirMinus(nombreUsuario) && usuarios[i].status == 1) {
                usuarios[i].status = 0; 
                cout << "El usuario \"" << usuarios[i].usuario << "\" se dio de baja\n\n";
                usuarioEncontrado = true;
                break; 
            }
        }

        if(!usuarioEncontrado){cout << "\n\n***Usuario \"" << nombreUsuario << "\" no encontrado. Intenta de nuevo. ***\n\n";}
    }
}

void modificarUsuario(){
    string nombreUsuario, pass;
    int opcion, tipo;

    while (true){
        bool usuarioEncontrado = false;
        bool mostrarOpciones = true;
        cout << "\n\n\tMODIFICACIONES\n\nUsuario: "; cin >> nombreUsuario;
        if (nombreUsuario == "*"){limpiarConsola(); break;}
        for(int i = 0; i<totalUsuarios; i++){
            if(convertirMinus(usuarios[i].usuario) == convertirMinus(nombreUsuario) && usuarios[i].status == 1) {
                limpiarConsola();
                while (mostrarOpciones){
                    cout << "\n\n\tMODIFICACIONES\n\nUsuario: "<< nombreUsuario << endl;
                    cout << "\n1. Contraseña\n2. Tipo\n3. Regresar al menu anterior\n\n";
                    cout << "\tOpcion: "; cin >> opcion; validarInput();
                    switch(opcion){
                        case 1:
                            cout << "\nContraseña actual: "<< usuarios[i].pass;
                            cout << "\nContraseña nueva: "; cin >> pass;
                            usuarios[i].pass = pass; // actualizamos el password
                            cout << "\n\nContraseña actualizada\n\n";
                            break;
                        case 2:
                            cout << "\nTipo actual: "<< usuarios[i].tipo;
                            cout << "\nTipo nuevo: "; cin >> tipo; validarInput();
                            usuarios[i].tipo = tipo; // actualizamos el tipo
                            cout << "\n\nTipo actualizado\n\n";
                            break;
                        case 3:
                            limpiarConsola();
                            mostrarOpciones = false;
                            break;
                        default:
                            cout << "*** Opcion incorrecta. Intenta de nuevo. ***";
                            break;
                    }
                }
                usuarioEncontrado = true;
            }
        }
        if(!usuarioEncontrado){cout << "\n\n***Usuario \"" << nombreUsuario << "\" no encontrado. Intenta de nuevo. ***\n\n";}
    }
}

void consultarUsuario(){
    Usuario usuario;
    string nombreUsuario;
    while (true){
        cout << "\n\n\tCONSULTA\n\nUsuario: "; cin >> nombreUsuario;
        if (nombreUsuario == "*"){limpiarConsola(); break;}
        usuario = buscarUsuario(nombreUsuario);
        if(usuario.status == 1){
            cout << "\n" << left << setw(15) << "Usuario"
                    << setw(10) << "Pass"
                    << setw(10) << "Tipo"
                    << "Status" << endl;
            cout << left << setw(15) << usuario.usuario
                    << setw(10) << usuario.pass
                    << setw(10) << usuario.tipo
                    << usuario.status << endl;
            continue;
        }
        cout << "\n\n*** No se encontro el usuario \"" << nombreUsuario << "\" ***\n\n";
    }
}

void mostrarCuentasUsuarios(){
    cout << "---------------------------------------------------------------------------\n\t\t\tMOSTRAR CUENTAS DE USUARIOS\n---------------------------------------------------------------------------\n";
    cout << "\n" << left << setw(15) << "Usuario"
                    << setw(10) << "Pass"
                    << setw(10) << "Tipo"
                    << "Status" << endl;
    for(int i = 0; i < totalUsuarios; i++){
        if(usuarios[i].status == 1){
            cout << left << setw(15) << usuarios[i].usuario
                    << setw(10) << usuarios[i].pass
                    << setw(10) << usuarios[i].tipo
                    << usuarios[i].status << endl;
        }
    }
    cout << "\n\n";
}