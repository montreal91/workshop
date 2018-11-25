
//
// Problem: https://codeforces.com/contest/1023/problem/A
// Author: montreal91
// Date: 24.11.2018
// Type: training
// Time: 00:34
// Failed attempts: 3
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

bool match(const string& s, const string& t) {
  int i=0;
  int ind = -2;
  for (i=0; i<s.size(); i++) {
    if (s[i] == '*') {
      ind = i - 1;
      break;
    }
    if (s[i] != t[i]) {
      return false;
    }
  }
  if (ind == -2 && s.size() != t.size()) {
    return false;
  } 
  int last_s = s.size() - 1;
  int last_t = t.size() - 1;

  for (int j=0; j<s.size(); j++) {
    if (s[last_s-j] == '*') {
      break;
    }
    if (s[last_s-j] != t[last_t-j] || last_t-j == ind) {
      debug_print(s[last_s-j]);
      debug_print(t[last_t-j]);
      return false;
    }
  }
  return true;
  
}

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);

  int n, m;
  in >> n >> m;
  string s, t;
  in >> s >> t;

  if (match(s, t)) {
    out << "YES" << endl;
  }
  else {
    out << "NO" << endl;
  }

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
