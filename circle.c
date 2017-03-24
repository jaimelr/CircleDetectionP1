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
			if(img1->imx[i*img1->ancho+j] < 100)
			{
				vector.x[k] = j;
				vector.y[k] = i;
				//printf("\n\nX=%d\ty=%d", vector.x[k], vector.y[k]);
				k++;
			}
		}
	}
  vector.size = --k;

  return vector;
}

float CenterCoordinateX(VECTORS vector, int i, int j, int k) {
  int xi = vector.x[i];
  int xj = vector.x[j];
  int xk = vector.x[k];
  int yi = vector.y[i];
  int yj = vector.y[j];
  int yk = vector.y[k];
  float det;
  float xCenter;
  int t1, t2, t3, t4;

  t1 = xj*xj + yj*yj-(xi*xi+yi*yi);
  t2 = 2*(yj-yi);
  t3 = xk*xk+yk*yk - (xi*xi+yi*yi);
  t4 = 2*(yk-yi);

  det = t1*t4 - t2*t3;
  xCenter = det/(4*((xj-xi)*(yk-yi) - (xk-xi)*(yj-yi)));

  return xCenter;
}

float CenterCoordinateY(VECTORS vector, int i, int j, int k) {
  int xi = vector.x[i];
  int xj = vector.x[j];
  int xk = vector.x[k];
  int yi = vector.y[i];
  int yj = vector.y[j];
  int yk = vector.y[k];
  float det;
  float yCenter;
  int t1, t2, t3, t4;

  t1 = 2*(xj-xi);
  t2 = xj*xj + yj*yj - (xi*xi + yi*yi);
  t3 = 2*(xk-xi);
  t4 = xk*xk + yk*yk - (xi*xi + yi*yi);

  det = t1*t4 - t2*t3;
  yCenter = det/(4*((xj-xi)*(yk-yi) - (xk-xi)*(yj-yi)));

  return yCenter;
}

float CircleRadius(VECTORS vector, int centerX, int centerY, int i) {
  int t1;
  int x = vector.x[i];
  int y = vector.y[i];
  float radius;

  t1 = (x-centerX)*(x-centerX) + (y-centerY)*(y-centerY);
  radius = sqrt(t1);
  return radius;
}
