#
# Author: montreal91
# Time: 0:36
# Failed attempts: 0
#

class Solution:
    def peakIndexInMountainArray(self, arr):
        # It has only one peak, so binary search is applicable
        left = 0
        right = len(arr) - 1
        i = (left + right) // 2
        while not isGoodPeak(arr, i) and left < right:
            if arr[i-1] > arr[i] > arr[i+1]:
                right = i
                i = (left + right) // 2
            elif arr[i-1] < arr[i] < arr[i+1]:
                left = i
                i = (left + right) // 2
        return i


def isGoodPeak(arr, i):
    if not 0 < i < len(arr) - 1:
        return False
    return arr[i-1] < arr[i] and arr[i] > arr[i+1]

if __name__ == "__main__":
    assert Solution().peakIndexInMountainArray([0, 1, 0]) == 1
    assert Solution().peakIndexInMountainArray([0, 2, 1, 0]) == 1
    assert Solution().peakIndexInMountainArray([0, 4, 3, 2, 1]) == 1
    assert Solution().peakIndexInMountainArray([0, 3, 4, 2, 1]) == 2
    assert Solution().peakIndexInMountainArray([0, 2, 3, 4, 1]) == 3
    assert Solution().peakIndexInMountainArray([0, 5, 4, 3, 2, 1]) == 1
    assert Solution().peakIndexInMountainArray([0, 4, 5, 3, 2, 1]) == 2
    assert Solution().peakIndexInMountainArray([0, 3, 4, 5, 2, 1]) == 3
    assert Solution().peakIndexInMountainArray([0, 2, 3, 4, 5, 1]) == 4
    print("All tests passed.")
