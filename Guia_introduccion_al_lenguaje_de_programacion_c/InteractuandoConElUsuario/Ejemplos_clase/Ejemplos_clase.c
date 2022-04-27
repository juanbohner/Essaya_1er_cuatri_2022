#include <stdio.h>
#include <string.h>

int main(void){
    const char s_1[] = "hola";
    char s_2[] = {104, 111, 108, 97, 0};
    char s_3[] = {'h', 'o', 'l', 'a', '\0'};

    //size_t longitud = strlen(s_1);    

    char copia[5];
    char concatenacion[15] = "agua";
    
    
    strcpy(copia, s_1);

    printf("el string copia contiene: %s\n", copia);

    printf("el string concatenado inicial contiene: %s\n", concatenacion);

    strcat(concatenacion, s_1);

    printf("el string concatenado final contiene: %s\n", concatenacion);

    printf("%s\n%s\n%s\n%zd\n", s_1, s_2, s_3, strlen(s_1));


    //strcmp devuelve 0 si son iguales. Entonces en un operador ? es necesario  negarlo ya que buscas un true, que es distinto de 0 por def.
    if(!strcmp(s_1, s_2))
        printf("true\n");

    printf(!strcmp(s_1, s_2) ? "true\n" : "false\n");

    return 0;
}