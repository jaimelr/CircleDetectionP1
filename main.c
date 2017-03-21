#include "PDI.h"
#include "PSO.h"
#include "circle.h"

int main(void)
{
	unsigned int i,j;
	unsigned int width,height;
	unsigned int k=0;
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
	printf("%d\n", vector.size);
	ShowSWARM(swarm);

	free(vector.x);
	free(vector.y);
	gcFreeImg(img1);
	return 0;
}
