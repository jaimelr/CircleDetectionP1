#include "circle.h"

VECTORS GetColoredPixels(gcIMG* img1) {
  int height;
  int width;
  int i;
  int j;
  int k;
  VECTORS vector;

  k = 0;
  height = img1->alto;
	width = img1->ancho;
  vector.x = (int*)malloc(width*height*sizeof(int));
  vector.y = (int*)malloc(width*height*sizeof(int));

  //Barrer imagen buscando puntos negros
	for(i=0; i<height; i++)
	{
		for(j=0;j<width; j++)
		{
			if(img1->imx[i*img1->ancho+j] == 0)
			{
				vector.x[k] = j;
				vector.y[k] = height-i;
				printf("\n\nX=%d\ty=%d", vector.x[k], vector.y[k]);
				k++;
			}
		}
	}
  vector.size = --k;

  return vector;
}
