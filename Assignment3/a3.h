// a3.h

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






class BST {
private:
    struct Node {
        string value;
        Node* left;
        Node* right;
    };

    Node* root;


    class stack{ //stack class
    private:
        struct Stnode{
            Node* value;
            Stnode* next;
        };
        Stnode* head;
    public:
        stack(){
            head = nullptr;
        }
       
        ~stack(){
            while(head != nullptr){
                Stnode* tmp = head;
                head = head->next;
                delete tmp;
            }
        }
       
        void push(Node* n){
            Stnode* newnode = new Stnode{n, nullptr};
            if(head == nullptr){
                head = newnode;
            }
            else{
                newnode->next = head;
                head = newnode;
            }
        }
        void push_front(Node* n){  //push the node in front
            Stnode* newnode = new Stnode{n, nullptr};
            Stnode* tmp = head;
            if(head == nullptr){
                head = newnode;
                return;
            }
            while(tmp->next != nullptr){
                tmp = tmp->next;
            }
            tmp->next = newnode;
        }
        Node* pop(){
            if(head == nullptr){
                return nullptr;
            }
            else{
                Stnode* top = head;
                Node* answ = head->value;
                head = head->next;
                delete top;
                return answ;
            }
        }
        Node* pop_front(){  //pop the front node 
            if(head == nullptr){
                return nullptr;
            }
            else if(head->next == nullptr){
                Node* answ = head->value;
                Stnode* tmp = head;
                head = nullptr;
                delete tmp;
                return answ;
            }
            else{
                Stnode* tmp = head;
                while(tmp->next->next != nullptr){
                    tmp = tmp->next;
                }
                Stnode* fro = tmp->next;
                Node* answ = fro->value;
                delete fro;
                tmp->next = nullptr;
                return answ;
            }
        }
        Node* top(){
            if(head == nullptr){
                return nullptr;
            }
            else{
                return head->value;
            }
        }
        Node* front(){  //get the front node
            if(head == nullptr){
                return nullptr;
            }
            else{
                Stnode* tmp = head;
                while(tmp->next != nullptr){
                    tmp = tmp->next;
                }
                Node* answ = tmp->value;
                return answ;
            }
        }
        bool empty(){
            if(head == nullptr){
                return true;
            }
            else{
                return false;
            }
        }
    };//stack class


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
        if(this->root == nullptr){ //tmpty tree
            return;
        }

        stack dqu;
        dqu.push(root);

        while(!dqu.empty()){
            Node* tmp = dqu.top();
            dqu.pop();

            if(tmp->left != nullptr){
                dqu.push(tmp->left);
            }
            if(tmp->right != nullptr){
                dqu.push(tmp->right);
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
    // int size() const{
    //     int num = 0;
    //     if(this->root == nullptr){ //empty tree!
    //         return num;
    //     }

    //     Node* tmp = root;
    //     stack dqu;
    //     dqu.push(root);

    //     while(!dqu.empty()){
    //         tmp = dqu.top();
    //         dqu.pop(); //everytime pop node means there is a node in tree
    //         num++;

    //         if(tmp->left != nullptr){      //push every node in a stack
    //             dqu.push(tmp->left);
    //         }
    //         if(tmp->right != nullptr){
    //             dqu.push(tmp->right);
    //         }
    //     }
    //     return num;
    // }

    int size() const{ //check!!
        int h = 0;
        if(root == nullptr){ //empty tree
            return h;
        }
        return size(root);
    }
    int size(Node *root) const{ //check!!
        if(root == nullptr){ //empty tree
            return 0;
        }
        int lefth = size(root->left);
        int righth = size(root->right);
        return lefth + righth + 1;
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
        if(this->root == nullptr){ //empty tree
            return h;
        }
        Node* last = root;
        stack dqu;
        dqu.push(root);
        while(!dqu.empty()){
            Node* tmp = dqu.front();
            if(tmp != nullptr){
                dqu.pop_front();
                if(tmp->left != nullptr){      //push every node in a stack
                    dqu.push(tmp->left);
                }
                if(tmp->right != nullptr){
                    dqu.push(tmp->right);
                }
                if(tmp == last){
                    if(!dqu.empty()){
                        last = dqu.top();
                    }
                    h++;
                }
            }
        }
        h--;
        return h;
    }

    int height() const{ //check!!
        int h = -1;
        if(root == nullptr){ //empty tree
            return h;
        }
        return height(root);
    }
    int height(Node *root) const{ //check!!
        if(root == nullptr){ //empty tree
            return -1;
        }
        int lefth = height(root->left);
        int righth = height(root->right);
        if(lefth > righth){
            return lefth + 1;
        }
        else{
            return righth + 1;
        }
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    returns true if s is in this tree, and false otherwise
    // Constraints:
    //    worst-case O(h) performance; does not use recursion!
    bool contains(const string& s) const{ //check!!
        if(this->root == nullptr){ //empty tree
            return false;
        }
        Node* tmp = root;
        while(tmp != nullptr){
            if(tmp->value == s){  //find the node
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
        if(root == nullptr){  //empty tree
            root = new Node{s,nullptr,nullptr};
        }
        else{
            Node* tmp = root;
            while(tmp != nullptr){
                if(tmp->value == s){  //this value is already in the tree
                    return;
                }
                else if(s < tmp->value){
                    if(tmp->left != nullptr){
                        tmp = tmp->left;
                    }
                    else{ //add this value in the end of the tree
                        tmp->left = new Node{s,nullptr,nullptr};
                    }
                }
                else if(s > tmp->value){
                    if(tmp->right != nullptr){
                        tmp = tmp->right;
                    }
                    else{ //add this value in the end of the tree
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
        if(root == nullptr){ //empty tree
            return;
        }
        else{
            Node* tmp = root;
            Node* last = nullptr;
            int pos = 0;   //this is the falge of left or right
                           //when pos=0, means the node we find is the root
                           //when pos=1, means tmp comes from left
                           //when pos=2, means tmp comes from right
            while(tmp != nullptr){
                if(tmp->value != s){ //not find the node
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
                else{ //find the node
                    if(tmp->left == nullptr && tmp->right == nullptr){ //this node has no children
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
                    else if(tmp->left != nullptr && tmp->right == nullptr){ //this node has left children 
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
                    else if(tmp->left == nullptr && tmp->right != nullptr){ //this node has right children
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
                    else if(tmp->left != nullptr && tmp->right != nullptr){ //this node has left and right children
                        if(pos == 0){
                            root = tmp->right;
                            Node* mm = tmp->right;
                            while(mm->left != nullptr){
                                mm = mm->left;
                            }
                            mm->left = tmp->left;
                            delete tmp;
                            tmp = nullptr;
                        }
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
    // void print_preorder() const{
    //     if(root == nullptr){ //empty tree
    //         return;
    //     }
    //     stack dqu;
    //     dqu.push(root);

    //     while(!dqu.empty()){
    //         Node* tmp = dqu.top();
    //         cout << tmp->value << " ";
    //         dqu.pop();  //every time pop node means we print this node

    //         if(tmp->right != nullptr){  //push every node in a stack
    //             dqu.push(tmp->right);
    //         }
    //         if(tmp->left != nullptr){
    //             dqu.push(tmp->left);
    //         }
    //     }
    //     cout << endl;
    // }

    void print_preorder() const{ //check!!
        if(root == nullptr){ //empty tree
            return;
        }
        print_preorder(root);
        cout << endl;
    }
    void print_preorder(Node *root) const{ //check!!
        if(root!=nullptr){
            cout << root->value;
            print_preorder(root->left);
            print_preorder(root->right);
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
        if(root == nullptr){  //empty tree
            return;
        }

        stack dqu;
        Node* tmp = root;
        while(!dqu.empty() || tmp != nullptr){
            if(tmp != nullptr){
                dqu.push(tmp);
                tmp = tmp->left;
            }
            else{ //find the left node of tree
                tmp = dqu.top();
                dqu.pop();
                cout << tmp->value << " ";
                tmp = tmp->right; // check is there a node in the right 
            }
        }
        cout << endl;
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    prints all the strings in T to cout in post-order order
    // Constraints:
    //    worst-case O(n) performance; does not use recursion!
    void print_postorder() const{
        Node* killer = root; //when killer piont a node, means this node is already printed
                             //when meet the killer, means nodes below tmp is already printed
        if (killer== nullptr){
            return;
        }

        stack dqu;
        Node* tmp = root;
        dqu.push(tmp);
        while (!dqu.empty()){
            tmp = dqu.top();
            if(tmp->left == nullptr && tmp->right == nullptr){
                dqu.pop();
                cout << tmp->value << " ";
                killer = tmp;
            }
            else if(tmp->left == killer || tmp->right == killer){
                dqu.pop();
                cout << tmp->value << " ";
                killer = tmp;
            }
            else{
                if (tmp->right != nullptr){  // push every node in a stack
                    dqu.push(tmp->right);
                }
                if (tmp->left != nullptr){
                    dqu.push(tmp->left);
                }
            }
        }
        cout << endl;
    }

}; // class BST


