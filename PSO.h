#ifndef _PSO_H_
#define _PSO_H_

#include<stdio.h>
#include<stdlib.h>

#define PARTICLES_NUMBER 30 // Este ejemplo en particular
#define PARAMS_NUMBER 2 // Solo se necesitan dos valores para darle solucion al problema
#define LOW_LIMIT 10.0
#define HIGH_LIMIT 0.0
#define ITERATION_LIMIT 300
#define LOW_SPEED -1.0
#define HIGH_SPEED 1.0


/* La PARTICLE debia estar dividida en tres partes ESTRUCTURA DE LA PARTICLE
* 1.-posición
* 2.-Velocidad
* 3.-Mejor posición
*/

/* Definición de la estructura SwarmAMBRE */
typedef struct
{
	float* Xi; // Posicion
	float* Vi; // Velocidad
	float* Pi; // Mejor posicion
	float XFit; // Posición fitness
	float PFit; // Mejor posición fitness
}PARTICLE;

typedef struct
{
	unsigned int nParticles;// Número de PARTICLES del SWARM
	unsigned int nParams;
	unsigned int idGbest; // Índice a la mejor partícula
	float        c1; //Las constantes dan peso a la experiencia
	float        c2; //indivudual o a la colectiva
	float        Vmin;
    float        Vmax;
    PARTICLE* Swarm; //Apuntador a SWARM
}SWARM;

SWARM *CreateSwarm(unsigned int nParticles, unsigned int nParams);
void SetupSWARM(SWARM *pSwarm,const float lowLimit,const float highLimit,const float c1,const float c2,const float vmin,const float vmax);
void ShowPARTICLE(SWARM *pSwarm, const int i);
void ShowSWARM(SWARM *pSwarm);
void FreeSWARM(SWARM *pSwarm);
void EvaluateSWARM(SWARM *pSwarm);
void SetupBest(SWARM *pSwarm);
void UpdateSpeed(SWARM *pSwarm);
void UpdatePosition(SWARM *pSwarm);
void UpdateBest(SWARM *pSwarm);

#endif //_PSO_H_
