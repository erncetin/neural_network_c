#include <stdio.h>
#include <stdlib.h>
#include <math.h>


// Activation function (squish to 0-1)
double sigmoid(double x){
    return (1)/(1+exp(-x));
}
// derivative activation function 
double Dsigmoid(double x){
    return sigmoid(x) * (1- sigmoid(x));
}
// Random weights
double init_weights(){
    return ((double)rand() / (double)(RAND_MAX));
}


// https://benpfaff.org/writings/clc/shuffle.html
void shuffle(int *array, size_t n){
    if (n > 1) {
        size_t i;
	for (i = 0; i < n - 1; i++) {
	  size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
	  int t = array[j];
	  array[j] = array[i];
	  array[i] = t;
	}
    }
}


#define input_num 2
#define output_num 1
#define hidden_layer_num 2
#define traninig_set_num 4


int main(){
    const double learning_rate = 0.1;

    // Training set
    double training__inputs[traninig_set_num][input_num] = {{0.0, 0.0},
                                                            {0.0, 1.0},
                                                            {1.0, 1.0},
                                                            {1.0, 0.0}};

    // Training set output
    double training_outputs[traninig_set_num][output_num] = {{0.0},
                                                            {0.0},
                                                            {1.0},
                                                            {0.0}}; 
    // Order to shuffle
    int trainingset_order[] = {0,1,2,3};

    double output_layer[output_num];
    double hidden_layer[hidden_layer_num];

    double hidden_layer_bias[hidden_layer_num];
    double output_layer_bias[output_num];

    double hidden_layer_weights[input_num][hidden_layer_num];
    double output_layer_weights[hidden_layer_num][output_num];


    //initialize weight arrays

    for(int i = 0; i < input_num;i++){
        for(int j = 0; j < hidden_layer_num ;j++){
            hidden_layer_weights[i][j] = init_weights();
        }
    }

    for(int i = 0; i < hidden_layer_num;i++){
        for(int j = 0; j < output_num ;j++){
            output_layer_weights[i][j] = init_weights();
        }
    }


    return 0;
}