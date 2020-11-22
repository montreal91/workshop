
//
// Problem: https://codeforces.com/contest/1451/problem/B
// Author: montreal91
// Type: contest
// Time: 00:53
// Failed attempts: 0
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

bool test_query(const string& s, int a, int b) {
  auto subs = s.substr(a, b - a + 1);
  for (int i=a-1; i>=0; i--) {
    if (s[i] == s[a]) {
      return true;
    }
  }

  for (int i=b+1; i<s.size(); i++) {
    if (s[i] == s[b]) {
      return true;
    }
  }
  return false;
}

string verbose(bool b) {
  if (b) {
    return "YES";
  }
  return  "NO";
}

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);
  int t, n, q, l, r;
  in >> t;

  string s;
  for (int i=0; i<t; i++) {
    in >> n >> q;
    in >> s;
    for (int j=0; j<q; j++) {
      in >> l >> r;
      out << verbose(test_query(s, l-1, r-1)) << endl;
    }
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
