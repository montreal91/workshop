
//
// Problem: https://codeforces.com/contest/1189/problem/B
// Author: montreal91
// Type: training
// Time: 00:51
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

void print_bool(bool val, ostream& out) {
  if (val) {
    out << "YES\n";
  }
  else {
    out << "NO\n";
  }
}

typedef long long ll;


bool perform_magic(const vector<ll> nums, vector<ll>& res) {
  if (nums[0] >= nums[1] + nums[2]) {
    return false;
  }
  vector<size_t> indexes;
  for (size_t i=0; i<nums.size() / 2; i++) {
    indexes.push_back(i);
    indexes.push_back(nums.size() - 1 - i);
  }
  if (nums.size() % 2 == 1) {
    indexes.push_back(nums.size() / 2);
  }

  for (size_t i=0; i<nums.size(); i++) {
    res[indexes[i]] = nums[i];
  }
  return true;
}

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);

  ll n;
  in >> n;

  vector<ll> nums;
  nums.resize(n);

  for (size_t i = 0; i<n; i++) {
    in >> nums[i];
  }
  sort(nums.begin(), nums.end(), greater<int>());

  debug_print(nums);

  vector<ll> circled_nums(nums);

  bool res = perform_magic(nums, circled_nums);

  print_bool(res, out);
  if (res) {
    for (auto num : circled_nums) {
      out << num << " ";
    }
    out << endl;
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
