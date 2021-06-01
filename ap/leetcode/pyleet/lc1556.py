#
# Author: montreal91
# Time: 0:29
# Failed attempts: 1
#

from collections import deque


class Solution:
    def thousandSeparator(self, n):
        if n == 0:
            return "0"
        
        A = deque()

        while n >= 1000:
            A.appendleft("{0:03d}".format(n % 1000))
            n = n // 1000

        if n > 0:
            A.appendleft(str(n))
        
        return ".".join(A)
        

if __name__ == '__main__':
    s = Solution()

    assert s.thousandSeparator(0) == "0"
    assert s.thousandSeparator(3) == "3"
    assert s.thousandSeparator(33) == "33"
    assert s.thousandSeparator(345) == "345"
    assert s.thousandSeparator(1342) == "1.342"
    assert s.thousandSeparator(61342) == "61.342"
    assert s.thousandSeparator(613425) == "613.425"
    assert s.thousandSeparator(7613425) == "7.613.425"
    assert s.thousandSeparator(76134259) == "76.134.259"
    assert s.thousandSeparator(761342590) == "761.342.590"
    assert s.thousandSeparator(8761342590) == "8.761.342.590"
    assert s.thousandSeparator(1010) == "1.010"

    print("All tests passed.")