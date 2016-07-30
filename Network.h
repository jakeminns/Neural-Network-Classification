#ifndef NETWORK_H
#define NETWORK_H
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <math.h>
#include <cmath>
#include <fstream>
#include <string>
// #include "Neuron.h"

using namespace std;

class Neuron;

class Network {

	typedef vector<Neuron> Layer;


public:

	Network(const vector<unsigned> &topology);
	void feedForward(const vector<double> &inputVals, int activationType);
	void backProp(const vector<double> &targetVals, int activationType);
	void getResults(vector<double> &resultVals) const;

private:

	double error;
	vector<Layer> neuronLayers; //Each layer contains a layer index and a neuron index within that layer, neuronLayers[layer index][neuron index].

};

#endif /* defined(__Neural_Net__Network_Class__) */
