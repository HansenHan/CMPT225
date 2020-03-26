// a3.h

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
#include <stack>
#include <queue>
#include <deque>

using namespace std;

///////////////////////////////////////////////////////////////////////////////
//
// Your task for this assignment is to implement all of the methods of the BST
// class given below, subject to a few important constraints.
//
// Here are the things your implementation **cannot** do:
//
// - You **cannot** use recursion anywhere in any of your code.
//
// - You **cannot** add new variables to the BST class, public or private. You
//   cannot add any global variables.
//
// - You **cannot** #include any other files. If you borrow code or ideas from
//   any other source, be sure to cite the source (e.g. as a comment in your
//   code).
//
// - You **cannot** use arrays or vectors or any other pre-made data
//   structure. As mentioned below, you may only use data structures that you
//   implement yourself.
//
// Here are the things your implementation **can** do:
//
// - You **can** add helper methods, either public or private, to BST. You may
//   also add helper functions outside of BST. Of course, any extra
//   methods/functions you add must follow the "cannot" rules above.
//
// - You **can** add helper classes, either in BST or outside of BST. For
//   instance, you could implement your own stack class.
//
// Put all the code necessary to implement BST correct inside a3.h, and then
// submit just this file when you are done. Put your testing code in a3.cpp.
//
// In the specification of the methods for BST, these variables are used:
//
// - n is the number of nodes in the BST
// - h is the height of the BST
// - T refers to the tree immediately before a method is called
// - T' refers to the tree immediately after the method is finished
//
///////////////////////////////////////////////////////////////////////////////


//     class deque{
//     private:
//         struct Dnode{
//             Node* value;
//             Dnode* nex;
//             Dnode* pre;
//         };

//         Dnode* head;
//         Dnode* tail;
//     public:
//         deque(){
//             head = nullptr;
//             tail = nullptr;
//         }

//         ~deque(){
//             while(head!=nullptr){
//                 Dnode* tmp = head;
//                 head = head->nex;
//                 delete tmp;
//             }
//         }

//         void push_front(Node* s){
//             Dnode* newnode = new Dnode{s, nullptr, nullptr};
//             if(head == nullptr){
//                 head = newnode;
//                 tail = newnode;
//             }
//             else{
//                 newnode->nex = head;
//                 head = newnode;
//             }
//         }

//         void push_back(Node* s){
//             Dnode* newnode = new Dnode{s, nullptr, nullptr};
//             if(head == nullptr){
//                 head = newnode;
//                 tail = newnode;
//             }
//             else{
//                 newnode->pre = tail;
//                 tail = newnode;
//             }
//         }

//         Node* pop_front(){
//             if(head == nullptr){
//                 return nullptr;
//             }
//             else{
//                 Dnode* tmp = head;
//                 head = head->nex;
//                 head->pre = nullptr;
//                 Node* st = tmp->value;
//                 delete tmp;
//                 return st;
//             }
//         }

//         Node* pop_back(){
//             if(head == nullptr){
//                 return nullptr;
//             }
//             else{
//                 Dnode* tmp = tail;
//                 tail = tail->pre;
//                 tail->nex = nullptr;
//                 Node* st = tmp->value;
//                 delete tmp;
//                 return st;
//             }
//         }

//         Node* front(){
//             if(head == nullptr){
//                 return nullptr;
//             }
//             else{
//                 return head->value;
//             }
//         }

//         Node* back(){
//             if(head == nullptr){
//                 return nullptr;
//             }
//             else{
//                 return tail->value;
//             }
//         }

//         bool empty(){
//             if(head==nullptr){
//                 return true;
//             }
//             else{
//                 return false;
//             }
//         }

//         int size(){
//             if(head == nullptr){
//                 return 0;
//             }
//             else{
//                 Dnode* tmp = head;
//                 int count = 0;
//                 while(tmp != nullptr){
//                     tmp = tmp->nex;
//                     count++;
//                 }
//                 return count;
//             }
//         }

// };


class BST {
private:
    struct Node {
        string value;
        Node* left;
        Node* right;
    };

    Node* root;

public:
    // Pre-condition:
    //    none
    // Post-condition:
    //    constructs a new empty BST
    // Constraints:
    //    O(1) performance
    BST(){
        root = nullptr;
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    deletes all the nodes in this BST
    // Constraints:
    //    O(n) performance
    ~BST(){  //check!!
        if(this->root == nullptr){
            return;
        }

        deque<Node*> dqu;
        dqu.push_back(root);

        while(!dqu.empty()){
            Node* tmp = dqu.front();
            dqu.pop_front();

            if(tmp->left != nullptr){
                dqu.push_back(tmp->left);
            }
            if(tmp->right != nullptr){
                dqu.push_back(tmp->right);
            }
            delete tmp;
        }
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    returns the number of string in this tree (i.e. n)
    // Constraints:
    //    worst-case O(n) performance; does not use recursion!
    int size() const{
        int num = 0;
        if(this->root == nullptr){
            return num;
        }

        Node* tmp = root;
        deque<Node*> dqu;
        dqu.push_back(root);
        while(!dqu.empty()){
            tmp = dqu.front();
            dqu.pop_back();
            num++;

            if(tmp->left != nullptr){
                dqu.push_back(tmp->left);
            }
            if(tmp->right != nullptr){
                dqu.push_back(tmp->right);
            }
        }
        return num;
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    returns the height of this tree
    // Constraints:
    //    worst-case O(n) performance; does not use recursion!
    // Note:
    //    The height of a BST is the number of links in the longest
    //    root-to-leaf path in the tree. An empty tree is height 0,
    //    and a tree with a single node is also height 0.
    int height() const{ //check!!
        int h = 0;
        if(this->root == nullptr){
            return h;
        }
        Node* last = root;
        deque<Node*> dqu;
        dqu.push_back(root);
        while(!dqu.empty()){
            Node* tmp = dqu.front();
            if(tmp != nullptr){
                dqu.pop_front();
                if(tmp->left != nullptr){
                    dqu.push_back(tmp->left);
                }
                if(tmp->right != nullptr){
                    dqu.push_back(tmp->right);
                }
                if(tmp == last){
                    if(!dqu.empty()){
                        last = dqu.back();
                    }
                    h++;
                }
            }
        }
        return h;
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    returns true if s is in this tree, and false otherwise
    // Constraints:
    //    worst-case O(h) performance; does not use recursion!
    bool contains(const string& s) const{ //check!!
        if(this->root == nullptr){
            return false;
        }
        Node* tmp = root;
        while(tmp != nullptr){
            if(tmp->value == s){
                return true;
            }
            else if(s < tmp->value){
                tmp = tmp->left;
            }
            else if(s > tmp->value){
                tmp = tmp->right;
            }
        }
        return false;
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    T'.contains(s)
    // Constraints:
    //    worst-case O(h) performance; does not use recursion!
    // Note:
    //    If s is already in T, then insert(s) does nothing.
    void insert(const string& s){
        if(root == nullptr){
            root = new Node{s,nullptr,nullptr};
        }
        else{
            Node* tmp = root;
            while(tmp != nullptr){
                if(tmp->value == s){
                    return;
                }
                else if(s < tmp->value){
                    if(tmp->left != nullptr){
                        tmp = tmp->left;
                    }
                    else{
                        tmp->left = new Node{s,nullptr,nullptr};
                    }
                }
                else if(s > tmp->value){
                    if(tmp->right != nullptr){
                        tmp = tmp->right;
                    }
                    else{
                        tmp->right = new Node{s,nullptr,nullptr};
                    }
                }
            }
        }
    }


    // Pre-condition:
    //    none
    // Post-condition:
    //    !T'.contains(s)
    // Constraints:
    //    worst-case O(h) performance; does not use recursion!
    // Note:
    //    If s is not in T, then remove(s) does nothing.
    void remove(const string& s){
        if(root == nullptr){
            return;
        }
        else{
            Node* tmp = root;
            Node* last = nullptr;
            int pos = 0;
            while(tmp != nullptr){
                if(tmp->value != s){
                    if(s < tmp->value){
                        last = tmp;
                        tmp = tmp-> left;
                        pos = 1;
                    }
                    else if(s > tmp->value){
                        last = tmp;
                        tmp = tmp->right;
                        pos = 2;
                    }
                }
                else{
                    if(tmp->left == nullptr && tmp->right == nullptr){
                        if(pos == 1){
                            delete tmp;
                            last->left = nullptr;
                            tmp = nullptr;
                        }
                        if(pos == 2){
                            delete tmp;
                            last->right = nullptr;
                            tmp = nullptr;
                        }
                    }
                    else if(tmp->left != nullptr && tmp->right == nullptr){
                        if(pos == 1){
                            last->left = tmp->left;
                            delete tmp;
                            tmp = nullptr;
                        }
                        if(pos == 2){
                            last->right = tmp->left;
                            delete tmp;
                            tmp = nullptr;
                        }
                    }
                    else if(tmp->left == nullptr && tmp->right != nullptr){
                        if(pos == 1){
                            last->left = tmp->right;
                            delete tmp;
                            tmp = nullptr;
                        }
                        if(pos == 2){
                            last->right = tmp->right;
                            delete tmp;
                            tmp = nullptr;
                        }
                    }
                    else if(tmp->left != nullptr && tmp->right != nullptr){
                        if(pos == 1){
                            last->left = tmp->right;
                            Node* mm = tmp->right;
                            while(mm->left != nullptr){
                                mm = mm->left;
                            }
                            mm->left = tmp->left;
                            delete tmp;
                            tmp = nullptr;
                        }
                        if(pos == 2){
                            last->right = tmp->right;
                            Node* mm = tmp->right;
                            while(mm->left != nullptr){
                                mm = mm->left;
                            }
                            mm->left = tmp->left;
                            delete tmp;
                            tmp = nullptr;
                        }
                    }
                }
            }
        }
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    prints all the strings in T to cout in pre-order order
    // Constraints:
    //    worst-case O(n) performance; does not use recursion!
    void print_preorder() const{
        if(root == nullptr)
        {
            return;
        }
        deque<Node*> dqu;
        dqu.push_back(root);

        while(!dqu.empty())
        {
            Node* tmp = dqu.back();
            cout << tmp->value << endl;
            dqu.pop_back();

            if(tmp->right != nullptr){
                dqu.push_back(tmp->right);
            }
            if(tmp->left != nullptr){
                dqu.push_back(tmp->left);
            }
        }
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    prints all the strings in T to cout in in-order order
    //    (i.e. alphabetical order)
    // Constraints:
    //    worst-case O(n) performance; does not use recursion!
    void print_inorder() const{
        if(root == nullptr){
            return;
        }
        deque<Node*> dqu;
        Node* tmp = root;

        while(!dqu.empty() || tmp != nullptr){
            if(tmp != nullptr){
                dqu.push_back(tmp);
                tmp = tmp->left;
            }
            else{
                tmp = dqu.back();
                dqu.pop_back();
                cout << tmp->value << endl;
                tmp = tmp->right;
            }
        }
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    prints all the strings in T to cout in post-order order
    // Constraints:
    //    worst-case O(n) performance; does not use recursion!
    // void print_postorder() const{
    //     if(root == nullptr){
    //         return;
    //     }

    //     Node* new_root = this->copy_tree();

    //     stack<Node*> st;
    //     Node* tmp = new_root;
    //     Node* le = root->left;
    //     Node* ri = root->right;
    //     int pos = 0;
    //     // Node* las = nullptr;
        
    //     while(!st.empty() || tmp != nullptr){
    //         if(le != nullptr){
    //             st.push(le);
    //             le = le->left;
    //             tmp = st.top();
    //             ri = tmp->right;
    //             pos = 1;
    //         }
    //         else if(le == nullptr && ri != nullptr){
    //             st.push(ri);
    //             ri = tmp->right;
    //             tmp = st.top();
    //             le = tmp->left;
    //             pos = 2;
    //         }
    //         else if(le == nullptr && ri == nullptr){
    //             cout << tmp->value << endl;
    //             st.pop();
    //             delete tmp;
    //             tmp = st.top();
    //             if(pos = 1){
    //                 tmp->left = nullptr;
    //             }
    //             else if(pos = 2){
    //                 tmp->right = nullptr;
    //             }
    //         }

    //         // else{
    //         //     tmp = st.top();
    //         //     st.pop();
    //         //     cout << tmp->value << endl;
    //         //     tmp = tmp->right;
    //         // }
    //     }
    // }

    // Node* copy_tree(){
    //     if(this->root == nullptr){
    //         return nullptr;
    //     }

    //     Node* new_root = new Node{root->value,nullptr,nullptr};

    //     Node* tmp = root;
    //     queue<Node*> qu;
    //     qu.push(root);
    //     while(!qu.empty()){
    //         tmp = qu.front();
    //         qu.pop();

    //         if(tmp->left != nullptr){
    //             qu.push(tmp->left);
    //         }
    //         if(tmp->right != nullptr){
    //             qu.push(tmp->right);
    //         }
    //     }
    //     return new_root;
    // }
}; // class BST


