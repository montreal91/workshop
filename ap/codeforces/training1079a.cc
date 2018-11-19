
//
// Problem: https://codeforces.com/contest/1079/problem/A
// Author: montreal91
// Type: training
// Date: 19.11.2018
// Time: 01:20
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

const int MAX_TYPES = 100;

template <typename T>
T get_max(const vector<T>& vec) {
  if (vec.empty()) {
    return 0; // ??
  }
  T the_max = vec[0];
  for (size_t i=0; i<vec.size(); i++) {
    if (vec[i] > the_max) {
      the_max = vec[i];
    }
  }
  return the_max;
}

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);

  int n, k;
  in >> n >> k;

  vector<int> utensils;
  utensils.resize(n);

  for (auto i=0; i<n; i++) {
    in >> utensils[i];
  }

  vector<int> types_count;
  types_count.resize(MAX_TYPES);

  for (auto i=0; i<MAX_TYPES; i++) {
    types_count[i] = 0;
  }

  for (auto u : utensils) {
    types_count[u-1]++;
  }

  auto max_utensils = get_max(types_count);
  double fractpart, intpart;
  fractpart = modf(static_cast<double>(max_utensils) / k, &intpart);

  int number_of_dishes = static_cast<int>(intpart);
  if (fractpart > 0) {
    number_of_dishes++;
  }

  long long answer = 0;
  for (auto tc : types_count) {
    if (tc > 0) {
      answer += ((number_of_dishes * k) - tc);
    }
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
