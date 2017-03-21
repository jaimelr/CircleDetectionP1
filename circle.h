#ifndef _CIRCLE_H
#define _CIRCLE_H

typedef struct {
	unsigned int x;
	unsigned int y;
} PIXEL;

PIXEL* GetColoredPixels(gcIMG* img1) {
  int height;
  int width;
  PIXEL *vector;

  height = img1->alto;
	width = img1->ancho;
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

  return vector;
}

int VectorSize(PIXEL* vector) {
  int i;
  int size;

  i = 0;

  while(vector[i] == NULL) {
    i++;
    size++;
  }
  return size;
}

#endif
