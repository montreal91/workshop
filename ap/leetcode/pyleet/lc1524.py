#
# Author: montreal91
# Time: 1:29
# Failed attempts: 1
#

class Solution:
    def numOfSubarrays(self, arr):
        s = 0
        sumsum = [0 for _ in range(1, len(arr) + 1)]
        for i, a in enumerate(arr):
            s += a
            sumsum[i] = s
        res = 0
        odd = 0
        for i, sm in enumerate(sumsum):
            if sm % 2 == 1:
                odd += 1
                res += 1
                res += (i + 1) - odd
            else:
                res += odd

        return res

    def naive(self, arr):
        res = 0
        for i, _ in enumerate(arr):
            for j in range(i+1, len(arr)+1):
                res += sum(arr[i:j]) % 2

        return res



if __name__ == '__main__':
    s = Solution()

    arr1 = [1,3,5]
    arr2 = [2,4,6]
    arr3 = [1,2,3,4,5,6,7]
    arr4 = [100,100,99,99]
    arr5 = [7]

    arr6 = [1, 1, 0, 0, 0]
    arr7 = [1, 1, 0, 0, 1]
    arr8 = [1, 0, 1, 0, 0]
    arr9 = [1, 0, 1, 0, 1]

    assert s.numOfSubarrays(arr1) == s.naive(arr1)
    assert s.numOfSubarrays(arr2) == s.naive(arr2)
    assert s.numOfSubarrays(arr3) == s.naive(arr3)
    assert s.numOfSubarrays(arr4) == s.naive(arr4)
    assert s.numOfSubarrays(arr5) == s.naive(arr5)

    assert s.numOfSubarrays(arr6) == s.naive(arr6)
    assert s.numOfSubarrays(arr7) == s.naive(arr7)
    assert s.numOfSubarrays(arr8) == s.naive(arr8)
    assert s.numOfSubarrays(arr9) == s.naive(arr9)

    print("All tests passed.")
