//
// Problem: https://codeforces.com/contest/1015/problem/D
// Author: montreal91
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
  int num; // ?
  int cost;
  bool is_visited;
  bool is_cycle;
  Node* next;

  Node(int num=0, int cost=0) {
    this->num = num;
    this->cost = cost;
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

  void push(int val) {
    _stack.push(val);
  }

  void update(int val) {
    auto preval = _stack.top();
    if (val < preval) {
      _stack.pop();
      _stack.push(val);
    }
  }

private:
  stack<int> _stack;
};

class RoomProcessor {
public:
  RoomProcessor(vector<Node>& rooms) {
    _rooms.resize(rooms.size());
    copy(rooms.begin(), rooms.end(), _rooms.begin());
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
    bool cycle = false;
    cout << "==\nSeed: " << seed->num << "\n==\n";
    while (true) {
      cout << curnode->num << " " << curnode->is_visited << " " << curnode->is_cycle;
      cout << " " << cycle << " ";
      if (!curnode->is_visited) {
        curnode->is_visited = true;
        if (curnode->is_cycle) {
          cout << "BREAK\n";
          break;
        } else {
          cout << "Mark Visited\n";
        }
      }
      else {
        if (!cycle && !curnode->is_cycle) {
          cout << "Push\n";
          _costs.push(curnode->cost);
          cycle = true;
          curnode->is_cycle = true;
          curnode = curnode->next;
          continue;
        }

        if (curnode->is_cycle) {
          cout << "BREAK\n";
          break;
        }
        else {
          cout << "Update\n";
          _costs.update(curnode->cost);
          curnode->is_cycle = true;
        }
      }
      curnode = curnode->next;
    }
  }
};


struct test {
  int a, b;
};


void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);

  int N;
  vector<Node> rooms;
  vector<int> costs;
  vector<int> moves;
  in >> N;
  costs.resize(N);
  moves.resize(N);

  for (auto I=0; I<N; I++) {
    in >> costs[I];
  }
  for (auto I=0; I<N; I++) {
    in >> moves[I];
  }
  for (auto I=0; I<N; I++) {
    rooms.push_back(Node(I+1, costs[I]));
  }
  for (auto I=0; I<N; I++) {
    rooms[I].next = &rooms[moves[I]-1];
  }

  // vector<test> vt;
  // for (auto i=0; i<10; i++) {
  //   test t;
  //   t.a = i;
  //   t.b = i * i;
  //   vt.push_back(t);
  // }

  // for (auto& t : vt) {
  //   out << t.a << " " << t.b << endl;
  // }

  // for (auto& t : vt) {
  //   t->b = 0;
  // }

  // for (auto& t : vt) {
  //   out << t.a << " " << t.b << endl;
  // }

  RoomProcessor rp(rooms);
  auto res = rp.get_trap_cost();
  out << res << endl;
}

int main() {
  // Node one(1, 1);
  // Node two(2, 2);
  // Node three(3, 3);
  // Node four(4, 2);
  // Node five(5, 10);
  // one.next = &one;
  // two.next = &three;
  // three.next = &four;
  // four.next = &three;
  // five.next = &three;

  // vector<Node> rooms;
  // rooms.push_back(one);
  // rooms.push_back(two);
  // rooms.push_back(three);
  // rooms.push_back(four);
  // rooms.push_back(five);

  // RoomProcessor rp(rooms);

  // auto res = rp.get_trap_cost();
  // cout << "SUM: " << res << endl;
  ifstream in("data/d.in");
  function(in, cout);
  return 0;
}
