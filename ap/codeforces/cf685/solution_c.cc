
//
// Problem: https://codeforces.com/contest/1451/problem/C
// Author: montreal91
// Type: aftercontest
// Time: 00:00
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

const string letters = "abcdefghijklmnopqrstuvwxyz";

string verbose(bool b) {
  if (b) {
    return "Yes";
  }
  return "No";
}

bool validate(const string& one, const string& two, int k) {
  unordered_map<char, int> pool_one, pool_two;
  for (int i=0; i<one.size(); i++) {
      pool_one[one[i]]++;
      pool_two[two[i]]++;
  }

  for (char c : letters) {
    int delta = min(pool_one[c], pool_two[c]);
    pool_one[c] -= delta;
    pool_two[c] -= delta;
  }

  int s1 = 0, s2 = 0;
  for (char c : letters) {
    if (pool_one[c] % k != 0 || pool_two[c] % k != 0) {
      return false;
    }
    s1 += pool_one[c];
    s2 += pool_two[c];
    if (s1 < s2) {
      return false;
    }
  }
  return s1 == s2;
}

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);
  int t;
  in >> t;
  int l, k;
  string one, two;
  for (int i=0; i<t; i++) {
    in >> l >> k >> one >> two;
    out << verbose(validate(one, two, k)) << endl;
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
