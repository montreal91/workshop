
//
// Problem: https://codeforces.com/contest/1189/problem/A
// Author: montreal91
// Type: training
// Time: 01:12
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

struct BinCount {
  int ones, zeroes;

  BinCount() {
    ones = 0;
    zeroes = 0;
  }

  bool is_good() const {
    return ones != zeroes;
  }
};

BinCount get_bin_count(const string& str) {
  BinCount res;

  for (char c : str) {
    if (c == '0') {
      res.zeroes++;
    }
    else if (c == '1') {
      res.ones++;
    }
  }
  return res;
}

vector<string> split(const string& str) {
  vector<string> res;
  BinCount bin_str = get_bin_count(str);
  if (bin_str.is_good()) {
    res.push_back(str);
    return res;
  }
  if (str.size() % 2 == 0) {
    res.push_back(str.substr(0, 1));
    res.push_back(str.substr(1, str.size() - 1));
    return res;
  }

  string begin, end;
  BinCount bin_begin, bin_end;
  for (int i=1; i<str.size() - 1; i++) {
    begin = str.substr(0, i);
    end = str.substr(i, res.size() - i);

    bin_begin = get_bin_count(begin);
    bin_end = get_bin_count(end);

    if (bin_begin.is_good() && bin_end.is_good()) {
      res.push_back(begin);
      res.push_back(end);
      return res;
    }
  }

  // Worst case
  res.push_back(str.substr(0, 1));
  res.push_back(str.substr(1, 1));
  res.push_back(str.substr(2, str.size() - 2));

  return res;
}

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);
  int n;
  in >> n;
  string s;
  in >> s;
  auto res = split(s);
  out << res.size() << endl;
  for (auto& str : res) {
    out << str << " ";
  }
  out << endl;
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
