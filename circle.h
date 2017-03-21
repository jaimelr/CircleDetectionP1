#ifndef _CIRCLE_H
#define _CIRCLE_H

#include<stdio.h>
#include<stdlib.h>
#include "PDI.h"

typedef struct {
	int* x;
	int* y;
  unsigned int size;
} VECTORS;

VECTORS GetColoredPixels(gcIMG* img1);
int VectorSize(VECTORS* vector);

#endif