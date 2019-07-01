
//
// Problem: https://codeforces.com/contest/1185/problem/B
// Author: montreal91
// Type: training
// Time: 00:49
// Failed attempts: 1
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

struct WordCouple {
  string in, out;
};

struct LetterSequence {
  char letter;
  int num;
};

LetterSequence read_char_from_pos(const string& s, int pos) {
  LetterSequence ls;
  ls.letter = s[pos];
  ls.num = 0;
  while (s[pos] == ls.letter && pos < s.size()) {
    pos++;
    ls.num++;
  }
  return ls;
}

void print_bool(ostream& out, bool value) {
  if (value) {
    out << "YES\n";
  }
  else {
    out << "NO\n";
  }
}

bool check_couple(const WordCouple& wc) {
  char in_char, out_char;
  int in_num = 0, out_num = 0;

  int i = 0, j = 0; // Pointers

  LetterSequence ls_in, ls_out;
  while (i < wc.in.size() && j < wc.out.size()) {
    ls_in = read_char_from_pos(wc.in, i);
    i += ls_in.num;
    ls_out = read_char_from_pos(wc.out, j);
    j += ls_out.num;

    if (ls_in.letter != ls_out.letter || ls_in.num > ls_out.num) {
      return false;
    }
  }
  return i == wc.in.size() && j == wc.out.size();
}

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);

  int n;
  in >> n;
  WordCouple wc;
  vector<WordCouple> couples;
  couples.resize(n);

  for (int i=0; i<n; i++) {
    in >> wc.in >> wc.out;
    couples[i] = wc;
  }

  for (auto& couple : couples) {
    print_bool(out, check_couple(couple));
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
