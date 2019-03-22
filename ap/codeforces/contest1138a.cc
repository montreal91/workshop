
//
// Problem: https://codeforces.com/contest/1138/problem/A
// Author: montreal91
// Type: contest
// Time: 00:31
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
typedef long double ld;

ll get_best_buy(const vector<ll> sushi) {
  typedef pair<ll, ll> ps;
  vector<ps> sequences;

  ll seq = 1;
  for (ll i=1; i<sushi.size(); i++) {
    if (sushi[i] == sushi[i-1]) {
      seq++;
    }
    else {
      sequences.push_back(ps(sushi[i-1], seq));
      seq = 1;
    }
  }

  ll last = sushi.size() - 1;
  if (sushi[last] == sushi[last-1]) {
    // seq++;
    sequences.push_back(ps(sushi[last], seq));
  }
  else {
    sequences.push_back(ps(sushi[last], 1));
  }

  ll best = 0;
  for (ll i=0; i<sequences.size() - 1; i++) {
    best = max(best, min(sequences[i].second, sequences[i+1].second));
  }
  return best * 2;
}

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);

  ll n;
  in >> n;

  vector<ll> sushi_set;
  sushi_set.resize(n);

  for (ll i=0; i<n; i++) {
    in >> sushi_set[i];
  }
  out << get_best_buy(sushi_set) << endl;
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
