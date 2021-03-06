#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "mpi.h"
#include "functions.h"

int main (int argc, char **argv) {

  MPI_Init(&argc,&argv);

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);

  //seed value for the randomizer 
  double seed = clock()+rank; //this will make your program run differently everytime
  //double seed = rank; //uncomment this and your program will behave the same everytime it's run

  srand(seed);

  //begin with rank 0 getting user's input
  unsigned int n, p, g, h, x;

  /* Q3.1 Make rank 0 setup the ELGamal system and
    broadcast the public key information */
  if (rank == 0){
  printf("Enter a number of bits: "); fflush(stdout);
  char status = scanf("%u",&n);

  //make sure the input makes sense
  if ((n<3)||(n>31)) {//Updated bounds. 2 is no good, 31 is actually ok
    printf("Unsupported bit size.\n");
    return 0;   
  }
  printf("\n");

  //declare storage for an ElGamal cryptosytem
  //unsigned int p, g, h, x;
  //if (rank == 0){
  //setup an ElGamal cryptosystem
  setupElGamal(n,&p,&g,&h,&x);
  }

  /*MPI Broadcast*/
  MPI_Bcast(&p, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);
  MPI_Bcast(&g, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);
  MPI_Bcast(&h, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);

  //Suppose we don't know the secret key. Use all the ranks to try and find it in parallel
  if (rank==0)
    printf("Using %d processes to find the secret key...\n", size);

  /*Q3.2 We want to loop through values i=0 .. p-2
     determine start and end values so this loop is 
     distributed amounst the MPI ranks  */
  unsigned int N = p-1; //total loop size
  unsigned int start, end;
  unsigned int startTime, endTime;
  
  //start = 0;
  //end = start + N;
   

  //For large bit there is more hangtime
  //Roughly splits the work evenly
  if (rank ==0) {
    startTime = MPI_Wtime();
  for (int i = 0; i < N-1; i++){ 
     int chunk = N/size; // need to account for remainder
     int remainder = N%size; //remainder
	if( rank < remainder){
	   start = rank * chunk + rank;
	}
	else {
	   start = rank * chunk + remainder;
	}
     end = start + N;
    }
  } 
 
  //loop through the values from 'start' to 'end'
  for (unsigned int i=start;i<end;i++) {
     if (modExp(g,i+1,p)==h)
      //endTime = MPI_Wtime();
      printf("Secret key found! x = %u \n", i+1);
  }

  endTime = MPI_Wtime();
  
  double timeElapsed = endTime - startTime;
  //throughput measure of bits persecond?
  //double throughPut  = (double) (N * size) / timeElapsed; //jobs times threads divided by runtime
  // the previous throughput would give me infinity   
  // If the computation is ran fast enough we may divide by zero which is why previous = inf sometimes
  double throughPut = (double) N / timeElapsed;


  if (rank == 0) {
    printf("The elapsed time = %g \n", timeElapsed);
    printf("The through put = %g \n", throughPut);
  }

  MPI_Finalize();

  return 0;
}
