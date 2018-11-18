
//
// Problem: https://codeforces.com/contest/1038/problem/C
// Author: montreal91
// Comment
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

template <typename T>
void print_list(const vector<T>& list, ostream& out) {
  for (auto& l : list) {
    out << l << " ";
  }
  out << endl;
}

bool should_pick_my(const vector<int>& my, const vector<int>& other) {
  if (other.empty()) {
    return true;
  }
  if (my.empty()) {
    return false;
  }
  return my[my.size() - 1] >= other[other.size() - 1];
}

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);

  int n;
  in >> n;

  vector<int> vals_a;
  vals_a.resize(n);

  vector<int> vals_b;
  vals_b.resize(n);

  for (auto i=0; i<n; i++) {
    in >> vals_a[i];
  }
  for (auto i=0; i<n; i++) {
    in >> vals_b[i];
  }
  sort(vals_a.begin(), vals_a.end());
  sort(vals_b.begin(), vals_b.end());

  long long sum_a = 0, sum_b = 0;


  for (auto i=0; i<2 * n; i++) {
    if (i % 2 == 0) {
      // Player A's action;
      if (should_pick_my(vals_a, vals_b)) {
        sum_a += vals_a[vals_a.size() - 1];
        vals_a.pop_back();
      } else {
        vals_b.pop_back();
      }
    }
    else {
      // Player B's action;
      if (should_pick_my(vals_b, vals_a)) {
        sum_b += vals_b[vals_b.size() - 1];
        vals_b.pop_back();
      }
      else {
        vals_a.pop_back();
      }
    }
  }
  out << sum_a - sum_b << endl;
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
