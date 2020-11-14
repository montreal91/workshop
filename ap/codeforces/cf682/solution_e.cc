
//
// Problem: https://codeforces.com/contest/1438/problem/E
// Author: montreal91
// Type: tutorial
// Time: 00:00
// Failed attempts: 0
// Unfinished
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

LL pow2(int pow) {
  return 1 << pow;
}

LL bithack_next_pow2(LL v) {
  LL w = v;
  w--;
  w |= w >> 1;
  w |= w >> 2;
  w |= w >> 4;
  w |= w >> 8;
  w |= w >> 16;
  w++;
  if (v == w) {
    return bithack_next_pow2(v + 1);
  }
  return w;
}

// Inclusive
LL my_sum(const vector<LL>& nums, int i, int j) {
  LL res = 0;
  for (int c=i; c<=j; c++) {
    res += nums[c+1];
  }
  return res;
}

int count_good_arrays(const vector<LL>& nums) {
  unordered_map<int, int> goodies;
  for (int l=0; l<nums.size() - 1; l++) {
    auto two_k_plus1 = bithack_next_pow2(nums[l]);
    for (int r=l+2; r<nums.size(); r++) {
      auto zum = my_sum(nums, l+1, r-1);
      if (zum == (l ^ r)) {
        goodies[l] = r;
      }
    }
  }

  for (int r=nums.size() - 1; r>=0; r++) {

  }
  return goodies.size();
}

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);
  int n;
  in >> n;
  vector<LL> nums;
  nums.resize(n);
  for (int i=0; i<n; i++) {
    in >> nums[i];
  }
  out << count_good_arrays(nums) << endl;
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
