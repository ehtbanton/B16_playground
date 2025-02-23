
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

#include <iostream>
using namespace std;

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

void b5_example_main() {
	double arr[] = {1,1,2,3,5,8,13};
	int size = sizeof(arr) / sizeof(arr[0]);
	double target = 5; // must be same type as array
	int result = binary_search(arr, size, target);
	if (result == -1) {
		cout << "Element not found" << endl;
	}
	else {
		cout << "Element found at index " << result << endl;
	}
}

// To make this use a double instead of unsigned char, I would just change the type of the vector to double and the type of the pixel values to double.
// I would also change the set_pixel function to take a double instead of an unsigned char.
// I would also change the display_image function to print out somethign which refers to doubles instead of unsigned chars.