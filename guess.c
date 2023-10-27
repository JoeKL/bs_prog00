#include "guessing.h"
#include <stdio.h>

unsigned int guess_the_number(void)
{
	int min = 0;
	int mid = 0;
	int max = 99999;
	int tuer = 1;
	int correct = 2;
	while(tuer) {
		mid = (max + min) / 2;
		correct = evaluate(mid);
		switch(correct){
		case 1 : 
			// guess < target
			min = mid;
			break;
		case -1 : 
			// guess > target
			max = mid;
			break; 
		case 0 :
			// guess = target
			tuer = 0;
			break;
		default:
			break;
		}
	}
	/*
	 * Enter your code here!
	 * You should call evaluate(int), to check whether your number is correct.
	 * E.g., evaluate(12345)
	 */
	return mid; // Return the correct number
}
