#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define PI          3.1415926535897932384
#define PLANK       6.626e-34
#define MASA_E      9.11e-31
#define CARGA_E     1.602e-19

double calcular_lambda(double p_e){
    return PLANK/p_e;
}

double calcular_p_relativ(double v){
    return sqrt(2 * MASA_E * CARGA_E * v);
}

int main (int argc, char *argv[]){
    
    double tension = atof(argv[1]);

    printf("p_e:\t%e\n", calcular_p_relativ(tension));
    
    printf("LAMBDA:\t%e\n", calcular_lambda(calcular_p_relativ(tension)));
    
    return 0;

}