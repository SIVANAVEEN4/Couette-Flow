#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<cmath>
#include<fstream>

using namespace std;

int main()
{
	int m = 101, i, j, iter=0;
	double dy, H=1.0, t=0.0, U=1.0, Re = 100.0, dt = 0.005, ga, error;
	double u[m], old_u[m];
	char name[50];	
	bool done = false;
	
	ofstream myfile;
	myfile.open("errorvstime.dat");
	
	dy = H/(m-1);
	ga = dt/(Re*dy*dy);
	
	u[0] = 0.0;
	u[m-1] = U; 
	
	for(j=1; j<m-1; j++)
	{
		u[m] = 0.5;
	}
	
	while(t<=60.0)
	{
		
		if((iter+100)%100 == 0)
		{
			sprintf(name, "velocity_%.2f.dat", t);
			FILE *fp;
			fp = fopen(name, "w");
			for(j=0; j<m; j++)
			{
				fprintf(fp, "%lf\t%lf\n", u[j], j*dy);
			}
			fclose(fp);	
		}
		
		for(j=0; j<m; j++)
		{
			old_u[j] = u[j];	
		}
			
		for(j=1; j<m-1; j++)
		{
			u[j] = 	(1-2*ga)*old_u[j] + ga*(old_u[j+1] + old_u[j-1]);
		}
			
		error = 0.0;
		for(j=0; j<m; j++)
		{
			error = error + pow((old_u[j] - u[j]), 2);
		}
		
		t = t+dt;
		error = sqrt(error/m);	
		iter = iter + 1;
		
		myfile<<t<<"\t\t"<<error<<endl;
		
		if(!done && error<1e-6)
		{
			int number = iter;
			cout<<"\n\n"<<"\t1) No. of iterations required to get an error < 10^(-6) : "<<number<<endl;
			cout<<"\n\t2) Time elapsed before reaching steady state : "<<t<<"\n\n";
			done = true;
		}	
 
	}
	
	cout<<"\n\n"<<"\t3) error after time t = 60 is "<<error;
	cout<<"\n\n"<<"\t4) Number of iterations for time t=60 is : "<<iter<<"\n\n";
	
	return 0;
		
}