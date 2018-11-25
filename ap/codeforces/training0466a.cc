
//
// Problem: https://codeforces.com/contest/466/problem/A
// Author: montreal91
// Type: training
// Date: 21.11.2018
// Time: 00:40
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

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);

  int n, m, a, b;
  in >> n >> m >> a >> b;

  int res = 0;

  int tickets = n / m;
  int tickets_cost = tickets * b;
  int regular_cost = tickets * m * a;

  res += min(tickets_cost, regular_cost);

  int remainder = n % m;

  res += min(remainder * a, b);
  
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
