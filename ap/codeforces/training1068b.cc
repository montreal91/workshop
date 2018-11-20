
//
// Problem: https://codeforces.com/contest/1068/problem/B
// Author: montreal91
// Type: training
// Date: 20.11.2018
// Time: 01:15
// Failed attempts: 1
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
  string separator;
  if (label.size() == 0) {
    separator = "";
  }
  else {
    separator = " ";
  }
  #ifndef ONLINE_JUDGE
    cout << label << separator << val << endl;
  #endif
}

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);

  long long b;
  in >> b;

  if (b == 1) {
    out << 1 << endl;
    return;
  }

  long long res = 0;
  long double bond = sqrt(b);
  debug_print(bond, "Bond   ");

  for (long double i=1.0; i<bond; i+=1.0) {
    long long divisor = static_cast<long long>(i);
    if (b % divisor == 0) {
      debug_print(divisor, "Divisor");
      res++;
    }
  }

  res *= 2;
  long double fractpart, intpart;
  fractpart = modf(bond, &intpart);

  if (fractpart == 0) {
    res++;
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
