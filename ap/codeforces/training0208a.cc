
//
// Problem: https://codeforces.com/contest/208/problem/A
// Author: montreal91
// Data: 30.11.2018
// Type: training
// Time: 17
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

const string WUB = "WUB";

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);

  string s;
  in >> s;

  bool good = false;
  string word = "";
  vector<string> words;
  for (auto i=0; i<s.size();) {
    if (s.substr(i, 3) == WUB) {
      if (good) {
        words.push_back(word);
        word = "";
      }
      i+= 3;
      good = false;
    }
    else {
      word = word + s[i];
      good = true;
      i++;
    }
  }
  if (good) {
    words.push_back(word);
  }
  // debug_print(words);
  for (auto w : words) {
    out << w << " ";
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
