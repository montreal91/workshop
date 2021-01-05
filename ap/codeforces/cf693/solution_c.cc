
//
// Problem: https://codeforces.com/contest/1472/problem/C
// Author: montreal91
// Type: contest
// Time: 00:40
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

#ifndef ONLINE_JUDGE
  #include "util.h"
#endif // ONLINE_JUDGE

using namespace std;


typedef long long LL;

class Decker {
public:
  Decker(const vector<LL>& input) : inpt(input) {
    // inpt(input);
    init_sums();
  }

  LL get_best() {
    for (int i=sums.size() - 1; i >= 0; i--) {
      get_score(i);
    }
    // debug_print(sums);
    return *max_element(sums.begin(), sums.end());
  }

  LL get_score(int pos) {
    if (sums[pos] >= 0) {
      return sums[pos];
    }
    if (pos + inpt[pos] >= inpt.size()) {
      sums[pos] = inpt[pos];
      return sums[pos];
    }
    sums[pos] = inpt[pos] + get_score(pos + inpt[pos]);
    return sums[pos];
  }

private:
  vector<LL> inpt;
  vector<LL> sums;

  void init_sums() {
    sums.resize(inpt.size());
    for (int i=0; i<sums.size(); i++) {
      sums[i] = -1;
    }
  }
};

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);
  int t, n;
  vector<LL> A;
  in >> t;
  for (int i=0; i<t; i++) {
    in >> n;
    A.resize(n);
    for (int j=0; j<n; j++) {
      in >> A[j];
    }
    Decker d(A);
    out << d.get_best() << endl;
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
