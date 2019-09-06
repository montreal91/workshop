
//
// Problem: https://codeforces.com/contest/1204/problem/A
// Author: montreal91
// Type: training
// Time: 01:18
// Date: 2019.09.06
// Failed attempts: 4
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

const char ONE = '1';
const char ZERO = '0';

long double logarithm(long double base, long double x) {
  return log(x) / log(base);
}

int missed_trains(const string& s) {
  if (s == "0") {
    return 0;
  }

  int ones = 0;
  for (char c : s) {
    if (c == ONE) {
      ones++;
    }
  }
  if (ones == 1) {
    // It's a power of 2 or four
    return s.size() / 2;
  }
  return (s.size() - 1) / 2 + 1;
}

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);
  string s;
  in >> s;

  out << missed_trains(s) << endl;
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
