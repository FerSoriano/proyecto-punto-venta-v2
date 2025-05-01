#ifndef USUARIO_H
#define USUARIO_H

#include <string>

extern std::string currentUser;

struct Usuario{
    std::string usuario;
    std::string pass;
    int tipo;
    int status;
};

bool validarLogin(int tipoUsuario);
void mostrarMenuAdminCuentasUsuario();
Usuario buscarUsuario(std::string nombreUsuario);
void altaUsuario();
void bajaUsuario();
void modificarUsuario();
void consultarUsuario();
void mostrarCuentasUsuarios();
bool crearUsuariosCSV(bool valoresDefault);
void agregarUsuarioCSV(const std::string& nuevoUsuario);
void actualizarVectorUsuarios();

#endif