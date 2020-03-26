// recursion.cpp

#include "cmpt_trace.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ////////////////////////////////////////////////////////////////////////////////
// //
// // Trace is a helper class that is meant to be used in functions as a simple
// // debugging aid. When you create a Trace object at the start of a function
// // (see the fib function below), it will cause a message to be printed when
// // the function is called, and also when the function ends. The messages are
// // indented according to how many times the function has been called, and the
// // results can be visually striking, and useful (i.e. you get an idea of stack
// // usage).
// //
// ////////////////////////////////////////////////////////////////////////////////

// class Trace {
// private:
//     string message;
//     static int indent;  // indent is static, and so one copy is shared by all
//                         // Trace objects
// public:
//     Trace(const string& msg) 
//     : message(msg)
//     {
//         cout << string(indent, ' ') << message << " ...\n";
//         indent += 3;
//     }

//     ~Trace() {
//         indent -= 3;
//         cout << string(indent, ' ') << " ... " << message << "\n";
//     }
// };

// // static variables are initialized outside their class
// int Trace::indent = 0;

////////////////////////////////////////////////////////////////////////////////

// Pre-condition:
//    n >= 0
// Post-condition:
//    returns the nth Fibonacci number, i.e.
//
//    1 1 2 3 5 8 13 ...
//
//    The 0th is 1, 1st is 1, the 2nd is 2, the 3rd is 3, etc.
//
// Note:
//    This is extremely inefficient! The two recursive calls in the else case
//    essentially cause this to do an exponential amount of work. In contrast,
//    a straightforward loop implementation without any recursion can easily
//    be made to do only about n additions.
//
//    But what it lacks in performance, it makes up for in elegance. The code
//    is short and easy to read, and is essentially a C++ transcription of the 
//    standard mathematical definition. So it's easy to believe that this works 
//    correctly.
int fib(int n) {
	cmpt::Trace trace("fib(" + to_string(n) + ")");  // comment this out to turn off tracing
	if (n == 0) return 1;       // base case 1
	if (n == 1) return 1;       // base case 2
	return fib(n-1) + fib(n-2); // recursive case
}

// Pre-condition:
//    0 <= begin
// Post-condition:
//    prints v[begin], ..., v[n-1] to cout (where n == v.size())
void print(const vector<int> v, int begin) {
	cmpt::Trace trace("print(v, " + to_string(begin) + ")");  // comment this out to turn off tracing
	if (begin < v.size()) {
		cout << v[begin] << " ";
		print(v, begin+1);
	}
}

//
// An alternative way to write this function that makes the cases explicit ....
//
// void print(const vector<int> v, int begin) {
// 	cmpt::Trace trace("print(v, " + to_string(begin) + ")");  // comment this out to turn off tracing
// 	if (begin >= v.size()) {
// 		// do nothing
// 	} else {
// 		cout << v[begin] << " ";
// 		print(v, begin+1);
// 	}
// }

// Pre-condition:
//    none
// Post-condition:
//    prints v to cout (followed by a newline)
void print(const vector<int> v) {
	print(v, 0);
	cout << "\n";
}

int main() {
	// cout << fib(10) << "\n";

	vector<int> a = {1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0};
	print(a);
}
