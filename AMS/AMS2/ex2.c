#include <stdio.h>

void count_down( void ) {
	// (a) Print the introductory message.
	printf("Counting backwards in steps of 4, beginning at 354, stopping before 35.\n");
	
	// (b) Declare an integer variable that you will use to count. Initially 
	//     the counter should equal the start value, 354.
	int counter = 354;
	
	// (c) Begin a WHILE statement that will execute its loop body if the 
	//     counter is greater than the end value, 35.
	while(counter>35){
		// (e) Print the value of the counter on a line by itself.
		printf("%d\n", counter);
		// (f) Subtract the step size, 4, from the counter.
		counter = counter - 4;
	// (d) End the WHILE statement
	}
}

int main( void ) {
	count_down();
	return 0;
}