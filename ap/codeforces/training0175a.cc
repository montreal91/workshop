
//
// Problem: https://codeforces.com/contest/175/problem/A
// Author: montreal91
// Date: 06.12.2018
// Type: training
// Time: 01:36
// Failed attempts: 2
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

const char ZERO = '0';
const long long MAX = 1000000;

int get_leading_zeroes(const string& s) {
  auto i = 0;
  for(i=0; s[i] == ZERO; i++);
  return i;
}

bool is_good(const string& s) {
  return (s.size() == 1 && stoll(s) == 0ll) || get_leading_zeroes(s) == 0; 
}

long long calculate_points(const string& s, int l1, int l2) {
  try {  
    auto res = 0ll;
    auto chunk1 = s.substr(0, l1);
    auto chunk2 = s.substr(l1, l2);
    auto chunk3 = s.substr(l1 + l2, s.size());

    if (!is_good(chunk1) || !is_good(chunk2) || !is_good(chunk3)) {
      return -1;
    }

    auto pts1 = stoll(chunk1);
    auto pts2 = stoll(chunk2);
    auto pts3 = stoll(chunk3);

    if (pts1 > MAX || pts2 > MAX || pts3 > MAX) {
      return -1;
    }
    res += pts1;
    res += pts2;
    res += pts3;
    return res;
  }
  catch (const std::out_of_range& e) {
    return -1;
  }
}

long long calculate_max_points(const string& s) {
  auto res = -1ll;
  if (s.size() > 21 || s.size() < 3) {
    return res;
  }

  for (auto i=1; i<=s.size()-2; i++) {
    for (auto j=1; j<=(s.size() - i - 1); j++) {
      auto subres = calculate_points(s, i, j);
      if (subres > res) {
        res = subres;
      }
    }
  }
  return res;
}

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);

  string s;
  in >> s;

  out << calculate_max_points(s) << endl;
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
