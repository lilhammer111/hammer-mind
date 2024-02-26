#include <stdio.h>
#include "single_linked_list.h"

int test_insert(linked_list H) {
	// test insert
	int inserted_val = 99, inserted_pos = 3;
	int res = list_insert(H, inserted_val, inserted_pos);
	if ( res == -1 ) {
		printf("failed to insert the node\n");
		return -1;
	}
	printf("after insert the number of %d at index %d, the list now is:\n", inserted_val, inserted_pos);
	res = list_show(H);
	if ( res == -1 ) {
		printf("failed to range the list\n");
		return -1;
	}
	
	return 0;
}

int test_get(linked_list H) {
	int cur_pos = 4;
	linked_list cur = list_get(H, cur_pos);
	if ( cur == NULL ) {
		return -1;
	}

	printf("the current node is the %dth one and the value is: %d\n",cur_pos, cur->data);
	return 0;
}

int test_delete(linked_list H) {
	int deleted_pos = 1;
	printf("to delete the node at index %d\n", deleted_pos);
	int res = list_delete(H, deleted_pos);
	if ( res == -1 ) {
		printf("failed to delete the node\n");
		return -1;
	}
	
	return 0;
}

linked_list test_free(linked_list H) {
	linked_list l = list_free(H);
	return l;
}



int main() 
{
	linked_list H;
	int res;

	H = list_create();
	if (H == NULL)
		return -1;
	
	int value;
	printf("please entry 5 numbers and the first one is: ");
	while (1) {
		scanf("%d", &value);
		if (value == -1) {
			break;
		}

		res = list_tail_insert(H, value);
		if (res == -1) {
			printf("failed to insert the value in tail\n");
			return -1;		
		}

		printf("please continue to entry, and entry -1 while the last one: ");
	}

	res = list_show(H);
	if ( res == -1 ) {
		printf("failed to show the list\n");
		return -1;	
	}
	
	// res = test_delete(H);
	// H = test_free(H);
	res = list_revert(H);
	if ( res == -1 ) {
		return res;
	}

	
	res = list_show(H);
	if ( res == -1 ) {
		printf("failed to show the list\n");
		return -1;	
	}

	return 0;
}
