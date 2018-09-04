//
// Problem: https://codeforces.com/contest/1015/problem/D
// Author: montreal91
// Solved during training, time spent is enormous.
// Five unsuccessful submissions.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
#include <string>
#include <utility>
#include <map>

using namespace std;

struct Node {
  long long num;
  long long cost;
  bool is_visited;
  bool is_cycle;
  Node* next;

  Node(long long inum=0, long long icost=0) :
  num(inum),
  cost(icost) {
    this->next = nullptr;
    this->is_visited = false;
    this->is_cycle = false;
  }

  Node(const Node& node) {
    this->num = node.num;
    this->cost = node.cost;
    this->next = node.next;
    this->is_visited = node.is_visited;
    this->is_cycle = node.is_cycle;
  }
};

class CostStack {
public:
  long long get_sum() {
    long long res = 0;
    while (_stack.size() > 0) {
      res += _stack.top();
      _stack.pop();
    }
    return res;
  }

  void push(long long val) {
    _stack.push(val);
  }

  void update(long long val) {
    auto preval = _stack.top();
    if (val < preval) {
      _stack.pop();
      _stack.push(val);
    }
  }

private:
  stack<long long> _stack;
};

class RoomProcessor {
public:
  RoomProcessor(const vector<long long>& costs, const vector<long long>& moves) {
    _rooms.resize(costs.size());
    for (auto i=0; i<costs.size(); i++) {
      _rooms[i] = Node(i, costs[i]);
    }
    for (auto i=0; i<costs.size(); i++) {
      _rooms[i].next = &_rooms[moves[i] - 1];
    }
  }

  long long get_trap_cost() {
    for (auto i=0; i<_rooms.size(); i++) {
      if (!_rooms[i].is_visited) {
        _process_seed(&_rooms[i]);
      }
    }
    return _costs.get_sum();
  }

private:
  vector<Node> _rooms;
  CostStack _costs;

  void _process_seed(Node* seed) {
    Node* curnode = seed;
    bool in_cycle = false;
    while (true) {
      if (!curnode->is_visited) {
        curnode->is_visited = true;
        if (curnode->next->is_cycle) {
          curnode->is_cycle = true;
          _upmark_cycle(seed);
          break;
        }
      }
      else {
        curnode->is_cycle = true;
        if (!in_cycle) {
          in_cycle = true;
          _costs.push(curnode->cost);
        }
        else {
          _costs.update(curnode->cost);
        }
        if (curnode->next->is_cycle) {
          _upmark_cycle(seed);
          break;
        }
      }
      curnode = curnode->next;
    }
  }

  void _upmark_cycle(Node* seed) {
    Node * curnode = seed;
    while (!curnode->is_cycle) {
      curnode->is_visited = true;
      curnode->is_cycle = true;
      curnode = curnode->next;
    }
  }
};


struct test {
  long long a, b;
};


void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);

  long long N;
  vector<long long> costs;
  vector<long long> moves;
  in >> N;
  costs.resize(N);
  moves.resize(N);

  for (auto I=0; I<N; I++) {
    in >> costs[I];
  }
  for (auto I=0; I<N; I++) {
    in >> moves[I];
  }

  RoomProcessor rp(costs, moves);
  auto res = rp.get_trap_cost();
  out << res << endl;
}

int main() {
  function(cin, cout);
  return 0;
}
