#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

//helper function that determines if the inputted integer is a prime number
bool isPrime(int n);

void main() {

	//bool set as true my function wants to see if its false
	int n;
	
	//Max number that can be inputted is 2147483647
	printf("Enter a number ");
	scanf("%d",&n);


	if(isPrime(n) == true){
		printf("%d is prime. \n", n);
	} else {
		printf("%d is not prime. \n",n);
	}
        		
}

//Helper function
bool isPrime(int n){
	
	int sqrtN = (int) sqrt(n);

	for(int i = 2; i<sqrtN; i++){
		int x = (n%i);
		if(x ==0){
			return false;
		}
	} 
	
	return true;
}

