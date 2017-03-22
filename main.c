#include "PDI.h"
#include "PSO.h"
#include "circle.h"

int main(void)
{
	unsigned int width,height;
	unsigned int centerX = 0;
	unsigned int centerY = 0;
	gcIMG *img1;
	VECTORS vector;
	SWARM *swarm;

	img1 = gcGetImgBmp("imag_circle_4.bmp");
	height = img1->alto;
	width = img1->ancho;
	vector.x = (int*)malloc(width*height*sizeof(int));
  vector.y = (int*)malloc(width*height*sizeof(int));

	vector = GetColoredPixels(img1);

	swarm = CreateSwarm(PARTICLES_NUMBER, PARAMS_NUMBER);
	SetupSWARM(swarm, 0, vector.size, 2, 2, LOW_SPEED, HIGH_SPEED);
	//ShowSWARM(swarm);
	//EvaluateSWARM(swarm);

	centerX = CenterCoordinateX(vector, 23, 56, 98);
	centerY = CenterCoordinateY(vector, 23, 56, 98);
	printf("Coordenadas de puntos Y:\n");
	printf("I: %d\n", vector.y[23]);
	printf("J: %d\n", vector.y[56]);
	printf("K: %d\n", vector.y[98]);
	printf("Centro en X: %d\n", centerX);
	printf("Centro en Y: %d\n", centerY);

	free(vector.x);
	free(vector.y);
	gcFreeImg(img1);
	return 0;
}
