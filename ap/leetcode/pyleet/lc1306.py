#
# Author: montreal91
# Time: 0:45
# Failed attempts: 0
#

from turtle import right
from unittest import TestCase
from collections import deque


class Solution:
    def canReach(self, arr, start):
        queue = deque()
        visited = set()

        queue.append(start)

        while queue:
            i = queue.popleft()

            if arr[i] == 0:
                return True

            visited.add(i)

            left = i - arr[i]
            if left >= 0 and left not in visited:
                queue.append(left)

            right = i + arr[i]
            if right < len(arr) and right not in visited:
                queue.append(right)

        return False


class SolutionTestCase(TestCase):
    def test_solution0(self):
        arr = [0]
        self.assertTrue(Solution().canReach(arr=arr, start=0))

    def test_solution1(self):
        arr = [0, 2]
        self.assertTrue(Solution().canReach(arr=arr, start=0))
        self.assertFalse(Solution().canReach(arr=arr, start=1))

    def test_solution1(self):
        arr = [5, 3, 2, 1, 3, 4, 1, 3, 1, 0]
        self.assertTrue(Solution().canReach(arr=arr, start=0))
        self.assertTrue(Solution().canReach(arr=arr, start=2))
        self.assertTrue(Solution().canReach(arr=arr, start=3))
        self.assertTrue(Solution().canReach(arr=arr, start=5))
        self.assertTrue(Solution().canReach(arr=arr, start=6))
        self.assertTrue(Solution().canReach(arr=arr, start=8))
        self.assertTrue(Solution().canReach(arr=arr, start=9))

        self.assertFalse(Solution().canReach(arr=arr, start=1))
        self.assertFalse(Solution().canReach(arr=arr, start=4))
        self.assertFalse(Solution().canReach(arr=arr, start=7))

    def test_lc1(self):
        lc = [4,2,3,0,3,1,2]
        self.assertTrue(Solution().canReach(lc, 5))

    def test_lc2(self):
        lc = [4,2,3,0,3,1,2]
        self.assertTrue(Solution().canReach(lc, 0))

    def test_lc3(self):
        lc = [3,0,2,1,2]
        self.assertFalse(Solution().canReach(lc, 2))


if __name__ == "__main__":
    import unittest
    unittest.main()

