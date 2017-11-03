/**************************************************/
/* Programa: ejercicio4       Fecha:              */
/* Autores:                                       */
/*                                                */
/* Programa que Comprueba SelectSort              */
/*                                                */
/* Entrada: Linea de comandos                     */
/* -tamanio: numero elementos permutacion         */
/* Salida: 0: OK, -1: ERR                         */
/**************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "ordenacion.h"


int main(int argc, char** argv)
{
    int arr[8] = {4,0,6,2,5,1,7,3};

    int obs = MergeSort(arr, 0, 7);
    
    for(int i = 0; i<8; i++){
        printf("%d ", arr[i]);
    }
    puts("\n");
    
    printf("ObS: %d", obs);
    
    
    return 0;
}

