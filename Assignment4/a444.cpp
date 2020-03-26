//a4.cpp
/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : Chen Zhao
// St.# : 301308092
// Email: cza94@sfu.ca
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
#include <iostream>
#include <vector>
#include <algorithm>
#include "cmpt_error.h"
#include "Priority_queue.h"
#include <stdlib.h>
#include <time.h>

using namespace std;

int count=0;

class Selectionsort: public Priority_queue  {
private: 
    struct node{
        int num;
        node* next;
        node* pre;
    };

    node* root;
    node* tail;

public:
    Selectionsort(){
        root=nullptr;
        tail=nullptr;
    }
    // C++ base classes should always provide a virtual destructor so that
    // deriving classes can over-ride if they need to.
    ~Selectionsort() {
        if(root==nullptr){
            return;
        }
        else{
            while(root!=nullptr){
                node* temp = root;
                root=root->next;
                delete temp;
            }
            return;
        }
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    Returns true if there are 0 items in this priority queue.
    bool empty() const{
        if(root==nullptr){
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
    void insert(int x){
        if(root!=nullptr){
            node* temp = root;
            while(temp!=nullptr){
                if(temp->num==x){
                    return;
                }
                else{
                    temp=temp->next;
                }
            }
            node* element = new node{x,nullptr,nullptr};
            tail->next=element;
            element->pre=tail;
            tail=tail->next;
        }
        else{
            node* element = new node{x,nullptr,nullptr};
            root=element;
            tail=element;
        }
    }

    // Pre-condition:
    //    !empty()
    // Post-condition:
    //    Removes and returns the smallest element from this priority queue.
    int pop_min(){
        int smallest = 0;
        if(root==nullptr){
            cmpt::error("nothing in the linked list");
        }
        else{
            smallest = root->num;
            node* temp = root;
            node* target = root;
            while(temp!=nullptr){
                if(temp->num<smallest){
                    smallest=temp->num;
                    target=temp;
                }
                temp=temp->next;
            }
            if(target==root){
                root=root->next;
                delete target;
                // return smallest;
            }
            else if(target==tail){
                tail=tail->pre;
                delete target;
                // return smallest;
            }
            else if(target!=root && target!=tail){
                target->next->pre=target->pre;
                target->pre->next=target->next;
                delete target;
                // return smallest;
            }
        }
        return smallest;
    }

    int size(){
        int count = 0;
        if(root == nullptr){
            return count;
        }
        else{
            node* tmp = root;
            while(tmp != nullptr){
                tmp = tmp->next;
                count++;
            }
            return count;
        }
    }

};

class Insertionsort: public Priority_queue {
private: 
    struct node{
        int num;
        node* next;
        node* pre;
    };

    node* root;
    node* tail;

public:
    Insertionsort(){
        root=nullptr;
        tail=nullptr;
    }
    // C++ base classes should always provide a virtual destructor so that
    // deriving classes can over-ride if they need to.
    ~Insertionsort() {
        if(root==nullptr){
            return;
        }
        else{
            while(root!=nullptr){
                node* temp = root;
                root=root->next;
                delete temp;
            }
            return;
        }
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    Returns true if there are 0 items in this priority queue.
    bool empty() const{
        if(root==nullptr){
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
    void insert(int x){
        if(root!=nullptr){
            node* temp = root;
            while(temp->num<=x){
                if(temp->num==x){
                    return;
                }
                else{
                    temp=temp->next;
                    if(temp==nullptr){
                        node* element = new node{x,nullptr,tail};
                        tail->next=element;
                        tail=tail->next;
                        return;
                    }
                }
            }
            if(temp!=root){
                node* element = new node{x,temp,temp->pre};
                temp->pre->next=element;
                temp->pre=element;
            }
            else{
                node* element = new node{x,root,nullptr};
                root=element;
            }
        }
        else{
            node* element = new node{x,nullptr,nullptr};
            root=element;
            tail=element;
        }
    }

    // Pre-condition:
    //    !empty()
    // Post-condition:
    //    Removes and returns the smallest element from this priority queue.
    int pop_min(){
        if(root==nullptr){
            cmpt::error("nothing in the linked list");
        }
        else{
            node* temp = root;
            root=root->next;
            int num=temp->num;
            delete temp;
            return num;
        }
    }

};

class Heapsort: public Priority_queue {
private: 
	vector<int> vec;
    int heap_size;

public:

    void swap(int *x, int *y) { 
	    int temp = *x; 
	    *x = *y; 
	    *y = temp; 
	}

    // Pre-condition:
    //    none
    // Post-condition:
    //    Returns true if there are 0 items in this priority queue.
    bool empty() {
    	return vec.empty();
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    Puts x into this priority queue. If x is already in the priority
    //    queue, then nothing is added (i.e. duplicates are not allowed).
    void insert(int x){

		heap_size++;
		int i = heap_size - 1;
		vec[i]=x;
		while(i!=0 && vec[(i-1)/2]>vec[i]){
			swap(&vec[i],&vec[(i-1)/2]);
			i = (i-1)/2;
    	}
    }


    // Pre-condition:
    //    !empty()
    // Post-condition:
    //    Removes and returns the smallest element from this priority queue.
    int pop_min(){
    	if(heap_size==1){
    		heap_size--;
    		return vec[0];
    	}
    	int root = vec [0];
    	vec[0]=vec[heap_size-1];
    	heap_size--;
    	heaplify(0);
    	return root;
    }

    void heaplify(int i) { 
	    int l = 2*i + 1; 
	    int r = 2*i + 2; 
	    int smallest = i; 
	    if (l < heap_size && vec[l] < vec[i]) 
	        smallest = l; 
	    if (r < heap_size && vec[r] < vec[smallest]) 
	        smallest = r; 
	    if (smallest != i) 
	    { 
	        swap(&vec[i], &vec[smallest]); 
	        heaplify(smallest); 
	    } 
	} 

};


void generateData(vector<int>& v, int count)
{
    srand(time(NULL));
    v.clear();
    for(int i = 0; i < count; ++i)
    {
        int tmp = rand() % RAND_MAX;
        v.push_back(tmp);
    }
}

// int main(){
// 	int myints[] = {16,2,77,29};
// 	vector<int> v;
// 	v.push_back(2);
// 	for(int i =0;i<5;i++){
// 		v[i]=myints[i];
// 	}
// 	Selectionsort d;
// 	d.insert(v[1]);
// 	d.insert(v[2]);	
// 	d.insert(v[3]);
// 	d.insert(v[4]);
// 	d.insert(v[0]);
// 	int aa=d.pop_min();
// 	cout << aa << endl;
// }

// int main ()
// {
//    vector<int> v;
//    vector<int> temp;
//    vector<int> countV;
//    Selectionsort d;
//    for(int i = 5000; i <= 100000; i+=5000)
//    {
//       generateData(v, i);
//       temp.resize(i);
//       copy(v.begin(), v.end(), temp.begin());
//       for(int j=0;j<i;j++){
//       	d.insert(temp[j]);
//       }
//       for(int n=0;n<i;n++){
//       	temp[n]=d.pop_min();
//       }

//       countV.push_back(::count);
//       ::count = 0;
//    }
//    for(int i = 0; i < 4; ++i)
//    {
//       switch(i)
//       {
//          case 0:
//              cout << "Insertion Sort: " << endl;
//              break;
//          case 1:
//              cout << "Selection Sort: " << endl; 
//              break;
//          case 2:
//              cout << "Heap Sort: " << endl;
//              break;
//          case 3:
//              cout << "STL Sort: " << endl;
//              break;
//       }
//       for(int j = 0; j < 20; ++j)
//          cout << countV[4 * j + i] << " ";
//       cout << endl;
//    }
//    return 0;
// }


void Selection_sort(vector<int>& v){
    Selectionsort pqueue;
    int tmp_count = 0;
    int Selection_count = 0; 

    for(int i = 0; i < v.size(); i++){
        pqueue.insert(v[i]);
    }
    for(int i = 0; i < v.size(); i++){
        v[i] = pqueue.pop_min();
        tmp_count = pqueue.size();
        Selection_count = Selection_count + tmp_count;
    }
    cout << "Selection sort comparisons: " << Selection_count << endl;
}


// void Insertion_sort(vector<int>& v){

// }


int main(){
    vector<int> v;
    for(int i = 0; i < 10; i++){
        v.push_back(rand()%1000);
    }
    // v.push_back(1);
    Selection_sort(v);
    return 0;
}
