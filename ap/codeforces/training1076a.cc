
//
// Problem: https://codeforces.com/contest/1076/problem/A
// Author: montreal91
// Type: training
// Date: 15.11.2018
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

string exclude(string str, int pos) {
  return str.substr(0, pos) + str.substr(pos + 1);
}

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);

  int n;
  string s;
  in >> n;
  in >> s;

  int del_ind = 0;
  bool flag = false;

  for (int i = 0; i < n - 1; i++) {
    if (s[i] > s[i+1]) {
      del_ind = i;
      flag = true;
      break;
    }
  }
  if (flag){ 
    out << exclude(s, del_ind) << endl;
  }
  else {
    out << exclude(s, n - 1) << endl;
  }
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
