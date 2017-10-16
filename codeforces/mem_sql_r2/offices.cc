
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

int function(istream& in, ostream& out) {
  int n;
  in >> n;
  string offices;
  in >> offices;


  int sf = 0;
  int fs = 0;
  for (int i=1; i < n; i++) {
    if (offices[i] == 'F' && offices[i-1] == 'S'){
      sf++; 
    } else if (offices[i] == 'S' && offices[i-1] == 'F') {
      fs++;
    }
  }
  if (sf > fs) out << "YES" << endl;
  else out << "NO" << endl;
  out << endl;
  return 0;
}

int main() {
  ifstream in("data/offices.in");
  function(cin, cout);
  return 0;
}
