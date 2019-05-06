
//
// Problem: https://codeforces.com/contest/1162/problem/A
// Author: montreal91
// Type: training
// Time: 00:40
// Failed attempts: 0
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

struct Restriction {
  Restriction() {
    left = 0;
    right = 0;
    max_height = 0;
  }

  int left, right, max_height;
};

struct RestrictionComparator {
  bool operator() (const Restriction& r1, Restriction& r2) {
    return r1.left < r2.left;
  }
} restriction_comparator;

class RestrictionZoner {
public:
  RestrictionZoner(int dr, const vector<Restriction>& restrictions) :
  _dr(dr),
  _restrictions(restrictions) {
    sort(_restrictions.begin(), _restrictions.end(), restriction_comparator);
  }

  int max(int i) const {
    vector<int> possibilities;

    for (auto& r : _restrictions) {
      if (r.left <= i && i <= r.right) {
        possibilities.push_back(r.max_height);
      }
    }
    if (possibilities.empty()) {
      possibilities.push_back(_dr);
    }
    auto res_ptr = min_element(possibilities.begin(), possibilities.end());
    return *res_ptr;
  }
private:
  int _dr;
  vector<Restriction> _restrictions;
};

int maximize_profit(int slots, const RestrictionZoner& rz) {
  int res = 0;
  int tmp = 0;
  for (int i=1; i<=slots; i++) {
    tmp = rz.max(i);
    res += tmp * tmp;
  }
  return res;
}

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);

  int num, height, m_zones;
  in >> num >> height >> m_zones;

  vector<Restriction> restrictions;
  restrictions.resize(m_zones);

  Restriction tmp;
  for (int i=0; i<m_zones; i++) {
    in >> tmp.left;
    in >> tmp.right;
    in >> tmp.max_height;

    restrictions[i] = tmp;
  }

  RestrictionZoner rz(height, restrictions);
  out << maximize_profit(num, rz) << endl;
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
