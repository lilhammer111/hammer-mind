#include "tree.h"

typedef tree_t* data_t;

typedef struct node {
	struct node *next;
	data_t data;
} node_t;

typedef struct {
	node_t *front;
	node_t *rear;
} lqueue_t;
 
lqueue_t *lq_create();

int enqueue(lqueue_t *lq_p, data_t val);

data_t dequeue(lqueue_t *lq_p);

int lq_empty(lqueue_t *lq_p);

int lq_clear(lqueue_t *lq_p);

int lq_free(lqueue_t *lq_p);
