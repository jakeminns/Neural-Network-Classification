// Neural Network Image Recognition, Jake Minns

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


vector<double> xInput;
vector<double> yInput;
vector<double> xyInput;
vector<double> nOutput;


//void useNeuralNet (Network myNet);

vector<double> targetSet (vector<double> trainingVals, int x, double input, double output);
Network training (Network myNet, vector<double> xInput, vector<double> yInput, vector<double> xyInput, vector<double> nOutput, vector<double>resultVals);
Network testData (Network myNet, vector<double> xInput, vector<double> yInput, vector<double> xyInput, vector<double> resultVals);
vector<double> getTrainingData ();
void resultSet (vector<double> xInput, vector<double> yInput, vector<double> nResult);

vector<double> resultList;
vector<double> resultVals;
vector<double> resultOutput;



int main(){


	vector<unsigned> topology;
	vector<double> inputVals;
	vector<double> targetVals;
	vector<double> trainingVals;

	double input = 2;
	double output = 1;
	double learnItt = 2000;


	trainingVals = getTrainingData();

	//Define topology of NN
	topology.push_back(3);
	topology.push_back(10);
	topology.push_back(3);
	//topology.push_back(10);
	//topology.push_back(2);
	topology.push_back(1);


	Network myNet(topology);

	//Training

	for(int i = 0; i<learnItt;i++){

		myNet = training(myNet, xInput, yInput, xyInput, nOutput, resultVals);
		cout << (i/learnItt)*100 <<endl;
	
	}

	vector<double> resultTemp; //Temp result vector Pass to be appended to nResult
	xInput.clear();
	yInput.clear();
	for(double x = -1.00; x<= 1.00;x=x+0.01){
		for (double y = -1.00; y <=1.00; y=y+0.01){
			xInput.push_back(x);
			yInput.push_back(y);
			xyInput.push_back(x*y);
		}
	}
	
	myNet = testData(myNet, xInput, yInput, xyInput, resultVals); //testData function produces results vector = resultTemp

	resultSet(xInput,yInput, resultOutput);

}





vector<double> getTrainingData (){

	string line, temp;
	double xval, yval, xyval, out;
	ifstream input ("training.txt");
	size_t sz;
	int z = 0;

	if (input.is_open()){
	
	while(getline (input,line)){

		int i = 0;

		int numSize = 5;
		temp.clear();

		if(line[i]=='-'){
			numSize++;
		}
		
		for(int x = 0; x<numSize; x++){

			temp.push_back(line[x]);

			i=x+2; 

		}
		
		xval = std::stod(temp, &sz);
		xInput.push_back(xval);

		numSize = i+5;
		temp.clear();

		if(line[i]=='-'){
			numSize++;
		}

		for(int x = i; x<numSize; x++){
			temp.push_back(line[x]);
				
			i=x+2; 
		
		}
		
		yval = std::stod(temp, &sz);
		yInput.push_back(yval);


		numSize = i+5;
		temp.clear();

		if(line[i]=='-'){
			numSize++;
		}

		for(int x = i; x<numSize; x++){
			temp.push_back(line[x]);
				
			i=x+2; 
		
		}
		
		xyval = std::stod(temp, &sz);
		xyInput.push_back(xyval);

		numSize = i+1;
		temp.clear();

		if(line[i]=='-'){
			numSize++;
		}

		for(int x = i; x<numSize; x++){

			temp.push_back(line[x]);

		}
	

		out = std::stod(temp, &sz);
		nOutput.push_back(out);

		z++;
	}

	input.close();
	
	}

	else cout << "No file";

	return xInput;

}


Network testData (Network myNet, vector<double> xInput, vector<double> yInput, vector<double> xyInput, vector<double> resultVals){

	vector<double> input;
	vector<double> output;

	for(int i = 0; i < xInput.size(); i++){

		input.clear();
		output.clear();

		input.push_back(xInput[i]);
		cout << input.back()<< " y";
		input.push_back(yInput[i]);
		cout << input.back()<<" ";
		input.push_back(xyInput[i]);
		myNet.feedForward(input);
		myNet.getResults(resultVals);

		for(int x = 0; x<resultVals.size(); x++){
			resultOutput.push_back(resultVals[x]);
			cout <<  " r: " << resultVals[x] <<  endl;

		}

	}


	return myNet;

}


Network training (Network myNet, vector<double> xInput, vector<double> yInput, vector<double> xyInput, vector<double> nOutput, vector<double>resultVals) {

	vector<double> input;
	vector<double> output;

	for(int i = 0; i < xInput.size(); i++){

		input.clear();
		output.clear();

		input.push_back(xInput[i]);
		//cout << input.back()<< " ";
		input.push_back(yInput[i]);
		//cout << input.back()<<" ";
		input.push_back(xyInput[i]);

		output.push_back(nOutput[i]);
		//cout << output.back()<<" ";
		
		myNet.feedForward(input);

		myNet.getResults(resultVals);

		myNet.backProp(output);


		//cout << resultVals[0]<<endl;

	}

		return myNet;

}



void resultSet (vector<double> xInput, vector<double> yInput, vector<double> nResult) {

	fstream result;
	string line;
	double buffer;
	result.open("results.dat", ios::out | ios::trunc );



	for(int x = 0; x < xInput.size(); x++){

		result << xInput[x] << " " << yInput[x] <<" " << nResult[x] << endl;

	}

	result.close();

}













