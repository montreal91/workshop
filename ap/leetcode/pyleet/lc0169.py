#
# Author: montreal91
# Time: 0:14
# Failed attempts: 0
#

class Solution:
    def majorityElement(self, nums):
        vals = {}
        for n in nums:
            if n in vals:
                vals[n] += 1
            else:
                vals[n] = 1

        for n, count in vals.items():
            if count > len(nums) // 2:
                return n


if __name__ == '__main__':
    s = Solution()

    assert s.majorityElement([1, 2, 1]) == 1
    assert s.majorityElement([1, 2, 1, 3, 1]) == 1 # ask about corner case
    assert s.majorityElement([1]) == 1
    print("All tests passed.")
