#include "GoodOldBlob.h"



GoodOldBlob::GoodOldBlob()
{
}

GoodOldBlob::GoodOldBlob(double maxX, double maxY, double maxSpeed_, double alphaSpeed_, double radius_, double deathProb_) :

	Blob(maxX, maxY, maxSpeed_, alphaSpeed_, radius_, deathProb_)
{
	maxFood = GOODOLDMAXFOOD;
	colissionRadius = GOODOLDRADIUS;
	group = GOODOLDGROUP;
}

GoodOldBlob::GoodOldBlob(double x_, double y_, double maxSpeed_, double alphaSpeed_, double dir_, double radius_, double deathProb_)
{
	x = x_;
	y = y_;
	newx = 0.0;
	newy = 0.0;
	maxSpeed = maxSpeed_;
	alphaSpeed = alphaSpeed_;
	dir = dir_;
	maxFood = GOODOLDMAXFOOD;
	speed = maxSpeed_*alphaSpeed_;
	radius = radius_;
	group = GOODOLDGROUP;
	foodEaten = 0;
	colissionRadius = GOODOLDRADIUS;
	isFull = false;
	willDie = false;
	willMerge = false;
	deathProb = deathProb_;
}


GoodOldBlob::~GoodOldBlob()
{
}
