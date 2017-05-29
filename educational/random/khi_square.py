import math

def calculate_khi(n, array):
    res = 0
    for i in range(len(array)):
        pi = density(i)
        print(i, "{0:.3f}".format(pi))
        r = ((array[i] - n * pi) ** 2) / (pi * n)
        res += r
    return res

def density(k):
    a = math.exp(-3.9) * 3.9**k
    b = math.factorial(k)
    return a / b

m = [57, 203, 383, 525, 532, 408, 273, 139, 45, 27, 16]
print(sum(m))
print(calculate_khi(2608, m))