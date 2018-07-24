
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

int function(istream& in, ostream& out) {
  int n;
  in >> n;
  vector<string> names;

  string s;
  for (int i = 0; i < n; i++) {
    in >> s;
    names.push_back(s);
  }

  for (int i = 0; i < names.size(); i++) {
    bool found = false;
    for (int j = 0; j < i; j++) {
      if (names[i] == names[j]) {
        found = true;
        break;
      }
    }
    if (found) {
      out << "YES\n";
    } else {
      out << "NO\n";
    }
  }
  out << endl;
  return 0;
}

int main() {
  ifstream in("data.in");
  function(cin, cout);
  return 0;
}
