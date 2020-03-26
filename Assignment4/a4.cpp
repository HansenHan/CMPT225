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

#include "Priority_queue.h"
#include "cmpt_error.h"
#include <algorithm>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h> 

using namespace std;




// class Priority_queue {
class Selectionsort: public Priority_queue { //class for selection sort
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
 //    // C++ base classes should always provide a virtual destructor so that
 //    // deriving classes can over-ride if they need to.
 //    ~Priority_queue(){
 //    	while(head != nullptr){
 //            Node* tmp = head;
 //            head = head->next;
 //            delete tmp;
 //        }
 //    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    Returns true if there are 0 items in this priority queue.
    bool empty() const{
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
    void insert(int x){  //inert number in the end of the priority queue
    	int state = 0;
    	Node* tmp = head;
    	if(head == nullptr){  //queue is empty
    		Node* newnode = new Node{x, nullptr, nullptr};
    		head = newnode;
    		state = 1;
    	}
    	tmp = head;
    	while(tmp->next != nullptr && state == 0){ //chearch if the number is already in the queue
    		if(tmp->value == x){
    			state = 1;
    		}
    		tmp = tmp->next;
    	}
    	if(tmp->value == x && state == 0){
    		state = 1;
    	}
    	if(state == 0){  //when state == 0 means the number is not in the queue
    		             //insert the number in the queue
    		Node* newnode = new Node{x, nullptr, nullptr};
    		tmp->next = newnode;
    		newnode->prev = tmp;
    		state = 1;
    	}
    }

    // Pre-condition:
    //    !empty()
    // Post-condition:
    //    Removes and returns the smallest element from this priority queue.
    int pop_min(){

    	int ss = 0;

    	if(head == nullptr){ //empty queue
    		cmpt::error("list is empty");
    	}
    	else{
    	
    		if(head->next == nullptr){ //only one number in the queue
    			ss = head->value;
    			delete head;
    			head = nullptr;
    		}
    		else{
    			Node* tmp = head;
    		    Node* sv = head;
    	    	while(tmp != nullptr){
    	    		if(tmp->value < sv->value){ //find the min number in the queue
    	    			sv = tmp;
    	    		}
    	    		tmp = tmp->next;
    	    		// Selectionsort_count++;
    	    		// cout << Selectionsort_count << endl;
    	    	}
    	    	if(sv->prev == nullptr){  //pop the nu,ber
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

    int size(){
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
    
}; // class Priority_queue for Selection


unsigned long int Insertion_count = 0;
// class Priority_queue {
class Insertionsort: public Priority_queue  {
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
 //    // C++ base classes should always provide a virtual destructor so that
 //    // deriving classes can over-ride if they need to.
 //    ~Priority_queue(){
 //    	while(head != nullptr){
 //            Node* tmp = head;
 //            head = head->next;
 //            delete tmp;
 //        }
 //    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    Returns true if there are 0 items in this priority queue.
    bool empty() const{
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
    void insert(int x){ //insert the number in order 
    	int state = 0;
    	Node* tmp = head;
    	if(head == nullptr){ //empty queue
    		Node* newnode = new Node{x, nullptr, nullptr};
    		head = newnode;
    		state = 1;
            // tmp = head;
    	}
        tmp = head;
    	while(tmp->next != nullptr && state == 0){  //find the position to insert the number
    		// Insertion_count++;
    		if(tmp->value < x){
    			tmp = tmp->next;

    			//Insertion_count++;
    		}
    		else if(tmp->value == x){
                state = 1;
                // Insertion_count++;
            }
            else{    //insert the number
                if(tmp->prev == nullptr){
                    Node* newnode = new Node{x, nullptr, nullptr};
                    newnode->next = tmp;
                    tmp->prev = newnode;
                    head = newnode;
                    state = 1;
                    // Insertion_count++;
                }
                else{
                    Node* newnode = new Node{x, nullptr, nullptr};
                    newnode->next = tmp;
                    newnode->prev = tmp->prev;
                    tmp->prev->next = newnode;
                    tmp->prev = newnode;
                    state = 1;
                    // Insertion_count++;
                }
            }
            Insertion_count++;
            // cout << Insertion_count << endl;
    	}
    	if(tmp->value < x && state == 0){  //check the last the numer
    		Node* newnode = new Node{x, nullptr, nullptr};
            tmp->next = newnode;
            newnode->prev = tmp;
            state = 1;
            Insertion_count++;
    	}
        if(tmp->value == x && state == 0){
            state = 1;
            Insertion_count++;
        }
    	if(tmp->value > x && state == 0){
    		if(tmp->prev == nullptr){
    			Node* newnode = new Node{x, nullptr, nullptr};
    			newnode->next = tmp;
    			tmp->prev = newnode;
    			head = newnode;
    			state = 1;
    			Insertion_count++;
    		}
    		else{
                Node* newnode = new Node{x, nullptr, nullptr};
                newnode->next = tmp;
                newnode->prev = tmp->prev;
                tmp->prev->next = newnode;
                tmp->prev = newnode;
                state = 1;
                Insertion_count++;
            }
        }
    }

    // Pre-condition:
    //    !empty()
    // Post-condition:
    //    Removes and returns the smallest element from this priority queue.
    int pop_min(){ //pop the number
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



    int size(){
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


}; // class Priority_queue for Insertion


unsigned long int Heap_count = 0;

class Heapsort :public Priority_queue{ //class for heap sort
private:
    vector<int> vec;
public:
    ~Heapsort(){
        vec.clear();
    }
    bool empty() const{
        return vec.empty();
    }
    
    void insert(int x){//insert the value to the end of the vector
    	bool state = false;
    	for (int i=0; i < vec.size(); i++){
    		if (vec[i] == x){ 
    			state = true;
    		}
    	}
    	if (!state){
            vec.push_back(x);
            int index = vec.size()-1;
            bubbleUp(index); //bubble up to maintain the min heap

        }
    }


    int pop_min(){  //get the min number
        int min = vec[0];
        vec[0] = vec.back();
        vec.pop_back();
        bubbleDown(0);
        return min;
    }


    void bubbleUp(int index) {
        if (index == 0) {
            return;
        }
        int parentIndex = (index - 1) / 2;
        Heap_count++;
        if (vec[parentIndex] > vec[index]) {
            int temp = vec[parentIndex];
            vec[parentIndex] = vec[index];
            vec[index] = temp;
            bubbleUp(parentIndex);
        }
    }
    void bubbleDown(int index) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        if (left >= vec.size()) {   //current is on the leaf
            return;
        }
        int minIndex = index;  //find the min
        Heap_count++;
        if (vec[right] < vec[left]) {
            minIndex = right;
        }
        else{
        	minIndex = left;
        }
        Heap_count++;
        if(vec[minIndex] < vec[index]){
        	int temp = vec[minIndex];
            vec[minIndex] = vec[index];
            vec[index] = temp;
            bubbleDown(minIndex);
        }

    }

    int vecsize(){  //get size
    	return vec.size();
    }


}; // class Priority_queue for Heap



// Pre-condition:
//    none
// Post-condition:

//    v is re-arranged into ascending sorted order
// void sort(vector<int>& v) {
//     //
//     // Step 1: put all elements of v into an empty
//     //         priority queue
//     //

//     //
//     // Step 2: remove all elements in PQ and put them back
//     //         into v (from smallest to biggest)
// }


void Selection_sort(vector<int>& v){ // check!!
	Selectionsort pqueue;
	unsigned long int tmp_count = 0;
	unsigned long int Selection_count = 0; 

	for(int i = 0; i < v.size(); i++){  //insert numbers in the queue
		pqueue.insert(v[i]);
	}

	int pqsize = pqueue.size();
	v.resize(pqsize);  //resize the vector
	for(int i = 0; i < pqsize; i++){  //pop all number into the vector
		v[i] = pqueue.pop_min();
		tmp_count = pqueue.size();
		Selection_count = Selection_count + tmp_count;
	}
	cout << "Selection sort comparisons: " << Selection_count << endl;
}



void Insertion_sort(vector<int>& v){
	Insertionsort pqueue;

	for(int i = 0; i < v.size(); i++){ //insert numbers in the queue
		pqueue.insert(v[i]);
	}

	int pqsize = pqueue.size();
	v.resize(pqsize);  //resize the vector
	for(int i = 0; i < pqsize; i++){  //pop all number into the vector
		v[i] = pqueue.pop_min();
	}
	cout << "Insertion sort comparisons: " << Insertion_count << endl;
}


void Heap_sort(vector<int>& v){
	Heapsort pqueue;

	for(int i = 0; i < v.size(); i++){ //insert numbers in the queue
		pqueue.insert(v[i]);
	}

	int pqsize = pqueue.vecsize();
	v.resize(pqsize);   //resize the vector
	for(int i = 0; i < pqsize; i++){  //pop all number into the vector
		v[i] = pqueue.pop_min();
	}
	cout << "Heap sort comparisons: " << Heap_count << endl;
}

unsigned long int STL_count = 0;
void STL_sort(vector<int>& v){

	sort(begin(v), end(v), [](int a, int b) {
    		STL_count++;
    		return a > b; 

    	});
	cout << "STL sort comparisons: " << STL_count << endl;
}




int main(){
	for(int gg = 5000; gg < 100001; gg = gg + 5000){
		cout << "----------sort for " << gg << " ----------" << endl;

		Insertion_count = 0;
		Heap_count = 0;
		STL_count = 0;
		srand((unsigned)time(NULL));


    vector<int> STL_v;
	
	for(int i = 0; i < gg; i++){
		STL_v.push_back(rand() % RAND_MAX);
	}
	STL_sort(STL_v);



	vector<int> selection_v;
	
	for(int i = 0; i < gg; i++){
		selection_v.push_back(rand() % RAND_MAX);
	}
	Selection_sort(selection_v);



    vector<int> insertion_v;

	for(int i = 0; i < gg; i++){
		insertion_v.push_back(rand() % RAND_MAX);
	}
	Insertion_sort(insertion_v);



    vector<int> Heap_v;

    for(int i = 0; i < gg; i++){
		Heap_v.push_back(rand() % RAND_MAX);
	}
	Heap_sort(Heap_v);

	// for(int ii = 0; ii < (Heap_v.size() - 1); ii++){
	// 	if(Heap_v[ii] > Heap_v[ii+1]){
	// 		cout << "error!" << endl;
	// 	}
	// }


    }

	return 0;
}