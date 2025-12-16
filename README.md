# Proyecto Hospital - AED1

Sistema de gestión hospitalaria desarrollado en C++ como proyecto para la asignatura de Algoritmos y Estructuras de Datos 1.

## 📋 Descripción

Este proyecto implementa un sistema de gestión para un hospital, incluyendo:

- Gestión de pacientes con prioridades de urgencia
- Gestión de doctores y cola de atención
- Control de enfermedades y su tratamiento
- Sistema de medicamentos y almacén
- Historial de tratamientos

## 🛠️ Requisitos

- **CMake** >= 3.14
- **Compilador C++** compatible con C++11 o superior (g++, clang++, MSVC)
- **Git** para clonar el repositorio

## 📦 Instalación

### 1. Clonar el repositorio

```bash
git clone https://github.com/Andreavilaro0/Proyecto-Hospital.git
cd Proyecto-Hospital
```

### 2. Compilar el proyecto

```bash
cd ProyectoAED1
mkdir build
cd build
cmake ..
make
```

> **Nota:** CMake descargará automáticamente Google Test para los tests unitarios.

## 🚀 Ejecución

### Ejecutar el programa principal

```bash
./ProyectoAED1
```

### Ejecutar los tests

```bash
# Ejecutar tests directamente
./ProyectoAED1_test

# O usando CTest
ctest --verbose
```

## 📁 Estructura del Proyecto

```
Proyecto-Hospital/
├── CMakeLists.txt              # Configuración CMake raíz
├── CMakePresets.json           # Presets de CMake
├── ProyectoAED1/
│   ├── CMakeLists.txt          # Configuración CMake del proyecto
│   ├── ProyectoAED1.cpp        # Archivo principal
│   ├── ProyectoAED1.h          # Header principal
│   ├── ProyectoAED1_test.cpp   # Tests unitarios
│   ├── lib.h                   # Biblioteca con las clases del sistema
│   └── lib.cpp                 # Implementación de la biblioteca
└── README.md                   # Este archivo
```

## 🏥 Clases Principales

- **`Hospital`**: Clase principal que gestiona doctores, pacientes y medicamentos
- **`Paciente`**: Representa un paciente con sus enfermedades e historial
- **`Doctor`**: Representa un doctor con su cola de enfermedades pendientes
- **`Enfermedad`**: Define una enfermedad con su letalidad y urgencia
- **`Medicamento`**: Gestiona el inventario de medicamentos

## 🧪 Tests

El proyecto incluye tests unitarios usando Google Test. Actualmente implementa:

- `test1`: Test básico de verificación
- `test2`: Test de ejemplo (falla intencionalmente)

Para agregar más tests, edita `ProyectoAED1_test.cpp`.

## 🔧 Compilación en diferentes plataformas

### Linux/macOS

```bash
cd ProyectoAED1/build
cmake .. && make
```

### Windows (Visual Studio)

```bash
cd ProyectoAED1
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

## 👥 Autores

- Andrea Ávila - [@Andreavilaro0](https://github.com/Andreavilaro0)

## 📝 Notas

- El directorio `build/` está excluido del control de versiones
- Google Test se descarga automáticamente durante la compilación
- Para recompilar desde cero: `rm -rf build && mkdir build && cd build && cmake .. && make`

## 🐛 Solución de Problemas

### Error: "No such file or directory"

Asegúrate de estar en el directorio correcto antes de compilar:

```bash
cd ProyectoAED1
mkdir -p build
cd build
```

### Error de CMake

Si CMake no encuentra el compilador, especifica uno manualmente:

```bash
cmake -DCMAKE_CXX_COMPILER=g++ ..
```

### Problemas con Google Test

Si hay problemas descargando Google Test, verifica tu conexión a internet y vuelve a intentar.

## 📄 Licencia

Proyecto académico - Universidad
