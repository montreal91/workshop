
def naive_fibo(n):
    if n == 0:
        return 0
    elif n == 1:
        return 1
    else:
        return naive_fibo(n - 1) + naive_fibo(n - 2)

def iter_fibo(n):
    if n == 0:
        return 0

    prev1, prev2 = 0, 1
    for i in range(1, n+1):
        cur = prev1 + prev2
        prev2 = prev1
        prev1 = cur
    return cur


if __name__ == '__main__':
    [print(naive_fibo(i), iter_fibo(i)) for i in range(10)]
