
//
// Problem: https://codeforces.com/contest/1111/problem/A
// Author: montreal91
// Type: training
// Time: 00:12
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

bool is_vowel(char h) {
  return h == 'a' || h == 'e' || h == 'i' || h == 'o' || h == 'u';
}

void say_yes() {
  cout << "YES" << endl;
}

void say_no() {
  cout << "NO" << endl;
}

bool compare_superheroes(const string& s, const string& t) {
  if (s.size() != t.size()) {
    return false;
  }

  for (auto i=0; i<s.size(); i++) {
    if (is_vowel(s[i]) != is_vowel(t[i])) {
      return false;
    }
  }
  return true;
}

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);

  string s, t;
  in >> s >> t;

  if (compare_superheroes(s, t)) {
    say_yes();
  }
  else {
    say_no();
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
