
//
// Problem: https://codeforces.com/contest/1133/problem/C
// Author: montreal91
// Type: training
// Time: 00:20
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

typedef long long ll;
const ll BEST_DIFF = 5;

ll calc_best_team(const vector<ll>& pupils) {
  // Assume pupils are sorted
  ll L = 0;
  ll max_gap = 0;
  for (ll U = L; U < pupils.size(); U++) {
    while (pupils[U] - pupils[L] > BEST_DIFF) {
      L++;
    }
    // debug_print(L);
    ll gap = U - L + 1;
    max_gap = max(max_gap, gap);
  }
  return max_gap;
}

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);

  ll n;
  in >> n;
  vector<ll> pupils;
  pupils.resize(n);
  for (ll i=0; i<n; i++) {
    in >> pupils[i];
  }
  // debug_print(pupils);
  // debug_print("Answer:");
  sort(pupils.begin(), pupils.end());
  out << calc_best_team(pupils) << endl;
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
