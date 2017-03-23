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
	gcIMG *img1;
	VECTORS vector;
	SWARM *swarm;

	img1 = gcGetImgBmp("c3.bmp");

	height = img1->alto;
	width = img1->ancho;
	vector.x = (int*)malloc(width*height*sizeof(int));
  vector.y = (int*)malloc(width*height*sizeof(int));

	vector = GetColoredPixels(img1);

	swarm = CreateSwarm(PARTICLES_NUMBER, PARAMS_NUMBER);
	SetupSWARM(swarm, 0, vector.size, 2, 2, LOW_SPEED, HIGH_SPEED);
	//ShowSWARM(swarm);
	EvaluateSWARM(swarm, vector, img1);

	free(vector.x);
	free(vector.y);
	gcPutImgBmp("Plox.bmp", img1);
	gcFreeImg(img1);
	return 0;
}
