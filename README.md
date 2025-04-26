# 🏪 Proyecto Punto de Venta v2

Sistema mejorado de punto de venta con persistencia en CSV y arquitectura modular.

## 📋 Tabla de Contenidos

- [Requisitos](#-requisitos)
- [Estructura del Proyecto](#-estructura-del-proyecto)
- [Compilación y Ejecución](#-compilación-y-ejecución)
- [Características Principales](#✨-características-principales)
- [Módulos](#📦-módulos)

---

## 🛠 Requisitos

- Compilador C++17 (g++ o clang++)
- Sistema operativo Linux/Windows/macOS
- Permisos de escritura en el directorio `output/`

---

## 📂 Estructura del Proyecto

```markdown
punto_venta/
├── include/ # Contiene todos los archivos header
│ ├── menu.h
│ ├── producto.h
│ ├── usuario.h
│ ├── utils.h
│ └── venta.h
│
├── src/ # Contiene todos los archivos fuente (.cpp)
│ ├── main.cpp # Programa principal
│ ├── menu.cpp # Interfaces
│ ├── producto.cpp # Lógica de gestión de productos
│ ├── usuario.cpp # Autenticación y roles de usuario
│ ├── utils.cpp # Funciones de utilidad compartidas
│ └── venta.cpp # Procesamiento de transacciones
│
└── output/
│ ├── main # Ejecutable compilado
│ └── data/ # Datos persistentes en CSV
│ ├── productos.csv
│ └── users.csv
```

---

## 🚀 Compilación y Ejecución

### Compilación (desde `src/`)

```bash
g++ -Wall -Wextra -g3 -std=c++17 main.cpp usuario.cpp utils.cpp venta.cpp producto.cpp menu.cpp -o ../output/main
```

**_Flags recomendados:_**

`-Wall -Wextra`: Habilita advertencias adicionales

`-g3`: Información de depuración

`-std=c++17`: Estándar C++17

### Ejecutar:

```bash
cd ../output/; ./main
```

## 💥 Características Principales

- **Persistencia de datos**: Almacenamiento en archivos CSV
- **Arquitectura modular**: Código organizado por responsabilidades
- **Manejo dinámico**: Vectores en lugar de arrays estáticos
- **Interfaz de consola**: Menús interactivos

## 📦 Módulos

| Módulo     | Función                                              |
| ---------- | ---------------------------------------------------- |
| `producto` | Gestión de inventario (altas, bajas, modificaciones) |
| `usuario`  | Control de acceso (admin/vendedor)                   |
| `venta`    | Procesamiento de transacciones                       |
| `utils`    | Funciones auxiliares (validaciones, formato)         |
| `menu`     | Interfaz de usuario                                  |
