#
# Author: montreal91
# Type: tutorial
# Time: N/A
# Failed attempts: 1
#

class Stuct:
    def __init__(self):
        self.leftmost = 0
        self.rightmost = 0
        self.frequency = 0


def get_data(books):
    C = {}
    for i, b in enumerate(books):
        if not b in C:
            C[b] = Stuct()
        C[b].frequency += 1
        C[b].rightmost = i

    for i, b in reversed(tuple(enumerate(books))):
        C[b].leftmost = i

    return C


def solve(books):
    data = get_data(books)
    Cf = {}
    DP = [0 for _ in range(len(books) + 1)]
    for i, ai in reversed(tuple(enumerate(books))):
        if ai not in Cf:
            Cf[ai] = 0
        Cf[ai] += 1
        DP[i] = DP[i+1]
        if i == data[ai].leftmost:
            DP[i] = max(DP[i], data[ai].frequency + DP[data[ai].rightmost+1])
        else:
            DP[i] = max(DP[i], Cf[ai])

    return len(books) - DP[0]


if __name__ == '__main__':
    N = int(input())
    books = tuple(map(int, input().split(" ")))
    print(solve(books))
