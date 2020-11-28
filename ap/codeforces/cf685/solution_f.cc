
//
// Problem: https://codeforces.com/contest/1451/problem/F
// Author: montreal91
// Type: tutorial
// Time: 00:00
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

typedef long long LL;
typedef vector<vector<LL>> Matrix;

bool check_matrix_diagonal(const Matrix& M, int d) {
  int max_i = M.size() - 1;
  int max_j = M[0].size() - 1;
  if (d > max_i + max_j) {
    return false;
  }
  int i = min(d, max_j);
  int j = d - i;
  LL zum = 0;
  while (j <= max_i && i >= 0) {
    zum = zum ^ M[j][i];
    j++; i--;
  }
  return zum == 0;
}

bool solve_game(const Matrix& M) {
  int D = M.size() + M[0].size() - 1;
  for (int d=0; d<D; d++) {
    if (!check_matrix_diagonal(M, d)) {
      return false;
    }
  }
  return true;
}

string verbose(bool x) {
  if (x) {
    return "Jeel";
  }
  return "Ashish";
}

void read_matrix(istream& in, Matrix& M) {
  int m, n;
  in >> m >> n;
  M.clear();
  M.resize(m);
  for (int i=0; i<m; i++) {
    vector<LL> row;
    row.resize(n);
    M[i] = row;
    for (int j=0; j<n; j++) {
      in >> M[i][j];
    }
  }
}

void print_matrix(ostream& out, const Matrix& M) {
  int m = M.size();
  int n = M[0].size();
  for (int i=0; i<m; i++) {
    for (int j=0; j<n; j++) {
      out << M[i][j] << " ";
    }
    out << "\n";
  }
}


void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);
  LL t;
  in >> t;
  Matrix M;
  for (int i=0; i<t; i++) {
    read_matrix(in, M);
    out << verbose(solve_game(M)) << endl;
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
