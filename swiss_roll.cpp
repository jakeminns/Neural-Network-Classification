
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


int main(){

	fstream data;
	data.open("training.txt", ios::out | ios::trunc);

	//Positive data
			double y, x, r;
			double noise;
			double rCheck =1;



	for (double i =1;i<720;i++){

		double theta=i*3.14159/180;
		r = (0.5)*(i/900);
		//noise = ((rand() % (100)+1)*0.001)*(i/900);
		y = (0.5+r*cos(theta));
		x = (0.5+r*sin(theta));

		data << setprecision(3) << fixed << x << " "<< y << " 1"<<endl;


		x=i+180;

		theta=x*3.14159/180;
		r = (0.5)*(rCheck/900);
		//noise = ((rand() % (100)+1)*0.001)*(i/900);
		y = (0.5+r*cos(theta));
		x = (0.5+r*sin(theta));

		data << setprecision(3) << fixed << x << " "<< y <<" -1"<< endl;
		rCheck++;

	}


} 
