
TOLERANCE = 10 ** (-6)

def fixed_point(fun, first_guess):
    def close_enough(v1, v2):
        return abs(v1 - v2) < TOLERANCE
    def test(guess):
        nxt = fun(guess)
        if close_enough(guess, nxt):
            return nxt
        return test(nxt)
    return test(first_guess)


def average(*args):
    return sum(args) / len(args)

def sqrt1(x):
    return fixed_point(lambda y: average(y, x / y), 1.0)
    
