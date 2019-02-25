
//
// Problem: https://codeforces.com/contest/1130/problem/A
// Author: montreal91
// Type: training
// Time: 00:22
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

int count_pozitives(const vector<double>& nums) {
  int res = 0;
  for (auto n : nums) {
    if (n > 0) {
      res++;
    }
  }
  return res;
}

int count_negatives(const vector<double>& nums) {
  int res = 0;
  for (auto n: nums) {
    if (n < 0) {
      res++;
    }
  }
  return res;
}

int calc_target(int n) {
  double fract, intp;
  fract = modf(static_cast<double>(n) / 2.0, &intp);
  return n / 2 + static_cast<int>(fract >= 0.5);
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

  int n;
  in >> n;

  vector<double> nums;
  nums.resize(n);

  for (int i=0; i<n; i++) {
    in >> nums[i];
  }

  int positives = count_pozitives(nums);
  int negatives = count_negatives(nums);
  int zeroes = nums.size() - (positives + negatives);

  int target = calc_target(n);

  if (positives >= target) {
    out << 1 << endl;
  }
  else if (negatives >= target) {
    out << -1 << endl;
  }
  else {
    out << 0 << endl;
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
