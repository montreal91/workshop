
//
// Problem: https://codeforces.com/contest/1475/problem/B
// Author: montreal91
// Type: contest
// Time: 00:48
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

class Checker {
public:
  Checker() {
    int counter = 0;
    vals.resize(125250);
    for (int i=0; i<500; i++) {
      for (int j=0; j<=i; j++) {
        vals[counter] = 2020 * (i-j) + 2021 * j;
        counter++;
      }
    }
  }

  bool check(int num) {
    auto res = find(vals.begin(), vals.end(), num);
    return res != vals.end();
  }

private:
  vector<int> vals;
};

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
  Checker c;
  for (int i=0; i<t; i++) {
    in >> n;
    out << verbose(c.check(n)) << endl;
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
