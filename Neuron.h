//Neuron.h


#ifndef NEURON_H

#define NEURON_H

#include <vector>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <math.h>
#include <cmath>
#include <fstream>
#include <string>
#include "Network.h"


using namespace std;



class Neuron {

		typedef vector<Neuron> Layer;

			struct Connection {
	double weight;
	double deltaweight;
	};


public:
	Neuron(unsigned numberOutputs, unsigned currentNeuronIndex);
	void setOutputValue(double value) {neuronOutputVals = value;}
	double getOutputVal(void) const {return neuronOutputVals; }
	void neuronFeedForward(const Layer &previousLayer);
	void calculateOutputGradients(double targetVal);
	void calculatehiddenGradients(const Layer &nextLayer);
	void weightInputUpdate(Layer &prevLayer);

private: 
	static double activationFunction(double x);
	static double activationFunctionDerivative(double x);
	double neuronOutputVals;
	vector<Connection> neuronWeights;
	static double randomWeight(void) { return rand()/double(RAND_MAX);}
	unsigned neuronIndex;
	double gradient;
	double sumDOW(const Layer &nextLayer) const;
	static double eta;
	static double alpha;



};

#endif /* defined(__Neural_Net__Neuron_Class__) */
