/*
Escribir funcion que dado un caracter escriba:

si el carácter es 'A':
    "House Arryn"
si el carácter es 'B':
    "House Baratheon"
si el carácter es 'F':
    "House Frey"
si el carácter es 'G':
    "House Greyjoy"
si el carácter es 'L':
    "House Lannister"
si el carácter es 'M':
    "House Martell"
si el carácter es 'S':
    "House Stark"
si el carácter es 'T':
    "House Targaryen"
si es otro carácter:
    "No lo conozco"
*/

#include <stdio.h>


typedef enum{
    ARRYN = 65 ,
    BARATHEON = 66,
    FREY = 70,
    GREYJOY = 71,
    LANNISTER = 76,
    MARTELL = 77,
    STARK = 83,
    TARGARYEN = 84
} houses_t;


void house_value(char n);


int main(void){

    char caracter = 'C';

    house_value(caracter);

    return 0;
}

void house_value(char n){
    
    switch(n){
        case ARRYN:
            printf("House Arryn\n");
            return;
        
        case BARATHEON:
        printf("House Baratheon\n");
            return;
        
        case FREY:
           printf("House Frey\n");
            return;
        
        case GREYJOY:
            printf("House Greyjoy\n");
            return;
        
        case LANNISTER:
            printf("House Lanister\n");
            return;
        
        case MARTELL:
            printf("House Martell\n");
            return ;
        
        case STARK:
            printf("House Stark\n");
            return;
        
        case TARGARYEN:
            printf("House Targaryen\n");
            return ;

        default:
        printf("No lo conozco\n");
            return;
    
    }
}