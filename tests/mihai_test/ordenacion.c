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
#include <stdio.h>


int partir(int* tabla, int ip, int iu, int *pos);
int medio(int* tabla, int ip, int iu, int *pos);
int medio_stat(int* tabla, int ip, int iu, int *pos);
int medio_avg(int* tabla, int ip, int iu, int *pos);
int swap(int* a, int* b);


int swap(int* a, int* b){
    int tmp;
    if(!a || !b){
        return ERR;
    }
    tmp = *b;

    *b = *a;
    *a = tmp;
}

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