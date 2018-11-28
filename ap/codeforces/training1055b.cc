
//
// Problem: https://codeforces.com/contest/1055/problem/B
// Author: montreal91
// Date: 28.11.2018
// Type: training
// Time: 01:53
// Failed attempts: 10
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


class Head {
public:
  Head(const vector<unsigned long long> v, unsigned long long l) :
  _hairs(v),
  _length(l) {
    _cuts = _get_cuts();
  }

  long long get_cuts() {
    return _cuts;
  }

  void grow(int pos, int delta) {
    auto index = pos - 1;

    if (_add_condition(index, delta)) {
      _cuts++;
    }
    else if (_decrease_condition(index, delta)) {
      _cuts--;
    }
    _hairs[index] += delta;
  }

private:
  bool _add_condition(int pos, int delta) {
    auto left = _hairs[pos - 1];
    if (pos == 0) {
      left = 0;
    }

    auto right = _hairs[pos + 1];
    if (pos == _hairs.size() - 1) {
      right = 0;
    }

    bool c1 = left <= _length;
    bool c2 = _hairs[pos] <= _length && _hairs[pos] + delta > _length;
    bool c3 = right <= _length;
    return c1 && c2 && c3;
  }

  long long _get_cuts() {
    auto res = 0ll;
    if (_hairs[0] > _length) {
      res++;
    }

    for (auto i=1; i<_hairs.size(); i++) {
      if (_hairs[i] > _length && _hairs[i-1] <= _length) {
        res++;
      }
    }
    return res;
  }

  bool _decrease_condition(int pos, int delta) {
    if (pos == 0 || pos == _hairs.size() - 1) {
      return false;
    }
    bool c1 = _hairs[pos - 1] > _length;
    bool c2 = _hairs[pos] + delta > _length && _hairs[pos] <= _length;
    bool c3 = _hairs[pos + 1] > _length;
    return c1 && c2 && c3;
  }

  long long _cuts;
  vector<unsigned long long> _hairs;
  unsigned long long _length;
};


void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);

  long long n, m, l;
  in >> n >> m >> l;
  vector<unsigned long long> hairs;
  hairs.resize(n);

  for (auto i=0; i<n; i++) {
    in >> hairs[i];
  }

  Head head(hairs, l);
  bool flag;
  int pos, delta;
  for (auto i=0; i<m; i++) {
    in >> flag;
    if (flag) {
      in >> pos >> delta;
      head.grow(pos, delta);
    }
    else {
      out << head.get_cuts() << endl;
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
