
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

	data.open("circle_train.dat", ios::out | ios::trunc);
	train.open("training.txt", ios::out | ios::trunc);

	//Positive data

	for (int i =0;i<500;i++){

		double y, x, r;

		double theta=randTheta();

		r = randRadius(0,40);
		y = r*cos(theta);
		x = r*sin(theta);

		train << setprecision(3) << fixed << x << " "<< y << " " << "0.000" << " 1" <<endl;
		data << setprecision(3) << fixed << x << " "<< y << " 1" <<endl;

		
		double theta2=randTheta();

		r = randRadius(60,70);
		y = r*cos(theta2);
		x = r*sin(theta2);

		train << setprecision(3) << fixed << x << " "<< y << " "<< "0.000" <<" -1" <<endl;
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