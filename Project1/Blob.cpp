#include "Blob.h"

/*Constructors*/
Blob::Blob()
{
}

Blob::
Blob(double maxX, double maxY, double maxSpeed_, double alphaSpeed_, double radius_, double deathProb_) //Constructor
{
	x = randBetweenReal(0,maxX);
	y = randBetweenReal(MIN_PRINTABLE_POIN_Y,maxY);
	dir = randomDir();
	radius = radius_;
	maxSpeed =maxSpeed_;
	alphaSpeed = alphaSpeed_;
	speed = maxSpeed_*alphaSpeed_/100.0;
	newx = 0.0;
	newy = 0.0;
	newdir = randomDir();
	foodEaten = 0;
	group = 1;
	colissionRadius = 0.0;
	deathProb = deathProb_;
	isFull = false;
	willDie = false;
	willMerge = false;
}
Blob::Blob(const Blob& copyBlob) //Constructor copiador
{

}

/*Destructors*/
Blob::~Blob()
{
}

/*Getters*/
double Blob::getX(void)
{
	return x;
}

double Blob::getY(void)
{
	return y;
}

double Blob::getNewx(void)
{
	return newx;
}

double Blob::getNewy(void)
{
	return newy;
}

double Blob::getMaxSpeed(void)
{
	return maxSpeed;
}

double Blob::getAlphaSpeed(void)
{
	return alphaSpeed;
}

double Blob::getSpeed(void)
{
	return speed;
}

double Blob::getDir(void)
{
	return dir;
}

double Blob::getNewdir(void)
{
	return newdir;
}

double Blob::getRadius(void)
{
	return radius;
}

double Blob::getcolissionRadius(void)
{
	return colissionRadius;
}

double Blob::getDeathProb(void)
{
	return deathProb;
}

double Blob::getFoodEaten(void)
{
	return foodEaten;
}

double Blob::getMaxFood(void)
{
	return maxFood;
}

bool Blob::getFullness(void)
{
	return isFull;
}

bool Blob::getDeathStatus(void)
{
	return willDie;
}

bool Blob::getMergeStatus(void)
{
	return willMerge;
}

int Blob::getGroup(void)
{
	return group;
}


/*Setters*/

void Blob::setX(double a)
{
	x = a;
}

void Blob::setY(double b)
{
	y = b;
}

void Blob::setRadius(double r)
{
	radius = r;
}

void Blob::setMaxSpeed(double s)
{
	maxSpeed = s;
}

void Blob::setAlphaSpeed(double s)
{
	alphaSpeed = s;
}

void Blob::setDir(double k)
{
	dir = k;
}

void Blob::setNewDir(double d)
{
	newdir = d;
}

void Blob::setDeadProb(double j)
{
	deathProb = j;
}

void Blob::setFoodEaten(int f)
{
	foodEaten = f;
}

void Blob::setFullness(bool x)
{
	isFull = x;
}

void Blob::setGroup(int g)
{
	group = g;
}

void Blob::setDeathStatus(bool d)
{
	willDie = d;
}

void Blob::setMergeStatus(bool s)
{
	willMerge = s;
}

/*Funciones*/
void Blob::newPositions(double maxX, double maxY)	//actualiza las posiciones futuras en base a la nueva dirección
{
	double speed = maxSpeed*alphaSpeed;
	double ndir = rand() % 360;
	
	double nx = x + speed*cos(newdir);
	double ny = y + speed*sin(newdir);
	if (nx >= maxX) 
	{
		nx -= maxX;
	}
	if (nx <= 0)
	{
		nx += maxX;
	}
	if (ny >= maxY)
	{
		ny -= maxY;
	}
	if (ny <= 0)
	{
		ny += maxY;
	}
	newx = nx;
	newy = ny;
}

bool Blob::blobFate(void)
{
	double unluckynum = normalRand();
	if (unluckynum < getDeathProb())
	{
		return true;
	}
	else return false;
}

void Blob::moveBlob(void)
{
	x = newx;
	y = newy;
	dir = newdir;
}

void Blob::blobEat(Food **foodPtr, int foodNum)	//revisa si puede comer alguna comida.
{
	double distance;
	for (int i = 0; i < foodNum; i++)
	{
		distance = getDistance(getX(), foodPtr[i]->getFoodPosX(), getY(), foodPtr[i]->getFoodPosY());
		if (distance < (getcolissionRadius()) / 2)
		{
			foodEaten++;
			foodPtr[i]->setFoodStatus(true);	//marca el alimento como comida para luego reponerlo en otro lado.
		}
	}

}

bool Blob::isBlobFull(void)		//revisa si un blob superó su límite de comida.
{
	if (foodEaten >= maxFood)
	{
		foodEaten = 0;
		return true;
	}
	else return false;
}


void Blob::check_for_food(Food **foodPtr, int foodNum)	//revisa si hay comida cerca y, si la hay, actualiza su posición.
{
	double closest_food = MAXDISTANCE;
	double closest_x, closest_y;

	for (int i = 0; i < foodNum; i++)
	{
		double food_distance = getDistance(getX(), foodPtr[i]->getFoodPosX(), getY(), foodPtr[i]->getFoodPosY());
		if (food_distance < getRadius())
		{
			if (food_distance < closest_food)	
			{
				closest_food = food_distance;
				closest_x = foodPtr[i]->getFoodPosX();
				closest_y = foodPtr[i]->getFoodPosY();
			}
		}
	}
	if (closest_food < MAXDISTANCE)
	{
		double angle = atan2(closest_y - getY(), closest_x - getX());
		
		

		setNewDir(angle);	
	}
}
