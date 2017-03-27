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
	unsigned int k;
	unsigned int iterator;
	unsigned int x;
	unsigned int y;
	unsigned int aux;
	unsigned int pixel;
	gcIMG *img1;
	VECTORS vector;
	SWARM *swarm;

	iterator = 0;
	//srand(time(NULL));

	img1 = gcGetImgBmp("Im0.bmp");

	height = img1->alto;
	width = img1->ancho;
	vector.x = (int*)malloc(width*height*sizeof(int));
  vector.y = (int*)malloc(width*height*sizeof(int));

	vector = GetColoredPixels(img1);

	swarm = CreateSwarm(PARTICLES_NUMBER, PARAMS_NUMBER);
	SetupSWARM(swarm, 0, vector.size, 2, 2, LOW_SPEED, HIGH_SPEED);
	//ShowSWARM(swarm);
	EvaluateSWARM(swarm, vector, img1);
	//ShowSWARM(swarm);
	SetupBest(swarm);

	while ((iterator < ITERATION_LIMIT) && (360 - swarm->Swarm[swarm->idGbest].PFit) > 1 ) {
		UpdateSpeed(swarm, vector);
		UpdatePosition(swarm, vector);
		EvaluateSWARM(swarm, vector, img1);
		UpdateBest(swarm);
		ShowSWARM(swarm);
		printf("\nIteracion: %d\t", iterator);
		iterator++;
	}
	printf("\n Best = %d", swarm->idGbest);
	i = swarm->Swarm[swarm->idGbest].Xi[0];
	j = swarm->Swarm[swarm->idGbest].Xi[1];
	k = swarm->Swarm[swarm->idGbest].Xi[2];

	centerX = (int)CenterCoordinateX(vector, i, j, k);
	centerY = (int)CenterCoordinateY(vector, i, j, k);
	radius = (int)CircleRadius(vector, centerX, centerY, i);

	printf("\n\nPFit: %f\n", swarm->Swarm[swarm->idGbest].PFit);
	printf("\nCentro: (%d, %d)\n", centerX, centerY);
	printf("Radio: %d\n", radius);

	for(int ang=0; ang < 360; ang += 1) {
		x = (int)radius*cos(ang*(PI/180)) + centerX;
		y = (int)radius*sin(ang*(PI/180)) + centerY;

		aux = x*img1->ancho + y;
		pixel = (int)img1->imx[aux];
		img1->imx[pixel] = 0;
	}

	gcPutImgBmp("result.bmp", img1);

	free(vector.x);
	free(vector.y);
	gcFreeImg(img1);
	FreeSWARM(swarm);
	return 0;
}
