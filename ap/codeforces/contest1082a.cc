
//
// Problem: https://codeforces.com/contest/1082/problem/A
// Author: montreal91
// Date: 28.11.2018
// Type: contest
// Time: 00:50
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

template<typename T>
T remainder1(T x, T y) {
  return static_cast<T>(x % y > 0);
}

int go_to(int n, int x, int y, int d) {
  if (x % d == y % d) {
    return abs(x - y) / d;
  }
  if (y % d == 1) {
    int res1 = numeric_limits<int>::max();
    int res2 = numeric_limits<int>::max();
    res1 = (y - 1) / d + (x / d + remainder1(x, d));
    if (n % d == 1) {
      res2 = (n - y) / d + (n - x) / d + remainder1(n - x, d);
    }
    return min(res1, res2);
  }
  if (y % d == n % d) {
    return (n - y) / d + (n - x) / d + remainder1(n - x, d);
  }
  return -1;
}

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);
  int t;
  in >> t;
  int n, x, y, d;

  for (int i=0; i<t; i++) {
    in >> n >> x >> y >> d;
    out << go_to(n, x, y, d) << endl;
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
