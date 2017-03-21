#ifndef _PDI_H_
#define _PDI_H_

#include<stdio.h>
#include<stdlib.h>
/* ***************** ESTRUCTURAS DE DATOS ****************************** */
typedef unsigned char  		byte;    	// Tipo de dato de 1 byte
typedef unsigned short int 	word;    // Tipo de dato de 2 bytes
typedef unsigned long  int 	dword;   // Tipo de dato de 4 bytes

typedef struct{
	byte    id[2];  // Identificador de fila BMP
	word    offset; // Offset al principio de la imagen
	word    ancho;  // Columnas de la imagen
	word    alto;   // Filas de la imagen
	byte    bpp;    // Bits de color por pixel
    int     size;   // Tamaño de la imagen
    byte    *head;  // Puntero al encabezado
	float   *imx;   // Puntero al inicio de la imagen
}gcIMG;

gcIMG* 	gcGetImgBmp(char *ruta);
void 	gcPutImgBmp(char *ruta, gcIMG *img);
gcIMG*	gcNewImg(int ancho,int alto);
void 	gcFreeImg (gcIMG *img);

#endif //_PDI_H_
