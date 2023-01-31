package com.xmpl.leetcode;

class TreeNode {
     TreeNode left;
     TreeNode right;
}


class Solution0110 {
    private boolean good = true;

    public boolean isBalanced(TreeNode root) {
        calculateDepth(root, 0);
        return good;
    }

    int calculateDepth(TreeNode node, int currDepth) {
        if (node == null) {
            return currDepth + 1;
        }

        int left = calculateDepth(node.left, currDepth + 1);
        int right = calculateDepth(node.right, currDepth + 1);

        if (Math.abs(left - right) > 1) {
            good = false;
        }

        return Math.max(left, right);
    }
}
