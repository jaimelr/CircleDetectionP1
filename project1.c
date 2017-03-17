#include<stdio.h>
#include<stdlib.h>

#define PARTICLES_NUMBER 100 // 50 Este ejemplo en particular
#define PARAMS_NUMBER 2 // Solo se necesitan dos valores para darle solucion al problema
#define LOW_LIMIT 10.0
#define HIGH_LIMIT 0.0
#define ITERATION_LIMIT 250 //100
#define UPPER_SPEED 1.0
#define LOWER_SPEED -1.0

/* La PARTICLE debia estar dividida en tres partes ESTRUCTURA DE LA PARTICLE
 * 1.-posición
 * 2.-Velocidad
 * 3.-Mejor posición
 */

/* PROBLEMA DE EJEMPLO, FUNCION SIMPLE QUE SE MAXIMICE
 * f(x,y)=50-(x-5)^2-(y-5)^2
 */

/* Definición de la estructura SwarmAMBRE */
typedef struct {
	float* Xi; // Posicion
	float* Vi; // Velocidad
	float* Pi; // Mejor posicion
	float XFit; // Posición fitness
	float PFit; // Mejor posición fitness
} PARTICLE;

typedef struct {
	unsigned int nParticles;// Número de PARTICLES del SWARM
	unsigned int nParams;
	unsigned int idGbest; // Índice a la mejor partícula
	/* Las constantes dan peso a la experiencia indivudual o a la colectiva */
	float lowerSpeed;
	float upperSpeed;
	float c1;
	float c2;
	PARTICLE* Swarm; //Apuntador a SWARM
} SWARM;

SWARM *CreateSwarm(unsigned int nParticles, unsigned int nParams);
void SetupSWARM(SWARM *pSwarm, const float lowLimit, const float highLimit, const float c1, const float c2,
								const float lowerSpeed, const float upperSpeed);
void ShowPARTICLE(SWARM *pSwarm, const int i);
void ShowSWARM(SWARM *pSwarm);
void FreeSWARM(SWARM *pSwarm);
void EvaluateSWARM(SWARM *pSwarm);
void SetupBest(SWARM *pSwarm);
void UpdateSpeed(SWARM *pSwarm);
void UpdatePosition(SWARM *pSwarm);
void UpdateBest(SWARM *pSwarm);

int main()
{
	SWARM *example;
	unsigned int j;
	unsigned int limit;
	j = 0;
	limit = ITERATION_LIMIT;

	example = CreateSwarm(PARTICLES_NUMBER, PARAMS_NUMBER);
	SetupSWARM(example, LOW_LIMIT, HIGH_LIMIT, 2, 2, LOWER_SPEED, UPPER_SPEED);
	ShowSWARM(example);
	EvaluateSWARM(example);
	printf("\n");
	EvaluateSWARM(example);
	ShowSWARM(example);
	SetupBest(example);
	printf("\n Best = %u", example->idGbest);


	while ((j < limit) && (50 - example->Swarm[example->idGbest].PFit) > 0.000001 ) {
		UpdateSpeed(example);
		UpdatePosition(example);
		EvaluateSWARM(example);
		UpdateBest(example);
		ShowSWARM(example);
		printf("\nIteracion: %d\t", j);
		j++;
	}
	printf("\n Best = %u", example->idGbest);

	FreeSWARM(example);
	return 0;
}

/* Asignación dinámica para SwarmAMBRE */
SWARM* CreateSwarm(unsigned int nParticles, unsigned int nParams)
{
	unsigned int k;
	SWARM *ptr;

	ptr = (SWARM*)malloc(sizeof(SWARM));
	if (ptr == NULL) {
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
	if (ptr->Swarm == NULL) {
		printf("Error al asignar Memoria a PARTICLEs");
		exit(-1);
	}

	// Asignar memoria a cada PARTICLE
	for (k = 0; k < nParticles; k++) {
		ptr->Swarm[k].Xi = (float*)malloc(sizeof(float)*nParams);
		ptr->Swarm[k].Vi = (float*)malloc(sizeof(float)*nParams);
		ptr->Swarm[k].Pi = (float*)malloc(sizeof(float)*nParams);
	}

	return ptr;
}

void SetupSWARM(SWARM *pSwarm, const float lowLimit, const float highLimit, const float c1, const float c2,
								const float lowerSpeed, const float upperSpeed)
{
	unsigned int i, k;
	float r;
	r = 0;

	for (i = 0; i < pSwarm->nParticles; i++) {
		for (k = 0; k < pSwarm->nParams; k++) {
			r = ((double)rand() / RAND_MAX)*(highLimit - lowLimit) + lowLimit;
			pSwarm->Swarm[i].Xi[k] = r;
			pSwarm->Swarm[i].Vi[k] = 0;
			pSwarm->Swarm[i].Pi[k] = r;
		}
		pSwarm->c1 = c1;
		pSwarm->c2 = c2;
		pSwarm->lowerSpeed = lowerSpeed;
		pSwarm->upperSpeed = upperSpeed;
	}
}

void SetupBest(SWARM *pSwarm) {
	unsigned int i;
	float best;

	best = pSwarm->Swarm[0].XFit;
	for(i=0; i < pSwarm->nParticles; i++) {
		pSwarm->Swarm[i].PFit = pSwarm->Swarm[i].XFit;
		if (pSwarm->Swarm[i].PFit > best) {
			pSwarm->idGbest = i;
			best = pSwarm->Swarm[i].PFit;
		}
	}
}

void ShowPARTICLE(SWARM *pSwarm, const int i) {
	unsigned int k;

	printf("\n X%u ", i);
	for (k = 0; k < pSwarm->nParams; k++)
		printf("%2.4f  ", pSwarm->Swarm[i].Xi[k]);

	printf("\n V%u ", i);
	for (k = 0; k < pSwarm->nParams; k++)
		printf("%2.4f  ", pSwarm->Swarm[i].Vi[k]);

	printf("\n P%u ", i);
	for (k = 0; k < pSwarm->nParams; k++)
		printf("%2.4f  ", pSwarm->Swarm[i].Pi[k]);

	printf("\n xFit = %f", pSwarm->Swarm[i].XFit);
	printf("\n xPit = %f", pSwarm->Swarm[i].PFit);
}

void ShowSWARM(SWARM *pSwarm) {
	unsigned int i;

	for (i = 0; i < pSwarm->nParticles; i++)
		ShowPARTICLE(pSwarm, i);
}

void FreeSWARM(SWARM *pSwarm) {
	unsigned int k;

	// Liberar memoria para todos los parametros de cada PARTICLE
	for (k = 0; k < pSwarm->nParticles; k++) {
		free(pSwarm->Swarm[k].Xi);
		free(pSwarm->Swarm[k].Vi);
		free(pSwarm->Swarm[k].Pi);
	}

	// Liberar memoria de PARTICLEs
	free(pSwarm->Swarm);
	// Liberar memoria de SWARM
	free(pSwarm);
}

void EvaluateSWARM(SWARM *pSwarm) {
	unsigned int k;

	// Evaluate cada PARTICLE
	for (k = 0; k < pSwarm->nParticles; k++)
		pSwarm->Swarm[k].XFit = 50 - ((pSwarm->Swarm[k].Xi[0] - 5)*(pSwarm->Swarm[k].Xi[0] - 5) +
		(pSwarm->Swarm[k].Xi[1] - 5)*(pSwarm->Swarm[k].Xi[1] - 5));
}

void UpdateSpeed(SWARM *pSwarm) {
	unsigned int i;
	unsigned int j;
	float y1;
	float y2;
	float aux;

	// Para todas las partículas
	for (i = 0; i < pSwarm->nParticles; i++) {
		// Para todos los parámetros
		for (j = 0; j < pSwarm->nParams; j++) {
			y1 = ((float)rand() / RAND_MAX);
			y2 = ((float)rand() / RAND_MAX);
			aux = pSwarm->Swarm[i].Vi[j] + (pSwarm->c1)*y1*(pSwarm->Swarm[i].Pi[j] - pSwarm->Swarm[i].Xi[j]) +
																(pSwarm->c2)*y2*(pSwarm->Swarm[pSwarm->idGbest].Pi[j] - pSwarm->Swarm[i].Xi[j]);
			if(aux > pSwarm->upperSpeed) {
				pSwarm->Swarm[i].Vi[j] = pSwarm->upperSpeed;
			}
			else if(aux < pSwarm->lowerSpeed) {
				pSwarm->Swarm[i].Vi[j] = pSwarm->lowerSpeed;
			}
			else {
				pSwarm->Swarm[i].Vi[j] = aux;
			}
		}
	}
}

void UpdatePosition(SWARM *pSwarm) {
	unsigned int i;
	unsigned int j;
	float y1;
	float y2;

	// Para todas las partículas
	for (i = 0; i < pSwarm->nParticles; i++)
		// Para todos los parámetros
		for (j = 0; j < pSwarm->nParams; j++) {
			pSwarm->Swarm[i].Xi[j] += pSwarm->Swarm[i].Vi[j];
		}
}

void UpdateBest(SWARM *pSwarm) {
	unsigned int i;
	float best;
	best = pSwarm->Swarm[pSwarm->idGbest].PFit;

	for(i=0; i < pSwarm->nParticles; i++) {
		if(pSwarm->Swarm[i].XFit > pSwarm->Swarm[i].PFit) {
			for(int j = 0; j < pSwarm->nParams; j++) {
				pSwarm->Swarm[i].Pi[j] = pSwarm->Swarm[i].Xi[j];
				pSwarm->Swarm[i].PFit = pSwarm->Swarm[i].XFit;
			}
		}
		if (pSwarm->Swarm[i].PFit > best) {
			pSwarm->idGbest = i;
			best = pSwarm->Swarm[i].PFit;
		}
	}
}
