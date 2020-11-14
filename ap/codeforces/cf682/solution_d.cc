
//
// Problem: https://codeforces.com/contest/1438/problem/D
// Author: montreal91
// Type: tutorial
// Time: 00:00
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

typedef long long LL;
typedef vector<vector<int>> Solution;

bool can_solve(const vector<LL>& nums) {
  if (nums.size() % 2 == 1) {
    return true;
  }
  LL res = nums[0];
  for (int i=1; i<nums.size(); i++) {
    res = res ^ nums[i];
  }
  return res == 0;
}

void solve(const vector<LL>& in, int n, Solution& out) {
  out.clear();
  int i;
  for (i=0; i+2 < n; i+=2) {
    vector<int> v = {i, i+1, i+2};
    out.push_back(v);
  }
  for (;i>0; i-=2) {
    vector<int> v = {i-2, i-1, i};
    out.push_back(v);
  }
}

void print(ostream& out, const Solution& solution) {
  out << solution.size() << endl;
  for (auto& line : solution) {
    out << line[0] + 1 << " ";
    out << line[1] + 1 << " ";
    out << line[2] + 1 << endl;
  }
}

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);
  int n;
  in >> n;
  vector<LL> A;
  A.resize(n);
  for (int  i=0; i<n; i++) {
    in >> A[i];
  }
  if (can_solve(A)) {
    out << "YES\n";
    Solution s;
    if (A.size() % 2 == 1) {
      solve(A, A.size(), s);
    }
    else {
      solve(A, A.size() - 1, s);
    }
    print(out, s);
  }
  else {
    out << "NO\n";
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
