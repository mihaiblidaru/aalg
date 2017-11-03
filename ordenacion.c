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
int partir(int* tabla, int ip, int iu, int *pos);
int medio(int* tabla, int ip, int iu, int *pos);
int medio_stat(int* tabla, int ip, int iu, int *pos);
int medio_avg(int* tabla, int ip, int iu, int *pos);
void swap(int* a, int* b);

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


/***********************************************************/
/* Funcion: QuickSort                                     */
/* Fecha: 03-10-2017                                       */
/*                                                         */
/* Funcion que ordena una tabla usando                     */
/* el algoritmo QuickSort                                 */
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
int QuickSort(int* tabla, int ip, int iu){
    int m;
    int obs = 0;

    if(!tabla || iu < ip)
        return ERR;

    if(ip == iu)
        return 0;
    else{
        
        obs += partir(tabla,ip,iu, &m);
        
        if(ip  < m-1){
            obs += QuickSort(tabla, ip, m-1);
        }
        
        if(m+1 < iu){
            obs += QuickSort(tabla, m+1, iu);
        }
    }
    return obs;
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


int partir(int* tabla, int ip, int iu, int *pos){
    int m, k, i, obs = 0;
    obs += medio(tabla,ip, iu, &m); //Añadir las obs del calculo del pivote
    k = tabla[m];
    swap(&tabla[ip], &tabla[m]);
    m = ip;

    for(i=ip+1; i<=iu; i++){
        obs++;
        if(tabla[i] < k){
            m++;
            swap(&tabla[i], &tabla[m]);
        }
    }
    
    swap(&tabla[ip], &tabla[m]);
    *pos = m;
    return obs;
}



/***********************************************************/
/* Funcion: medio                                          */
/* Fecha: 31-10-2017                                       */
/*                                                         */
/* Funcion que  ordena una tabla usando                    */
/* el algoritmo QuickSort                                  */
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
 
 
int medio(int *tabla, int ip, int iu,int *pos){
    *pos = ip;
    return 0;
}

int medio_stat(int*tabla, int ip, int iu, int *pos){
    int med = (ip + iu) / 2;
    
    if (tabla[ip] < tabla[med]){
        if(tabla[med] < tabla[iu]){
            *pos = med;
        }else{
            *pos = tabla[ip] < tabla[iu] ? iu: ip;
        }
    }else{
        if(tabla[med] < tabla[iu]){
            *pos = tabla[ip] < tabla[iu] ? ip : iu;
            
        }else{
            *pos = med;
        }
    }
    
    return 3;
}

int medio_avg(int *tabla, int ip, int iu, int *pos){
    if(!tabla || !pos || iu < ip)
        return ERR;

    *pos = (iu + ip)/2;
    return OK;
}

void swap(int* a, int* b){
    int tmp;
    if(!a || !b)
        return;
    
    tmp = *b;

    *b = *a;
    *a = tmp;
}