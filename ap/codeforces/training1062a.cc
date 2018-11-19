//
// Problem: https://codeforces.com/contest/1062/problem/A
// Author: montreal91
// Type: training
// Date: 16.11.2018
// Time: None
// Failed attempts: 4
//

#include <algorithm>
#include <chrono>
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

const int ARRAY_MAX = 1000;

template<typename T>
void print_vector(const vector<T>& to_print, const string& separator) {
  for (T p : to_print) {
    cout << p << separator;
  }
  cout << endl;
}

template<typename T>
T get_max_element(const vector<T>& vec) {
  T the_max = vec[0];
  for (T v : vec) {
    if (v > the_max) {
      the_max = v;
    }
  }
  return the_max;
}

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);
  int n;
  in >> n;
  vector<int> array;
  array.resize(n);
  for (auto i=0; i<n; i++) {
    in >> array[i];
  }

  if (n == 1) {
    out << 0 << endl;
    return;
  }

  if (n == ARRAY_MAX) {
    out << 1000 << endl;
    return;
  }

  vector<int> answer;
  answer.clear();
  answer.push_back(0);
  int cursor = 0;
  while (cursor < n) {
    int i = cursor;
    int seq_start = array[i];
    
    for (i=cursor; array[i+1] - array[i] == 1 && i < n-1; i++) {}
    
    cursor = i + 1;
    int seq_end = array[i];
    int res = seq_end - seq_start -1;
    
    if (seq_start == seq_end) {
      continue;
    }
    if (seq_start == 1) {
      res++;
    }
    if (seq_end == ARRAY_MAX) {
      res++;
    }
    
    #ifndef ONLINE_JUDGE
      out << seq_start << " " << seq_end << " res: " << res;
      out << endl;
    #endif // ONLINE_JUDGE
    
    answer.push_back(res);
  }

  #ifndef ONLINE_JUDGE
    out << "The answer is:" << endl;
  #endif // ONLINE_JUDGE
  out << get_max_element(answer) << endl;
}

int main() {
#ifndef ONLINE_JUDGE
  using namespace chrono;
  auto time1 = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
#endif // ONLINE_JUDGE
  function(cin, cout);
#ifndef ONLINE_JUDGE
  auto time2 = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
  cout << "Time consumed: " << milliseconds(time2 - time1).count();
  cout << " ms.\n";
#endif // ONLINE_JUDGE
  return 0;
}
