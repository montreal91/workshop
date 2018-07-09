
def exp1(a, b):
    """
    Raises base a to the exponent b.
    Recursive (linear growth).
    """
    if b == 0:
        return 1
    else:
        return a * exp1(a, b - 1)


def exp2(a, b):
    """
    Raises base a to the exponent b.
    Recursive (logarithmic growth).
    """
    def sqr(x):
        return x * x

    if b == 0:
        return 1

    if b == 1:
        return a

    if b % 2 == 0:
        return sqr(exp2(a, b / 2))
    else:
        return a * exp2(a, b - 1)


import unittest


class _ExponentiationTestCase(unittest.TestCase):
    def setUp(self):
        self._bases = list(range(1, 10))
        self._exponents = list(range(10))

    def test_exp1(self):
        for b in self._bases:
            self._exponentiation_checks(
                base=b,
                exponents=self._exponents,
                exp_function=exp1
            )


    def test_exp2(self):
        for b in self._bases:
            self._exponentiation_checks(
                base=b,
                exponents=self._exponents,
                exp_function=exp2
            )


    def _exponentiation_checks(self, base, exponents, exp_function):
        with self.subTest(base=base):
            for e in exponents:
                self.assertEqual(exp_function(base, e), base ** e)


if __name__ == '__main__':
    unittest.main()
