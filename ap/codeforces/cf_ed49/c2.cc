
//
// Problem: https://codeforces.com/contest/1027/problem/C
// Author: montreal91
// This solution uses the same idea, as my another solution.
// It is a failed optimization attempt.
//

#include <algorithm>
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

const int MAAX = numeric_limits<int>::max();



template<typename T>
void print_vec(const std::vector<T>& vec, ostream& out) {
  for (auto& x: vec) {
    out << x << " ";
  }
  out << endl;
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

  for (auto i=0; i<sticks.size() - 1; i++) {
    auto new_ratio = calculate_ratio(sticks[i], sticks[i+1]);
    if (new_ratio < ratio) {
      ratio = new_ratio;
      side_a = sticks[i];
      side_b = sticks[i+1];
      if (side_a == side_b) {
        break;
      }
    }
  }
  out->push_back(side_a);
  out->push_back(side_a);
  out->push_back(side_b);
  out->push_back(side_b);
}

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);
  int T;
  int N;
  vector<int> raw;
  vector<int> rect;
  vector<int> sticks;
  unordered_map<int, int> counter;
  in >> T;
  for (auto I=0; I<T; I++) {
    in >> N;
    raw.resize(N);
    for (int j=0; j<N; j++) {
      in >> raw[j];
    }
    rect.resize(0);
    sticks.resize(0);

    counter.clear();

    for (auto& stick : raw) {
      counter[stick] += 1;
    }

    bool four_flag = false;
    for (auto& stick_count : counter) {
      if (stick_count.second > 4) {
        for (auto i=0; i<4; i++) {
          rect.push_back(stick_count.first);
        }
        four_flag = true;
        break;
      }

      if (stick_count.second >= 2) {
        sticks.push_back(stick_count.first);
      }
    }
    if (!four_flag) {
      sort(sticks.begin(), sticks.end());
      get_min_rect(sticks, &rect);
    }
    print_vec(rect, out);
  }
}

int main() {
  ifstream in("data/c.in");
  function(cin, cout);
  return 0;
}
