#include "Food.h"



Food::Food()
{
	foodx = 0.0;
	foody = 0.0;
	foodRadius = FOODRADIUS;
}


Food::~Food()
{
}

Food::Food(double maxX, double maxY)		//inicializa un objeto comida en una posición aleatoria dentro de los límites de juego.
{
	foodx = randBetweenReal(0.0, maxX);
	foody = randBetweenReal(MIN_PRINTABLE_POIN_Y, maxY);
	foodRadius = FOODRADIUS;
	isFoodEaten = false;
}


/*Getters*/
double Food::getFoodPosX(void)
{
	return foodx;
}

double Food::getFoodPosY(void)
{
	return foody;
}

double Food::getFoodRadius(void)
{
	return foodRadius;
}

bool Food::getFoodStatus(void)
{
	return isFoodEaten;
}

/*Setters*/
void Food::setFoodPosX(double a)
{
	foodx = a;
}

void Food::setFoodPosY(double b)
{
	foody = b;
}

void Food::setFoodStatus(bool z)
{
	isFoodEaten = z;
}

void Food::newFood(double maxX, double maxY)
{
	foodx = randBetweenReal(0.0, maxX);
	foody = randBetweenReal(0.0, maxY);

}

