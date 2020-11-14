
//
// Problem: https://codeforces.com/contest/1438/problem/C
// Author: montreal91
// Type: aftercontest
// Time: 00:00
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

typedef vector<vector<long long>> matrix;
void read_matrix(istream& in, vector<vector<long long>>& M, int n, int m) {
  M.resize(n);
  for (int i=0; i<n; i++) {
    vector<long long> row;
    row.resize(m);
    for (int j=0; j<m; j++) {
      in >> row[j];
    }
    M[i] = row;
  }
}

void pirnt_matrix(ostream& out, const vector<vector<long long>>& M) {
  int n = M.size();
  int m = M[0].size();
  for (int i=0; i<n; i++) {
    for (int j=0; j<m; j++) {
      out << M[i][j] << " ";
    }
    out << endl;
  }
}

void process_matrix(matrix& M) {
  vector<long long> l;
  int n = M.size();
  int m = M[0].size();
  for (int i=0; i<n; i++)  {
    for (int j=0; j<m; j++) {
      if (M[i][j] % 2 != (i + j) % 2) {
        M[i][j]++;
      }
    }
  }
}

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);
  int t;
  int n, m;
  in >> t;
  vector<vector<long long>> M;
  for (int i=0; i<t; i++) {
    in >> n >> m;
    read_matrix(in, M, n, m);
    process_matrix(M);
    pirnt_matrix(out, M);
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
