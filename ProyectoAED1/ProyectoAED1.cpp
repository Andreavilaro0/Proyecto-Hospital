// ProyectoAED1.cpp: define el punto de entrada de la aplicación.
//

#include "ProyectoAED1.h"


int main()
{
	std::cout << "Hello CMake." << std::endl;
	Hospitalnames::Medicamento* m0 = new Hospitalnames::Medicamento();
	Hospitalnames::Enfermedad* e0 = new Hospitalnames::Enfermedad();
	Hospitalnames::Doctor* d0 = new Hospitalnames::Doctor();
	Hospitalnames::Paciente* p0 = new Hospitalnames::Paciente();
	Hospitalnames::Hospital* hosp = new Hospitalnames::Hospital();


	//free memory
	delete hosp;
	return 0;
}
