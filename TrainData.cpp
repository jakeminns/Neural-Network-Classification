
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <math.h>
#include <cmath>
#include <fstream>
#include <string>
#include <iomanip>
#include "TrainData.h"

using namespace std;

	double randTheta();
	double randRadius(int lowLimit, int highLimit);
	void circleType(vector<int> inputProp);
	void gridType(vector<int> inputProp);
	void swirl(vector<int> inputProp);

TrainData::TrainData(int probType, vector<int> inputProp){

if(probType == 1) {

	circleType(inputProp);

}

else if (probType == 2){

	gridType(inputProp);

}

else if (probType == 3){

	swirl(inputProp);
}



} 

void swirl(vector<int> inputProp){

	fstream data;
	fstream train;
	train.open("training.txt", ios::out | ios::trunc);
	data.open("swirl.dat", ios::out | ios::trunc);

	//Positive data
			double noise;
			double rCheck =1;



	for (double i =1;i<720;i++){

		double y_temp, x_temp;
		double y = 0.00, x=0.00, r, xy=0.00, xx=0.00, yy=0.00, sinx=0.00, siny=0.00;

		double theta=i*3.14159/180;
		r = (i/900);
		//noise = ((rand() % (100)+1)*0.001)*(i/900);
		y_temp = (r*cos(theta));
		x_temp = (r*sin(theta));

			if(inputProp[0] == 1){
				x = x_temp; 
			}

			if(inputProp[1] == 1){
				y = y_temp;
			}
			if(inputProp[2] == 1){
				xy = x_temp*y_temp;
			}

			if(inputProp[3] == 1){
				xx = x_temp*x_temp;
			}


			if(inputProp[4] == 1){
				yy = y_temp*y_temp;
			}

			if(inputProp[5] == 1){
				sinx = sin(x_temp);
			}

			if(inputProp[6] == 1){
				siny = sin(y_temp);
			}

		train << setprecision(3) << fixed << x << " "<< y << " " << xy << " " << xx << " " << yy << " " << sinx << " " << siny << " " << "1"<<endl;
		data << setprecision(3) << fixed << x << " "<< y << " 1"<<endl;


		x=i+180;

		theta=x*3.14159/180;
		r = (rCheck/900);
		//noise = ((rand() % (100)+1)*0.001)*(i/900);
		y = (r*cos(theta));
		x = (r*sin(theta));

		train << setprecision(3) << fixed << x << " "<< y << " " << xy << " " << xx << " " << yy << " " << sinx << " " << siny << " " << "-1"<< endl;
		data << setprecision(3) << fixed << x << " "<< y << " -1"<< endl;

		rCheck++;

	}


} 




void gridType(vector<int> inputProp){

	fstream data;
	fstream train;

	data.open("grid.dat", ios::out | ios::trunc);
	train.open("training.txt", ios::out | ios::trunc);



	//Positive data

	for (int i =0;i<500;i++){

		double y = 0.00, x=0.00, r, xy=0.00, xx=0.00, yy=0.00, sinx=0.00, siny=0.00;
		double y_temp, x_temp;
		double theta=randTheta();

		r = randRadius(0,40);
		y_temp = 0.5+r*cos(theta);
		x_temp = 0.5+r*sin(theta);

			if(inputProp[0] == 1){
				x = x_temp; 
			}

			if(inputProp[1] == 1){
				y = y_temp;
			}
			if(inputProp[2] == 1){
				xy = x_temp*y_temp;
			}

			if(inputProp[3] == 1){
				xx = x_temp*x_temp;
			}


			if(inputProp[4] == 1){
				yy = y_temp*y_temp;
			}

			if(inputProp[5] == 1){
				sinx = sin(x_temp);
			}

			if(inputProp[6] == 1){
				siny = sin(y_temp);
			}

		train << setprecision(3) << fixed << x << " "<< y << " " << xy << " " << xx << " " << yy << " " << sinx << " " << siny << " " << "1" <<endl;
		data << setprecision(3) << fixed << x << " "<< y << " 1" <<endl;

		
		double theta2=randTheta();

		r = randRadius(0,40);
		y = -0.5+r*cos(theta2);
		x = 0.5+r*sin(theta2);

		train << setprecision(3) << fixed << x << " "<< y << " " << xy << " " << xx << " " << yy << " " << sinx << " " << siny << " " <<"-1" <<endl;
		data << setprecision(3) << fixed << x << " "<< y << " -1" <<endl;


		double theta3=randTheta();

		r = randRadius(0,40);
		y = -0.5+r*cos(theta3);
		x = -0.5+r*sin(theta3);

		train << setprecision(3) << fixed << x << " "<< y << " " << xy << " " << xx << " " << yy << " " << sinx << " " << siny << " " <<"1" <<endl;
		data << setprecision(3) << fixed << x << " "<< y << " 1" <<endl;

		double theta4=randTheta();

		r = randRadius(0,40);
		y = 0.5+r*cos(theta4);
		x = -0.5+r*sin(theta4);

		train << setprecision(3) << fixed << x << " "<< y << " " << xy << " " << xx << " " << yy << " " << sinx << " " << siny << " "<<"-1" <<endl;
		data << setprecision(3) << fixed << x << " "<< y << " "<< "-1" <<endl;

	}


} 


void circleType (vector<int> inputProp) {

	fstream data;
	fstream train;

	data.open("circle.dat", ios::out | ios::trunc);
	train.open("training.txt", ios::out | ios::trunc);

	//Positive data

		for (int i =0;i<500;i++){

			double y = 0.000, x=0.000, r, xy=0.000, xx=0.000, yy=0.000, sinx=0.000, siny=0.000;

			double theta=randTheta();

			r = randRadius(0,40);
			double y_temp = r*cos(theta);
			double x_temp = r*sin(theta);

			if(inputProp[0] == 1){
				x = x_temp; 
			}

			if(inputProp[1] == 1){
				y = y_temp;
			}
			if(inputProp[2] == 1){
				xy = x_temp*y_temp;
			}

			if(inputProp[3] == 1){
				xx = x_temp*x_temp;
			}


			if(inputProp[4] == 1){
				yy = y_temp*y_temp;
			}

			if(inputProp[5] == 1){
				sinx = sin(x_temp);
			}

			if(inputProp[6] == 1){
				siny = sin(y_temp);
			}

			
			train << setprecision(3) << fixed << x << " "<< y << " " << xy << " " << xx << " " << yy << " " << sinx << " " << siny << " " << "1" <<endl;
			data << setprecision(3) << fixed << x << " "<< y << " 1" <<endl;

			
			double theta2=randTheta();

			r = randRadius(60,70);
			y = r*cos(theta2);
			x = r*sin(theta2);

			train << setprecision(3) << fixed << x << " "<< y << " " << xy << " " << xx << " " << yy << " " << sinx << " " << siny << " " <<"-1" <<endl;
			data << setprecision(3) << fixed << x << " "<< y << " -1" <<endl;
		}

		data.close();
		train.close();

}

double randRadius(int lowLimit, int highLimit){

	bool check = true;
	int randR;

	while(check == true){

		randR = rand() % (highLimit)+1;

		if(randR < lowLimit){

		}

		else {

			check = false;

		}

	}

	return randR*0.01;


}

double randTheta(){

	//double randMaxPos = 0.5;
	bool check=true;
	int  randNumPos;

	while(check == true){
			randNumPos = (rand() % 721 +(-360));


		if (randNumPos == 0){
				
			randNumPos = (rand() % 721 +(-360));

		}

		else{

			check=false;

		}

	}

	return (randNumPos*3.14159/180);

}