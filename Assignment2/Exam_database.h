// Exam_database.h

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : Zelin Han
// St.# : 301309342
// Email: zelinh@sfu.ca
//
//
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations in the comments with enough
// detail so that someone can see the exact source and extent of the
// borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have
// not seen solutions from other students, tutors, websites, books,
// etc.
//
/////////////////////////////////////////////////////////////////////////


#include "cmpt_error.h"
#include <iostream>
#include <string>




using namespace std;

class Exam_database {
private:

    // ... put private variables and methods here ...

    struct Node {
        string name;
        Node* name_pre;
        Node* name_nex;
        int score;
        Node* score_pre;
        Node* score_nex;
    };

    Node* name_head;
    Node* name_tail;
    Node* score_head;
    Node* score_tail;

public:
    // Pre-condition:
    //    none
    // Post-condition:
    //    constructs a new empty Exam_database
    // Note:
    //    you can use an initialization with this constructor
    Exam_database(){
        name_head = nullptr;
        name_tail = nullptr;
        score_head = nullptr;
        score_tail = nullptr;
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    destructs Exam_database, i.e. ensures all memory (or other resources)
    //    owned by this object are properly deleted
    ~Exam_database(){
        while(name_head != nullptr){
            Node* p = name_head;
            name_head = name_head->name_nex;
            delete p;
        }
        // while(score_head != nullptr){
        //     Node* p = score_head;
        //     score_head = score_head->score_nex;
        //     delete p;
        // }
    }

    // Pre-condition:
    //    name is non-empty and contains no spaces
    //    use cmpt::error to throw an exception if this is not satisfied
    // Post-condition:
    //    adds (name, score) to this object; if a pair in the database already
    //    has the name, then its corresponding score is set to score
    void add_exam(const string& name, int score){
        

        // cout << "Test: " << name.find_first_of(" ") << endl;
        string name_tmp = name;
        if(is_space(name_tmp) == 1){
            // delete newnode;
            cmpt::error("name contains spaces!");
            // cout << "name conains spaces!" << endl;
            // return;
        }

        if(name != ""){
            Node* newnode = new Node{name, nullptr, nullptr, score, nullptr, nullptr};
            Node* tmp = name_head;
            
            //empty list:
            if(name_head == nullptr){
                name_head = newnode;
                name_tail = name_head;
                score_head = name_head;
                score_tail = name_head;
            }
            //non-empty list:
            else{
                //set name:
                int state = 0; // is now finish setting?
                               // when state = 0, it means we donot set the name and the score
                               // when state = 1, it means we already set the name and we need to set the score
                               // when state = 2, it means the name is in the list and we need to set the score in a special case
                               // when state = 3, it means we already set the name and the score
                while(tmp->name_nex != nullptr && state == 0){
                    if(comp_name(tmp->name, name) == 0){ //name are the same
                        // tmp->score = score;
                        // state = 2; //finish setting
                        this->remove_exam(name);
                        // cout << "remove complete" << endl;

                        delete newnode;

                        this->add_exam(name,score);
                        // cout << "cout complete" << endl;
                        state = 3;
                    }
                    else if(comp_name(tmp->name, name) < 0){ //tmp name is samller 
                        tmp = tmp->name_nex;
                    }
                    else if(comp_name(tmp->name, name) > 0){ //tmp name is bigger, now we should set the name before tmp
                        if(tmp->name_pre == nullptr){ //tmp name is the first
                            name_head = newnode;
                            newnode->name_nex = tmp;
                            tmp->name_pre = newnode;
                            state = 1; //finish setting
                        }
                        else{
                            tmp->name_pre->name_nex = newnode;
                            newnode->name_pre = tmp->name_pre;
                            newnode->name_nex = tmp;
                            tmp->name_pre = newnode;
                            state = 1; //finish setting
                        }
                    }
                }
                if(tmp->name_nex == nullptr && state == 0){ //tmp position is the last of the name list
                    if(comp_name(tmp->name, name) == 0){
                        // tmp->score = score;
                        // state = 2; //finish setting
                        tmp = tmp->name_pre;
                        this->remove_exam(name);

                        delete newnode;

                        this->add_exam(name,score);
                        state = 3;
                    }
                    else if(comp_name(tmp->name, name) < 0){ //the last name is also smaller than the name
                        tmp->name_nex = newnode; //we should set the name on the last of the name list
                        newnode->name_pre = tmp;
                        name_tail = newnode;
                        state = 1; //finish setting
                    }
                    else if(comp_name(tmp->name, name) > 0){ //the last name is bigger than the name and we should set the name before the last name
                        if(tmp->name_pre == nullptr){ //tmp name is the first
                            name_head = newnode;
                            newnode->name_nex = tmp;
                            tmp->name_pre = newnode;
                            state = 1; //finish setting
                        }
                        else{
                            tmp->name_pre->name_nex = newnode;
                            newnode->name_pre = tmp->name_pre;
                            newnode->name_nex = tmp;
                            tmp->name_pre = newnode;
                            state = 1; //finish setting
                        }
                    }
                }

                //set score:
                tmp = score_head;
                while(tmp->score_nex != nullptr && state == 1){
//                    if(tmp->score == score){ //how to set when two same score?
//                        //
//                    }
                    if(tmp->score < score){
                        tmp = tmp->score_nex;
                    }
                    else if(tmp->score >= score){
                        if(tmp->score_pre == nullptr){
                            score_head = newnode;
                            newnode->score_nex = tmp;
                            tmp->score_pre = newnode;
                            state = 2; //finish setting
                        }
                        else{
                            tmp->score_pre->score_nex = newnode;
                            newnode->score_pre = tmp->score_pre;
                            newnode->score_nex = tmp;
                            tmp->score_pre = newnode;
                            state = 2; //finish setting
                        }
                    }
                }
                if(tmp->score_nex == nullptr && state == 1){
//                    if(tmp->score == score){ //how to set when two same score?
//                        //
//                    }
                    if(tmp->score < score){
                        tmp->score_nex = newnode;
                        newnode->score_pre = tmp;
                        score_tail = newnode;
                        state = 2; //finish setting
                    }
                    else if(tmp->score >= score){
                        if(tmp->score_pre == nullptr){
                            score_head = newnode;
                            newnode->score_nex = tmp;
                            tmp->score_pre = newnode;
                            state = 2; //finish setting
                        }
                        else{
                            tmp->score_pre->score_nex = newnode;
                            newnode->score_pre = tmp->score_pre;
                            newnode->score_nex = tmp;
                            tmp->score_pre = newnode;
                            state = 2; //finish setting
                        }
                    }
                }
            }
        }
        else{
            cmpt::error("name is empty!");
        }      
    }

    int comp_name(const string& name1, const string& name2){ //helping function
        if(name1.compare(name2) < 0){
            return -1;
        }
        else if(name1.compare(name2) > 0){
            return 1;
        }
        return 0;
    }

    int is_space(string name){ //helping function to check is there is space in the name
        int state = 0;
        for(int i = 0; i < name.size(); i++){
            if(name[i] == ' '){
                state = 1;
            }
        }
        return state;
    }

    // Pre-condition:
    //    name is non-empty and contains no spaces
    //    use cmpt::error to throw an exception if this is not satisfied
    // Post-condition:
    //    deletes the (name, score) pair from this Exam_database; if there is no
    //    pair with the given name, then this does nothing
    void remove_exam(const string& name){
        string name_tmp = name;
        if(is_space(name_tmp) == 1){
            cmpt::error("name contains spaces!");
            // cout << "name conains spaces!" << endl;
            // return;
        }
        if(name_head == nullptr && name != ""){
            // cmpt::error("list is empty!");
            cout << "list is empty!" << endl;
            return;
        }
        if(name_head->name_nex == nullptr && name != ""){
            // cout << "ONE NAME" << endl;
            if(name_head->name == name){
                // cout << "ONE NAME 2" << endl;
                delete name_head;
                name_head = nullptr;
                name_tail = nullptr;
                score_head = nullptr;
                score_tail = nullptr;
                // cout << "ONE NAME 3" << endl;

            }
        }
        else if(name != ""){ //name is non-empty
            Node* tmp = name_head;
            int state = 0; //do we complete remove

            while(tmp->name_nex != nullptr && state == 0){ //while loop to find the name
                if(name == tmp->name){ //tmp name is the name we want
                    if(tmp->name_pre == nullptr && tmp->name_nex == nullptr){ //only one ele in the list
                        delete tmp;
                        name_head = nullptr;
                        name_tail = nullptr;
                        score_head = nullptr;
                        score_tail = nullptr;
                    }
                    else if(tmp->name_pre == nullptr){ //name is in the first position
                        name_head = tmp->name_nex; //set name
                        tmp->name_nex->name_pre = nullptr;
                        if(tmp->score_pre != nullptr && tmp->score_nex != nullptr){ //set score
                            tmp->score_nex->score_pre = tmp->score_pre;
                            tmp->score_pre->score_nex = tmp->score_nex;
                            delete tmp;
                            state = 1;
                        }
                        else if(tmp->score_pre == nullptr){ //tmp score is first of score list
                            score_head = tmp->score_nex;
                            tmp->score_nex->score_pre = nullptr;
                            delete tmp;
                            state = 1;
                        }
                        else if(tmp->score_nex == nullptr){ //tmp score is the last of score list
                            score_tail = tmp->score_pre;
                            tmp->score_pre->score_nex = nullptr;
                            delete tmp;
                            state = 1;
                        }
                    }
                    else{
                        tmp->name_nex->name_pre = tmp->name_pre; //set name
                        tmp->name_pre->name_nex = tmp->name_nex;
                        if(tmp->score_pre != nullptr && tmp->score_nex != nullptr){ //set score
                            tmp->score_nex->score_pre = tmp->score_pre;
                            tmp->score_pre->score_nex = tmp->score_nex;
                            delete tmp;
                            state = 1;
                        }
                        else if(tmp->score_pre == nullptr){ //tmp score is first of score list
                            score_head = tmp->score_nex;
                            tmp->score_nex->score_pre = nullptr;
                            delete tmp;
                            state = 1;
                        }
                        else if(tmp->score_nex == nullptr){ //tmp score is the last of score list
                            score_tail = tmp->score_pre;
                            tmp->score_pre->score_nex = nullptr;
                            delete tmp;
                            state = 1;
                        }
                    }
                }
                else{ 
                    tmp = tmp->name_nex;
                }
            }
            if(tmp->name_nex == nullptr && state == 0){ //check the last position
                if(name == tmp->name){ //tmp name is the name we want
                    name_tail = tmp->name_pre; //set name
                    tmp->name_pre->name_nex = nullptr;
                    if(tmp->score_pre != nullptr && tmp->score_nex != nullptr){ //set score
                        tmp->score_nex->score_pre = tmp->score_pre;
                        tmp->score_pre->score_nex = tmp->score_nex;
                        delete tmp;
                        state = 1;
                    }
                    else if(tmp->score_pre == nullptr){ //tmp score is first of score list
                         score_head = tmp->score_nex;
                         tmp->score_nex->score_pre = nullptr;
                         delete tmp;
                         state = 1;
                    }
                    else if(tmp->score_nex == nullptr){ //tmp score is the last of score list
                        score_tail = tmp->score_pre;
                        tmp->score_pre->score_nex = nullptr;
                        delete tmp;
                        state = 1;
                    }
                }
            }

        }

        else if(name == ""){ //name is empty
            cmpt::error("name is empty!");
        }
        // else
        // {
        //    cmpt::error("name is empty!");

        // }
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    print (to cout) all (name, score) pairs in alphabetical order by name
    void print_by_name() const{
        Node* tmp = name_head;
        if(name_head == nullptr){
            cout << "list is empty!" << endl;
        }
        else{
        while(tmp->name_nex != nullptr){
            cout << "(" << tmp->name << ", " << tmp->score << ")" << endl;
            tmp = tmp->name_nex;
        }
        cout << "(" << tmp->name << ", " << tmp->score << ")" << endl;
        }
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    print (to cout) all (name, score) pairs in reverse alphabetical order
    //    by name
    void print_by_name_rev() const{
        Node* tmp = name_tail;
        if(name_head == nullptr){
            cout << "list is empty!" << endl;
        }
        else{
        while(tmp->name_pre != nullptr){
            cout << "(" << tmp->name << ", " << tmp->score << ")" << endl;
            tmp = tmp->name_pre;
        }
        cout << "(" << tmp->name << ", " << tmp->score << ")" << endl;
        }
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    print (to cout) all (name, score) pairs from smallest to biggest by score
    void print_by_score_ascending() const{
        Node* tmp = score_head;
        if(name_head == nullptr){
            cout << "list is empty!" << endl;
        }
        else{
        while(tmp->score_nex != nullptr){
            cout << "(" << tmp->name << ", " << tmp->score << ")" << endl;
            tmp = tmp->score_nex;
        }
        cout << "(" << tmp->name << ", " << tmp->score << ")" << endl;
        }
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    print (to cout) all (name, score) pairs from biggest to smallest by score
    void print_by_score_descending() const{
        Node* tmp = score_tail;
        if(name_head == nullptr){
            cout << "list is empty!" << endl;
        }
        else{
        while(tmp->score_pre != nullptr){
            cout << "(" << tmp->name << ", " << tmp->score << ")" << endl;
            tmp = tmp->score_pre;
        }
        cout << "(" << tmp->name << ", " << tmp->score << ")" << endl;
        }
    }

    //
    // ... you can add other helper methods here if you need them ...
    //

}; // class Exam_database