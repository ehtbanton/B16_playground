#include "../sheet_a/a_1.hpp"
#include "../sheet_a/a_2.hpp"
#include "../sheet_a/a_3,4.hpp"
#include "../sheet_a/a_5,6.hpp"
#include "../sheet_a/a_7.hpp"
#include "../sheet_a/a_8.hpp"
#include "../sheet_a/a_9.hpp"
#include "../sheet_a/a_10.hpp"
#include "../sheet_b/b_1,2.hpp"
#include "../sheet_b/b_5.hpp"

#include <iostream>
using namespace std;

int main()
{

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	// Q1
	//q1_say_hello();

	// Q2
	//int remainder = q2_improved_remainder(19, 7); cout << remainder << endl;
	
	// Q3
	// See a_3-4.hpp

	// Q4
	//q4_mass_spring_sim(); // nice sim :)

	// Q5-Q8
	// See other headers

	// Q9
	//q9_main();

	// Q10
	//q10_example_main();
	//q10_sum_tan_main();

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// B1
	//b1_example_main();


	// B5
	int arr[] = {1, 1, 2, 3, 5, 8, 13, 21, 34, 55};
	int size = sizeof(arr) / sizeof(arr[0]);
	int target = 21;
	std::cout << "Target at location " << binary_search(arr, size, target);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	return 0;
}

// To make this use a double instead of unsigned char, I would just change the type of the vector to double and the type of the pixel values to double.
// I would also change the set_pixel function to take a double instead of an unsigned char.
// I would also change the display_image function to print out somethign which refers to doubles instead of unsigned chars.