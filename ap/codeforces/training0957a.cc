
//
// Problem: https://codeforces.com/contest/957/problem/A
// Author: montreal91
// Date: 25.11.2018
// Type: training
// Time: 01:40
// Failed attempts: 1
//

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <limits>
#include <map>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

const char BLANK = '?';
const char CYAN = 'C';
const char MAGENTA = 'M';
const char YELLOW = 'Y';

template<typename T>
void debug_print(T val, const string& label="") {
  #ifndef ONLINE_JUDGE
    string separator;
    if (label.size() == 0) {
      separator = "";
    }
    else {
      separator = " ";
    }
    cout << label << separator << val << endl;
  #endif // ONLINE_JUDGE
}

template<typename T>
void debug_print(
  const vector<T>& to_print,
  const string& separator=" ",
  const string& label=""
) {
  #ifndef ONLINE_JUDGE
    for (T p : to_print) {
      cout << p << separator;
    }
    cout << endl;
  #endif // ONLINE_JUDGE
}

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);

  int n;
  in >> n;
  string s;
  in >> s;
  
  for (int i=1; i<s.size(); i++) {
    if (s[i] == s[i-1] && s[i] != BLANK) {
      out << "NO" << endl;
      return;
    }
  }

  int blanks = 0;
  int pos = 0;

  if (s[0] == BLANK || s[s.size() - 1] == BLANK) {
    out <<  "YES" << endl;
    return;
  }

  for (auto i=1; i< s.size() - 1; i++) {
    if (s[i] != BLANK) {
      continue;
    }

    if (s[i-1] == BLANK || s[i+1] == BLANK || s[i-1] == s[i+1]) {
      out << "YES" << endl;
      return;
    } 
  }
  out << "NO" << endl;
}

int main() {
  #ifndef ONLINE_JUDGE
    using namespace chrono;
    auto time1 = duration_cast<milliseconds>(
      system_clock::now().time_since_epoch()
    );
  #endif // ONLINE_JUDGE

  function(cin, cout);

  #ifndef ONLINE_JUDGE
    auto time2 = duration_cast<milliseconds>(
      system_clock::now().time_since_epoch()
    );
    cout << "Time consumed: " << milliseconds(time2 - time1).count();
    cout << " ms.\n";
  #endif // ONLINE_JUDGE

  return 0;
}
