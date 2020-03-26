// Priority_queue.h

#include "cmpt_error.h"
#include <algorithm>
// #include <vector>
// #include <deque>
#include <iostream>

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
	// Priority_queue(){
	// 	head = nullptr;
	// }
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
    	// cout << "insert" << endl;
    	int state = 0;
    	Node* tmp = head;
    	if(head == nullptr){
    		Node* newnode = new Node{x, nullptr, nullptr};
    		head = newnode;
    		state = 1;
    	}
    	tmp = head;
    	while(tmp->next != nullptr && state == 0){
    		if(tmp->value == x){
    			state = 1;
    		}
    		tmp = tmp->next;
    	}
    	if(tmp->value == x && state == 0){
    		state = 1;
    	}
    	if(state == 0){
    		Node* newnode = new Node{x, nullptr, nullptr};
    		tmp->next = newnode;
    		newnode->prev = tmp;
    		state = 1;
    	}
    	// cout << "insert" << endl;
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
    	
    		if(head->next == nullptr){
    			// int ss = 0;
    			ss = head->value;
    			delete head;
    			head = nullptr;
    			// return ss;
    		}
    		else{
    			Node* tmp = head;
    		    Node* sv = head;
    	    	while(tmp != nullptr){
    	    		if(tmp->value < sv->value){
    	    			sv = tmp;
    	    		}
    	    		tmp = tmp->next;
    	    	}
    	    	if(sv->prev == nullptr){
    	    		ss = sv->value;
    	    		head = sv->next;
    	    		sv->next->prev = nullptr;
    	    		delete sv;
    	    		// return ss;
    	    	}
    	    	else if(sv->next == nullptr){
    	    		ss = sv->value;
    	    		sv->prev->next = nullptr;
    	    		delete sv;
    	    		// return ss;
    	    	}
    	    	else{
    	    		ss = sv->value;
    	    	    sv->next->prev = sv->prev;
    	    	    sv->prev->next = sv->next;
    	    	    delete sv;
    	    	    // return ss;
    	    	}
    		}
    	}
    	return ss;
    }


    // virtual int size(){
    // 	int count = 0;
    // 	if(head == nullptr){
    // 		return count;
    // 	}
    // 	else{
    // 		Node* tmp = head;
    // 		while(tmp != nullptr){
    // 			tmp = tmp->next;
    // 			count++;
    // 		}
    // 		return count;
    // 	}
    // }
    
}; // class Priority_queue