#include <stdio.h>
#include <string.h>
#include <stdbool.h>

//Similar a strcmp(s_1, s_2)
bool son_inguales (const char s_1[], const char s_2[]){
    
    if(strlen(s_1) != strlen(s_2)) 
        return false;
    
    for(size_t i = 0; i <= strlen(s_1); i++){
        if(s_1[i] != s_2[i])
            return false;
    }
    return true;
}

int main(void){

    char string_1[] = "hola mundo";
    char string_2[] = "hola mundo";

    printf( son_inguales(string_1, string_2) ? "Son iguales\n": "Son diferentes\n");
    printf("las cadenas son:%d\n", strcmp(string_1, string_2));
    
    return 0;
}