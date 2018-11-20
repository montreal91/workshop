
//
// Problem: https://codeforces.com/contest/1068/problem/A
// Author: montreal91
// Type: training
// Date: 20.11.2018
// Time: 00:30
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

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);

  long long N, M, K, L;
  in >> N >> M >> K >> L;

  long long alpha = K + L;

  #ifndef ONLINE_JUDGE
    out << "[DEBUG] ";
    out << "K + L = " << K + L << endl;
    out << "M, N " << M << " " << N;
    out << endl;
  #endif

  if (K + L > N || M > N) {
    out << -1 << endl;
    return;
  }

  long double fractpart, intpart;
  fractpart = modf(static_cast<long double>(alpha) / M, &intpart);
  long long answer = static_cast<long double>(intpart);
  if (fractpart > 0) {
    answer++;
  }

  if (answer * M > N) {
    answer = -1;
  }
  out << answer << endl;
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
