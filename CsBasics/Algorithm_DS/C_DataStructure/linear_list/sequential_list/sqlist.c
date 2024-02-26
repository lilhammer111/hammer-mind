#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlist.h"

sqlink list_create() {
	sqlink L;
	L = (sqlink)malloc(sizeof(sqlist));	
	if ( L == NULL ) 
	{
		printf("failed to allocate memory\n");
		return L;
	}
	
	memset(L, 0, sizeof(sqlist));

	L -> last = -1;	
	
	return L;
}

/*
 * set all values of a sequential list to 0 
 * @param L the sequential list
 * @return 0 for success, -1 for fail
 */
int list_clear(sqlink L) {
	if ( L == NULL )
	{
		printf("the list pointer is NULL\n");
		return -1;	
	}

	memset(L, 0, sizeof(sqlist));
	L -> last = -1;

	return 0;
}

/*
 * check if the sequential list is empty
 * @param L the sequential list
 * @return 1 for empty, 0 for not
 */
int list_empty(sqlink L) {
	if ( L -> last == -1 )
	{
		return 1;	
	}

	return 0;
}

/*
 * get the length of the list
 * @param the list
 * @return the length of the list, and -1 for the null pointer
 */
int list_length(sqlink L) {
	if ( L == NULL ) 
	{
		printf("the list pointer is NULL\n");
		return -1;
	}

	return L -> last + 1;	
}

int list_locate(sqlink L, data_t value) {
	if ( L == NULL ) {
		printf("the list pointer is NULL\n");
		return -1;
	}

	for ( int i = 0; i < list_length(L); i++ ) {
		if ( L->data[i] == value ) {
			return i;
		}
	}
	 
	return -1;
}

int list_insert(sqlink L, data_t value, int pos) {
	if ( L -> last == N - 1 )
	{
		printf("failed to insert the value, the list is full\n");
		return -1;
	}
	
	if ( pos < 0 || pos > L -> last + 1 )
	{
		printf("wrong position for inserting\n");
		return -1;
	}

	for ( int i = L -> last + 1; i > pos; i-- )
	{
		L -> data [i] = L -> data [i-1];
	}
	
	L -> data [pos] = value;
	L -> last ++;
		
	return 0;
}

int list_show(sqlink L) {
	if ( L == NULL )
	{
		printf("the list pointer is NULL\n");
		return -1;
	}

	if ( L->last == -1 )
	{
		printf("the list is empty\n");
		return -1;
	}
	
	printf("[");	
	for ( int i = 0; i < L->last + 1; i++ )
	{
		if ( i == L->last )
		{
			printf("%d", L->data[i]);
		}
		else
		{
			printf("%d, ", L->data[i]);
		}
	}
	printf("]\n");
	
	return 0;
}

int list_delete(sqlink L) {
	if ( L == NULL ) {
		printf("the list pointer is NULL\n");
		return -1;
	}
	
	free(L);
	L = NULL;
	return 0;
}


int list_merge(sqlink L1, sqlink L2) {
	if ( L1 == NULL || L2 == NULL ) {
		printf("the list pointer of L1 or L2 is NULL\n");
		return -1;
	}

	for ( int i = 0; i < list_length(L2); i++ ) {
		if ( list_locate(L1, L2->data[i]) == -1 ) {
			int res = list_insert(L1, L2->data[i], L1->last + 1);
			if ( res == -1 ) {
				// the list is full
				return -1;
			}
		}
	}
		
	return 0;
}

int list_purge(sqlink L) {
	if ( L == NULL ) {
		printf("the list is not existed or the length is 0\n");
		return -1;
	}

	if ( L->last == 0 ) {
		return 0;
	}

	for ( int i = 0; i < list_length(L); i++ ) {
		for ( int j = i + 1; j < list_length(L); j++ ) {
			if ( L->data[i] == L->data[j] ) {	
				int res = list_delete_at(L, j);
				if ( res != 0 ) {
					printf("failed to delete repeating values\n");
					return -1;
				} 
				j--;
			}
		}
	}
	return 0;
}

int list_delete_at(sqlink L, int pos) {
	if ( L->last == -1 ) {
		printf("the list is empty\n");
		return -1;	
	}

	if ( pos < 0 || pos > L->last ) {
		printf("wrong position for deleting elements\n");
		return -1;
	}

	for ( int i = pos; i < L->last; i++ ) {
		L->data[i] = L->data[i+1];
	}

	L->last--;
	return 0;
}
