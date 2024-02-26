#include <stdio.h>
#include <stdlib.h>
#include "sqstack.h"

int main()
{
	// create stack
	printf("entry a number for the cap of created stack: ");
	
	int cap = 0;
	scanf("%d", &cap);

	sq_stack *s = stack_create(cap);
	if (s == NULL) {
		printf("failed to create the stack\n");
		return -1;
	}

	//test push 
	stack_push(s, 10);
	stack_push(s, 20);
	stack_push(s, 30);
	stack_push(s, 40);

	// test pop
	while (!stack_empty(s)) {
		printf("the value popped from the stack is: %d\n", stack_pop(s));
	}

	stack_free(s);


	return 0;
}
