#pragma once
#include "Blob.h"

/**********************************
DEFINE
**********************************/
#define GOODOLDMAXFOOD 3
#define GOODOLDRADIUS 40.0

/**********************************
CLASS
**********************************/
class GoodOldBlob :
	public Blob
{
public:
	GoodOldBlob();
	GoodOldBlob(double maxX, double maxY, double maxSpeed_, double alphaSpeed_, double radius_, double deathProb_);

	/*Constructor para el merge*/
	GoodOldBlob(double x_, double y_, double maxSpeed_, double alphaSpeed_, double dir_, double radius_, double deathProb_);
	

	/*Destructor*/
	~GoodOldBlob();
};

