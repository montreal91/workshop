
//
// Problem: https://codeforces.com/contest/1061/problem/B
// Author: montreal91
// Date: 27.11.2018
// Type: training
// Time: 02:12
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

long long fill_rectangle(long long height, long long width, long long to_fill) {
  return (height - 1) * width - max(to_fill - width, 0ll);
}

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);

  long long n, m;
  in >> n >> m;

  if (n == 1) {
    out << 0 << endl;
    return;
  }

  vector<long long> blocks;
  blocks.resize(n);
  for (long long i=0; i<n; i++) {
    in >> blocks[i];
  }
  
  sort(blocks.begin(), blocks.end());
  debug_print(blocks);

  auto res = 0ll;
  auto cube_height = 0ll;
  for (auto i=0ll; i<n-1; i++) {
    res += blocks[i] - 1;
    if (blocks[i] > cube_height) {
      cube_height++;
    }
  }

  debug_print(cube_height, "CH:");
  if (blocks[n-1] > cube_height) {
    res += cube_height;
  }
  else if (blocks[n-1] == cube_height) {
    res += blocks[n-1] - 1;
  }
  out << res << endl;
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
