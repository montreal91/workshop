
//
// Problem: https://leetcode.com/problems/path-sum/
// Author: montreal91
// Solved in 1:20
// Solution is accepted from the second attempt
// I forgot to check if the root is null.
//

using System;
using System.Diagnostics;
using Utils;

namespace leetsharp {

public class Solution0012 {
  public bool HasPathSum(TreeNode root, int sum) {
    if (root == null) {
      return false;
    }
    return HasSum(root, 0, sum);
  }

  private static bool HasSum(TreeNode current, int currentSum, int lookingSum) {
    var newSum = current.val + currentSum;
    if (IsLeaf(current)) {
      return newSum == lookingSum;
    }
    if (HasOnlyLeft(current)) {
      return HasSum(current.left, newSum, lookingSum);
    }
    if (HasOnlyRight(current)) {
      return HasSum(current.right, newSum, lookingSum);
    }

    bool isleft = HasSum(current.left, newSum, lookingSum);
    bool isright = HasSum(current.right, newSum, lookingSum);
    return isleft || isright;
  }

  private static bool IsLeaf(TreeNode node) {
    return node.left == null && node.right == null;
  }

  private static bool HasOnlyLeft(TreeNode node) {
    return node.left != null && node.right == null;
  }

  private static bool HasOnlyRight(TreeNode node) {
    return node.left == null && node.right != null;
  }

  // private static bool HasBoth

  public static void TestSolution() {
    var root0 = TreeNode.ComposeTestTree0();

    var s = new Solution0012();
    Debug.Assert(s.HasPathSum(root0, 10) == true);
    Debug.Assert(s.HasPathSum(root0, 9) == false);
    Debug.Assert(s.HasPathSum(root0, 11) == false);

    var root1 = TreeNode.ComposeTestTree1();
    Debug.Assert(s.HasPathSum(root1, 22) == true);
    Debug.Assert(s.HasPathSum(root1, 18) == true);
    Debug.Assert(s.HasPathSum(root1, 27) == true);
    Debug.Assert(s.HasPathSum(root1, 5) == false);
    Debug.Assert(s.HasPathSum(root1, 20) == false);
    Debug.Assert(s.HasPathSum(root1, 17) == false);
    Debug.Assert(s.HasPathSum(root1, -1) == false);

    var root2 = TreeNode.ComposeTestTree2();
    Debug.Assert(s.HasPathSum(root2, 0) == true);
    Debug.Assert(s.HasPathSum(root2, -3) == true);
    Debug.Assert(s.HasPathSum(root2, -1) == false);

    var root3 = TreeNode.ComposeTestTree3();
    Debug.Assert(s.HasPathSum(root3, 0) == false);
    Debug.Assert(s.HasPathSum(root3, 1) == false);
    Debug.Assert(s.HasPathSum(root3, -1) == false);

    Console.WriteLine("All tests passed.");
  }
}

} // namespace leetsharp
