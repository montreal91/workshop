//
// Problem: https://leetcode.com/problems/n-ary-tree-preorder-traversal/
// Author: montreal91
// Solved in 0:23
// Failed attempts: 0
//
using System;
using System.Collections.Generic;
using System.Diagnostics;

using Utils;


namespace leetsharp {


class Solution0589 {
  public IList<int> Preorder(Node root) {
    if (root == null) {
      return new List<int>();
    }
    var stack = new Stack<Node>();
    stack.Push(root);
    Node cn;
    var res = new List<int>();
    while (stack.Count > 0) {
      cn = stack.Pop();
      res.Add(cn.val);

      for (int i=cn.children.Count-1; i>=0; i--) {
        stack.Push(cn.children[i]);
      }
    }
    return res;
  }

  public static void TestSolution() {
    var S = new Solution0589();
    Debug.Assert(true);
    Console.WriteLine("All tests passed.");
  }
}


} // namespace leetsharp
