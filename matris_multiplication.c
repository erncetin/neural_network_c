#include <stdio.h>
#include <stdlib.h>

#define R1 5
#define C1 4
#define R2 4
#define C2 3


void multiply(int m1[][C1], int m2[][C2]){


    int result[R1][C2] = {0};

    for(int i = 0; i<R1; i++){
        for(int j = 0; j<C2; j++){

            for(int k = 0; k<C1; k++){
                result[i][j] += m1[i][k] * m2[k][j];
            }
            printf("%d\t", result[i][j]);
        }
       printf("\n");
    }

}


int main(){

    int m1[R1][C1] = { { 1, 1, 2, 3 }, { 2, 2, 5, 6}, {1, 4, 6, 8}, {1, 6, 9, 1}, {1, 6, 1, 2} };
 
    int m2[R2][C2] = { { 1, 1, 1 }, { 2, 2, 2 }, { 1, 7, 12 }, { 15, 7, 5 }};

    printf("Input Matrix 1:\n");
    for (int i = 0; i < R1; i++) {
        for (int j = 0; j < C1; j++) {
            printf("%d\t", m1[i][j]);
        }
        printf("\n");
    }
    printf("\nInput Matrix 2:\n");
    for (int i = 0; i < R2; i++) {
        for (int j = 0; j < C2; j++) {
            printf("%d\t", m2[i][j]);
        }
        printf("\n");
    }
    printf("\nResult Matrix:\n");
    multiply(m1, m2);

}