#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <utility>
#include <map>
#include <cmath>
#include <climits>


using namespace std;


long long find_divisor(long long n, long long test_divisor) {
  if (pow(test_divisor, 2) > n) {
    return n;
  }
  else if (n % test_divisor == 0) {
    return test_divisor;
  }
  return find_divisor(n, test_divisor + 1);
}

long long smallest_divisor(long long n) {
  return find_divisor(n, 2);
}

bool is_prime(long long n) {
  return n == smallest_divisor(n);
}

template <typename T>
void print_list(const vector<T>& list, ostream& out) {
  for (auto& l : list) {
    out << l << endl;
  }
}

int function(istream& in, ostream& out) {
  int n;
  in >> n;
  typedef pair<long long, long long> Pair;
  vector<Pair> list_of_pairs;

  for (int i = 0; i < n; i++) {
    Pair p;
    in >> p.first >> p.second;
    list_of_pairs.push_back(p);
  }
  vector<long long> divisors;

  auto maz = sqrt(max(list_of_pairs[0].first, list_of_pairs[0].second));

  for (auto i=2; i<=maz; i++) {
    bool first_added = false;
    if (list_of_pairs[0].first % i == 0) {
      first_added = true;
      divisors.push_back(i);
      divisors.push_back(list_of_pairs[0].first / i);
    }

    if (list_of_pairs[0].second % i == 0) {
      if (! first_added) {
        divisors.push_back(i);
      }
      divisors.push_back(list_of_pairs[0].second / i);
    }
  }
  divisors.push_back(list_of_pairs[0].first);
  divisors.push_back(list_of_pairs[0].second);

  for (auto d : divisors) {
    if (d == 1 || !is_prime(d)) {
      continue;
    }
    bool divides_all_pairs = true;
    for (auto& p : list_of_pairs) {
      if (p.first % d != 0 && p.second % d != 0) {
        divides_all_pairs = false;
        break;
      }
    }
    if (divides_all_pairs) {
      out << d << endl;
      return 0;
    }
  }
  out << -1 << endl;
  return 0;
}


int main() {
  ifstream in("data/b.in");
  function(cin, cout);
  return 0;
}
