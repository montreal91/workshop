
//
// Problem: https://codeforces.com/contest/230/problem/B
// Author: montreal91
// Type: training
// Time: 00:57
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

bool is_prime(long double ld) {
  if (ld == 2 || ld == 3 || ld == 5) {
    return true;
  }
  
  long double fract, intp;
  fract = modf(ld, &intp);
  if (fract > 0) {
    return false;
  }
  
  auto root_d = sqrt(ld);

  long long root = static_cast<long long>(root_d);
  long long ll = static_cast<long long>(ld);

  for (long long i=2; i <= root + 1; i++) {
    if (ll % i == 0) {
      return false;
    }
  }
  return true;
}

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);

  int N;
  in >> N;

  vector<long long> nums;
  nums.resize(N);

  for (int i=0; i<N; i++) {
    in >> nums[i];
  }

  for (int i=0; i<N; i++) {
    if (nums[i] != 1 && is_prime(sqrt(nums[i]))) {
      debug_print(i);
      out << "YES" << endl;
    }
    else {
      out << "NO" << endl;
    }
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
