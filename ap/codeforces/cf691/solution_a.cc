
//
// Problem: https://codeforces.com/contest/1459/problem/A
// Author: montreal91
// Type: contest
// Time: 00:34
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
  #include "util.h"
#endif // ONLINE_JUDGE

using namespace std;


string verbose(char c) {
  if (c == -1) {
    return "BLUE";
  }
  if (c == 1) {
    return "RED";
  }
  return "EQUAL";
}

struct RB {
  char red, blue;
};

char solve(const vector<RB>& cards) {
  int equals = 0;
  int reds = 0;
  for (auto& c : cards) {
    if (c.red > c.blue) {
      reds++;
    }
    else if (c.red == c.blue) {
      equals++;
    }
  }
  int cmax = cards.size() - equals;
  if (reds * 2 == cmax) {
    return 0;
  }
  if (reds > cmax / 2) {
    return 1;
  }
  return -1;
}


void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);
  int T;
  in >> T;
  vector<RB> cards;
  int n;
  for (int i=0; i<T; i++) {
    in >> n;
    cards.resize(n);
    for (int i=0; i<n; i++) {
      in >> cards[i].red;
    }
    for (int i=0; i<n; i++) {
      in >> cards[i].blue;
    }
    out << verbose(solve(cards)) << endl;
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
