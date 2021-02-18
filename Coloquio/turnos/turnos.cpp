#include "..\ayedlib\ayed.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <limits>



struct Paciente {
	std::string nombre, apellido;
};


std::ostream &salida(std::ostream &dispositivo_salida = std::cout) {
	static std::ostream &salida = dispositivo_salida;
	return salida;
}



void proximo_paciente(ayed::Cola<Paciente> &turnos, std::ostream &output) {


   if (!turnos.is_vacia()) {   
      salida(output) << "Sr/Sra " << turnos.frente().apellido << ", " << turnos.frente().nombre << std::endl;
      salida(output) << "Pase, por favor" << std::endl;
      turnos.unqueue();    
   } else {
      std::cout << "No hay turnos" << std::endl;
   }
}


Paciente Agregar_Turno() {
   Paciente paciente;
   std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Para ignorar los saltos de linea que se hayan dado antes
   std::cout << "Ingrese el nombre del paciente: ";
   std::getline(std::cin, paciente.nombre);
   std::cout << "Ingrese el apellido del paciente: ";
   std::getline(std::cin, paciente.apellido);
   return paciente;
}




int main()  {

  ayed::Cola<Paciente> turnos;
  char respuesta = 0;
  
  std::ofstream buffer_monitor("buffer_cola.log");
  
  while (respuesta != '5')  {

  std::cout << "Presione: (1) para ingresar un paciente; (3) para llamar al proximo paciente; (5) Para salir" << std::endl;
  std::cin >> respuesta;

     switch (respuesta) {
 
         case '1' :
		turnos.queue(Agregar_Turno()); 
                break;
 
         case '3' : 
		proximo_paciente(turnos, buffer_monitor); 
                break;

	 case '5' :
	        break;

         default: 
	        std::cout << "\nERROR: Comando invalido\n";
		break;
	        

     }
  }
  buffer_monitor.close();
}