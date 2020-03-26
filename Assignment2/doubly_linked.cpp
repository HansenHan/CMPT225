// doubly_linked.cpp

#include <iostream>
#include "cmpt_error.h"
#include <cassert>

using namespace std;

class Doubly_linked {
private:
    struct Node {
        int val;
        Node* prev;
        Node* next;
    }; // struct Node
    
    Node* head;  // points to the first element
    Node* tail;  // points to the last element
public:
    // Pre-condition:
    //    none
    // Post-condition:
    //     constructs a new empty list
    Doubly_linked()
    : head(nullptr), tail(nullptr)
    { }
    
    // Pre-condition:
    //    none
    // Post-condition:
    //     deletes all nodes on this list
    // Note:
    //     this is a destructor and so is called utomatically when this Doubly_linked 
    //     goes out of scope, or is deleted; thus no memory leaks are possible!
    ~Doubly_linked() {
        while (head != nullptr) {
            Node* p = head;
            head = head->next;
            delete p;
        }
        cout << "Doubly_linked destructor: all list elements deleted\n";
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //     returns true if there are no elements in this list, and false
    //     otherwise
    bool is_empty() const {
        return head == nullptr;
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //     returns the number of items in this list
    int size() const {
        int count = 0;
        Node* p = head;
        while (p != nullptr) {
            count++;
            p = p->next;
        }
        return count;
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //     adds x as the first element of this list
    void push_front(int x) {
        if (is_empty()) {
            head = new Node{x, nullptr, nullptr};
            tail = head;
        } else {
            Node* p = new Node{x, nullptr, head};
            head->prev = p;
            head = p;
        }
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //     adds x as the last element of this list
    void push_back(int x) {
        if (is_empty()) {
            head = new Node{x, nullptr, nullptr};
            tail = head;
        } else {
            Node* p = new Node{x, tail, nullptr};
            tail->next = p;
            tail = p;
        }
    }

    // Pre-condition:
    //    !is_empty()
    // Post-condition:
    //    removes and return the first element of this list
    int pop_front() {
        if (is_empty()) cmpt::error("can't pop empty list");
        if (head->next == nullptr) { // single-element list is a special case
            Node* p = head;
            head = nullptr;
            tail = nullptr;
            int result = p->val;
            delete p; 
            return result;  
        } else {  // list has two, or more, elements
            Node* p = head;
            head = head->next;
            int result = p->val;
            delete p; 
            return result;              
        }
    }

    // Pre-condition:
    //    !is_empty()
    // Post-condition:
    //    removes and return the last element of this list
    int pop_back() {
        if (is_empty()) cmpt::error("can't pop empty list");
        if (tail->prev == nullptr) { // single-element list is a special case
            Node* p = tail;
            head = nullptr;
            tail = nullptr;
            int result = p->val;
            delete p;
            return result;
        } else {  // list has two, or more, elements
            Node* p = tail;
            tail = tail->prev;
            int result = p->val;
            delete p;
            return result;
        }
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    prints this list to cout
    void print() const {
        cout << "[";
        Node* p = head;
        while (p != nullptr) {
            cout << p->val << " ";
            p = p->next;
        }
        cout << "]";
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    prints this list to cout, and then a newline
    void println() const {
        print();
        cout << "\n";
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    prints this list, in reverse order, to cout
    void print_reverse() const {
        cout << "[";
        Node* p = tail;
        while (p != nullptr) {
            cout << p->val << " ";
            p = p->prev;
        }
        cout << "]";
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    prints this list, in reverse order, to cout, and then
    //    a newline
    void println_reverse() const {
        print_reverse();
        cout << "\n";
    }
}; // class List

void test1() {
    Doubly_linked lst;
    for(int i = 1; i <= 10; ++i) {
        lst.push_back(i);
        assert(lst.size() == i);
    }

    lst.println_reverse();
    while (!lst.is_empty()) {
        lst.pop_back();
    }
    lst.println();
}

void test2() {
    for(int i = 0; i < 10; ++i) {
        Doubly_linked lst;
        for(int j = 1; j <= i; ++j) {
            lst.push_back(j);
        }
        assert(lst.size() == i);
        lst.println();
    }
}


int main() {
    test1();
    // test2();
}
