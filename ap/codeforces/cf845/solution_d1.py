
from collections import deque

MOD = 10 ** 9 + 7


class Graph:
    def __init__(self, size):
        self.nodes = [[] for _ in range(size)]
        self.levels = [0 for _ in range(size)]

    def append_edge(self, i, j):
        self.nodes[i].append(j)
        self.nodes[j].append(i)


def calculate_levels(node, graph):
    stack = deque()
    stack.append(node)
    visited = set()
    visited.add(node)

    def all_children_visited(children):
        return all(c in visited for c in children)

    while stack:
        cn = stack[-1]
        visited.add(cn)
        if cn != 0 and len(graph.nodes[cn]) == 1:
            graph.levels[cn] = 1
            stack.pop()
            continue

        if all_children_visited(graph.nodes[cn]):
            graph.levels[cn] = max(graph.levels[child] for child in graph.nodes[cn]) + 1
            stack.pop()
            continue

        for child in graph.nodes[cn]:
            if not child in visited:
                stack.append(child)


def solve(graph):
    if len(graph.nodes) == 1:
        return 1

    calculate_levels(0, graph)
    res = 0
    base = 2 ** (len(graph.nodes) - 1)
    for level in graph.levels:
        res += base * level
    return res % MOD


if __name__ == "__main__":
    import time
    T = int(input())
    for _ in range(T):
        n = int(input())
        graph = Graph(n)
        for __ in range(n - 1):
            i, j = tuple(map(int, input().split(" ")))
            graph.append_edge(i-1, j-1)

        t1 = time.monotonic_ns()
        print(solve(graph))
        t2 = time.monotonic_ns()
        print(f"Time: {(t2 - t1)} ns")
        # print(graph.levels)

