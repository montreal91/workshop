
//
// Problem: https://codeforces.com/contest/1472/problem/B
// Author: montreal91
// Type: contest
// Time: 00:22
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


bool is_good(vector<int>& cands) {
  int ones = 0, twos = 0;
  for (int c : cands) {
    if (c == 1) {
      ones++;
    }
    else if (c == 2) {
      twos++;
    }
  }

  // cout << "ONES: " << ones <<endl;

  if (ones % 2 != 0) {
    return false;
  }
  if (ones == 0 && twos % 2 != 0) {
    return false;
  }
  return true;
}

string verbose(bool b) {
  if (b) {
    return "YES";
  }
  return "NO";
}


void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);
  int t, n;
  in >> t;
  vector<int> cands;

  for (int i=0; i<t; i++) {
    in >> n;
    cands.resize(n);

    for (int j=0; j<n; j++) {
      in >> cands[j];
    }
    // debug_print(cands);
    out << verbose(is_good(cands)) << endl;
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
