//
// Problem: https://codeforces.com/contest/1076/problem/B
// Author: montreal91
// Type: training
// Date: 15.11.2018
// Time: None
// Failed attempts: 5
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
void print_vector(const vector<T>& to_print, const string& separator) {
  for (T p : to_print) {
    cout << p << separator;
  }
}

bool is_prime(long long x) {
  for (long long i = 3; ; i++) {
    auto q = x / i;
    if (q < i) {
      return true;
    }
    if (x == q * i) {
      return false;
    }
  }
}

long long next_prime(long long x) {
  if (x < 2) {
    return 2;
  }
  if (x == 2) {
    return 3;
  }
  if (!(x & 1)) {
    x++;
  }
  for (; !is_prime(x); x += 2);
  return x;
}

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);

  long long n;
  in >> n;

  #ifndef ONLINE_JUDGE
    out << "the input was:\n";
    out << n << endl << endl;
  #endif

  long long prime = 0;
  long long res = 0;
  double fractpart, intpart;
  while (n > 0) {
    prime = next_prime(prime + 1);

    if (n % 2 == 0) {
      res += n / 2;
      break;
    }

    fractpart = modf(sqrt(n), &intpart);

    if (fractpart == 0.0 && is_prime(static_cast<long long>(intpart))) {
      n -= static_cast<long long>(intpart);
      res++;
    }

    if (is_prime(n)) {
      res++;
      break;
    }
    
    if (n % prime == 0) {
      res++;
      n -= prime;
    }
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
