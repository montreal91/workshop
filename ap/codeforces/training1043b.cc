
//
// Problem: https://codeforces.com/contest/1043/problem/B
// Author: montreal91
// Date: 30.11.2018
// Type: training
// Time: None
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

bool can_generate(const vector<int>& a, const vector<int>& x, int k) {
  for (auto i=1; i<a.size(); i++) {
    if (a[i] != a[i-1] + x[(i-1) % k]) {
      return false;
    }
  }
  return true;
}

template<typename T>
T remainder(T x, T k) {
  return static_cast<T>(x % k > 0);
}

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);

  int n;
  in >> n;

  vector<int> A;
  A.resize(n);

  for (auto i=0; i< n; i++) {
    in >> A[i];
  }

  A.insert(A.begin(), 0);
  debug_print(A);

  vector<int> d;
  d.resize(n);

  for (int i = 0; i < n; i++) {
    d[i] = A[i+1] - A[i];
  }

  debug_print(d);
  
  int k = 0;
  vector<int> res;
  for (k=1; k<=n; k++) {
    if (can_generate(A, d, k)) {
      res.push_back(k);
    }
  }

  out << res.size() << endl;
  for (auto r : res) {
    out << r << " ";
  }
  out << endl;
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
