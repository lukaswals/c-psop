/******************************************************************************
 * Algoritmo PSO (Particle Swarm Optimization) para permutación de enteros (PSOP)
 * Autores: Labayén Franco - Wals Lucas.
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "operadoresArray.c"
#include "operadoresPSOP.c"
#include "instanciaATSP.c"
#include "resultadosPSOP.c"

/* 
 * Definicion de las estructuras necesarias 
 */
typedef struct {
    int mejor_valor_local;  //Valor de fitness valuada en p.
    int valor_local;        //Valor de fitness valuada en x.
    int x[70];              //Vector con la posición actual.
    int v[70][2];           //Vector con la velocidad actual.
    int p[70];              //Vector con la mejor posición local explorada.
} Particula;

typedef struct {
    Particula part[500];
    int mejor_valor_global; //Valor de fitness valuada en g.
    int g[70];              //Vector con la mejor posición global explorada.
} Enjambre;


/*
 * Funcion Heurística/Fitness 
 */
int funcion(int cant_ciud, int tour[], int costos[cant_ciud][cant_ciud]) {
    int result = 0, k;
    for(k = 0; k < cant_ciud; k++) {
        result = result + costos[tour[k]][tour[(k+1)%cant_ciud]];
    }
    return result;
}

/* 
 * Algoritmo PSO basado en permutación de enteros 
 */
void algoritmoPSOP(char *instancia, int cant_part, int lim_iter, float c1, float c2) {

    //Cargamos la matriz de costos correspondiente a la instancia del problema
    int cant_ciud = calc_dimension(instancia);
    int costos[cant_ciud][cant_ciud];
    cargar_matriz(instancia, cant_ciud, costos);

    //Dejamos abierta la posibilidad de que la velocidad sea de tamaño variable
    int dim_v = cant_ciud;

    //Declaramos las variables necesarias para correr el algoritmo
    int i,j;
    int v1[cant_ciud], v2[cant_ciud];
    int iter_s;
    Enjambre nube;

    //Llamamos a las funciones necesarias para generar números aleatorios
    srand(time(NULL));
    srand48(time(NULL));

    //Declaramos las variables necesarias para obtener el tiempo de ejecución
    float t1, t2, t3, tiempo_t, tiempo_s; 
    t1 = clock();

    //Inicializamos un enjambre de forma totalmente aleatoria
    nube.mejor_valor_global = 2147483647;
    for(j = 0; j < cant_part; j++) {
        //Creamos una posición
        randArray(cant_ciud, nube.part[j].x);
        arrayCP(cant_ciud, nube.part[j].p, nube.part[j].x);
        //Creamos una velocidad
        randArray(cant_ciud, v1);
        randArray(cant_ciud, v2);
        restaPSOP(dim_v, v1, v2, nube.part[j].v);
        //Calculamos los valores de fitness
        nube.part[j].valor_local = funcion(cant_ciud, nube.part[j].x, costos);
        nube.part[j].mejor_valor_local = nube.part[j].valor_local;
        if(nube.part[j].mejor_valor_local < nube.mejor_valor_global) {
            arrayCP(cant_ciud, nube.g, nube.part[j].p);
            nube.mejor_valor_global = nube.part[j].mejor_valor_local;
        }
    }
        
    //Comenzamos la  iteración del algoritmo
    for(i = 0; i < lim_iter; i++) {
        //Actualizamos la velocidad y posición de cada partícula
        for(j = 0; j < cant_part; j++) {
            actualizacionPSOP(cant_ciud, dim_v, nube.part[j].v, c1, c2, 
                nube.part[j].x, nube.part[j].p, nube.g);
            movimientoPSOP(cant_ciud, dim_v, nube.part[j].x, nube.part[j].v);
        }
        //Actualizamos los valores de fitness
        for(j = 0; j < cant_part; j++) {
            nube.part[j].valor_local = funcion(cant_ciud, nube.part[j].x, costos);
            if(nube.part[j].valor_local < nube.part[j].mejor_valor_local) {
                arrayCP(cant_ciud, nube.part[j].p, nube.part[j].x);
                nube.part[j].mejor_valor_local = nube.part[j].valor_local;
                if(nube.part[j].mejor_valor_local < nube.mejor_valor_global) {
                    arrayCP(cant_ciud, nube.g, nube.part[j].p);
                    nube.mejor_valor_global = nube.part[j].mejor_valor_local;
                    //Guardamos la iteración en donde se encontró la mejor solución
                    iter_s = i;
                    t2 = clock();
                    //tiempo_s = (t2-t1)/(double) CLOCKS_PER_SEC;
                }
            }
        }
    }

    //Calculamos el tiempo en encontrar la mejor solución
    tiempo_s = (t2-t1)/(double) CLOCKS_PER_SEC;

    //Calculamos el tiempo de ejecución
    t3 = clock();
    tiempo_t = (t3-t1)/(double) CLOCKS_PER_SEC;

    //Almacenamos en un archivo los resultados de la ejecución
    registrar(cant_part, iter_s, lim_iter, c1, c2, cant_ciud, 
        nube.mejor_valor_global, tiempo_t, tiempo_s);
}

/* 
 * Main 
 */
int main(int argc, char **argv) {

    if(argc != 6){
        printf("Faltan parametros. Los parametros en orden son: \n");
        printf("psop nombre_instancia cant_particulas cant_iteraciones valor_c1 valor_c2\n");
        printf("Ejemplo: psop br17.atsp 50 10000 0.9 1.2\n");
        exit(EXIT_FAILURE);
    }

    int particulas = (int) strtol(argv[2], NULL, 10);
    int iteraciones = (int) strtol(argv[3], NULL, 10);
    float c1 = strtof(argv[4], NULL);
    float c2 = strtof(argv[5], NULL);

    algoritmoPSOP(argv[1], particulas, iteraciones, c1, c2);
    return 0;
}
