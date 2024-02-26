#include <stdio.h>
#include "single_linked_list.h"
#include <stdlib.h>


linked_list list_create() {
	linked_list H = (linked_list)malloc(sizeof(list_node));
	if (H == NULL) {
		printf("failed to allocate memory\n");
		return H;
	}
	
	H->data = 0;
	H->next = NULL;	
	
	return H;
}

int list_tail_insert(linked_list H, data_t value) {
	if ( H == NULL ) {
		printf("head is NULL\n");
		return -1;
	}
	
	linked_list cur = H;
	while (1) {
		if ( cur->next == NULL ) {
			linked_list tail_node = (linked_list)malloc(sizeof(list_node));
			if ( tail_node == NULL ) {
				printf("failed to allocate the memory for the tail node\n");
				return -1;	
			}
			
			tail_node->data = value;
			tail_node->next = NULL;
				
			cur->next = tail_node;
			
			return 0;
		}
		
		cur = cur->next;
	} 
	return -1;
} 

int list_show(linked_list H) {
	if ( H == NULL ) {
		printf("the list is NULL\n");
		return -1;
	}

	linked_list cur = H;
	printf("the list is : ");
	while ( cur->next != NULL ) {
		printf("%d ", cur->next->data);
		cur = cur->next;
	}
	puts("");
	return 0;
}

linked_list list_get(linked_list H, int pos) {
	if ( H == NULL ) {
		printf("the list is NULL\n");
		return NULL;
	}

	if ( pos == -1 ) {
		return H;
	}
	
	linked_list cur = H;
	for ( int i = 0; i < pos + 1; i++ ) {
		if ( cur->next == NULL ) {
			printf("position out of the list range\n");
			return NULL;
		}

		cur = cur->next;
	}

	return cur;	
}

int list_insert(linked_list H, data_t value, int pos) {
	if ( H == NULL ) {
		printf("the list is NULL\n");
		return -1;
	}
	
	linked_list prev_node = list_get(H, pos - 1);
	if ( prev_node == NULL ) {
		printf("failed to get the list\n");
		return -1;
	}

	linked_list inserted_node = (linked_list)malloc(sizeof(list_node));
	if ( inserted_node == NULL ) {
		printf("failed to allocate the memory for the inserted node\n");
		return -1;
	}

	inserted_node->next = prev_node->next;
	prev_node->next = inserted_node;

	inserted_node->data = value;
	
	return 0;
}

int list_delete(linked_list H, int pos) {
	if ( H == NULL ) {
		printf("the list is NULL\n");
		return -1;
	}
	
	
	linked_list prev_node = list_get(H, pos - 1);
	if ( prev_node == NULL ) {
		printf("failed to get the list\n");
		return -1;
	}

	linked_list deleted_node = prev_node->next;
	if ( deleted_node == NULL ) {
		printf("the node to delete is not existed\n");
		return -1;
	}
	
	prev_node->next = deleted_node->next;
	
	printf("the value of the node to be free is: %d\n", deleted_node->data);
	free(deleted_node);
	deleted_node = NULL;
	
	return 0;
}

linked_list list_free(linked_list H) {
	if ( H == NULL ) 
		return NULL;
	linked_list cur = H;
	linked_list prev;
	while ( cur != NULL ) {
		prev = cur;
		cur = cur->next;
		printf("the value of the node to be free is %d\n", prev->data);
		free(prev); 
	}
	
	return NULL;
}

int list_revert(linked_list H) {
	if ( H == NULL ) {
		printf("the list is NULL\n");
		return -1;
	}

	if ( H->next == NULL || H->next->next == NULL ) {
		return 0;
	}

	linked_list cur = H->next->next, moved_node;
	H->next->next = NULL;

	while ( cur != NULL ) {
		moved_node = cur;
		cur = cur->next;
		moved_node->next = H->next;
		H->next = moved_node;
	}

	return 0;
}

linked_list list_max_adj_sum(linked_list H) {
	if ( H == NULL ) {
		printf("the list is NULL\n");
		return NULL;
	}
	
	if ( H->next == NULL || H->next->next == NULL ) {
		printf("the node is less than two\n");
		return NULL;
	}

	int max_sum = 0, adj_sum = 0;
	linked_list cur = H->next, max_node = H->next;
	while ( cur->next != NULL ) {
		adj_sum = cur->data + cur->next->data;
		if ( adj_sum > max_sum ) {
			max_sum = adj_sum;
			max_node = cur;
		}
		
		cur = cur->next;
	}

	return max_node;
}	



