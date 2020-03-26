// #include <cassert>
#include <iostream>
// #include <vector>
// #include <algorithm>

#include <string>
#include "Exam_database.h"
#include "cmpt_error.h"

using namespace std;

    // int comp_name(const string& name1, const string& name2){
    //     if(name1.compare(name2) < 0){
    //         return -1;
    //     }
    //     else if(name1.compare(name2) > 0){
    //         return 1;
    //     }
    //     return 0;
    // }

int main(){
	Exam_database li;

	li.add_exam("a", 4);
    li.add_exam("c", 2);
    li.add_exam("b", 5);
    li.add_exam("e", 3);
    li.add_exam("d", 1);

    // li.add_exam("a b", 75);
 //    li.add_exam("a", 50);
    // li.add_exam("b", 100);
    // li.add_exam("c", 25);
    // li.add_exam("wer", 0);

    // li.remove_exam("a");
    // li.remove_exam("c");

    // li.remove_exam("a");
    // li.remove_exam("a");
    // li.remove_exam("b");
    // li.remove_exam("c");
    // li.remove_exam("d");
    // li.remove_exam("e");
    
	li.print_by_name();
    cout << "-----------" << endl;
    li.print_by_name_rev();
    cout << "-----------" << endl;
    li.print_by_score_ascending();
    cout << "-----------" << endl;
    li.print_by_score_descending();
}