#include <stdio.h>

int binary_search(int * nums,int target, int left, int right) {
    if ( left > right )
        return -1;

    int middle = ( left + right ) / 2;
    if ( nums[middle] == target )
        return middle;

    if ( nums[middle] < target ) {
        return binary_search(nums, target, middle + 1, right);
    } 
    return binary_search(nums, target, left, middle - 1);
}

int search(int* nums, int numsSize, int target) {
    return binary_search(nums, target, 0, numsSize - 1);
}

int main()
{
	printf("the length of the list is: ");
	int len;
	scanf("%d", &len);
	printf("and fill the list with: ");
	int input;
	int nums[len];
	for ( int i = 0; i < len; i++ ) {
		scanf("%d", &input); 
		nums[i] = input;
	}
	printf("and entry a target number: ");
	scanf("%d", &input);	
	int index = search(nums, len, input); 
	printf("the index of the target is: %d\n", index);
	return 0;
}
