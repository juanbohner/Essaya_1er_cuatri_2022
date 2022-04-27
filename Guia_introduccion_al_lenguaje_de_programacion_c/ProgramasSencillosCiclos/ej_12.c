/*
Escribir un programa que imprima, en 3 líneas separadas, su nombre, apellido y padrón. Por ejemplo:

Nombre: Nicasio
Apellido: Maciel
Padron: 123456
*/

#include <stdio.h>

#define NOMBRE_ALUMNO "Pedro"
#define APELLIDO_ALUMNO "Maciel"
#define PADRON 123456

void print_student_data (char nombre[], char apellido[], unsigned int padron);

int main(void){
    print_student_data(NOMBRE_ALUMNO, APELLIDO_ALUMNO, PADRON);
    return 0;
}

void print_student_data (char nombre[], char apellido[], unsigned int padron){
    printf("Nombre:%s\nApellido:%s\nPadron:%d\n",nombre,apellido,padron);
    return;
}