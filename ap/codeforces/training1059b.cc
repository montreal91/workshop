
//
// Problem: https://codeforces.com/contest/1059/problem/B
// Author: montreal91
// Date: 24.11.2018
// Type: training
// Time: 01:05
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

typedef pair<char, bool> Cell;
typedef vector<vector<Cell>> Field;
const char INK = '#';
const char BLANK = '.';

bool can_apply(const Field& f, int pos_x, int pos_y) {
  if (f[pos_x][pos_y-1].first == BLANK) {
    return false;
  }
  if (f[pos_x][pos_y+1].first == BLANK) {
    return false;
  }
  if (f[pos_x-1][pos_y].first == BLANK) {
    return false;
  }
  if (f[pos_x+1][pos_y].first == BLANK) {
    return false;
  }
  if (f[pos_x+1][pos_y+1].first == BLANK) {
    return false;
  }
  if (f[pos_x-1][pos_y-1].first == BLANK) {
    return false;
  }
  if (f[pos_x+1][pos_y-1].first == BLANK) {
    return false;
  }
  if (f[pos_x-1][pos_y+1].first == BLANK) {
    return false;
  }
  return true;
}

void apply(Field& f, int pos_x, int pos_y) {
  f[pos_x][pos_y-1].second = true;
  f[pos_x][pos_y+1].second = true;
  f[pos_x-1][pos_y].second = true;
  f[pos_x+1][pos_y].second = true;
  f[pos_x+1][pos_y+1].second = true;
  f[pos_x-1][pos_y-1].second = true;
  f[pos_x+1][pos_y-1].second = true;
  f[pos_x-1][pos_y+1].second = true;
}

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);

  int n, m;
  in >> n >> m;
  vector<vector<Cell>> field;

  Cell buffer;
  for (int i=0; i<n; i++) {
    vector<Cell> row;
    row.resize(m);
    for (int j=0; j<m; j++) {
      in >> buffer.first;
      buffer.second = false;
      row[j] = buffer;
    }
    field.push_back(row);
  }

  #ifndef ONLINE_JUDGE
    for (auto row : field) {
      for (auto& cell : row) {
        out << cell.first << " ";
      }
      out << endl;
    }
  #endif

  for (int i=1; i<n-1; i++) {
    for (int j=1; j<m-1; j++) {
      if (can_apply(field, i, j)) {
        apply(field, i, j);
      }
    }
  }

  bool go = true;
  for (int i=0; i<n && go; i++) {
    for (int j=0; j<m && go; j++) {
      if (field[i][j].first == INK && !field[i][j].second) {
        out << "NO" << endl;
        return;
      }
    }
  }
  out << "YES" << endl;
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
