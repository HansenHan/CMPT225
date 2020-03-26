// intvec.cpp

//
// The following is an implementation of the Intvec class discussed in the
// lectures. It's good practice for basic C++, and arrays.
// 
// Things to try:
//
// 1. add a public copy constructor so you can write code like this:
//
//       Intvec a;
//       // ... add some elements to a ...
//       Intvec a(b);
//       // now a is a copy of b
//
// 2. add a public method called reverse() that reverses the order of the
//    elements of an Intvec
//
// 3. add a public method called shrink() that will, if necessary, re-sizes
//    the underlying array so the size and capacity are the same (i.e. load
//    factor is 100%)
//
// 4. add functions that let you use == and != to test if two Intvecs are the
//    same or different; two Intvecs are the same if they have the same
//    elements in the same order
//
// 5. look up to use operator[] in a class so that you can use []-notation to
//    access values of an Intvec, e.g.:
//
//      Intvec v;
//      v.append(5);
//      v[0] = 3;
//      cout << v[0]; // prints 3
//

#include "cmpt_error.h"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Intvec {
private:
    int* arr;
    int cap; // capacity of Intvec (i.e. size of arr)
    int sz;  // size of Intvec

    void resize() {
        // create a new array twice as big as the current one
        cap = 2 * cap;
        int* newarr = new int[cap];
        // copy old arr values into newarr
        for(int i = 0; i < sz; i++) {
            newarr[i] = arr[i];
        }
        // get rid of the old array
        delete[] arr;
        // make arr point to the new array
        arr = newarr;
    }

public:

    // default constructor; creates a new Intvec of size 10, capacity 10
    
    Intvec() 
    : arr(new int[10]), cap(10), sz(0)  // initialization list
    { }

    ~Intvec() {  // destructor
        delete[] arr;
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    returns current size of this Intvec
    int size() const { return sz; }

    // Pre-condition:
    //    none
    // Post-condition:
    //    returns current capacity of this Intvec
    int capacity() const { return cap; }

    // Pre-condition:
    //    none
    // Post-condition:
    //    returns current load factor of this Intvec (size / capacity)
    double load_factor() const { return double(size()) / capacity(); }

    // Pre-condition:
    //    none
    // Post-condition:
    //    increases the size of this Intvec by 1 and then sets last element to n
    void append(int n) {
        // re-size underlying array if necessary
        if (sz == cap) resize();
        arr[sz] = n;
        sz++;
    }

    void sort() {
        std::sort(arr, arr + sz);   
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    removes all elements from this vector (so size is 0);
    // Note:
    //    the capacity doesn't change
    void clear() {
        sz = 0;
    }

    // Pre-condition:
    //    0 <= i < size()
    // Post-condition:
    //    sets the int at index location i to val
    void set(int i, int val) {
        if (i < 0 || i >= sz) cmpt::error("set: index out of range");
        arr[i] = val;
    }

    // Pre-condition:
    //    0 <= i < size()
    // Post-condition:
    //    returns the int at index location i of this Intvec
    int get(int i) const {
        if (i < 0 || i >= sz) cmpt::error("get: index out of range");
        return arr[i];
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    returns a string representation of this Intvec
    string to_string() const {
        if (size() == 0) {
            return "{}";
        } else if (size() == 1) {
            return "{" + std::to_string(arr[0]) + "}";
        } else {
            string result = "{" + std::to_string(arr[0]);
            for(int i = 1; i < size(); i++) {
                result += "," + std::to_string(arr[i]);
            }
            return result + "}";
        }
    }

}; // class Intvec

ostream& operator<<(ostream& os, const Intvec& v) {
    os << v.to_string();
    return os;
}

// helper function for checking contens of an Intvec
void check(const Intvec& v) {
    cout << v << "\n"
         << "size=" << v.size() << ", "
         << "cap=" << v.capacity() << ", "
         << "load factor=" << (100 * v.load_factor()) << "%"
         << "\n\n";
}

void test1() {
    Intvec v;
    check(v);
    v.append(1);
    check(v);
    v.append(2);
    check(v);
    v.append(3);
    check(v);
    for(int i = 4; i <= 100; i++) {
        v.append(i);
        check(v);
    }

    // sum the values
    int sum = 0;
    for(int i = 0; i < v.size(); i++) {
        sum += v.get(i);
    }
    cout << "sum = " << sum << "\n";

    // set all values to 0
    for(int i = 0; i < v.size(); i++) {
        v.set(i, 0);
    }
    check(v);

    v.clear();
    check(v);   
}

void test2() {
    Intvec v;
    v.append(5);
    v.append(4);
    v.append(1);
    v.append(6);
    v.append(2);
    v.append(3);
    check(v);
    v.sort();
    check(v);
}

int main() {
    test1();
    test2();
}
