// a5.cpp

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

//
// You are only allowed to include these files --- don't include anything else!
// If you think it's necessary to include another file, please speak to the
// instructor.
//

#include "cmpt_error.h"
#include <iostream>
#include <string>
#include <fstream>   // for reading/writing text files
#include <sstream>   // for using string streams

using namespace std;

class Hashtable {
private:
	int cap; // capacity of the table
	int sz;  // # of elements in the table
	int mod; // a prime number which smaller than cap

	enum class State { empty, removed, filled };

	struct Cell {
		string val;
		State state;
	};

	Cell* arr;

	// Simple string hash function that adds the ASCII code of all the
	// characters. Using a polynomial hash function may be better.
	int hash(const string& s) const { //hash function; transfer string to integer
		int h = 0;
		// for((char c : s) h += int(c));
		for(int i = 0; i < s.size(); i++){
			h = h + s[i] * (133^i);
		}
		return h;
	}

public:
	Hashtable(int init_cap=101) //5507
	: cap(init_cap), sz(0), mod(init_cap), arr(new Cell[cap])
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

	void put(const string& s) { //add string to hash table
		if (is_full()) cmpt::error("table is full");
		if(s == ""){
			return;
		}
		if(load_factor()>=0.5){
			resize(); //ressize hash table
		}
		int h = hash(s);
		for(int i = 0; ; i++) {
			int loc = (h + (i^2)) % mod;
			switch (arr[loc].state) {
				case State::empty:
				case State::removed:
					arr[loc].val = s; //add string to hash table
					arr[loc].state = State::filled;
					sz++;
					return;
				case State::filled:
					break;
			} // switch
		} // for
	} // put

	int primenum(int min, int max){ //find prime number which between min and max
		                            //pre-request: min is a prime number
		int num = min;
		for(int tmp = (min+1); tmp <= max; tmp++){ //temp number
			for(int j = 2; j < tmp; j++){
				if((tmp % j) == 0){
					break;
				}
				if(j == (tmp-1)){
					num = tmp;
				}
			}
		}
		return num;
	}

	void resize(){ //resize hash table function (double capacity)
		cap = cap * 2;
		sz = 0;
		mod = primenum(mod, cap);
		Cell* newarr = new Cell[cap];
		for(int j = 0; j < cap; j++){
			newarr[j] = Cell{"", State::empty};
		}
		int h = 0;
		int ff = 0;
		
		for(int k = 0; k < (cap/2); k++){
			string s = arr[k].val;
			// if(arr[k].state == State::filled){
			if(s != ""){
				h = hash(s);
				for(int i = 0; ; i++) {
			        int loc = (h + (i^2)) % mod;
			        switch (newarr[loc].state) {
			        	case State::empty:
				        case State::removed:
				        	newarr[loc].val = s;
					        newarr[loc].state = State::filled;
					        sz++;
					        ff = 1;
					        break;
				        case State::filled:
					        break;				
			        } // switch
			        if(ff == 1){
			        	break;
			        }
		        }
		        ff = 0;
			}
		}
		delete[] arr;
		arr = newarr;
	}


	bool find(const string& s) { //check whether the string is in the hash table
		if (is_empty()){
			return false;
		}
		int h = hash(s);
		for(int i = 0; i < cap; i++) {
			int loc = (h + (i^2)) % mod;
			string val = arr[loc].val;
			switch (arr[loc].state) {
				case State::empty:
					return false;
				case State::filled:
					if(arr[loc].val == s){
						return true;
					}
					break;
				case State::removed:
					break;
			} // switch
		} // for
		return false;
	} // find

	bool remove(const string& s) { //remove the string frome hash table
		if (is_empty()) return false;
		int h = hash(s);
		for(int i = 0; i < cap; i++) {
			int loc = (h + (i^2)) % mod;
			switch (arr[loc].state) {
				case State::empty:
					 return false;
				case State::filled:
					 if (s == arr[loc].val) {
					 	 arr[loc].val = "";
						 arr[loc].state = State::removed;
						 sz--;
						 return true;
					 }
					 break;
				case State::removed:
					 break;
			} // switch	
		} // for
		return false;
	} // remove

	void print_info() const { //helping function to debug
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

	string* setwords(){ //return a pointer array which contains every string in the hash table
		                //the first element is the size of array
		string* tmp = new string[sz+1];
		int num = 1;
		stringstream ss;
		ss << sz;
		tmp[0] = ss.str(); //save the size in the first position
		for(int i = 0; i < cap; i++){
			if(arr[i].state == State::filled && num < (sz+1)){
				tmp[num] = arr[i].val;
				num++;
			}
		}
		return tmp;
	}

	void suggest(const string& s){ //suggest function: check is there a similar string in hash table
		for(int i = 0; i < cap; i++){ //loop for every Cell in hash table
			if(arr[i].state == State::filled){
				string tmp = arr[i].val;
				// bool similar = false;
				int tmp_size = tmp.size();
				int s_size = s.size();
				if( abs(tmp_size-s_size) >= 2 ){ //if the string is more or less two letters,
					                             //then it is not similar
					// break;
				}
				else if(tmp.size() == s.size()){  //if the temporary string has the same size with s
					int ff = 0; //number of different letter
					char char1, char2;
					int pos = -1; //position of the first different letter
					              //pos = -1 means no different letter
					for(int j = 0; j < tmp.size() && ff <= 2; j++){
						if(tmp[j] != s[j] && ff == 0){
							ff = 1;
							char1 = tmp[j];
							char2 = s[j];
							pos = j;
						}
						else if(tmp[j] != s[j] && ff == 1){
							if((j == (pos+1)) && (tmp[j] == char2 && s[j] == char1)){
								ff = 2;
							}
							else{ //if the two different letter are not adjacent,
								  //we also set there are more than two different letter
								ff = 3;
							}
						}
						else if(tmp[j] != s[j] && ff == 2){
							ff = 3;
						}
					}
					if(ff <= 2){ //if the temporary string has no more than two different letter,
						         //then it is a similar string
						cout << " " << tmp << endl; //print similar words
					}
				}
				else if(tmp.size() < s.size()){ //the size of temp string is smaller than s
					int pos = -1; //position of the first different letter
					for(int k = 0; k < tmp.size(); k++){
						if(tmp[k] != s[k] && pos < 0){
							pos = k;
							break;
						}
					}
					if(pos < 0){ //no different letter
						         //which means the last letter in s is redundant
						cout << " " << tmp << endl; //print similar words
					}
					else{ //check whether the rest letter is same
						bool same = true;
						for(int l = pos; l < tmp.size(); l++){
							if(tmp[l] != s[l+1]){
								same = false;
							}
						}
						if(same){
							cout << " " << tmp << endl; //print similar words
						}
					}
				}
				else if(tmp.size() > s.size()){ //the size of temp string is bigger than s
					                            //similar skill as top
					int pos = -1;
					for(int m = 0; m < s.size(); m++){
						if(tmp[m] != s[m] && pos < 0){
							pos = m;
							break;
						}
					}
					if(pos < 0){
						cout << " " << tmp << endl; //print similar words
					}
					else{
						bool same = true;
						for(int n = pos; n < s.size(); n++){
							if(tmp[n+1] != s[n]){
								same = false;
							}
						}
						if(same){
							cout << " " << tmp << endl; //print similar words
						}
					}
				}
			}
		}
	}
}; // class Hashtable



int main() {
	cout << "Welcome to SpellCheck Master!" << endl;


  //       int num = 0;   //creat main dic 
  //       for(int i = 0; i < 26; i++){
  //       	for(int j = 0; j < 26; j++){
  //       		for(int k = 0; k < 26; k++){
  //       			char aa = i+97;
  //       			char bb = j+97;
  //       			char cc = k+97;
  //       			num++;
  //       			mainf << aa << bb << cc << " " << endl;
  //       			// mainf << endl;
  //       		}
  //       	}
  //       }


	//read main dic
	Hashtable mainf;
	ifstream mainfile ("maindict.txt");//set maindic hashtable
	if(mainfile.is_open()){
		string aa;
		while(getline(mainfile,aa)){
			mainf.put(aa);
		}
        mainfile.close();
	}

    //read added dic
	Hashtable addf;
	fstream addfile ("addedwords.txt", ios::in);
	if(addfile.is_open()){
		string bb;
		while(getline(addfile,bb)){
			addf.put(bb);
		}
		addfile.close();
	}



	string str1, str2;
	while(1){
		cout << "> ";
	    cin >> str1;
	    if(str1 == "end"||str1 == "quit"||str1 == "stop"||str1 == "done"){ //end command
	    	addfile.open("addedwords.txt", ios::out); //add every string in add hash table to addedwords file
	    	string* ss = addf.setwords();
	    	int sssize = 0;
	    	stringstream sstmp;
	    	sstmp << ss[0];
	    	sstmp >> sssize;
	    	for(int op = 1; op < (sssize+1); op++){
	    		addfile << ss[op] << endl;
	    	}
	    	addfile.close();
	    	// addf.print_info();
	    	return 0;
	    }
	    cin >> str2;


	    if(str1 == "check"){ //check command
	    	// cin >> str2;
	    	if(mainf.find(str2) || addf.find(str2)){
	    		cout << "ok" << endl;
	    	}
	    	else{
	    		cout << "don't know " << str2 << endl;
	    	}
	    }

	    if(str1 == "add"){ //add command
	    	// cin >> str2;
	    	if(addf.find(str2) || mainf.find(str2)){}
	    	else{
	    		addf.put(str2);
	    	    cout << '"' << str2 << '"' << " added to the dictionary" << endl;
	    	}
	    }

	    if(str1 == "remove"){ //remove command
	    	// cin >> str2;
	    	if(mainf.find(str2)){
	    		cout << "can’t remove s: it’s in the main dictionary" << endl;
	    	}
	    	else if(addf.remove(str2)){
	    		cout << '"' << str2 << '"' << " removed" << endl;
	    	}
	    	else{
	    		cout << "can’t remove s: unknown word" << endl;
	    	}
	    }

	    if(str1 == "checkfile"){ //checkfile command
	    	// cin >> str2;
	    	int line_number = 0;
	        ifstream checkfile (str2);
	        if(checkfile.is_open()){
	        	string cc;
	           	while(getline(checkfile,cc)){
	           		line_number++;
			        if(mainf.find(cc) || addf.find(cc)){}
			        else{
			        	cout << cc << " " << line_number << endl; 
			        }
		        }
		        checkfile.close();
	        }
	    }

	    if(str1 == "suggest"){ //suggest command
	    	                   //the rule for suggest words:
	    	                   //1.has a extra letter in string
	    	                   //2.miss a letter in string
	    	                   //3.there is a different letter in string
	    	                   //4.two adjacent letter in inverse order
	    	// cin >> str2;
	    	cout << "Suggested words: " << endl;
	    	addf.suggest(str2);
	    	mainf.suggest(str2);
	    }

	    cout << endl;
	}



	return 0;
} // main
