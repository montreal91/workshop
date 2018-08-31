
//
// Problem: https://codeforces.com/contest/1015/problem/D
// Author: montreal91
// Solved during training in 0:15
//

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <utility>
#include <map>

using namespace std;

bool test_chars(char a, char b) {
  bool c1 = a - 1 == b - 1;
  bool c2 = a - 1 == b + 1;
  bool c3 = a + 1 == b - 1;
  bool c4 = a + 1 == b + 1;
  return c1 || c2 || c3 || c4;
}

bool test_string(const string& s) {
  for (auto i=0; i<s.size()/2; i++) {
    auto mi = s.size() - i - 1;
    if (!test_chars(s[i], s[mi])) {
      return false;
    }
  }
  return true;
}

void function(istream& in, ostream& out) {
  int T;
  in >> T;
  for (auto i=0; i<T; i++) {
    int n;
    string s;
    in >> n >> s;
    if (test_string(s)) {
      out << "YES" << endl;
    }
    else {
      out << "NO" << endl;
    }
  }
}

int main() {
  ifstream in("data/a.in");
  function(cin, cout);
  return 0;
}
