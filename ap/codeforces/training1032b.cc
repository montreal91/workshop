
//
// Problem: https://codeforces.com/contest/1032/problem/B
// Author: montreal91
// Date: 26.11.2018
// Type: training
// Time: 02:02
// Failed attempts: 3
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

const int MAX_COLS = 20;
const int MAX_ROWS = 5;

void good_print(const string& str, int rows) {
  auto cols = str.size() / rows;
  cols += static_cast<int>(str.size() % rows > 0);
  auto asterisks = (cols * rows - str.size()) % rows;
  auto line_length = cols - static_cast<int>(asterisks > 0);
  auto cursor = 0;
  debug_print(asterisks, "asterisks:");
  for (auto i=0; i<rows; i++) {
    if (asterisks) {
      auto line = str.substr(cursor, cols-1);
      cout << line[0] << "*" << line.substr(1, line.size() -1);
      cursor += (cols - 1);
      asterisks--;
    }
    else {
      cout << str.substr(cursor, cols);
      cursor += cols;
    }
    cout << endl;
  }
}

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);

  string s;
  in >> s;

  if (s.size() <= MAX_COLS) {
    out << 1 << " " << s.size() << endl;
    out << s << endl;
    return;
  }

  auto rows = 0;
  for (auto i=1; i<=MAX_ROWS; i++) {
    if (s.size() / i + static_cast<int>(s.size() % i > 0) <= MAX_COLS) {
      rows = i;
      break;
    } 
  }
  int cols = s.size() / rows;
  if (s.size() % rows > 0) {
    cols++;
  }
  out << rows << " " << cols << endl;
  good_print(s, rows);
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
