// Neural Network Classification Problem, Jake Minns
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


vector<double> xInput, yInput, xyInput, xxInput, yyInput, sinxInput, sinyInput; //Input Training vectors


vector<double> nOutput;

vector<double> targetSet (vector<double> trainingVals, int x, double input, double output);
Network training (Network myNet, int activationType, vector<double> xInput, vector<double> yInput, vector<double> xyInput, vector<double> xxInput, vector<double> yyInput, vector<double> sinxInput, vector<double> sinyInput, vector<double> nOutput, vector<double>resultVals);
vector<double> testData (Network myNet, int activationType, vector<double> xInput, vector<double> yInput, vector<double> xyInput, vector<double> xxInput, vector<double> yyInput, vector<double> sinxInput, vector<double> sinyInput, vector<double> resultVals);
vector<double> getTrainingData ();
void resultSet (vector<double> nResult);
void resultOut(int problemType, int gnuplotOpenCheck, FILE *gnuplotPipe);
vector<double> sampleNetwork (Network myNet, int activationType, vector<int> inputProp);

vector<double> resultVals;
vector<double> resultOutput;



int main(){


	vector<unsigned> topology;
	vector<double> trainingVals;
	int problemType, layernum, updateFreq, numNeurons;
	int x, y, xy, xx, yy, sinx, siny;
	int activationType;
	double learnItt;

	//User Input

	cout << "This program requires GNUPLOT"<<endl;

	cout << "Enter Problem Type (1 = Circle, 2 = Grid, 3 = Swirl): ";
	cin >> problemType;

	cout << "Provide the Properties to be feed in. Enter a 1 for on and 0 for off for the following features, x, y, xy, x^2, y^2, sin(x), sin(y). (E.g: 1 1 1 0 0 0 0): ";
	cin >> x >> y >> xy >> xx >> yy>> sinx >> siny;

	cout << "Enter Number of Learning Itterations (Recomended 1000): ";
	cin >> learnItt;

	cout << "Enter Output Update Frequency: ";
	cin >> updateFreq;

	cout << "Enter Activation Function Type (1 = tanh, 2 = shifted sigmoid):";
	cin >> activationType;

	cout << "Enter Number of Hidden Layers (Recomended 2):";
	cin >> layernum;

	cout << "You have Entered " << layernum << " Hidden layers. For Each layer Provide the number of Neurons (Recomended 12 neurons in the first layer and 3 in the second for 2 hidden layers):" <<endl;

	topology.push_back(7);
	
	for(int i = 0; i < layernum; i++){

		cout << "Layer " << i+1 <<": ";
		cin >> numNeurons;
		topology.push_back(numNeurons);

	}

	topology.push_back(1);

	//Generate Training Data

	vector<int> inputProp = {x,y,xy,xx,yy,sinx,siny}; // 1 = on, 0 = off, {x,y,x^2,y^2,xy,sin(x),sin(y)}

	TrainData Data(problemType, inputProp); // 1 = Circle, 2 = Grid, 3 = Swirl;

	trainingVals = getTrainingData();

	//Generate Network

	Network myNet(topology);

	//Training

	vector<double> resultValsTemp;
	int gnuplotOpenCheck = 0;
	int counter = 0;
	FILE *gnuplotPipe, *files;
	    
	int done;
	gnuplotPipe = popen("gnuplot -persist","w"); //
			//  fprintf(gnuplotPipe, "set term png""\n");
		       
		  // fflush(gnuplotPipe);

	for(int i = 1; i<=learnItt;i++){

		myNet = training(myNet, activationType, xInput, yInput, xyInput, xxInput, yyInput, sinxInput, sinyInput, nOutput, resultVals);

		if(i%updateFreq == 0 || i == learnItt){


	//	fprintf(gnuplotPipe, "set output '%1$d.png'""\n", counter);
		       
		  // 	fflush(gnuplotPipe);
		    counter++;

			resultValsTemp = sampleNetwork(myNet, activationType, inputProp);

			resultSet(resultValsTemp);

			resultOut(problemType, gnuplotOpenCheck, gnuplotPipe);

			gnuplotOpenCheck = 1;

		}

			cout << (i/learnItt)*100 << "..." << endl;

	}


	pclose(gnuplotPipe);


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


vector<double> sampleNetwork (Network myNet, int activationType, vector<int> inputProp){

	vector<double> xInputTemp, yInputTemp, xyInputTemp, xxInputTemp, yyInputTemp, sinxInputTemp, sinyInputTemp; //Input Sampling vectors
	vector<double> resultValsTemp;
	resultValsTemp.clear();
	
	for(double x = -1.00; x<= 1.00;x=x+0.01){
		for (double y = -1.00; y <=1.00; y=y+0.01){

			if(inputProp[0]==1){
			xInputTemp.push_back(x);
			} else {
				xInputTemp.push_back(0.00);
			}

			if(inputProp[1]==1){
			yInputTemp.push_back(y);
			}else {
				yInputTemp.push_back(0.00);
			}

			if(inputProp[2]==1){
			xyInputTemp.push_back(x*y);
			}else {
				xyInputTemp.push_back(0.00);
			}

			if(inputProp[3]==1){
			xxInputTemp.push_back(sin(x*2*3.14159));
			}else {
				xxInputTemp.push_back(0.00);
			}

			if(inputProp[4]==1){
			yyInputTemp.push_back(cos(y*2*3.14159));
			}else {
				yyInputTemp.push_back(0.00);
			}

			if(inputProp[5]==1){
			sinxInputTemp.push_back(sin(x*2*3.14159));
			}else {
				sinxInputTemp.push_back(0.00);
			}

			if(inputProp[6]==1){
			sinyInputTemp.push_back(sin(y*2*3.14159));
			}else {
				sinyInputTemp.push_back(0.00);
			}

		}
	}


	resultValsTemp = testData(myNet, activationType, xInputTemp, yInputTemp, xyInputTemp, xxInputTemp, yyInputTemp, sinxInputTemp, sinyInputTemp, resultValsTemp); //testData function produces results vector = resultTemp



	return resultValsTemp;



}

vector<double> testData (Network myNet, int activationType, vector<double> xInput, vector<double> yInput, vector<double> xyInput, vector<double> xxInput, vector<double> yyInput, vector<double> sinxInput, vector<double> sinyInput, vector<double> resultVals){

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


		myNet.feedForward(input, activationType);
		myNet.getResults(output);


		for(int z = 0; z<output.size();z++){
			resultVals.push_back(output[z]);
		}
		
	}


	return resultVals;

}


Network training (Network myNet, int activationType, vector<double> xInput, vector<double> yInput, vector<double> xyInput, vector<double> xxInput, vector<double> yyInput, vector<double> sinxInput, vector<double> sinyInput, vector<double> nOutput, vector<double>resultVals) {

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
		
		myNet.feedForward(input, activationType);

		myNet.getResults(resultVals);

		myNet.backProp(output, activationType);

	}

		return myNet;

}



void resultSet (vector<double> nResult) {

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

void resultOut(int problemType, int gnuplotOpenCheck, FILE *gnuplotPipe){


	if(problemType==1){

	    if(gnuplotOpenCheck==0) {

	    	if(gnuplotPipe){

		    	fprintf(gnuplotPipe, "set pm3d map; unset key; set xrange [-1:1]; set yrange [-1:1]; set title 'Result'; set title font ',20'; set xlabel 'x'; set xlabel font ',20'; set ylabel 'y'; set ylabel font ',20'; set palette defined (-1 '#FCB941', 0 'white', 1 '#2C82C9'); splot 'results.dat' matrix using (($1/100)-1):(($2/100)-1):3, 'circle.dat' using 1:2:3 w points pt 7 ps 1.5 lc rgb 'white', 'circle.dat' using 1:2:3 w points pt 7 lt palette""\n");
		       
		    	fflush(gnuplotPipe);

		    } else {
       			
       			printf("gnuplot not found...");
    		
    		}	

		}else{

			if(gnuplotPipe){

		   		fprintf(gnuplotPipe, "set pm3d map; unset key; set xrange [-1:1]; set yrange [-1:1]; set title 'Result'; set title font ',20'; set xlabel 'x'; set xlabel font ',20'; set ylabel 'y'; set ylabel font ',20'; unset key;  set palette defined (-1 '#FCB941', 0 'white', 1 '#2C82C9'); replot 'results.dat' matrix using (($1/100)-1):(($2/100)-1):3, 'circle.dat' using 1:2:3 w points pt 7 ps 1.5 lc rgb 'white', 'circle.dat' using 1:2:3 w points pt 7 lt palette""\n");

		    	fflush(gnuplotPipe);
		    
		    } else {
       			
       			printf("gnuplot not found...");
    		
    		}	
		}

	}

	if(problemType==2){

		if(gnuplotOpenCheck==0){

			if(gnuplotPipe){
	      		fprintf(gnuplotPipe, "set pm3d map; unset key; set xrange [-1:1]; set yrange [-1:1]; set title 'Result'; set title font ',20'; set xlabel 'x'; set xlabel font ',20'; set ylabel 'y'; set ylabel font ',20'; set palette defined (-1 '#FCB941', 0 'white', 1 '#2C82C9'); splot 'results.dat' matrix using (($1/100)-1):(($2/100)-1):3, 'grid.dat' using 1:2:3 w points pt 7 ps 1.5 lc rgb 'white', 'grid.dat' using 1:2:3 w points pt 7 lt palette""\n");
		       
		    	fflush(gnuplotPipe);
		 
		    } else {
       			
       			printf("gnuplot not found...");
    		
    		}

		}else{

		   if(gnuplotPipe){
	       		fprintf(gnuplotPipe, " set pm3d map; unset key; set xrange [-1:1]; set yrange [-1:1]; set title 'Result'; set title font ',20'; set xlabel 'x'; set xlabel font ',20'; set ylabe 'y'; set ylabel font ',20'; unset key;  set palette defined (-1 '#FCB941', 0 'white', 1 '#2C82C9'); replot 'results.dat' matrix using (($1/100)-1):(($2/100)-1):3, 'grid.dat' using 1:2:3 w points pt 7 ps 1.5 lc rgb 'white', 'grid.dat' using 1:2:3 w points pt 7 lt palette""\n");
	       
	       		fflush(gnuplotPipe);

	    	

		    } else {
       			
       			printf("gnuplot not found...");
    		
    		}
	       	
		}

	}

	if(problemType==3){

		if(gnuplotOpenCheck==0){

   			if(gnuplotPipe){

	   			fprintf(gnuplotPipe, "set pm3d map; unset key; set xrange [-1:1]; set yrange [-1:1]; set title 'Result'; set title font ',20'; set xlabel 'x'; set xlabel font ',20'; set ylabel 'y'; set ylabel font ',20';unset key;  set palette defined (-1 '#FCB941', 0 'white', 1 '#2C82C9'); splot 'results.dat' matrix using (($1/100)-1):(($2/100)-1):3, 'swirl.dat' using 1:2:3 w points pt 7 ps 1.5 lc rgb 'white', 'swirl.dat' using 1:2:3 w points pt 7 lt palette""\n");
	   		 
	   		 	fflush(gnuplotPipe);

		    } else {
       			
       			printf("gnuplot not found...");
    		
    		}

	    }else{

	    	if(gnuplotPipe){

	    		fprintf(gnuplotPipe, "set pm3d map; unset key; set xrange [-1:1]; set yrange [-1:1]; set title 'Result'; set title font ',20'; set xlabel 'x'; set xlabel font ',20'; set ylabel 'y'; set ylabel font ',20';  set palette defined (-1 '#FCB941', 0 'white', 1 '#2C82C9'); replot 'results.dat' matrix using (($1/100)-1):(($2/100)-1):3, 'swirl.dat' using 1:2:3 w points pt 7 ps 1.5 lc rgb 'white', 'swirl.dat' using 1:2:3 w points pt 7 lt palette""\n");
	       
	    		fflush(gnuplotPipe);

		    } else {
       			
       			printf("gnuplot not found...");
    		
    		}

	    }
	    

	}



    

}












