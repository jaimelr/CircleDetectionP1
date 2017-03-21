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

int main(void)
{ 
	//Declarar un Puntero a imagen
	gcIMG *Img1;
	//unsigned int i,j;
	unsigned int W,H;
	W=300;
	H=300;
	//Abrir una imagen llamada Uno.bmp
	Img1=gcGetImgBmp("imagen.bmp");
	//Crear una imagen nueva
	//Img1=gcNewImg(H,W);
	/*  
	//Obtiene sus dimensiones
	printf("\n El ancho es: %i",Img1->ancho);
	printf("\n El alto es: %i",Img1->alto);
	printf("\n El tama~no es: %i",Img1->size);
	printf("\n\n");
	*/
	
	//Pintar toda la imagen de un color
	/*
	for(i=0; i<H; i++)
		for(j=0;j<W; j++)
			Img1->imx[i*Img1->ancho+j]=0;
	*/
	//Dibujar circulo
	circulo(Img1,H,W);
	//Crear archivo de imagen
	gcPutImgBmp("imagen.bmp",Img1);
	//Libera la Imagen utilizada
	gcFreeImg(Img1);
	return 0;
}
