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
 
void swap(int* a, int* b);

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
    if (tamanio < 0 ) return NULL;
    
    if(orden != ORDENADO && orden != NO_ORDENADO) return NULL;
    
	PDICC diccionario = NULL;
	
	diccionario = calloc (1, sizeof(DICC));
	
	if (diccionario == NULL) return NULL;
	
	diccionario->tamanio = tamanio;
	
	diccionario->orden = orden;
	
	if(!(diccionario->tabla = (int*)malloc(tamanio * sizeof(int)))){
		free(diccionario);
		return NULL;	
	} 
	
	return diccionario;
}

void libera_diccionario(PDICC pdicc)
{
	if(!pdicc)
	    return;
	
	if(pdicc->tabla) // si por alguna razon la tabla no se ha reservado
	   free(pdicc->tabla);
	
	free(pdicc);
}

int inserta_diccionario(PDICC pdicc, int clave){
    int A, j;
	if(!pdicc)
	    return ERR;
	    
	pdicc->tabla[pdicc->n_datos] = clave;
	pdicc->n_datos++;
	
	if(pdicc->orden == ORDENADO){
	    A = pdicc->tabla[pdicc->n_datos - 1];
	    j = pdicc->n_datos - 2;
	    
	    while (j >= 0 && pdicc->tabla[j] > A){
            pdicc->tabla[j+1] = pdicc->tabla[j];
            j--;
	    }
        pdicc->tabla[j+1] = A;
	}
	
	return OK;
}

int insercion_masiva_diccionario (PDICC pdicc,int *claves, int n_claves){
    int i;
	if (!pdicc) return ERR;
	
	if(!claves) return ERR;
	if (n_claves < 1) return ERR;
	
	for(i=0; i < n_claves; i++){
	  
	  inserta_diccionario(pdicc, claves[i]);  
 
	}
	
	return OK;
}

int busca_diccionario(PDICC pdicc, int clave, int *ppos, pfunc_busqueda metodo){
	if(!pdicc || !metodo || !ppos)
		return ERR;
		
	if(pdicc->orden == NO_ORDENADO && metodo == bbin)
		return ERR;
	
	return metodo(pdicc->tabla, 0, pdicc->tamanio - 1, clave, ppos);
}

/* Funciones de busqueda del TAD Diccionario */
int bbin(int *tabla, int P, int U,int clave,int *ppos){
    int tmp;
    int obs = 0;
    if(!tabla)
        *ppos  = NO_ENCONTRADO;
        
    while(P <= U){
    	tmp = (U + P) / 2;
    	obs++;
    	
    	if (tabla[tmp] == clave) {
    		*ppos = tmp;  
    		return obs;
    	}
    	
    	if (tabla[tmp] < clave) {
    		P = tmp + 1; 	
    	}else{
    		U = tmp - 1; 	
    	}
         
    }
    *ppos = NO_ENCONTRADO;
	return obs;
}

int blin(int *tabla,int P,int U,int clave,int *ppos)
{
	int i,obs = 0;

	if (!tabla || P > U || P < 0 ){ 
		*ppos = NO_ENCONTRADO;
		return obs;
	}
	
	for (i = P; i <= U; i++){
		obs++;
	    if(tabla[i]==clave){
	    	*ppos = i;
	    	return obs;
	    }
	}
	
	*ppos = NO_ENCONTRADO;
	return obs;
	
}

int blin_auto(int *tabla,int P,int U,int clave,int *ppos){
	int obs = 0, i;
	if (!tabla || P > U || P < 0 ){
		*ppos = NO_ENCONTRADO;
		return obs;	
	}

	for (i=P; i<=U; i++){
		obs++;
	    if(tabla[i]==clave){
	    	if (i != 0){
	    		*ppos = i-1;
				swap(&tabla[i-1], &tabla[i]);
			}
			return obs;
	    }
	}
	
	*ppos = NO_ENCONTRADO;
	return obs;
}

void swap(int* a, int* b){
    int tmp;
    if(!a || !b)
        return;
    
    tmp = *b;

    *b = *a;
    *a = tmp;
}