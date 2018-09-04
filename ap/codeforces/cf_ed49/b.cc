
//
// I didn't managed to solve this problem within an hour.
// Solution is based on this blog post (seciton on problem B):
// https://codeforces.com/blog/entry/61311
//

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <utility>
#include <map>

using namespace std;

long long calculate_number(long long i, long long j, long long n) {
  auto cnt = (i - 1) * n + j;
  cnt = (cnt + (cnt % 2)) / 2;
  if ((i + j) % 2 != 0) {
    auto sqr = n * n;
    cnt += (sqr + (sqr % 2)) / 2;
  }
  return cnt;
}

void function(istream& in, ostream& out) {
  long long n;
  int q;
  in >> n >> q;

  for (auto c=0; c<q; c++) {
    long long i, j;
    in >> i >> j;
    out << calculate_number(i, j, n) << endl;
  }
}

int main() {
  ifstream in("data/b.in");
  function(cin, cout);
  return 0;
}
