
//
// Problem: https://codeforces.com/contest/1015/problem/B
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

const string letters = "abcdefghijklmnopqrstuvwxyz";

int get_letter_index(char c) {
  for (auto i=0; i<letters.size(); i++) {
    if (letters[i] == c) {
      return i;
    }
  }
  return -1;
}

bool check_if_possible(const string& s, const string& t) {
  vector<int> letters_s;
  vector<int> letters_t;
  letters_s.resize(letters.size());
  letters_t.resize(letters.size());

  // Just to be sure that vectors are filled with zeroes;
  for (auto i=0; i<letters.size(); i++) {
    letters_s[i] = 0;
    letters_t[i] = 0;
  }

  for (auto i=0; i<s.size(); i++) {
    letters_s[get_letter_index(s[i])]++;
    letters_t[get_letter_index(t[i])]++;
  }
  return letters_s == letters_t;
}

void sswap(string& s, int pos) {
  if (pos >= s.size()) {
    return;
  }
  auto bubble = s[pos];
  s[pos] = s[pos+1];
  s[pos+1] = bubble;
}

void function(istream& in, ostream& out) {
  int n;
  string s, t;
  in >> n >> s >> t;
  if (!check_if_possible(s, t)) {
    out << -1 << endl;
    return;
  }

  vector<int> res;

  for (int i=0; i<n-1; i++) {
    if (t[i] == s[i]) {
      continue;
    }
    int pos = 0;
    for (int j=i+1; j<n; j++) {
      if (t[i] == s[j]) {
        pos = j;
      }
    }

    while (pos > i) {
      sswap(s, pos-1);
      res.push_back(pos);
      pos--;
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
  ifstream in("data/b.in");
  function(cin, cout);
  return 0;
}
