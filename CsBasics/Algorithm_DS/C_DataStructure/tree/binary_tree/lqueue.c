#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lqueue.h"

lqueue_t *lq_create() {
	lqueue_t *lq_p = (lqueue_t*)malloc(sizeof(lqueue_t));
	if (lq_p == NULL) {
		printf("failed to allocate memory for linked queue\n");
		return NULL;
	}

	lq_p->front = lq_p->rear = (node_t*)malloc(sizeof(node_t));
	if (lq_p->front == NULL) {
		printf("failed to allocate memory for queue node\n");
		free(lq_p);
		lq_p = NULL;
		return NULL;
	}

	lq_p->front->data = 0;
	lq_p->front->next = NULL;
	 
	return lq_p;
}

int enqueue(lqueue_t *lq_p, data_t val) {
	if (lq_p == NULL) {
		printf("the linked queue pointer is NULL\n");
		return -1;
	}

	node_t *node_p = (node_t*)malloc(sizeof(node_t));
	if (node_p == NULL) {
		printf("failed to allocate memory for the new node\n");
		return -1;
	}

	node_p->data = val;
	node_p->next = NULL;

	lq_p->rear->next = node_p;
	lq_p->rear = node_p;

	return 0;
}

data_t dequeue(lqueue_t *lq_p) {
	if (lq_p == NULL) {
		printf("the linked queue pointer is NULL\n");
		return -1;
	}

	if (lq_empty(lq_p)) {
		printf("dequeue failed. the linked queue is empty\n");
		return -1;
	}

	node_t *head = lq_p->front;
	lq_p->front = head->next;
	
	free(head);
	
	return lq_p->front->data;
}

int lq_empty(lqueue_t *lq_p) {
	if (lq_p == NULL) {
		printf("the linked queue pointer is NULL\n");
		return -1;
	}

	return lq_p->front == lq_p->rear ? 1 : 0;
}

int lq_clear(lqueue_t *lq_p) {
	if (lq_p == NULL) {
		printf("the linked queue pointer is NULL\n");
		return -1;
	}
	
	while (lq_p->front->next) {
		node_t *org_head = lq_p->front;
		lq_p->front = lq_p->front->next;
		// printf("free for clear: %d\n", org_head->data);
		free(org_head);
		org_head = NULL;
	}


	return 0;
}

int lq_free(lqueue_t *lq_p) {
	if (lq_p == NULL) {
		printf("the linked queue pointer is NULL\n");
		return -1;
	}

	while (lq_p->front) {
		node_t *org_head = lq_p->front;
		lq_p->front = org_head->next;
		// printf("free : %d\n", org_head->data);
		free(org_head);
	}
	

	free(lq_p);
	lq_p = NULL;

	return 0;
}
