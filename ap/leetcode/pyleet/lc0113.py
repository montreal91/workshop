# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
# 14:00
# 14:37

from collections import deque


def traverse(node, path, curSum, targetSum, result):
    curSum += node.val
    path.append(node.val)

    if node.left is None and node.right is None:
        if curSum == targetSum:
            result.append(list(path))
        path.pop()
        curSum -= node.val
        return

    if node.left is not None:
        traverse(node.left, path, curSum, targetSum, result)
    if node.right is not None:
        traverse(node.right, path, curSum, targetSum, result)

    path.pop()
    curSum -= node.val


class Solution:
    def pathSum(self, root, targetSum):
        if root is None:
            return []

        path = deque()
        result = []
        traverse(root, path, 0, targetSum, result)
        return result
