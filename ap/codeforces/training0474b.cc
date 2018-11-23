
//
// Problem: https://codeforces.com/contest/474/problem/B
// Author: montreal91
// Type: training
// Time: 01:14
// Failed attempts: 1
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

long long get_index(const vector<long long>& piles, long long worm) {
  long long b_left = 0, b_right = piles.size() - 1;
  long long i = (b_left + b_right + 1) / 2;

  while (i > 0 && (worm > piles[i] || worm <= piles[i-1])) {
    i = (b_right + b_left) / 2;
    if (worm > piles[i]) {
      b_left = i + 1;
    }
    else {
      b_right = i;
    }
  }
  return i;
}

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);

  long long n;
  in >> n;

  vector<long long> piles;
  long long delta, last_index = 0;
  for (long long i=0; i < n; i++) {
    in >> delta;
    last_index += delta;
    piles.push_back(last_index);
  }

  long long m;
  in >> m;

  long long worm, res;
  for (long long i=0; i < m; i++) {
    in >> worm;
    res = get_index(piles, worm);
    out << res + 1 << endl;
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
