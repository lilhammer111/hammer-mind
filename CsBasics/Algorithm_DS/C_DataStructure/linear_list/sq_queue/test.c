#include <stdio.h>
#include "queue.h"

int main()
{
	queue_t *q = queue_create();
	if (q == NULL) {
		printf("failed to create the queue\n");
		return -1;
	}

	int loop_times = 5;
	for (int i = 0; i < loop_times; i++) {
		enqueue(q, i * 10);
		printf("enqueue: %d\n", i * 10);
	}

	if (queue_full(q)) {
		printf("the queue is full\n");
	} else {
		printf("the queue is not full\n");
	}

	while (!queue_empty(q)) {
		printf("dequeue: %d\n", dequeue(q));
	}

	return 0;
}
