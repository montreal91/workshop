
#pragma once

#include <string>
#include <vector>


using namespace std;


template<typename T>
void debug_print(T val, const string& label="") {
  string separator;
  if (label.size() == 0) {
    separator = "";
  }
  else {
    separator = " ";
  }
  cout << label << separator << val << endl;
}

template<typename T>
void debug_print(
  const vector<T>& to_print,
  const string& separator=" ",
  const string& label=""
) {
  for (T p : to_print) {
    cout << p << separator;
  }
  cout << endl;
}
