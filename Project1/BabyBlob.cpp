#include "BabyBlob.h"



BabyBlob::BabyBlob()
{
}

BabyBlob::BabyBlob(double maxX, double maxY, double maxSpeed_, double alphaSpeed_, double radius_, double deathProb_) :

	Blob(maxX, maxY, maxSpeed_, alphaSpeed_, radius_, deathProb_) //inicializo la parte de la clase padre.

{
	maxFood = BABYMAXFOOD;					//inicializo parámetros cracterísticos de babyblob
	colissionRadius = BABYRADIUS;
	group = BABYGROUP;
}

BabyBlob::BabyBlob(Blob * copyBlob)
{
}



BabyBlob::~BabyBlob()
{
}
