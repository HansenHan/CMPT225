// Natural.h

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : <put your full name here!>
// St.# : <put your full SFU student number here>
// Email: <put your SFU email address here>
//
//
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations in the comments with enough detail
// so that someone can see the exact source and extent of the borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have not
// seen solutions from other students, tutors, websites, books, etc.
//
/////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////
//
// - Implement each of the following constructors and methods.
//
// - The details of the implementation of Natural are up to you.
//
// - **Do not** change the signatures of any of the constructors or methods
//   that are given (if you do, then the testing program will give you 0)
//
// - **Do not** add any more #includes.
//
// - You can add member initialization lists to the given constructors if you
//   like.
//
//  - You can add any other useful constructors, methods, or functions. Keep
//    all the code in this one file.
//
/////////////////////////////////////////////////////////////////////////

#include "cmpt_error.h"  // don't add any more #includes
#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Natural {
private:

    //
    // ... implementation details go here ...
    //
    int arr[3000];
    // int cap;
    // int sz;

    // void resize(){
    //     int pos = 0;
    //     while( arr[pos] == 0 ){
    //         pos++;
    //     }
    //     int* newarr = new int[3000 - pos];
    //     for(int i = 0; i < (3000 - pos); i++){
    //         newarr[i] = arr[i];
    //     }
    //     delete[] arr;
    //     arr = newarr;
    // }

    //
    // ... you can also add other helper methods here ...
    //

public:
    // Pre-condition:
    //    none
    // Post-condition:
    //    constructs a new Natural with value 0
    Natural() {  // default constructor
        // ...
        //arr[3000];
        for(int i = 0; i < 3000; i++){
            arr[i] = 0;
        }
        //number(0);
        //number{0};
    }

    // Pre-condition:
    //    n >= 0
    //    (call cmpt:error if this is not satisfied)
    // Post-condition:
    //    constructs a new Natural with value n
    Natural(int n) {
        // ...
        if(n >= 0){
            while(n >= 1){
                int tem = 2999;
                arr[tem] = (n % 10);
                n = (n - (n % 10)) / 10;
                tem--;
            }
        }
        else{
            cmpt::error("n cannot smaller than 0");
        }
    }

    // void resize(){
    //     int pos = 0;
    //     while( arr[pos] == 0 ){
    //         pos++;
    //     }
    //     int* newarr = new int[3000 - pos];
    //     for(int i = 0; i < (3000 - pos); i++){
    //         newarr[i] = arr[i];
    //     }
    //     delete[] arr;
    //     arr = newarr;
    // }

    // Pre-condition:
    //    s consists of 1, or more, digit characters
    //    (call cmpt:error if this is not satisfied)
    // Post-condition:
    //    constructs a Natural representation of s so that
    //    this->to_string() == s
    // Natural(const string& s) {
    //     // ...
    //     if(s != ""){
    //         for(int i = 0; i < s.size(), i++){
    //             arr[3000 - s.size() + i] = ( (s[i] - 48) );
    //         }
    //     }
    //     else{
    //         cmpt::error("s is empty");
    //     }
    // }

    // Pre-condition:
    //    none
    // Post-condition:
    //    constructs a new Natural whose value is the same as other
    // Natural(const Natural& other) {  // copy constructor
    //     // ...
    //     //number = other.number;
    //     //vec.assign( other.begin(), other.end() );
    //     newarr[other.size()]
    //     for(int i = 0; i < other.arr.size(); i++){
    //         newarr[i] = other.arr[i];
    //     }
    //     delete[] arr;
    //     arr = newarr;
    // }

    // Pre-condition:
    //    none
    // Post-condition:
    //    returns the number of digits in this Natural
    int num_digits() const {
        // // ...
        // int dig = 1;
        // double tem = number;
        // // if(number < 0){
        // //     tem = number * (-1);
        // // }
        // while(tem * 0.1 >= 1){
        //     tem = tem * 0.1;
        //     dig++;
        // }
        // return dig;
        int pos = 0;
        while( arr[pos] == 0 ){
            pos++;
        }
        int num = 2999 - pos;
        return num;
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    returns true if this Natural is 0, and false otherwise
    bool is_zero() const {
        // ...
        int pos = 0;
        while( pos < 3000 && arr[pos] == 0 ){
            pos++;
        }
        if(pos == 0){
            return true;
        }
        else{
            return false;
        }
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    returns a new Natural equal to the sum of a and this Natural
    Natural operator+(const Natural& a) const {
        // // ...
        // Natural result;
        // result.number = this->number + a.number;
        // return result;

        Natural result;
        // int size_a = arr.size();
        // int size_b = a.arr.size();

        int size_a =(sizeof(arr)/sizeof(*arr));
        int size_b =(sizeof(a.arr)/sizeof(*a.arr));

        int sum = 0;
        int one = 0;
        int ten = 0;

        if(size_a >= size_b){
            for(int i = (size_a - 1); i >= 0; i--){
                if((i - (size_a - size_b)) >= 0){
                    sum = arr[i] + a.arr[i - (size_a - size_b)];
                    one = sum % 10;
                    result.arr[3000 - size_a + i] = one + ten;
                    ten = (sum - (one))/10;
                }
                else{
                    one = arr[i];
                    result.arr[3000 - size_a + i] = one + ten;
                    ten = 0;
                }
            }
        }

        else{
            for(int i = (size_b - 1); i >= 0; i--){
                if((i - (size_b - size_a)) >= 0){
                    sum = arr[i] + a.arr[i - (size_b - size_a)];
                    one = sum % 10;
                    result.arr[3000 - size_b + i] = one + ten;
                    ten = (sum - (one))/10;
                }
                else{
                    one = arr[i];
                    result.arr[3000 - size_b + i] = one + ten;
                    ten = 0;
                }
            }
        }
        return result;

        
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    returns a new Natural equal to the product of a and this Natural
    // Natural operator*(const Natural& a) const {
    //     // ...
    //     Natural result;
    //     result.number = this->number * a.number;
    //     return result;
    // }

    // // Pre-condition:
    // //    none
    // // Post-condition:
    // //    returns a string representation of this Natural
    string to_string() const {
        // ...
        //return std::to_string(arr);
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


}; // class Natural


// the following methods are provided for convenience


ostream& operator<<(ostream& os, const Natural& b) {
    os << b.to_string();
    return os;
}

bool operator==(const Natural& a, const Natural& b) {
    return a.to_string() == b.to_string();
}

bool operator!=(const Natural& a, const Natural& b) {
    return !(a == b);
}

bool operator==(const Natural& a, const string& b) {
    return a.to_string() == b;
}

bool operator!=(const Natural& a, const string& b) {
    return !(a == b);
}