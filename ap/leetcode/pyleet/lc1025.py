#
# Author: montreal91
# Time: N/A
# Failed attempts: 0
#

class Solution:
    def divisorGame(self, n: int) -> bool:
        return n % 2 == 0


def test():
    s = Solution()
    assert s.divisorGame(1) == False
    assert s.divisorGame(2) == True
    assert s.divisorGame(3) == False
    assert s.divisorGame(4) == True
    assert s.divisorGame(5) == False
    assert s.divisorGame(6) == True
    assert s.divisorGame(7) == False
    assert s.divisorGame(8) == True
    assert s.divisorGame(9) == False
    assert s.divisorGame(10) == True
    assert s.divisorGame(12) == True
    assert s.divisorGame(13) == False
    assert s.divisorGame(14) == True
    assert s.divisorGame(15) == False
    assert s.divisorGame(16) == True
    print("All tests passed.")


if __name__ == '__main__':
    test()