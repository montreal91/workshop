
//
// Problem: https://leetcode.com/problems/coin-change/
// Author: montreal91
// Type: training
// Time: None
// Failed attempts: 5
//

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <limits>
#include <map>
#include <queue>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

const int NOT_FOUND = -1;

class Solution {
public:
  int coinChange(vector<int>& coins, int amount) {
    if (amount == 0) {
      return 0;
    }
    _init_coins(coins);
    _init_solutions(amount);

    for (int i=1; i<=amount; i++) {
      _solutions[i] = _get_solution(i);
    }
    return _solutions.back();
  }

private:
  vector<int> _coins;
  vector<int> _solutions;

  int _get_solution(int n) {
    int answer = numeric_limits<int>::max();
    for (auto coin : _coins) {
      int j = n - coin;
      if (j < 0 || _solutions[j] == NOT_FOUND) {
        continue;
      }
      answer = min(answer, _solutions[j] + 1);
    }
    if (answer == numeric_limits<int>::max()) {
      return NOT_FOUND;
    }
    return answer;
  }

  void _init_coins(const vector<int>& coins) {
    _coins.resize(coins.size());
    for (int i=0; i<coins.size(); i++) {
      _coins[i] = coins[i];
    }
  }

  void _init_solutions(int amount) {
    _solutions.resize(amount + 1);
    _solutions[0] = 0;
  }
};

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);
  int k;
  in >> k;
  vector<int> coins;
  coins.resize(k);
  for (int i=0; i<k; i++) {
    in >> coins[i];
  }
  int to_change;
  in >> to_change;
  Solution sol;

  out << "The answer is:\n";
  out << sol.coinChange(coins, to_change) << endl;
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
