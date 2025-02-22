
/*
Q5

A refresher:
Binary search is a search algorithm that finds the position of a target value within a sorted array.
First, we compare the target value to the middle element of the array. 
	If the target value is equal to the middle element, we've found the target value. 
	If the target value is less than the middle element, we search the left half of the array.
	If the target value is greater than the middle element, we search the right half of the array.
We repeat this process until we find the target value or until the subarray has no more elements.

*/



template <typename T>

T binary_search(T arr[], int size, T target) {
	int low = 0;
	int high = size - 1;
	while (low <= high) {
		int mid = (low + high) / 2;
		if (arr[mid] == target) {
			return mid;
		}
		else if (arr[mid] < target) {
			low = mid + 1;
		}
		else {
			high = mid - 1;
		}
	}
	return -1;
}