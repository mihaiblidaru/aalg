/**
 *
 * Descripcion: Implementacion de funciones de generacion de permutaciones
 *
 * Fichero: permutaciones.c
 * Autor: Mihai Blidaru, Alberto Ayala
 * Version: 1.0
 * Fecha: 16-09-2017
 *
 */


#include <time.h>
#include <stdlib.h>
#include "permutaciones.h"

/***************************************************/
/* Funcion: aleat_num Fecha:                       */
/* Autores:                                        */
/*                                                 */
/* Rutina que genera un numero aleatorio           */
/* entre dos numeros dados                         */
/*                                                 */
/* Entrada:                                        */
/* int inf: limite inferior                        */
/* int sup: limite superior                        */
/* Salida:                                         */
/* int: numero aleatorio                           */
/***************************************************/

int aleat_num(int inf, int sup){ 
    int dif;
  
    if (sup < inf)
        return ERR;
  
    dif = sup - inf + 1;
  
    return rand() % dif + inf;
}

/***************************************************/
/* Funcion: genera_perm Fecha:                     */
/* Autores: Alberto Ayala, Mihai Blidaru           */
/*                                                 */
/* Rutina que genera una permutacion               */
/* aleatoria                                       */
/*                                                 */
/* Entrada:                                        */
/* int n: Numero de elementos de la                */
/* permutacion                                     */
/* Salida:                                         */
/* int *: puntero a un array de enteros            */
/* que contiene a la permutacion                   */
/* o NULL en caso de error                         */
/***************************************************/
int* genera_perm(int N){
    int i, tmp, num, *perm = NULL;
    
    if(N < 1)
        return NULL;
  
    if(!(perm = malloc(N * sizeof(int))))
        return NULL;
  
    for (i = 0; i < N; i++)
        perm[i] = i;  
  
    for(i = 0; i < N; i++){
        tmp = perm[i];
        num = aleat_num(i, N-1); 
        perm[i] = perm[num];
        perm[num] = tmp;
    }

    return perm;
}

/***************************************************/
/* Funcion: genera_permutaciones Fecha:            */
/* Autores: Alberto Ayala, Mihai Blidaru           */
/*                                                 */
/* Funcion que genera n_perms permutaciones        */
/* aleatorias de tamanio elementos                 */
/*                                                 */
/* Entrada:                                        */
/* int n_perms: Numero de permutaciones            */
/* int N: Numero de elementos de cada              */
/* permutacion                                     */
/* Salida:                                         */
/* int**: Array de punteros a enteros              */
/* que apuntan a cada una de las                   */
/* permutaciones                                   */
/* NULL en caso de error                           */
/***************************************************/
int** genera_permutaciones(int n_perms, int N){
    int** permutaciones = NULL;
    int i, j;
    
    if(n_perms < 1 || N < 1)
        return NULL;
    
    permutaciones = calloc(n_perms, sizeof(int*));
    if(!permutaciones)
        return NULL;
        
    for (i = 0; i < n_perms; i++){
        permutaciones[i] = genera_perm(N);
        
        if(permutaciones[i] == NULL){
            for(j=0; j < i; j++){
                free(permutaciones[j]);
            }
            free(permutaciones);
            return NULL;
        }
    }
    
    return permutaciones;
}
