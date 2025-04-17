#include "../include/producto.h"
#include "../include/utils.h"
#include <iostream>
#include <string>
#include <iomanip> // uso de setw()
#include <fstream> // ifstream (lectura) y ofstream (escritura)
#include <sstream>   // Para ostringstream (formatear strings) y istringstream (parsear)

using namespace std;

static const string productosCSV = "data/productos.csv";

// vectores

static vector<string> productoHeaders = {"id","producto","pc","pv","existencias","nivelReorden","status"};

static vector<Producto> productos = {
    {1,"Agua",13.39,18.55,12,4,1},
    {2,"Leche",12.35,15.5,16,5,1},
    {3,"Huevos",22.4,30.39,20,7,1},
    {4,"Pan",5.5,7.95,18,6,1},
    {5,"Refresco",10.99,14.75,30,8,1}
};



Producto buscarProducto(string nombreProducto){
    Producto producto = {0, "", 0.0, 0.0, 0, 0, 0};
    for(size_t i = 0; i < productos.size(); i++){
        if(convertirMinus(productos[i].producto) == convertirMinus(nombreProducto)) { producto = productos[i]; break; }
    }
    return producto;
}

// Para alta de productos nuevos. Se agrega al final.
bool agregarProductoCSV(const string& nuevoProducto){
    const string fileName = productosCSV;
    ofstream file(fileName, ios::app); // Modo append
    if(!file.is_open()){
        cout << "\n\n *** Error al intentar abrir el archivo \"" << fileName << "\". Intenta de nuevo ***\n\n";
        return false;
    }

    file << nuevoProducto << '\n';
    file.close();
    // cout << "El producto se agrego correctamente al CSV.\n\n" << endl;
    return true;
}


void mostrarInventario(){
    int option;
    bool ejecutarMenu = true;
    
    while(ejecutarMenu){
        cout << "\n\n\tMOSTRAR INVENTARIO\n\nOrdenado por:\n";
        cout << "1. Por Id\n2. Por producto\n3. Regresar al menú anterior.\n\n";
        cout << "\tOpcion: "; cin >> option;
        validarInput();
        switch (option)
        {
        case 1:
            limpiarConsola();
            mostrarProductos(1);
            break;
        case 2:
            limpiarConsola();
            mostrarProductos(2);
            break;
        case 3:
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

bool compararPorId(const Producto &a, const Producto &b) {return a.id < b.id;}
bool compararPorNombre(const Producto &a, const Producto &b) {
    // se convierten a minusculas para poderlos ordenar correctamente.
    string producto_a = convertirMinus(a.producto);
    string producto_b = convertirMinus(b.producto);
    return producto_a < producto_b;
}

void mostrarProductos(int tipoOrden){
    if 
        // (tipoOrden == 1) sort(productos,productos + productos.size(),compararPorId); // se ordena por ID
        (tipoOrden == 1) sort(productos.begin(),productos.end(),compararPorId); // se ordena por ID
    else 
        sort(productos.begin(),productos.end(),compararPorNombre); // se ordena por nombre producto

    cout << "---------------------------------------------------------------------------\n\t\t\t\tINVENTARIO\n---------------------------------------------------------------------------\n";
        cout << left << setw(5) << "Id"
                    << setw(15) << "Producto"
                    << setw(10) << "PC"
                    << setw(10) << "PV"
                    << setw(15) << "Existencias"
                    << setw(10) << "NR"
                    << "Resurtir" << endl;

        char resurtir;
        for (size_t i = 0; i < productos.size(); i++){
            if(productos[i].status == 1){
                resurtir = (productos[i].existencias <= productos[i].nivelReorden) ? '*' : ' ';
                cout << left << setw(5) << productos[i].id
                            << setw(15) << productos[i].producto
                            << setw(10) << productos[i].pc
                            << setw(10) << productos[i].pv
                            << setw(15) << productos[i].existencias
                            << setw(10) << productos[i].nivelReorden
                            << resurtir << endl;
            }
        }
}

void altaProducto(){
    Producto producto;
    string nombreProducto;
    float pc, pv;
    int existencia, nivelReorden;

    cout << "\n\n\tALTA DE PRODUCTO\n\n";
    while(true){
        cout << "Producto: "; cin >> nombreProducto;
        if (nombreProducto == "*"){limpiarConsola(); break;}

        producto = buscarProducto(nombreProducto);
        if(producto.status == 1){cout << "\n\n*** El producto \"" << nombreProducto << "\"  ya existe. Intenta de nuevo. ***\n\n"; continue;} // validacion estatus.

        // si el producto no exite
        if(producto.id == 0){
            do{    
                cout << "Precio compra: "; cin >> pc; validarInput();
                cout << "Precio venta: "; cin >> pv; validarInput();
                if(pc>pv) {cout << "\n\n*** El Precio de Compra no puede ser mayor al Precio de Venta. Intenta de nuevo. ***\n\n";}
            } while(pc>pv);

            do{
                cout << "Existencia: "; cin >> existencia; validarInput();
                cout << "Nivel de Reorden: "; cin >> nivelReorden; validarInput();
                if(existencia<nivelReorden){cout << "\n\n*** La Existencia no puede ser menor que el Nivel de Reorden. Intenta de nuevo ***\n\n";}
            } while (existencia<nivelReorden);

            Producto nuevoProducto = {productos.back().id + 1, nombreProducto, pc, pv, existencia, nivelReorden, 1};
            // se guardan valores a 2 decimales
            ostringstream pc_str; pc_str << fixed << setprecision(2) << nuevoProducto.pc;
            ostringstream pv_str; pv_str << fixed << setprecision(2) << nuevoProducto.pv;
            // se crea el producto en formato CSV
            string nuevoProductoStr = to_string(nuevoProducto.id) + "," + 
                                    nuevoProducto.producto + "," + 
                                    pc_str.str() + "," +
                                    pv_str.str() + "," +
                                    to_string(nuevoProducto.existencias) + "," + 
                                    to_string(nuevoProducto.nivelReorden) + "," + 
                                    "1"; 
            // se agrega el producto en el vector.
            productos.push_back(nuevoProducto);
            cout << "\n\nEl producto \"" << nombreProducto << "\" se agrego correctamente.\n\n";
            
            // se agrega el producto en el CSV.
            agregarProductoCSV(nuevoProductoStr);
        } 
        // el producto ya existe pero esta dado de baja. Se da de alta nuevamente con la misma info.
        else { 
            sort(productos.begin(),productos.end(),compararPorId); // ordenamos la lista para poderla modificar.
            productos[producto.id - 1].status = 1;
            cout << "\n\nEl producto \"" << producto.producto << "\" se dio de alta nuevamente.\n\n";
        }
    }
}

void consultarProducto(){
    Producto producto;
    string nombreProducto;
    while (true){
        cout << "\n\n\tCONSULTA\n\nProducto: "; cin >> nombreProducto;
        if (nombreProducto == "*"){limpiarConsola(); break;}
        producto = buscarProducto(nombreProducto);
        if(producto.status == 1){
            cout << "\n" << left << setw(5) << "Id"
                    << setw(15) << "Producto"
                    << setw(10) << "PC"
                    << setw(10) << "PV"
                    << setw(15) << "Existencias"
                    << setw(20) << "Nivel de Reorden"
                    << "St" << endl;
            cout << left << setw(5) << producto.id
                    << setw(15) << producto.producto
                    << setw(10) << producto.pc
                    << setw(10) << producto.pv
                    << setw(15) << producto.existencias
                    << setw(20) << producto.nivelReorden
                    << producto.status << endl;
            continue;
        }
        cout << "\n\n*** No se encontro el producto \"" << nombreProducto << "\" ***\n\n";
    }
}

void modificarProducto(){
    Producto producto;
    string nombreProducto;
    float pc, pv;
    int existencia, nivelReorden, opcion;

    sort(productos.begin(),productos.end(),compararPorId); // ordenamos la lista para poderla modificar.
    
    while (true){
        bool mostrarOpciones = true;
        cout << "\n\n\tMODIFICACIONES\n\nProducto: "; cin >> nombreProducto;
        if (nombreProducto == "*"){limpiarConsola(); break;}
        producto = buscarProducto(nombreProducto);
        if(producto.status == 1){
            while (mostrarOpciones){
                    cout << "\n\n\tMODIFICACIONES\n\nProducto: "<< producto.producto << endl;
                    cout << "\n1. Precio de compra\n2. Precio de venta\n3. Existencias\n4. Nidel de reorden\n5. Regresar al menu anterior\n\n";
                    cout << "\tOpcion: "; cin >> opcion; validarInput();
                    switch(opcion){
                        case 1:
                            do{
                                cout << "\nPrecio de Compra actual: "<< producto.pc;
                                cout << "\nPrecio de Compra nuevo: "; cin >> pc; validarInput();
                                if(pc <= 0){cout << "*** Precio de Compra invalido. Intenta de nuevo. ***\n\n";}
                            } while (pc <= 0);
                            productos[producto.id - 1].pc = pc; // actualizamos el producto original con el ID.
                            producto = buscarProducto(nombreProducto); // actualizamos nuestro producto temporal.
                            cout << "\n\nPrecio de compra actualizado\n\n";
                            break;
                        case 2:
                            do{
                                cout << "\nPrecio de Venta actual: "<< producto.pv;
                                cout << "\nPrecio de Venta nuevo: "; cin >> pv; validarInput();
                                if(pv <= 0){cout << "*** Precio de Venta invalido. Intenta de nuevo. ***\n\n";}
                            } while (pv <= 0);
                            productos[producto.id - 1].pv = pv; // actualizamos el producto original con el ID.
                            producto = buscarProducto(nombreProducto); // actualizamos nuestro producto temporal.
                            cout << "\n\nPrecio de venta actualizado\n\n";
                            break;
                        case 3:
                            cout << "\nExistencias actuales: "<< producto.existencias;
                            cout << "\nExistencias nuevas: "; cin >> existencia; validarInput();
                            productos[producto.id - 1].existencias = existencia; // actualizamos el producto original con el ID.
                            producto = buscarProducto(nombreProducto); // actualizamos nuestro producto temporal.
                            cout << "\n\nExistencia actualizada\n\n";
                            break;
                        case 4:
                            cout << "\nNivel de reorden actual: "<< producto.nivelReorden;
                            cout << "\nNivel de reorden nuevo: "; cin >> nivelReorden; validarInput();
                            productos[producto.id - 1].nivelReorden = nivelReorden; // actualizamos el producto original con el ID.
                            producto = buscarProducto(nombreProducto); // actualizamos nuestro producto temporal.
                            cout << "\n\nNivel de reorden actualizado\n\n";
                            break;
                        case 5:
                            limpiarConsola();
                            mostrarOpciones = false;
                            break;
                        default:
                            cout << "*** Opcion incorrecta. Intenta de nuevo. ***";
                            break;
                    }
                }
        } else { limpiarConsola(); cout << "\n\n*** No se encontro el producto \"" << nombreProducto << "\" ***\n\n"; }
    }
}

void bajaProducto(){
    Producto producto;
    string nombreProducto;

    sort(productos.begin(),productos.end(),compararPorId); // ordenamos la lista para poderla modificar.

    while(true){
        cout << "\n\n\tBAJA DE PRODUCTO\n\n";
        cout << "Producto: "; cin >> nombreProducto;
        if (nombreProducto == "*"){limpiarConsola(); break;}

        producto = buscarProducto(nombreProducto);
        if(producto.status == 0){cout << "\n\n***Prodcuto \"" << nombreProducto << "\" no encontrado. Intenta de nuevo. ***\n\n"; continue;}

        productos[producto.id - 1].status = 0;
        cout << "El producto \"" << producto.producto << "\" se dio de baja\n";
    }
}

void restarInventario(int id, int cantidad){
    for(size_t i=0; i<productos.size(); i++){
        if(productos[i].id == id){
            productos[i].existencias -= cantidad;
            break;
        }
    }
}

// Sobreescribir el archivo con el vector: modificaciones, bajas o altas de productos ya existentes.
bool crearProductosCSV(){
    ofstream file;
    file.open(productosCSV, ios::out); // Abre para escribir (sobrescribe)
    if(!file.is_open()){
        cout << "\n\n *** Error al intentar abrir el archivo \"" << std::filesystem::absolute(productosCSV) << "\". Intenta de nuevo ***\n\n";
        return false;
    }

    ostringstream headers;
    for(size_t i=0; i < productoHeaders.size(); i++){
        if(i!=0) headers << ",";
        headers << productoHeaders[i];
    }

    file << headers.str() << endl; // se agregan los headers a nuestro file, pero primero se convierte a str.

    // recorremos el vector de productos
    for(const auto&producto : productos){
        file << producto.id << ","
            << producto.producto << ","
            << producto.pc << ","
            << producto.pv << ","
            << producto.existencias << ","
            << producto.nivelReorden << ","
            << producto.status << '\n';
    }

    file.close();
    cout << "\nArchivo creado en: " << std::filesystem::absolute(productosCSV) << endl;
    return true;
}

void actualizarVectorProductos(){
    productos.clear(); // limpiamos el vector

    ifstream file(productosCSV); // leer CSV

    if(!file.is_open()){
        cout << "\n\n *** Error al intentar abrir el archivo \"" << std::filesystem::absolute(productosCSV) << "\". Intenta de nuevo ***\n\n";
        return;
    }

    string row;
    bool isFirstRow = true;

    while(getline(file, row)){
        if (isFirstRow){
            isFirstRow = false;
            continue; // saltamos header
        }

        stringstream ss(row); // trata a un string como un flujo de datos
        string field;
        Producto p;

        // cada que se llama a getline() avanza automáticamente al siguiente valor. El "cursor" interno de ss se mueve justo después de la primera coma.
        getline(ss,field,','); p.id = stoi(field);
        getline(ss,field,','); p.producto = field;
        getline(ss,field,','); p.pc = stof(field);
        getline(ss,field,','); p.pv = stof(field);
        getline(ss,field,','); p.existencias = stoi(field);
        getline(ss,field,','); p.nivelReorden = stoi(field);
        getline(ss,field,','); p.status = stoi(field);

        productos.push_back(p); // se agrega el producto al vector
    }
    file.close();
}