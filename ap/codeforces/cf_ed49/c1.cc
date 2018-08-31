//
// Problem: https://codeforces.com/contest/1027/problem/C
// Author: montreal91
// Solved during training in 1:25
// This solution is too slow, though. Don't pass test 5 (exceeds time limits).
// The idea is practically the same as in tutorial explanation.
//

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <limits>
#include <map>
#include <string>
#include <utility>
#include <vector>

using namespace std;

const int MAAX = numeric_limits<int>::max();

// we assume that sticks is a sorted vector
bool square_stick_check(size_t i, const vector<int>& sticks) {
  if (i+3 >= sticks.size()) {
    return false;
  }
  return sticks[i] == sticks[i+3];
}

double calculate_ratio(int a, int b) {
  int top = 4 * (a * a + 2 * a * b + b * b);
  return static_cast<double>(top) / static_cast<double>(a * b);
}

// we assume that sticks is a sorted vector
// and out vector is empty
void get_min_rect(const vector<int>& sticks, vector<int>* out) {
  auto side_a = MAAX;
  auto side_b = MAAX;
  auto ratio = static_cast<double>(MAAX);

  for (auto i=0; i<sticks.size() - 2; i++) {
    if (square_stick_check(i, sticks)) {
      side_a = sticks[i];
      side_b = sticks[i];
      break;
    }
    if (sticks[i] != sticks[i+1]) {
      continue;
    }
    for (auto j=i+2; j<sticks.size()-1; j++) {
      if (sticks[j] != sticks[j+1]) {
        continue;
      };
      auto new_ratio = calculate_ratio(sticks[i], sticks[j]);
      if (new_ratio < ratio) {
        ratio = new_ratio;
        side_a = sticks[i];
        side_b = sticks[j];
      }
    }
  }

  out->push_back(side_a);
  out->push_back(side_a);
  out->push_back(side_b);
  out->push_back(side_b);
}

void function(istream& in, ostream& out) {
  int T;
  int N;
  vector<int> sticks;
  vector<int> rect;
  in >> T;
  for (auto i=0; i<T; i++) {
    in >> N;
    sticks.resize(N);
    for (int j=0; j<N; j++) {
      in >> sticks[j];
    }
    rect.resize(0);
    sort(sticks.begin(), sticks.end());
    get_min_rect(sticks, &rect);

    for (auto stick : rect) {
      out << stick << " ";
    }
    out << endl;
  }
}

int main() {
  ifstream in("data/c.in");
  function(cin, cout);
  return 0;
}
