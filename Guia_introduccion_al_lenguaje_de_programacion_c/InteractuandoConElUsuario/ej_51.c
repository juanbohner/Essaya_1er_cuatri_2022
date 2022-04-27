#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MAX_STR         20 

typedef enum{
    OK,
    ENOTNUM,
    ENEGATIVENUM,
    E0,
} errores_t;

const char errors[][40]={"OK", "Error not a number", "Negativo no tiene raiz", "0 no tiene inverso"};

bool char_is_num(char str[MAX_STR]){
    
    size_t i;
    size_t cantidad_puntos = 0;
    size_t cantidad_menos = 0;


    for (i = 0; str[i] != '\n'; i++){
        
        if((str[i] >= '0' && str[i] <= '9') || str[i] == '.' || '-'){
                        
            if(str[i] == '.'){
                cantidad_puntos++;
                if (cantidad_puntos > 1)
                return false;
            }

            if(str[i] == '-'){
                cantidad_menos++;
                if (cantidad_menos > 1)
                return false;
            }
            continue;
        }
        return false;  
    }

    return true;
}


int main(void){
    char str[MAX_STR];
    float f;
    
    fgets(str,MAX_STR,stdin);
    puts(str);

    if(!char_is_num(str)){
        puts(errors[ENOTNUM]);
        return ENOTNUM;
    }
    
    f =atof(str);

    printf("%f\n", f);
    
    if(f < 0){
        printf("%lf\n", (double) 1/f);

        puts(errors[ENEGATIVENUM]);
        return ENEGATIVENUM;
    }

    printf("%lf\n", sqrt(f));

    if(f == 0){
        puts(errors[E0]);
        return E0;
    }
    printf("%lf\n", (double) 1/f);

    return 0;
}