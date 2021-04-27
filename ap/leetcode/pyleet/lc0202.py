#
# Author: montreal91
# Time: 0:09
# Failed attempts: 0
#

class Solution:
    def isHappy(self, n):
        sums = {}
        while n not in sums:
            sums[n] = self.checksum(n)
            n = sums[n]

        return 1 in sums

    @staticmethod
    def checksum(n):
        res = 0
        while n > 0:
            d = n % 10
            res += d * d
            n //= 10
        return res



if __name__ == '__main__':
    s = Solution()

    assert s.isHappy(19) == True
    assert s.isHappy(100) == True
    assert s.isHappy(1) == True
    assert s.isHappy(2) == False
    assert s.isHappy(1024) == False
    assert s.isHappy(2147483647) == False

    print("All tests passed.")
