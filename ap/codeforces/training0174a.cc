
//
// Problem: https://codeforces.com/contest/174/problem/A
// Author: montreal91
// Date: 01.12.2018
// Type: training
// Time: 00:34
// Failed attempts: 0
//

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <iomanip>
#include <ios>
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
  int a;
  double b;
  in >> a >> b;

  vector<double> cups;
  cups.resize(a);

  for (auto& c : cups) {
    in >> c;
  }
  // sort(cups.begin(), cups.end());
  debug_print(cups);

  // auto maxx= cups[cups.size() - 1];
  auto it = max_element(cups.begin(), cups.end());
  auto max_cup = cups[distance(cups.begin(), it)];

  debug_print(max_cup);
  double deficite = 0.0;

  for (auto c : cups) {
    deficite += max_cup - c;
  }

  if (deficite > b) {
    out << -1 << endl;
    return;
  }

  auto eq = (b - deficite) / a;

  for (auto& c : cups) {
    out << setprecision(10) << fixed << max_cup - c + eq << endl;
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
