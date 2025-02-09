
/*
Question 10

a) The class hierarchy is as follows:
	X
	|
	|- Y
	|
	|- Z

b)	First, 3 Z objects are created with values 2.5, 3.0 and 10.0. 
	Then, a Y object is created with the first two Z objects as arguments.
    Then, another Y object is created with the previous Y object and the third Z object as arguments. 
	
	The PrintValue() method is called for a. While PrintValue from X is used, the local implementation 
	of eval() in Z is used, because of the virtual keyword in the base class. This returns -v = -2.5.

	Then, the PrintValue() method is called for d. The local implementation of eval() in Y is used, so 
	now the eval() method in Z is called twice. This returns -2.5 * -3.0 = 7.5.

	Then, the PrintValue() method is called for e. The local implementation of eval() in Y is used, but 
	now one of the arguments is another Y object. This means that in total, the eval() method in Z is called 
	three times. This returns -2.5 * -3.0 * -10.0 = -75.0.

*/





#include <iostream>
using namespace std;

class X {
public:
	virtual double Eval() { 
		return 1.0; 
	}
	void PrintValue() { 
		cout << Eval() << endl; 
	}
};

class Y : public X {
public:
	Y(X& x1, X& x2) :arg1(x1), arg2(x2) {}
	double Eval() { 
		return arg1.Eval()* arg2.Eval(); 
	}
private:
	X& arg1;
	X& arg2;
};

class Z : public X {
public:
	Z(double v) : val(v) {}
	double Eval() { 
		return-val; 
	}
private:
	double val;
};


void q10_example_main() {
	Z a(2.5), b(3.0), c(10.0);
	Y d(a, b);
	Y e(d, c);
	a.PrintValue();
	d.PrintValue();
	e.PrintValue();
}





///////////////////////////////////////////////////////////////////////////////////////////////

#include <cmath>

class Calculation {
public:
	virtual double Eval() = 0;
	void PrintValue() {
		cout << Eval() << endl;
	}
};

class Sum : public Calculation {
public:
	Sum(Calculation& calc_1, Calculation& calc_2) :arg1(calc_1), arg2(calc_2) {}
	double Eval() {
		return arg1.Eval() + arg2.Eval();
	}
private:
	Calculation& arg1;
	Calculation& arg2;
};

class Tan : public Calculation {
public:
	Tan(double v) : val(v) {}
	double Eval() {
		return tan(val);
	}
private:
	double val;
};





void q10_sum_tan_main() {
	Tan a(1.0), b(2.0), c(3.0);
	Sum d(a, b);
	Sum e(d, c);
	a.PrintValue();
	d.PrintValue();
	e.PrintValue();
}