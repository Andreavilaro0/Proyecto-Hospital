#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "lib.h"

// Función para cargar medicamentos
void cargarMedicamentos(Hospitalnames::Hospital* hospital) {
    std::ifstream archivo("medicamentos.csv"); 

    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir medicamentos.csv" << std::endl;
        return;
    }

    std::string linea;
    
    // Saltar la línea de encabezados
    std::getline(archivo, linea);

    while (std::getline(archivo, linea)) {
        std::stringstream ss(linea); 
        std::string dato;
        
        int id;
        std::string nombre;
        std::string tipo;
        int cantidad;
        
        std::getline(ss, dato, ','); 
        id = std::stoi(dato); 
        std::getline(ss, nombre, ',');
        std::getline(ss, tipo, ',');
        std::getline(ss, dato, ',');
        cantidad = std::stoi(dato);

        Hospitalnames::Medicamento m(id, nombre, tipo, cantidad);
        hospital->getAlmacen()->push_back(m);
    }

    archivo.close();
    std::cout << "Carga completada. Medicamentos en almacen: " 
              << hospital->getAlmacen()->size() << std::endl;
}

// Función auxiliar para cargar enfermedades desde CSV
std::vector<Hospitalnames::Enfermedad> cargarEnfermedades() {
    std::vector<Hospitalnames::Enfermedad> enfermedades;
    std::ifstream archivo("enfermedades.csv");

    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir enfermedades.csv" << std::endl;
        return enfermedades;
    }

    std::string linea;
    
   
    std::getline(archivo, linea);

    while (std::getline(archivo, linea)) {
        if (linea.empty()) continue; 
        std::stringstream ss(linea);
        std::string dato;
        
        int id;
        std::string nombre;
        int letalidad;
        int urgencia;
        
        std::getline(ss, dato, ',');
        id = std::stoi(dato);
        std::getline(ss, nombre, ',');
        std::getline(ss, dato, ',');
        letalidad = std::stoi(dato);
        std::getline(ss, dato, ',');
        urgencia = std::stoi(dato);

        Hospitalnames::Enfermedad enf(id, nombre, letalidad, urgencia);
        enfermedades.push_back(enf);
    }

    archivo.close();
    std::cout << "Enfermedades cargadas: " << enfermedades.size() << std::endl;
    
    return enfermedades;
}

// para buscar una enfermedad por ID
Hospitalnames::Enfermedad* buscarEnfermedadPorId(std::vector<Hospitalnames::Enfermedad>& enfermedades, int id) {
    for (size_t i = 0; i < enfermedades.size(); i++) {
        if (enfermedades[i].getId() == id) {
            return &enfermedades[i];
        }
    }
    return nullptr;
}

// Función para cargar pacientes
void cargarPacientes(Hospitalnames::Hospital* hospital) {
    // Primero cargar el vector de enfermedades
    std::vector<Hospitalnames::Enfermedad> enfermedades = cargarEnfermedades();
    
    std::ifstream archivo("pacientes.csv");

    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir pacientes.csv" << std::endl;
        return;
    }

    std::string linea;
    
    
    std::getline(archivo, linea);

    int pacientesCargados = 0;

    while (std::getline(archivo, linea)) {
        if (linea.empty()) continue; 
        
        std::stringstream ss(linea);
        std::string dato;
        
        int id;
        std::string nombre;
        int enf1, enf2, enf3;
   
        std::getline(ss, dato, ',');
        id = std::stoi(dato);
        
       
        std::getline(ss, nombre, ',');
        
    
        std::getline(ss, dato, ',');
        enf1 = std::stoi(dato);
        
        std::getline(ss, dato, ',');
        enf2 = std::stoi(dato);
        
        std::getline(ss, dato, ',');
        enf3 = std::stoi(dato);

        std::list<Hospitalnames::Enfermedad>* enfermedadesPaciente = new std::list<Hospitalnames::Enfermedad>();

        if (enf1 != 0) {
            Hospitalnames::Enfermedad* enf = buscarEnfermedadPorId(enfermedades, enf1);
            if (enf != nullptr) {
                enfermedadesPaciente->push_back(*enf);
            }
        }
        if (enf2 != 0) {
            Hospitalnames::Enfermedad* enf = buscarEnfermedadPorId(enfermedades, enf2);
            if (enf != nullptr) {
                enfermedadesPaciente->push_back(*enf);
            }
        }
        if (enf3 != 0) {
            Hospitalnames::Enfermedad* enf = buscarEnfermedadPorId(enfermedades, enf3);
            if (enf != nullptr) {
                enfermedadesPaciente->push_back(*enf);
            }
        }

        // Crear historial vacío
        std::stack<std::pair<Hospitalnames::Enfermedad, Hospitalnames::Doctor> >* historial = 
            new std::stack<std::pair<Hospitalnames::Enfermedad, Hospitalnames::Doctor> >();

        // Crear paciente
        Hospitalnames::Paciente p(id, nombre, enfermedadesPaciente, historial);
        
        // Añadir a la cola de urgencias del hospital
        hospital->getUrgencias()->push(p);
        
        pacientesCargados++;
    }

    archivo.close();
    std::cout << "Carga completada. Pacientes en urgencias: " 
              << pacientesCargados << std::endl;
}