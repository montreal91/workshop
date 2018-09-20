
//
// Problem: https://codeforces.com/contest/1037/problem/B
// Author: montreal91
// Solved during the practice.
// Algorithm is straightforward, but has tricky corner cases.
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

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);

  long long n, s;
  in >> n >> s;
  vector<long long> nums;
  nums.resize(n);
  for (long long i=0; i<n; i++) {
    in >> nums[i];
  }

  if (n == 1) {
    out << abs(nums[0] - s) << endl;
    return;
  }

  sort(nums.begin(), nums.end());
  long long i = n / 2;
  long long res = 0;

  if (nums[i] <= s) {
    while (nums[i] < s && i < n) {
      res += abs(nums[i] - s);
      i++;
    }
  }
  else {
    while (nums[i] > s && i >= 0) {
      res += abs(nums[i] - s);
      i--;
    }
  }
#ifndef ONLINE_JUDGE
  out << "Res: ";
#endif // ONLINE_JUDGE
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
