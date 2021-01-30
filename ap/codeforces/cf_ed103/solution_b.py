# //
# // Author: montreal91
# // Type: tutorial
# // Time: 0:27
# // Failed attempts: 2
# //


def solve(pies, k):
    sigma = 0
    x = 0

    for j, pj in enumerate(pies):
        if j == 0:
            sigma += pj
            continue
        val = max((100 * pj - k * sigma) / k, 0)
        x = max(x, int(val) + int(val % 1 > 0))
        sigma += pj
    return x


if __name__ == '__main__':
    T = int(input())
    for _ in range(T):
        n, k = tuple(map(int, input().split()))
        ppp = tuple(map(int, input().split()))
        print(solve(pies=ppp, k=k))
