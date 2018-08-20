
from random import randint


def fermat_test(n):
    if n == 2 or n == 3:
        return True
    elif n < 5:
        return False

    def try_it(a):
        return a == a ** n % n

    return try_it(1 + randint(1, n-1))


def fast_prime(n, times):
    for i in range(times):
        if not fermat_test(n):
            return False
    return True


if __name__ == '__main__':
    for i in range(2, 50):
        print("{0:2d}: {1}".format(i, fast_prime(i, 10)))

