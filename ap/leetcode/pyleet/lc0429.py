#
# Author: montreal91
# Time: 0:09
# Failed attempts: 0
#

class Node:
    def __init__(self, val=None, children=None):
        self.val = val
        self.children = children


class Solution:
    def levelOrder(self, root):
        res = []
        lvl = [root]

        while len(lvl) > 0:
            lvltrace = [node.val for node in lvl]
            res.append(lvltrace)
            new_lvl = []
            for node in lvl:
                new_lvl.extend(node.children)

            lvl = new_lvl

        return res
