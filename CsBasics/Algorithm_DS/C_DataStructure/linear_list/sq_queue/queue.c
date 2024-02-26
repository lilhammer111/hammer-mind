#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"


queue_t *queue_create() {
	queue_t *q = (queue_t*)malloc(sizeof(queue_t));
	if (q == NULL) {
		printf("failed to allocate memory for the queue\n");
		return NULL;
	}

	memset(q->data, 0, sizeof(data_t));
	q->front = q->rear = 0;
	
	return q;
}

int queue_clear(queue_t *q) {
	if (q == NULL) {
		printf("the queue pointer is NULL\n");
		return -1;
	}

	q->front = q->rear = 0;
	return 0;
}

int queue_empty(queue_t *q) {
	if (q == NULL) {
		printf("the queue pointer is NULL\n");
		return -1;
	}

	return (q->front == q->rear ? 1 : 0);
}

int queue_full(queue_t *q) {
	if (q == NULL) {
		printf("the queue pointer is NULL\n");
		return -1;
	}
	
	return ((q->rear + 1) % N == q->front ? 1 : 0);
}

int enqueue(queue_t *q, data_t value) {
	if (q == NULL) {
		printf("the queue pointer is NULL\n");
		return -1;
	}
	
	if ((q->rear + 1) % N == q->front) {
		printf("enqueue failed. the queue is full\n");
		return -1;
	}
	
	q->data[q->rear] = value;
	q->rear = (q->rear + 1) % N;
	
	return 0;
}

data_t dequeue(queue_t *q) {
	if (q == NULL) {
		printf("the queue pointer is NULL\n");
		return -1;
	}
	
	if (q->rear == q->front) {
		printf("dequeue failed. the queue is empty\n");
		return -1;
	}
	
	data_t dequeued = q->data[q->front];
	q->front = (q->front + 1) % N;

	return dequeued;
}

int queue_free(queue_t *q) {
	if (q == NULL) {
		printf("the queue pointer is NULL\n");
		return -1;
	}

	free(q);
	q = NULL;

	return 0;
}
