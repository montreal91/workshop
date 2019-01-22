
//
// Problem: https://codeforces.com/contest/1088/problem/B
// Author: montreal91
// Type: contest
// Time: 00:39
// Failed attempts: 1
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

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);

  long long n, k;
  in >> n >> k;

  vector<long long> nums;
  nums.resize(n);
  for (auto i=0; i<n; i++) {
    in >> nums[i];
  }

  sort(nums.begin(), nums.end());

  vector<long long> distinct_non_zero;
  if (nums[0] > 0) {
    distinct_non_zero.push_back(nums[0]);
  }
  for (auto i=1ll; i<n; i++) {
    if (nums[i] != nums[i-1]) {
      distinct_non_zero.push_back(nums[i]);
    }
  }
  auto dn = min(static_cast<long long>(distinct_non_zero.size()), k);
  out << distinct_non_zero[0] << endl;
  for (auto i=1ll; i<dn; i++) {
    out << distinct_non_zero[i] - distinct_non_zero[i-1] << endl;
  }

  if (k > dn) {
    for (;dn < k; dn++) {
      out << 0 << endl;
    }
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
