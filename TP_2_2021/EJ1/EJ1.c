#include <stdio.h>
#include <math.h>

/*-----------------------------------------------------------------*/
//defines
#define PI 3.14159265359

//Matriz PPM
#define ENCABEZADO "P1"
#define ANCHO 640
#define ALTO 480
#define FOV 90

//Esfera
#define CX  0.5
#define CY  0.75
#define CZ  1.9
#define R   0.8

/*-----------------------------------------------------------------*/
//Funciones

float producto_interno(float x1, float y1, float z1, float x2, float y2, float z2);
float norma(float x, float y, float z);

int intersecta_esfera(float dx, float dy, float dz);

double grados_a_radianes(double grados){
    return grados * (PI/180.0) ;
}
/*-----------------------------------------------------------------*/

int main(void){

    //x [-ancho/2, ancho/2)
    //y [-alto/2, alto/2)
    
    //origen (0,0)

    float z = ANCHO/(2.0 * tan( grados_a_radianes(FOV/2.0)));
    
    /* 
    ciclos for anidados para recorrer una matriz de puntos:
    |(-ANCHO/2, ALTO/2-1),      (-ANCHO/2+1, ALTO/2-1),     ...,        (ANCHO/2 -1, ALTO/2-1)      |
    |                           ...                                                                 |    
    |                           ...                                                                 |
    |                           ...                                                                 |
    |                           ...                                                                 |
    |                           ...                                                                 |
    |                           ...                                                                 |
    |                           ...                                                                 |
    |(-ANCHO/2, -ALTO/2+1),     (-ANCHO/2+1, -ALTO/2+1),    ...,        (ANCHO/2 -1, -ALTO/2+1)     |
    |(-ANCHO/2, -ALTO/2),       (-ANCHO/2+1, -ALTO/2),      ...,        (ANCHO/2 -1, -ALTO/2)       |
    
    arrancamos en: que es la posicion 1_1
    Avanzamos en la fila hasta llegar al final: 2_1, 3_1, ..., n_1
    subimos una columna y nos movemos en la respectiva fila de igual manera: 1_2, 2_2, ..., n_2

    Asi avanzamos y repetimos hasta ir al ultimo punto que será n_n 
    */
    int min_y = -ALTO/2, max_x = ANCHO/2;
    printf("%s\n%d\t%d\n", ENCABEZADO, ANCHO, ALTO);
    for(int y = (ALTO/2) ; y > min_y; y--){
        
        for(int x = -(ANCHO/2); x < max_x ; x++){
            printf( intersecta_esfera (x/norma(x,y,z), y/norma(x,y,z), z/norma(x,y,z)) == 1 ? "1 " : "0 ");

        }    
        printf("\n");
    }


    return 0;
}


/*-----------------------------------------------------------------*/
//Algebra
float producto_interno(float x1, float y1, float z1, float x2, float y2, float z2){
    return x1*x2 + y1*y2 + z1*z2;
}

float norma(float x, float y, float z){
    return sqrt(x*x + y*y + z*z);
}

/*-----------------------------------------------------------------*/
//Interseccion de esferas
int intersecta_esfera(float dx, float dy, float dz){
    
    float producto_interno_C_d = producto_interno(CX, CY, CZ, dx, dy, dz);
    if( ((producto_interno_C_d*producto_interno_C_d) - producto_interno(CX, CY, CZ, CX, CY, CZ)) + (R*R) >= 0 )
        return 1;
    return 0;
}