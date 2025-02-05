

/*
a) A function has side effects if it is modifying something which is not a local variable, e.g. something out og its scope.
Having this in play makes it harder to track the flow of information in the program, and can make it harder to debug, as
well as potentially giving trouble when attempting parallel computing (if the same memory is accessed by multiple threads).
All in all, best avoided if possible.

b) The implementation below finds the remainder res when an integer num is divided by another integer s.
Problems with the implementation below:
- The function uses num and res as global variables, which is bad practice (not least because they have short, generic
  names which could be easily accidentally overwritten).
- r() is not a descriptive name for a function, and is confusing to read.
- There is no need for such complexity as division and modulo are built-in operators in C.


Original function:

	#include <stdio.h>

	int num, res;
	void r(int s) {
		while (num >= 0) { 
			num = num - s;
		} 
		num = num + s; 
		res = num;
	}

	inline void q2_original_function() {
		num = 10;
		r(4); printf
		("%d\n"
			, res
		);
	}

c) The implementation below is a better version of the function r() from b).
*/



inline int q2_improved_remainder(int number, int divisor) {
	int remainder = number % divisor;
	return remainder; // cout in main!
}