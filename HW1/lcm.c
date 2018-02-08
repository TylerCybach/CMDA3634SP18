#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//helper function used to determine the gcd
int gcd(int a, int b);

void main () {

   int a , b; //allocates integers 'a,b'
   
   printf("Enter the first number:");
   scanf("%d", &a);

   printf("Enter the second number:");
   scanf("%d", &b);

   int lcomm = (a*b)/gcd(a,b);

   printf("The least common multiple of  %d and %d is %d. \n", a,b, lcomm);	
}

//helperfunction
int gcd(int a, int b){
   if (b!=0){
      gcd(b,a%b);
   }
   else{
      return a;
  }
}






