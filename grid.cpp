
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <math.h>
#include <cmath>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;


double randTheta();
double randRadius(int lowLimit, int highLimit);

int main(){

	fstream data;
	fstream train;

	data.open("grid.dat", ios::out | ios::trunc);
	train.open("training.txt", ios::out | ios::trunc);



	//Positive data

	for (int i =0;i<500;i++){

		double y, x, r;

		double theta=randTheta();

		r = randRadius(0,40);
		y = 0.5+r*cos(theta);
		x = 0.5+r*sin(theta);

		train << setprecision(3) << fixed << x << " "<< y << " " <<x*y << " 1" <<endl;
		data << setprecision(3) << fixed << x << " "<< y << " 1" <<endl;

		
		double theta2=randTheta();

		r = randRadius(0,40);
		y = -0.5+r*cos(theta2);
		x = 0.5+r*sin(theta2);

		train << setprecision(3) << fixed << x << " "<< y << " " << x*y <<" -1" <<endl;
		data << setprecision(3) << fixed << x << " "<< y << "-1" <<endl;


		double theta3=randTheta();

		r = randRadius(0,40);
		y = -0.5+r*cos(theta3);
		x = -0.5+r*sin(theta3);

		train << setprecision(3) << fixed << x << " "<< y << " " << x*y <<" 1" <<endl;
		data << setprecision(3) << fixed << x << " "<< y << " 1" <<endl;

		double theta4=randTheta();

		r = randRadius(0,40);
		y = 0.5+r*cos(theta4);
		x = -0.5+r*sin(theta4);

		train << setprecision(3) << fixed << x << " "<< y << " " << x*y <<" -1" <<endl;
		data << setprecision(3) << fixed << x << " "<< y << " -1" <<endl;

	}


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