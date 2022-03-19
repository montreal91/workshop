#
# Author: montreal91
# Time: 0:10
# Failed attempts: 0
#

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def levelOrder(self, root):
        if root is None:
            return []

        level = [root]

        res = []

        while level:
            next_level = []
            vals = []

            for node in level:
                vals.append(node.val)

                if not node.left is None:
                    next_level.append(node.left)
                if not node.right is None:
                    next_level.append(node.right)

            level = next_level
            res.insert(vals)

        return res
