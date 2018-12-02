
//
// Problem: https://codeforces.com/contest/1000/problem/A
// Author: montreal91
// Date: 02.12.2018
// Type: training
// Time: 00:32
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

const vector<string> sizes = {
  "XXXL",
  "XXL",
  "XL",
  "L",
  "M",
  "S",
  "XS",
  "XXS",
  "XXXS",
};


class SizeCounter {
public:
  SizeCounter() {
    for (auto& s : sizes) {
      _sizes[s] = 0;
    }
  }

  void add_size(const string& s) {
    _sizes[s]++;
  }

  int get_size(const string& s) {
    return _sizes[s];
  }

private:
  map<string, int> _sizes;
};

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);

  int n;
  in >> n;

  SizeCounter prev, curr;

  string size;
  for (int i=0; i<n; i++) {
    in >> size;
    prev.add_size(size);
  }

  for (int i=0; i<n; i++) {
    in >> size;
    curr.add_size(size);
  }

  int deltas = 0;
  for (auto& s : sizes) {
    deltas += abs(curr.get_size(s) - prev.get_size(s));
  }

  out << deltas / 2 << endl;
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
