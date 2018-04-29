#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "functions.h"


int main (int argc, char **argv) {

  //declare storage for an ElGamal cryptosytem
  unsigned int n, p, g, h, x;
  unsigned int Nints;

  //get the secret key from the user
  printf("Enter the secret key (0 if unknown): "); fflush(stdout);
  char stat = scanf("%u",&x);

  printf("Reading file.\n");

  /* Q3 Complete this function. Read in the public key data from public_key.txt
    and the cyphertexts from messages.txt. */

  //public key first dec after secret key

  //allocating space for fp
  unsigned int *data_fp = (unsigned int *) malloc(4*sizeof(unsigned int));

  FILE *fp;
  FILE *fm;

  fp = fopen("public_key.txt", "r");
  fm = fopen("message.txt", "r");

  for(unsigned int i = 0; i < 4; i++) {
    fscanf(fp, "%u", data_fp+i);
  }
 
  fclose(fp);  
  
  n = data_fp[0];
  p = data_fp[1];
  g = data_fp[2];
  h = data_fp[3];
  



  // find the secret key
  if (x==0 || modExp(g,x,p)!=h) {
    printf("Finding the secret key...\n");
    double startTime = clock();
    for (unsigned int i=0;i<p-1;i++) {
      if (modExp(g,i+1,p)==h) {
        printf("Secret key found! x = %u \n", i+1);
        x=i+1;
      } 
    }
    double endTime = clock();

    double totalTime = (endTime-startTime)/CLOCKS_PER_SEC;
    double work = (double) p;
    double throughput = work/totalTime;

    printf("Searching all keys took %g seconds, throughput was %g values tested per second.\n", totalTime, throughput);
  }

  /* Q3 After finding the secret key, decrypt the message */
  fscanf(fm, "%u", &Nints);
  
  //allocating space for m and a arrays
  unsigned int *m_data = (int *) malloc(Nints*sizeof(unsigned int));
  unsigned int *a_data = (int *) malloc(Nints*sizeof(unsigned int));

  unsigned char *data_fm = (unsigned char*) malloc(Nints*sizeof(unsigned char));  

  for(unsigned int j = 0; j < Nints; j++){
     fscanf(fm, "%u %u", m_data+j, a_data+j);
  }
  
  fclose(fm);

  int bufferSize =1024;
 

  unsigned char *message = (unsigned char *) malloc(bufferSize*sizeof(unsigned char));  

  unsigned int Nchars =( (n-1)/8)*Nints;



  ElGamalDecrypt(m_data, a_data, Nints, p, x);   
  convertZToString(m_data, Nints, message, Nchars);
  printf("The decrypted message: \"%s\" \n", message); 
  return 0;
}
