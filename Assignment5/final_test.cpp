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
    Doubly_linked()
    : head(nullptr), tail(nullptr)
    { }
    
    ~Doubly_linked() {
        while (head != nullptr) {
            Node* p = head;
            head = head->next;
            delete p;
        }
    }

    bool is_empty() const {
        return head == nullptr;
    }

    int size() const {
        int count = 0;
        Node* p = head;
        while (p != nullptr) {
            count++;
            p = p->next;
        }
        return count;
    }

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

    void print() const {
        cout << "[";
        Node* p = head;
        while (p != nullptr) {
            cout << p->val << " ";
            p = p->next;
        }
        cout << "]" << endl;
    }

    void reverse() {
        if(head == nullptr || head->next == nullptr){
            return;
        }
        Node* tmpp = tail;
        Node* tmp = tail;
        while(tmp != nullptr){
            tmpp = tmp->next;
            tmp->next = tmp->prev;
            tmp->prev = tmpp;
            tmp = tmp->next;
        }
        tmpp = tail;
        tail = head;
        head = tmpp;
    }

}; // class List


int main() {
    Doubly_linked lst;
    for(int i = 1; i <= 10; ++i) {
        lst.push_back(i);
    }
    cout << "complete"<< endl;

    lst.print();
    lst.reverse();
    lst.print();
}