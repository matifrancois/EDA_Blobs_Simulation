#include "Simulation.h"
#include "Graph.h"

Simulation::Simulation()
{
	maxX = WIDTH ;
	maxY = TAMANIO_PANTALLA_Y;
	foodNum = 0.0;
	alphaSpeed = 0.0;
	smellRadius = 0.0;
	randomJiggleLimit = 0.0;
	babyDeathProb = 0.0;
	grownDeathProb =0.0 ;
	goodDeathProb =0.0 ;
	mode = 0;
	blobNum = 0;
	bellToll = COUNT;
	tick = 0;
}


Simulation::~Simulation()
{
}

void Simulation:: Simulate(Graph& myGUI) 
{
	tick++;
	bellToll--;
	getData(myGUI);                           //fijate que una de estas funciones hace q los blobs desaparezcan
    gameLoop();
}

bool Simulation::generateFood(int newFood)
{
	bool res = true;
	for (int i = 0; i < newFood; i++)
	{
		foodPtr[(i)] = new (nothrow) Food(maxX, maxY);
		if (foodPtr[(i)]==nullptr)
		{
			res = false;
		}
	}
	return res;
}


bool Simulation::generateBlobs(int blobNum)
{
	bool result = true;
	double maxSpeed_;
	for (int i = 0; i < blobNum; i++)
	{
		if (mode == 1) 
		{
			maxSpeed_ = maxSpeed;
		}
		else 
		{
			maxSpeed_ = randBetweenReal(0.0, maxSpeed);
		}
		blobPtr[i] = new (nothrow) BabyBlob(maxX, maxY, maxSpeed_, alphaSpeed, smellRadius, babyDeathProb);
		if (blobPtr[i] == nullptr)
		{
			result = false;
		}
	}
	return result;
}




void Simulation::firstData(Graph& myGUI)
{
	maxX = TAMANIO_PANTALLA_X;			//Se complete los valores iniciales en la simulación
	maxY = TAMANIO_PANTALLA_Y-BACKG_Y;
	mode = myGUI.getModo();
	blobNum = myGUI.getBlobNum();
	foodNum = myGUI.getFoodCount();
	maxSpeed = myGUI.getMaxSpeed();
	alphaSpeed = myGUI.getVelp();
	babyDeathProb = myGUI.getDead(0);
	grownDeathProb = myGUI.getDead(1);
	goodDeathProb = myGUI.getDead(2);
	smellRadius = myGUI.getSmellRadius();
	randomJiggleLimit = myGUI.getRJL();
}




void Simulation::getData(Graph& myGUI)	//Recupera los datos que haya modificado el usuario.
{
	int newFood = 0;
	double maxSpeed_;

	for (int i = 0; i < blobNum; i++)
	{
		if ((blobPtr[i]->getGroup()) == BABYGROUP)		//primero seteo la probabilidad de muerte según grupo etario.
		{
			blobPtr[i]->setDeadProb(myGUI.getDead(0));
		}

		if ((blobPtr[i]->getGroup()) == GROWNGROUP)
		{
			blobPtr[i]->setDeadProb(myGUI.getDead(1));

		}

		if ((blobPtr[i]->getGroup()) == GOODOLDGROUP)
		{
			blobPtr[i]->setDeadProb(myGUI.getDead(2));
		}

		if (mode == 1) {							//ajusto la velocidad máxima según modo de juego.
			maxSpeed_ = myGUI.getMaxSpeed();
		}
		else {
			maxSpeed_ = randBetweenReal(0.0, myGUI.getMaxSpeed());
		}

		blobPtr[i]->setMaxSpeed(maxSpeed_);			//Actualizo velocidad máxima
		blobPtr[i]->setAlphaSpeed(myGUI.getVelp());		//Ajusta velocidad porcentual y smellRadius.
		blobPtr[i]->setRadius(myGUI.getSmellRadius());
	}

	newFood = myGUI.getFoodCount();		//agrego o quito comida según corresponda.
	if (newFood >= foodNum)
	{
		addFood(newFood - foodNum);
	}
	if (newFood < foodNum)
	{
		delFood(foodNum - newFood);
	}

	babyDeathProb = myGUI.getDead(0);	//Ajusto los parámetros dead en la simulación.
	grownDeathProb = myGUI.getDead(1);
	goodDeathProb = myGUI.getDead(2);
}




void Simulation::blobDeath(void)
{
	for (int i = 0; i < blobNum; i++)

		if (blobPtr[i]->blobFate())	//se decide si un blob debe morir o no.
		{
			clearBlob(i);	//si debe morir, se elimina del arreglo y se ajusta éste de forma que blobNum sea la primera posición libre.
			i--;
		}
}


void Simulation::blobBirth(void)
{
	double maxSpeed_;
	int birthNum = 0;	//cantidad de nacimientos
	for (int i = 0; i < blobNum; i++)
	{
		if (blobPtr[i]->isBlobFull())	//verifica que el blob esté lleno.
		{
			if (mode == 1) {
				maxSpeed_ = maxSpeed; 
			}
			else { 
				maxSpeed_ = randBetweenReal(0.0, maxSpeed); 
			}
			blobPtr[blobNum + birthNum] = new BabyBlob(maxX, maxY, maxSpeed_, alphaSpeed, smellRadius, babyDeathProb);	//si lo está, se genera un BbyBlob en una posición aleatoria.
			birthNum++;
		}
	}
	blobNum += birthNum;	//se ajusta la cantidad de blobs totales en el tablero.
}

void Simulation::clearBlob(int i)
{
	delete blobPtr[i];
	for (int j = i; j<(blobNum - 1); j++)
	{
		blobPtr[j] = blobPtr[j + 1];
	}
	blobNum--;
}

void Simulation::blobMerge(void)
{
	sound = NOT_SOUND;
	double addRandom, distance;
	int totalMerges = 0;			//cantidad de merges para luego calcular el promedio de la dirección y velocidad.
	for (int i = 0; i < blobNum; i++)
	{
		if (!((blobPtr[i]->getGroup()) == GOODOLDGROUP))		//revisa que el blob no sea uno de tipo GoodOldBlob.
		{
			for (int j = i+1; j < blobNum; j++)				//compara con los otros blobs en el arreglo.
			{
				if ((blobPtr[i]->getGroup()) == (blobPtr[j]->getGroup()))	//revisa que los blobs sean del mismo grupo etario
				{
					distance = getDistance(blobPtr[i]->getX(), blobPtr[j]->getX(), blobPtr[i]->getY(), blobPtr[j]->getY());
					if (distance < ((blobPtr[i]->getcolissionRadius()) * 2.0))
					{					
						blobPtr[i]->setDir((blobPtr[i]->getDir()) + (blobPtr[j]->getDir()));	//la idea es agrupar los datos del nuevo Blob en blob[i] para luego generarlo.
						blobPtr[i]->setMaxSpeed((blobPtr[i]->getMaxSpeed()) + (blobPtr[j]->getMaxSpeed()));	//se agrupan dirección, velocidad máxmima, y velocidad relativa.
						blobPtr[i]->setAlphaSpeed((blobPtr[i]->getAlphaSpeed()) + (blobPtr[j]->getAlphaSpeed()));
						totalMerges++;
						clearBlob(j);		//una vez que se recuperaron los datos del blob[j], como en la fusión desaparecen los involucrados, podemos eliminar a j ahora
						j--;	//al haberse ajustado el arreglo en clearBlob (disminuyendo en 1 el total), es necesario reducir j en uno para continuar con el for correctamente.
					}
				}
			}
			if (totalMerges > 0) //si hubo algún merge se calcula la dirección y velocidad del nuevo blob.
			{
				sound = MUST_SOUND;
				addRandom = randBetweenReal(0.0, randomJiggleLimit);	//genero el ángulo aleatorio con JiggleLimit
				addRandom = ((addRandom*PI) / 180);						//lo convierto a radianes.
				blobPtr[i]->setDir(((blobPtr[i]->getDir()) / totalMerges) + addRandom);	//se genera la nueva dirección haciendo el promedio y luego sumándole randomJiggleLimit;
				blobPtr[i]->setMaxSpeed((blobPtr[i]->getMaxSpeed()) / totalMerges);	//de forma análoga, se calcula la nueva velocidad máxima y relativa como el promedio de las anteriores.
				blobPtr[i]->setAlphaSpeed((blobPtr[i]->getAlphaSpeed()) / totalMerges);
				blobPtr[i]->setMergeStatus(true);	//se indica que este blob debe dividirse.
				totalMerges = 0;
			}
		}
	}
	blobDivide();	//genera las divisiones de blobs necesarias.
}

void Simulation::blobDivide(void)
{
	double maxSpeed_, alphaSpeed_, dir_,  mergex, mergey;
	for (int i = 0; i < blobNum; i++)
	{
		if (blobPtr[i]->getMergeStatus())	//se fija si es necesario crear un nuevo blob.
		{
			if (mode == 1) {
				maxSpeed_ = blobPtr[i]->getMaxSpeed();
			}
			else {
				maxSpeed_ = randBetweenReal(0.0,blobPtr[i]->getMaxSpeed());
			}
			alphaSpeed_ = blobPtr[i]->getAlphaSpeed();	//recupero las características del Blob resultante.
			dir_ = blobPtr[i]->getDir();
			mergex = blobPtr[i]->getX();
			mergey = blobPtr[i]->getY();

			switch (blobPtr[i]->getGroup())	//según el grupo de blob, crea un grownblob o un goodoldblob
			{
			case BABYGROUP:

				clearBlob(i);	//el blob que se divide es eliminado, y se agrega otro en la última posición del arreglo disponible.
				i--;
				blobPtr[blobNum] = new GrownBlob(mergex, mergey, maxSpeed_, alphaSpeed_, dir_, smellRadius, grownDeathProb);
				blobNum++;
				break;
			case GROWNGROUP:
				clearBlob(i);	//De forma similar si se trata de colisiones de GrownBlobs.
				i--;
				blobPtr[blobNum] = new GoodOldBlob(mergex, mergey, maxSpeed_, alphaSpeed_, dir_, smellRadius, grownDeathProb);
				blobNum++;
				break;
			default:
				break;
			}
		}
	}
}



void Simulation::addFood(int newFood)
{
	for (int i = 0; i < newFood; i++)
	{
		foodPtr[(foodNum + i)] = new Food(maxX, maxY);
	}
	foodNum += newFood;
}

void Simulation::delFood(int total)
{	
		int remainder = foodNum - total;
		for (int i = remainder; i < foodNum; i++) 
		{
			delete foodPtr[i];

		}
		foodNum = remainder;
}

void Simulation::gameLoop(void)	//Ciclo de juego
{
	int i = 0;
	
	//Revisa si algún blob debe morir por el fenómeno de blobDeath. Sólo se usa cada 100 'ticks'.
	if (bellToll==0)
	{
		blobDeath();
		bellToll = COUNT;
	}	

	//Cada blob busca la comida más cercana y actualiza su dirección, pero No se mueve.
	for (i = 0; i < blobNum; i++)
	{
		blobPtr[i]->check_for_food(foodPtr, foodNum);
	}

	//Los blobs se mueven a su nueva posición
	for (i = 0; i < blobNum; i++)
	{
		blobPtr[i]->newPositions(maxX, maxY);
		blobPtr[i]->moveBlob();
	}

	//Se revisa cuáles blobs están en posición para comer comida.
	for (i = 0; i < blobNum; i++)
	{
		blobPtr[i]->blobEat(foodPtr, foodNum);
	}

	//Regenera la comida que haya sido consumida por los blobs en una posición aleatoria
	for (i = 0; i < foodNum; i++)
	{
		if ((foodPtr[i]->getFoodStatus()) == true)
		{
			foodPtr[i]->newFood(maxX, maxY);
			foodPtr[i]->setFoodStatus(false);
		}
	}

	//Se revisa si hay instancias de blobBirth.
	blobBirth();

	//Revisa si hay colisiones de blobs
	blobMerge();

}

