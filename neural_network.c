#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double sigmoid(double x){
    return (1)/(1+exp(-x));
}

double Dsigmoid(double x){
    return sigmoid(x) * (1- sigmoid(x));
}

#define inputNum 2
#define outputNum 1

int main(){
    double a = 0.156f;

    printf("%f",sigmoid(a));
    printf("\n%f",Dsigmoid(a));




    return 0;
}