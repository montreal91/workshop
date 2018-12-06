
//
// Problem: https://codeforces.com/contest/7/problem/A
// Author: montreal91
// Date: 06.12.2018
// Type: training
// Time: 00:28
// Failed attempts: 0
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

const char BLACK = 'B';
const char WHITE = 'W';

typedef vector<char> ChessRow;
// typedef vector<ChessRow> ChessBoard;

class ChessBoard {
public:
  ChessBoard(const vector<ChessRow>& rows) : _board(rows) {
    _calculate_to_paint();
  }

  int get_strokes() const {
    if (_to_paint == 64) {
      return 8;
    }

    auto res = 0;
    for (auto i=0; i<8; i++) {
      if (_is_column_black(i)) {
        res++;
      }
      if (_is_row_black(i)) {
        res++;
      }
    }
    return res;
  }

private:
  int _to_paint;

  void _calculate_to_paint() {
    _to_paint = 0;
    for (auto& row: _board) {
      for (auto cell : row) {
        if (cell == BLACK) {
          _to_paint++;
        }
      }
    }
  }

  bool _is_column_black(int i) const {
    for (auto& row : _board) {
      if (row[i] != BLACK) {
        return false;
      }
    }
    return true;
  }

  bool _is_row_black(int i) const {
    for (auto cell : _board[i]) {
      if (cell != BLACK) {
        return false;
      }
    }
    return true;
  }

  vector<ChessRow> _board;
};

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);

  vector<ChessRow> board;
  for (int i=0; i<8; i++) {
    ChessRow r;
    r.resize(8);
    for (int j=0; j<8; j++) {
      in >> r[j];
    }
    board.push_back(r);
  }
  for (auto& r : board) {
    debug_print(r);
    out << endl;
  }
  ChessBoard cb(board);
  out << cb.get_strokes() << endl;
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
