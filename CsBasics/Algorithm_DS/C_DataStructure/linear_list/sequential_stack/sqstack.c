#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqstack.h"

sq_stack *stack_create(int cap) {
	if (cap <= 0) {
		printf("the cap value should be larger than 0\n");
		return NULL;
	}

	sq_stack *s = (sq_stack*)malloc(sizeof(sq_stack));
	if (s == NULL) {
		printf("failed to allocate memory for stack\n");
		return NULL;
	}

	s->data = (data_t*)malloc(cap * sizeof(data_t));
	if (s->data == NULL) {
		printf("failed to allocate memory for the array of the stack\n");
		free(s);
		s = NULL;
		return NULL;
	}
	
	memset(s->data, 0, cap * sizeof(data_t));
	s->cap = cap;
	s->top_idx = -1;
	
	return s;
}

int stack_push(sq_stack *s, data_t value) {
	if (s == NULL) {
		printf("the stack pointer is NULL\n");
		return -1;
	}

	if (s->top_idx == (s->cap - 1)) {
		printf("push failed. the stack is full\n");
		return -1;
	}

	s->top_idx++;
	s->data[s->top_idx] = value;

	return 0;
}

data_t stack_pop(sq_stack *s) {
	if (s == NULL) {
		printf("the stack pointer is NULL\n");
		return -1;
	}

	if (s->top_idx == -1) {
		printf("pop failed. the stack is empty\n");
		return -1;
	}

	s->top_idx--;
	return s->data[s->top_idx + 1];
}

data_t stack_top(sq_stack *s) {
	if (s == NULL) {
		printf("the stack pointer is NULL\n");
		return -1;
	}
	return 0;
}

int stack_clear(sq_stack *s) {
	if (s == NULL) {
		printf("the stack pointer is NULL\n");
		return -1;
	}

	s->top_idx = -1;
	return 0;
}

int stack_free(sq_stack *s) {
	if (s == NULL) {
		printf("the stack pointer is NULL\n");
		return -1;
	}

	if (s->data != NULL) {
		free(s->data);
		s->data = NULL;
	}

	free(s);
	s = NULL;

	return 0;
}

/*
 * check if the stack is empty
 * @param *s the pointer of the stack
 * @return 1 for empty, 0 for not, -1 for error
 */
int stack_empty(sq_stack *s) {
	if (s == NULL) {
		printf("the stack pointer is NULL\n");
		return -1;
	}
	
	return (s->top_idx == -1 ? 1 : 0);
}

int stack_full(sq_stack *s) {
	if (s == NULL) {
		printf("the stack pointer is NULL\n");
		return -1;
	}
	
	return (s->top_idx == (s->cap - 1) ? 1 : 0);
}
