
//
// Problem: https://codeforces.com/contest/1079/problem/C
// Author: montreal91
// Date: 26.11.2018
// Type: training
// Time: 4:20
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

template<typename T>
void print(const vector<T>& to_print) {
  for (T p : to_print) {
    cout << p << " ";
  }
  cout << endl;
}

const int MIN = 1;
const int MID = 3;
const int MAX = 5;
const int BAD = -1;

int get_min_possible_finger(int last_finger, bool up) {
  if (up) {
    if (last_finger < MAX) {
      return last_finger + 1;
    }
    else {
      return BAD;
    }
  }
  if (last_finger == MIN) {
    return MIN + 1;
  }
  else {
    return MIN;
  }
}

int get_max_possible_finger(int last_finger, bool down) {
  if (down) {
    if (last_finger > MIN) {
      return last_finger - 1;
    }
    else {
      return BAD;
    }
  }
  if (last_finger == MAX) {
    return MAX - 1;
  }
  else {
    return MAX;
  }
}

bool is_locmin(const vector<int>& v, int i) {
  return v[i-1] > v[i] && v[i] < v[i+1];
}

bool is_locmax(const vector<int>& v, int i) {
  return v[i-1] < v[i] && v[i] > v[i+1];
}

int get_finger(const vector<int>& keys, int last_finger, int pos) {
  if (is_locmin(keys, pos)) {
    return get_min_possible_finger(last_finger, false);
  }
  if (is_locmax(keys, pos)) {
    return get_max_possible_finger(last_finger, false);
  }
  if (keys[pos - 1] > keys[pos]) {
    return get_max_possible_finger(last_finger, true);
  }
  if (keys[pos - 1] < keys[pos]) {
    return get_min_possible_finger(last_finger, true);
  }
  debug_print("BANG!!");
  if (pos == keys.size() - 1) {
    return get_min_possible_finger(last_finger, false);
  }
  if (keys[pos] < keys[pos + 1]) {
    return get_min_possible_finger(last_finger, false);
  }
  else if (keys[pos] > keys[pos + 1]) {
    return get_max_possible_finger(last_finger, false);
  }
  else {
    if (last_finger == MID) {
      return MID - 1;
    }
    else {
      return MID;
    }
  }
}

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);

  int n;
  in >> n;

  if (n == 1) {
    out << 1 << endl;
    return;
  }

  vector<int> piano_keys;
  piano_keys.resize(n);

  for (int i=0; i<n; i++) {
    in >> piano_keys[i];
  }

  vector<int> fingers;
  fingers.resize(1);

  if (piano_keys[0] < piano_keys[1]) {
    fingers[0] = MIN;
  }
  else if (piano_keys[0] == piano_keys[1]) {
    fingers[0] = MID;
  }
  else {
    fingers[0] = MAX;
  }
  
  int last_finger = fingers[0];
  for (int i = 1; i < n; i++) {
    last_finger = get_finger(piano_keys, last_finger, i);
    if (last_finger == BAD) {
      debug_print(fingers);
      out << BAD << endl;
      return;
    }
    fingers.push_back(last_finger);
  }

  print(fingers);
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
