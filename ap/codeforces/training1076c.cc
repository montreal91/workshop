
//
// Problem: https://codeforces.com/contest/1076/problem/C
// Author: montreal91
// Date: 28.11.2018
// Type: training
// Time: 00:21
// Failed attempts: 0
//

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <iomanip>
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

long double get_b(int gd) {
  if (gd == 0) {
    return 0.0;
  }
  if (gd < 4) {
    return -1.0;
  }

  auto d = static_cast<long double>(gd);
  auto b = (d + sqrt(d * d - 4 * d)) / 2;
  return b;
}

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);
  int t;
  in >> t;
  int in_d = 0;

  for (auto i=0; i<t; i++) {
    in >> in_d;
    auto b = get_b(in_d);
    if (b < 0) {
      out << "N" << endl;
      continue;
    }
    out << "Y ";
    out << setprecision(15) << b << " ";
    out << setprecision(15) << static_cast<long double>(in_d) - b << endl;
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
