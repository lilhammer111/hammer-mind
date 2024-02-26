#include <stdio.h>
#include <stdlib.h>
#include "tree.h"


tree_t *tree_create() {
	data_t ch;
	scanf("%c", &ch);
	if (ch == '#') {
		return NULL;
	}

	tree_t *root = (tree_t*)malloc(sizeof(tree_t));
	if (root == NULL) {
		printf("failed to allocate memory for binary tree\n");
		return NULL;
	}

	root->data = ch;
	root->left = tree_create();
	root->right = tree_create();

	return root;
}


void preorder(tree_t *t) {
	if (t == NULL) {
		return;
	}

	printf("%c ", t->data);
	preorder(t->left); 
	preorder(t->right); 
}


void inorder(tree_t  *t) {
	if (t == NULL) {
		return;
	}
	
	inorder(t->left);
	printf("%c ", t->data);
	inorder(t->right);
}


void postorder(tree_t *t) {
	if (t == NULL) {
		return;
	}

	postorder(t->left);
	postorder(t->right);
	printf("%c ", t->data);
}

