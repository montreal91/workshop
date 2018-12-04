
//
// Problem: https://codeforces.com/contest/466/problem/B
// Author: montreal91
// Date: 04.12.2018
// Type: training
// Time: None
// Failed attempts: 4
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
  #ifndef ONLINE_JUDGE
    string separator;
    if (label.size() == 0) {
      separator = "";
    }
    else {
      separator = " ";
    }
    cout << label << separator << val << endl;
  #endif // ONLINE_JUDGE
}

template<typename T>
void debug_print(
  const vector<T>& to_print,
  const string& separator=" ",
  const string& label=""
) {
  #ifndef ONLINE_JUDGE
    for (T p : to_print) {
      cout << p << separator;
    }
    cout << endl;
  #endif // ONLINE_JUDGE
}

void get_divisors(long long a, long long min_div, vector<long long>* res) {
  res->resize(0);
  auto sq = static_cast<long long>(sqrt(a)) + 1;
  for (auto i=min_div; i<= sq; i++) {
    if (a % i == 0) {
      res->push_back(i);
    }
  }
}

long long remainder(long long a, long long b) {
  return static_cast<long long>(a % b > 0);
}

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);
  long long n, a, b;
  in >> n >> a >> b;
  auto req = n * 6;

  // Already more, than required
  if (req <= a * b) {
    out << a * b << endl << a << " " << b << endl;
    return;
  }

  vector<long long> divisors;

  bool found = false;
  while(!found) {
    get_divisors(req, min(a, b), &divisors);

  // debug_print(req, "req:");

    for (auto i=divisors.size(); i> 0; i--) {
      if (divisors[i-1] == 0) {
        debug_print(i, "WTF?");
      }
      divisors.push_back(req / divisors[i-1]);
    }
    // debug_print(divisors);
    // Exact requirement could be achieved;
    for (auto d : divisors) {
      if (req / d >= a && d >= b) {
        out << req << endl;
        out << req / d << " " << d << endl;
        return;
      }
    }
    req++;
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
