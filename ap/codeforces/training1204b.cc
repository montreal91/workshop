
//
// Problem: https://codeforces.com/contest/1204/problem/B
// Author: montreal91
// Type: training
// Time: 00:37
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
  #include "lib/debug.h"
#endif // ONLINE_JUDGE

using namespace std;

typedef long long ll;

ll geom_sum(ll b, ll q, ll n) {
  ll qn = static_cast<ll>(pow(q, n));
  return b * (1ll - qn) / (1ll - q);
}

ll array_min(ll s, ll k) {
  return geom_sum(1, 2, k) + s - k;
}

ll array_max(ll s, ll l) {
  ll best = static_cast<ll>(pow(2, l - 1));
  return geom_sum(1, 2, l) + best * (s - l);
}



void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);

  ll n, k, l;
  in >> n >> k >> l;

  out << array_min(n, k) << " " << array_max(n, l) << endl;
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
