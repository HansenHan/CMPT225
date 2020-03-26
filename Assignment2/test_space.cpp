// int is_space()
#include <cassert>
#include <iostream>

#include <string>
// #include "Exam_database.h"
#include "cmpt_error.h"
using namespace std;

int is_space(string& name){
	int state = 0;
	for(int i = 0; i < name.size(); i++){
		if(name[i] == ' '){
			state = 1;
		}
	}
	return state;
}
// char a = 'x';
// char b = "x";
int main(){
	string s = "abc";
	if(is_space(s) == 0){
		cout << "no space" << endl;
	}
	else{
		cout << "have space" << endl;
	}
}