
# https://codeforces.com/contest/1121/problem/B

def calculate_invited_kids(sweets):
    combos = {}
    for i in range(len(sweets) - 1):
        for j in range(i + 1, len(sweets)):
            combo = sweets[i] + sweets[j]
            combos.setdefault(combo, 0)
            combos[combo] += 1
    return max(combos.values())


if __name__ == '__main__':
    n = int(input())
    sweets = []
    sweets.extend(map(int, input().split(" ")))

    print(calculate_invited_kids(sweets))
