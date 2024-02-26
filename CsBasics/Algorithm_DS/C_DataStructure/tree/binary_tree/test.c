#include <stdio.h>
#include "tree.h"

int main()
{

	tree_t *root = tree_create();
	if (root == NULL) {
		printf("failed to create the tree\n");
		return -1;
	}

	printf("preorder : ");
	preorder(root);
	puts("");

	printf("inorder : ");
	inorder(root);
	puts("");

	printf("postorder : ");
	postorder(root);
	puts("");

	return 0;
}	
