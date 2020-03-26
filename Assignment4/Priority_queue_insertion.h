// Priority_queue.h
// For Insertion
#include "cmpt_error.h"
#include <algorithm>
// #include <vector>
// #include <deque>

using namespace std;

class Priority_queue {
private:
	struct Node{
		int value;
		Node* next;
		Node* prev;
	};
	Node* head;
public:
	Priority_queue(){
		head = nullptr;
	}
    // C++ base classes should always provide a virtual destructor so that
    // deriving classes can over-ride if they need to.
    virtual ~Priority_queue(){
    	while(head != nullptr){
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    Returns true if there are 0 items in this priority queue.
    virtual bool empty() const{
    	if(head == nullptr){
    		return true;
    	}
    	else{
    		return false;
    	}
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    Puts x into this priority queue. If x is already in the priority
    //    queue, then nothing is added (i.e. duplicates are not allowed).
    virtual void insert(int x){
    	int state = 0;
    	Node* tmp = head;
    	if(head == nullptr){
    		Node* newnode = new Node{x, nullptr, nullptr};
    		head = newnode;
    		state = 1;
            tmp = head;
    	}
        tmp = head;
    	while(tmp->next != nullptr && state == 0){
    		if(tmp->value < x){
    			tmp = tmp->next;
    		}
    		else if(tmp->value == x){
                state = 1;
            }
            else{
                if(tmp->prev == nullptr){
                    Node* newnode = new Node{x, nullptr, nullptr};
                    newnode->next = tmp;
                    tmp->prev = newnode;
                    head = newnode;
                    state = 1;
                }
                else{
                    Node* newnode = new Node{x, nullptr, nullptr};
                    newnode->next = tmp;
                    newnode->prev = tmp->prev;
                    tmp->prev->next = newnode;
                    tmp->prev = newnode;
                    state = 1;
                }
            }
    	}
    	if(tmp->value < x && state == 0){
    		Node* newnode = new Node{x, nullptr, nullptr};
            tmp->next = newnode;
            newnode->prev = tmp;
            state = 1;
    	}
        if(tmp->value == x && state == 0){
            state = 1;
        }
    	if(tmp->value > x && state == 0){
            Node* newnode = new Node{x, nullptr, nullptr};
            newnode->next = tmp;
            newnode->prev = tmp->prev;
            tmp->prev->next = newnode;
            tmp->prev = newnode;
            state = 1;
        }
    }

    // Pre-condition:
    //    !empty()
    // Post-condition:
    //    Removes and returns the smallest element from this priority queue.
    virtual int pop_min(){
        int ss = 0;
    	if(head == nullptr){
    		cmpt::error("list is empty");
    	}
    	else{
    		Node* tmp = head;
            ss = tmp->value;
            if(tmp->next == nullptr){
                head = nullptr;
                delete tmp;
            }
            else{
                tmp->next->prev = nullptr;
                head = tmp->next;
                delete tmp;
            }
    	}
        return ss;
    }



    virtual int size(){
    	int count = 0;
    	if(head == nullptr){
    		return count;
    	}
    	else{
    		Node* tmp = head;
    		while(tmp != nullptr){
    			tmp = tmp->next;
    			count++;
    		}
    		return count;
    	}
    }
}; // class Priority_queue