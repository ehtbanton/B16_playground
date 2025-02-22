
/* Q3

Templates allow you to write fuctions which can take any type of input (generic types). This is useful because it 
allows you to write a function once and use it for many different types of input.

I'm not certain what is being asked for for what is a function template vs a template function. 
I think that a function template is the blueprint for a function (which accepts any type), while a template function 
is a function which has been instantiated from a function template.



Q4
Iterators are used as a standard way to access the elements of an STL container, e.g. a vector's element may be 
accessed by a vector<int>::iterator. This is useful because it allows you to write code which can be used with 
any container, rather than having to write a different version of the code for each container type (technically, the 
iterator itself needs to be implemented differently for each container, but the public interface can remain the same). 
They can also be implemented with increased safety features such as automatic bounds checking.
*/

#include <vector>
using namespace std;

void q4_snippet() {
	vector<int> v = {1, 2, 3, 4, 5};
	vector<int>::iterator it = v.begin();
	while (it != v.end()) {
		cout << *it << endl;
		it++;
	}
}