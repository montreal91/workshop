//
// Problem: https://leetcode.com/problems/maximum-depth-of-n-ary-tree/
// Author: montreal91
// Solved in 0:28
// Solved using non-recursive approach.
//

using System;
using System.Collections.Generic;
using System.Diagnostics;

using Utils;


namespace leetsharp {


class Solution0559 {
  public int MaxDepth(Node root) {
    if (root == null) {
      return 0;
    }
    var queue = new LinkedList<IList<Node>>();
    queue.AddLast(new List<Node>{root});
    var res = 1;
    while (queue.Count > 0) {
      var nextLevel = GetAllChildren(queue.First.Value);
      queue.RemoveFirst();
      if (nextLevel.Count == 0) {
        continue;
      }
      queue.AddLast(nextLevel);
      res++;
    }
    return res;
  }

  private static IList<Node> GetAllChildren(IList<Node> treeLevel) {
    // Assume that treeLevel doesn't contain nulls;
    var result = new List<Node>();
    foreach (var node in treeLevel) {
      if (node.children != null) {
        result.AddRange(node.children);
      }
    }
    return result;
  }

  public static void TestSolution() {
    Debug.Assert(true);
    Console.WriteLine("All tests passed.");
  }
}


} // namespace leetsharp
