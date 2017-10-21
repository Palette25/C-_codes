#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
bool take_form_outside = false;
int main(int argc, char* argv[]) {
  if(argc == 2 || argc > 3) {
    cout << "Input Error! Program terminating." << endl;
    return 1;
  }
  string one, two;
  if(argc == 3) {
    one = argv[1];
    two = argv[2];
    take_form_outside = true;
  }
  if(take_form_outside == false) {
    cout << "enter the name of file 1:   ";
    cin >> one;
  }
  ifstream file1(one.c_str());
  if(!file1.is_open()) {
    cout << "No file found! Program terminating."<< endl;
    cin.get();
    cin.get();
    return(1);
  }
  else
    cout << "file 1 loaded." << endl;
  if(take_form_outside == false) {
    cout << "enter the name of file 2:   ";
    cin >> two;
  }
  ifstream file2(two.c_str());
    if(!file2.is_open()) {
    cout << "No file found! Program terminating."<< endl;
    cin.get();
    cin.get();
    return(1);
  }
  else
    cout << "file 2 loaded." << endl;
  stringstream ssr1, ssr2;
  ssr1 << file1.rdbuf();
  ssr2 << file2.rdbuf();
  string first(ssr1.str()), second(ssr2.str());
  int error_count = 0;
  int length = first.size() > second.size() ? second.size() : first.size();
  if(first.size() != second.size()) 
    cout << "It's not even the same size!" << endl;
  for(int i = 0; i < length; i++) {
    if(first[i] == second[i])
      continue;
    else {
      cout << "difference found in charcter " << i + 1 << endl;
      error_count++;
    }
    if(error_count > 10) {
      cout << "Too many differences, keep fixing!" << endl;
    cin.get();
    cin.get();
    return (0);
    }
  }
  cout << "checking complete, " << error_count << "difference(s) found."<< endl;
  cin.get();
  cin.get();
  return 0;
}