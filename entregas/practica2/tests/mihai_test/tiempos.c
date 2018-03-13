/**
 *
 * Descripcion: Implementacion de funciones de tiempo
 *
 * Fichero: tiempos.c
 * Autor: Alberrto Ayala, Mihai Blidaru
 * Version: 1.0
 * Fecha: 03-09-2017
 *
 */

#include <time.h>
#include <unistd.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include "tiempos.h"
#include "ordenacion.h"
#include "permutaciones.h"

#define MAX_NSEC 1000000000

/******************************************************/
/* Funcion: tiempo_medio_ordenacion                   */
/* Fecha: 03-10-2017                                  */
/* Autores: Mihai Blidaru y Alberto Ayala             */
/*                                                    */
/* Rutina que guarda en una estructura el número de   */
/* permutaciones de una tabla, su tamaño, el número   */
/* medio de obs, el mínimo, el máximo, y el tiempo    */
/* que tarda un método en ordenarlas                  */
/*                                                    */
/* Entrada:                                           */
/* pfunc_ordena metodo: método de ordenación          */
/* int n_perms: número de permutaciones               */
/* int N: Tamaño de las permutaciones                 */
/* PTIEMPO ptiempo: estructura de tipo PTIEMPO        */
/*                                                    */
/* Salida:                                            */
/* short: ERR o OK segun el resultado de la función   */
/******************************************************/
short tiempo_medio_ordenacion(pfunc_ordena metodo, int n_perms, int N, PTIEMPO ptiempo){
    int** perms = NULL;
    struct timespec t1, t2;
    long i, min = LONG_MAX, max = 0, ob;
    double suma_ob = 0;
    
    if(n_perms <1 || N <1 || !ptiempo)
        return ERR;
    
    if(!(perms = genera_permutaciones(n_perms, N)))
        return ERR;
    
    clock_gettime(CLOCK_REALTIME, &t1);
    
    for(i=0; i< n_perms; i++){
        ob = metodo(perms[i], 0, N-1);
	
        suma_ob += ob;
    
        if(ob < min) min = ob;
        if(ob > max) max = ob;
    }
    
    clock_gettime(CLOCK_REALTIME, &t2);
    
    ptiempo->N = N;
    ptiempo->n_elems = n_perms;
    ptiempo->medio_ob = suma_ob / n_perms;
    ptiempo->min_ob = min;
    ptiempo->max_ob = max;
    
    /* Tiempo medio */
    if(t1.tv_sec == t2.tv_sec){
        ptiempo->tiempo = t2.tv_nsec - t1.tv_nsec;
    }else{
        ptiempo->tiempo = (t2.tv_sec - t1.tv_sec - 1) * MAX_NSEC;
        ptiempo->tiempo += ((MAX_NSEC - t1.tv_nsec) + t2.tv_nsec);
    }
    
    ptiempo->tiempo /= (double)n_perms;
    
    
    for(i=0;i < n_perms;i++){
        free(perms[i]);
    }
    
    free(perms);
    
    return OK;
}

/*********************************************************************/
/* Funcion: genera_tiempos_ordenacion                                */
/* Fecha: 10-10-2017                                                 */
/* Autores: Mihai Blidaru y Alberto Ayala                            */
/*                                                                   */
/* Entrada:                                                          */
/* pfunc_ordena metodo: funcion de ordenación                        */
/* char* fichero: Nombre del fichero donde guardar los resultados    */
/* int num_min: tamaño minimo de las tablas                          */
/* int num_max: tamaño máximo de las tablas                          */
/* int inct: incremento                                              */
/* int n_perms: número de permutaciones                              */
/*                                                                   */
/* Salida:                                                           */
/* short: ERR o OK segun el resultado de la función                  */
/*********************************************************************/
short genera_tiempos_ordenacion(pfunc_ordena metodo, char* fichero,int num_min, int num_max, int incr, int n_perms){
    int i, tam, j, ret_val = OK;

    PTIEMPO tiempos = NULL;
    
    if(!metodo || !fichero || num_min > num_max || incr < 1 || n_perms < 1 || num_min < 1 || num_max < 1) 
        return ERR;
      
    tam=(int)ceil((num_max + 1 - num_min) / (double)incr);
    
    
    if(!(tiempos=calloc(tam, sizeof(TIEMPO))))
        return ERR;


    for(j = 0, i = num_min; i <= num_max; i += incr, j++){
        if(tiempo_medio_ordenacion(metodo, n_perms, i, &tiempos[j]) == ERR){
            guarda_tabla_tiempos(fichero, tiempos, j); // guardar los datos obtenidos hasta el momento        
            free(tiempos);
            return ERR;
        }
    }
    
    if(guarda_tabla_tiempos(fichero, tiempos, tam) == ERR)
        ret_val =  ERR;
    
    free(tiempos);

    return ret_val;
}

/*********************************************************************/
/* Funcion: guarda_tabla_tiempos Fecha:                              */
/* Fecha: 10-10-2017                                                 */
/* Autores: Mihai Blidaru y Alberto Ayala                            */
/*                                                                   */
/* Rutina que ecribe el contenido de la estructura pasada por        */
/* argumentos                                                        */
/* Entrada:                                                          */
/* char* fichero: Nombre del fichero donde guardar los resultados    */
/* PTIEMPO tiempo:estructura de tipo PTIEMPO                         */
/* int n_tiempos: número de estructuras que escribe                  */
/*                                                                   */
/* Salida:                                                           */
/* short: ERR o OK segun el resultado de la función                  */
/*********************************************************************/
short guarda_tabla_tiempos(char* fichero, PTIEMPO tiempo, int n_tiempos){
    FILE *fp = NULL;
    int i;
    
    if(!(fp = fopen(fichero, "w"))){
        fprintf(stderr, "ERR: %s no se puede abrir\n", fichero);
        return ERR;
    }
        
        
    for(i = 0; i < n_tiempos; i++){
    	fprintf(fp,"%d\t%.1lf\t%.3lf\t%d\t%d\n", tiempo[i].N, tiempo[i].tiempo, tiempo[i].medio_ob,tiempo[i].max_ob, tiempo[i].min_ob);
    }
    
    fclose(fp);
    return OK;
}


