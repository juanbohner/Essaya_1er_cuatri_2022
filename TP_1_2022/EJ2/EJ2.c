/*----------------------------------------------------------------------------------------------------------------------------------------*/
//Librerias

#include <stdio.h>
#include <math.h>


/*----------------------------------------------------------------------------------------------------------------------------------------*/
//preprocesador

#define LARGO_FILA                      2
#define PI                              3.14159265359   
#define X                               0
#define Y                               1     


#define TOLERANCIA_ACEPTABLE            1e-8                                      
#define ERROR_MSJ_TOLERANCIA            "No se valido la diistancia"



/*----------------------------------------------------------------------------------------------------------------------------------------*/
//constantes DEL ENUNCIADO

const float polilinea [][LARGO_FILA] ={ {0,1}, {1,3}, {1, 5}, {2, 5}, {3, 4}, {4, 4}, {5, 3}, {4, 2}, {5, 1}, {2, 0} };

const float puntos_P [][LARGO_FILA] ={ {0, 0}, {0, 2}, {6, 1}, {2, 2}, {1, 1}, {1, 4}, {5, 4}, {-1, -3}, {3, 3}, {5, 3}, {0, 7} };
           
const double valores_validacion[] = {
    1.0000000000,
    0.4472136322,
    1.0000000000,
    1.3416407687,
    0.8944271977,
    0.0000000000,
    0.7071067812,
    4.1231056256,
    1.0000000000,
    0.0000000000,
    2.2360679775
    };



/*----------------------------------------------------------------------------------------------------------------------------------------*/
//Fucioes complementarias para funcion distancia_punto_a_polilinea

double producto_interno(double x1, double y1, double x2, double y2);                                        //X_1 . X_2

double norma(double x, double y);                                                                           //|X|

double grados_a_radianes(double angulo_grados);

double calcular_alfa (const float polilinea[][LARGO_FILA], size_t i, float px, float py);                  

double distancia_punto_a_segmento(float p1_x, float p1_y, float p2_x, float p2_y);





/*----------------------------------------------------------------------------------------------------------------------------------------*/
//Funciones para validar resultados

void imprimir_matriz(const float polilinea[][LARGO_FILA], size_t n);

void validar_resultado(double resultado, double valor_valido, double parametro);                    //Compara dos numeros y verifia que sean menores que un parametro




/*----------------------------------------------------------------------------------------------------------------------------------------*/
//Funciones para trasaladar o rotar matrices

void trasladar(float polilinea[][LARGO_FILA], size_t n, float dx, float dy);                        //traslada una matriz en x e y
void rotar(float polilinea[][LARGO_FILA], size_t n, double rad);                                    //rota una matriz respecto del origen




/*----------------------------------------------------------------------------------------------------------------------------------------*/
/*
Funcion para encontrar la distancia entre un punto y una polilinea


    *Una Polilinea va a tener varios puntos, donde cada punto sucesivo se une el uno con el otro, formando segmentos.
    Entonces los puntos A,B,C,D,E,F al unirlos formando los segmentos AB,BC,CD,DE,EF. La union de esos segmentos nos da una polilinea.

    *Esta funcion va a ir checkeando para cada segmento, de la polilinea cual es su punto mas cercano (p) al punto P. Obtiene p y calcula la distancia
    entre p y P. Guarda ese valor y repite el proceso. Si la distancia encontrada en algun proximo segmento de la polilínea es menor al que tiene guardado,
    lo reemplaza por ese valor obtenido.  

    *Se va a tratar cada segmento de la polilinea de la siguiente manera:
        Segmento generico AB con A el principio del segmento y B el final del segmento. P el punto al cual se quiere conocer su menor distancia al segmento.
        P = (px, py), A = (polilinea[i][X], polilinea[i][Y]),  B = (polilinea[i+1][X], polilinea[i+1][Y]) y p el punto del segmento mas cercano a P. 

*/
double distancia_punto_a_polilinea(const float polilinea[][LARGO_FILA], size_t n, float px, float py){

    double distancia_minima = norma(px - polilinea[0][X], py - polilinea[0][Y]);    //distancia minima arranca con el valor de la distancia del punto P al primer punto de la polilinea

    double temp_distancia_minima_segmento;                  //Variable para encontrar la distancia minima de cada segmento AB al punto P = (px, py)
    double alfa;

    size_t iteraciones = n - 1;
    for(size_t i = 0; i < iteraciones; i++){  

        alfa = calcular_alfa(polilinea, i, px, py);         //alfa = [(P - A) . (B - A)] / |(B - A)|^2

        if(alfa <= 0){                                      //Punto mas cercano es p = A
            
            //d = |p - A|
            if ( (temp_distancia_minima_segmento = distancia_punto_a_segmento(polilinea[i][X], polilinea[i][Y], px, py) ) < distancia_minima)
                
                distancia_minima = temp_distancia_minima_segmento;      //si es menor, la reemplazo

            if(distancia_minima == 0)                                   //Si la distancia es 0, no es necesario verificar los demas puntos
                return distancia_minima;

            continue;
        }
        
        if(alfa >= 1){                                                  //El punto mas cercano del segmento es p = B

            //distancia d = |P - B|
            if ( (temp_distancia_minima_segmento = distancia_punto_a_segmento(polilinea[i+1][X], polilinea[i+1][Y], px, py) ) < distancia_minima)
                distancia_minima = temp_distancia_minima_segmento;
 
            if(distancia_minima == 0)
                return distancia_minima;

            continue;
        }
        
        //Punto mas cercano es p = A + fi(B-A)
        //   dist = |P - p|                                             A_x         + alfa *  ( B_x             -       A_x      )      A_y         + alfa * (    B_y           -       A_y      )          
        temp_distancia_minima_segmento = distancia_punto_a_segmento(polilinea[i][X] + alfa * (polilinea[i+1][X] - polilinea[i][X]), polilinea[i][Y] + alfa * (polilinea[i+1][Y] - polilinea[i][Y]), px, py);
 
        if ( temp_distancia_minima_segmento < distancia_minima)
            distancia_minima = temp_distancia_minima_segmento;
        
        if(distancia_minima == 0)
            return distancia_minima;
    }

    return distancia_minima;
}





/*----------------------------------------------------------------------------------------------------------------------------------------*/
//main

int main(void){


    double distancia;

    size_t cantidad_puntos_polilinea = sizeof(polilinea) /(LARGO_FILA * sizeof(float));     //cantidad de puntos de la polilinea
    size_t cantidad_puntos_P = sizeof(puntos_P) /(LARGO_FILA * sizeof(float));              //cantidad de puntos P
    

    for(size_t i = 0; i < cantidad_puntos_P; i++){
        
        distancia = distancia_punto_a_polilinea(polilinea, cantidad_puntos_polilinea, puntos_P[i][X], puntos_P[i][Y]);
        
        //Si el (|distancia - Valor_validacion|) <= error_tolerado  ------> VALIDO
        //Si el (|distancia - Valor_validacion|) >= error_tolerado  ------> ERROR
        validar_resultado(distancia, valores_validacion[i], TOLERANCIA_ACEPTABLE);
    }
    return 0;

}




/*----------------------------------------------------------------------------------------------------------------------------------------*/

double norma(double x, double y){

    return sqrt(x*x + y*y);
}

double producto_interno(double x1, double y1, double x2, double y2){

    return x1*x2 + y1*y2;
}


double grados_a_radianes(double angulo_grados){

    return angulo_grados * PI / 180.0;
}





/*----------------------------------------------------------------------------------------------------------------------------------------*/

//Recibe  (valor_x del primer punto, valor_y del primer punto, valor_x del segundo punto, valor_y del segundo punto)
double distancia_punto_a_segmento(float p1_x, float p1_y, float p2_x, float p2_y){

    return norma(p2_x - p1_x, p2_y - p1_y);
}

double calcular_alfa (const float polilinea[][LARGO_FILA], size_t i, float px, float py){ 

    double modulo_cuadrado = norma(polilinea[i+1][X] - polilinea[i][X], polilinea[i+1][Y] - polilinea[i][Y]);  // |(B - A)|
    
    modulo_cuadrado *= modulo_cuadrado;                                                                        // |(B - A)|^2

    //  alfa = [(P - A) . (B - A)] / |(B - A)|^2
    return  producto_interno(px - polilinea[i][X], py - polilinea[i][Y], polilinea[i+1][X] - polilinea[i][X], polilinea[i+1][Y] - polilinea[i][Y]) / modulo_cuadrado;
}





/*----------------------------------------------------------------------------------------------------------------------------------------*/

void trasladar(float polilinea[][LARGO_FILA], size_t n, float dx, float dy){
    
    for(size_t i = 0; i < n; i++){

        polilinea[i][X] += dx;
        polilinea [i][Y] += dy; 
        
    }
}


void rotar(float polilinea[][LARGO_FILA], size_t n, double rad){
    
    double coseno = cos(rad);
    double seno = sin(rad);

    
    float temp_p[LARGO_FILA];               //guarda los valores donde rota cada punto sin modificar la matriz


    for(size_t i = 0; i < n; i++){

        //nuevos puntos se guardan en una variable temporal sin modificar la matriz
        temp_p[X] = polilinea[i][X]*coseno - polilinea[i][Y]*seno; 
        temp_p[Y] = polilinea[i][X] * seno + polilinea[i][Y] * coseno;
        
        //se modifica la matriz con las variables temporales
        polilinea[i][X] = temp_p[X];
        polilinea[i][Y] = temp_p[Y];

    }
}




/*----------------------------------------------------------------------------------------------------------------------------------------*/

void validar_resultado(double resultado, double valor_valido, double parametro){

    printf( (fabs(resultado - valor_valido) <= parametro) ? "%.10f\n" : "%.10f\t%s\n", resultado, ERROR_MSJ_TOLERANCIA);
    return;
}


void imprimir_matriz(const float polilinea[][LARGO_FILA], size_t n){

    for(size_t i = 0; i < n; i++){

        printf("|%f\t%f|\n", polilinea[i][X], polilinea[i][Y]);     //evito segundo ciclo para recorrer cada punto
        
    }
}