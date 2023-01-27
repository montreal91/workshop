
class SortedTracker:
    def __init__(self):
        self._nums = []

    def insert(self, num):
        i = self._find(num)
        self._nums.insert(i, num)

    def remove(self, num):
        i = self._find(num)
        self._nums.pop(i)

    def getMedian(self):
        l = len(self._nums)
        if l % 2 == 1:
            return self._nums[l // 2]

        m = l // 2
        return (self._nums[m] + self._nums[m-1]) / 2

    def _find(self, num):
        if len(self._nums) == 0:
            return 0

        left, right = 0, len(self._nums) - 1

        while True:
            mid = (left + right) // 2

            if self._nums[mid] == num:
                return mid
            if num < self._nums[mid] and self._nums[mid-1] < num:
                return mid

            if mid == len(self._nums) - 1 and self._nums[mid] < num:
                return mid + 1

            if mid == 0 and num < self._nums[mid]:
                return 0

            if num < self._nums[mid]:
                right = mid - 1
                continue
            if self._nums[mid] < num:
                left = mid + 1
                continue


class Solution:
    def medianSlidingWindow(self, nums, k):
        st = SortedTracker()
        for n in nums[:k]:
            st.insert(n)

        i = 0
        j = k - 1
        res = []
        while j < len(nums):
            res.append(st.getMedian())
            st.remove(nums[i])
            i += 1
            j += 1
            st.insert(nums[j % len(nums)])
        return res



def compare(actual, expected):
    assert len(actual) == len(expected)
    assert all(almost_equal(actual[i], expected[i], 0.000001) for i in range(len(actual)))


def almost_equal(d1, d2, epsilon):
    return abs(d1 - d2) < epsilon


if __name__ == "__main__":
    compare(
      Solution().medianSlidingWindow([1,3,-1,-3,5,3,6,7], k=3),
      [1.00000,-1.00000,-1.00000,3.00000,5.00000,6.00000]
    )
    compare(
      Solution().medianSlidingWindow([1,2,3,4,2,3,1,4,2], k=3),
      [2.00000,3.00000,3.00000,3.00000,2.00000,3.00000,2.00000]
    )
    compare(
      Solution().medianSlidingWindow([1,3,-1,-3,5,3,6,7], k=4),
      [0.00000,1.00000,1.00000,4.00000,5.50000]
    )
    compare(
      Solution().medianSlidingWindow([1,3,-1,-3,5,3,6,7], k=5),
      [1.00000,3.00000,3.00000,5.00000]
    )
    print("All tests passed.")
