
//
// Problem: https://codeforces.com/contest/1036/problem/B
// Author: montreal91
// Solved during contest.
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

  unsigned long long T, i, j, q;
  in >> T;

  for (auto I=0; I<T; I++) {
    in >> i >> j >> q;
    auto road = max(i, j);
    if (q < road) {
        out << -1 << endl;
        continue;
    }

    if ((i + j) % 2 == 1) {
        out << q - 1 << endl;
    }
    else {
        if (q % 2 == road % 2) {
            out << q << endl;
        } else {
            out << q - 2 << endl;
        }
    }
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
