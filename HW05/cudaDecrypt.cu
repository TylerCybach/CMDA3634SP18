#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "cuda.h"
#include "functions.c"


__device__ unsigned int modProdCuda(unsinged int a, unsigned int b, unsigned int p){
 
  unsigned int za = a;
  unsigned int ab = 0;

  while(b > 0){
    if(b%2 == 1) ab = (ab + za) % p;
    za =  (2 * za) % p;
    b /= 2;
  }
  return ab;
}

__device__ unsigned int modExpCuda(unsigned int a, unsigned int b, unsigned int p){
  unsigned int z = a;
  unsigned int aExpb = 1;

  while (b > 0) {
   if( (b%2 == 1) aExpb = modProdCuda(aExpb, z, p);
   z = modProdCuda(z, z, p);
   b /= 2;
  }
 
  return aExpb;
}


__global__ void kenrelFindSecretKey(unsigned int p, unsigned int g, unsigned int h, unsigned int *d_array){

  unsigned int thread = threadIdx.x; 
  unsigned int block = blockIdx.x;
  unsigned int blockSize = blockDim.x;
  //unsinged int gridsize =gridDim.x;

  //unique global thread id
  unsigned int id = thread + blockSize*block;  

  //for(unsinged int i=0; i<p-1; i++)
  if (id < p-1){
    if (modExpCuda(g, id+1, p) ==h) {
      d_array[0] = id+1;
    }
  }

}


int main (int argc, char **argv) {

  /* Part 2. Start this program by first copying the contents of the main function from 
     your completed decrypt.c main function. */

  /* Q4 Make the search for the secret key parallel on the GPU using CUDA. */

  unsigned int n, p, g, h, x;
  unsigned int Nints;

  unsigned int *data_fp = (unsigned int *) malloc(4*sizeof(unsigned int));

  FILE *fp;
  FILE *fm;
 
  fp = fopen("public_key.txt", "r");
  fm = fopen("message.txt" , "r");

  for(unsigned int i = 0; i < 4; i++) {
    fscanf(fp, "%u", data_fp+i);
  }  

  fclose(fp);

  n = data_fp[0];
  p = data_fp[1];
  g = data_fp[2];
  h = data_fp[3];

  //secret key
  
  fscanf(fm, "%u", Nints);

  unsigned int *m_data = (int *) malloc(Nints*sizeof(unsigned int));
  unsigned int *a_data = (int *) malloc(Nints*sizeof(unsigned int));

  unsigned int *data_fm = (unsigned char*) malloc(Nints*sizeof(unsigned char));

  for(unsigned int j =0; j < Nints; j++){
    fscanf(fm, "%u %u", m_data+j, a_data+j);
}

  fclose(fm);

  //Cuda work goes here
  //unsigned int Nthreads
  //dim3 I();
  //cudaMemcpy


  int bufferSize =1024;
  
  unsigned char *message = (unsigned char*) malloc(bufferSize*sizeof(unsigned char));
 
  unsigned int Nchars = ((n-1)/8)*Nints;

  ElGamaldecrypt(m_data, a_data, Nints, p , x);
  convertZtoString(m_data, Nints, message, Nchars);
  printf("The decrypted message: \"%s\" \n", message);

   return 0;

}
