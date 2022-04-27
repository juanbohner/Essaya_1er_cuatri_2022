#include <stdio.h>
#include <math.h>
#include <float.h>
#include <stdbool.h>


#define INFINITO FLT_MAX

#define ANCHO 640
#define ALTO 480
#define FOV 90
#define PI 3.1415926f


#define X 0
#define Y 1
#define Z 2

#define DIMENSION 3


#define IA  20
#define II  255

//direccion fuente de luz
const float luz[DIMENSION] = {0.2873478855663454, 0.9578262852211513, 0};

const float centros[][DIMENSION] = {
    {-.4, .75, 1.55},
    {-.55, -.4, 2},
    {3, 1.5, 4},
    {3, 1.5, 5},
    {3, -1.5, 4},
    {3, -1.5, 5},
    {1, 3, 4},
};

const float radios[] = {
    .3,
    .85,
    .4,
    .4,
    .4,
    .4,
    .3,
};



/*-----------------------------------------------------------------------------------------------------*/

double grados_a_radianes(double grados){

    return grados * (PI/180.0) ;
}

float producto_interno(const float a[DIMENSION], const float b[DIMENSION]){

    return a[X]*b[X] + a[Y]*b[Y] + a[Z]*b[Z]; 
}
float norma(const float a[DIMENSION]){

    return sqrt(a[X]*a[X] + a[Y]*a[Y] + a[Z]*a[Z]);
}

void normalizar(float a[DIMENSION]){

    double norma_1 = norma(a);
    a[X] = a[X]/norma_1;
    a[Y] = a[Y]/norma_1;
    a[Z] = a[Z]/norma_1;
    return; 
}

//r = a - b
void resta(float r[3], const float a[3], const float b[3]){

    r[X] = a[X] - b[X];
    r[Y] = a[Y] - b[Y];
    r[Z] = a[Z] - b[Z];
    return;
}

//P = O +td esto guarda a P
void interpolar_recta(float p[3], const float o[3], const float d[3], float t){

    p[X] = o[X] + t * d[X];
    p[Y] = o[Y] + t * d[Y];
    p[Z] = o[Z] + t * d[Z];
}

bool intersecta_esfera(float o[DIMENSION], float c[DIMENSION], float r){
    
    float producto_interno_o_centro = producto_interno(o,c);
    if( ((producto_interno_o_centro*producto_interno_o_centro) - producto_interno(c, c)) + (r * r) >= 0 )
        return true;
    return false;
}

//computa la distancia entre la esfera y la recta O + td. Se obtiene t.
float distancia_esfera(const float c[3], float r, const float o[3], const float d[3]){

    //vector que va desde o hasta el centro de la esfera
    float r_c_prima[DIMENSION];
    //guardo el vector que sale de o hacia el centro de la esfera
    resta(r_c_prima, c, o);

    float temp;

    float beta = producto_interno(r_c_prima, d);
    float gamma = beta * beta - producto_interno(r_c_prima, r_c_prima) + r*r;

    //t = beta +- sqrt(gamma)
    // si beta - sqrt(gamma) > 0 es solucion. Si no lo es entonces es beta + sqrt(gamma).
    //Si ninguna de las dos es solucion entonces no hay interseccion.
    if (gamma <= 0)
        return INFINITO;
    gamma = sqrt(gamma);    
    if((temp = beta - gamma) > 0)
        return  temp; 

    if((temp = beta + gamma) > 0)
        return  temp;

    return INFINITO;
}

//guarda el valor normal de una esfera en un arreglo
void normal_esfera(float normal[DIMENSION], const float c[DIMENSION], float r, const float p[DIMENSION]){

	float b[DIMENSION];
	resta(b, p, c);

	normal[X] = b[X] / r;
	normal[Y] = b[Y] / r;
	normal[Z] = b[Z] / r;
}

int computar_intensidad(const float cs[][DIMENSION], const float rs[], size_t n_esferas, const float luz[DIMENSION], const float o[DIMENSION], const float d[DIMENSION]){

	float normal[DIMENSION];            //donde se guarda la normal de cadaa esfera
	float P[DIMENSION];                 //P = O +td esto guarda a P
	float dist_min = INFINITO;          //distancia minima en esa direccion. Arranco desde el infinito hasta lo mas cercano 
	size_t esfera_min_dist = 0;         //Se busca la esfera mas cercana al observador

	for (size_t i = 0; i < n_esferas; i++){
        //P = O + td
    	float t = distancia_esfera(cs[i], rs[i], o, d);
		if (t != INFINITO && dist_min > t){
			dist_min = t;

            //Asi se cual es la esfera mas cercana a O
			esfera_min_dist = i;
		}
	}

	if (dist_min == INFINITO)
		return 0;

    //P = O +td
	interpolar_recta(P, o, d, dist_min);

	normal_esfera(normal, cs[esfera_min_dist], rs[esfera_min_dist], P);

	for (size_t x = 0; x < n_esferas; x++){
        //Si una esfera tiene otras esferas adelante entonces devuelve el minimo valor de intensidad.
		if ((esfera_min_dist != x) && ((distancia_esfera(cs[x], rs[x], P, luz)) != INFINITO))
			return IA;
	}

    //I = I_a + gamma_s [I_i (L.N)]         Aca gamma_s = 1
	int I = IA + (II * (producto_interno(luz, normal)));
	if (I > II){
		return II;
	}
	else if (I < 0){
		return IA;
	}
	return I;
}


int main(void){
	float o[] = {0, 0, 0};
	int dx;
	int dy;
	int dz = ANCHO / (2 * tan(grados_a_radianes(FOV/2.0)));
    size_t cantidad_esferas = sizeof(centros)/( 3 * sizeof(float));

	printf("P2\n%d %d\n%d\n", ANCHO, ALTO, II);

	for (dy = ALTO / 2; dy > -ALTO / 2; dy--){

		for (dx = -ANCHO / 2; dx < ANCHO / 2; dx++){
			float d[] = {dx, dy, dz};
			normalizar(d);
			printf("%d ", computar_intensidad(centros, radios, cantidad_esferas, luz, o, d));
		}

		printf("\n");
	}
    return 0;
}