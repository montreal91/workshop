
def solution(lst):
    res = 0
    for i in range(1, len(lst)):
        if (lst[i] % 2 == lst[i-1] % 2):
            res += 1

    return res

if __name__ == "__main__":
    T = int(input())
    for _ in range(T):
        n = int(input())
        l = list(map(int, input().split(" ")))
        print(solution(l))

