#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

/* Austin Royce Soriano Pineda
   Math 164 HW 2 Programming Assignment
*/

///////KEY FUNCTIONS
	

//Our objective function. pass in pointers to input and output vectors
//Here f is a function from R cubed to the real numbers.

//  f(x,y,z) = 0.5*(x - 1)^2 + 0.25*(y - 2)^2 + 0.5*(z - 3)^2
float f(float x[]){

	return 0.5*pow(x[0] - 1, 2.0) + 
		0.25*pow(x[1] - 2,2.0) + 
		0.5*pow(x[2]- 3, 2.0);
}

//the gradient of the function f.
// maps R cubed to R cubed.
//I worked this out manually:

//  gradf(x,y,z) = (x - 1, 0.5*y - 1, z - 3)
void gradf(float x[], float y[]){

	y[0] = x[0] - 1;	
	y[1] = 0.5*x[1] - 1;
	y[2] = x[2] - 3; 

	return;
}


///////ITERATION FUNCTIONS

//Takes the kth x vector and writes the k+1th in out[],
//using the step passed in.

void iterate(float in[], float out[], const float step){

	//need to get the gradient of the input vector
	
	float grad [3] = {0,0,0};
	gradf(in, grad);

	for(int i = 0; i < 3; i++){
		out[i] = in[i] - step * grad[i];
	}

	return;
}

//calculates the size of the kth step value,
//using the kth x vector as input.
//For the matrix algebra:
/*
	Q = [1, 0.0, 0
	     0, 0.5, 0
	     0, 0.0, 1]
	b = (1, 1, 3)
	c = 6
	in f(x,y,z) = 0.5*(x,y,z)*Q*(x,y,z) - b*(x,y,z) + c
	the quadratic version of f.
*/

float step_iterate(float x[]){

	const float q[3] = {1, 0.5, 1}; //Q diagonal
	float g[3] = {0,0,0}; //gradient
	gradf(x, g);

	float norm_sqr = g[0]*g[0] + g[1]*g[1] + g[2]*g[2];
	float denom = 0;
	for(int i = 0; i < 3; i++){
		denom += g[i]*q[i]*g[i];
	}
	
	if(norm_sqr == 0 || denom == 0){
		return 0;
	}else{
		return norm_sqr / denom;
	}
}



///////MISC FUNCTIONS

//Prints the values of the x vector in a nice way.

void display(float x[]){

	cout << "The value of x is ("
	<< x[0] << "," << x[1] << "," << x[2] << ")\n";
	float val = f(x);

	return;
}


int main(){

	float x[3] = {3,4,5};
	//simple gradient descent
	float step = 0.7;

	cout << "Simple gradient descent (step = 0.7)\n";
	for(int i=0; i < 10;i++){
		
		iterate(x, x, step); //replaces old x with i+1th iteration
		cout << "For iteration " << i+1 << ":\n";
		display(x);
	}
	
	float y[3] = {3,4,5};
	//steepest descent experiment
	cout << "Steepest gradient descent\n";
	for(int i=0; i < 10;i++){
		step = step_iterate(y);
		iterate(y, y, step);
		cout << "For iteration " << i+1 << ":\n";
		display(y);
	}
	return 0;
}

