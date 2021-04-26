
//
// Problem: https://leetcode.com/problems/valid-sudoku/
// Author: montreal91
// Type: training
// Time: None
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

#ifndef ONLINE_JUDGE
  #include "lib/debug.h"
#endif // ONLINE_JUDGE

using namespace std;


struct Cell {
  int x, y, val;
};


struct CellColHash {
  size_t operator() (const Cell& key) const {
    return static_cast<size_t>(10 * key.x + key.val);
  }
};


struct CellRowHash {
  size_t operator()(const Cell& key) const {
    return static_cast<size_t>(10 * key.y + key.val);
  }
};

struct CellBoxHash {
  size_t operator()(const Cell& key) const {
    int a = key.x / 3;
    int b = key.y / 3;
    return static_cast<size_t>(10 * (a * 3 + b) + key.val);
  }
};

const char BLANK = '.';
const int IN = 1;

template<typename K, typename V>
bool key_in_map(const unordered_map<K, V>& map, const K& key) {
  auto res = map.find(key);
  return res != map.end();
}


class Solution {
public:
  bool isValidSudoku(vector<vector<char>>& board) {
    vector<Cell> non_blank_cells;

    for (auto i=0u; i<board.size(); i++) {
      for (auto j=0u; j<board.size(); j++) {
        if (board[i][j] == BLANK) {
          continue;
        }
        Cell new_cell;
        new_cell.x = i;
        new_cell.y = j;
        new_cell.val = static_cast<int>(board[i][j]) - 48;
        non_blank_cells.push_back(new_cell);
      }
    }

    CellColHash col_hash;
    CellRowHash row_hash;
    CellBoxHash box_hash;

    unordered_map<size_t, int> col_map;
    unordered_map<size_t, int> row_map;
    unordered_map<size_t, int> box_map;

    for (auto& cell : non_blank_cells) {
      if (key_in_map(col_map, col_hash(cell))) {
        return false;
      }
      if (key_in_map(row_map, row_hash(cell))) {
        return false;
      }
      if (key_in_map(box_map, box_hash(cell))) {
        return false;
      }
      col_map[col_hash(cell)] = IN;
      row_map[row_hash(cell)] = IN;
      box_map[box_hash(cell)] = IN;
    }
    return true;
  }
};


const unsigned int SIZE = 9;

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);

  vector<vector<char>> board;
  board.resize(SIZE);
  for (auto i=0u; i<SIZE; i++) {
    vector<char> row;
    row.resize(SIZE);
    board[i] = row;
  }

  for (auto i=0u; i<SIZE; i++) {
    for (auto j=0u; j<SIZE; j++) {
      in >> board[i][j];
    }
  }

  Solution solution;

  if (solution.isValidSudoku(board)) {
    out << "YES" << endl;
  }
  else {
    out << "NO" << endl;
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
