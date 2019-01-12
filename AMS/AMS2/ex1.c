#include <stdio.h>

void list_integers( void ) {
	// (a) Print the introductory message. 'Listing integers between 71 and 382...'
	printf("Listing integers between 71 and 382...\n");
	
	// (b) Declare an integer variable that will be used as a counter. 
	//     Make it initially equal to the start value.
	int counter = 71;

	// (c) Begin a WHILE statement that will execute its loop body if the
	//     counter is less than or equal to the end value.
	while(counter <= 382){
		// (e) Print the current value of the counter variable.
		printf("%d\n", counter);
		// (f) Add 1 to the counter variable.
		counter++;
	// (d) End the WHILE statement that starts at (c).
	}
}

int main( void ) {
	list_integers();
	return 0;
}