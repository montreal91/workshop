
//
// Problem: https://leetcode.com/problems/maximum-depth-of-binary-tree/
// Author: montreal91
// Solved in 1:01
// Sotution is good. It took so long to compose all test cases
// and write utility functions.
//

using System;
using System.Collections.Generic;
using System.Diagnostics;


namespace leetsharp {

class Solution0104 {
  public int MaxDepth(TreeNode root) {
    return MaxDepth(root, 0);
  }

  private int MaxDepth(TreeNode node, int depth) {
    if (node == null) {
      return depth;
    }
    return Math.Max(
      MaxDepth(node.left, depth + 1),
      MaxDepth(node.right, depth + 1)
    );
  }
  public static void TestSolution() {
    var S = new Solution0104();
    var fiveNodes = new List<int>{0, 1, 2, 3, 4, 5};
    var tenNodes = new List<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    var emptyTree = MakeTree(new List<int>(), new List<List<int>>());
    var singleNodeTree = MakeTree(new List<int>{1}, new List<List<int>>());
    var singleEdgeTree = MakeTree(
      new List<int>{0, 1},
      new List<List<int>>{MakeEdge(0, 1)}
    );

    var leetTree = MakeTree(
      fiveNodes,
      new List<List<int>>{
        MakeEdge(0, 1),
        MakeEdge(0, 2),
        MakeEdge(2, 3),
        MakeEdge(2, 4)
      }
    );

    var heavyLeftTree = MakeTree(
      fiveNodes,
      new List<List<int>>{
        MakeEdge(0, 1),
        MakeEdge(0, 2),
        MakeEdge(1, 3),
        MakeEdge(3, 4)
      }
    );

    var oneBranchAppendix = MakeTree(
      fiveNodes,
      new List<List<int>> {
        MakeEdge(0, 1),
        MakeEdge(1, 2),
        MakeEdge(1, 3),
        MakeEdge(2, 4)
      }
    );

    var tenNode1 = MakeTree(
      tenNodes,
      new List<List<int>> {
        MakeEdge(0, 1),
        MakeEdge(0, 2),
        MakeEdge(1, 3),
        MakeEdge(1, 4),
        MakeEdge(2, 5),
        // MakeEdge(2, 6),
        MakeEdge(4, 7),
        MakeEdge(7, 8),
        MakeEdge(7, 9),
        MakeEdge(9, 6)
      }
    );

    var tenNode2 = MakeTree(
      tenNodes,
      new List<List<int>> {
        MakeEdge(0, 1),
        MakeEdge(0, 2),
        MakeEdge(1, 3),
        MakeEdge(2, 4),
        MakeEdge(3, 5),
        MakeEdge(3, 6),
        MakeEdge(4, 7),
        MakeEdge(4, 8),
        MakeEdge(8, 9)
      }
    );

    var tenNode3 = MakeTree(
      tenNodes,
      new List<List<int>> {
        MakeEdge(0, 1),
        MakeEdge(1, 2),
        MakeEdge(1, 9),
        MakeEdge(2, 3),
        MakeEdge(2, 4),
        MakeEdge(3, 5),
        MakeEdge(3, 6),
        MakeEdge(4, 7),
        MakeEdge(4, 8)
      }
    );
    Debug.Assert(S.MaxDepth(emptyTree) == 0);
    Debug.Assert(S.MaxDepth(singleNodeTree) == 1);
    Debug.Assert(S.MaxDepth(singleEdgeTree) == 2);
    Debug.Assert(S.MaxDepth(leetTree) == 3);
    Debug.Assert(S.MaxDepth(heavyLeftTree) == 4);
    Debug.Assert(S.MaxDepth(oneBranchAppendix) == 4);
    Debug.Assert(S.MaxDepth(tenNode1) == 6);
    Debug.Assert(S.MaxDepth(tenNode2) == 5);
    Debug.Assert(S.MaxDepth(tenNode3) == 5);
    Console.WriteLine("All tests passed.");
  }

  private static List<int> MakeEdge(int root, int child) {
    var edge = new int[] {root, child};
    return new List<int>(edge);
  }

  private static TreeNode MakeTree(List<int> nodes, List<List<int>> edges) {
    var treeNodes = new List<TreeNode>();
    foreach (var v in nodes) {
      treeNodes.Add(new TreeNode(v));
    }

    int i, j;
    foreach (var edge in edges) {
      i = edge[0];
      j = edge[1];
      CreateEdge(treeNodes[i], treeNodes[j]);
    }
    if (treeNodes.Count == 0) {
      return null;
    }
    return treeNodes[0];
  }

  private static void CreateEdge(TreeNode parent, TreeNode child) {
    if (parent.left == null) {
      parent.left = child;
      return;
    }
    if (parent.right == null) {
      parent.right = child;
      return;
    }
  }
}


} // namespace leetsharp
