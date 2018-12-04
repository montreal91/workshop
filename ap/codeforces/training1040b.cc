
//
// Problem: https://codeforces.com/contest/1040/problem/B
// Author: montreal91
// Date: 04.12.2018
// Type: training
// Time: 01:51
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

int remainder(int a, int b) {
  return static_cast<int>(a % b > 0);
}

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);
  int n, k;
  in >> n >> k;
  auto min_cut = k + 1;
  auto max_cut = k * 2 + 1;

  auto turns = n / max_cut + remainder(n, max_cut);
  out << turns << endl;
  if (n == 1) {
    out << n << endl;
    return;
  }
  if (turns == 2) {
    out << n / 2 - k << " " << n / 2 + k + 1 << endl;
    return;
  }

  vector<int> res;
  auto first_cut = max_cut;
  if (n % max_cut > 0) {
    first_cut = max(n % max_cut, min_cut);
  }
  
  auto start = 1 + first_cut - min_cut;
  
  for (auto i=0; i<n; i+= max_cut) {
    out << start + i << " ";
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
