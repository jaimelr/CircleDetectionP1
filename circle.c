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

int CenterCoordinateX(VECTORS vector, int i, int j, int k) {
  int xi = vector.x[i];
  int xj = vector.x[j];
  int xk = vector.x[k];
  int yi = vector.y[i];
  int yj = vector.y[j];
  int yk = vector.y[k];
  int det;
  int xCenter;
  int t1, t2, t3, t4;

  printf("\nCoordenadas de puntos X:\n");
	printf("I: %d\n", vector.x[i]);
	printf("J: %d\n", vector.x[j]);
	printf("K: %d\n", vector.x[k]);

  t1 = xj*xj + yj*yj-(xi*xi+yi*yi);
  t2 = 2*(yj-yi);
  t3 = xk*xk+yk*yk - (xi*xi+yi*yi);
  t4 = 2*(yk-yi);

  det = t1*t4 - t2*t3;
  xCenter = det/(4*((xj-xi)*(yk-yi) - (xk-xi)*(yj-yi)));

  return xCenter;
}

int CenterCoordinateY(VECTORS vector, int i, int j, int k) {
  int xi = vector.x[i];
  int xj = vector.x[j];
  int xk = vector.x[k];
  int yi = vector.y[i];
  int yj = vector.y[j];
  int yk = vector.y[k];
  int det;
  int yCenter;
  int t1, t2, t3, t4;

  t1 = 2*(xj-xi);
  t2 = xj*xj + yj*yj - (xi*xi + yi*yi);
  t3 = 2*(xk-xi);
  t4 = xk*xk + yk*yk - (xi*xi + yi*yi);

  det = t1*t4 - t2*t3;
  yCenter = (int)(det/(4*((xj-xi)*(yk-yi) - (xk-xi)*(yj-yi))));

  return yCenter;
}
