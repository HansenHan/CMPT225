// #include "cmpt_error.h"
#include <iostream>
#include <vector>
#include <cassert>
#include <fstream> 
#include <sstream> 

using namespace std;
 int main()
 {
 	// float x;
 	// cin >> x;
 	// cin >> y;
 	// if(x<10 && x>-10 && y<10 && y>-10 ){
 	// 	float sum = x + y;
 	// 	cout << "sum is "<< sum << endl;
  //   }
  //   else{
  //   	cout << "this is not a number." << endl;
  //   }

    // string input;
    // cin >> input;
    // stringstream ss;
    // ss << input;
    float number;
    cin >> number;
    // char test = input[0];
    // ss >> number;
    // ss >> test;
    if(cin.fail()){
    	cout << "error" << endl;
    }
    // cout << number << endl;
  	return 0;
 } 	
