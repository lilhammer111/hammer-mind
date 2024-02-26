typedef int data_t;

typedef struct node {
	data_t data;
	struct node * next;
} list_node, * linked_list;

linked_list list_create();

int list_tail_insert(linked_list H, data_t value); // head

int list_show(linked_list H);

linked_list list_get(linked_list H, int pos);

int list_insert(linked_list H, data_t value, int pos);

int list_delete(linked_list H, int pos);

linked_list list_free(linked_list H);

int list_revert(linked_list H);

linked_list list_max_adj_sum(linked_list H);
