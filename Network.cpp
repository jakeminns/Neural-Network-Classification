
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <math.h>
#include <cmath>
#include <fstream>
#include <string>
#include "Network.h"
#include "Neuron.h"


using namespace std;

typedef vector<Neuron> Layer;


Network::Network(const vector<unsigned> &topology) { //Network Constructor builds the network of layers containing neurons dependent on the topology vector

	unsigned numberLayers = topology.size(); //number of layers descirbes how many layers in the neural network from the input topology vector.

	for(unsigned layerIndex = 0; layerIndex <  numberLayers; layerIndex++){ //Generate layers of neurons in neuronLayer from the topology specified.
		
		neuronLayers.push_back(Layer()); //Add Layer of neurons to neuronLayer vector.

		unsigned numberOutputs;

		if( layerIndex == topology.size() - 1){ //If layer index is output layer (final layer) add zero outputs
			numberOutputs = 0;
		} else { //Otherwise the number of oututs of the neuron is the number of neurons in the next level
			numberOutputs = topology[layerIndex +1];
		}
		

		for(unsigned neuronIndex = 0; neuronIndex <= topology[layerIndex]; neuronIndex++){ //Add a number of neurons to each layer vector defined by how many specifed in the topology + a bias neuron (<=).

			neuronLayers.back().push_back(Neuron(numberOutputs, neuronIndex)); //Add neuron to most recent neuronLayers layer genrated.
		}

		neuronLayers.back().back().setOutputValue(1.0);

	}


}

void Network::feedForward(const vector<double> &inputVals, int activationType) { //Feedforward function that takes inputVals vector

	assert(inputVals.size() == neuronLayers[0].size() - 1); //Check number of input neurons = number of input values, " - 1" accounts for bias neuron;

	for(int i = 0; i < inputVals.size(); i++) { //Loop through neurons input layer

		neuronLayers[0][i].setOutputValue(inputVals[i]); //Setting input layer neurons output to input value

	}


	for(int layerIndex = 1; layerIndex < neuronLayers.size(); layerIndex++){ //Go through all layers except input

		Layer &previousLayer = neuronLayers[layerIndex - 1]; //Store variable of previous layers to be fed into neuron feedForward function

		for(int n = 0; n < neuronLayers[layerIndex].size() - 1; n++){ //Go through each neuron except bias

			neuronLayers[layerIndex][n].neuronFeedForward(previousLayer, activationType); //Apply function feedForward (of neuron class!) to each neuron, feed in previous laer

		}


	}


}


void Network::backProp(const vector<double> &targetVals, int activationType) {

	Layer &outputLayer = neuronLayers.back(); //Create layers type layer of output layer

	error = 0.0;

	for(unsigned n = 0; n < outputLayer.size() - 1; n++) {

		double delta = targetVals[n] - outputLayer[n].getOutputVal(); //difference in target and actual output

		error += delta*delta; // sum and square


	}

	error /=outputLayer.size() -1; //Average error
	error = sqrt(error); //Root mean square

	for(unsigned n = 0; n < outputLayer.size()-1; n++) {

		outputLayer[n].calculateOutputGradients(targetVals[n], activationType); //Calculate gradient for output layer

	}

	for(unsigned layerIndex = neuronLayers.size() -2; layerIndex > 0; layerIndex--) {

		Layer &hiddenLayer = neuronLayers[layerIndex];
		Layer &nextLayer = neuronLayers[layerIndex +1];

		for(unsigned n = 0; n<hiddenLayer.size(); ++n) {
			hiddenLayer[n].calculatehiddenGradients(nextLayer, activationType); //Calculate gradient of hidden layer
		}

	}

	for(unsigned layerIndex = neuronLayers.size() - 1; layerIndex > 0; layerIndex--){

		Layer &layer = neuronLayers[layerIndex];
		Layer &prevLayer = neuronLayers[layerIndex - 1];

		for(unsigned n = 0; n < layer.size() - 1; n++ ){

			layer[n].weightInputUpdate(prevLayer);


		}


	}


}



void Network::getResults(vector<double> &resultVals) const {

	resultVals.clear();

	for(unsigned n = 0; n < neuronLayers.back().size() - 1; n++){

		resultVals.push_back(neuronLayers.back()[n].getOutputVal());

	}

}









