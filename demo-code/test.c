#include <stdio.h>
#include "test.h"

int main(void) {
	for (int i = 0; i < 5; i++)
		printf("hello world!\n");
	some_fn();	
	printf("all done!\n");
	return 0;
}