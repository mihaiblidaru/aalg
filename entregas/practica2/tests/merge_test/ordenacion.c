/**
 *
 * Descripcion: Implementacion de funciones de ordenacion 
 *
 * Fichero: ordenacion.c
 * Autores: Alberto Ayala, Mihai Blidaru
 * Version: 1.0
 * Fecha: 26-09-2017
 *
 */

#include "ordenacion.h"
#include <math.h>
#include <stdlib.h>

int merge(int* tabla, int ip, int iu, int imedio);
/***********************************************************/
/* Funcion: Bubblesort                                     */
/* Fecha: 03-10-2017                                       */
/*                                                         */
/* Funcion que ordena una tabla usando                     */
/* el algoritmo BubbleSort                                 */
/*                                                         */
/* Entrada:                                                */
/* int* tabla: un puntero a la tabla que se quiere ordenar */
/* int ip: indice inferior                                 */
/* int iu: indice superior                                 */
/*                                                         */
/* Salida:                                                 */
/* Número de OBs del algoritmo                             */
/*                                                         */
/***********************************************************/
int BubbleSort(int* tabla, int ip, int iu){
    int i=iu, j, aux;
    int ob = 0;
    
    if (!tabla ||  ip < 0 || iu < 0 || iu < ip)
        return ERR;
    
    while (i>=ip+1){
        for(j = ip; j < i; j++){
            ob++;
            if( tabla[j] > tabla[j+1]){ 
                aux=tabla[j];
                tabla[j]=tabla[j+1];
                tabla[j+1]=aux;
            }
        }
        i--;
    }
    return ob;
}

int medio_avg(int *tabla, int ip, int iu, int *pos){
    if(!tabla || !pos || iu < ip)
        return ERR;
    
    *pos = (iu+ip)/2;
    return OK;
}


/***********************************************************/
/* Funcion: MergeSort                                     */
/* Fecha: 03-10-2017                                       */
/*                                                         */
/* Funcion que ordena una tabla usando                     */
/* el algoritmo MergeSort                                 */
/*                                                         */
/* Entrada:                                                */
/* int* tabla: un puntero a la tabla que se quiere ordenar */
/* int ip: indice inferior                                 */
/* int iu: indice superior                                 */
/*                                                         */
/* Salida:                                                 */
/* Número de OBs del algoritmo                             */
/*                                                         */
/***********************************************************/
int MergeSort(int* tabla, int ip, int iu){
    int medio;
    int n_obs = 0;
    
    if(!tabla || ip > iu) 
        return -1;
    
    if(ip == iu) 
        return 0; 
    
    medio = floor((ip + iu)/2);
    
    n_obs += MergeSort(tabla, ip, medio);
    n_obs += MergeSort(tabla, medio + 1, iu);
    n_obs += merge(tabla, ip, iu, medio);
    
    return n_obs;
  
}

int merge(int* tabla, int ip, int iu, int imedio){
    int * aux = NULL, i = ip, j = imedio + 1, k = 0;
    
    int n_obs = 0; 
    
    if(!tabla || ip > imedio || imedio > iu) 
        return 0;
    
    if(!(aux = malloc(((iu-ip+1) * sizeof(int)))))
        return -1;
    
    while (i<=imedio && j<=iu){
        n_obs++;
        if(tabla[i] < tabla[j]){
            aux[k] = tabla[i];
            i++;
            
        }else{
            aux[k] = tabla[j];
            j++;
        }
        k++;

    }
    
    if(i>imedio){
        while(j<=iu){
            aux[k] = tabla[j];
            j++;
            k++;
        }  
    }else if(j>iu){
        while(i<=imedio){
            
            aux[k] = tabla[i];
            i++;
            k++;
            
        }
    }
    
    for(i=ip, j=0; i<=iu; j++, i++){
                tabla[i] = aux[j];
    }
    
    free(aux);
    return n_obs;
}

