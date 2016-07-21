//Neuron Class

#include <vector>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <math.h>
#include <cmath>
#include <fstream>
#include <string>
#include "Neuron.h"
#include "Network.h"



using namespace std;




typedef vector<Neuron> Layer;


double Neuron::eta = 0.03;
double Neuron::alpha = 0.5;


Neuron::Neuron(unsigned numberOutputs, unsigned currentNeuronIndex) { //Neuron constructor adds vector of connection (neuronWeights) to neuron and adds random weight to each connection

	for (unsigned c = 0; c < numberOutputs; c++){ //Generating a number of outputs for each neuron depending on the numberOutputs value passed in

		neuronWeights.push_back(Connection()); //adding a connection (weight and delta weight) to each neuron
		neuronWeights.back().weight = randomWeight(); //assign random value of weight to most recent connection using randomWeight function
	}

	neuronIndex = currentNeuronIndex;
}

void Neuron::neuronFeedForward(const Layer &previousLayer) {

	double sum = 0.0;

	for (unsigned n = 0; n < previousLayer.size(); n++) {

		sum += previousLayer[n].getOutputVal() * previousLayer[n].neuronWeights[neuronIndex].weight; // Sum the multiple of neuron weight by output value for each incoming neuron from previous layer


	}

	neuronOutputVals = Neuron::activationFunction(sum); //neuron output value is the activation function applied to the sum, sum = sum of x*w + b. activation function is sigmoid.

}


double Neuron::activationFunction(double x) {

	return tanh(x); //Return sigmoid function

}




void Neuron::weightInputUpdate(Layer &prevLayer) { //Update weights in the connection container of the preceding layer

	for(unsigned n = 0; n < prevLayer.size(); n++){

		Neuron &neuron = prevLayer[n];
		double oldDeltaWeight = neuron.neuronWeights[neuronIndex].deltaweight;

		double newDeltaWeight = eta * neuron.getOutputVal() * gradient + alpha * oldDeltaWeight;

		neuron.neuronWeights[neuronIndex].deltaweight = newDeltaWeight;
		neuron.neuronWeights[neuronIndex].weight += newDeltaWeight;



	}

}



double Neuron::sumDOW(const Layer &nextLayer) const {

	double sum = 0.0;

	for(unsigned n = 0; n < nextLayer.size() - 1; n++){

		sum+= neuronWeights[n].weight * nextLayer[n].gradient; //Sum of neuron weight multiplied by gradient in next layer

	}

	return sum;
}


void Neuron::calculatehiddenGradients(const Layer &nextLayer) {

	double dow =sumDOW(nextLayer); //No target value so difference is calculated from the sum of the derivaties of the weights in the next layer  
	gradient = dow * Neuron::activationFunctionDerivative(neuronOutputVals); //Hidden gradient 

}


void Neuron::calculateOutputGradients(double targetVal) {

	double delta = targetVal - neuronOutputVals; //Difference between target value and neuron output
	gradient = delta * Neuron::activationFunctionDerivative(neuronOutputVals); //Multiply difference by the derivative of the output to give the gradient of the output layer


}



double Neuron::activationFunctionDerivative(double x) {

	double sigmoid = 1/(1+pow(2.71828,-x));

	return (1/cosh(x))*(1/cosh(x)); //Return derivative of sigmoid function


}





