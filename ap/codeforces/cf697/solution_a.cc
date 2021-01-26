
//
// Problem: https://codeforces.com/contest/1475/problem/A
// Author: montreal91
// Type: contest
// Time: 00:23
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


bool is_good(LL n) {
  if (n == 1 || n == 2) {
    return false;
  }

  LL tmp = n;
  while (tmp % 2 == 0) {
    tmp /= 2;
  }
  return tmp > 1;
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
  LL t, n;
  in >> t;
  for (LL i=0; i<t; i++) {
    in >> n;
    out << verbose(is_good(n)) << endl;
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
