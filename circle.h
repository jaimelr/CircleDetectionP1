#ifndef _CIRCLE_H
#define _CIRCLE_H

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "PDI.h"

typedef struct {
	int* x;
	int* y;
  unsigned int size;
} VECTORS;

VECTORS GetColoredPixels(gcIMG* img1);
int VectorSize(VECTORS* vector);
int CenterCoordinateX(VECTORS vector, int i, int j, int k);
int CenterCoordinateY(VECTORS vector, int i, int j, int k);
int CircleRadius(VECTORS vector, int centerX, int centerY, int i);

#endif
