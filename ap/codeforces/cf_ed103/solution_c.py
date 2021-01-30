#
# Author: montreal91
# Type: tutorial
# Time: 0:31
# Failed attempts: 0
#

def solve(chains, A, B):
    L = [0] * len(chains)
    for i, ci in enumerate(chains):
        if i == 0:
            continue
        if A[i] == B[i]:
            L[i] = ci + 1
            continue
        L[i] = max(L[i-1] - abs(A[i] - B[i]), abs(A[i] - B[i]))
        L[i] += ci + 1

    return max(L)


if __name__ == '__main__':
    T = int(input())
    for _ in range(T):
        n = int(input())
        chains = list(map(int, input().split(" ")))
        A = list(map(int, input().split(" ")))
        B = list(map(int, input().split(" ")))
        print(solve(chains, A, B))
