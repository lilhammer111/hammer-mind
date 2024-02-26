typedef int data_t;

#define N 64

typedef struct {
	data_t data[N];
	int front;
	int rear;
} queue_t;

queue_t *queue_create();

int queue_clear(queue_t *q);

int queue_empty(queue_t *q);

int queue_full(queue_t *q);

int enqueue(queue_t *q, data_t value);

data_t dequeue(queue_t *q);

int queue_free(queue_t *q);
