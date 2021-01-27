
//
// Author: montreal91
// Type: tutorial
// Time: 03:24
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

typedef long long LL;

class App {
public:
  LL memory = 0, score = 0;

  App() {}

  App(LL memory, LL score) {
    this->memory = memory;
    this->score = score;
  }

  App(const App& app) {
    this->memory = app.memory;
    this->score = app.score;
  }

  double ratio() const {
    return static_cast<double>(score) / static_cast<double>(memory);
  }
};


bool operator <(const App& a1, const App& a2) {
  if (a1.ratio() == a2.ratio()) {
    return a1.score < a2.score;
  }
  return a1.ratio() < a2.ratio();
}

class Generator {
public:
  Generator(const vector<App>& ones, const vector<App>& twos)
  : one(ones), two(twos) {}

  App get_next() {

    //
    // Corner-cases
    //
    if (i == one.size()) {
      App a = two[j];
      j++;
      return a;
    }
    if (j == two.size()) {
      App a = one[i];
      i++;
      return a;
    }

    if (i == one.size() - 1) {
      if (one[i].memory <= two[j].memory) {
        App a = one[i];
        i++;
        return a;
      }
      else {
        App a = two[j];
        j++;
        return a;
      }
    }

    //
    // Main case
    //
    if (one[i].memory + one[i+1].memory >= two[j].memory) {
      App a = one[i];
      i++;
      return a;
    }
    else {
      App a = two[j];
      j++;
      return a;
    }
  }

  bool has_next() const {
    return i < one.size() || j < two.size();
  }

private:
  LL i = 0, j = 0;
  vector<App> one;
  vector<App> two;
};

LL find_min_importance(const vector<App>& apps, LL target_mem) {
  vector<App> one;
  vector<App> two;

  for (auto app : apps) {
    if (app.score == 1) {
      one.push_back(app);
    }
    else {
      two.push_back(app);
    }
  }

  // cout << "Sizes: " << one.size() << " " << two.size() << endl;

  struct {
    bool operator()(const App& a, const App& b) const {
      return a.memory > b.memory;
    }
  } app_comparator;

  sort(one.begin(), one.end(), app_comparator);
  sort(two.begin(), two.end(), app_comparator);

  LL cur_sum_one = 0;
  LL cur_sum_two = 0;
  for (LL j=0; j<two.size(); j++) {
    cur_sum_two += two[j].memory;
  }

  LL answer = numeric_limits<LL>::max();
  LL i = 0, j = two.size();
  // cout << "sum2: " << cur_sum_two << endl;
  for (;i<=one.size(); i++) {
    while (j > 0 && cur_sum_one + cur_sum_two - two[j - 1].memory >= target_mem) {
      j--;
      cur_sum_two -= two[j].memory;
    }
    // cout << cur_sum_one + cur_sum_two << endl;
    if (cur_sum_one + cur_sum_two >= target_mem) {
      answer = min(answer, 2 * j + i);
    }
    if (i != one.size()) {
      cur_sum_one += one[i].memory;
    }
  }
  if (answer == numeric_limits<LL>::max()) {
    return -1;
  }
  return answer;
}


void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);

  LL t;
  in >> t;
  for (LL c=0; c<t; c++) {

  LL n, m;
  in >> n >> m;

  vector<LL> mem, score;
  mem.resize(n);
  score.resize(n);

  for (LL i=0; i<n; i++) {
    in >> mem[i];
  }
  for (LL i=0; i<n; i++) {
    in >> score[i];
  }

  vector<App> apps;
  apps.resize(n);
  for (int i=0; i<n; i++) {
    apps[i].memory = mem[i];
    apps[i].score = score[i];
  }

  // sort(apps.begin(), apps.end());
  out << find_min_importance(apps, m) << endl;
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
