
//
// Problem: https://codeforces.com/contest/1438/problem/F
// Author: montreal91
// Type: tutorial
// Time: 00:00
// Failed attempts: 0
// Unfinished
//

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <limits>
#include <map>
#include <random>
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

struct triple {
  int a, b, c;
};

struct duplet {
  int a, b;
};

triple get_random_triple(int max_n) {
  random_device rd;  //Will be used to obtain a seed for the random number engine
  mt19937 gen(chrono::steady_clock::now().time_since_epoch().count()); //Standard mersenne_twister_engine seeded with rd()
  uniform_int_distribution<> distrib(1, max_n);
  triple t;
  t.a = 0, t.b = 0, t.c = 0;
  while (t.a == t.b || t.b == t.c || t.a == t.c) {
    t.a = distrib(gen);
    t.b = distrib(gen);
    t.c = distrib(gen);
  }
  return t;
}

int perform_query(istream& in, ostream& out, const triple& t) {
  out.flush();
  out << "? " << t.a << " " << t.b << " " << t.c << endl;
  int res;
  in >> res;
  return res;
}

duplet get_top_two(const unordered_map<int, int>& counter) {
  duplet res;
  res.a = 0;
  res.b = 0;
  int best = 0, second = 0;
  for (auto& entry : counter) {
    if (entry.second > best) {
      second = best;
      best = entry.second;
      res.b = res.a;
      res.a = entry.first;
    }
    else if (entry.second > second) {
      second = entry.second;
      res.b = entry.first;
    }
  }
  return res;
}

int pow2(int pow) {
  return 1 << pow;
}

duplet get_root_children(istream& in, ostream& out, int max_n) {
  unordered_map<int, int> counter;
  int c;
  for (int i=0; i<420; i++) {
    c = perform_query(in, out, get_random_triple(max_n));
    counter[c]++;
  }
  return get_top_two(counter);
}

int get_root(istream& in, ostream& out, int max_n, const duplet& root_children) {
  int tmp_root;
  triple tmp;
  tmp.a = root_children.a;
  tmp.b = root_children.b;
  for (int i=1; i<=max_n; i++) {
    if (i==tmp.a || i==tmp.b) {
      continue;
    }
    tmp.c = i;
    tmp_root = perform_query(in, out, tmp);
    if (tmp_root != root_children.a && tmp_root != root_children.b) {
      return tmp_root;
    }
  }
  return -1;
}


void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);
  int k;
  in >> k;
  duplet childeren = get_root_children(in, out, pow2(k) - 1);
  int root = get_root(in, out, pow2(k) - 1, childeren);
  out << "! " << root << endl;
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
