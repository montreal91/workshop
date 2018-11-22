
//
// Problem: https://codeforces.com/contest/XXXX/problem/A
// Author: montreal91
// Type: training
// Date: 22.11.2018
// Time: None
// Failed attempts: 2
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
void print_vector(const vector<T>& to_print, const string& separator) {
  #ifndef ONLINE_JUDGE
    for (T p : to_print) {
      cout << p << separator;
    }
    cout << endl;
  #endif // ONLINE_JUDGE
}

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

  int n, a, b, c;
  in >> n >> a >> b >> c;
  vector<int> nums = {a, b, c};
  sort(nums.begin(), nums.end());

  print_vector(nums, " ");
  a = nums[0];
  b = nums[1];
  c = nums[2];

  int res = 0;

  for (int j = 0; j <= n / c; j++) {
    for (int i = 0; i <= n / b; i++) {
      int tmp = n - i * b - j * c;
      if (tmp < 0) {
        break;
      }
      if (tmp % a == 0) {
        tmp = tmp / a + i + j;
        if (tmp > res) {
          res = tmp;
        }
      }
    }
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
