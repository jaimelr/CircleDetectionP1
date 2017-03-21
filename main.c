/* **********************************************************************
   PROCESAMIENTO DIGITAL DE IMAGENES
   Biblioteca Basica de Funciones
   Autor: Dr. Carlos Hugo Garcia Capulin
   Ver 1.2
   Prohibido su uso, distribucion y copia sin autorizacion por parte del autor.
   DIVISION DE INGENIERAAS CAMPUS IRAPUATO-SALAMANCA
   UNIVERSIDAD DE GUANAJUATO 
   **********************************************************************
*/

#include "PDI.h"
#include "figura.h"
//#include "PSO.h"

int main(void)
{ 
	//Declarar un Puntero a imagen
	gcIMG *Img1;
	unsigned int i,j;
	unsigned int W,H;
	//unsigned int x,y;
	//W=300;
	//H=300;
	//Abrir una imagen llamada Uno.bmp
	Img1=gcGetImgBmp("Circulos.bmp");
	H=Img1->alto; //Obtener alto
	W=Img1->ancho;//Obtener ancho
	printf("\nalto\t%u",H);
	printf("\nancho\t%u",W);
	//Crear una imagen nueva
	//Img1=gcNewImg(H,W);
	
	/* //Pintar toda la imagen de un color
	for(i=0; i<H; i++)
		for(j=0;j<W; j++)
			Img1->imx[i*Img1->ancho+j]=0;
	*/
	
	//Dibujar circulo
	//circulo(Img1,H,W);
	
	//Crear archivo de imagen
	//gcPutImgBmp("imagen.bmp",Img1);
	
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
