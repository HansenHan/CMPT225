#include "cmpt_error.h"  // don't add any more #includes
#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Vec_Natural.h"

using namespace std;


int main()
{
    //...
    Natural first(56);
    Natural second(71);
    Natural sum = first.operator+(second);
    cout << sum << endl;

    int p = '1';
    cout << p << endl;
}


 //   999
 //    99
 //  8991
 // 8991
 // 98901