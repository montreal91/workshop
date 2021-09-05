#
# Author: montreal91
# Time: 0:31
# Failed attempts: 0
#

class Solution:
    def productExceptSelf(self, nums):
        res = [1 for _ in enumerate(nums)]
        prefixes = Solution._makePrefixes(nums)
        suffixes = Solution._makeSuffixes(nums)
        for i in range(len(nums) - 1):
            res[i] = prefixes[i - 1] * suffixes[i + 1]
        res[0] = suffixes[1]
        res[-1] = prefixes[-2]
        return res

    @staticmethod
    def _makePrefixes(nums):
        res = [1 for _ in nums]
        for i, n in enumerate(nums):
            res[i] = n * res[i-1]
        return res
    
    @staticmethod
    def _makeSuffixes(nums):
        res = [1 for _ in range(len(nums) + 1)]
        for i, _ in enumerate(nums):
            ind = (len(nums) - i -1)
            res[ind] = nums[ind] * res[ind + 1]
        return res


if __name__ == "__main__":
    s = Solution()

    assert s.productExceptSelf([1, 2]) == [2, 1]
    assert s.productExceptSelf([1, 2, 3, 4]) == [24, 12, 8, 6]
    assert s.productExceptSelf([-1,1,0,-3,3]) == [0,0,9,0,0]
    assert s.productExceptSelf([0, 0]) == [0, 0]
    assert s.productExceptSelf([1, 1]) == [1, 1]
    print("All tests passed.")
