
from math import factorial

MOD = 10 ** 9 + 7

def solution(n):
    return (n * (n - 1) * factorial(n)) % MOD


if __name__ == "__main__":
    T = int(input())
    for _ in range(T):
        n = int(input())
        print(solution(n))
