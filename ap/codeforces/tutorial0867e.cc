
//
// Problem: https://codeforces.com/contest/867/problem/E
// Author: montreal91
// Type: tutorial
// Time: null
// Failed attempts: 1
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

long long get_heap_top(
  const priority_queue<long long, vector<long long>, greater<long long>>& heap
) {

  if (heap.empty()) {
    return numeric_limits<long long>::max();
  }
  return heap.top();
}

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);
  int n;
  in >> n;
  vector<long long> stocks;
  stocks.resize(n);

  for (int i=0; i<n; i++) {
    in >> stocks[i];
  }

  priority_queue<long long, vector<long long>, greater<long long>> stock_heap;
  priority_queue<long long, vector<long long>, greater<long long>> sell_heap;
  vector<long long> exercises;

  for (auto s : stocks) {
    auto tested_val = s;
    if (get_heap_top(sell_heap) < tested_val) {
      tested_val = sell_heap.top();
      sell_heap.pop();
      sell_heap.push(s);
    }
    if (get_heap_top(stock_heap) < tested_val) {
      exercises.push_back(stock_heap.top());
      stock_heap.pop();
      sell_heap.push(tested_val);
    }
    else {
      stock_heap.push(tested_val);
    }
  }

  long long profit = 0;
  while (!sell_heap.empty() && !exercises.empty()) {
    profit += sell_heap.top();
    sell_heap.pop();

    profit -= exercises.back();
    exercises.pop_back();
  }
  out << profit << endl;
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
