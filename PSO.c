#include "PSO.h"

/* Asignación dinámica para enjambre */
SWARM* CreateSwarm(unsigned int nParticles, unsigned int nParams)
{
	unsigned int k;
	SWARM *ptr;

	ptr = (SWARM*)malloc(sizeof(SWARM));
	if (ptr == NULL)
	{
		printf("Error al asignar Memoria a la estructura Swarmambre");
		exit(-1);
	}

	/*
	* Inicializar la estructura
	*/
	ptr->nParticles = nParticles;
	ptr->nParams = nParams;

	/* Asignar memoria a las partículas */
	// Primero para estructuras mas externas y luego para las internas
	ptr->Swarm = (PARTICLE*)malloc(sizeof(PARTICLE)*nParticles);
	if (ptr->Swarm == NULL)
	{
		printf("Error al asignar Memoria a PARTICLEs");
		exit(-1);
	}

	// Asignar memoria a cada PARTICLE
	for (k = 0; k < nParticles; k++)
	{
		ptr->Swarm[k].Xi = (float*)malloc(sizeof(float)*nParams);
		ptr->Swarm[k].Vi = (float*)malloc(sizeof(float)*nParams);
		ptr->Swarm[k].Pi = (float*)malloc(sizeof(float)*nParams);
	}

	return ptr;
}

void SetupSWARM(SWARM *pSwarm,const float lowLimit,const float highLimit,const float c1,const float c2,const float vmin,const float vmax)
{
	unsigned int i, k;
	float r;
	r = 0;

	for (i = 0; i < pSwarm->nParticles; i++)
	{
		for (k = 0; k < pSwarm->nParams; k++)
		{
			r = ((double)rand() / RAND_MAX)*(highLimit - lowLimit) + lowLimit;
			pSwarm->Swarm[i].Xi[k] = (int)r;
			pSwarm->Swarm[i].Vi[k] = 0;
			pSwarm->Swarm[i].Pi[k] = (int)r;
		}
		pSwarm->c1 = c1;
		pSwarm->c2 = c2;
    pSwarm->Vmax=vmax;
    pSwarm->Vmin=vmin;
	}
}

void SetupBest(SWARM *pSwarm)
{
	unsigned int i;
	float best;

	best = pSwarm->Swarm[0].XFit;
	for(i=0; i < pSwarm->nParticles; i++)
	{
		pSwarm->Swarm[i].PFit = pSwarm->Swarm[i].XFit;
		if (pSwarm->Swarm[i].PFit > best)
		{
			pSwarm->idGbest = i;
			best = pSwarm->Swarm[i].PFit;
		}
	}
}

void EvaluateSWARM(SWARM *pSwarm, VECTORS vector, gcIMG *img)
{
	unsigned int index;
	float ang;
	float matchCircle;
	unsigned int i;
	unsigned int j;
	unsigned int k;
	unsigned int x;
	unsigned int y;
	unsigned int centerX;
	unsigned int centerY;
	unsigned int radius;

	matchCircle = 0;

	// Evaluate cada Partícula
	for (index = 0; index < 1; index++) {
		i = pSwarm->Swarm[index].Xi[0];
		j = pSwarm->Swarm[index].Xi[1];
		k = pSwarm->Swarm[index].Xi[2];

		//centerX = CenterCoordinateX(vector, i, j, k);
		//centerY = CenterCoordinateY(vector, i, j, k);
		//radius = CircleRadius(vector, centerX, centerY, i);
		radius = 200;
		centerX = 400;
		centerY = 400;

		for(ang=0; ang < 360; ang += 0.001) {
			x = (int)radius*cos(ang*(PI/180)) + centerX;
			y = (int)radius*sin(ang*(PI/180)) + centerY;

			if(img->imx[x*(img->ancho + y)] < 150)
				matchCircle += 0.001;

			//img->imx[x*(img->ancho + y)] = 255;

		}
		//gcPutImgBmp("prueba.bmp", img);
		printf("MATCH: %f\n", matchCircle);
	}
}

void UpdateSpeed(SWARM *pSwarm)
{
	unsigned int i;
	unsigned int j;
	float y1;
	float y2;
    float aux;

	// Para todas las partículas
	for (i = 0; i < pSwarm->nParticles; i++)
	{
		// Para todos los parámetros
		for (j = 0; j < pSwarm->nParams; j++)
		{
			y1 = ((float)rand() / RAND_MAX);
			y2 = ((float)rand() / RAND_MAX);
			//pSwarm->Swarm[i].Vi[j] += (pSwarm->c1)*y1*(pSwarm->Swarm[i].Pi[j] - pSwarm->Swarm[i].Xi[j]) +
			//			(pSwarm->c2)*y2*(pSwarm->Swarm[pSwarm->idGbest].Pi[j] - pSwarm->Swarm[i].Xi[j]);
            aux = pSwarm->Swarm[i].Vi[j] + (pSwarm->c1)*y1*(pSwarm->Swarm[i].Pi[j] - pSwarm->Swarm[i].Xi[j]) +
						(pSwarm->c2)*y2*(pSwarm->Swarm[pSwarm->idGbest].Pi[j] - pSwarm->Swarm[i].Xi[j]);
            if(aux>pSwarm->Vmax)
            {
                pSwarm->Swarm[i].Vi[j] = pSwarm->Vmax;
                break;
            }
            if(aux<pSwarm->Vmin)
            {
                pSwarm->Swarm[i].Vi[j] = pSwarm->Vmin;
                break;
            }
		}
	}
}

void UpdatePosition(SWARM *pSwarm)
{
	unsigned int i;
	unsigned int j;

	// Para todas las partículas
	for (i = 0; i < pSwarm->nParticles; i++)
	{
		// Para todos los parámetros
		for (j = 0; j < pSwarm->nParams; j++)
		{
			pSwarm->Swarm[i].Xi[j] += pSwarm->Swarm[i].Vi[j];
		}
	}
}

void UpdateBest(SWARM *pSwarm)
{
	unsigned int i,j;
	float best;
	best = pSwarm->Swarm[pSwarm->idGbest].PFit;

	for(i=0; i < pSwarm->nParticles; i++)
	{
		if(pSwarm->Swarm[i].XFit > pSwarm->Swarm[i].PFit)
		{
			for(j = 0; j < pSwarm->nParams; j++)
			{
				pSwarm->Swarm[i].Pi[j] = pSwarm->Swarm[i].Xi[j];
				pSwarm->Swarm[i].PFit = pSwarm->Swarm[i].XFit;
			}
		}
		if (pSwarm->Swarm[i].PFit > best)
		{
			pSwarm->idGbest = i;
			best = pSwarm->Swarm[i].PFit;
		}
	}
}


void ShowPARTICLE(SWARM *pSwarm, const int i)
{
	unsigned int k;

	printf("\n\n X%u:\t", i);
	for (k = 0; k < pSwarm->nParams; k++)
		printf("%2.4f\t", pSwarm->Swarm[i].Xi[k]);

	printf("\n V%u:\t", i);
	for (k = 0; k < pSwarm->nParams; k++)
		printf("%2.4f\t", pSwarm->Swarm[i].Vi[k]);

	/*printf("\n P%u:\t", i);
	for (k = 0; k < pSwarm->nParams; k++)
		printf("%2.4f\t", pSwarm->Swarm[i].Pi[k]);

	printf("\n xFit = %f", pSwarm->Swarm[i].XFit);
	printf("\n xPit = %f", pSwarm->Swarm[i].PFit);*/
}

void ShowSWARM(SWARM *pSwarm)
{
	unsigned int i;

	for (i = 0; i < pSwarm->nParticles; i++)
		ShowPARTICLE(pSwarm, i);
}

void FreeSWARM(SWARM *pSwarm)
{
	unsigned int k;

	// Liberar memoria para todos los parametros de cada PARTICLE
	for (k = 0; k < pSwarm->nParticles; k++)
	{
		free(pSwarm->Swarm[k].Xi);
		free(pSwarm->Swarm[k].Vi);
		free(pSwarm->Swarm[k].Pi);
	}

	// Liberar memoria de PARTICLEs
	free(pSwarm->Swarm);
	// Liberar memoria de SWARM
	free(pSwarm);
}
