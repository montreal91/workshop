#
# Author: montreal91
# Type: contest
# Time: 00:18
# Failed attempts: 0
#

class Point:
    def __init__(self, x=0, y=0):
        self.x = x
        self.y = y


def get_required(dest):
    U, R, D, L = 0, 0, 0, 0
    if dest.x > 0:
        R = dest.x
    else:
        L = abs(dest.x)
    if dest.y > 0:
        U = dest.y
    else:
        D = abs(dest.y)
    return U, R, D, L


def compare(expected, got):
    for i in range(len(expected)):
        if expected[i] > got[i]:
            return False

    return True


def count_commands(command_string):
    counter = {"U": 0, "R": 0, "D": 0, "L": 0}
    for cmd in command_string:
        counter[cmd] += 1

    return counter["U"], counter["R"], counter["D"], counter["L"]


def verbose(res):
    if res:
        return "YES"
    return "NO"


if __name__ == '__main__':
    T = int(input())
    for _ in range(T):
        x, y = tuple(map(int, input().split(" ")))
        dest = Point(x=x, y=y)
        commands = input()
        print(verbose(
            compare(get_required(dest), count_commands(commands))
        ))
