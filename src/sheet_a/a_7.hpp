/*
Question 7



class BernoulliDistributionA
 {
 float p;
 public:
 BernoulliDistributionA(float _p):
 p(_p) {};
 float getProbability() const{
 return p;
 }
 };

 class BernoulliDistributionB
 {
 public:
 BernoulliDistributionB(float _p):
 p(_p) {};
 float p;
 };




a) BernoulliDistributionA is more verbose than BernoulliDistributionB, but it is more robust.
   This is because the member variable p is private, so it can only be accessed through the getProbability() method.
   For such a simple implementation it may be worth considering the second version, but only if there is benefit to
   be gained from minor performance improvements due to one less function call (unlikely).
   In general, it is better practise to use version A.

b)  
	 i. void fn_i(BernoulliDistributionA &b);
		b is a BernoulliDistributionA object.
		Object b is passed by non-const reference, so will reflect any modifications the function makes to it.

	 ii. void fn_ii(BernoulliDistributionA *&b);
		b is a pointer to a BernoulliDistributionA object.
	    Object b is also passed by reference.
		So the function is able to modify the original pointer b itself, and hence also the object it points to.
		This is the most flexible option! Perhaps also the most dangerous due to pointer manipulation.

	 iii. void fn_iii(const BernoulliDistributionB& b);
		This is similar to i, but read-only. 
		The object b is passed by const reference, so the function cannot modify it (if it tries, error).

	 iv. void fn_iv(BernoulliDistributionB &b);
		Exactly the same as i, but with the other class implementation.

	 v. void fn_v(BernoulliDistributionB b);
		Similar to iv, but the object is passed by value.
		So the function will create a copy of the object, and the original object will not change.

*/


