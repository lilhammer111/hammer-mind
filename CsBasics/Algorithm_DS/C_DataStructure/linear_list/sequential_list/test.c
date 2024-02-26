#include "sqlist.h"
#include <stdio.h>

void test_purge() {
	sqlink L;

	L = list_create();

	if ( L == NULL ) {
		printf("failed to create a list\n");
		return;
	}

	for ( int i = 0; i < 5; i++ ) {
		list_insert(L, 23, 0);
	}

	for ( int i = 0; i < 5; i++ ) {
		list_insert(L, 533, 0);
	}

	for ( int i = 0; i < 5; i++ ) {
		list_insert(L, 1, 0);
	}

	list_show(L);
	
	list_purge(L);
		
	list_show(L);
}


void test_merge() {
	sqlink L1;

	L1 = list_create();
	if ( L1 == NULL ) {
		printf("failed to create a list\n");
		return;
	}

	for ( int i = 3; i < 8; i++ ) {
		list_insert(L1, i, 0);
	}

	list_show(L1);

	sqlink L2;

	L2 = list_create();
	if ( L2 == NULL ) {
		printf("failed to create a list\n");
		return;
	}

	for ( int i = 0; i < 5; i++ ) {
		list_insert(L2, i, 0);
	}

	list_show(L2);

	printf("********************************\n");

	int res = list_merge(L1, L2);
	if ( res != -1 ) {
		return;
	}

	list_show(L1);
}

void test_delete_at() {
	sqlink L;

	L = list_create();

	if ( L == NULL ) {
		printf("failed to create a list\n");
		return;
	}

	for ( int i = 0; i < 5; i++ ) {
		list_insert(L, i, 0);
	}

	list_show(L);

	list_delete_at(L, 0);

	list_show(L);

	list_delete(L);
}


void test_insert() {
	sqlink L;
	L = list_create();
	if ( L == NULL ) {
		printf("failed to create a list\n");
		return;
	}

	for ( int i = 0; i < 5; i++ ) {
		list_insert(L, i, 0);
	}
	
	list_show(L);
	
	list_delete(L);
} 

int main(int argc, const char *argv[])
{
	// test_insert();
	// test_delete_at();
	// test_merge();
	test_purge();
	return 0;
}
