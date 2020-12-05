
//
// Problem: https://codeforces.com/contest/1438/problem/E
// Author: montreal91
// Type: tutorial
// Time: 00:00
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

LL my_sum(const vector<LL>& nums, int i, int j) {
  LL res = 0;
  for (int c=i+1; c<j; c++) {
    res += nums[c];
  }
  return res;
}

class Keeper {
public:
  void add_pair(int i, int j) {
    good_arrays[convert(i, j)]++;
  }

  int size() const {
    return good_arrays.size();
  }

private:
  unordered_map<string, int> good_arrays;

  bool contains(int i, int j) const {
    auto token = convert(i, j);
    auto f = good_arrays.find(token);
    return f != good_arrays.end();
  }

  string convert(int i, int j) const {
    return to_string(i) + "-" + to_string(j);
  }
};

bool array_is_good(const vector<LL>& nums, LL s, int i, int j) {
  return s == (nums[i] ^ nums[j]);
}

int count_good_arrays(const vector<LL>& nums) {
  Keeper keeper;
  for (int l=0; l<nums.size() - 1; l++) {
    auto two_k_plus1 = bithack_next_pow2(nums[l]);
    auto s = 0;
    for (int r=l+2; s < two_k_plus1 && r < nums.size(); r++) {
      s += nums[r-1];
      if (array_is_good(nums, s, l, r)) {
        keeper.add_pair(l, r);
      }
    }
  }

  for (int r=nums.size() - 1; r>=0; r--) {
    auto two_k_plus1 = bithack_next_pow2(nums[r]);
    auto s = 0;
    for (int l=r-2; s < two_k_plus1 && l >=0; l--)  {
      s += nums[l+1];
      if (array_is_good(nums, s, l, r)) {
        keeper.add_pair(l, r);
      }
    }
  }
  return keeper.size();
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
