#include<iostream>
#include<cmath>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>

using namespace std;

int main()
{
	int m = 101, i, j, iter=0;
	double dy, H=1.0, t, U=1.0, Re = 100.0, dt = 0.01, ga, error;
	double u[m], old_u[m], d[m], p[m], q[m];
	char name[50];	
	bool only_once = false;	
	
	dy = H/(m-1);
	ga = dt/(Re*dy*dy);
	
	ofstream myfile;
	myfile.open("errorvstime.dat");
	
	double aj = -(1 + 2*ga), bj=ga, cj=ga;
	
	u[0] = 0.0;
	u[m-1] = U; 
	
	for(j=1; j<m-1; j++)
	{
		u[m] = 0.0;
	}
	
	d[0] = -u[0];
	d[m-1] = -u[m-1];
	p[0] = -bj/aj;
	p[m-1] = 0.0;
	q[0] = d[0]/aj;
	q[m-1] = u[m-1];
	
	while(t<=70.0)
	{
		
		if((iter+100)%100 == 0)
		{
			sprintf(name, "BTCS_u_%.2f.dat", t);
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
			d[j] = -u[j];

            p[j] = -(bj/(aj+cj*p[j-1]));

            q[j] = (d[j]-cj*q[j-1])/(aj+cj*p[j-1]);
		}
		
		for(j=m-2; j>0; j--)
		{
			u[j] = p[j]*u[j+1] + q[j];
		}
		
		error = 0.0;
		for(j=0; j<m; j++)
		{
			error = error + pow((old_u[j] - u[j]), 2);
		}
		error = sqrt(error/m);
		iter = iter + 1;
		
		myfile<<t<<"\t\t"<<error<<endl;
		
		if(!only_once && error<1e-6)
		{
			int number = iter;
			cout<<"\n\n"<<"\t1) No. of iterations required to get an error < 10^(-6) : "<<number<<endl;
			cout<<"\n\t2) Time elapsed before reaching steady state : "<<t<<"\n\n";
			only_once = true;
		}
		
		t = t+dt;		
	} 
	
	cout<<"\n\n"<<"\t3) error after time t = 70 is "<<error;
	cout<<"\n\n"<<"\t4) Number of iterations for time t=70 is : "<<iter<<"\n\n";
	
	return 0;
		
}