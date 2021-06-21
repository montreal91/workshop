#
# Author: montreal91
# Time: N/A
# Failed attempts: 1
#

from collections import deque


class Solution:
    def findMode(self, root: TreeNode) -> List[int]:
        nodes = {}
        queue = deque()
        queue.append(root)

        while len(queue) > 0:
            node = queue.pop()
            if node is None:
                continue
            if node.val in nodes:
                nodes[node.val] += 1
            else:
                nodes[node.val] = 1

            queue.append(node.left)
            queue.append(node.right)


        best = max(nodes.values())
        res = []

        for k in nodes:
            if nodes[k] == best:
                res.append(k)
        return res
