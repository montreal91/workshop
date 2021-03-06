
//
// Problem: https://codeforces.com/contest/1042/problem/A
// Author: montreal91
// Date: 24.11.2018
// Type: training
// Time: 00:18
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

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);

  long long n, m;
  in >> n >> m;

  vector<long long> benches;
  benches.resize(n);

  for (auto i=0; i<n; i++) {
    in >> benches[i];
  }
  long long max_bench = 0;
  for (auto b : benches) {
    if (b > max_bench) {
      max_bench = b;
    }
  }

  long long gap = 0;
  for (auto b : benches) {
    gap += max_bench - b;
  }

  long long max_k = max_bench + m;
  long long delta = m - gap;
  long long min_k = max_bench;
  if (delta > 0) {
    min_k += delta / n + static_cast<long long>(delta % n > 0);
  }
  out << min_k << " " << max_k << endl;

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
