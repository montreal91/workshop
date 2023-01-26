
def guess(num):
    pass

class Solution:
    def guessNumber(self, n: int) -> int:
        left = 1
        right = n
        g = -1
        while g != 0:
            mid = (left + right) // 2
            g = guess(mid)
            if g < 0:
                right = mid - 1
                continue
            if g > 0:
                left = mid + 1
                continue
        return mid
