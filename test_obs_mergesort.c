#include "ordenacion.c"
#include <math.h>
#include <stdio.h>

void print_table(int* arr, int size){
    for(int i=0; i<size;i++)
        printf("%d ", arr[i]);
    
    printf("\n");
}

int shuffle(int* arr, int size){
    int obs = 0;
    if(size < 2){
        return 0;
    }
    
    int* a = malloc(size/2 * sizeof(int));
    int* b = malloc(size/2 * sizeof(int));
    for(int i=0; i< size/2; i++){
        a[i] = arr[i*2];
        b[i] = arr[1 + (i*2)];
    }
    
    for(int i=0; i<size/2;i++){
        arr[i] = a[i];        
    }
    
    for(int i=size/2; i<size;i++){
        arr[i] = b[i - size/2];        
    }
    free(a);
    free(b);
    obs += size-1;
    obs += shuffle(arr, size/2);
    obs += shuffle(arr + size/2, size/2);
    return obs;
}


int main(){
    
    int max_size = 268435456;
    int* arr;
    
    arr = malloc(max_size * sizeof(int));
    
    for(int i=0; i<24;i++){
        int size = pow(2, i);
        
        for(int j = 0; j< size;j++){
            arr[j] = j;
        }
       
        int obs = shuffle(arr, size);
        int med = MergeSort(arr,0, size-1);
        printf("Tamaño: %d\t\tTeorico:%d \t\t Medido:%d\t%s\n",size, obs, med, obs == med ? "\033[32;1mOK\033[0m":"\033[31;1mERR\033[0m");
    }
    
    return 0;
}