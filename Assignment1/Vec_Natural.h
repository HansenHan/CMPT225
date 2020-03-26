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
    vector<int> vec;

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
        vec.push_back(0);
        //number(0);
        //number{0};.
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
                vec.push_back(n % 10);
                n = (n - (n % 10)) / 10;
            }
        }
        else{
            cmpt::error("n cannot smaller than 0");
        }
        this->vec_reverse(); //Helping Function!
    }

    void vec_reverse(){
        for(int i = 0; i < (vec.size()/2); i++){
            int tmp = vec[i];
            vec[i] = vec[vec.size()-i-1];
            vec[vec.size()-i-1] = tmp;
        }
    }


    // Pre-condition:
    //    s consists of 1, or more, digit characters
    //    (call cmpt:error if this is not satisfied)
    // Post-condition:
    //    constructs a Natural representation of s so that
    //    this->to_string() == s
    Natural(const string& s) {
        // ...
        if(s != ""){
            for(int i = 0; i < s.size(); i++){
                vec.push_back( (s[i] - 48) );
            }
        }
        else{
            cmpt::error("s is empty");
        }
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    constructs a new Natural whose value is the same as other
    Natural(const Natural& other) {  // copy constructor
        // ...
        vec.assign( other.vec.begin(), other.vec.end() );
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    returns the number of digits in this Natural
    int num_digits() const {
        return vec.size();
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    returns true if this Natural is 0, and false otherwise
    bool is_zero() const {
        // ...
        if(vec.size() == 0){
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
        std::vector<int> num_a(this->vec);
        std::vector<int> num_b(a.vec);
        std::vector<int> sum;
        if(num_a.size() < num_b.size()){
            std::vector<int> tmp;
            tmp = num_b;
            num_b = num_a;
            num_a = tmp; 
        }
        reverse(num_a.begin(), num_a.end());
        reverse(num_b.begin(), num_b.end());
        int ele = 0;
        int shi = 0;
        for(int i = 0; i < num_b.size(); i++){
            ele = shi + num_a[i] + num_b[i];
            sum.push_back(ele % 10);
            shi = (ele - (ele % 10)) / 10;
        }
        if(num_b.size() == num_a.size() && shi > 0){
            sum.push_back(shi);
        }
        else if(num_b.size() < num_a.size()){
            for(int j = num_b.size(); j < num_a.size(); j++){
                ele = shi + num_a[j];
                sum.push_back(ele % 10);
                shi = (ele - (ele % 10)) / 10;
            }
            if(shi > 0){
                sum.push_back(shi);
                shi = 0;
            }
        }
        reverse(sum.begin(), sum.end());
        Natural result;
        result.vec = sum;
        return result;
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    returns a new Natural equal to the product of a and this Natural
    Natural operator*(const Natural& a) const {
        // ...
        std::vector<int> num_a(this->vec);
        std::vector<int> num_b(a.vec);
        Natural ti;
        ti.vec.clear();
        Natural pp;
        pp.vec.clear();
        if(num_a.size() < num_b.size()){
            std::vector<int> tmp;
            tmp = num_b;
            num_b = num_a;
            num_a = tmp; 
        }
        reverse(num_a.begin(), num_a.end());
        reverse(num_b.begin(), num_b.end());
        int ele = 0;
        int shi = 0;
        for(int i = 0; i < num_b.size(); i++){
            for(int j= 0; j < num_a.size(); j++){
                ele = shi + num_b[i] * num_a[j];
                ti.vec.push_back(ele % 10);
                shi = (ele - (ele % 10)) / 10;
            }
            if(shi > 0){
                ti.vec.push_back(shi);
                shi = 0;
            }
            ti.vec_reverse();
            for(int c = 0; c < i; c++){
                ti.vec.push_back(0);
            }
            //..............
            // pp.operator+(ti);
        // pp = pp + ti;
        std::vector<int> num_a(pp.vec);
        std::vector<int> num_b(ti.vec);
        std::vector<int> sum;
        if(num_a.size() < num_b.size()){
            std::vector<int> tmp;
            tmp = num_b;
            num_b = num_a;
            num_a = tmp; 
        }
        reverse(num_a.begin(), num_a.end());
        reverse(num_b.begin(), num_b.end());
        int ele = 0;
        int shi = 0;
        for(int i = 0; i < num_b.size(); i++){
            ele = shi + num_a[i] + num_b[i];
            sum.push_back(ele % 10);
            shi = (ele - (ele % 10)) / 10;
        }
        if(num_b.size() == num_a.size() && shi > 0){
            sum.push_back(shi);
        }
        else if(num_b.size() < num_a.size()){
            for(int j = num_b.size(); j < num_a.size(); j++){
                ele = shi + num_a[j];
                sum.push_back(ele % 10);
                shi = (ele - (ele % 10)) / 10;
            }
            if(shi > 0){
                sum.push_back(shi);
                shi = 0;
            }
        }
        reverse(sum.begin(), sum.end());
        pp.vec = sum;

            // ..............
            cout << pp.vec.size() << endl;
            for(int w = 0; w < pp.vec.size(); w++){
                cout << pp.vec[w];
            }
            cout << endl;

            ti.vec.clear();
        }
        return pp;
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    returns a string representation of this Natural
    string to_string() const {
        // // ...
        string str;
        char ch;
        for(int p = 0; p < this->vec.size(); p++){
            ch = vec[p] + 48;
            str = str + ch;
        }
        return str;
    }


}; // class Natural

//
// the following methods are provided for convenience
//

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