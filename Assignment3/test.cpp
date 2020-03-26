
#include <iostream>
#include <string>
#include "a3.h"
using namespace std;

int main()
{
  BST a;
  a.insert("l");
  a.insert("e");
  a.insert("r");
  a.insert("b");
  a.insert("i");
  a.insert("o");
  a.insert("s");
  a.insert("q");
  a.insert("p");

  // a.remove("l");

  a.print_preorder();
  cout << "............." << endl;
  a.print_inorder();
  cout << "............." << endl;
  a.print_postorder();



  int si = a.size();
  cout << si << endl;

  int hi = a.height();
  cout << hi << endl;

  if(a.contains("s")){
  	cout << "True" << endl;
  }
  else{
  	cout << "False" << endl;
  }



}

