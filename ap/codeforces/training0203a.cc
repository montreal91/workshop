
//
// Problem: https://codeforces.com/contest/203/problem/A
// Author: montreal91
// Date: 01.12.2018
// Type: training
// Time: 00:31
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

  int x, t, a, b, d_a, d_b;
  in >> x >> t >> a >> b >> d_a >> d_b;

  if (x == 0) {
    out << "YES" << endl;
    return;
  }

  for (auto i=0; i<t; i++) {
    auto points = a - i * d_a;
    if (x == points) {
      out << "YES" << endl;
      return;
    }
  }

  for (auto i=0; i<t; i++) {
    auto points = b - i * d_b;
    if (x == points) {
      out << "YES" << endl;
      return;
    }
  }

  for (auto i=0; i<t; i++) {
    for (auto j=0; j<t; j++) {
      auto points = max(a - i * d_a, 0);
      points += max(b - j * d_b, 0);
      if (x == points) {
        out << "YES" << endl;
        return;
      }
    }
  }
  out << "NO" << endl;
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
