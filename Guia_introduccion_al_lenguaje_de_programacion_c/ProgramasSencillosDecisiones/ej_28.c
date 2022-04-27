/*
Escribir funciones que resuelvan los siguientes problemas:

a)Dado un año indicar si es bisiesto.
Nota
Un año es bisiesto si es un número divisible por 4, pero no si es divisible por 100, excepto que también sea divisible por 400.

b)Dado un mes y un año, devolver la cantidad de días correspondientes.

c)Dada una fecha (día, mes, año), indicar si es válida o no.

d)Dada una fecha, indicar los días que faltan hasta fin de mes.

e)Dada una fecha, indicar los días que faltan hasta fin de año.

f)Dada una fecha, indicar la cantidad de días transcurridos en ese año hasta esa fecha.

g)Dadas dos fechas (día1, mes1, año1, día2, mes2, año2), indicar el tiempo transcurrido entre ambas, en años, meses y días.
*/


#include <stdio.h>

// TRUE algo distinto de 0. FALSE algo igual a 0.
#include <stdbool.h>

/*Este valor es unicamente un nmro arbitrario muy grande. Lo uso para poder identificar si una funcion tuvo algun error. Checkear si hay alguna forma distinta y mas prolija de hacer esto.*/
#define ERROR_VALUE_INVALID_DATE        1000000

#define DAY_P                           13
#define MONTH_P                         4
#define YEAR_P                          2022

#define DAY_F                           11
#define MONTH_F                         6
#define YEAR_F                          2028


typedef unsigned int                    uint;
typedef unsigned long int               ulint;

//month_t tiene los meses del año
typedef enum {
    JANUARY = 1,
    FEBRUARY,
    MARCH,
    APRIL,
    MAY,
    JUNE,
    JULY,
    AUGUST,
    SEPTEMBER,
    OCTOBER,
    NOVEMBER,
    DECEMBER
}month_t;



//Indica si un año es biciesto
bool isLeapYear (uint year);

//Cantidad de dias en un mes
uint amountDaysInMonth(month_t month, uint year);

//Verifia que una fecha introducida sea valida
bool checkDate(uint day, month_t month, uint year);

//calcula la cantidad de dias faltantes en el mes
uint remainingMonthDays(uint day, month_t month, uint year);

//calcula la cantidad de dias que pasaron en el año
uint daysSpentThisYear(uint day, month_t month, uint year);

//calcula la cantidad de dias faltantes en el año
uint remainingYearDays(uint day, month_t month, uint year);

//calcula la cantidad de años,meses,dias entre 2 fechas
ulint timeBetweenDatesInDays(uint day_p, month_t month_p, uint year_p, uint day_f, month_t month_f, uint year_f);

int main(void){
    
    uint day = DAY_P;
    month_t month = MONTH_P;
    uint year = YEAR_P;

    uint future_day = DAY_F;
    month_t future_month = MONTH_F;
    uint future_year = YEAR_F;

    printf(isLeapYear(year) ? "Es ano biciesto\n" : "No es ano biciesto\n");

    printf(amountDaysInMonth(month, year) ==  false ? "Se introdujo un mes invalido\n" : "El mes %d tiene %d dias.\n", month, amountDaysInMonth(month, year));

    printf(checkDate(day, month, year) == true ? "La fecha introducida es valida.\n" : "La fecha introducida es invalida.\n");
    
    printf(remainingMonthDays(day, month, year) == ERROR_VALUE_INVALID_DATE ? "La fecha introducida es invalida.\n" : "La cantidad de dias del mes restantes es:%d.\n" , remainingMonthDays(day, month, year));

    printf("La cantidad de dias transcorridos en el ano es:%d.\n" , daysSpentThisYear(day, month, year) );

    printf("La cantidad de dias restantes en el ano son:%d.\n" , remainingYearDays(day, month, year) );

    printf("la cantidad de dias entre ambas fechas es:%ld.\n", timeBetweenDatesInDays(day, month, year, future_day, future_month, future_year));

    return 0;
}

//devuelve true si es año biciesto. Flase caso contrario
bool isLeapYear(uint year){

    //Si el resto de dividir el año por 4 es distinto de 0 entonces no es biciesto
    if((year%4) == true) return false;

    //Una vez checkeado lo anterior, si el resto de dividir por 100 es distinto de 0 entonces es biciesto
    if((year%100)== true) return true;

    //Si no se cumplen los dos anteriores, falta ver el resto de dividirlo por 400. si es distinto de 0 entonces el año no es biciesto.
    if((year%400) == true) return false;

    //habiendo pasado por las anteriores condiciones solo puede ser biciesto
    return true;
}

uint amountDaysInMonth(month_t month, uint year){
    
    switch(month){
        case JANUARY:
            return 31;
        
        case FEBRUARY:
            if(isLeapYear(year))
                return 29;
            return 28;
        
        case MARCH:
            return 31;
        
        case APRIL:
            return 30;
        
        case MAY:
            return 31;
        
        case JUNE:
            return 30;
        
        case JULY:
            return 31;
        
        case AUGUST:
            return 31;

        case SEPTEMBER:
            return 30;
        
        case OCTOBER:
            return 31;

        case NOVEMBER:
            return 30;

        case DECEMBER:
            return 31;        
        
        default:
            return false;
    }
}

//devuelve true si la fecha introducida es valida
bool checkDate(uint day, month_t month, uint year){
    
    //primero se asrgura que el dia y los meses estén dentro de sus limites
    if (day > 31) return false;
    if(month > 12) return false;

    if(day > amountDaysInMonth (month, year)) return false;

    return true;
}

uint remainingMonthDays(uint day, month_t month, uint year){

    if(checkDate(day,month,year) == false) 
        return ERROR_VALUE_INVALID_DATE;
 
    return ((amountDaysInMonth(month, year) - day)); 
}

uint daysSpentThisYear(uint day, month_t month, uint year){

    if(checkDate(day,month,year) == false) 
        return ERROR_VALUE_INVALID_DATE;
    
    uint temp = 0;

    
    //Obtengo la cantidaad de dias que pasaron en este año, hasta el pricipio del mes en el que estoy.
    for(month_t i = JANUARY; i < DECEMBER; i++){
        if(i == month)
            break;

        temp += amountDaysInMonth(i, year);
    }
    //se suman los dias transcurridos del mes a los dias transcurridos hasta el mes (los dias sumados de todos los meses anteriores).
    temp += day;

    return temp;
}

uint remainingYearDays(uint day, month_t month, uint year){

    if(checkDate(day,month,year) == false) 
        return ERROR_VALUE_INVALID_DATE;
    if(isLeapYear(year))
        return 366- daysSpentThisYear(day,month,year);

    return 365 - daysSpentThisYear(day,month,year);
}

//Devuelve la cantidad de dias entre ambas fechas
ulint timeBetweenDatesInDays(uint day_p, month_t month_p, uint year_p, uint day_f, month_t month_f, uint year_f){
    //Se checkea si lo introducido es valido
    if(checkDate(day_p,month_p,year_p) == false)
        return  ERROR_VALUE_INVALID_DATE;

    if(checkDate(day_f,month_f,year_f) == false)
        return  ERROR_VALUE_INVALID_DATE;

    ulint days = 0;

    //Se obtiene la cantidad de dias entre ambos años.
    for(uint i = 1; i < (year_f - year_p); i++){
        if(isLeapYear(i)){
            days += 366;
            continue;
        }  
        
        days += 365;
    }

    days = days + daysSpentThisYear(day_f, month_f, year_f) + remainingYearDays(day_p ,month_p, year_p); 

    return days;
}



uint timeBetweenDates(uint day_p, month_t month_p, uint year_p, uint day_f, month_t month_f, uint year_f){

    if(checkDate(day_p,month_p,year_p) == false)
        return  ERROR_VALUE_INVALID_DATE;

    if(checkDate(day_f,month_f,year_f) == false)
        return  ERROR_VALUE_INVALID_DATE;

    // ya estan checkeadas las fechas introducidas.

    //hay que encontrar el año
    uint year = year_f - year_p;
    uint month = month_f - month_p;

    daysSpentThisYear(day_f, month_f, year_f) - daysSpentThisYear(day_p ,month_p, year_p);

}

