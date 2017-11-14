/**
 *
 * Descripcion: Implementacion funciones para busqueda 
 *
 * Fichero: busqueda.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 11-11-2016
 *
 */

#include "busqueda.h"

#include <stdlib.h>
#include <math.h>

/**
 *  Funciones de geracion de claves
 *
 *  Descripcion: Recibe el numero de claves que hay que generar
 *               en el parametro n_claves. Las claves generadas
 *               iran de 1 a max. Las claves se devuelven en 
 *               el parametro claves que se debe reservar externamente
 *               a la funcion.
 */
  
/**
 *  Funcion: generador_claves_uniforme
 *               Esta fucnion genera todas las claves de 1 a max de forma 
 *               secuencial. Si n_claves==max entonces se generan cada clave
 *               una unica vez.
 */
void generador_claves_uniforme(int *claves, int n_claves, int max)
{
  int i;

  for(i = 0; i < n_claves; i++) claves[i] = 1 + (i % max);

  return;
}

/**
 *  Funcion: generador_claves_potencial
 *               Esta funcion genera siguiendo una distribucion aproximadamente
 *               potencial. Siendo los valores mas pequenos mucho mas probables
 *               que los mas grandes. El valor 1 tiene una probabilidad del 50%,
 *               el dos del 17%, el tres el 9%, etc.
 */
void generador_claves_potencial(int *claves, int n_claves, int max)
{
  int i;

  for(i = 0; i < n_claves; i++) {
    claves[i] = (1+max) / (1 + max*((double)rand()/RAND_MAX));
  }

  return;
}

PDICC ini_diccionario (int tamanio, char orden)
{
    if (tamanio<0) return NULL;
    
    if(orden != ORDENADO && orden != ORDENADO) return NULL;
    
	PDICC diccionario;
	
	diccionario =calloc (1, sizeof(DICC));
	
	if (diccionario == NULL) return NUll;
	
	diccionario->tamanio = tamanio;
	
	diccionario->orden = orden;
	
	if(diccionario->tabla = calloc(1,sizeof(int)) == NULL) return NULL;
	
	
	
	return diccionario;

}

void libera_diccionario(PDICC pdicc)
{
	if(!pdicc)
	    return;
	
	if(pdicc->tabla) // si por alguna razon la tabla no se ha reservado
	   free(pdicc->tabla);
	
	free(pdicc)
}

int inserta_diccionario(PDICC pdicc, int clave){
    int A, j;
	if(!pdicc)
	    return ERR;
	    
	pdicc->tabla[pdicc->n_datos] = clave;
	pdicc->n_datos++;
	
	if(pdicc->orden == ORDENADO){
	    A = pdicc->tabla[pdicc->n_datos - 1];
	    j = pdicc->n_datos - 1;
	    
	    while (j >= 0 && pdicc->tabla[j] > A){
            pdicc->tabla[j+1] = pdicc->tabla[j];
            j--;
	    }
        pdicc->tabla[j+1] = A;
	}
	return OK;
}

int insercion_masiva_diccionario (PDICC pdicc,int *claves, int n_claves)
{
    int i;
	if (!pdicc) return ERR;
	if(!claves) return ERR;
	if (n_claves < 1) return ERR;
	
	for(i=0; i < n_claves; i++){
	  
	  inserta_diccionario(pdicc,clave[i]);  
	    
	}
	
	return OK;
}

int busca_diccionario(PDICC pdicc, int clave, int *ppos, pfunc_busqueda metodo)
{
	/* vuestro 
}


/* Funciones de busqueda del TAD Diccionario */
int bbin(int *tabla, int P, int U,int clave,int *ppos){
    int tmp;
    int obs;
    if(!tabla)
        return NO_ENCONTRADO;
    do{
        tmp = (U - P) / 2;
        if(tabla[tmp] == clave){
            *ppos = tmp;
      	     return ENCONTRADO;     
        }else if(tabla[tmp] < clave){
            U = tmp;
        }else if(tabla[tmp] > clave){
            P = tmp;
        }
    }while(P != U);
	RETURN NO_ENCONTRADO
}

int blin(int *tabla,int P,int U,int clave,int *ppos)
{
	int i;
	if (!tabla || P > U || P < 0 ) return NO_ENCONTRADO;
	
	for (i=P;i<=U;i++){
	    if(tabla[i]==clave){
	    	*ppos = i;
	    	return ENCONTRADO;
	    }
	
	    
	}
	return NO_ENCONTRADO;
}

int blin_auto(int *tabla,int P,int U,int clave,int *ppos)
{
	/* vuestro codigo */
}
