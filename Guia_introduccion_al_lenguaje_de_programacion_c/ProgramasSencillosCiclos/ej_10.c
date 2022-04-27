/*Escribir una función que reciba un número entero y devuelva 1 si el número es positivo y -1 si el número es negativo.*/
#include <stdio.h>
#define NUMERO_INGRESADO -3

int IsPositive(int num);

int main(void){

    int x = IsPositive(NUMERO_INGRESADO);
    printf("%d\n", x);

    return 0;

}

int IsPositive(int num){
    printf(num > 0 ? "num positivo\n": "num negativon\n");
    return (num > 0 ? 1:-1);
}