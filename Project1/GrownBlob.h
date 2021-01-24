#pragma once
#include "Blob.h"

/**********************************
DEFINE
**********************************/
#define GROWNMAXFOOD 4
#define GROWNRADIUS 22.5

/**********************************
CLASS
**********************************/
class GrownBlob :
	public Blob
{
public:
	GrownBlob();
	GrownBlob(double maxX, double maxY, double maxSpeed_, double alphaSpeed_, double radius_, double deathProb_);

	//Constructor para blobMerge
	GrownBlob(double x_, double y_, double maxSpeed_, double alphaSpeed_, double dir_, double radius_, double deathProb_);
	
	//Destructor
	~GrownBlob();
};

