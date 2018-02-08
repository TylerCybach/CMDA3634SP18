#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

//helper function to find the first generator of a prime number
int findGenerator(int p);

//This function can run large number but has hang
void main(){

	int p;

	//large primes can be entered but there is some lag
	printf("Enter a prime \n");
	scanf("%d", &p);

	int gen = findGenerator(p);

	printf("%d is a generator of Z_%d \n", gen, p);
}

//helper function
int findGenerator(int p){
	
	int cnt = 1; //integer used to determine if a generator has a complete set

	bool hoopla2 = false; //boolean used to determine if generator went thruogh a whole set

	for(int g = 2; g < p-1;g++){
		

		for(int r = 1; r <= p-2; r++){
			
			int y = pow(g,r);
			
			//break if generator has a mod 1
			if(y%p ==1){
			break;
			}
			cnt++;
			
			//break if generator made a complete set
			if (cnt == p-1){
			hoopla2 = true;
			break;
			}
		}
		
		if(hoopla2 == true){
		return g;
		}	
	}
}
