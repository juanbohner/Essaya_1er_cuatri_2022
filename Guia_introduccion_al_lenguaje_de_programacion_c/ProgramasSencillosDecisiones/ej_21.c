/*Escribir una función que dado un número entero lo imprima espejado. Por ejemplo: 9511 se imprime como 1159. Sugerencia: utilice los operadores módulo % y división / */

#include <stdio.h>

int mirror_num(int num);

int main(void){
    printf("%d\n",mirror_num(9511));
    return 0;
}

int mirror_num(int num){

// swap the numbers so that s is always smaller than l
   /*
    if (s > l) {
        int temp = s;
        s = l;
        l = temp;
    }*/

    int rev=0;
    while(num > 0){
        rev*=10;
        rev+=num%10;
        num/=10;
    }

    return rev;
}