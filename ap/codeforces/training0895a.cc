
//
// Problem: https://codeforces.com/contest/895/problem/A
// Author: montreal91
// Type: training
// Time: 00:52
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

const int DEGREES = 360;

int calculate_min_differencr(const vector<int>& v) {
  int min_delta = DEGREES;
  if (v.size() == 1) {
    return min_delta;
  }
  if (v.size() == 2) {
    return abs(v[0] - v[1]);
  }
  for (int i=0; i<v.size(); i++) {
    int psum = 0;
    for (int j=i; j<v.size(); j++) {
      if (psum + v[j] < DEGREES / 2) {
        psum += v[j];
      }
      else if (psum + v[j] == DEGREES / 2) {
        return 0;
      }
      else {
        // Decide wether it is good to add current slice or not.
        int with_j = psum + v[j];
        int without_j = psum;
        if (abs(DEGREES / 2 - with_j) <= abs(DEGREES / 2 - without_j)) {
          psum = with_j;
        }
        break;
      }
    }
    min_delta = min(min_delta, abs(DEGREES / 2 - psum) * 2);
  }
  return min_delta;
}

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);

  int n;
  in >> n;
  vector<int> slices;
  slices.resize(n);

  for (int i=0; i<n; i++) {
    in >> slices[i];
  }
  debug_print(slices);
  out << calculate_min_differencr(slices) << endl;
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
