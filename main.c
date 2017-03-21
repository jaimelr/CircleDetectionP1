
#include "PDI.h"
#include "figura.h"

int main(void)
{
	//Declarar un Puntero a imagen
	gcIMG *Img1;
	unsigned int i,j;
	unsigned int W,H;

	Img1=gcGetImgBmp("imag_circle_4.bmp");
	H=Img1->alto; //Obtener alto
	W=Img1->ancho;//Obtener ancho
	printf("\nalto\t%u",H);
	printf("\nancho\t%u",W);
	
	//Barrer imagen buscando puntos negros
	unsigned int k=0;
	int vector[H*W];
	for(i=0; i<H; i++)
	{
		for(j=0;j<W; j++)
		{
			if(Img1->imx[i*Img1->ancho+j] <= 10)
			{
				vector[k]=i*Img1->ancho+j;
				//printf("\n\n%i",vector[k]);
				k++;
				printf("\n\nX=%u\ty=%u",i,j);
			}
			//printf("\n\n%e",Img1->imx[i*Img1->ancho+j]);
		}
	}

	//Libera la Imagen utilizada
	gcFreeImg(Img1);
	return 0;
}
