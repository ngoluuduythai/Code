#include <iostream>
#include "nclinhWrap.h"
#include <math.h>
#include "integrands.h"
#define DIMENSION 3
#define FUNCTIONS 1
 extern "C" {
    #include "vegas.h"
}

using namespace std;

void val(double x[DIMENSION], double f[FUNCTIONS])
{
	//~ double e=1.60217657 *pow(10,-19);	
	//~ double e=1;		
        double Pi = 3.1415926535897932385;
	double Pi2 = Pi*Pi;
	double pTmax=50.,pTmin=40.;
	double y3max=1.   ,y3min=-1.   ;
	double y4max=1.0   ,y4min=-1.0   ;
        double s = pow(14000.,2.);
   	double hc=pow(0.38935,9.);	
	double cv=pow(10,9);
       	double fpdf;
        double x1,x2,pT,y3,y4;
        pT=(pTmax-pTmin)*x[0]+pTmin;
        y3=(y3max-y3min)*x[1]+(y3min);
        y4=(y4max-y4min)*x[2]+(y4min);
        double sqr_s= sqrt(s);
        x1=(pT*(exp(y3)+exp(y4)))/sqr_s;
        x2=(pT*(exp(-y3)+exp(-y4)))/sqr_s;  
        //cout<<"x1 = "<<x1<<endl;
        //cout<<"x2 = "<<x2<<endl;
	//	
	double sh = x1*x2*s;
	double sqr_sh= sqrt(sh);
	//
        double Q2 = pT*pT;
	double Q = pT;
	double sh2 = sh*sh;
	//
	double alpS = 0.130;//alpS(Mz)
	double alp= 1./137;
	//
        int i,fl,k;
        i=5;
        k=0;
        fl=-i;
	//~ cout << "running: integrand " << sigma << "\n";
	//
	nclinhWrap pdf = nclinhWrap();
	//
        //cout<<"pdfx1 = "<<pdf.fx(i,x1,Q2)<<endl;
	//cout<<"pdfx2 = "<<pdf.fx(k,x2,Q2)<<endl;
	
	fpdf = pdf.fx(i,x1,Q2)*pdf.fx(k,x2,Q2)+pdf.fx(fl,x1,Q2)*pdf.fx(k,x2,Q2);		
	//
	double jacobien =(pTmax-pTmin)*(y3max-y3min)*(y4max-y4min);
	//
	double uh =-x2*pT*sqr_s*exp(y3);
        double amp2_math_int(double s,double sh,double uh,double alpha,double alphaS,double Pi);
	double sigma = amp2_math_int(s,sh,uh,alp,alpS,Pi);
	//
	//if (sh>=4.*mQ2)
		//~ f[0] fpdf*sig_hat;//define the integrand
	f[0] = hc*jacobien*fpdf*2.*(1./3)*(1./3)*sigma*pT*x1*x2;
	//cout << "gtri sigma: " <<sigma<< endl;
	//cout << "gtri f: " <<f[0]<<" , "<<jacobien<<" , "<<fpdf<< endl;
	//else
	//	f[0] =0.;
}

int main(int argc, char **argv)

{

        int iset = 4; //Stand for PDFs set CTEQ6L

        nclinhWrap pdf = nclinhWrap();

        pdf.initPDF(iset);

        cout << "\n\n------------------------------\n";

	int i;
        //int rank,size;
         double estim[FUNCTIONS];   /* estimators for integrals                     */
         double std_dev[FUNCTIONS]; /* standard deviations                          */
         double chi2a[FUNCTIONS];   /* chi^2/n                                      */
         double reg[2*DIMENSION];   /* integration domain                           */

	//~ MPI_Init(&argc, &argv);

	for (i=0; i<DIMENSION; i++) {
	        reg[i] = 0.;
        	reg[i+DIMENSION] = 1.;
	}
	//~ cout << "\n dimension i after loop-------------------------------" << i << "\n";

	/* set up the grid (init = 0) with 5 iterations of 1000 samples,
	 * no need to compute additional accumulators (fcns = 1),
	 * no parallelization yet (wrks = 1). */

	vegas(reg, DIMENSION, val, 0, 1000,5, NPRN_INPUT | NPRN_RESULT, 1, 0, 1, estim, std_dev, chi2a);

	vegas(reg, DIMENSION, val, 1, 10000,10, NPRN_INPUT | NPRN_RESULT, FUNCTIONS, 0, 4, estim, std_dev, chi2a);

        vegas(reg, DIMENSION, val, 2, 100000,10, NPRN_INPUT | NPRN_RESULT, FUNCTIONS, 0, 4, estim, std_dev, chi2a);

	double real_part1 = estim[0];

        double error1 = std_dev[0];

	cout << " \n----------integrate sum_pdf*x-section*dx ----------\n\n" << real_part1 << " (+/-" << error1<< ") \n\n******\n";
      
	//~ MPI_Finalize();


        return 0;
}									
