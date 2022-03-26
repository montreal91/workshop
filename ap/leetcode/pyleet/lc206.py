#
# Author: montreal91
# Time: 0:30
# Failed attempts: 0
#

import unittest


class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def reverseList(self, head):
        if head is None:
            return None

        prev = None
        curr = head

        while curr is not None:
            next = curr.next

            curr.next = prev

            prev = curr
            curr = next

        return prev


class SolutionTests(unittest.TestCase):
    @staticmethod
    def _l_to_ll(lst):
        if not lst:
            return None

        head = ListNode(val=lst[0])
        prev = head

        for i in range(1, len(lst)):
            new_node = ListNode(val=lst[i])
            prev.next = new_node

            prev = new_node

        return head

    @staticmethod
    def _ll_to_l(head):
        res = []

        if head is None:
            return res

        curr = head
        while curr is not None:
            res.append(curr.val)
            curr = curr.next

        return res

    def test_utils_smoke(self):
        l1 = []
        self.assertIsNone(self._l_to_ll(l1))
        self.assertEqual(l1, self._ll_to_l(self._l_to_ll(l1)))

        l2 = [2402]
        self.assertEqual(l2, self._ll_to_l(self._l_to_ll(l2)))

        l3 = [2402, 2502, 2602, 2702, 2802, 103]
        self.assertEqual(l3, self._ll_to_l(self._l_to_ll(l3)))

    def test_solution0(self):
        input = []

        head = self._l_to_ll(input)
        self.assertIsNone(Solution().reverseList(head))

    def test_solution1(self):
        input = [1]
        expected = [1]

        head = self._l_to_ll(input)
        result = self._ll_to_l(Solution().reverseList(head))
        self.assertEqual(expected, result)

    def test_solution2(self):
        input = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
        expected = [10, 9, 8, 7, 6, 5, 4, 3, 2, 1]

        head = self._l_to_ll(input)
        result = self._ll_to_l(Solution().reverseList(head))
        self.assertEqual(expected, result)

if __name__ == "__main__":
    unittest.main()
