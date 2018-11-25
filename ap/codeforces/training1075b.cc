//
// Problem: https://codeforces.com/contest/1075/problem/B
// Author: montreal91
// Type: training
// Date: 19.11.2018
// Time: 01:30
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

template<typename T>
void print_vector(const vector<T>& to_print, const string& separator) {
  for (T p : to_print) {
    cout << p << separator;
  }
}

int get_divide(const vector<int>& drivers, int pos) {
  if (pos == drivers.size() - 1) {
    return numeric_limits<int>::max();
  }
  return (drivers[pos] + drivers[pos + 1]) / 2;
}

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);

  int n, m;
  in >> n >> m;
  vector<int> positions;
  positions.resize(n + m);

  vector<bool> indicators;
  indicators.resize(n + m);

  for (auto i=0; i<n+m; i++) {
    in >> positions[i];
  }

  bool flag;
  for (auto i=0; i<n+m; i++) {
    in >> flag;
    indicators[i] = flag;
  }

  vector<int> drivers;
  vector<int> passengers;


  for (auto i=0; i<n+m; i++) {
    if (indicators[i]) {
      drivers.push_back(positions[i]);
    }
    else {
      passengers.push_back(positions[i]);
    }
  }

  if (drivers.size() == 1) {
    out << passengers.size() << endl;
    return;
  }

  vector<int> res;
  res.resize(drivers.size());

  for (auto i=0; i<res.size(); i++) {
    res[i] = 0;
  }

  auto driver_pos = 0;
  for (auto passenger : passengers) {
    auto divide = get_divide(drivers, driver_pos);

    if (passenger <= divide) {
      res[driver_pos]++;
    }
    else {
      while (divide < passenger) {
        driver_pos++;
        divide = get_divide(drivers, driver_pos);
      }
      res[driver_pos]++;
    }
  }

  print_vector(res, " ");
  out << endl;
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
