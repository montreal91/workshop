from random import random

def coinfilp():
    x = random()
    return int(x > 0.5)

def h1():
    cf = (0,0)
    while cf == (0,0):
        cf = (coinfilp(), coinfilp())
    return cf

def hypothetic_function():
    s1, s2, s3 = 0, 0, 0
    for i in range(1000):
        cf = h1()
        if (cf == (0, 1)):
            s1 += 1
        elif cf == (1, 0):
            s2 += 1
        elif cf == (1, 1):
            s3 += 1
    print(s1 / 1000, s2 / 1000, s3 / 1000)


def args_generator(base):
    for i in range(base):
        for j in range(base):
            yield i, j

def decimal_to_base(val, base):
    res = []
    while val // base >= base:
        res.append(val % base)
        val //= base
    res.append(val % base)
    res.append(val // base)
    return res

def all_possible_results_generator(base):
    for i in range(base ** (base ** 2)):
        res = decimal_to_base(i, base)
        yield res + [0 for i in range(base ** 2 - len(res))]

class KLogicFunction(object):
    def __init__(self, base, results):
        assert len(results) == base ** 2
        self._base = base
        self._dict = {}
        i = 0
        for args in args_generator(base):
            self._dict[args] = results[i]
            i += 1

    def __call__(self, a, b):
        return self._dict[(a, b)]

    @property
    def base(self):
        return self._base

fun1 = KLogicFunction(2, [0, 1, 1, 0])
fun2 = KLogicFunction(2, [1, 0, 0, 0])
fun3 = KLogicFunction(2, [1, 1, 1, 0])

def all_functions_generator(base):
    for res in all_possible_results_generator(base):
        yield KLogicFunction(base, res)

def print_test_one_function(function, probs_dict):
    res = {}
    for i in range(function.base):
        res[i] = 0
    for args in args_generator(function.base):
        p = probs_dict[args[0]] * probs_dict[args[1]]
        res[function(*args)] += p

    for key in res:
        print("{0:.4f}".format(res[key]), end="  ")

def print_all_functions(base, probs_dict):
    for function in all_functions_generator(base):
        # print(type(function))
        print_test_one_function(function, probs_dict)
        print()

print_all_functions(3, {0:0.0625, 1:0.375, 2:0.5625})

# for f in all_functions_generator(2):
#     for args in args_generator(2):
#         print(f(*args), end=" ")
#     print()


# print(decimal_to_base(4, 2))