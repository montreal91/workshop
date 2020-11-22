
//
// Problem: https://codeforces.com/contest/1451/problem/E
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

int get_index(const vector<LL>& v, LL k) {
  auto it = find(v.begin(), v.end(), k);
  if (it != v.end()) {
    return it - v.begin();
  }
  return -1;
}

struct Action {
  bool is_simple;
  LL i, j;
};

class TehSolver {
public:
  TehSolver(LL n) {
    this->n = n;
    xors.resize(n);
    xors[0] = 0;
    results.resize(n);
  }

  void add_xor(LL i, LL xorr) {
    xors[i] = xorr;
  }

  void add_or(LL i, LL j, LL orr) {
    results[i] = orr;
    results[j] = orr;
  }

  Action next_actions() {
    unordered_map<LL, LL> counter;
    LL dublicate = -1;
    LL i, j;
    Action result;
    for (j=0; j<xors.size(); j++) {
      counter[xors[j]]++;
      if (counter[xors[j]] > 1) {
        dublicate = xors[j];
        break;
      }
      if (xors[j] == xors.size() -1) {
        i = j;
      }
    }
    if (dublicate > -1) {
      result.is_simple = true;
      result.i = get_index(xors, dublicate);
      result.j = j;
      return result;
    }
    j = (i + 1) % n;
    if (j == 0) {
      j++;
    }
    result.is_simple = false;
    result.i = i;
    result.j = j;
    return result;
  }

  void solve_simple(LL i) {
    results[0] = restore_b(results[i], xors[i]);
    for (LL j=1; j<n; j++) {
      results[j] = restore_b(results[0], xors[j]);
    }
  }

  void solve_complex(LL i, LL j, LL first_and_i, LL i_and_j) {
    LL x = xors[i];
    LL y = xors[j] + 2 * first_and_i;
    LL z = get_xor(i, j) + 2 * i_and_j;
    results[0] = solve_equation(x, y, z);

    for (LL j=1; j<n; j++) {
      results[j] = restore_b(results[0], xors[j]);
    }
  }

  void print_res(ostream& out) {
    out << "! ";
    for (auto r : results) {
      out << r << " ";
    }
    out << endl;
  }
private:
  LL n;
  vector<LL> xors;
  vector<LL> results;

  LL restore_b(LL a, LL a_xor_b) {
    return a ^ a_xor_b;
  }

  LL get_xor(LL i, LL j) {
    return xors[i] ^ xors[j];
  }

  LL solve_equation(LL x, LL y, LL z) {
    return (x + y - z) / 2;
  }
};

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);

  LL n;
  in >> n;
  out.flush();
  TehSolver solver(n);
  LL tmp;
  for (LL i=1; i<n; i++) {
    out << "XOR 1 " << i+1 << endl;
    in >> tmp;
    solver.add_xor(i, tmp);
    out.flush();
  }
  auto res = solver.next_actions();
  if (res.is_simple) {
    out << "OR " << res.i + 1 << " " << res.j + 1 << endl;
    in >> tmp;
    solver.add_or(res.i, res.j, tmp);
    solver.solve_simple(res.i);
  }
  else {
    out << "AND 1 " << res.j + 1 << endl;
    LL zero_and_j;
    in >> zero_and_j;
    out.flush();
    LL i_and_j;
    out << "AND " << res.i + 1 << " " << res.j + 1 << endl;
    in >> i_and_j;
    out.flush();
    solver.solve_complex(res.i, res.j, zero_and_j, i_and_j);
  }
  solver.print_res(out);
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
