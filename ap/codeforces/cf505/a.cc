
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <utility>
#include <map>

using namespace std;

int function(istream& in, ostream& out) {
  int n;
  string s;
  in >> n;
  in >> s;

  if (n == 1) {
    out << "Yes" << endl;
    return 0;
  }
  map<char, int> colors;
  for (int i=0; i<n; i++) {
    colors[s[i]]++;
  }

  for (int i=0; i<n; i++) {
    if (colors[s[i]] >= 2) {
      out << "Yes" << endl;
      return 0;
    }
  }
  out << "No" << endl;
  return 0;
}

int main() {
  ifstream in("data/a.in");
  function(cin, cout);
  return 0;
}
