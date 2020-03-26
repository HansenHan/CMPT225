// Exam_database.h

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
    struct Node {
        string name;
        Node* prev_name;
        Node* next_name;

        int score;
        Node* prev_score;
        Node* next_score;
    }; // struct Node

    Node* head_name;  // points to the first name
    Node* tail_name;  // points to the last name
    Node* head_score;  // points to the lowest score
    Node* tail_score;  // points to the highest element

public:
    // Pre-condition:
    //    none
    // Post-condition:
    //    constructs a new empty Exam_database
    // Note:
    //    you can use an initialization with this constructor
    Exam_database()
    {
        head_name = nullptr; 
        head_score = nullptr; 
        tail_name = nullptr;
        tail_score = nullptr;

    }
    // Pre-condition:
    //    none
    // Post-condition:
    //    destructs Exam_database, i.e. ensures all memory (or other resources)
    //    owned by this object are properly deleted
    ~Exam_database()
    {
        // while (head_name != nullptr)
        // {
        //     Node* p = head_name;
        //     head_name = head_name->next_name;
        //     delete p;
        // }
        while (head_score != nullptr)
        {
            Node* a = head_score;
            head_score = head_score->next_score;
            delete a;
        }

    }


    // Pre-condition:
    //    name is non-empty and contains no spaces
    //    use cmpt::error to throw an exception if this is not satisfied
    // Post-condition:
    //    adds (name, score) to this object; if a pair in the database already
    //    has the name, then its corresponding score is set to score
    void add_exam(const string& name, int score)
    {
        if (name != "") //non-empty name
        {
            Node* newnode = new Node{name, nullptr, nullptr, score, nullptr, nullptr};         
            // linked list is empty
            if (head_name == nullptr) 
            {
                head_name = newnode;
                head_score = newnode;
                tail_name = newnode;
                tail_score = newnode;     
            }
            // linked list is non-empty
            else
            {
                //add new name
                Node* temp = head_name;
                // Node* final_name = head_name;
                while(temp != nullptr) // check every node until finish
                {
                    if (temp->name.compare(name) == 0) // 
                    {
                        temp->score = score;
                        break;
                    }
                    else if (temp->name.compare(name) < 0) //new name's string is bigger than temp
                    {
                        // final_name = temp;
                        temp = temp->next_name;
                    }
                    else // now, got the position that new name's string is smaller than temp
                    {
                        if (temp == head_name) // special case: new name's string is smaller than the head_name
                        {
                            newnode->next_name = head_name;
                            head_name->prev_name = newnode;
                            head_name = newnode;
                            break;
                        }
                        else //insert the new name in the correct position
                        {
                            newnode->prev_name = temp->prev_name;
                            temp->prev_name->next_name = newnode;
                            newnode->next_name = temp;
                            temp->prev_name = newnode;
                            break;
                        }

                    }
                }
                if (temp == nullptr) // if new name's string is bigger than anyone, then put it at the tail
                {                   
                    newnode->prev_name = tail_name;
                    tail_name->next_name = newnode;
                    tail_name = newnode;
                }


    //************* link score from smaller to bigger
                temp = head_score;
                // Node* final_score = temp;
                while(temp != nullptr) // check every node until finish
                {
                    if (temp->score < score) //new score is bigger than temp
                    {
                        // final_score = temp;
                        temp = temp->next_score;
                    }
                    else // now, got the position that new score is smaller than temp
                    {
                        if (temp == head_score) // special case: new score is smaller than the score_head
                        {
                            newnode->next_score = head_score;
                            head_score->prev_score = newnode;
                            head_score = newnode;
                            break;
                        }
                        else //insert the new score in the correct position
                        {
                            newnode->prev_score = temp->prev_score;
                            temp->prev_score->next_score = newnode;
                            newnode->next_score = temp;
                            temp->prev_score = newnode;
                            break;
                        }

                    }
                }
                if (temp == nullptr) // if new score is bigger than anyone, then put it at the tail
                {
                    newnode->prev_score = tail_score;
                    tail_score->next_score = newnode;
                    tail_score = newnode;
                }
            }
        }
        else
        {
            cmpt::error("empty");
        }
    }
    



    // Pre-condition:
    //    name is non-empty and contains no spaces
    //    use cmpt::error to throw an exception if this is not satisfied
    // Post-condition:
    //    deletes the (name, score) pair from this Exam_database; if there is no
    //    pair with the given name, then this does nothing
    void remove_exam(const string& name);

    // Pre-condition:
    //    none
    // Post-condition:
    //    print (to cout) all (name, score) pairs in alphabetical order by name
    void print_by_name() const
    {
        Node* temp = head_name;
        while(temp != nullptr)
        {
            cout << "(" << temp->name << ", " << temp->score << ")" << endl;
            temp = temp->next_name;
        }
    }
    

    // Pre-condition:
    //    none
    // Post-condition:
    //    print (to cout) all (name, score) pairs in reverse alphabetical order
    //    by name
    void print_by_name_rev() const
    {
        Node* temp = tail_name;
        while(temp != nullptr)
        {
            cout << "(" << temp->name << ", " << temp->score << ")" << endl;
            temp = temp->prev_name;
        }
        // cout << "(" << temp->prev_name->prev_name->name << ", " << temp->score << ")" << endl;
        // cout << "(" << temp->prev_name->name << ", " << temp->score << ")" << endl;


    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    print (to cout) all (name, score) pairs from smallest to biggest by score
    void print_by_score_ascending() const
    {
        Node* temp = head_score;
        while(temp != nullptr){
            cout << "(" << temp->name << ", " << temp->score << ")" << endl;
            temp = temp->next_score;
        }
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    print (to cout) all (name, score) pairs from biggest to smallest by score
    void print_by_score_descending() const
    {
        Node* temp = tail_score;
        while(temp != nullptr){
            cout << "(" << temp->name << ", " << temp->score << ")" << endl;
            temp = temp->prev_score;
        }
    }

    //
    // ... you can add other helper methods here if you need them ...
    //

    // bool is_empty() const
    // {
    //     return (head_name == nullptr) && (head_score == nullptr) && (tail_name == nullptr) && (tail_score == nullptr);
    // }

    // int compare (const string &str1, const string &str2)
    // {
    //     if (str1.compare(str2) < 0)
    //     {
    //         return -1;
    //     }
    //     else if (str1.compare(str2) == 0)
    //     {
    //         return 0;
    //     }
    //     else
    //         return 1;
    // }

}; // class Exam_database