typedef char data_t;

typedef struct node_t {
	data_t data;
	struct node_t *left;
	struct node_t *right;
} tree_t;

tree_t *tree_create();

void preorder(tree_t *t);

void inorder(tree_t  *t);

void postorder(tree_t *t);
