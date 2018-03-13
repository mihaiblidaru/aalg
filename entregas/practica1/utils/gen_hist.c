#include "../permutaciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N_NUMS 100000000
#define SHOW_PERCENTAGE 0

int main(int argc, char** argv){
    long table[10] = {0};
    int i;
    
    srand(time(NULL));
    
    for(i=0; i< N_NUMS; i++){
        table[aleat_num(0,9)]++;
    }
    if(SHOW_PERCENTAGE){
        for(i=0; i < 10; i++){
            printf("%d %ld\t%.4f%%\n", i, table[i], (double)table[i]/N_NUMS * 100);
        }    
    }else{
        for(i=0; i < 10; i++){
            printf("%d\t%ld\n", i, table[i]);
        }    
    }
    
    return 0;
}