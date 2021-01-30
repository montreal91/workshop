#
# Author: montreal91
# Type: practice
# Time: 00:55
# Failed attempts: 1
#

from math import factorial


def cnk(n, k):
    return factorial(n) // factorial(k) // factorial(n - k)


def get_bloggers(bs, l):
    if l >= len(bs):
        return 1
    bs.sort(reverse=True)
    n = bs.count(bs[l])
    k = bs[:l].count(bs[l])
    return cnk(n, k) % (10 ** 9 + 7)


if __name__ == '__main__':
    t = int(input())
    for _ in range(t):
        n, k = tuple(map(int, input().split(" ")))
        bloggers = list(map(int, input().split(" ")))
        print(get_bloggers(bloggers, k))
