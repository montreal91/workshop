
//
// Problem: https://codeforces.com/contest/1133/problem/B
// Author: montreal91
// Type: training
// Time: 02:58
// Failed attempts: 7
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

typedef long long ll;
typedef long double ld;

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

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);

  ll n, k;
  in >> n >> k;
  vector<ll> presents;
  presents.resize(n);
  for (ll i=0; i<n; i++) {
    in >> presents[i];
  }

  vector<ll> remains;
  remains.resize(k);
  for (ll i=0; i<k; i++) {
    remains[i] = 0;
  }

  for (ll i=0; i<n; i++) {
    remains[presents[i] % k]++;
  }

  debug_print(remains);
  ll res = remains[0] / 2 * 2;
  for (ll i = 1; i<k; i++) {
    if (i * 2 == k) {
      res += min(remains[i], remains[k - i]) / 2 * 2;
    }
    else {
      res += min(remains[i], remains[k - i]);
    }
  }

  out << res << endl;
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
