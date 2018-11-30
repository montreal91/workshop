
//
// Problem: https://codeforces.com/contest/1082/problem/B
// Author: montreal91
// Date: 28.11.2018
// Type: training
// Time: None
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

struct Gold {
  int length, distance, start;
  Gold(int x=0, int y=0) {
    length = x;
    start = x;
  }

  Gold(const Gold& g) {
    length = g.length;
    start = g.start;
  }
};

const char GOLD = 'G';
const char SILVER = 'S';

int get_distance(const Gold& g1, const Gold& g2) {
  auto last_g1 = g1.start + g1.length;
  return g2.start - last_g1;
}

bool can_merge(const Gold& g1, const Gold&g2) {
  return get_distance(g1, g2) == 1;
}

int get_beauty(const string& s) {
  bool g = false;
  vector<Gold> gg;
  Gold seq;
  for (int i=0; i<s.size(); i++) {
    if (!g && s[i] == GOLD) {
      seq.length = 1;
      seq.start = i;
      g = true;
    }
    else if (g && s[i] == GOLD) {
      seq.length++;
    }
    else if (g && s[i] == SILVER) {
      gg.push_back(seq);
      g = false;
    }
  }

  if (g) {
    gg.push_back(seq);
  }

  if (gg.size() == 0) {
    return 0;
  }

  if (gg.size() == 1) {
    return gg[0].length;
  }

  if (gg.size() == 2) {
    if (can_merge(gg[0], gg[1])) {
      return gg[0].length + gg[1].length;
    }
    else {
      return max(gg[0].length, gg[1].length) + 1;
    }
  }

  int maxres = 0;
  for (int i=0; i<gg.size() - 1; i++) {
    int loc_res = gg[i].length + 1;
    if (can_merge(gg[i], gg[i+1])) {
      loc_res += gg[i+1].length;
    }
    if (loc_res > maxres) {
      maxres = loc_res;
    }
  }
  return max(maxres, gg[gg.size() - 1].length + 1);
}

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);
  int n;
  in >> n;

  string s;
  in >> s;

  out << get_beauty(s) << endl;
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
