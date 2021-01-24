#include "Simulation.h"
#include "Graph.h"

using namespace std;
int main(void) {

	srand(time(NULL));
	Simulation simPtr;	//se inicializa la simulación.
	
	
		Graph myGUI;	//Objeto que permitirá recuperar información de la GUI.
		if (!(myGUI.get_info()))
		{

			simPtr.firstData(myGUI);					//Recupero los primeros datos (necesarios para iniciar las cosas invariantes)
			simPtr.generateBlobs(simPtr.blobNum);		//genero la cantidad de blobs iniciales
			simPtr.generateFood(simPtr.foodNum);		//genero la cantidad de comida inicial.
			
			while (simPtr.blobNum && !myGUI.getClose())  //siempre que exista algun blob y que no se haya cerrado la pestaña
			{
				if (myGUI.grafica(simPtr) == -1)		// si la funcion grafica devuelve -1 entonce hubo un error dentro de ella
				{
					printf("Error");
					return -1;
				}
			}


		}




	return 0;
}