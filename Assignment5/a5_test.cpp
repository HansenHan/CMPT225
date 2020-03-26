

// a5.cpp

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
 // ...

class dictionary_add {

private:

	int sz;

	int cap;

	enum class State { empty, removed, filled };

	struct node{
	    string key;
	    State state;
	};

	node* arr;

	int hash(const string& s) {
		int time = 0;
		for(int i=0; i<s.length() ;i++){
			time+=s[i];
		}
		return time;
	}

public:

	dictionary_add(){
		sz=0;
		cap=101;
		arr = new node[cap];
		for(int i=0;i<cap;i++){
			arr[i]=node{"",State::empty};
		}
	}

	~dictionary_add(){
		delete[] arr;
	}

	void resize() {

		cap = cap * 2;
		sz=0;

	    node* newArr = new node[cap];

		for(int i=0;i<cap;i++){
			newArr[i]=node{"",State::empty};
		}

	    for(int i =0 ; i<cap/2; i++){
	    	string stri=arr[i].key;
	    	int test=0;
	    	if(stri==""){continue;}
	    	else{
			    int h = hash(stri);
				for(int i = 0;i<cap; i++) {
					int loc = (h + i*i)%cap;
					switch (newArr[loc].state) {
						case State::empty:
						case State::removed:
							 newArr[loc].key = stri;
							 newArr[loc].state = State::filled;
							 sz++;
							 test++;
							 break;
						case State::filled:
							 break;	

					} // switch
					if(test!=0){
						break;
					}	
				} // for
	    	}
	    }

	    delete [] arr;

	    arr = newArr;
	}

	int size() { return sz; }

	int capacity() { return cap; }

	double load_factor() { return double(size()) / capacity(); }

	bool is_empty() { return size() == 0; }

	bool is_full() { return sz==cap; }


	bool add(const string& s) {

		string letter;

		ifstream mainf("maindict.txt");
		
		while(getline(mainf,letter)){
			if(letter==s){
				return false;
			}
		}

		int h = hash(s);
		for(int i = 0;i<cap; i++) {
			int loc = (h + i*i)%cap;
			if(arr[loc].key==s)return false;
			switch (arr[loc].state) {
				case State::empty:
				case State::removed:
					 arr[loc].key = s;
					 arr[loc].state = State::filled;
					 sz++;
					 if(load_factor()>=0.5){
						resize();
					 }

					 return true;
				case State::filled:
					 break;				
			} // switch
		} // for                                                                                                                                                                                                                                                                                                                                                                                                                                                     
		return false;
	} // put



	bool check(const string& s) {
		if (!is_empty()) {
		
			int h = hash(s);
			for(int i = 0; i < cap; i++) {
				int test=0;
				int loc = (h + i*i) % cap;
				string key = arr[loc].key;
				switch (arr[loc].state) {
					case State::empty:
						 test++;
						 break;
					case State::filled:
						 if (arr[loc].key == s) {
						 cout << "ok" << endl;
						 return true;
						 }
						 break;
					case State::removed:
						 break;
				} // switch
				if(test!=0)break;
			} // for
			
		}

		string letter;

		ifstream mainf("maindict.txt");
		
		while(getline(mainf,letter)){
			if(letter==s){
				cout << "ok" << endl;
				return true;
			}
		}
		cout << "don't know " << s << endl;
		return false;
	} // find


	bool remove(const string& s) {
		if (is_empty()){
			string letter;

			ifstream mainf("maindict.txt");
			
			while(getline(mainf,letter)){
				if(letter==s){
					cout << "can't remove " << s <<endl;
					return false;
				}
			}
			cout << "can't remove " << s << ": unknown word" << endl;
			return false;

		}
		else{
			int test=0;
			int h = hash(s);
			for(int i = 0; i < cap; i++) {
				int loc = (h + i*i) % cap;
				switch (arr[loc].state) {
					case State::empty:
						 test++;
						 break;
					case State::filled:
						 if (s == arr[loc].key) {
						 	 // Uncomment the next statement to delete the string.
						 	 // We leave it out by default since it can be helpful 
						 	 // during debugging to see what values have been removed.
						 	 //
						 	 arr[loc].key = "";
							 arr[loc].state = State::removed;
							 sz--;
							 cout << s << " removed" << endl;

							 return true;
						 }
						 break;
					case State::removed:
						 break;
				} // switch	
				if(test!=0)break;
			} // for
			string letter;

			ifstream mainf("maindict.txt");
			
			while(getline(mainf,letter)){
				if(letter==s){
					cout << "can't remove " << s << endl;
					return false;
				}
			}
			cout << "can't remove " << s << ": unknown word" << endl;
			return false;
		}
	}


	bool checkf(const string& s) {
		if (!is_empty()) {
		
			int h = hash(s);
			for(int i = 0; i < cap; i++) {
				int loc = (h + i*i) % cap;
				string key = arr[loc].key;
				switch (arr[loc].state) {
					case State::empty:
						 // cout << "don't know " << s << endl;
						 return false;
					case State::filled:
						 if (arr[loc].key == s) {
						 // cout << "ok" << endl;
						 return true;
						 }
						 break;
					case State::removed:
						 break;
				} // switch
			} // for
		}
		else{return false;} 
		return false;
	} // find



	void print_info() const {
		cout << "load_factor = " << sz << "/" << cap
		                << " = " << double(sz) / cap << "\n";
		for(int i = 0; i < cap; i++) {
			cout << "arr[" << i << "] = \"" << arr[i].key << "\" (";
			switch (arr[i].state) {
				case State::empty: cout << "empty"; break;
				case State::removed: cout << "removed"; break;
				case State::filled: cout << "filled"; break;
			} // switch
			cout << ")\n";
		} // for
	}

};

class dictionary_main {

private:

	int sz;

	int cap;

	enum class State { empty, removed, filled };

	struct node{
	    string key;
	    State state;
	};

	node* arr;

	int hash(const string& s) {
		int time = 0;
		for(int i=0; i<s.length() ;i++){
			time+=s[i];
		}
		return time;
	}

public:

	dictionary_main(){
		sz=0;
		cap=101;
		arr = new node[cap];
		for(int i=0;i<cap;i++){
			arr[i]=node{"",State::empty};
		}
	}

	~dictionary_main(){
		delete[] arr;
	}

	void resize() {

		cap = cap * 2;
		sz=0;

	    node* newArr = new node[cap];

		for(int i=0;i<cap;i++){
			newArr[i]=node{"",State::empty};
		}

	    for(int i =0 ; i<cap/2; i++){
	    	string stri=arr[i].key;
	    	int test=0;
	    	if(stri==""){continue;}
	    	else{
			    int h = hash(stri);
				for(int i = 0;i<cap; i++) {
					int loc = (h + i*i)%cap;
					switch (newArr[loc].state) {
						case State::empty:
						case State::removed:
							 newArr[loc].key = stri;
							 newArr[loc].state = State::filled;
							 sz++;
							 test++;
							 break;
						case State::filled:
							 break;	

					} // switch
					if(test!=0){
						break;
					}	
				} // for
	    	}
	    }

	    delete [] arr;

	    arr = newArr;
	}

	int size() { return sz; }

	int capacity() { return cap; }

	double load_factor() { return double(size()) / capacity(); }

	bool is_empty() { return size() == 0; }

	bool is_full() { return sz==cap; }


	bool add(const string& s) {

		// string letter;

		// ifstream mainf("maindict.txt");
		
		// while(getline(mainf,letter)){
		// 	if(letter==s){
		// 		return false;
		// 	}
		// }

		int h = hash(s);
		for(int i = 0;i<cap; i++) {
			int loc = (h + i*i)%cap;
			if(arr[loc].key==s)return false;
			switch (arr[loc].state) {
				case State::empty:
				case State::removed:
					 arr[loc].key = s;
					 arr[loc].state = State::filled;
					 sz++;
					 if(load_factor()>=0.5){
						resize();
					 }

					 return true;
				case State::filled:
					 break;				
			} // switch
		} // for                                                                                                                                                                                                                                                                                                                                                                                                                                                     
		return false;
	} // put




	bool checkf(const string& s) {
		if (!is_empty()) {
		
			int h = hash(s);
			for(int i = 0; i < cap; i++) {
				int loc = (h + i*i) % cap;
				string key = arr[loc].key;
				switch (arr[loc].state) {
					case State::empty:
						 // cout << "don't know " << s << endl;
						 return false;
					case State::filled:
						 if (arr[loc].key == s) {
						 // cout << "ok" << endl;
						 return true;
						 }
						 break;
					case State::removed:
						 break;
				} // switch
			} // for
		}
		else{return false;} 
		return false;
	} // find






	void print_info() const {
		cout << "load_factor = " << sz << "/" << cap
		                << " = " << double(sz) / cap << "\n";
		for(int i = 0; i < cap; i++) {
			cout << "arr[" << i << "] = \"" << arr[i].key << "\" (";
			switch (arr[i].state) {
				case State::empty: cout << "empty"; break;
				case State::removed: cout << "removed"; break;
				case State::filled: cout << "filled"; break;
			} // switch
			cout << ")\n";
		} // for
	}

};

class Arr{
private:
	string * arr;
	int cap;
	int size;
public:
	Arr(){
		size=0;
		cap=101;
		arr = new string[cap];
		for(int i=0;i<cap;i++){
			arr[i]=string{""};
		}
	}

	~Arr(){
		delete[] arr;
	}

	void resize(){
		cap = cap * 2;

	    string* newArr = new string[cap];

		for(int i=0;i<cap;i++){
			newArr[i]=string{""};
		}

	    for(int i = 0 ; i<size; i++){
	    	string stri=arr[i];
	    	newArr[i]=stri;
	    }

	    delete [] arr;

	    arr = newArr;
	}

	void insert (const string & s){
		if(size==cap-1){resize();}
		arr[size]=s;
		size++;
	}

	int sz(){return size;}

	string get(int i){
		return arr[i];
	}

	void remove(string s){
		for(int i=0;i<size;i++){
			if(arr[i]==s){
				arr[i]="";
				while(i!=size){
					arr[i]=arr[i+1];
					i++;
				}
				size--;
			}
		}
	}


};


// void checkfile (string s, dictionary_main mainf,dictionary_add addf){
// 	ifstream other(s);
// 	int num=0;
// 	if(other.is_open()){
// 		string test;
// 		while(getline(other,test)){
// 			num++;
// 			if(mainf.check(test)||addf.check(test)){
// 				continue;
// 			}
// 			else{
// 				cout << test << " is missplelled at line " << num << endl; 
// 			}

// 		}
// 		other.close();
// 	}
// 	else{
// 		cout << "can't find file " << s << endl;

// 		return;
// 	}
// }

int MIN(int a,int b, int c){
	int temp=a;
	if(temp>b){temp=b;}
	if(temp>c){temp=c;}
	return temp;
}

int edit(string str1,string str2){
	int temp;
	char* c1=&str1[0u];
	char* c2=&str2[0u];
	int length1=sizeof(c1)/sizeof(char);
	int length2=sizeof(c2)/sizeof(char);
	int d[length1][length2];
	for(int i=0;i<=length1;i++){
		for(int j=0;j<=length2;j++){
			d[i][j]=0;
		}
	}
	for(int i=1;i<=length1;i++){
		d[i][0]=i;
	}
	for(int i=1;i<=length2;i++){
		d[0][i]=i;
	}

	for(int i=1;i<=length1;i++){
		for(int j=1;j<=length2;j++){
			if(c1[i]==c2[j])temp=0;
			else{temp=1;}
			d[i][j]=MIN(d[i-1][j]+1,d[i][j-1]+1,d[i-1][j-1]+temp);
		}
	}
	return d[length1][length2];
}





int main(){
	dictionary_add hashtable;
	dictionary_main tbl;

	ifstream mainf("maindict.txt");
	string mainstr;
	while(getline(mainf,mainstr)){
		tbl.add(mainstr);
	}
	mainf.close();
	


	Arr striarr;

	ifstream outfile("addedwords.txt");
	string str;

	while(getline(outfile,str)){
		hashtable.add(str);
		striarr.insert(str);
	}
	outfile.close();


	ofstream infile("addedwords.txt");

	string s,j ;
	cout << "Welcome to Spellcheck Master" << endl;
	while(1){

		cin >> s;
	    if (s == "check")
	    {
	        cin >> j;

	        hashtable.check(j);
	    }
	    if (s == "remove")
	    {
	        cin >> j;
	        if(hashtable.remove(j)){
	        	striarr.remove(j);
	        }
	        
	        

	    }
	    if (s == "add")
	    {

	   
	        cin >> j;
	        if(hashtable.add(j))
	        infile << j << endl;
	        

	    }

	    if(s=="checkfile"){
	    	cin >> j;
	    	ifstream other(j);
	    	int num=0;
	    	if(other.is_open()){
	    		string test;
				while(getline(other,test)){
					num++;
					if(hashtable.checkf(test)||tbl.checkf(test)){
						continue;
					}
					else{
						cout << test << " is missplelled at line " << num << endl; 
					}

				}
				other.close();
	    	}
	    	else{
	    		cout << "can't find file " << s << endl;
	    	}

	    }

	    if(s=="suggest"){
	    	cin>>j;
			string a;
			for(int i=0;i<striarr.sz();i++){
				// if(arr.sz()==0)return;
				a=striarr.get(i);
				if(edit(a,j)<3){
					cout << "Suggested word are " << a <<endl;
				}
			}
			ifstream mainfile("maindict.txt");
			if(mainfile.is_open()){
				while(getline(mainfile,a)){
					if(edit(a,j)<3){
						cout << "Suggested word are " << a <<endl;
					}
				}
			}
		}





	    if(s=="quit"||s=="stop"||s=="end"||s=="done"){
	    	for(int i=0;i<striarr.sz();i++){
				infile << striarr.get(i) << endl;
			}


	    	infile.close();
	    	return 0;
	    }
	}

}