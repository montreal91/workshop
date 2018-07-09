
import json


def multiply(a, b):
    print("Will compute", a, "times", b)
    _a = int(a)
    _b = int(b)
    c = 0
    for _ in range(_a):
        c += _b
    return str(c)


def divide(a, b):
    import sys
    print(sys.version)
    print("Will compute", a, "divided by", b)
    _a = float(a)
    _b = float(b)
    if _b == 0:
        raise Exception("Division by 0")
    else:
        return str(_a / _b);


def length(some_string):
    return len(some_string)


def foo():
    d = {}
    d["foo"] = 3
    res = json.dumps(d)
    return res
