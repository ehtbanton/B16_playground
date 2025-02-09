/*
Question 9

a) Class hierarchy is basic. Bar is a child of Foo.

b)	It should be beared in mind that Foo.g() is virtual, but Foo.f() is not. Virtual functions can be overwriten in child classes.

	All calls to the foo object in main will call the Foo version of the f and g methods, as the object is of type Foo (and has no 
	access to, nor interest in, the Bar version of the methods).

	For doit1(bar), the object is passed by value. But methods f and g expect a (smaller) foo object, so only this part of the object
	is passed to the method (object slicing). So the function will call the Foo version of the f and g methods.

	For doit2(bar), the object is passed by reference, so all of the object is passed to the method. This is simple now: the doit2(bar)
	function calls Foo::f() (the non-virtual function cannot be overwritten by Bar) and Bar::g() (the virtual function is overwritten).

	So the output will be:
		Foo::f()
		Foo::g()
		Foo::f()
		Foo::g()
		Foo::f()
		Foo::g()
		Foo::f()
		Bar::g()

*/



#include <iostream>
class Foo {
public:
	void f() { 
		std::cout << "Foo::f()" << std::endl; 
	}
	virtual void g() {
		std::cout << "Foo::g()" << std::endl;
	}
};
class Bar : public Foo {
public:
	void f() { 
		std::cout << "Bar::f()" << std::endl; 
	}
	virtual void g() {
		std::cout << "Bar::g()" << std::endl;
	}
};
void doit1(Foo f) {
	f.f();
	f.g();
}
void doit2(Foo& f) {
	f.f();
	f.g();
}
int q9_main() {
	Foo foo;
	Bar bar;
	doit1(foo);
	doit1(bar);
	doit2(foo);
	doit2(bar);
	return 0;
}