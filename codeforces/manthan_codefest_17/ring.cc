
#include <iostream>
#include <vector>
#include <fstream>
#include <climits>
#include <algorithm>

using namespace std;

// class PolynomObject {
// public:
//   PolynomObject(int p, int q, int r) {
//     this->p = p;
//     this->q = q;
//     this->r = r;
//   }

//   long long operator () (int a1, int a2, int a3) {
//     return a1 * this->p + a2 * this->q + a3 * this->r;
//   }
// private:
//   int p, q, r;
// };

int function(istream& in, ostream& out) {
  int n;
  in >> n;

  long long p, q, r;
  in >> p >> q >> r;

  vector<long long> array;
  int s;
  for (int i = 0; i < n; i++) {
    in >> s;
    array.push_back(s);
  }

  // PolynomObject po(p, q, r);
  // long long p_max = LLONG_MIN;
  // long long q_max = LLONG_MIN;
  // long long r_max = LLONG_MIN;

  vector<long long> dp0, dp1, dp2;

  dp0.push_back(p*array[0]);
  for (int i=1; i<n; i++) {
    long long item = max(dp0[i-1], array[i]*p);
    dp0.push_back(item);
  }

  dp1.push_back(dp0[0] + q*array[0]);
  for (int j=1; j<n; j++) {
    long long item = max(dp1[j-1], dp0[j] + q*array[j]);
    dp1.push_back(item);
  }

  dp2.push_back(dp1[0] + r*array[0]);
  for (int k=1; k<n; k++) {
    long long item = max(dp2[k-1], dp1[k] + r*array[k]);
    dp2.push_back(item);
  }

  out << dp2[n-1] << endl;
  return 0;
}

int main() {
  ifstream in("data.in");
  function(cin, cout);
  return 0;
}
