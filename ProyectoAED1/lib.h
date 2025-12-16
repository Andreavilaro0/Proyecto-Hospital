#pragma once
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <string>

namespace Hospitalnames {
	class Medicamento {
	private:
		int id;
		std::string nombre;
		std::string tipo;
		int cantidad;

	public:
		Medicamento() {};
		//TODO: full constructor

		//TODO: getters and setters
	};

	class Enfermedad {
	private:
		int id;
		std::string nombre;
		int letalidad;
		int urgencia;
		//TODO: full constructor

		//TODO: getters and setters

		//returns letalidad * urgencia (y tal vez algo mas)
		int prioridad();

	};

	class Doctor {
	private:
		int id;
		std::string nombre;
		int dinero;
		std::list<Enfermedad>* pendientes;

	public:
		Doctor() { pendientes = new std::list<Enfermedad>(); };
		 ~Doctor() { delete pendientes; }
		//TODO: full constructor
      Doctor(int _id, std::string _nombre,int _dinero,std::list<Enfermedad>* _pendientes){
		id = _id;
		nombre = _nombre;
		dinero = _dinero;
		pendientes = _pendientes;
	  }
		//TODO: getters and setters
		int getId()const {
			return id;
		}
		std::string getNombre()const{
			return nombre;
		}
		int getDinero()const {
			return dinero;
		}
		std::list<Enfermedad>* getPendientes(){
			return pendientes;
		}

		void setId(int _id){
			id = _id;
		}
		void setNombre(std::string _nombre){
			nombre = _nombre;
		}
		void setPendientes(std::list<Enfermedad>* _pendientes){
			pendientes = _pendientes;
		}

		
		//iterates over pendientes and sums the priority of each Enfermedad to dinero
		//returns the amount received by the Doctor
		// LA IMPLEMENTACION DEBE SER RECURSIVA
		int cobrar();

	};

	class Paciente {
	private:
		int id;
		std::string nombre;
		std::list<Enfermedad>* enfermedades;
		std::stack<std::pair<Enfermedad, Doctor> >* historial;

	public:
		Paciente() { 
			enfermedades = new std::list<Enfermedad>();
			historial = new std::stack<std::pair<Enfermedad, Doctor> >();
		};
		~Paciente() {
			delete enfermedades;
			delete historial;
		}
		//TODO: full constructor
	  Paciente(int _id, std::string _nombre, std::list<Enfermedad>* _enfermedades, std::stack<std::pair<Enfermedad, Doctor> >* _historial){
		id = _id;
		nombre = _nombre;
		enfermedades = _enfermedades;
		historial = _historial;
	  }

		//TODO: getters and setters
		int getId()const {
			return id;
		}

		std::string getNombre()const {
			return nombre;
		}

		std::list<Enfermedad>* getEnfermedades()const{
			return enfermedades;
		}

		std::stack<std::pair<Enfermedad, Doctor> >* getHistorial()const{
			return historial;
		}

		void setId(int _id){
			id = _id;
		}

		void setNombre(std::string _nombre){
			nombre = _nombre;
		}
		void setEnfermedades(std::list<Enfermedad>* _enfermedades){
			enfermedades = _enfermedades;
		}
		void setHistorial(std::stack<std::pair<Enfermedad, Doctor> >* _historial){
			historial = _historial;
		}



	

		//returns the max priority among the patient's illnesses
		int prioridadPaciente();

		//removes the highest priority Enfermedad from enfermedades and stores the pair Enfermedad, Doctor in historial, the most recent on top
		//returns the highest priority Enfermedad
		Enfermedad tratarEnfermedad(Doctor d);

		//ser� invocado cuando un Paciente se haya tratado todas sus Enfermedades
		void darAlta(Doctor d);
	};

	class Hospital {
	private:
		std::queue<Doctor>* doctores;
		std::list<Medicamento>* almacen;
		std::priority_queue<Paciente>* urgencias;

	public:
		Hospital() { 
			doctores = new std::queue<Doctor>(); 
			almacen = new std::list<Medicamento>();
			urgencias = new std::priority_queue<Paciente>();
		};
		~Hospital() {
			delete doctores;
			delete almacen;
			delete urgencias;
		}

		//TODO: full constructor

		Hospital(std::queue<Doctor>* _doctores,std::list<Medicamento>* _almacen,std::priority_queue<Paciente>* _urgencias){
			doctores = _doctores;
			almacen = _almacen;
			urgencias = _urgencias;
		}


		//TODO: getters and setters

		std::queue<Doctor>* getDoctores(){
			return doctores;
		}

		std::list<Medicamento>* getAlmacen(){
		 return almacen;
		}

		std::priority_queue<Paciente>* getUrgencias(){
		return urgencias;
		}

		void setDoctores(std::queue<Doctor>* _doctores){
			doctores = _doctores;
		}
		

		//TODO:insert and remove doctores, medicamentos(in almacen) and pacientes(in urgencias)

		//returns a new list of Medicamento in which for all Medicamento cantidad = k - almacen[j].cantidad 
		//where j is the index that correspond to a certain Medicamento, e.g. "Paracetamol"
		//effectively returning how much units of each Medicamento to buy to replenish the stock
		//Puntos: 1.5
		std::list<Medicamento> reponerStock_k(int k);

		//returns a new list of Medicamento in which for all Medicamento cantidad = nivelesAdecuados[i].cantidad - almacen[j].cantidad
		//where i and j are the indexes that correspond to a certain Medicamento, e.g. "Paracetamol"
		//effectively returning how much units of each Medicamento to buy to replenish the stock
		//Puntos: 1.5
		std::list<Medicamento> reponerStock_niveles(std::list<Medicamento> nivelesAdecuados);

		//returns a pair Doctor, Paciente where the doctor is the first available in the queue doctores and Paciente is the Paciente with the highest priority
		//side effects: the Doctor returned must be extracted from the queue and inserted at the end, simulating the she is treating the Paciente
		//side_effects: the Paciente loses the Enfermedad with higher priority (storing the pair Enfermedad, Doctor ) and is inserted again in urgencias to treat other Enfermedad(es)
		//Puntos: 1.5
		std::pair<Doctor, Paciente> treatPaciente();

		//pays each Doctor the quantity of the priority of the Enfermedades that they treated, for this the Doctor stores a list of unpaid Enfermedades
		//this list should be empty each time the Doctor gets paid
		//returns the total amount paid to all doctors
		// LA IMPLEMENTACION DEBE SER RECURSIVA
		//Puntos: 1.5
		int pagarDoctores();


	};

}
