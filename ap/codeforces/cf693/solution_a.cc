
//
// Problem: https://codeforces.com/contest/1472/problem/A
// Author: montreal91
// Type: contest
// Time: 00:21
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

LL get_max_two(LL n) {
  LL base = 2;
  while (n % base == 0) {
    base *= 2;
  }
  return base / 2;
}

LL get_max_cards(LL w, LL h) {
  return get_max_two(w) * get_max_two(h);
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
  LL t, w, h, n;
  in >> t;
  for (LL i=0; i<t; i++) {
    in >> w >> h >> n;
    out << verbose(get_max_cards(w, h) >= n) << endl;
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
