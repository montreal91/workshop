
//
// Problem: https://codeforces.com/contest/1121/problem/B
// Author: montreal91
// Type: training
// Time: 02:37
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

typedef long long llt;

llt calculate_invided_kids(vector<llt> sweets) {
  unordered_map<llt, llt> sums;

  for (llt i = 0; i < sweets.size()-1; i++) {
    for (llt j = i + 1; j < sweets.size(); j++) {
      sums[sweets[i] + sweets[j]]++;
    }
  }
  llt res = 0;
  for (auto& pair : sums) {
    if (pair.second > res) {
      res = pair.second;
    }
  }
  return res;
}

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);

  llt n;
  in >> n;
  vector<llt> sweets;
  sweets.resize(n);

  for (llt i=0; i<n; i++) {
    in >> sweets[i];
  }

  // debug_print(sweets);

  out << calculate_invided_kids(sweets) << endl;
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
