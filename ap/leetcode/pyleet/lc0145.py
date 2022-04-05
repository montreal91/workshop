#
# Author: montreal91
# Time: 0:20
# Failed attempts: 0
#

from collections import deque
import unittest


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def postorderTraversal(self, root):
        res = []
        self._solve_recursive(root, res)
        return res

    def _solve_recursive(self, node, res):
        if node is None:
            return

        self._solve_recursive(node.left, res)
        self._solve_recursive(node.right, res)

        res.append(node.val)



class SolutionTestCase(unittest.TestCase):
    def test_none(self):
        self.assertEqual([], Solution().postorderTraversal(None))

    def test_one_node_tree(self):
        self.assertEqual([1], Solution().postorderTraversal(TreeNode(1)))

    def test_tree1(self):
        root = test_tree1()

        self.assertEqual(
            [4, 8, 9, 5, 2, 6, 11, 10, 7, 3, 1],
            Solution().postorderTraversal(root=root)
        )


def test_tree1():
    one = TreeNode(1)
    two = TreeNode(2)
    three = TreeNode(3)
    four = TreeNode(4)
    five = TreeNode(5)
    six = TreeNode(6)
    seven = TreeNode(7)
    eight = TreeNode(8)
    nine = TreeNode(9)
    ten = TreeNode(10)
    eleven = TreeNode(11)

    ten.left = eleven
    seven.right = ten
    five.left = eight
    five.right = nine
    three.left = six
    three.right = seven
    two.left = four
    two.right = five
    one.left = two
    one.right = three

    return one

if __name__ == "__main__":
    unittest.main()
