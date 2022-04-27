#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LEN  50

int main(void){
    //size_t cantidad_lineas = 0;
    //char caracteres[MAX_LEN];
    /*
    fgets
    lee hasta encontrar el \n
    devuelve puntero a la cadena y si no lo pudo leer correctamente puntero a NULL
    */
    
    /*
    Hola
    A 
    todos
    Mis amigos
    Saludos.

    chau
    */

    size_t lineas = 1;
    size_t caracteres;
    
    /*while (fgets(caracteres, MAX_LEN, stdin) != NULL){
        i++;
    }*/

    int c;
    while ( (c = getchar()) != EOF){
        if(c == '\n')
            lineas++;

        caracteres++;
    }
    /*
    bool x = true;
    while(x){
        if (fgets(caracteres, MAX_LEN, stdin) != NULL){
            i++;
            continue;
        }
        break;
    } 
    */
    printf("%zd\n%zd\n", lineas, caracteres);
    
    return 0;
}
