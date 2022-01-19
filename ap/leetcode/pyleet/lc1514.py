#
# Author: montreal91
# Time: N/A
# Failed attempts: 4
#

import heapq


EPS = 1e-5

class Solution:
    def maxProbability(self, n: int, edges, succProb, start, end):
        matrix = Solution._makeMatrix(n, edges, succProb)
        visited = [False for _ in range(n)]
        probabilities = [0 for _ in range(n)]
        probabilities[start] = 1

        queue = []
        heapq.heappush(queue, (-1, start))

        while queue:
            current_prob, current = heapq.heappop(queue)

            if current == end:
                return -current_prob
            if not current in matrix:
                continue
            visited[current] = True
            for i, prob in matrix[current]:

                if visited[i] or equals(prob, 0.0, EPS):
                    continue
                tentative = -current_prob * prob
                probabilities[i] = max(probabilities[i], tentative)
                heapq.heappush(queue, (-probabilities[i], i))
        return 0


    @staticmethod
    def _makeMatrix(n, edges, succProb):
        graph={}
        for i,[u,v] in enumerate(edges):
            graph[u]=graph.get(u,[])+[(v,succProb[i])]
            graph[v]=graph.get(v,[])+[(u,succProb[i])]

        return graph


def testLeet1():
    n = 3
    edges = [(0, 1), (0, 2), (1, 2)]
    succProb = [0.5, 0.2, 0.5]

    assert equals(
        0.25,
        Solution().maxProbability(
            n=n,
            edges=edges,
            succProb=succProb,
            start=0,
            end=2
        ),
        EPS
    )


def testLeet2():
    n = 3
    edges = [(0, 1), (0, 2), (1, 2)]
    succProb = [0.5, 0.3, 0.5]

    assert equals(
        0.3,
        Solution().maxProbability(
            n=n,
            edges=edges,
            succProb=succProb,
            start=0,
            end=2
        ),
        EPS
    )

def testLeet3():
    n = 3
    edges = [(0, 1)]
    succProb = [0.5]

    assert equals(
        0.0,
        Solution().maxProbability(
            n=n,
            edges=edges,
            succProb=succProb,
            start=0,
            end=2
        ),
        EPS
    )

def testCompare():
    assert equals(0.333, 1/3, eps=0.001)
    assert not equals(0.333, 1/3, eps=0.0001)

def equals(a, b, eps):
    return abs(a - b) < eps


def testWrongAnswer1():
    n = 5
    edges = [[1,4],[2,4],[0,4],[0,3],[0,2],[2,3]]
    succProb = [0.37,0.17,0.93,0.23,0.39,0.04]

    assert equals(
        0.21390,
        Solution().maxProbability(
            n=n, edges=edges, succProb=succProb, start=3, end=4
        ),
        EPS
    )


def testKeyError():
    n = 500
    edges = [[193,229],[133,212],[224,465]]
    succProb = [0.91,0.78,0.64]

    assert equals(
        0,
        Solution().maxProbability(
            n=n, edges=edges, succProb=succProb, start=4, end=364
        ),
        EPS
    )



if __name__ == "__main__":
    testCompare()
    testLeet1()
    testLeet2()
    testLeet3()
    testWrongAnswer1()
    testKeyError()
    print("All tests passed.")
