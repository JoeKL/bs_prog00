#include "guessing.h"

int guess_the_number(void)
{
	int mid = 0;
	int max = 100000;
	int guess = (max + mid) / 2;
	mid = guess;
	int tuer = 0;
	//int correct = evaluate(mid);
	while(tuer) {
		mid = guess;
		int correct = evaluate(mid);
		switch(correct){
		case 1 : 
			// guess < target
			guess = (max + mid) / 2;
			mid = guess;
			break;
		case -1 : 
			// guess > target
			guess = mid / 2;
			max = mid;
			mid = guess;
			break; 
		case 0 :
			// guess = target
			tuer = 1;
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
	return guess; // Return the correct number
}
