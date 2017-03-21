#include "PDI.h"
#include "PSO.h"

int main(void)
{
	//Declarar un Puntero a imagen
	unsigned int i,j;
	unsigned int width,height;
	unsigned int k=0;
	gcIMG *Img1;
	PIXEL *vector;

	Img1=gcGetImgBmp("imag_circle_4.bmp");
	height=Img1->alto;
	width=Img1->ancho;

	vector = (PIXEL*)malloc(height*width*sizeof(PIXEL));

	//Barrer imagen buscando puntos negros
	for(i=0; i<height; i++)
	{
		for(j=0;j<width; j++)
		{
			if(Img1->imx[i*Img1->ancho+j] == 0)
			{
				vector[k].x = j;
				vector[k].y = height-i;
				printf("\n\nX=%d\ty=%d", vector[k].x, vector[k].y);
				k++;
			}
		}
	}

	//Libera la Imagen utilizada
	free(vector);
	gcFreeImg(Img1);
	return 0;
}
