#include "GrownBlob.h"



GrownBlob::GrownBlob()
{
}

GrownBlob::GrownBlob(double maxX, double maxY, double maxSpeed_, double alphaSpeed_, double radius_, double deathProb_):
	
	Blob(maxX, maxY, maxSpeed_, alphaSpeed_, radius_, deathProb_)
{
	maxFood = GROWNMAXFOOD;
	colissionRadius = GROWNRADIUS;
	group = GROWNGROUP;
}

GrownBlob::GrownBlob(double x_, double y_, double maxSpeed_, double alphaSpeed_, double dir_, double radius_, double deathProb_)
{
	x = x_;
	y = y_;
	newx = 0.0;
	newy = 0.0;
	maxSpeed = maxSpeed_;
	alphaSpeed = alphaSpeed_;
	dir = dir_;
	maxFood = GROWNMAXFOOD;
	speed = maxSpeed_*alphaSpeed_;
	radius = radius_;
	group = GROWNGROUP;
	foodEaten = 0;
	colissionRadius = GROWNRADIUS;
	isFull = false;
	willDie = false;
	willMerge = false;
	deathProb = deathProb_;

}



GrownBlob::~GrownBlob()
{
}
