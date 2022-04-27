
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LARGO_ARREGLO 30

int main(void){
    
    char i_s[LARGO_ARREGLO];
    char f_s[LARGO_ARREGLO];

    
    int i;
    float f;

    
    puts("Ingrese un numero entero");
    fgets(i_s, 30, stdin);

    
    puts("Ingrese un numero flotante");

    //está guardando en f_s tambien el \n de cuando uno escribe en el teclado 
    fgets(f_s, 30, stdin);


    puts("Ingresaste:");
    puts(i_s);
    puts(f_s);

    i = atoi(i_s);
    f = atof(f_s);

    printf("i_s: %s,\t%d\nf_s: %s,\t%f\n", i_s, i, f_s, f);
    return 0;
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main () {
   float val;
   char str[20];
   
   strcpy(str, "98993489");
   val = atof(str);
   printf("String value = %s, Float value = %f\n", str, val);

   strcpy(str, "tutorialspoint.com");
   val = atof(str);
   printf("String value = %s, Float value = %f\n", str, val);

   return(0);
}*/