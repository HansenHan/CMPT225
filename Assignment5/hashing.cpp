// hashing.cpp

#include "cmpt_error.h"
#include <iostream>
#include <vector>
#include <cassert>

//
// Simple implementation of a hash table with linear probing.
//

using namespace std;

class Hashtable {
private:
	int cap; // capacity of the table
	int sz;  // # of elements in the table

	enum class State { empty, removed, filled };

	struct Cell {
		string val;
		State state;
	};

	Cell* arr;

	// Simple string hash function that adds the ASCII code of all the
	// characters. Using a polynomial hash function may be better.
	int hash(const string& s) const {
		int h = 0;
		for(char c : s) h += int(c);
		return h;
	}

public:
	Hashtable(int init_cap=101)
	: cap(init_cap), sz(0), arr(new Cell[cap])
	{
		for(int i = 0; i < cap; i++) {
			arr[i] = Cell{"", State::empty};
		}
	}

	~Hashtable() {
		delete[] arr;
	}

	int size() const { return sz; }
	int capacity() const { return cap; }
	double load_factor() const { return double(size()) / capacity(); }

	bool is_empty() const { return size() == 0; }
	bool is_full() const { return size() == capacity(); }

	void put(const string& s) {
		if (is_full()) cmpt::error("table is full");
		int h = hash(s);
		for(int i = 0; ; i++) {
			int loc = (h + i) % cap;
			switch (arr[loc].state) {
				case State::empty:
				case State::removed:
					 arr[loc].val = s;
					 arr[loc].state = State::filled;
					 sz++;
					 return;
				case State::filled:
					 break;				
			} // switch
		} // for
	} // put

	bool find(const string& s) {
		if (is_empty()) return false;
		int h = hash(s);
		for(int i = 0; i < cap; i++) {
			int loc = (h + i) % cap;
			string val = arr[loc].val;
			switch (arr[loc].state) {
				case State::empty:
					 return false;
				case State::filled:
					 if (arr[loc].val == s) return true;
					 break;
				case State::removed:
					 break;
			} // switch
		} // for
		return false;
	} // find

	void remove(const string& s) {
		if (is_empty()) return;
		int h = hash(s);
		for(int i = 0; i < cap; i++) {
			int loc = (h + i) % cap;
			switch (arr[loc].state) {
				case State::empty:
					 return;
				case State::filled:
					 if (s == arr[loc].val) {
					 	 // Uncomment the next statement to delete the string.
					 	 // We leave it out by default since it can be helpful 
					 	 // during debugging to see what values have been removed.
					 	 //
					 	 // arr[loc].val = "";
						 arr[loc].state = State::removed;
						 sz--;
						 return;
					 }
					 break;
				case State::removed:
					 break;
			} // switch	
		} // for
	} // remove

	void print_info() const {
		cout << "load_factor = " << size() << "/" << capacity() 
		                << " = " << load_factor() << "\n";
		for(int i = 0; i < cap; i++) {
			cout << "arr[" << i << "] = \"" << arr[i].val << "\" (";
			switch (arr[i].state) {
				case State::empty: cout << "empty"; break;
				case State::removed: cout << "removed"; break;
				case State::filled: cout << "filled"; break;
			} // switch
			cout << ")\n";
		} // for
	}

}; // class Hashtable

void test1() {
	cout << "Hashing test1 ...\n";
	Hashtable tbl(101);
	// tbl.print_info();

	assert(tbl.size() == 0);
	assert(!tbl.find("needle"));

	vector<string> words = {"apple", "cow", "mouse", "hat", "hats", "pots", "spot"};
	// auto words = {"apple"};
	for(string w : words) tbl.put(w);
	assert(tbl.size() == words.size());
	// tbl.print_info();

	for(string w : words) assert(tbl.find(w));
	assert(tbl.size() == words.size());

	assert(!tbl.find("shoe"));
	assert(!tbl.find("eappl"));
	assert(!tbl.find(""));

	tbl.remove("shoe");
	tbl.remove("eappl");
	tbl.remove("");

	tbl.remove(words.front());
	tbl.remove(words.back());

	for(string w : words) {
		tbl.remove(w);
		assert(!tbl.find(w));
		tbl.put(w);
		assert(tbl.find(w));
	}

	// tbl.print_info();
}

int main() {
	test1();
	cout << "All tests passed!\n";
} // main
