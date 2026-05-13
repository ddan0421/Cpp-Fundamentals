#include <iostream>
#include <string>

using namespace std;

/*
Function template: a pattern for a function that can work with many data types
When written, parameters are left for the data types
When called, compiler generates code for specific data types in function call 

template <typename T>
T times10(T num)
{
    return 10 * num;
}

- typename T is template prefix and typename is generic data type
- T is type parameter

*/

// Call a template function in the usual manner:
/*
In the background it essentially writes:
// For ival
int times10(int num) {
    return 10 * num;
}

// For dval
double times10(double num) {
    return 10 * num;
}
*/
int ival = 3;
double dval = 2.55;
template <typename T>
T times10(T num)
{
    return 10 * num;
}
int main(){
    cout << times10(ival) << endl; // displays 30 
    cout << times10(dval) << endl; // displays 25.5
    return 0;
}



/*
Function templates can be overloaded Each template must have a unique parameter list
	template <typename T>
	T sumAll(T num) ...

	template <typename T1, typename T2>
	T1 sumall(T1 num1, T2 num2) ...


All data types specified in template prefix must be used in template definition
Function calls must pass parameters for all data types specified in the template prefix
Like regular functions, function templates must be defined before being called


A function template is a pattern
No actual code is generated until the function named in the template is called
A function template uses no memory 
When passing a class object to a function template, ensure that all operators in the template are defined or overloaded in the class definition

*/


/*
Where to start when defining templates
Templates are often appropriate for multiple functions that perform the same task with different parameter data types
Develop function using usual data types first, then convert to a template:
add template prefix
convert data type names in the function to a type parameter (i.e., a T type) in the template

*/


// Class Templates
/*
Classes can also be represented by templates.  When a class object is created, type information is supplied to define the type of data members of the class.
Unlike functions, classes are instantiated by supplying the type name (int, double, string, etc.) at object definition


template <typename T>
class grade
{	
	  private:
			T score;
		 public:
			grade(T);
			void setGrade(T);
			T getGrade()
};

Pass type information to class template when defining objects:
	grade<int> testList[20];
	grade<double> quizList[20];
Use as ordinary objects once defined




Class Templates and Inheritance
Class templates can inherit from other class templates:
template <typename T>
class Rectangle
	{ ... };

template <typename T>
class Square : public Rectangle<T>
	{ ... };
Must use type parameter T everywhere base class name is used in derived class

*/








