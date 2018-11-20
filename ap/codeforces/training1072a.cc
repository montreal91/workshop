
//
// Problem: https://codeforces.com/contest/1072/problem/A
// Author: montreal91
// Type: training
// Date: 20.11.2018
// Time: 00:15
// Failed attempts: 0
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

int glide(int w, int h) {
  return 2 * (w + h - 2);
}

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);

  int w, h, k;
  in >> w >> h >> k;

  int res = 0;
  for (int i=0; i<k; i++) {
    res += glide(w - i*4, h - i*4);
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
