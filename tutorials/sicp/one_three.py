
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
    

def average_damp(f):
    return lambda x: average(x, f(x))


def square(x):
    return x * x


average_damp(square)(10)   # 55.0


def sqrt2(x):
    return fixed_point(average_damp(lambda y: x / y), 1.0)


sqrt2(2)   # 1.4142135623746899
dx = 10 ** (-6)


def deriv(g):
    return lambda x: (g(x + dx) - g(x)) / dx


def cube(x):
    return x * x * x


def newton_transform(g):
    return lambda x: x - g(x) / deriv(g)(x)


def newtons_method(g, guess):
    return fixed_point(newton_transform(g), guess)


def sqrt_newton(x):
    return newtons_method(lambda y: y * y - x, 1.0)

sqrt_newton(2)   # 1.4142135623754424


def compose(f, g):
    return lambda x: f(g(x))


def smooth(f):
    return lambda x: average(f(x - dx), f(x), f(x + dx))

smooth_square = smooth(square)

square(2.3)         # 5.289999999999999
smooth_square(2.3)  # 5.290000000000666
