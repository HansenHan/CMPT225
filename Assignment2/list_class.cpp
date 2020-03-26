// list_class.cpp

#include <iostream>
#include "cmpt_error.h"
#include <cassert>

using namespace std;

class List {
private:
    struct Node {
        int val;
        Node* next;
    }; // struct Node
    
    Node* head;
public:
    // Pre-condition:
    //    none
    // Post-condition:
    //    creates a new empty List
    List()
    : head(nullptr)
    { }

    // Pre-condition:
    //    none
    // Post-condition:
    //     deletes all nodes on this list
    // Note:
    //     this is a destructor and so is called utomatically when this Doubly_linked 
    //     goes out of scope, or is deleted; thus no memory leaks are possible!
    ~List() {
        while (head != nullptr) {
            Node* p = head;
            head = head->next;
            delete p;
        }
        cout << "List destructor: all list elements deleted\n";
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    returns true is this has no elements, and false otherwise
    bool is_empty() const {
        return head == nullptr;
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    returns the number of elements on this list
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
    //    adds x as the new first element of this list
    void push(int x) {
        head = new Node{x, head};
    }

    // Pre-condition:
    //    !is_empty()
    // Post-condition:
    //    removes and returns the first element of this list
    int pop() {
        if (is_empty()) cmpt::error("pop: can't pop empty list");
        Node* p = head;
        head = head->next;
        int result = p->val;
        delete p; 
        return result;      
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    adds x as the new last element of this list
    void push_back(int x) {
        if (head == nullptr) {
            head = new Node{x, nullptr};
        } else {
            // get a pointer to the last element
            Node* p = head;
            while (p->next != nullptr) {
                p = p->next;
            }
            // invariant: p->next == nullptr
            p->next = new Node{x, nullptr};
        }
    }

    // Pre-condition:
    //    !is_empty()
    // Post-condition:
    //    adds x as the new last element of this list
    int pop_back() {
        int n = size();
        if (n == 0) {
            cmpt::error("pop_back: can't pop empty list");
        } else if (n == 1) {
            int result = head->val;
            delete head;
            head = nullptr;
            return result;
        } else { // n > 1
            // get a pointer to the second-to-last element
            Node* p = head;
            while (p->next->next != nullptr) {
                p = p->next;
            }
            // invariant: p->next->next == nullptr
            int result = p->next->val;
            delete p->next;
            p->next = nullptr;
            return result;
        } // if
        cmpt::error("pop_back: something has gone wrong!!");
        return -1;
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    returns a string representation of this list
    string to_string() const {
        if (head == nullptr) {
            return "[]";
        } else if (head->next == nullptr) {
            return "[" + std::to_string(head->val) + "]";
        } else {
            string result = "[" + std::to_string(head->val);
            Node* p = head->next;
            while (p != nullptr) {
                result += " " + std::to_string(p->val);
                p = p->next;
            }
            return result + "]";
        }
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    prints this list to cout
    void print() const {
        cout << to_string();
        // cout << "[";
        // Node* p = head;
        // while (p != nullptr) {
        //     cout << p->val << " ";
        //     p = p->next;
        // }
        // cout << "]";
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    prints this list to cout, folloed by a newline
    void println() const {
        print();
        cout << "\n";
    }
}; // class List

ostream& operator<<(ostream& os, const List& lst) {  
    os << lst.to_string();
    return os;
} 

void test1() {
    List lst;
    for(int i = 1; i <= 10; ++i) lst.push(i);

    lst.println();
}

void test2() {
    for(int i = 0; i < 10; ++i) {
        List lst;
        for(int j = 1; j <= i; ++j) {
            lst.push(j);
        }
        assert(lst.size() == i);
        lst.println();
    }
}

void test3() {
    List lst;
    lst.println();
    for(int i = 0; i < 10; ++i) {
        lst.push_back(i + 1);
        lst.println();
    }
    
    cout << "\n";

    while (!lst.is_empty()) {
        int result = lst.pop_back(); 
        cout << lst << "   " << result << " popped\n";
    }
}

int main() {
    // test1();
    // test2();
    test3();
}
