
//
// Problem: https://codeforces.com/contest/1015/problem/A
// Author: montreal91
// Solved during training in 0:25
//

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <utility>
#include <map>

using namespace std;

void function(istream& in, ostream& out) {
  typedef pair<int, int> Segment;
  vector<Segment> segments;

  int n, m;
  in >> n >> m;

  for (auto i=0; i<n; i++) {
    auto a = 0, b = 0;
    in >> a >> b;
    segments.push_back(Segment(a, b));
  }

  vector<int> res;
  for (int i=1; i <= m; i++ ) {
    bool should_add = true;
    for (auto& s : segments) {
      if (s.first <= i && i <= s.second) {
        should_add = false;
        break;
      }
    }
    if (should_add) {
      res.push_back(i);
    }
  }
  out << res.size() << endl;
  if (res.size() > 0) {
    for (auto r : res) {
      out << r << " ";
    }
    out << endl;
  }
}

int main() {
  ifstream in("data/a.in");
  function(cin, cout);
  return 0;
}
