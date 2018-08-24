//
// Problem: https://codeforces.com/contest/1015/problem/B
// Author: montreal91
// Solved during training in 2:55
//

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <utility>
#include <map>

using namespace std;

void function(istream& in, ostream& out) {
  long long houses, moves, to_walk;
  in >> houses >> moves >> to_walk;

  if ((houses - 1) * moves < to_walk || moves > to_walk) {
    out << "NO" << endl;
    return;
  }

  out << "YES" << endl;

  long long base = to_walk / moves;
  long long remainder = to_walk % moves;

  long long current_house = 1;
  while (moves > 0) {
    moves--;
    auto run = 0;
    if (base + remainder < houses - 1) {
      run = base + remainder;
      remainder = 0;
    }
    else {
      run = houses - 1;
      remainder -= (houses - base - 1);
    }

    if (current_house - run < 1) {
      current_house += run;
    }
    else {
      current_house -= run;
    }

    out << current_house << " ";
  }
  out << endl;
}

int main() {
  ifstream in("data/d.in");
  function(cin, cout);
  return 0;
}
