#
# Author: montreal91
# Type: tutorial
# Time: 0:31
# Failed attempts: 0
#


class City:
    def __init__(self, left=None, right=None):
        self.left = left
        self.right = right
        self.can_visit = -1

    def has_outs(self):
        return self.left == "L" or self.right == "R"

    def __str__(self):
        return f"City: ({self.left}, {self.right})"


def solve(cities):
    def can_move_left(i, start):
        if cities[i].left is None:
            return False
        if abs(i - start) % 2 == 0:
            return cities[i].left == "L"
        return cities[i].left == "R"

    def can_move_right(j, start):
        if cities[j].right is None:
            return False
        if abs(j - start) % 2 == 0:
            return cities[j].right == "R"
        return cities[j].right == "L"

    lmost = [i for i in range(len(cities))]

    if cities[1].left == "L":
        lmost[1] = 0

    for i, city in enumerate(cities):
        if i < 2:
            continue
        if city.left == "L":
            lmost[i] = i - 1

            if can_move_left(i=i-1, start=i):
                lmost[i] = lmost[i-2]

    rmost = [i for i in range(len(cities))]
    if cities[len(cities) - 2].right == "R":
        rmost[len(cities) - 2] = len(cities) - 1

    for i, city in reversed(list(enumerate(cities))):
        if len(cities) - i < 2:
            continue

        if city.right == "R":
            rmost[i] = i + 1

            if can_move_right(j=i+1, start=i):
                rmost[i] = rmost[i+2]

    return [rmost[i] - lmost[i] + 1 for i, _ in enumerate(cities)]


def build_cities(roads):
    cities = [City() for _ in range(len(roads) + 1)]

    for i, road in enumerate(roads):
        cities[i].right = road
        cities[i+1].left = road
    return cities


if __name__ == '__main__':
    T = int(input())
    for _ in range(T):
        input()
        cities = build_cities(input())
        res = [str(s) for s in solve(cities)]
        print(" ".join(res))
