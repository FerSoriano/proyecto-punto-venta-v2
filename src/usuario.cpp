#include "../include/usuario.h"
#include "../include/utils.h"
#include <iostream>
#include <string>
#include <iomanip> // uso de setw()
#include <fstream> // ifstream (lectura) y ofstream (escritura)
#include <sstream>   // Para ostringstream (formatear strings) y istringstream (parsear)

using namespace std;

static const string usuariosCSV = "data/users.csv";

string currentUser;

// vectores
static vector<string> usuariosHeaders = {"usuario", "pass", "tipo", "status"};
static vector<Usuario> usuarios = {
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

        for (size_t i = 0; i < usuarios.size(); i++){
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
    for(size_t i = 0; i < usuarios.size(); i++){
        if(convertirMinus(usuarios[i].usuario) == convertirMinus(nombreUsuario)) { usuario = usuarios[i]; break; }
    }
    return usuario;
}

// Para agregar usuarios nuevos, se agrega al final del CSV.
void agregarUsuarioCSV(const string& nuevoUsuario){
    const string fileName = usuariosCSV;
    ofstream file(fileName, ios::app); // append
    if(!file.is_open()){
        throw runtime_error("\n\n *** Error al abrir el archivo \"" + fileName + "\". Intenta de nuevo ***");
    }
    file << nuevoUsuario << '\n';
    file.close();
}

// Sobreescribir el archivo con el vector
bool crearUsuariosCSV(bool valoresDefault){
    const string fileName = usuariosCSV;
    ofstream file(fileName, ios::out); // Abre para sobreescribir
    if(!file.is_open()){
        throw runtime_error("\n\n *** Error al abrir el archivo \"" + fileName + "\". Intenta de nuevo ***");
    }

    // crear headers
    ostringstream headers;
    for(size_t i = 0; i < usuariosHeaders.size(); i++){
        if(i!=0) headers << ",";
        headers << usuariosHeaders[i];
    }

    file << headers.str() << endl; // agregamos headers al CSV

    for(const auto& usuario : usuarios){
        file << usuario.usuario << ","
            << usuario.pass << ","
            << usuario.tipo << ","
            << usuario.status << "\n";             
    }

    file.close();
    if(valoresDefault) cout << "\nArchivo creado en: " << filesystem::absolute(usuariosCSV) << endl;
    return true;
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

        Usuario nuevoUsuario = {nombreUsuario, pass, tipo, 1}; // 1 = status activo

        // se crea el usuario en formato CSV
        string nuevoUsuarioStr = nombreUsuario + "," + pass + "," + to_string(tipo) + "," + "1";
        
        // se agrega el usuario al vector
        usuarios.push_back(nuevoUsuario);
        cout << "\n\nEl Usuario \"" << nombreUsuario << "\" se agrego correctamente.\n\n";
        // se agrega el usuario al CSV
        agregarUsuarioCSV(nuevoUsuarioStr);
    }
}

void bajaUsuario(){
    string nombreUsuario;
    bool baja = false;
    
    while(true){
        bool usuarioEncontrado = false;
        cout << "\n\n\tBAJA USUARIO\n\n";
        cout << "Usuario: "; cin >> nombreUsuario;
        if (nombreUsuario == "*"){limpiarConsola(); break;}

        for(size_t i = 0; i<usuarios.size(); i++){
            if(convertirMinus(usuarios[i].usuario) == convertirMinus(nombreUsuario) && usuarios[i].status == 1) {
                usuarios[i].status = 0; 
                cout << "El usuario \"" << usuarios[i].usuario << "\" se dio de baja\n\n";
                usuarioEncontrado = true;
                baja = true;
                break; 
            }
        }
        if(!usuarioEncontrado){cout << "\n\n***Usuario \"" << nombreUsuario << "\" no encontrado. Intenta de nuevo. ***\n\n";}
    }
    if(baja) crearUsuariosCSV(false); // se actualiza el CSV
}

void modificarUsuario(){
    string nombreUsuario, pass;
    int opcion, tipo;
    bool modificado = false;

    while (true){
        bool usuarioEncontrado = false;
        bool mostrarOpciones = true;
        cout << "\n\n\tMODIFICACIONES\n\nUsuario: "; cin >> nombreUsuario;
        if (nombreUsuario == "*"){limpiarConsola(); break;}
        for(size_t i = 0; i<usuarios.size(); i++){
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
                            modificado = true;
                            break;
                        case 2:
                            cout << "\nTipo actual: "<< usuarios[i].tipo;
                            cout << "\nTipo nuevo: "; cin >> tipo; validarInput();
                            usuarios[i].tipo = tipo; // actualizamos el tipo
                            cout << "\n\nTipo actualizado\n\n";
                            modificado = true;
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
    if(modificado) crearUsuariosCSV(false); // actualizar CSV
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
    for(size_t i = 0; i < usuarios.size(); i++){
        if(usuarios[i].status == 1){
            cout << left << setw(15) << usuarios[i].usuario
                    << setw(10) << usuarios[i].pass
                    << setw(10) << usuarios[i].tipo
                    << usuarios[i].status << endl;
        }
    }
    cout << "\n\n";
}

// actualizar vector al iniciar el programa
void actualizarVectorUsuarios(){
    usuarios.clear();

    ifstream file(usuariosCSV);

    if(!file.is_open()){
        throw runtime_error("\n\n *** Error actualizando el vector. No se pudo abrir el archivo \"" + filesystem::absolute(usuariosCSV).string() + "\". ***\n\n");
    }

    string row;
    bool isFirstRow = true;

    while(getline(file,row)){
        if(isFirstRow){
            isFirstRow = false;
            continue;; // saltamos el header
        }

        stringstream ss(row);
        string field;
        Usuario u;

        getline(ss,field,','); u.usuario = field;
        getline(ss,field,','); u.pass = field;
        getline(ss,field,','); u.tipo = stoi(field);
        getline(ss,field,','); u.status = stoi(field);

        usuarios.push_back(u); // se agrega el usuario al vector
    }

    file.close();
}