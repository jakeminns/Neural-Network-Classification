// Neural Network Image Recognition, Jake Minns
// Live learning update
//Noise option
//Choose activation function
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
#include "TrainData.h"

using namespace std;


vector<double> xInput;
vector<double> yInput;
vector<double> xyInput;
vector<double> xxInput;
vector<double> yyInput;
vector<double> sinxInput;
vector<double> sinyInput;

vector<double> nOutput;

vector<double> targetSet (vector<double> trainingVals, int x, double input, double output);
Network training (Network myNet, vector<double> xInput, vector<double> yInput, vector<double> xyInput, vector<double> xxInput, vector<double> yyInput, vector<double> sinxInput, vector<double> sinyInput, vector<double> nOutput, vector<double>resultVals);
Network testData (Network myNet, vector<double> xInput, vector<double> yInput, vector<double> xyInput, vector<double> xxInput, vector<double> yyInput, vector<double> sinxInput, vector<double> sinyInput, vector<double> resultVals);
vector<double> getTrainingData ();
void resultSet (vector<double> xInput, vector<double> yInput, vector<double> nResult);
void resultOut(int problemType);

vector<double> resultVals;
vector<double> resultOutput;



int main(){


	vector<unsigned> topology;
	vector<double> trainingVals;
	int problemType, layernum;
	int x, y, xy, xx, yy, sinx, siny;
	double learnItt;

	//User Input

	cout << "This program requires GNUPLOT"<<endl;

	cout << "Enter Problem Type (1 = Circle, 2 = Grid, 3 = Swirl): ";
	cin >> problemType;

	cout << "Provide the Properties to be feed in. Enter a 1 for on and 0 for off for the following features, x, y, xy, x^2, y^2, sin(x), sin(y). (E.g: 1 1 1 0 0 0 0): ";
	cin >> x >> y >> xy >> xx >> yy>> sinx >> siny;

	cout << "Enter Number of Learning Itterations (Recomended 1000): ";
	cin >> learnItt;

	cout << "Enter Number of Hidden Layers (Recomended 2):";
	cin >> layernum;

	cout << "You have Entered " << layernum << " Hidden layers. For Each layer Provide the number of Neurons (Recomended 12 neurons in the first layer and 3 in the second for 2 hidden layers):" <<endl;

	topology.push_back(7);
	
	for(int i = 0; i < layernum; i++){

		int numNeurons;
		cout << "Layer " << i+1 <<": ";
		cin >> numNeurons;
		topology.push_back(numNeurons);

	}

	topology.push_back(1);


	vector<int> inputProp = {x,y,xy,xx,yy,sinx,siny}; // 1 = on, 0 = off, {x,y,x^2,y^2,xy,sin(x),sin(y)}

	TrainData Data(problemType, inputProp); // 1 = Circle, 2 = Grid, 3 = Swirl;

	trainingVals = getTrainingData();

	Network myNet(topology);

	//Training

	for(int i = 0; i<learnItt;i++){

		myNet = training(myNet, xInput, yInput, xyInput, xxInput, yyInput, sinxInput, sinyInput, nOutput, resultVals);

		cout << (i/learnItt)*100 << "..." << endl;

	}

	//Temp result vector Pass to be appended to nResult
	xInput.clear();
	yInput.clear();
	xyInput.clear();
	xxInput.clear();
	yyInput.clear();
	sinxInput.clear();
	sinyInput.clear();


	for(double x = -1.00; x<= 1.00;x=x+0.01){
		for (double y = -1.00; y <=1.00; y=y+0.01){

			if(inputProp[0]==1){
			xInput.push_back(x);
			} else {
				xInput.push_back(0.00);
			}

			if(inputProp[1]==1){
			yInput.push_back(y);
			}else {
				yInput.push_back(0.00);
			}

			if(inputProp[2]==1){
			xyInput.push_back(x*y);
			}else {
				xyInput.push_back(0.00);
			}

			if(inputProp[3]==1){
			xxInput.push_back(x*x);
			}else {
				xxInput.push_back(0.00);
			}

			if(inputProp[4]==1){
			yyInput.push_back(y*y);
			}else {
				yyInput.push_back(0.00);
			}

			if(inputProp[5]==1){
			sinxInput.push_back(sin(x));
			}else {
				sinxInput.push_back(0.00);
			}

			if(inputProp[6]==1){
			sinyInput.push_back(sin(y));
			}else {
				sinyInput.push_back(0.00);
			}

		}
	}
	



	myNet = testData(myNet, xInput, yInput, xyInput, xxInput, yyInput, sinxInput, sinyInput, resultVals); //testData function produces results vector = resultTemp
	

	resultSet(xInput,yInput, resultOutput);
	resultOut(problemType);



}





vector<double> getTrainingData (){

	string line, temp;
	double xval, yval, xyval, xxval, yyval, sinxval, sinyval, out;
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

		numSize = i+5;
		temp.clear();

		if(line[i]=='-'){
			numSize++;
		}

		for(int x = i; x<numSize; x++){
			temp.push_back(line[x]);
				
			i=x+2; 
		
		}
		
		xxval = std::stod(temp, &sz);
		xxInput.push_back(xxval);

		numSize = i+5;
		temp.clear();

		if(line[i]=='-'){
			numSize++;
		}

		for(int x = i; x<numSize; x++){
			temp.push_back(line[x]);
				
			i=x+2; 
		
		}
		
		yyval = std::stod(temp, &sz);
		yyInput.push_back(yyval);

		numSize = i+5;
		temp.clear();

		if(line[i]=='-'){
			numSize++;
		}

		for(int x = i; x<numSize; x++){
			temp.push_back(line[x]);
				
			i=x+2; 
		
		}
		
		sinxval = std::stod(temp, &sz);
		sinxInput.push_back(sinxval);

		numSize = i+5;
		temp.clear();

		if(line[i]=='-'){
			numSize++;
		}

		for(int x = i; x<numSize; x++){
			temp.push_back(line[x]);
				
			i=x+2; 
		
		}
		
		sinyval = std::stod(temp, &sz);
		sinyInput.push_back(sinyval);

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


Network testData (Network myNet, vector<double> xInput, vector<double> yInput, vector<double> xyInput, vector<double> xxInput, vector<double> yyInput, vector<double> sinxInput, vector<double> sinyInput, vector<double> resultVals){

	vector<double> input;
	vector<double> output;

	for(int i = 0; i < xInput.size(); i++){

		input.clear();
		output.clear();

		input.push_back(xInput[i]);
		input.push_back(yInput[i]);
		input.push_back(xyInput[i]);
		input.push_back(xxInput[i]);
		input.push_back(yyInput[i]);
		input.push_back(sinxInput[i]);
		input.push_back(sinyInput[i]);


		myNet.feedForward(input);
		myNet.getResults(resultVals);

		for(int x = 0; x<resultVals.size(); x++){
			resultOutput.push_back(resultVals[x]);

		}

	}


	return myNet;

}


Network training (Network myNet, vector<double> xInput, vector<double> yInput, vector<double> xyInput, vector<double> xxInput, vector<double> yyInput, vector<double> sinxInput, vector<double> sinyInput, vector<double> nOutput, vector<double>resultVals) {

	vector<double> input;
	vector<double> output;

	for(int i = 0; i < xInput.size(); i++){

		input.clear();
		output.clear();

		input.push_back(xInput[i]);
		input.push_back(yInput[i]);
		input.push_back(xyInput[i]);
		input.push_back(xxInput[i]);
		input.push_back(yyInput[i]);
		input.push_back(sinxInput[i]);
		input.push_back(sinyInput[i]);


		output.push_back(nOutput[i]);
		
		myNet.feedForward(input);

		myNet.getResults(resultVals);

		myNet.backProp(output);

	}

		return myNet;

}



void resultSet (vector<double> xInput, vector<double> yInput, vector<double> nResult) {

	fstream result;
	string line;
	double buffer;
	result.open("results.dat", ios::out | ios::trunc );

	int i = 0;

	for(double x = -1.00; x<= 1.00;x=x+0.01){
		for(double y = -1.00; y<= 1.00;y=y+0.01){

		result << nResult[i] << " ";
		i++;
	}

	result << endl;

	}

	result.close();

}

void resultOut(int problemType){


	if(problemType==1){
    FILE *gnuplotPipe, *files;
    
int done;
    gnuplotPipe = popen("gnuplot -persist","w"); //
    
    if(gnuplotPipe){

       fprintf(gnuplotPipe, "set pm3d map; unset key;  set palette defined (-1 '#FCB941', 0 'white', 1 '#2C82C9'); splot 'results.dat' matrix using (($1/100)-1):(($2/100)-1):3, 'circle.dat' using 1:2:3 w points pt 7 ps 1.5 lc rgb 'white', 'circle.dat' using 1:2:3 w points pt 7 lt palette""\n");
       
       fflush(gnuplotPipe);
       
       pclose(gnuplotPipe);

    } else {
      //  printf("gnuplot not found...");
    }	

}

	if(problemType==2){
		    FILE *gnuplotPipe, *files;
    
	int done;
    gnuplotPipe = popen("gnuplot -persist","w"); //
    
    if(gnuplotPipe){

       fprintf(gnuplotPipe, "set pm3d map; unset key;  set palette defined (-1 '#FCB941', 0 'white', 1 '#2C82C9'); splot 'results.dat' matrix using (($1/100)-1):(($2/100)-1):3, 'grid.dat' using 1:2:3 w points pt 7 ps 1.5 lc rgb 'white', 'grid.dat' using 1:2:3 w points pt 7 lt palette""\n");
       
       fflush(gnuplotPipe);
       
       pclose(gnuplotPipe);

    } else {
      //  printf("gnuplot not found...");
    }	
	}

	if(problemType==3){
		    FILE *gnuplotPipe, *files;
    
	int done;
    gnuplotPipe = popen("gnuplot -persist","w"); //
    
    if(gnuplotPipe){

       fprintf(gnuplotPipe, "set pm3d map; unset key;  set palette defined (-1 '#FCB941', 0 'white', 1 '#2C82C9'); splot 'results.dat' matrix using (($1/100)-1):(($2/100)-1):3, 'swirl.dat' using 1:2:3 w points pt 7 ps 1.5 lc rgb 'white', 'swirl.dat' using 1:2:3 w points pt 7 lt palette""\n");
       
       fflush(gnuplotPipe);
       
       pclose(gnuplotPipe);

    } else {
      //  printf("gnuplot not found...");
    }	
	}



    

}












