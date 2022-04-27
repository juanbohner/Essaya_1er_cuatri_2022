#include <stdio.h>

#define MAX_STR_LEN 30

//strlen
size_t strlen_(const char s[]){
    size_t i;

    for(i = 0; s[i] != '\0'; i++);
    return i;
}

void strcat_(char s[], const char r[]){
    
    size_t ls = strlen_(s);
    //size_t lr = strlen_(r);
    if(strlen_(r) + ls  >= MAX_STR_LEN){
        //Si la union de ambas es mas larga que lo maximo posible no hace nada
        return;
    }

    for(size_t i = 0; r[i] != '\0'; i++){
        s[ls+i] = r[i];
    }
}

void strcpy(char s[], const char c[]){
    for(size_t i = 0; (s[i] = c[i]); i++);
}

void puts_(const char s[]){
    for(size_t i = 0; s[i] != '\0'; i++)
        printf("%c", s[i]);
    printf("\n");
}

/*Es buena practica comprobar que esto verfique todas las condiciones de borde. 
printf("%d < 0\n", strcmp_("", "hola"));
printf("%d = 0\n", strcmp_("", ""));
printf("%d < 0\n", strcmp_("auto", "barco"));
printf("%d > 0\n", strcmp_("auto", "autos"));
printf("%d < 0\n", strcmp_("auto", "arbol"));
*/

int strcmp_(const char a[], const char  b[]){
    size_t i;

    for(i = 0; a[i] != '\0' && b[i] == a[i], i++);

    return a[i] - b[i];
}

int main(void){
    const char str[] = "HOLA MUNDO";
    char a[MAX_STR_LEN] = "hola";

    puts(a);
    puts_(a);

    strcat_(a,str);
    
    
    puts(a);
    
    printf("%zd\n", strlen_(str));
    return 0;
}