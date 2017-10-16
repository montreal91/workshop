
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int function(istream& in, ostream& out) {
  int n;
  in >> n;
  vector<int> shedules;

  int s;
  for (int i = 0; i < n; i++) {
    in >> s;
    shedules.push_back(s);
  }

  for (int el : shedules) {
    out << el * el << " ";
  }
  out << endl;
  return 0;
}

int main() {
  ifstream in("data/template.in");
  function(in, cout);
  return 0;
}
