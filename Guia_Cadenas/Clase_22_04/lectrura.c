#include <stdio.h>
#include <stdlib.h>

/*double factorial(int n){

}*/

int main(void){
    char aux[100];

    while(fgets(aux, 100, stdin) != NULL)
        printf("%s\n", aux);

    int i = atoi(aux);
    float f = atof(aux);

    printf("%d\n%f\n", i, f);

    return 0;
}