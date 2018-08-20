
def find_divisor(n, test_divisor):
    if test_divisor ** 2 > n:
        return n

    elif n % test_divisor == 0:
        return test_divisor


    return find_divisor(n, test_divisor + 1)


def smallest_divisor(n):
    return find_divisor(n, 2)


def is_prime(n):
    return n == smallest_divisor(n)


if __name__ == "__main__":
    for i in range(50):
        print("{0:2d}: {1:b}".format(i, is_prime(i)))
