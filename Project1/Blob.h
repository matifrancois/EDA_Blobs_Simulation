#ifndef BLOB_H_
#define BLOB_H_


/**********************************
INCLUDE
**********************************/
#include "Food.h"


/**********************************
DEFINE
**********************************/
#define BABYGROUP 1
#define GROWNGROUP 2
#define GOODOLDGROUP 3

/**********************************
CLASS
**********************************/
class Blob
{
public:
	Blob();
	Blob(double maxX, double maxY, double maxSpeed_, double alphaSpeed_, double radius_, double deathProb_);
	Blob(const Blob& copyBlob);
	~Blob();

	/*Getters*/
	double getX(void);
	double getY(void);
	double getNewx(void);
	double getNewy(void);
	double getMaxSpeed(void);
	double getAlphaSpeed(void);
	double getSpeed(void);
	double getDir(void);
	double getNewdir(void);
	double getRadius(void);
	double getcolissionRadius(void);
	double getDeathProb(void);
	double getFoodEaten(void);
	double getMaxFood(void);
	bool getFullness(void);
	bool getDeathStatus(void);
	bool getMergeStatus(void);
	int getGroup(void);

	/*Setters*/
	void setX(double a);
	void setY(double b);
	void setRadius(double r);
	void setMaxSpeed(double s);
	void setAlphaSpeed(double s);
	void setDir(double k);
	void setNewDir(double d);
	void setDeadProb(double j);
	void setFoodEaten(int f);
	void setFullness(bool x);
	void setGroup(int g);
	void setDeathStatus(bool d);
	void setMergeStatus(bool s);

	/*Funciones*/
	void check_for_food(Food **foodPtr, int foodNum); //revisa cuál es la comida más cercana y actualiza la dirección.
	void newPositions(double maxX, double maxY);	//en base a la nueva dirección, actualiza las futuras posiciones.
	bool blobFate(void);	//revisa si un blob debe morir en base a deathProb.
	void moveBlob(void); //actualiza la posición del blob y su dirección.
	void blobEat(Food **foodPtr, int foodNum); // revisa si su posición coincide con una comida, y si es así la come.
	bool isBlobFull(void); //revisa si un blob está lo suficientemente lleno para generar un blob bebé


protected:
	double x;
	double y;
	double newx;
	double newy;
	double dir;
	double newdir;
	double radius;
	double maxSpeed;
	double alphaSpeed;
	double speed;
	int foodEaten;
	int maxFood;
	int group;
	double colissionRadius;
	double deathProb;
	bool isFull;
	bool willDie;
	bool willMerge;
};




#endif // !BLOB_H_