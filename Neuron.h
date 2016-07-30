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
	void neuronFeedForward(const Layer &previousLayer, int activationType);
	void calculateOutputGradients(double targetVal, int activationType);
	void calculatehiddenGradients(const Layer &nextLayer, int activationType);
	void weightInputUpdate(Layer &prevLayer);
	static double eta;
	static double alpha;

private: 
	static double activationFunction(double x, int activationType);
	static double activationFunctionDerivative(double x, int activationType);
	double neuronOutputVals;
	vector<Connection> neuronWeights;
	static double randomWeight(void) { return rand()/double(RAND_MAX);}
	unsigned neuronIndex;
	double gradient;
	double sumDOW(const Layer &nextLayer) const;




};

#endif /* defined(__Neural_Net__Neuron_Class__) */
