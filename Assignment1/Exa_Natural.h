
// Natural.h

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : shengzhuo li
// St.# : 301326746
// Email: sla297@sfu.ca
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
    std::vector<int> numbers;
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
        numbers = { 0 };
    }
    
    // Pre-condition:
    //    n >= 0
    //    (call cmpt:error if this is not satisfied)
    // Post-condition:
    //    constructs a new Natural with value n
    Natural(int n) {
        
        if (n < 0) {
         //call cpmt error
            cmpt::error("error");
         }
        while (n) {
            numbers.push_back(n % 10);
            n /= 10;
        }
        reverse_number();
    }
    
    // Pre-condition:
    //    s consists of 1, or more, digit characters
    //    (call cmpt:error if this is not satisfied)
    // Post-condition:
    //    constructs a Natural representation of s so that
    //    this->to_string() == s
    Natural(const string& s) {
        if (s.empty()) {
            cmpt::error("error");
        }
        for (int i = 0; i < s.size(); i++) {
            //cout << s[i] << endl;
            numbers.push_back(s[i] -48);
        }
    }

    //constructor using vector
    Natural(const std::vector<int> vector) {
        for (int i=0; i<vector.size(); i++)
            numbers.push_back(vector[i]);
    }
    
    // Pre-condition:
    //    none
    // Post-condition:
    //    constructs a new Natural whose value is the same as other
    Natural(const Natural& other) {  // copy constructor
        
        //copy vector, using <algorithm>
        numbers.assign(other.numbers.begin(), other.numbers.end());
    }
    
    // Pre-condition:
    //    none
    // Post-condition:
    //    returns the number of digits in this Natural
    int num_digits() const {
        return numbers.size();
    }
    
    // Pre-condition:
    //    none
    // Post-condition:
    //    returns true if this Natural is 0, and false otherwise
    bool is_zero() const {
        if (numbers.size() == 0)
            return true;
        else
            return false;
    }
    
    // Pre-condition:
    //    none
    // Post-condition:
    //    returns a new Natural equal to the sum of a and this Natural
    Natural operator+(const Natural& a) const {
        //Idea: reverse vectors prepare for adding;
        //then add element by elment;
        //reverse back at last;
        std::vector<int> sum;
        int rest = 0;
        std::vector<int> n_rev;
        n_rev.resize(numbers.size());
        std::reverse_copy(numbers.begin(), numbers.end(), n_rev.begin());
        
        std::vector<int> a_rev;
        a_rev.resize(a.num_digits());
        std::reverse_copy(a.numbers.begin(), a.numbers.end(), a_rev.begin());
        //if this number is the smaller one
        if (numbers.size() <= a.num_digits()) {
            for (int i = 0; i < numbers.size(); i++) {
                int c = n_rev[i] + a_rev[i] + rest;
                sum.push_back(c % 10);
                rest = c / 10;
            }
            
            for (int i = numbers.size(); i < a.num_digits(); i++) {
                int c = a_rev[i] + rest;
                sum.push_back(c % 10);
                rest = c / 10;
            }
            while (rest > 0) {
                sum.push_back(rest % 10);
                rest /= 10;
            }
        }
        
        //if this.number has more digits than Natural 'a', same logic as above
        else if (numbers.size() > a.num_digits()) {
            for (int i = 0; i < a.num_digits(); i++) {
                int c = a_rev[i] + n_rev[i] + rest;
                sum.push_back(c % 10);
                rest = c / 10;
            }
            
            for (int i = a.num_digits(); i < numbers.size(); i++) {
                int c = n_rev[i] + rest;
                sum.push_back(c % 10);
                rest = c / 10;
            }
            while (rest > 0) {
                sum.push_back(rest % 10);
                rest /= 10;
            }
        }

        //covert sum to string and reverse back
        std::string actual;
        char ch;
        for (int i = sum.size()-1; i>=0 ; i--) {
            ch = sum[i] + 48;
            actual += ch;
        }
        return Natural(actual);
    }
    
    // Pre-condition:
    //    none
    // Post-condition:
    //    returns a new Natural equal to the product of a and this Natural
    Natural operator*(const Natural& a) const {
        //reverse two vector first,
        std::vector<std::vector<int>> all_sum;
        std::vector<int> result;
        
        std::vector<int> n_rev;
        n_rev.resize(numbers.size());
        std::reverse_copy(numbers.begin(), numbers.end(), n_rev.begin());
        
        std::vector<int> a_rev;
        a_rev.resize(a.num_digits());
        std::reverse_copy(a.numbers.begin(), a.numbers.end(), a_rev.begin());
        
        //then multiply
        if (numbers.size() <= a.num_digits()) {
            for (int i = 0; i < numbers.size(); i++) {
                result.clear();
                //add zeros to the end of digits
                int zero = i;
                while(zero>0){
                    result.push_back(0);
                    zero--;
                }

                
                int rest = 0;
                for (int j = 0; j < a.num_digits(); j++) {
                    int c = n_rev[i]*a_rev[j] + rest;
                    result.push_back(c % 10);
                    rest = c / 10;
                }
                while(rest >0){
                    result.push_back(rest % 10);
                    rest /= 10;
                }
                all_sum.push_back(result);
            }
        }
        else if (numbers.size() > a.num_digits()) {
            for (int i = 0; i < a.num_digits(); i++) {
                result.clear();
                //add zeros to the end of digits
                int zero = i;
                while(zero>0){
                    result.push_back(0);
                    zero--;
                }
                
                int rest = 0;
                for (int j = 0; j < numbers.size(); j++) {
                    int c = n_rev[j]*a_rev[i] + rest;
                    result.push_back(c % 10);
                    rest = c / 10;
                }
                while(rest >0){
                    result.push_back(rest % 10);
                    rest /= 10;
                }
                all_sum.push_back(result);
            }
        }
        Natural n;
        //calculate all sum
        for(int i = 0; i < all_sum.size(); i++){
            Natural temp(all_sum[i]);
            temp.reverse_number();
            n = n+temp;
        }
        //n.reverse_number();
        return n;
    }
    
    // Pre-condition:
    //    none
    // Post-condition:
    //    returns a string representation of this Natural
    string to_string() const {
        std::string actual;
        char ch;
        for (int i = 0; i < numbers.size(); i++) {
            ch = numbers[i]+48;
            actual += ch;
        }
        return actual;
    }
    
    //reverse vector
    void reverse_number()
    {
       std::reverse(numbers.begin(),numbers.end());
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
