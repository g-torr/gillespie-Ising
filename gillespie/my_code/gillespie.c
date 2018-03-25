#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <time.h>
/*************************************
*	number generator exponential *
****************************************/

void main(){
srand(time(NULL));
float r=(float)rand()/INT_MAX;// uniform random in [0,1)
float r2;
double tau,time_elapsed;
int x[2];
int N_realisation=10;
float prop[4];//propensities, prop[0] is the sum of all the propensities
float rates[3];// the reaction index is shifted by 1 to left compared to vector prop[]
int i,j,step;

float accumulation;// it is an internal variable used to accumulate the probability of different reactions
int N=10000; //length of simulation
int realisation;
int state_change[3][2];// the first index maps which reaction occurs, the second the change in the vector of  x 
state_change[0][0]=-2;
state_change[0][1]=1;
state_change[1][0]=2;
state_change[1][1]=-1;
state_change[2][0]=-1;
state_change[2][1]=0;
char filename[30];
FILE* f;

for (realisation=0;realisation<N_realisation;realisation++){
	sprintf (filename,"./data/dataset_%d.txt",realisation);
	f=fopen(filename,"w");
	x[0]=50;// index 0 represent the specie A
	x[1]=0;// index 1 represents B

	for (i=0;i<3;i++){//initialise the reactions
		rates[i]=1;}
	time_elapsed=0;

	// here starts the temporal loop
	for (step=0;step<N;step++){
		prop[1]=rates[0]*x[0]*x[0];
		prop[2]=rates[1]*x[1];
		prop[3]=rates[2]*x[0];
		prop[0]=prop[1]+prop[2]+prop[3];

		//create the exponentially distributed number 
		r=(float)rand()/INT_MAX;// uniform random in [0,1)
		tau=-1./prop[0]* log(r);
		time_elapsed+=tau;
	
		//choose which reaction occurrs
		r2=(float)rand()/INT_MAX;// uniform random in [0,1)
		accumulation=0;
		for (j=1;j<=3;j++)//find the reactions
		{
			accumulation+=prop[j]/prop[0];
			//printf("%f, %f \n",accumulation,r2);
			if (accumulation>r2) break;		
	
		}
		//printf("%d\n",j);
		//change in the the number of particules  due to the reaction
		x[0]+=state_change[j-1][0];
		x[1]+=state_change[j-1][1];
	
		fprintf(f,"%d	 %d	 %f \n",x[0],x[1],time_elapsed);
		if(x[0]<0 ||x[1]<0) {break; printf("Simulation ended because there are no particles");}// interrupt the simulation if there are negative particles
	
	}
	fprintf(f,"\n");
}

//printf("just for check state_change[0][1]= %d",state_change[0][1]);
fclose(f);

exit(0);
}


