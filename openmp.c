#include "utility.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>
#include "numgen.c"


int main(int argc,char **argv) {


  Args ins__args;
  parseArgs(&ins__args, &argc, argv);

  //set number of threads
  omp_set_num_threads(ins__args.n_thr);
  
  //program input argument
  long inputArgument = ins__args.arg; 
  unsigned long int *numbers = (unsigned long int*)malloc(inputArgument * sizeof(unsigned long int));
  numgen(inputArgument, numbers);

  struct timeval ins__tstart, ins__tstop;
  gettimeofday(&ins__tstart, NULL);
  
  // run your computations here (including OpenMP stuff)
  
  int counter = 0; 
  int flag = 0;
	
  #pragma omp parallel for reduction(+:counter)
  for(int i = 0; i < inputArgument;i++)
  {	
  		for(unsigned long j = 2; j * j <= numbers[i]; j++)
  		{
  			if(numbers[i] % j == 0)
  			{
  				flag = 1;
  				break;
  			}
  		}
  		
  		if(!flag)
  			counter++;
  		
  		flag = 0;					
  }
  
  printf("Number of prime numbers: %d", counter);
  
  // synchronize/finalize your computations
  gettimeofday(&ins__tstop, NULL);
  ins__printtime(&ins__tstart, &ins__tstop, ins__args.marker);

}
