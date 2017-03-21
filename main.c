#include "PDI.h"
#include "PSO.h"

int main(void)
{
	//Declarar un Puntero a imagen
	unsigned int i,j;
	unsigned int width,height;
	unsigned int k=0;
	gcIMG *img1;
	PIXEL *vector;

	img1 = gcGetImgBmp("imag_circle_4.bmp");
	height = img1->alto;
	width = img1->ancho;

	vector = (PIXEL*)malloc(height*width*sizeof(PIXEL));
	vector = GetColoredPixels(img1);



	//Libera la Imagen utilizada
	free(vector);
	gcFreeImg(img1);
	return 0;
}
