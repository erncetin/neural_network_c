#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#define input_num 2
#define output_num 1
#define hidden_layer_num 2
#define traninig_set_num 4
#define learning_rate 0.4
#define EPOCHS 10000


// Activation function (squish to 0-1)
double sigmoid(double x){
    return (1/(1+exp(-x)));
}
// derivative activation function 
double Dsigmoid(double x){
    return x * (1.0 - x);
}
// Random weights
double init_weights(){
    return ((double)rand() / (double)(RAND_MAX)) * 2.0 - 1.0;
}
void init_bias(double *bias_array, int size){
    for (int i = 0; i < size; i++){
        bias_array[i] = 0.0;
    }
}
/*  https://benpfaff.org/writings/clc/shuffle.html
void shufflee(int *array, size_t n){
    if (n > 1) {
        size_t i;
	for (i = 0; i < n - 1; i++) {
	  size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
	  int t = array[j];
	  array[j] = array[i];
	  array[i] = t;
	}
    }
} */
void shuffle(int *array, int n){
    for(int i = 0;i<n;i++){
        bool check;
        int num;
        do{
            check = true;
            num = rand() % n;
                for(int j = 0 ; j < i ; j++){
                    if(array[j] == num){
                        check = false;
                        break;
                    }
                }
        }while(!check);
        array[i] = num;
    }
}

void transpose(int rows, int cols, double matrix[][cols], double result[][rows]){
    for(int i = 0;i<rows;i++){
        for(int j = 0;j<cols;j++){
            result[j][i] = matrix[i][j];
        }
    }
}


void matrix_multiplication(int R1, int C1, int C2,
                        double layer_bias[], 
                        double m1[][C1],
                        double m2[][C2],
                        double layer[C2][1]){



    double result[R1][C2];

    for(int i = 0;i<R1;i++){
        for(int j = 0;j<C2;j++){
            result[i][j] = 0.0;
        }
    }

    for(int i = 0; i<R1; i++){
        for(int j = 0; j<C2; j++){
            for(int k = 0; k<C1; k++){
                result[i][j] += m1[i][k] * m2[k][j];    
            }
            //printf("Result[%d][%d]: ", i, j);
            //printf("%f ", result[i][j]);
        }
       //printf("\n");
    }
    //printf("\nRESULT MATRIX\n");

    for(int i = 0; i<R1; i++){
        for(int j = 0; j<C2; j++){
            //printf("%f ", result[i][j]);
        }
       //printf("\n");
    }

    // copy result to layer adding bias
    for(int i = 0; i < R1; i++){
        layer[i][0] = layer_bias[i]+ result[i][0];
    }


}
// TODO
void initialize_weights(int rows, int cols, double weight_array[rows][cols]){
    for(int i = 0; i < rows; i ++){
        for(int j = 0; j < cols; j++){
            weight_array[i][j] = init_weights();
        }
    }

}


// TODO
void forward_prop(double hidden_layer_bias[],
                double output_layer_bias[],
                double hidden_layer[][1], 
                double output_layer[][1], 
                double hidden_layer_weights[][hidden_layer_num], 
                double output_layer_weights[][output_num], 
                double input_data[][input_num]){

    // Hidden layer
    //printf("Hidden Layer Calculation:\n");
    matrix_multiplication(input_num, hidden_layer_num, 1, hidden_layer_bias, hidden_layer_weights, input_data, hidden_layer);
    hidden_layer[0][0] = sigmoid(hidden_layer[0][0]);
    hidden_layer[1][0] = sigmoid(hidden_layer[1][0]);

    
    // Output layer
    //printf("Output Layer Calculation:\n");
    matrix_multiplication(1, hidden_layer_num, 1, output_layer_bias, output_layer_weights, hidden_layer , output_layer);
    output_layer[0][0] = sigmoid(output_layer[0][0]);
    //printf("Final output: %f\n", output_layer[0][0]);

}

// TODO
void backward_prop(double hidden_layer_bias[],
                double output_layer_bias[],
                double hidden_layer[][1], 
                double output_layer[][1], 
                double hidden_layer_weights[][hidden_layer_num], 
                double output_layer_weights[][output_num],
                double training_examples[][input_num], 
                double expected_outputs[][output_num]){

    // Calculate output layer error
    double output_layer_delta[output_num][1];
    double output_error[output_num][1];
    double hidden_layer_deltas[hidden_layer_num][1];
    output_error[0][0] = expected_outputs[0][0] - output_layer[0][0];



    // Calculate output layer gradients
    output_layer_delta[0][0] = output_error[0][0] * Dsigmoid(output_layer[0][0]);
    // calculate hidden layer deltas
    for(int i = 0; i < hidden_layer_num; i++){
        hidden_layer_deltas[i][0] = Dsigmoid(hidden_layer[i][0]) * output_layer_weights[i][0] * output_layer_delta[0][0];
    }



    //update output layer weights
    for(int i = 0; i < hidden_layer_num; i++){
        output_layer_weights[i][0] += hidden_layer[i][0] * output_layer_delta[0][0] * learning_rate;
    }
    output_layer_bias[0] += learning_rate * output_layer_delta[0][0];


    //update hidden layer weights
    for(int i = 0; i < hidden_layer_num; i++){
        for(int j = 0; j < input_num;j++){
            hidden_layer_weights[i][j] += hidden_layer_deltas[i][0] * training_examples[0][j] * learning_rate;
        }
        hidden_layer_bias[i] += learning_rate * hidden_layer_deltas[i][0];
    }

    // print updated weights and biases
    /*
    printf("Updated Weights and Biases:\n");
    for(int i = 0; i < hidden_layer_num;i++){
        for(int j = 0; j < output_num ;j++){
            printf("Output layer weight[%d][%d]: %f\n", i, j, output_layer_weights[i][j]);
        }
    }
    for(int i = 0; i < input_num;i++){
        for(int j = 0; j < hidden_layer_num ;j++){
            printf("Hidden layer weight[%d][%d]: %f\n", i, j, hidden_layer_weights[i][j]);
        }
    }
    for(int i = 0; i < hidden_layer_num;i++){
        printf("Hidden layer bias[%d]: %f\n", i, hidden_layer_bias[i]);
    }
    for(int i = 0; i < output_num;i++){
        printf("Output layer bias[%d]: %f\n", i, output_layer_bias[i]);
    }
    
    
*/
}



int main(){
    srand(time(NULL));

    // Training set
    double training_inputs[traninig_set_num][input_num] = {{0.0, 0.0},
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

    double output_layer[output_num][1];
    double hidden_layer[hidden_layer_num][1];

    double hidden_layer_bias[hidden_layer_num];
    double output_layer_bias[output_num];
    init_bias(hidden_layer_bias, hidden_layer_num);
    init_bias(output_layer_bias, output_num);

    double hidden_layer_weights[input_num][hidden_layer_num];
    double output_layer_weights[hidden_layer_num][output_num];
    initialize_weights(input_num, hidden_layer_num, hidden_layer_weights);
    initialize_weights(hidden_layer_num, output_num, output_layer_weights);

    printf("initialized weights\n");
    for(int i = 0; i < input_num;i++){
        for(int j = 0; j < hidden_layer_num ;j++){
            printf("Hidden layer weight[%d][%d]: %f\n", i, j, hidden_layer_weights[i][j]);
        }
    }
    for(int i = 0; i < hidden_layer_num;i++){
        for(int j = 0; j < output_num ;j++){
            printf("Output layer weight[%d][%d]: %f\n", i, j, output_layer_weights[i][j]);
        }
    }

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
    int array[traninig_set_num];
    
    // TRAINING LOOP
    
    double training_example[1][2];
    memcpy(training_example[0], training_inputs[2], sizeof(double)*2);
    double expected_output[1][1];
    memcpy(expected_output[0], training_outputs[0], sizeof(double));
    
    forward_prop(hidden_layer_bias, output_layer_bias, hidden_layer, output_layer, hidden_layer_weights, output_layer_weights, training_example);

    printf("Final output: %f\n", output_layer[0][0]);

    for(int i = 0; i<2;i++){
        for(int j = 0;j<1;j++){
            printf("Hidden layer [%d][%d]: %f\n", i, j, hidden_layer[i][j]);
        }
    }

    backward_prop(hidden_layer_bias, output_layer_bias, hidden_layer, output_layer, hidden_layer_weights, output_layer_weights, training_example, expected_output);

    // training loop
    for(int i = 0; i< EPOCHS; i++){
        shuffle(array, traninig_set_num);
        for(int j = 0; j < traninig_set_num; j++){
            int index = array[j];
            memcpy(training_example[0], training_inputs[index], sizeof(double)*2);
            memcpy(expected_output[0], training_outputs[index], sizeof(double));
            forward_prop(hidden_layer_bias, output_layer_bias, hidden_layer, output_layer, hidden_layer_weights, output_layer_weights, training_example);
            backward_prop(hidden_layer_bias, output_layer_bias, hidden_layer, output_layer, hidden_layer_weights, output_layer_weights, training_example, expected_output);
        }
        printf("Epoch %d complete\n", i);
    }
    // test after training
    printf("Testing after training:\n");
    for(int i = 0; i < traninig_set_num; i++){
        memcpy(training_example[0], training_inputs[i], sizeof(double)*2);
        forward_prop(hidden_layer_bias, output_layer_bias, hidden_layer, output_layer, hidden_layer_weights, output_layer_weights, training_example);
        printf("Input: [%f, %f] => Output: %f\n", training_inputs[i][0], training_inputs[i][1], output_layer[0][0]);
    }
    
    return 0;
}