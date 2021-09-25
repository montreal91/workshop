#
# Author: montreal91
# Time: 1:15
# Failed attempts: 0
#

class Solution:
    def fractionToDecimal(self, numerator, denominator):
        res = []
        if (numerator * denominator) < 0:
            res.append("-")
        m = abs(numerator)
        n = abs(denominator)
        res.append(str(m // n))

        rems = {}
        rem = m % n
        while rem != 0 and not rem in rems:
            rems[rem] = str((rem * 10) // n)
            rem = (rem * 10) % n

        if len(rems) > 0:
            res.append(".")

        for r, v in rems.items():
            if r == rem:
                res.append("(")
            res.append(v)

        if rem != 0:
            res.append(")")
        print("".join(res))
        return "".join(res)


if __name__ == "__main__":
    assert Solution().fractionToDecimal(1, 1) == "1"
    assert Solution().fractionToDecimal(1, 2) == "0.5"
    assert Solution().fractionToDecimal(1, 3) == "0.(3)"
    assert Solution().fractionToDecimal(1, 15) == "0.0(6)"
    assert Solution().fractionToDecimal(1, 7) == "0.(142857)"
    assert Solution().fractionToDecimal(1, 21) == "0.(047619)"
    assert Solution().fractionToDecimal(1, 1024) == "0.0009765625"
    assert Solution().fractionToDecimal(3, 2) == "1.5"
    assert Solution().fractionToDecimal(4, 3) == "1.(3)"
    assert Solution().fractionToDecimal(1024, 100) == "10.24"

    print("All tests passed.")
