
//
// Problem: https://codeforces.com/contest/1475/problem/C
// Author: montreal91
// Type: tutorial
// Time: 00:47
// Failed attempts: 2
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

#ifndef ONLINE_JUDGE
  #include "util.h"
#endif // ONLINE_JUDGE

using namespace std;


class BallPair {
public:
  BallPair() {
    boy = 0;
    girl = 0;
  }

  BallPair(int boy, int girl) {
    this->boy = boy;
    this->girl = girl;
  }

  BallPair(const BallPair& bp) {
    this->boy = bp.boy;
    this->girl = bp.girl;
  }

  string to_string() const {
    return "(" + std::to_string(boy) + "|" + std::to_string(girl) + ")";
  }

  int boy, girl;
};

bool operator <(const BallPair& bp1, const BallPair& bp2) {
  if (bp1.boy == bp2.boy) {
    return bp1.girl < bp2.girl;
  }
  return bp1.boy < bp2.boy;
}

string pair_record(const BallPair& bp1, const BallPair& bp2) {
  BallPair first, second;
  if (bp1 < bp2) {
    first = bp1;
    second = bp2;
  }
  else {
    first = bp2;
    second = bp1;
  }
  return  first.to_string() + second.to_string();
}

bool are_pairs_complement(const BallPair& bp1, const BallPair& bp2) {
  return bp1.boy != bp2.boy && bp1.girl != bp2.girl;
}

long long count_representatives(const vector<BallPair>& pairs) {
  unordered_map<int, int> boy_deg;
  unordered_map<int, int> girl_deg;
  for (auto& pair : pairs) {
    boy_deg[pair.boy]++;
    girl_deg[pair.girl]++;
  }
  long long res = 0;

  long long k = static_cast<long long>(pairs.size());
  for (auto& pair : pairs) {
    res += max(k - boy_deg[pair.boy] - girl_deg[pair.girl] + 1, 0LL);
  }
  return res / 2;
}

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);

  int t, a, b, k;
  in >> t;

  vector<int> boys;
  vector<int> girls;
  vector<BallPair> pairs;

  for (int i=0; i<t; i++) {
    in >> a >> b >> k;
    boys.resize(k);
    for (int j=0; j<k; j++) {
      in >> boys[j];
    }

    girls.resize(k);
    for (int j=0; j<k; j++) {
      in >> girls[j];
    }

    pairs.resize(k);

    for (int j=0; j<k; j++) {
      pairs[j].boy = boys[j];
      pairs[j].girl = girls[j];
    }

    out << count_representatives(pairs) << endl;
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
