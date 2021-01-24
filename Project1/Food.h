#ifndef FOOD_H_
#define FOOD_H_

/**********************************
INCLUDE
**********************************/
#include "prototype.h"


/**********************************
DEFINE
**********************************/
#define FOODRADIUS 10.0


/**********************************
CLASS
**********************************/
class Food
{
public:
	Food();
	Food(double maxX, double maxY);
	~Food();

	/*Getters*/
	double getFoodPosX(void);
	double getFoodPosY(void);
	double getFoodRadius(void);
	bool getFoodStatus(void);

	/*Setters*/
	void setFoodPosX(double a);
	void setFoodPosY(double b);
	void setFoodStatus(bool z);

	void newFood(double maxX, double maxY); //crea una nueva comida para el objeto Food que fue comido

private:
	double foodx;
	double foody;
	double foodRadius;
	bool isFoodEaten;
};



#endif // !FOOD_H_
