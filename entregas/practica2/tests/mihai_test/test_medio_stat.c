#include <stdio.h>
int medio_stat(int*tabla, int ip, int iu, int *pos);


int main(){
    int i,j,k;
    
    int tabla[3] = {0,0,0};
    
    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            for(k=0; k<3; k++){
                tabla[0] = i;
                tabla[1] = j;
                tabla[2] = k;
                int pos = 0;
                medio_stat(tabla, 0,2,&pos);
                printf("Tabla: %d %d %d - med = (pos = %d)\n", i,j,k, pos);
            }
        }    
    }
    
    
}