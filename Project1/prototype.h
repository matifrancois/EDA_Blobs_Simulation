#ifndef PROTOTYPE_H_
#define PROTOTYPE_H_

/**********************************
DEFINE
**********************************/
#define MAXDISTANCE 2000
#define PI 3.14159265359
#define HEIGHT 550.0
#define WIDTH 1200.0

#define FOODRADIUS 10.0
#define BABYRADIUS 20.0
#define GROWNRADIUS 21.5
#define GOODOLDRADIUS 40.0
#define TAMANIO_PANTALLA_X_ENTRADA 600
#define TAMANIO_PANTALLA_Y_ENTRADA 400
#define TAMANIO_PANTALLA_X 1200.0
#define TAMANIO_PANTALLA_Y 800.0
#define MIN_PRINTABLE_POIN_Y 250
#define MAX_FOOD 1000
#define FOOD_COUNT_INICIAL 5
#define PROBABILIDAD_MUERTE_BABY 0.002f
#define PROBABILIDAD_MUERTE_GROWN 0.004f
#define PROBABILIDAD_MUERTE_OLD 0.008f
#define PORCENTAJE_INICIAL_VEL 50.0f
#define SMELLRADIUS_INICIAL 150.0f
#define DIR_INICIAL 0.0f
#define BACKG_Y  250.0f
#define BACKG_X 0.0f
#define INIC_VEL 0.01
#define INIC_BLOBS 3
#define MUST_SOUND 1
#define NOT_SOUND 0

typedef unsigned int uint;

using namespace std;

/**********************************
INCLUDE
**********************************/
#include<iostream>
#include <ctime>
#include <cstdlib>
#include <stdint.h>
#include <cstdio>
#include <string>
#include <stdarg.h>
#include <cstring>
#include <vector>
#include <new>
#include <fstream>


/**********************************
FUNCTIONS
**********************************/
double getDistance(double x1, double x2, double y1, double y2); //obtiene la distancia entre dos puntos
int randBetween(int a, int b); //regresa un número aleatorio entre a y b
double normalRand(void); //regresa un número aleatorio entre cero y uno
double randBetweenReal(double a, double b);  //regresa un double entre dos valores especificados
double randomDir(void);
void setSeed(void);



#endif // !PROTOTYPE_H_
