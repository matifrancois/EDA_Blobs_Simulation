#ifndef SIM_H_
#define SIM_H_

/**********************************
INCLUDE
**********************************/
#include "Blob.h"
#include "BabyBlob.h"
#include "GrownBlob.h"
#include "GoodOldBlob.h"
class Graph;

/**********************************
DEFINE
**********************************/
#define MAXBLOBS 10000
#define MAXFOOD 1000
#define COUNT 100	//Indica la cantidad de ciclos hasta que se active blobdeath.

#define default_maxX 1000.0
#define default_maxY 500.0
#define default_blobNum 1
#define default_maxSpeed 0.0
#define default_alphaSpeed 0.0
#define defaultMode 1
#define default_foodNum 0
#define default_smellRadius 0.0
#define defaultMode 1
#define default_deathProb 0.0
#define default_randomJiggleLimit 0
#define default_deathProb 0.0

/**********************************
CLASS
**********************************/

class Simulation
{
public:
	Simulation();   //Constructor de simulación inicial.
	
	~Simulation();

	/*Inicializar blobs y food*/
	bool generateFood(int newFood);	//genera la cantidad de comida inicial
	bool generateBlobs(int blobNum);	//genera los babyBlobs iniciales en posiciones aleatorias.
	void Simulate(Graph& myGUI);
	
	/*Completar y recuperar datos*/
	void firstData(Graph& myGUI);	//Recupera los datos de inicio del juego
	void getData(Graph& myGUI);		//Recupera los datos para el nuevo ciclo.
										
										
	/*Revisar nacimientos y muertes*/
	void blobDeath(void);	//Elimina a los blobs por probabilidad de muerte.
	void blobBirth(void);	//crea nuevos blobs.
	void clearBlob(int i);	//elimina a un blob del arreglo de blobs y luego ajusta el arreglo acorde a la eliminación, de forma que blobNum siempre apunte al primer lugar libre para crear un blob.
	void blobMerge(void);	//revisa si hay blobs que se deban mezclar.
	void blobDivide(void);	//crea al nuevo blob por división y elimina al padre


	/*Agrega y elimina comida*/
	void addFood(int newFood);
	void delFood(int total);

	/*Inicia un ciclo de juego*/
	void gameLoop(void);

	
	Blob *blobPtr[MAXBLOBS];	//contiene los punteros a los distintos blobs en el tablero.
	Food *foodPtr[MAXFOOD];		//contiene los punteros a las distintas comidas en el juego.
	int blobNum;
	int sound;
	int foodNum;
	int mode;
	int tick;
	double babyDeathProb;
	double grownDeathProb;
	double goodDeathProb;
	double maxX;
	double maxY;
	double maxSpeed;
	double alphaSpeed;
	double randomJiggleLimit;
	double smellRadius;
	int bellToll;

};



#endif // !SIM_H_