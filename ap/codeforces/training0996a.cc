
//
// Problem: https://codeforces.com/problemset/problem/996/A
// Author: montreal91
// Type: training
// Date: 20.11.2018
// Time: 00:45
// Failed attempts: 1
//

#include <algorithm>
#include <chrono>
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
  string separator;
  if (label.size() == 0) {
    separator = "";
  }
  else {
    separator = " ";
  }
  #ifndef ONLINE_JUDGE
    cout << label << separator << val << endl;
  #endif
}

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);

  long long n;
  in >> n;

  vector<long long> bills = {100, 20, 10, 5 ,1};

  long long res = 0;

  for (auto b : bills) {
    auto bills_num = n / b;
    auto cut = bills_num * b;
    res += bills_num;
    n -= cut;
    debug_print(n, "remainder");
  }
  out << res << endl;
}

int main() {
#ifndef ONLINE_JUDGE
  using namespace chrono;
  auto time1 = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
#endif // ONLINE_JUDGE
  function(cin, cout);
#ifndef ONLINE_JUDGE
  auto time2 = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
  cout << "Time consumed: " << milliseconds(time2 - time1).count();
  cout << " ms.\n";
#endif // ONLINE_JUDGE
  return 0;
}
