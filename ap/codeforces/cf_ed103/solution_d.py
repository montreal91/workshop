
class City:
    def __init__(self, left=None, right=None):
        self.left = left
        self.right = right
        self.can_visit = -1

    def has_outs(self):
        return self.left == "L" or self.right == "R"

    def __str__(self):
        return f"City: ({self.left}, {self.right})"

def build_cities(roads):
    cities = [City() for _ in range(len(roads) + 1)]

    for i, road in enumerate(roads):
        cities[i].right = road
        cities[i+1].left = road
    return cities


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

    def traverse(s):
        i = s
        j = s

        while can_move_left(i=i, start=s):
            i -= 1

        while can_move_right(j=j, start=s):
            j += 1


        cities[s].can_visit = j - i + 1

    for c, city in enumerate(cities):
        if city.can_visit > 0:
            continue
        traverse(c)

def print_answer(cities):
    vals = [str(city.can_visit) for city in cities]
    print(" ".join(vals))


if __name__ == '__main__':
    T = int(input())
    for _ in range(T):
        input()
        cities = build_cities(input())
        solve(cities)
        print_answer(cities)
