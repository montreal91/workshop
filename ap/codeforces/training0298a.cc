
//
// Problem: https://codeforces.com/problemset/problem/298/A
// Author: montreal91
// Date: 25.11.2018
// Type: training
// Time: 00:33
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

const char BLANK = '.';
const char RIGHT = 'R';
const char LEFT = 'L';

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

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);
  int n;
  in >> n;
  string s;
  in >> s;
  bool l_flag = false;
  bool r_flag = false;
  int l_pos = 0;
  int r_pos = 0;
  int r_blank_pos = 0;
  for (int i=0; i<n; i++) {
    if (!l_flag && s[i] == LEFT) {
      l_flag =  true;
      l_pos = i + 1;
      continue;
    }
    if (!r_flag && s[i] == RIGHT) {
      r_flag = true;
      r_pos = i + 1;
      continue;
    }
    if ((l_flag || r_flag) && s[i] == BLANK) {
      r_blank_pos = i + 1;
      break;
    }
  }
  if (!l_flag && !r_flag) {
    out << 1 << " " << 1 << endl;
  }
  else if (!l_flag && r_flag) {
    out << r_pos << " " << r_blank_pos << endl;
  }
  else if (l_flag && !r_flag) {
    out << l_pos << " " << l_pos - 1 << endl;
  }
  else if (l_flag && r_flag) {
    out << r_pos << " " << l_pos - 1 << endl;
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
