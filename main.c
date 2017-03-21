#include "PDI.h"
#include "PSO.h"
#include "circle.h"

int main(void)
{
	//Declarar un Puntero a imagen
	unsigned int i,j;
	unsigned int width,height;
	unsigned int k=0;
	gcIMG *img1;
	VECTORS vector;

	img1 = gcGetImgBmp("imag_circle_4.bmp");
	height = img1->alto;
	width = img1->ancho;
	vector.x = (int*)malloc(width*height*sizeof(int));
  vector.y = (int*)malloc(width*height*sizeof(int));

	vector = GetColoredPixels(img1);

	//Libera la Imagen utilizada
	gcFreeImg(img1);
	return 0;
}
