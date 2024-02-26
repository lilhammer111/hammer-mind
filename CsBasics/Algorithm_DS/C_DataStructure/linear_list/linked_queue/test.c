#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lqueue.h"

int main()
{
	// test create
	lqueue_t *lq_p = lq_create();
	if (lq_p == NULL) {
		printf("failed to create a linked queue\n");
		return -1;
	}

	// test enqueue
	int loop = 5;
	for (int i = 0; i < loop; i++) {
		enqueue(lq_p, i * 10);
		printf("enqueue: %d\n", i * 10);
	}

	// test dequeue and empty
	// while (!lq_empty(lq_p)) {
	//	printf("dequeue: %d\n", dequeue(lq_p));
	// }

	// test clear
	enqueue(lq_p, 10);
	printf("enqueue: %d\n", 10);
	lq_clear(lq_p);
	if (lq_empty(lq_p)) {
		printf("success to clear the linked queue\n");
	}

	lq_free(lq_p);
 
	return 0;
}
