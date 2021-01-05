
//
// Problem: https://codeforces.com/contest/1472/problem/D
// Author: montreal91
// Type: contest
// Time: 00:33
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

typedef long long LL;

string solve_game(vector<LL>& A) {
  sort(A.begin(), A.end(), greater<LL>());
  LL alice = 0;
  LL bob = 0;
  for (int i=0; i<A.size(); i+=2) {
    if (A[i] % 2 == 0) {
      alice += A[i];
    }
  }
  for (int i=1; i<A.size(); i+=2) {
    if (A[i] %2 == 1) {
      bob += A[i];
    }
  }

  if (alice > bob) {
    return "Alice";
  }
  else if (bob > alice) {
    return "Bob";
  }
  return "Tie";
}


void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);

  vector<LL> A;
  int t, n;
  in >> t;
  for (int i=0; i<t; i++) {
    in >> n;
    A.resize(n);
    for (int j=0; j<n; j++) {
      in >> A[j];
    }
    // debug_print(A);
    out << solve_game(A) << endl;
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
