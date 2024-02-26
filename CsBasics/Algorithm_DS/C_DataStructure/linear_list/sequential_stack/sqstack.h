typedef int data_t;

typedef struct {
	data_t *data;
	int cap;
	int top_idx;
} sq_stack;

sq_stack *stack_create(int cap);

int stack_push(sq_stack *s, data_t value);

data_t stack_pop(sq_stack *s);

data_t stack_top(sq_stack *s);

int stack_clear(sq_stack *s);

int stack_free(sq_stack *s);

int stack_empty(sq_stack *s);

int stack_full(sq_stack *s);

