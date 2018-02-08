#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//helper function to determine gcd
int gcd(int a, int b);

void main() {

   int a, b; // allocates integers 'a,b'

   printf("Enter the first number:");
   scanf("%d", &a);

   printf("Enter the second number:");
   scanf("%d", &b);

   int comd = gcd(a,b);

   printf("The greatest common divisor %d and %d is %d \n", a,b,comd);

}

//helper function
int gcd(int a , int b){
 
   if (b != 0){
		gcd(b,a%(b));
	}
	else{
	   return a;
	}

}





