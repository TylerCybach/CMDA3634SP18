#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "functions.h"

int main (int argc, char **argv) {

	//seed value for the randomizer 
  double seed = clock(); //this will make your program run differently everytime
  //double seed = 0; //uncomment this and your program will behave the same everytime it's run

  srand(seed);

  int bufferSize = 1024;
  unsigned char *message = (unsigned char *) malloc(bufferSize*sizeof(unsigned char));

  printf("Enter a message to encrypt: ");
  int stat = scanf (" %[^\n]%*c", message); //reads in a full line from terminal, including spaces

  //declare storage for an ElGamal cryptosytem
  unsigned int n, p, g, h;

  printf("Reading file.\n");

  /* Q2 Complete this function. Read in the public key data from public_key.txt,
    convert the string to elements of Z_p, encrypt them, and write the cyphertexts to 
    message.txt */

  //fscanf( ,npgh) 

  unsigned int *data = (int *) malloc(4*sizeof(unsigned int));

  FILE* fp = fopen("public_key.txt", "r");
  
  for (int i = 0; i < 4; i++){
     fscanf(fp, "%u", data+i);
  }
 
  fclose(fp);

  //array data
  n = data[0]; 
  p = data[1];
  g = data[2];
  h = data[3];
  
  unsigned int charsPerInt = (n-1)/8;
  padString(message, charsPerInt);

  unsigned int Nchars = strlen(message);
  unsigned int Nints =  Nchars/charsPerInt;


  unsigned int *a = (unsigned int *) malloc(Nints*sizeof(unsigned int));

  unsigned int *Zmessage = (unsigned int *) malloc(Nints*sizeof(unsigned int));
  
  convertToStringToZ(message, Nchars, Zmessage, Nints);

  ElGamalEncrypt(Zmessage, a, Nints, p, g, h);

  FILE *fm = fopen("message.txt", "w");

  for (int j = 0; j<Nints; j++) {
    fprintf(fp, "%u \n", Zmessage[j], a[j]);
  }
  
  fclose(fm);
  
  return 0;
}
