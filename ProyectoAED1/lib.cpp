#pragma once

#include "lib.h"

namespace Hospitalnames {
	
	// Calcula la prioridad de una enfermedad (letalidad * urgencia)
	int Enfermedad::prioridad() {
		return letalidad * urgencia;
	}

	// Obtiene la maxima prioridad entre todas las enfermedades del paciente. Usa: list
	int Paciente::prioridadPaciente() const {
		int maxPrioridad = 0;
		std::list<Enfermedad>::iterator it;
		for (it = enfermedades->begin(); it != enfermedades->end(); it++) {
			int prioridadActual = it->prioridad();
			if (prioridadActual > maxPrioridad) {
				maxPrioridad = prioridadActual;
			}
		}
		return maxPrioridad;
	}

	// Trata la enfermedad mas grave, la quita de enfermedades y guarda en historial. Usa: list, stack
	Enfermedad Paciente::tratarEnfermedad(Doctor d) {
		std::list<Enfermedad>::iterator it;
		std::list<Enfermedad>::iterator itMasGrave = enfermedades->begin();
		int maxPrioridad = 0;
		
		for (it = enfermedades->begin(); it != enfermedades->end(); it++) {
			if (it->prioridad() > maxPrioridad) {
				maxPrioridad = it->prioridad();
				itMasGrave = it;
			}
		}
		
		Enfermedad enfermedadMasGrave = *itMasGrave;
		enfermedades->erase(itMasGrave);
		
		historial->push(std::make_pair(enfermedadMasGrave, d));
		d.getPendientes()->push_back(enfermedadMasGrave);
		
		return enfermedadMasGrave;
	}

	// Da de alta al paciente cuando ya no tiene mas enfermedades
	void Paciente::darAlta(Doctor d) {
	}

	// Funcion auxiliar recursiva para sumar prioridades de enfermedades pendientes. Usa: recursion, list
	int cobrarRecursivo(std::list<Enfermedad>* pendientes, std::list<Enfermedad>::iterator it) {
		if (it == pendientes->end()) {
			return 0;
		}
		int prioridadActual = it->prioridad();
		it++;
		return prioridadActual + cobrarRecursivo(pendientes, it);
	}

	// Cobra por las enfermedades tratadas y limpia pendientes. Usa: recursion, list
	int Doctor::cobrar() {
		int total = cobrarRecursivo(pendientes, pendientes->begin());
		dinero += total;
		pendientes->clear();
		return total;
	}

	// Trata al paciente mas urgente con el primer doctor disponible. Usa: queue, priority_queue, list, stack
	std::pair<Doctor, Paciente> Hospital::treatPaciente() {
		if (doctores->empty() || urgencias->empty()) {
			return std::pair<Doctor, Paciente>(); 
		}
		Doctor doctorActual = doctores->front(); 
		doctores->pop();
		Paciente pacienteActual = urgencias->top();
		urgencias->pop();
		pacienteActual.tratarEnfermedad(doctorActual);
		doctores->push(doctorActual);
		if (!pacienteActual.getEnfermedades()->empty()) {
			urgencias->push(pacienteActual);
		} else {
			pacienteActual.darAlta(doctorActual);
		}
		return std::make_pair(doctorActual, pacienteActual);
	}

	// Calcula cuanto falta para tener k unidades de cada medicamento. Usa: list
	std::list<Medicamento> Hospital::reponerStock_k(int k) {
		std::list<Medicamento> resultado;
		std::list<Medicamento>::iterator it;
		
		for (it = almacen->begin(); it != almacen->end(); it++) {
			int cantidadFaltante = k - it->getCantidad();
			if (cantidadFaltante > 0) {
				Medicamento med(it->getId(), it->getNombre(), it->getTipo(), cantidadFaltante);
				resultado.push_back(med);
			}
		}
		
		return resultado;
	}

	// Calcula cuanto falta segun niveles adecuados de cada medicamento. Usa: list
	std::list<Medicamento> Hospital::reponerStock_niveles(std::list<Medicamento> nivelesAdecuados) {
		std::list<Medicamento> resultado;
		std::list<Medicamento>::iterator itAlmacen;
		std::list<Medicamento>::iterator itNiveles;
		
		for (itNiveles = nivelesAdecuados.begin(); itNiveles != nivelesAdecuados.end(); itNiveles++) {
			for (itAlmacen = almacen->begin(); itAlmacen != almacen->end(); itAlmacen++) {
				if (itAlmacen->getId() == itNiveles->getId()) {
					int cantidadFaltante = itNiveles->getCantidad() - itAlmacen->getCantidad();
					if (cantidadFaltante > 0) {
						Medicamento med(itAlmacen->getId(), itAlmacen->getNombre(), 
						                itAlmacen->getTipo(), cantidadFaltante);
						resultado.push_back(med);
					}
					break;
				}
			}
		}
		
		return resultado;
	}

	// Funcion auxiliar recursiva para pagar a doctores. Usa: recursion, queue
	int pagarDoctoresRecursivo(std::queue<Doctor>* doctores, int contador) {
		if (contador == 0) {
			return 0;
		}
		
		Doctor doctorActual = doctores->front();
		doctores->pop();
		int cobrado = doctorActual.cobrar();
		doctores->push(doctorActual);
		
		return cobrado + pagarDoctoresRecursivo(doctores, contador - 1);
	}

	// Paga a todos los doctores por las enfermedades que trataron. Usa: recursion, queue
	int Hospital::pagarDoctores() {
		int numDoctores = doctores->size();
		return pagarDoctoresRecursivo(doctores, numDoctores);
	}

} 