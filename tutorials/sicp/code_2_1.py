
class Rational:
    _denominator: int
    _numerator: int

    def __add__(self, other: "Rational") -> "Rational":
        val1 = self._numerator * other._denominator
        val2 = other._numerator * self._denominator
        return Rational(
            val1 + val2,
            self._denominator * other._denominator
        )

    def __truediv__(self, other: "Rational") -> "Rational":
        return Rational(
            self._numerator * other._denominator,
            self._denominator * other._numerator
        )

    def __init__(self, numerator: int, denominator: int = 1):
        if denominator == 0:
            raise ValueError("Denominator can not be 0.")

        def gcd(a: int, b: int) -> int:
            if b == 0:
                return a
            return gcd(b, a % b)

        divisor = gcd(numerator, denominator)
        self._numerator = numerator // divisor
        self._denominator = denominator // divisor

    def __eq__(self, rat: "Rational") -> bool:
        return self._numerator == rat._numerator and self._denominator == rat._denominator

    def __mul__(self, other: "Rational") -> "Rational":
        return Rational(
            self._numerator * other._numerator,
            self._denominator * other._denominator,
        )

    def __repr__(self) -> str:
        return str(self._numerator / self._denominator)

    def __sub__(self, other: "Rational"):
        val1 = self._numerator * other._denominator
        val2 = other._numerator * self._denominator
        return Rational(
            val1 - val2,
            self._denominator * other._denominator
        )


if __name__ == "__main__":
    r1 = Rational(1, 2)
    r2 = Rational(1, 3)
    r3 = Rational(2, 4)
    assert r1 == r3, "Equality fail"
    assert r1 != r2, "Inequality fail"
    assert r1 + r2 == Rational(5, 6), "Addition fail"
    assert r1 - r2 == Rational(1, 6), "Subtraction fail"
    assert r1 * r2 == Rational(1, 6), "Multiplication fail"
    assert r1 / r2 == Rational(3, 2), "Division fail"
    r3 *= r3
    assert r3 == Rational(1, 4)
    print("OK")
