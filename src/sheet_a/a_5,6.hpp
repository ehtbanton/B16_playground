#include <vector>

class MathVector {

private:
    int length;
	std::vector<double> elements;
	

public:
    // i. Default constructor taking only vector size
    MathVector(int size) {
        length = size;
        elements = std::vector<double>(size, 0.0); // Initialize with zeros
    }

    // ii. Constructor with length and array initialization
	MathVector(int size, const double arr[]) { // double arr[] is equivalent to double* arr
        length = size;
        elements = std::vector<double>(arr, arr + size);
    }

    // iii. Copy constructor
    MathVector(const MathVector& other) {
        this->length = other.length;
        this->elements = other.elements;
    }

	// 6)a) We add an overloaded square bracket operator to access elements. It obviously has to be a class member
	// function, as it's a specific operation for the MathVector class, and must be public to be accessible.
	// Both the const and non-const versions are needed: the non-const version allows for element modification,
	// but will not be allowed to use on const objects.
    double& operator[](int index) {
        if (index < 0 || index >= length) {
            throw std::out_of_range("Index out of bounds");
        }
        return elements[index];
    }
    const double& operator[](int index) const {
        if (index < 0 || index >= length) {
            throw std::out_of_range("Index out of bounds");
        }
        return elements[index];
    }

    // Operator overloading for products:
    // 1. Member function for vector * scalar (vα)
    MathVector operator*(double scalar) const {
        MathVector result(length);
        for (int i = 0; i < length; i++) {
            result[i] = elements[i] * scalar;
        }
        return result;
    }

    // 2. Friend function for scalar * vector (αv)
	// (friend function is not a member of the class, but has access to its private members.
	// So we can copy the member function and swap the order of the operands.)
    friend MathVector operator*(double scalar, const MathVector & vec) {
        return vec * scalar;  // Reuse the member operator*
    }

    // 3. Cross product (u*v) - only for 3D vectors
    MathVector operator*(const MathVector & other) const {
        if (length != 3 || other.length != 3) {
            throw std::invalid_argument("Cross product only defined for 3D vectors");
        }

        MathVector result(3);
        result[0] = elements[1] * other.elements[2] - elements[2] * other.elements[1];
        result[1] = elements[2] * other.elements[0] - elements[0] * other.elements[2];
        result[2] = elements[0] * other.elements[1] - elements[1] * other.elements[0];
        return result;
        
    }

};


// Example usage
void q5_example_usage() {
	// i. Default constructor taking only vector size
	MathVector v1(3);

	// ii. Constructor with length and array initialization
	double arr[] = { 1.0, 2.0, 3.0 };
	MathVector v2(3, arr);

	// iii. Copy constructor
	MathVector v3(v2);
}


/*
Using dynamic memory allocation could cause trouble. 
For example, memory leaks (when memory is not deallocated after use) or dangling pointers 
(when a pointer points to a memory location that has been deallocated). Both are serious 
issues which need not be considered when using the std::vector class.

One solution to avoid these issues is to use smart pointers, which automate the deallocation
of memory when it is no longer needed. e.g. std::unique_ptr works by ensuring that the memory
is deallocated when the pointer goes out of scope.
Alternatively, methods for deep copying and proper deletion have to be carefully implemented.
*/