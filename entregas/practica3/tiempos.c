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
#include "busqueda.h"
#include "permutaciones.h"

#define MAX_NSEC 1000000000

short tiempo_medio_busqueda(pfunc_busqueda metodo, pfunc_generador_claves generador, int orden, int N, int n_veces, PTIEMPO ptiempo){
    long i, min = LONG_MAX, max = 0, ob;
    int* perm = NULL, *claves = NULL;
    struct timespec t1, t2;
    double suma_ob = 0;
    PDICC dic = NULL;
    int ppos = -1;
    int n_claves = N * n_veces;
    
    if(!metodo || !generador || !ptiempo || n_veces < 1 || N < 1)
        return ERR;
    
    if(!(perm = genera_perm(N)))
        return ERR;
    
    if(!(claves = malloc(N * n_veces * sizeof(int)))){
        free(perm);
        return ERR;
    }

    if(!(dic = ini_diccionario(N, orden))){
        free(perm);
        free(claves);
        return ERR;
    }
    
    insercion_masiva_diccionario(dic, perm, N);

    generador(claves, n_claves, N);
    
    clock_gettime(CLOCK_REALTIME, &t1);
    
    for(i = 0; i < N * n_veces; i++){
        ob = busca_diccionario(dic, claves[i], &ppos, metodo);
        if(ob == ERR){
            libera_diccionario(dic);
            free(claves);
            free(perm);
            return ERR;
        }
        suma_ob += ob;
        if(ob < min) min = ob;
        if(ob > max) max = ob;
    }

    clock_gettime(CLOCK_REALTIME, &t2);
    
    ptiempo->N = N;
    ptiempo->n_elems = N * n_veces;
    ptiempo->min_ob = min;
    ptiempo->max_ob = max;
    ptiempo->medio_ob = suma_ob / (N * n_veces);
    
    /* Tiempo medio */
    if(t1.tv_sec == t2.tv_sec){
        ptiempo->tiempo = t2.tv_nsec - t1.tv_nsec;
    }else{
        ptiempo->tiempo = (t2.tv_sec - t1.tv_sec - 1) * MAX_NSEC;
        ptiempo->tiempo += ((MAX_NSEC - t1.tv_nsec) + t2.tv_nsec);
    }
    ptiempo->N = N;
    ptiempo->tiempo /= (double)(n_veces * N);
    
    free(claves);
    free(perm);
    libera_diccionario(dic);
    return OK;
}


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


short genera_tiempos_busqueda(pfunc_busqueda metodo, pfunc_generador_claves generador,int orden, char* fichero,int num_min, int num_max,int incr, int n_veces){
    int i, tam, j, ret_val = OK;

    PTIEMPO tiempos = NULL;
    
    if(!metodo || !fichero || num_min > num_max || incr < 1 || n_veces < 0 || num_min < 1 || num_max < 1) 
        return ERR;
    
    if(orden != ORDENADO && metodo == bbin)
        return ERR;
      
    tam=(int)ceil((num_max + 1 - num_min) / (double)incr);
    
    
    if(!(tiempos=calloc(tam, sizeof(TIEMPO))))
        return ERR;

    for(j = 0, i = num_min; i <= num_max; i += incr, j++){
        if(tiempo_medio_busqueda(metodo,generador,orden, i, n_veces, &tiempos[j]) == ERR){
            free(tiempos);
            return ERR;
        }
    }
    
    if(guarda_tabla_tiempos(fichero, tiempos, tam) == ERR)
        ret_val =  ERR;
    
    free(tiempos);

    return ret_val;
 
}
