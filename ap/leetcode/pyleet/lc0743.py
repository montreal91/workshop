#
# Author: montreal91
# Time: N/A
# Failed attempts: 2
#

INTMAX = 10000000000
class Solution:
    def networkDelayTime(self, times, n, k) -> int:
        M = [[-1 for _ in range(n)] for _ in range(n)]
        for i in range(n):
            M[i][i] = 0

        for e in times:
            M[e[0]-1][e[1]-1] = e[2]

        T = [INTMAX for _ in range(n)]
        Q = set(range(n))
        T[k-1] = 0

        def get_best_unvisited_vertex():
            l = [(q, T[q]) for q in Q]
            l.sort(key=lambda x: x[1])
            return l[0][0]

        while len(Q) > 0:
            u = get_best_unvisited_vertex()
            if T[u] == INTMAX:
                break

            Q.remove(u)

            for i, w in enumerate(M[u]):
                if w == -1:
                    continue
                T[i] = min(T[i], T[u] + w)

        res = max(T)
        if res == INTMAX:
            return -1
        return res



if __name__ == '__main__':
    s = Solution()
    g1 = [[2,1,1],[2,3,1],[3,4,1]]
    g2 = [[1,2,1],[2,3,2],[2,5,1],[3,4,1],[4,3,2],[5,1,2]]
    g3 = [
        [1,2,0],
        [1,3,0],
        [1,4,43],
        [1,5,91],
        [2,1,1],
        [2,3,59],
        [2,4,23],
        [2,5,4],
        [3,1,36],
        [3,2,98],
        [3,4,22],
        [3,5,78],
        [4,1,16],
        [4,2,51],
        [4,3,59],
        [4,5,75],
        [5,1,15],
        [5,2,22],
        [5,3,85],
        [5,4,31],
    ]

    g4 = [[1,2,1],[1,3,3],[2,3,1]]
    g5 = [
        [1,2,3],
        [1,3,1],
        [1,5,6],
        [2,5,2],
        [3,2,1],
        [3,4,3],
        [4,2,1],
        [4,5,1]
    ]

    assert s.networkDelayTime(times=g1, n=4, k=1) == -1
    assert s.networkDelayTime(times=g1, n=4, k=2) == 2
    assert s.networkDelayTime(times=g1, n=4, k=3) == -1
    assert s.networkDelayTime(times=g1, n=4, k=4) == -1
    assert s.networkDelayTime(times=[], n=1, k=1) == 0

    assert s.networkDelayTime(times=g2, n=5, k=1) == 4
    assert s.networkDelayTime(times=g2, n=5, k=2) == 3
    assert s.networkDelayTime(times=g2, n=5, k=3) == -1
    assert s.networkDelayTime(times=g2, n=5, k=4) == -1
    assert s.networkDelayTime(times=g2, n=5, k=5) == 6

    assert s.networkDelayTime(times=g4, n=3, k=1) == 2
    assert s.networkDelayTime(times=g5, n=5, k=1) == 4
    assert s.networkDelayTime(times=g3, n=5, k=5) == 31
    print("All tests passed.")
