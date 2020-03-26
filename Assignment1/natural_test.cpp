// natural_test.cpp

#include "Natural_answer.h"
#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "cmpt_error.h"
// ... other #includes ...

// ... other helper functions for testing and development ...



void factorial_test() {
    Natural result{1};
    for(int i = 0; i < 1000; i++) {
        result = result + result * Natural(i);
    }
    cout << result << "\n";
}

void test_mult(const string& sa,
               const string& sb,
               const string& expected)
{
    Natural a(sa), b(sb);
    Natural actual = a.operator*(b);
    cout << a << " * " << b << " == " << actual
         << " (expected " << expected << ")\n";
    // assert(actual.to_string() == expected);
}

int main() {
	// test_mult("0", "0", "0");
	// test_mult("1", "0", "0");
	// test_mult("0", "1", "0");
	// test_mult("1", "1", "1");
	// test_mult("2", "11", "22");
	// test_mult("11", "2", "22");
 //    test_mult("76", "88", "164");
    test_mult("999", "99", "98901");
	
	factorial_test();

}
