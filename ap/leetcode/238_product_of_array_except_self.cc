
//
// Problem: https://leetcode.com/problems/product-of-array-except-self/
// Author: montreal91
// Type: training
// Time: None
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

#ifndef ONLINE_JUDGE
  #include "lib/debug.h"
#endif // ONLINE_JUDGE

using namespace std;

class Solution {
public:
  vector<int> productExceptSelf(vector<int>& nums) {
    vector<int> products;
    products.resize(nums.size());

    int product = 1;
    products[0] = product;

    for (int i=1; i<nums.size(); i++) {
      product *= nums[i-1];
      products[i] = product;
    }

    product = 1;
    for (int i=nums.size() - 2; i>=0; i--) {
      product *= nums[i+1];
      products[i] *= product;
    }
    return products;
  }
};


void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);

  int n;
  in >> n;
  vector<int> nums;
  nums.resize(n);

  for (int i=0; i<n; i++) {
    in >> nums[i];
  }

  Solution sol;
  auto res = sol.productExceptSelf(nums);
  for (auto r : res) {
    out << r << " ";
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
