#
# Author: montreal91
# Time: 1:30
# Failed attempts: 1
#

import unittest
import heapq


class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

    def __repr__(self):
        next_val = None
        if self.next is not None:
            next_val = self.next.val
        return f"Node [{self.val} -> {next_val}]"

    def __str__(self) -> str:
        return self.__repr__()


MAX = 100000


class Merger:
    def __init__(self, nodes):
        self._value_heap = []
        for node in nodes:
            curr = node
            while curr is not None:
                self._value_heap.append(curr.val)
                curr = curr.next

        heapq.heapify(self._value_heap) # O(N)

    def merged_values(self):
        while self._value_heap:
            yield heapq.heappop(self._value_heap)


class Solution:
    def mergeKLists(self, lists):
        prev = None
        head = None

        merger = Merger(lists)

        for value in merger.merged_values():
            new_node = ListNode(value)
            if prev is None:
                head = new_node
            else:
                prev.next = new_node
            prev = new_node
        return head


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

    def test_solution0(self):
        input = []
        self.assertIsNone(Solution().mergeKLists(input))

    def test_solution1(self):
        raw_input = [[]]
        actual_input = [self._l_to_ll(l) for l in raw_input]
        expected = []

        self.assertEqual(self._ll_to_l(Solution().mergeKLists(actual_input)), expected)

    def test_solution2(self):
        raw_input = [[], [], []]
        actual_input = [self._l_to_ll(l) for l in raw_input]
        expected = []

        self.assertEqual(self._ll_to_l(Solution().mergeKLists(actual_input)), expected)

    def test_solution3(self):
        raw_input = [[1], [2], []]
        actual_input = [self._l_to_ll(l) for l in raw_input]
        expected = [1, 2]

        self.assertEqual(self._ll_to_l(Solution().mergeKLists(actual_input)), expected)

    def test_solution4(self):
        raw_input = [[1], [2], []]
        actual_input = [self._l_to_ll(l) for l in raw_input]
        expected = [1, 2]

        self.assertEqual(self._ll_to_l(Solution().mergeKLists(actual_input)), expected)

    def test_solution5(self):
        raw_input = [[1, 3, 5], [2, 4, 6], [1, 2, 3, 4, 5, 6], []]
        actual_input = [self._l_to_ll(l) for l in raw_input]
        expected = [1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6]

        self.assertEqual(self._ll_to_l(Solution().mergeKLists(actual_input)), expected)

    def test_solution6(self):
        raw_input = [[1, 3, 5, 7], [2, 4, 6, 8], [1, 2, 3, 4, 5, 6, 7, 8], []]
        actual_input = [self._l_to_ll(l) for l in raw_input]
        expected = [1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8]

        self.assertEqual(self._ll_to_l(Solution().mergeKLists(actual_input)), expected)


if __name__ == "__main__":
    unittest.main()
