/****************************************/
/*					*/
/*					*/
/*	Gillespie Alg. Example		*/
/*	----------------------		*/
/*	written by Ryan Hannam		*/
/*					*/
/*					*/
/****************************************/


// This script gives a basic example of the Gillespie algorithm - also known as the Stochastic Simulation algorithm.

//compile using "gcc -g -o output script_name.c -lm"
// debugg using "valgrind --leak-check=full -v ./output_name"


/*Reactions: The Michaelis-Menten enzyme kinetics:

	E + S --k1--> ES	(1)
	ES --k2--> E + S	(2)
	ES --k3--> E + P	(3)

*/


#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#include <limits.h>
#include <time.h>


#define NSPECIES 4
#define NREACTIONS 3
#define TMAX 10
#define SEED 123

//Global variables
int i, j, Nreactions, nr, X[4], S[3][4];
double r1, r2, t, tau, a0, k[3], a[3];
FILE *fopen(), *fp;


void stoichemetric_matrix();
void initial_conditions();
double propensities( double a[], double k[], int X[]);
double monte_carlo_step(double a0);
int next_reaction();

int main() {
	
	// Used to time the simulation
	clock_t begin = clock();
	
	// rate constants
	k[0]=1.0;	// reaction (1)
	k[1]=1.0;	// reaction (2)
	k[2]=1.0;	// reaction (3)

	
	
	/* >>>>>>>> Step 1: Initialisation <<<<<<< */

	//printf("Initial number of particles:\n#E	#S	#ES	#P\n");
	initial_conditions();
	//printf("\n\n");


	//printf("The stoichemetric matrix is given by:\n");
	stoichemetric_matrix();	

	a0 = propensities(a, k, X);
	
	//printf("\n\nThe sum of the propensities is %lf\n\n%lf\n", a0,a[0]);



	// Dynamics
	srand(time(NULL));
	Nreactions = 0;
	t = 0.0;
	
	fp=fopen("trajectories.dat","w");
	fprintf(fp,"\"t\" \"E\" \"S\" \"ES\" \"P\"\n");
	fprintf(fp,"%lf ", t);
	fclose(fp);
	
	
	while(t<TMAX){
		

		//printf("%lf, %d\n",t, Nreactions);


		/* >>>>>>>>>> Step 2: Monte-Carlo <<<<<<<<<<<*/
		//draw next time from exponential distrib
		if(a0>0.0){tau=monte_carlo_step(a0);}
		else{break;}


		
		/* >>>>>>>>>> Step 3: Update <<<<<<<<<<<<*/
		//randomly select the next reaction based on propensities
		nr = next_reaction(a, a0);

		for(i=0;i<NSPECIES;i++){
		X[i]+= S[nr][i];
		}

		fp = fopen("trajectories.dat","a");
		fprintf(fp,"%lf ", t);
		for(i=0;i<NSPECIES;i++){fprintf(fp,"%d ", X[i]);}
		fprintf(fp,"\n");
		fclose(fp);

	a0 = propensities(a, k, X);
	Nreactions++;
	t+=tau;

	/* >>>>>> Step 4: Iterate <<<<<<<<*/
	}
	
	// Plot dynamics using GNUplot
	system("gnuplot X_t.p");


	// Calculate the simulation time
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("\n\nThis script took %lf seconds to be executed\n\n", time_spent);


return 0;
}




/*---------> Read in initial conditions <---------*/
void initial_conditions(){
//FILE rows: E, S, ES, P

	
	
	fp=fopen("initial_population.in","r");
	for(i=0; i<NSPECIES; i++){
		fscanf(fp,"%d", &X[i]);
	}
	fclose(fp);
	
	//for(i=0;i<NSPECIES;i++) {printf("%d	", X[i]);}
	
	
}




/*---------> Read in stoichemetric matrix <-------*/
void stoichemetric_matrix(){
// Michaelis-Menten Equation: E + S <-> ES -> E + P

//FILE colums: E, S, ES, P

//FILE rows:
//E + S -> ES
//ES -> E + S
//ES -> E + P

	int i;
	int nrows=3;
	//int ncols=4;
	

	fp=fopen("stoichemetric_matrix.in","r");
	for(i=0; i<nrows; i++){
		fscanf(fp,"%d %d %d %d", &S[i][0],&S[i][1],&S[i][2],&S[i][3]);
	}
	fclose(fp);

	
	/*for(i=0;i<nrows;i++){
		for(j=0;j<ncols;j++){
		printf("%d	", S[i][j]);
		}
	printf("\n");
	}*/
	

}

/*-------------> Calculate Propensities <---------*/

double propensities(double a[], double k[], int X[]){
// updates the individual propensities and returns the sum of the propensities.
	
	a[0] = k[0]*X[0]*X[1];
	a[1] = k[1]*X[2];
	a[2] = k[2]*X[2];
	
	double asum = 0.0;
	asum = a[0]+a[1]+a[2];
	return(asum);
}


/*-------------> Monte-Carlo step <------------*/
double monte_carlo_step(double a0){
	//sample the waiting time from an exponential distribution
	double t_step = 0.0;
	double r1;

	r1=((double)rand())/INT_MAX;
	
	t_step = -log(r1) / a0;

	return(t_step);
}




/*--------------> Update <-----------------*/

int next_reaction(double a[], double a0) {
	//select the next reaction to occur based on the propensities
	int i, reaction;
	double r2, a_rsum;
	r2=((double)rand())/INT_MAX;
	r2= r2*a0;
	
	a_rsum = 0.0;
	reaction = 0;
	for(i=0;i<NREACTIONS; i++){
		a_rsum += a[i];
		if(r2 < a_rsum){reaction = i; break;}

	}

	return reaction;
}
