// test

#include "cmpt_error.h"
#include <iostream>
#include <vector>
#include <cassert>
// #include <fstream> 
#include <sstream> 

using namespace std;

int main(){
	// string s = "george";
	// int h = 0;
	// for(int i = 0; i < s.size(); i++){
	//     h = h + s[i];
	// }
	// cout << h << endl;

	// string str1, str2;
	// while(1){
	// 	cout << "enter your code: ";
	//     cin >> str1;
	//     if(str1 == "end"){
	//     	return 0;
	//     }
	//     cin >> str2;
	//     cout << str2 << endl;
	//     cout << str1 << endl;
	// }


	// string str1, str2, name;
	// str1 = "maindict";
	// str2 = ".txt";
	// name = str1 + str2;
 //    ofstream mainfile (name);
 //    int num = 0;   //creat main dic 
 //    for(int i = 0; i < 12; i++){
 //    	for(int j = 0; j < 12; j++){
 //    		for(int k = 0; k < 12; k++){
 //    			char aa = i+97;
 //    			char bb = j+97;
 //   	    		char cc = k+97;
 //   		     	num++;
 //   		     	mainfile << aa << bb << cc << endl;
 //   			    // mainf << endl;
 //   		    }
 //   	    }
 //    }


    // int* arr = new int[100];
    // for(int i = 0; i < 100; i++){
    // 	arr[i] = i + 1;
    // }
    // cout << sizeof(arr) << endl;
    // cout << arr[49] << endl;


    // string s = "1234"; //string to int
    // stringstream tmp; //stringstream tmp(s);
    // tmp << s;
    // int a = 0;
    // tmp >> a;
    // cout << a << endl;

    // int aa = 4321; //int to string
    // stringstream ss;
    // ss << aa;
    // string str = ss.str();
    // cout << str << endl;


    // fstream tmpfile ("addedwords.txt", ios::out);
    // tmpfile << "red" << endl;
    // tmpfile.close();


    // string str1, str2;
    // str1 = "ab";
    // str2 = "cd";
    // string word = str1 + str2;
    // cout << word << endl;



    // float ii =  3.14;
    // string ss = to_string(ii);
    // cout << ss << endl;


    // enum MealType { NO_PREF, REGULAR, LOW_FAT, VEGETARIAN };
    // struct Passenger {
    //     string name;
    //     MealType mealPref;
    //     bool isFreqFlyer;
    //     string freqFlyerNo;
    // };
    // Passenger p1;
    // p1.name = "hansen";
    // Passenger p2 = p1;
    // cout << p2.name << endl;
    // p1.name = "black";
    // cout << p2.name << endl; //not changed
    // Passenger *p3 = new Passenger; //initialized
    // p3->name = "YC";
    // Passenger *p4 = p3;
    // cout << p4->name << endl;
    // p3->name = "CY";
    // cout << p4->name << endl; //changed


    // vector <int> intvec;
    // cout << intvec.size() << endl;
    // intvec.push_back(1);
    // cout << intvec.size() << endl;

    cout << sizeof(int) << endl;
}