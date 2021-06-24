#
# Author: montreal91
# Time: N/A
# Failed attempts: 1
#

class Solution:
    def isValidBST(self, root: TreeNode) -> bool:
        track = []
        self.traverse(root, track)
        print(track)

        for i in range(len(track)-1):
            if track[i+1] <=track[i]:
                return False
        return True

    def traverse(self, node, values):
        if node is None:
            return

        self.traverse(node.left, values)
        values.append(node.val)
        self.traverse(node.right, values)
