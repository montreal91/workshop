
//
// Problem: https://codeforces.com/contest/XXXX/problem/A
// Author: montreal91
// Type:
// Time:
// Failed attempts:
//

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <limits>
#include <map>
#include <stack>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#ifndef ONLINE_JUDGE
  #include "util.h"
#endif // ONLINE_JUDGE

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

ll pow_mod(ll base, ll power) {
  ll res = 1;
  for (ll i = 0; i < power; i++) {
    res *= base;
    res = res % MOD;
  }

  return res;
}

class Graph {
public:
  Graph(ll n) : nodes(), levels() {
    nodes.resize(n);
    levels.resize(n);
  }

  void add_edge(ll i, ll j) {
    nodes[i].push_back(j);
    nodes[j].push_back(i);
  }

  vector<vector<ll>> nodes;
  vector<ll> levels;
};

bool all_children_visited(ll node, const Graph& g, const vector<bool>& visited) {
  for (ll i=0; i<g.nodes[node].size(); i++) {
    if (!visited[g.nodes[node][i]]) {
      return false;
    }
  }

  return true;
}

ll mmax(const vector<ll>& children, const Graph& graph) {
  ll res = 0;
  for (ll i = 0; i < children.size(); i++) {
    res = max(res, graph.levels[children[i]]);
  }
  return res;
}


void calculate_levels(ll node, Graph* graph) {
  stack<ll> main_stack;
  vector<bool> visited;
  visited.resize(graph->levels.size());
  main_stack.push(node);

  ll cn;
  while (!main_stack.empty()) {
    cn = main_stack.top();
    visited[cn] = true;
    // leaf
    if (cn != 0 && graph->nodes[cn].size() == 1) {
      graph->levels[cn] = 1;
      main_stack.pop();
      continue;
    }

    if (all_children_visited(cn, *graph, visited)) {
      graph->levels[cn] = mmax(graph->nodes[cn], *graph) + 1;
      main_stack.pop();
      continue;
    }

    for (ll i = 0; i<graph->nodes[cn].size(); i++) {
      ll child = graph->nodes[cn][i];
      if (!visited[child]) {
        main_stack.push(child);
      }
    }
  }
}

ll solve(Graph* graph) {
  if (graph->nodes.size() == 1) {
    return 1;
  }

  calculate_levels(0, graph);
  ll res = 0;
  ll base = pow_mod(2, graph->nodes.size() - 1);

  for (ll i = 0; i < graph->levels.size(); i++) {
    res += base * graph->levels[i];
    res %= MOD;
  }

  return res;
}


void solution(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);

  ll T, n, i, j;
  in >> T;
  for (int ii = 0; ii < T; ii++) {
    in >> n;
    Graph graph(n);
    for (ll k = 0; k < n - 1; k++) {
      in >> i >> j;
      graph.add_edge(i-1, j-1);
    }
    out << solve(&graph) << endl;
  }
}

int main() {
  #ifndef ONLINE_JUDGE
    using namespace chrono;
    auto time1 = duration_cast<milliseconds>(
      system_clock::now().time_since_epoch()
    );
  #endif // ONLINE_JUDGE

  solution(cin, cout);

  #ifndef ONLINE_JUDGE
    auto time2 = duration_cast<milliseconds>(
      system_clock::now().time_since_epoch()
    );
    cout << "Time consumed: " << milliseconds(time2 - time1).count();
    cout << " ms.\n";
  #endif // ONLINE_JUDGE

  return 0;
}
