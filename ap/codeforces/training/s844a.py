#
# Author: montreal91
# Time: 0:35
# Failed attempts: 0
#

def path(x, y, z, a, b, f, g):
    p1 = 2 * x - a - f + abs(b - g)
    p2 = a + f + abs(b - g)
    p3 = 2 * y - b - g + abs(a - f)
    p4 = b + g + abs(a - f)
    return min(p1, p2, p3, p4) + z


if __name__ == "__main__":
    T = int(input())
    for _ in range(T):
        x, y, z = tuple(map(int, input().split(" ")))
        a, b, f, g = tuple(map(int, input().split(" ")))
        print(path(x, y, z, a, b, f, g))
