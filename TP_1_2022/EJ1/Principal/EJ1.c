#include <stdio.h>
#include <math.h>


#define PI                                          3.14159265359
#define DT                                          0.001
#define G                                           9.81


#define VELOCIDAD_INICIAL                           20
#define ANGULO_INICIAL                              50

#define POSICION_INICIAL_X                          0
#define POSICION_INICIAL_y                          0



double  computar_velocidad(double vi, double a, double dt);
double  computar_posicion(double pi, double vi, double dt);


void    imprimir_posicion(double pi_x, double pi_y, double vi, double angulo_inicial, double a_y, double a_x, double dt);


double  aceleracion_resultante_x(double a_x_positio, double a_x_negativo);

double  grados_a_radianes(double angulo_grados);

double  velocidad_i_x(double angulo_grados, double vi);
double  velocidad_i_y(double angulo_grados, double vi);


int main(void){
    
    imprimir_posicion(POSICION_INICIAL_X, POSICION_INICIAL_y, VELOCIDAD_INICIAL, ANGULO_INICIAL, -G, 0, DT);

    return 0;
}


double computar_velocidad(double vi, double a, double dt){
    return vi + dt*a;
}

double computar_posicion(double pi, double vi, double dt){
    return pi + vi*dt;
}


void imprimir_posicion(double pi_x, double pi_y, double vi, double angulo_inicial, double a_y, double a_x, double dt){
    
    double posicion_x = pi_x;
    double posicion_y = pi_y;
    double tiempo = 0;

    double velocidad_x = velocidad_i_x(angulo_inicial, vi);
    double velocidad_y = velocidad_i_y(angulo_inicial, vi); 
    
   
   
    do{       
        printf("%.4lf,%.4lf,%.4lf\n", tiempo, posicion_x, posicion_y);
        
        tiempo += dt;

        //Se obtiene el valor de la posicion actual para x e y.
        posicion_x = computar_posicion(posicion_x, velocidad_x, dt);
        posicion_y = computar_posicion(posicion_y, velocidad_y, dt);

        //se obtiene el valor de la velocidad actual para x e y.
        velocidad_x = computar_velocidad(velocidad_x, a_x, dt);
        velocidad_y = computar_velocidad(velocidad_y, a_y, dt);

        
    
    } while ( posicion_y > 0);

     printf("%.4lf,%.4lf,%.4lf\n", tiempo, posicion_x, posicion_y);
    
}


/*
funcion para considerar casos donde hay aceleracion en el eje X por si
la pelota tiene un propulsor o hay rozamiento con el aire. Entrega la
aceleracion resultante en x.
*/
double aceleracion_resultante_x(double a_x_positio, double a_x_negativo){
    return a_x_positio - a_x_negativo;
}

double grados_a_radianes(double angulo_grados){
    return angulo_grados * PI / 180.0;
}

double velocidad_i_x(double angulo_grados, double vi){
    return cos(grados_a_radianes(angulo_grados)) * vi;
}
double velocidad_i_y(double angulo_grados, double vi){
    return sin(grados_a_radianes(angulo_grados)) * vi;
}