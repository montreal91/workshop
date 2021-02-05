#
# Author: montreal91
# Type: tutorial
# Time: N/A
# Failed attempts: 5
#

def get_best_edge(graph):
    for i in range(len(graph) - 1):
        for j in range(i + 1, len(graph)):
            if graph[i][j] == graph[j][i]:
                return True, i, j
    # Doesn't matter, all edges are a-b
    return False, 0, 1, 2


def solve(graph, m):
    x = get_best_edge(graph)

    res = []
    if x[0] or m % 2 == 1:
        for i in range(m+1):
            if  i % 2 == 0:
                res.append(str(x[1] + 1))
            else:
                res.append(str(x[2] + 1))
        return res
    if len(graph) == 2:
        return res

    return solve_on_first3(graph, m)


def check_short_cycle(graph):
    if graph[0][:3] == "*ba" and graph[1][:3] == "a*b":
        return True
    if graph[0][:3] == "*ab" and graph[1][:3] == "b*a":
        return True
    return False


def get_three_nodes(graph):
    if graph[0][1] != graph[0][2]:
        return 2, 0, 1
    if graph[1][0] != graph[1][2]:
        return 0, 1, 2
    if graph[2][0] != graph[2][1]:
        return 0, 2, 1


def solve_on_first3(graph, m):
    res = []
    if check_short_cycle(graph):
        for i in range(m+1):
            res.append(str(i % 3 + 1))
        return res

    x, y, z = get_three_nodes(graph)
    if (m // 2 % 2 == 1):
        for i in range(m + 1):
            if i % 4 == 0:
                res.append(str(x + 1))
            elif i % 4 == 1:
                res.append(str(y + 1))
            elif i % 4 == 2:
                res.append(str(z + 1))
            elif i % 4 == 3:
                res.append(str(y + 1))
    else:
        for i in range(m + 1):
            if i % 4 == 0:
                res.append(str(y + 1))
            elif i % 4 == 1:
                res.append(str(z + 1))
            elif i % 4 == 2:
                res.append(str(y + 1))
            elif i % 4 == 3:
                res.append(str(x + 1))
    return res


if __name__ == '__main__':
    T = int(input())
    for _ in range(T):
        n, m = tuple(map(int, input().split(" ")))
        graph = []
        for i in range(n):
            graph.append(input())
        answer = solve(graph, m)
        if len(answer) > 0:
            print("YES")
            print(" ".join(answer))
        else:
            print("NO")
