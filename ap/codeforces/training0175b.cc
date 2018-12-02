
//
// Problem: https://codeforces.com/contest/175/problem/B
// Author: montreal91
// Date: 01.12.2018
// Type: training
// Time: 01:00
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

typedef pair<string, long long> Record;
typedef pair<string, string> Rank;

class Categorizer {
public:
  Categorizer(const vector<Record>& all_records):
  _best_results() {
    // Initiationg the map
    for (auto& record : all_records) {
      _best_results[record.first] = record.second;
    }

    // Filling with best results
    for (auto& record : all_records) {
      if (_best_results[record.first] < record.second) {
        _best_results[record.first] = record.second;
      }
    }
  }

  vector<Rank> get_ranks() const {
    vector<Rank> result;

    vector<Record> records;
    for (auto& res : _best_results) {
      records.push_back(res);
    }

    auto total = static_cast<long double>(records.size());

    for (auto& left: records) {
      auto goods = 0.0l;
      for (auto& right: records) {
        if (left.second >= right.second) {
          goods += 1.0l;
        }
      }

      auto percentage = goods / total;
      result.push_back(Rank(left.first, get_category(percentage)));
    }

    return result;
  }

  long long size() const {
    return _best_results.size();
  }

private:
  map<string, long long> _best_results;

  string get_category(long double percentage) const {
    if (percentage >= 0.99l) {
      return "pro";
    }
    if (percentage >= 0.9l) {
      return "hardcore";
    }
    if (percentage >= 0.8l) {
      return "average";
    }
    if (percentage >= 0.5l) {
      return "random";
    }
    return "noob";
  }
};

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);

  auto n = 0ll;
  in >> n;

  string name = "";
  auto score = 0ll;
  vector<Record> inputs;
  inputs.resize(n);
  for (auto i = 0ll; i<n; i++) {
    in >> name >> score;
    inputs[i] = Record(name, score);
  }

  Categorizer c(inputs);
  out << c.size() << endl;
  auto ranks = c.get_ranks();
  for (auto& rank: ranks) {
    out << rank.first << " " << rank.second << endl;
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
