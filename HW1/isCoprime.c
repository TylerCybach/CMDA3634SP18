#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//helper function to determin the gcd
int gcd(int a, int b);

void main() {

   int a, b; // allocates integers 'a,b'

   printf("Enter the first number:");
   scanf("%d", &a);

   printf("Enter the second number:");
   scanf("%d", &b);

   int comd = gcd(a,b);
   
   if(comd == 1){
   printf("%d and %d are coprime \n",a, b);
   }
   else
   {
   printf("%d and %d are not coprime \n", a, b);
   }
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





