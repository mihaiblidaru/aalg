#include "../permutaciones.h"
#include "../tiempos.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_NSEC 1000000000

#define N_PERM 30
int main(){
    
    int i,j,k;
    int** perm;
    struct timespec t1,t2;
    double tiempo;
    
    perm = genera_permutaciones(N_PERM, 5000);
    for(i=1000; i<=6000; i+=1000){
        for(j=0; j<N_PERM; j++){
            for(k=0; k<i; k++){
               perm[j][k] = k;      
            }
        }
        
        clock_gettime(CLOCK_REALTIME, &t1);
        for(j=0; j<N_PERM; j++){
            BubbleSort(perm[j],0, i-1);
        }
        clock_gettime(CLOCK_REALTIME, &t2);
        
        if(t1.tv_sec == t2.tv_sec){
            tiempo = t2.tv_nsec - t1.tv_nsec;
        }else{
            tiempo = ((t2.tv_sec - t1.tv_sec - 1) * MAX_NSEC) + ((MAX_NSEC - t1.tv_nsec) + t2.tv_nsec);
        }
    
        tiempo /= N_PERM*1000000;
        printf("Best for %d:\t%lfns\n", i, tiempo);     
        
        for(j=0; j<N_PERM; j++){
            for(k=0; k<i; k++){
               perm[j][k] = i-1-k;      
            }
        }
        
        clock_gettime(CLOCK_REALTIME, &t1);
        for(j=0; j<N_PERM; j++){
            BubbleSort(perm[j],0, i-1);
        }
        clock_gettime(CLOCK_REALTIME, &t2);
        
        if(t1.tv_sec == t2.tv_sec){
            tiempo = t2.tv_nsec - t1.tv_nsec;
        }else{
            tiempo = ((t2.tv_sec - t1.tv_sec - 1) * MAX_NSEC) + ((MAX_NSEC - t1.tv_nsec) + t2.tv_nsec);
        }
    
        tiempo /= N_PERM*1000000;
        
        printf("Worst for %d:\t%lfns\n\n", i, tiempo);  
    }
    
    
    for(j=0; j<N_PERM; j++){
           free(perm[j]);
    }
    free(perm);
}