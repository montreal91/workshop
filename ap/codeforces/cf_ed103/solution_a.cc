
//
// Author: montreal91
// Type: contest
// Time: 00:39
// Failed attempts: 2
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

LL get_next_good(LL n, LL k) {
  if (n % k == 0 || k == 1) {
    return k;
  }
  return n + k - n % k;
}

LL get_max_min(LL n, LL k) {
  LL sum = get_next_good(n, k);
  LL base = sum / n;
  if (sum % n > 0) {
    base++;
  }
  return base;
}


void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);
  LL t;
  LL n, k;
  in >> t;
  for (int i=0; i<t; i++) {
    in >> n >> k;
    out << get_max_min(n, k) << endl;
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
