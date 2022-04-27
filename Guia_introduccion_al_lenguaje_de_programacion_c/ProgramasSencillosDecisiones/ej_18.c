/*
Escribir funciones que calculen:
Factorial---------------> n! = 1*2*3*...*n
Número de Euler --------> e = 1 + 1/1! + 1/2! + ... + 1/n!
Exponencial-------------> e^x = 1 + x/1! + x^2/2! + ... + x^n/n!
Tetración---------------> a^(a^(a^(a^(...)))) 
*/

#include <stdio.h>
#include <stdlib.h>


/*defines del factorial*/
#define NUM 6
#define MENSAJE_FACOTRIAL "El factorial del numero "
#define ES " es: "

/*Define de Euler*/
#define NUMERO_PRECISION_EULER 9
#define MENSAJE_EULER "El numero de Euler es: "

/*define exp*/
#define MENSAJE_EXP "El valor de e^"
#define NUM_EXP 7
#define NUM_PRESICION_FACT 20


typedef long double ldob;
typedef unsigned int uint;

ldob calculate_pow(uint num, uint pow);
ldob calculate_factorial(uint num);
ldob calculate_euler(uint num);
ldob calculate_exp(uint num, uint precision);
ldob calculate_tetracion_n_a(uint num_a, uint num_n);

int main(void){


    printf("%s%d%s%Lf\n",MENSAJE_FACOTRIAL,NUM,ES,calculate_factorial(NUM));
    printf("%s%Lf\n",MENSAJE_EULER,calculate_euler(NUMERO_PRECISION_EULER)); 
    printf("%s%d%s%Lf\n",MENSAJE_EXP,NUM_EXP, ES,calculate_exp(NUM_EXP, NUM_PRESICION_FACT));
    printf("%Lf\n", calculate_tetracion_n_a(2, 5));

       
  
    return 0;
}

/*Calcular la potnecia de un numero x a la n*/
ldob calculate_pow(uint num, uint pow){
    size_t i = 2;
    ldob value = num;
    if (pow == 0) return 1;
    if (pow == 1) return num;

    while ( i <= pow){
    value *= num;
    i++;
    }
    return value;
}

/*Factorial---------------> n! = 1*2*3*...*n*/
ldob calculate_factorial(uint num){
 
    size_t i = 1;
    ldob fact = 1;

    if (num <= 1) return 1;
    
    //Hace el prdocuto partiendo de 1*1, luego 1*2, luego 2*3, ..., (n-1)*n
    while (i<=num){
        fact *= i;
        i++;
 }

 return fact;
}

/*Número de Euler --------> e = 1 + 1/1! + 1/2! + ... + 1/n!*/
ldob calculate_euler(uint num){
 
    size_t i = 1;
    ldob euler = 1;
    
    while (i<=num){
        euler += (1.0/calculate_factorial(i));
        i++;
 }

 return euler;
}

/*
Exponencial-------------> e^x = 1 + x/1! + x^2/2! + ... + x^n/n!
Tambien es: e^x = e*e*e*e*...*e x veces.
*/
ldob calculate_exp(uint num, uint precision){
    
    
    if(num == 0) return 1;
    if(num == 1) return calculate_euler(precision);
    
    ldob exp = 1;
    for(size_t i = 1 ; i <= precision ; i++){
        exp += (calculate_pow(num, i)/calculate_factorial(i));
    }

    /*
    
    *Acá queda otra forma de hacer este mismo computo haciendo:

    e^x = e*e*e*e*...*e x veces.

    exp = calculate_euler(precision);
    ldob resultado = exp;
    printf("%Lf\n", exp);

    for(size_t i = 2; i <= num; ++i){
        resultado *= exp;
    }
    printf("%s%d%s%Lf\n",MENSAJE_EXP,num, ES,resultado);

    */

    return exp;
}

ldob calculate_tetracion_n_a(uint num_a, uint num_n){
    
    //Si n=0 entonces seria como hacer a^0
    if(num_n == 0) return 1;
    //si a = 1 seria siempre multiplicar 1
    if(num_a == 1) return 1;
    //Si n=1--------> a
    if(num_n == 1) return num_a;
    
    ldob potencia_actual = 0;
    ldob potencia_anterior = 1;

    /*
        
       PRIMER CICLO*   i=1     Arranca con potencia_actual = 2^1 = 2. Se lo asigna a potencia anterio. 
       SEGUNDO CICLO*  i=2     Arranca con potencia_actual = 2^2 = 4. Se lo asigna a potencia anterio.
       TERCER CICLO*   i=3     Arranca con potencia_actual = 2^4 = 16. Se lo asigna a potencia anterio.
       CUARTO CICLO*   i=4     Arranca con potencia_actual = 2^16 = 65536. Se lo asigna a potencia anterio.
       .
       .
       .
    */    

    for(size_t i = 1; i <= num_n; i++){
        

        potencia_actual = calculate_pow(num_a, potencia_anterior);
        potencia_anterior = potencia_actual;

    }

    return potencia_actual;

}
