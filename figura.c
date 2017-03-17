#include "PDI.h"
#include "figura.h"

void circulo(gcIMG *img, const int h, const  int w)
{
	unsigned int i,j;
	const int Cx = 150;
	const int Cy = 150;
	const int R = 100;
	double d2;
	double R2 = R*R;
	/*
	for(i=0; i<h; i++)
	{
		for(j=0;j<w; j++)
		{
			img->imx[i*img->ancho+j]=255;
		}
	}
	*/
	for(j=0;j<h;j++)
	{                              
		for (i=0;i<w;i++)
		{                          
			d2 =(Cx - i)*(Cx - i);                      
			d2 +=(Cy - j)*(Cy - j);                    
			if (d2 <= R2)
			{
				img->imx[i*img->ancho+j]=255;
			}
		}
	}
}
