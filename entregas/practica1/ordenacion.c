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



