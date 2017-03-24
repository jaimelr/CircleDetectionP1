#include "PDI.h"
#include "PSO.h"
#include "circle.h"

int main(void)
{
	unsigned int width;
	unsigned int height;
	unsigned int centerX = 0;
	unsigned int centerY = 0;
	unsigned int radius;
	unsigned int i;
	unsigned int j;
	gcIMG *img1;
	VECTORS vector;
	SWARM *swarm;

	j = 0;

	img1 = gcGetImgBmp("imag_circle_4.bmp");

	height = img1->alto;
	width = img1->ancho;
	vector.x = (int*)malloc(width*height*sizeof(int));
  vector.y = (int*)malloc(width*height*sizeof(int));

	vector = GetColoredPixels(img1);

	swarm = CreateSwarm(PARTICLES_NUMBER, PARAMS_NUMBER);
	SetupSWARM(swarm, 0, vector.size, 2, 2, LOW_SPEED, HIGH_SPEED);
	ShowSWARM(swarm);
	EvaluateSWARM(swarm, vector, img1);
	printf("\n");
	EvaluateSWARM(swarm, vector, img1);
	ShowSWARM(swarm);
	SetupBest(swarm);
	printf("\n Best = %u", swarm->idGbest);

	while ((j < ITERATION_LIMIT) && (360 - swarm->Swarm[swarm->idGbest].PFit) > 1 ) {
		UpdateSpeed(swarm);
		UpdatePosition(swarm);
		EvaluateSWARM(swarm, vector, img1);
		UpdateBest(swarm);
		ShowSWARM(swarm);
		printf("\nIteracion: %d\t", j);
		j++;
	}
	printf("\n Best = %u", swarm->idGbest);

	free(vector.x);
	free(vector.y);
	gcFreeImg(img1);
	FreeSWARM(swarm);
	return 0;
}
