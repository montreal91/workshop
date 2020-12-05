
//
// https://codeforces.com/contest/1140/problem/A
// Author: montreal91
// Type: training
// Time: 00:24
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
#include <unordered_set>
#include <utility>
#include <vector>

#ifndef ONLINE_JUDGE
  #include "util.h"
#endif // ONLINE_JUDGE

using namespace std;

bool contains(unordered_set<int> u, int i) {
  auto search = u.find(i);
  return search != u.end();
}

int solve(const vector<int>& v) {
  unordered_set<int> K;
  int c = 0;
  for (int i=0; i<v.size(); i++) {
    K.insert(v[i]);
    if (contains(K, i+1)) {
      K.erase(i+1);
    }

    if (K.size() == 0) {
      c++;
    }
  }
  return c;
}


void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);

  int n;
  vector<int> v;
  in >> n;
  v.resize(n);
  for (int i=0; i<n; i++) {
    in >> v[i];
  }
  out << solve(v) << endl;
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
