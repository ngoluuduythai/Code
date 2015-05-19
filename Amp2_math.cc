#include <iostream>
#include <stdexcept>
#include <fstream>
#include <math.h>
#include "integrands.h"

using namespace std;

double amp2_math_int(double s,double sh,double uh,double alpha,double alphaS,double Pi)//ei
{
	//
	double factor = (-1.*Pi*alpha*alphaS)/(sh*sh); //ei*ei
	//
	double temp;
	//
	temp = (1./3.)*factor*(sh/uh+uh/sh);
 	//cout <<"temp = "<<temp<<" , "<<sh<<" , "<<uh<<" , "<<alpha<<" , "<<alphaS<<" , "<<factor<<" , "<<Pi<<endl;

	//
	return (temp);
}
