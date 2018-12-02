
//
// Problem: https://codeforces.com/contest/1020/problem/A
// Author: montreal91
// Date: 02.12.2018
// Type: training
// Time: 00:50
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

struct Request {
  long long tower_a, floor_a, tower_b, floor_b, a, b;

  Request(
    long long ta,
    long long fa,
    long long tb,
    long long fb,
    long long a,
    long long b) :
  tower_a(ta),
  floor_a(fa),
  tower_b(tb),
  floor_b(fb),
  a(a),
  b(b) {}
};

long long route_length(const Request& request) {
  if (request.tower_a == request.tower_b) {
    return abs(request.floor_a - request.floor_b);
  }

  auto horfloor = request.a;
  if (request.b < request.floor_a) {
    horfloor = request.b;
  }
  else if (request.floor_a < request.a) {
    horfloor = request.a;
  }
  else {
    horfloor = request.floor_a;
  }
  auto hor = abs(request.tower_a - request.tower_b);
  return abs(horfloor - request.floor_a) + hor + abs(horfloor - request.floor_b);
}

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);
  long long n, h, a, b, q;
  in >> n >> h >> a >> b >> q;

  long long fa, ta, fb, tb;
  for (auto i=0ll; i<q; i++) {
    in >> fa >> ta >> fb >> tb;
    Request r(fa, ta, fb, tb, a, b);
    out << route_length(r) << endl;
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
