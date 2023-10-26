#include "guessing.h"
#include <math.h>

unsigned int guess_the_number(void) //lt. Aufgabenstellung darf dieser Header nicht verändert werden.
{

    int left = 0;
    int right = 99999;
    while (left <= right){
		int mid = round((left + right)/2);
				if (evaluate(mid) == 0){
					return mid;
				} else if (evaluate(mid) == 1) {	// evaluate == 1 wenn mid < target
					left = mid + 1;
				} else if (evaluate(mid) == -1) {	// evaluate == -1 wenn mid > target
					right = mid - 1;
				}
	}
	return -1;

}
