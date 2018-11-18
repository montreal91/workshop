
//
// Problem: https://codeforces.com/contest/1038/problem/A
// Author: montreal91
// Solved during contest.
//

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <climits>
#include <map>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

template <typename T>
void print_list(const vector<T>& list, ostream& out) {
  for (auto& l : list) {
    out << l << endl;
  }
}

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);

  int n, k;
  in >> n >> k;

  string s;
  in >> s;

  vector<int> freq;
  freq.resize(k);

  for (auto i = 0; i<freq.size(); i++) {
    freq[i] = 0;
  }

  for (char c : s) {
    freq[c - '0' - 17]++;
  }

  int maxx = INT_MAX;
  for (auto f : freq) {
    if (f < maxx) {
      maxx = f;
    }
  }
  out << maxx * k << endl;
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
