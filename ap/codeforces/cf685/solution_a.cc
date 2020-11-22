
//
// Problem: https://codeforces.com/contest/1451/problem/A
// Author: montreal91
// Type: contest
// Time: 00:23
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

typedef long long LL;

void solve_n(ostream& out, LL n){
  if (n == 1) {
    out << 0 << endl;;
    return;
  }
  if (n == 2) {
    out << 1 << endl;;
    return;
  }
  if (n == 3) {
    out << 2 << endl;;
    return;
  }
  if (n % 2 == 0) {
    out << 2 << endl;;
  }
  else {
    out << 3 << endl;;
  }
}

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);
  LL t, n;
  in >> t;
  for (int i=0; i<t; i++) {
    in >> n;
    solve_n(out, n);
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
